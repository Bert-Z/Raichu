#include "../../utils/rpcservice/service.h"
#include "../../utils/zk/zk_cpp.h"

raichu::server::zk::zk_cpp zk;

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
  return Status::OK;
}

raichu::server::Status raichu::server::KVServiceImpl::Put(ServerContext *context, const KVRequest *request,
                                                          KVResponse *response)
{
  response->set_message("Put " + request->key() + "--" + request->value() + " success.");
  return Status::OK;
}

raichu::server::Status raichu::server::KVServiceImpl::Delete(ServerContext *context, const KVRequest *request,
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

// zk node3 port is 2183
void zkinit(raichu::server::zk::zoo_rc &flag)
{
  std::string url = "localhost:2183";
  std::cout << "zk node3 address is " << url << std::endl;

  flag = zk.connect(url);
  if (flag != raichu::server::zk::z_ok)
  {
    printf("try connect zk server failed, code[%d][%s]\n",
           flag, raichu::server::zk::zk_cpp::error_string(flag));
    return;
  }
}

int main(int argc, char **argv)
{
  // zk init
  raichu::server::zk::zoo_rc flag = raichu::server::zk::z_ok;
  zkinit(flag);
  if (flag != raichu::server::zk::z_ok)
    return 1;

  // node3 server address as localhost:50053
  raichu::server::RunServer("0.0.0.0:50053");

  return 0;
}
