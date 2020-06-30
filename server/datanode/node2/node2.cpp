#include "../../utils/rpcservice/service.h"
#include "../../utils/zk/zk_cpp.h"
#include "../dbservice/db.h"
#include <memory>

raichu::server::zk::zk_cpp node2_zk;
std::unique_ptr<raichu::server::db::db> node2db;
std::string path = "/node2/address";
std::string node2_address = "localhost:50052";

// rpc sevice implement
raichu::server::Status raichu::server::KVServiceImpl::Where(ServerContext *context, const KVRequest *request,
                                                            KVResponse *response)
{
  response->set_message("");
  return Status::OK;
}

raichu::server::Status raichu::server::KVServiceImpl::Read(ServerContext *context, const KVRequest *request,
                                                           KVResponse *response)
{
  response->set_message("Read " + request->key() + " success.");

  std::string key = request->key();

  std::string node2key = "/node2/" + key;
  raichu::server::zk::zoo_rc ret2 = node2_zk.exists_node(node2key.c_str(), nullptr, true);

  response->set_message(node2db->dbRead(key));
  return Status::OK;
}

raichu::server::Status raichu::server::KVServiceImpl::Put(ServerContext *context, const KVRequest *request,
                                                          KVResponse *response)
{
  response->set_message("Put " + request->key() + "--" + request->value() + " success.");

  std::string key = request->key(), value = request->value();
  response->set_message("Put " + key + "-" + value);

  node2db->dbPut(key, value);

  std::string node2key = "/node2/" + key;
  raichu::server::zk::zoo_rc ret2 = node2_zk.exists_node(node2key.c_str(), nullptr, true);
  if (ret2 == raichu::server::zk::z_ok)
  {
    node2_zk.set_node(node2key.c_str(), "1", -1);

    return (ret2 == raichu::server::zk::z_ok) ? Status::OK : Status::CANCELLED;
  }

  std::vector<raichu::server::zk::zoo_acl_t> acl;
  acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
  ret2 = node2_zk.create_persistent_node(node2key.c_str(), "1", acl);

  return (ret2 == raichu::server::zk::z_ok) ? Status::OK : Status::CANCELLED;
}

raichu::server::Status raichu::server::KVServiceImpl::Delete(ServerContext *context, const KVRequest *request,
                                                             KVResponse *response)
{
  response->set_message("Delete " + request->key() + " success.");

  std::string key = request->key();

  std::string node2key = "/node2/" + key;
  raichu::server::zk::zoo_rc ret2 = node2_zk.exists_node(node2key.c_str(), nullptr, true);

  if (ret2 != raichu::server::zk::z_ok)
    return Status::CANCELLED;

  // db operation
  response->set_message("delete " + key + "-" + node2db->dbRead(key));
  node2db->dbDelete(key);

  // zk operation
  ret2 = node2_zk.delete_node(node2key.c_str(), -1);

  return (ret2 == raichu::server::zk::z_ok) ? Status::OK : Status::CANCELLED;
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

// zk node2 port is 2181
void zkinit(raichu::server::zk::zoo_rc &flag)
{
  std::string url = "localhost:2181";
  std::cout << "zk node2 address is " << url << std::endl;

  flag = node2_zk.connect(url);
  if (flag != raichu::server::zk::z_ok)
  {
    printf("try connect zk server failed, code[%d][%s]\n",
           flag, raichu::server::zk::zk_cpp::error_string(flag));
    return;
  }
  // initialize node2 address
  raichu::server::zk::zoo_rc ret = node2_zk.exists_node(path.c_str(), nullptr, true);
  if (ret != raichu::server::zk::z_ok)
  {
    std::vector<raichu::server::zk::zoo_acl_t> acl;
    acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
    // initialize node size as 0
    flag = node2_zk.create_persistent_node(path.c_str(), node2_address, acl);
    if (flag != raichu::server::zk::z_ok)
    {
      printf("try to create node2 failed, code[%d][%s]\n",
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
    return 1;

  node2db.reset(new raichu::server::db::db("node2"));

  // node3 server address as localhost:50052
  raichu::server::RunServer(node2_address);

  return 0;
}
