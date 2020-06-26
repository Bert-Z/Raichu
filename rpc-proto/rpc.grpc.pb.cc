// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rpc.proto

#include "rpc.pb.h"
#include "rpc.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace rpc {

static const char* KV_method_names[] = {
  "/rpc.KV/Where",
  "/rpc.KV/Read",
  "/rpc.KV/Put",
  "/rpc.KV/Delete",
};

std::unique_ptr< KV::Stub> KV::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< KV::Stub> stub(new KV::Stub(channel));
  return stub;
}

KV::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Where_(KV_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Read_(KV_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Put_(KV_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Delete_(KV_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status KV::Stub::Where(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::rpc::KVResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Where_, context, request, response);
}

void KV::Stub::experimental_async::Where(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Where_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Where(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Where_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Where(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Where_, context, request, response, reactor);
}

void KV::Stub::experimental_async::Where(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Where_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::AsyncWhereRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Where_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::PrepareAsyncWhereRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Where_, context, request, false);
}

::grpc::Status KV::Stub::Read(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::rpc::KVResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Read_, context, request, response);
}

void KV::Stub::experimental_async::Read(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Read_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Read(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Read_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Read(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Read_, context, request, response, reactor);
}

void KV::Stub::experimental_async::Read(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Read_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::AsyncReadRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Read_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::PrepareAsyncReadRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Read_, context, request, false);
}

::grpc::Status KV::Stub::Put(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::rpc::KVResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Put_, context, request, response);
}

void KV::Stub::experimental_async::Put(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Put(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Put(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, reactor);
}

void KV::Stub::experimental_async::Put(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::AsyncPutRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::PrepareAsyncPutRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Put_, context, request, false);
}

::grpc::Status KV::Stub::Delete(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::rpc::KVResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Delete_, context, request, response);
}

void KV::Stub::experimental_async::Delete(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Delete_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Delete(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Delete_, context, request, response, std::move(f));
}

void KV::Stub::experimental_async::Delete(::grpc::ClientContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Delete_, context, request, response, reactor);
}

void KV::Stub::experimental_async::Delete(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::rpc::KVResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Delete_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::AsyncDeleteRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Delete_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::rpc::KVResponse>* KV::Stub::PrepareAsyncDeleteRaw(::grpc::ClientContext* context, const ::rpc::KVRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::rpc::KVResponse>::Create(channel_.get(), cq, rpcmethod_Delete_, context, request, false);
}

KV::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KV_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KV::Service, ::rpc::KVRequest, ::rpc::KVResponse>(
          std::mem_fn(&KV::Service::Where), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KV_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KV::Service, ::rpc::KVRequest, ::rpc::KVResponse>(
          std::mem_fn(&KV::Service::Read), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KV_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KV::Service, ::rpc::KVRequest, ::rpc::KVResponse>(
          std::mem_fn(&KV::Service::Put), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      KV_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< KV::Service, ::rpc::KVRequest, ::rpc::KVResponse>(
          std::mem_fn(&KV::Service::Delete), this)));
}

KV::Service::~Service() {
}

::grpc::Status KV::Service::Where(::grpc::ServerContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KV::Service::Read(::grpc::ServerContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KV::Service::Put(::grpc::ServerContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status KV::Service::Delete(::grpc::ServerContext* context, const ::rpc::KVRequest* request, ::rpc::KVResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace rpc

