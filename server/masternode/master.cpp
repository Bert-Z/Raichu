#include "../utils/rpcservice/service.h"
#include "../utils/zk/zk_cpp.h"
#include <boost/functional/hash.hpp>
#include <boost/format.hpp>
#include <boost/crc.hpp>
#include "../../consistent-hash/consistent-hash.h"

raichu::server::zk::zk_cpp master_zk;
std::string path2 = "/node2", path3 = "/node3";
const std::string nodes[] = {
    "/node2",
    "/node3"};

using raichu::server::KVServiceImpl;
using raichu::server::Status;

struct vnode_t
{
  vnode_t() {}
  vnode_t(std::size_t n, std::size_t v) : node_id(n), vnode_id(v) {}

  std::string to_str() const
  {
    return boost::str(boost::format("%1%-%2%") % nodes[node_id] % vnode_id);
  }

  std::size_t node_id;
  std::size_t vnode_id;
};

struct crc32_hasher
{
  uint32_t operator()(const vnode_t &node)
  {
    boost::crc_32_type ret;
    std::string vnode = node.to_str();
    ret.process_bytes(vnode.c_str(), vnode.size());
    return ret.checksum();
  }
  uint32_t operator()(std::string &key)
  {
    boost::crc_32_type ret;
    std::string vnode = key;
    // std::cout << "vnode:" << vnode << std::endl;
    ret.process_bytes(vnode.c_str(), vnode.size());
    return ret.checksum();
  }
  using result_type = uint32_t;
};

using consistent_hash_t = raichu::hash::consistent_hash_map<vnode_t, crc32_hasher>;
consistent_hash_t consistent_hash_;

void consistentHashInit()
{
  for (std::size_t i = 0; i < 2; ++i)
  {
    for (std::size_t j = 0; j < 100; j++)
    {
      consistent_hash_.insert(vnode_t(i, j));
    }
  }
}

std::size_t getNodeSize(const std::string &path)
{
  std::string value;
  std::vector<std::string> children;
  raichu::server::zk::zoo_rc ret = master_zk.get_children(path.c_str(), children, true);
  printf("try get path[%s]'s children's, children count[%d], ret[%d][%s]\n",
         path.c_str(), (int32_t)children.size(), ret, raichu::server::zk::zk_cpp::error_string(ret));
  return children.size();
}

std::string getNodeAddress(const std::string &path)
{
  std::string value;
  raichu::server::zk::zoo_rc ret = master_zk.get_node(path.c_str(), value, nullptr, true);
  printf("try get path[%s]'s value, value[%s] ret[%d][%s]\n", path.c_str(), value.c_str(), ret, raichu::server::zk::zk_cpp::error_string(ret));
  return value;
}

// rpc sevice implement
Status KVServiceImpl::Where(ServerContext *context, const KVRequest *request,
                            KVResponse *response)
{
  std::string key = request->key(), value = request->value();
  consistent_hash_t::iterator it = consistent_hash_.find(crc32_hasher().operator()(key));
  printf("%s\n",(nodes[it->second.node_id] + "/" + key).c_str());
  std::string node2key = "/node2/" + key, node3key = "/node3/" + key;
  raichu::server::zk::zoo_rc ret2 = master_zk.exists_node(node2key.c_str(), nullptr, true);
  raichu::server::zk::zoo_rc ret3 = master_zk.exists_node(node3key.c_str(), nullptr, true);
  if (ret2 == raichu::server::zk::z_ok)
  {
    response->set_message(getNodeAddress("/node2/address"));
    return Status::OK;
  }
  else if (ret3 == raichu::server::zk::z_ok)
  {
    response->set_message(getNodeAddress("/node3/address"));
    return Status::OK;
  }

  if (value.size() != 0)
  {
    response->set_message(getNodeAddress(nodes[it->second.node_id] + "/address"));
    return Status::OK;
  }
  else
  {
    printf("%s is not exist.\n",key.c_str());
    response->set_message(key + " is not exist.");
    return Status::CANCELLED;
  }
}

Status KVServiceImpl::Read(ServerContext *context, const KVRequest *request,
                           KVResponse *response)
{
  response->set_message("Read " + request->key() + " success.");
  return Status::OK;
}

Status KVServiceImpl::Put(ServerContext *context, const KVRequest *request,
                          KVResponse *response)
{
  response->set_message("Put " + request->key() + "--" + request->value() + " success.");
  return Status::OK;
}

Status KVServiceImpl::Delete(ServerContext *context, const KVRequest *request,
                             KVResponse *response)
{
  response->set_message("Delete " + request->key() + " success.");
  return Status::OK;
}

void raichu::server::RunServer(const std::string &address)
{
  std::string server_address(address);

  // kv service
  KVServiceImpl kvservice;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&kvservice);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

// zk master node port is 2182
void zkinit(raichu::server::zk::zoo_rc &flag)
{
  std::string url = "localhost:2182";
  std::cout << "zk master node address is " << url << std::endl;

  flag = master_zk.connect(url);
  if (flag != raichu::server::zk::z_ok)
  {
    printf("try connect zk server failed, code[%d][%s]\n",
           flag, raichu::server::zk::zk_cpp::error_string(flag));
    return;
  }

  // initialize node2 and node3 if empty
  raichu::server::zk::zoo_rc ret = master_zk.exists_node(path2.c_str(), nullptr, true);
  if (ret != raichu::server::zk::z_ok)
  {
    std::vector<raichu::server::zk::zoo_acl_t> acl;
    acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
    // initialize node size as 0
    flag = master_zk.create_persistent_node(path2.c_str(), "0", acl);
    if (flag != raichu::server::zk::z_ok)
    {
      printf("try to create node2 failed, code[%d][%s]\n",
             flag, raichu::server::zk::zk_cpp::error_string(flag));
      return;
    }
  }
  ret = master_zk.exists_node(path3.c_str(), nullptr, true);
  if (ret != raichu::server::zk::z_ok)
  {
    std::vector<raichu::server::zk::zoo_acl_t> acl;
    acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
    // initialize node size as 0
    flag = master_zk.create_persistent_node(path3.c_str(), "0", acl);
    if (flag != raichu::server::zk::z_ok)
    {
      printf("try to create node3 failed, code[%d][%s]\n",
             flag, raichu::server::zk::zk_cpp::error_string(flag));
      return;
    }
  }
}

int main(int argc, char **argv)
{
  // zk init
  raichu::server::zk::zoo_rc flag = raichu::server::zk::z_ok;
  zkinit(flag);
  if (flag != raichu::server::zk::z_ok)
    return 0;

  // consistent hash
  consistentHashInit();

  // master server address as localhost:50051
  raichu::server::RunServer("0.0.0.0:50051");

  return 0;
}
