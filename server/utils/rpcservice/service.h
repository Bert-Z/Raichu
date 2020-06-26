#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "../../../rpc-proto/rpc.grpc.pb.h"

namespace raichu
{
    namespace server
    {
        using grpc::Server;
        using grpc::ServerBuilder;
        using grpc::ServerContext;
        using grpc::Status;

        // KV server rpc
        using rpc::KV;
        using rpc::KVRequest;
        using rpc::KVResponse;

        class KVServiceImpl final : public KV::Service
        {
            Status Where(ServerContext *context, const KVRequest *request,
                         KVResponse *response) override;

            Status Read(ServerContext *context, const KVRequest *request,
                        KVResponse *response) override;

            Status Put(ServerContext *context, const KVRequest *request,
                       KVResponse *response) override;

            Status Delete(ServerContext *context, const KVRequest *request,
                          KVResponse *response) override;
        };

        void RunServer(const std::string &address);
    } // namespace server
} // namespace raichu
