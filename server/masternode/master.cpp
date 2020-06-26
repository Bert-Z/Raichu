#include "../utils/rpcservice/service.h"
#include "../utils/zk/zk_cpp.h"

raichu::server::zk::zk_cpp master_zk;
std::string path2 = "/node2", path3 = "/node3";

using raichu::server::KVServiceImpl;
using raichu::server::Status;

long getNodeSize(const std::string &path)
{
  std::string value;
  raichu::server::zk::zoo_rc ret = master_zk.get_node(path2.c_str(), value, nullptr, true);
  printf("try get path[%s]'s value, value[%s] ret[%d][%s]\n", path2.c_str(), value.c_str(), ret, raichu::server::zk::zk_cpp::error_string(ret));
  return std::stol(value);
}

std::string getNodeAddress(const std::string &path)
{
  std::string value;
  raichu::server::zk::zoo_rc ret = master_zk.get_node(path2.c_str(), value, nullptr, true);
  printf("try get path[%s]'s value, value[%s] ret[%d][%s]\n", path2.c_str(), value.c_str(), ret, raichu::server::zk::zk_cpp::error_string(ret));
  return value;
}

// rpc sevice implement
Status KVServiceImpl::Where(ServerContext *context, const KVRequest *request,
                            KVResponse *response)
{
  std::string key = request->key(), value = request->value();

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
    long node2_size = getNodeSize("/node2");
    long node3_size = getNodeSize("/node3");
    if (node2_size <= node3_size)
    {
      response->set_message(getNodeAddress("/node2/address"));
      return Status::OK;
    }
    else
    {
      response->set_message(getNodeAddress("/node3/address"));
      return Status::OK;
    }
  }
  else
  {
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

  // master server address as localhost:50051
  raichu::server::RunServer("0.0.0.0:50051");

  return 0;
}
