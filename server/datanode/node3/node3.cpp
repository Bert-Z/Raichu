#include "../../utils/rpcservice/service.h"
#include "../../utils/zk/zk_cpp.h"
#include "../dbservice/db.h"
#include <memory>

raichu::server::zk::zk_cpp node3_zk;
std::unique_ptr<raichu::server::db::db> node3db;
std::string path = "/node3/address";
std::string node3_address = "localhost:50053";

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

  std::string node3key = "/node3/" + key;
  raichu::server::zk::zoo_rc ret2 = node3_zk.exists_node(node3key.c_str(), nullptr, true);

  response->set_message(node3db->dbRead(key));
  return Status::OK;
}

raichu::server::Status raichu::server::KVServiceImpl::Put(ServerContext *context, const KVRequest *request,
                                                          KVResponse *response)
{
  response->set_message("Put " + request->key() + "--" + request->value() + " success.");

  std::string key = request->key(), value = request->value();
  response->set_message("Put " + key + "-" + value);

  node3db->dbPut(key, value);

  std::string node3key = "/node3/" + key;
  raichu::server::zk::zoo_rc ret2 = node3_zk.exists_node(node3key.c_str(), nullptr, true);
  if (ret2 == raichu::server::zk::z_ok)
  {
    node3_zk.set_node(node3key.c_str(), "1", -1);

    return (ret2 == raichu::server::zk::z_ok) ? Status::OK : Status::CANCELLED;
  }

  std::vector<raichu::server::zk::zoo_acl_t> acl;
  acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
  ret2 = node3_zk.create_persistent_node(node3key.c_str(), "1", acl);

  return (ret2 == raichu::server::zk::z_ok) ? Status::OK : Status::CANCELLED;
}

raichu::server::Status raichu::server::KVServiceImpl::Delete(ServerContext *context, const KVRequest *request,
                                                             KVResponse *response)
{
  response->set_message("Delete " + request->key() + " success.");

  std::string key = request->key();

  std::string node3key = "/node3/" + key;
  raichu::server::zk::zoo_rc ret2 = node3_zk.exists_node(node3key.c_str(), nullptr, true);

  if (ret2 != raichu::server::zk::z_ok)
    return Status::CANCELLED;

  // db operation
  response->set_message("delete " + key + "-" + node3db->dbRead(key));
  node3db->dbDelete(key);

  // zk operation
  ret2 = node3_zk.delete_node(node3key.c_str(), -1);

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

// zk node3 port is 2183
void zkinit(raichu::server::zk::zoo_rc &flag)
{
  std::string url = "localhost:2183";
  std::cout << "zk node3 address is " << url << std::endl;

  flag = node3_zk.connect(url);
  if (flag != raichu::server::zk::z_ok)
  {
    printf("try connect zk server failed, code[%d][%s]\n",
           flag, raichu::server::zk::zk_cpp::error_string(flag));
    return;
  }
  // initialize node3 address
  raichu::server::zk::zoo_rc ret = node3_zk.exists_node(path.c_str(), nullptr, true);
  if (ret != raichu::server::zk::z_ok)
  {
    std::vector<raichu::server::zk::zoo_acl_t> acl;
    acl.push_back(raichu::server::zk::zk_cpp::create_world_acl(raichu::server::zk::zoo_perm_all));
    // initialize node size as 0
    flag = node3_zk.create_persistent_node(path.c_str(), node3_address, acl);
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
    return 1;

  node3db.reset(new raichu::server::db::db("node3"));

  // node3 server address as localhost:50053
  raichu::server::RunServer(node3_address);

  return 0;
}
