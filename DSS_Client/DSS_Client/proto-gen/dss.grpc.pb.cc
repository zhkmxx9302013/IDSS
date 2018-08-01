// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: dss.proto

#include "dss.pb.h"
#include "dss.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace buaa {
namespace dss {

static const char* Reasoning_method_names[] = {
  "/buaa.dss.Reasoning/GetReasoningResult",
  "/buaa.dss.Reasoning/StartReasoning",
  "/buaa.dss.Reasoning/GetRuleFile",
  "/buaa.dss.Reasoning/LoadRuleFile",
  "/buaa.dss.Reasoning/GetFactSlots",
  "/buaa.dss.Reasoning/SetFactSlots",
  "/buaa.dss.Reasoning/GetFactFile",
  "/buaa.dss.Reasoning/LoadFactFile",
  "/buaa.dss.Reasoning/GetSelectedSlots",
  "/buaa.dss.Reasoning/GetVariableList",
  "/buaa.dss.Reasoning/SetMappingList",
};

std::unique_ptr< Reasoning::Stub> Reasoning::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Reasoning::Stub> stub(new Reasoning::Stub(channel));
  return stub;
}

Reasoning::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_GetReasoningResult_(Reasoning_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_StartReasoning_(Reasoning_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetRuleFile_(Reasoning_method_names[2], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_LoadRuleFile_(Reasoning_method_names[3], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_GetFactSlots_(Reasoning_method_names[4], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_SetFactSlots_(Reasoning_method_names[5], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_GetFactFile_(Reasoning_method_names[6], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_LoadFactFile_(Reasoning_method_names[7], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_GetSelectedSlots_(Reasoning_method_names[8], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_GetVariableList_(Reasoning_method_names[9], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_SetMappingList_(Reasoning_method_names[10], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  {}

::grpc::Status Reasoning::Stub::GetReasoningResult(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::buaa::facts::result* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetReasoningResult_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::buaa::facts::result>* Reasoning::Stub::AsyncGetReasoningResultRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::buaa::facts::result>::Create(channel_.get(), cq, rpcmethod_GetReasoningResult_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::buaa::facts::result>* Reasoning::Stub::PrepareAsyncGetReasoningResultRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::buaa::facts::result>::Create(channel_.get(), cq, rpcmethod_GetReasoningResult_, context, request, false);
}

::grpc::Status Reasoning::Stub::StartReasoning(::grpc::ClientContext* context, const ::buaa::facts::sim_start& request, ::buaa::dss::placeholder* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_StartReasoning_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::buaa::dss::placeholder>* Reasoning::Stub::AsyncStartReasoningRaw(::grpc::ClientContext* context, const ::buaa::facts::sim_start& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::buaa::dss::placeholder>::Create(channel_.get(), cq, rpcmethod_StartReasoning_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::buaa::dss::placeholder>* Reasoning::Stub::PrepareAsyncStartReasoningRaw(::grpc::ClientContext* context, const ::buaa::facts::sim_start& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::buaa::dss::placeholder>::Create(channel_.get(), cq, rpcmethod_StartReasoning_, context, request, false);
}

::grpc::ClientReader< ::buaa::file::rule_file_info>* Reasoning::Stub::GetRuleFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request) {
  return ::grpc::internal::ClientReaderFactory< ::buaa::file::rule_file_info>::Create(channel_.get(), rpcmethod_GetRuleFile_, context, request);
}

::grpc::ClientAsyncReader< ::buaa::file::rule_file_info>* Reasoning::Stub::AsyncGetRuleFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::rule_file_info>::Create(channel_.get(), cq, rpcmethod_GetRuleFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::buaa::file::rule_file_info>* Reasoning::Stub::PrepareAsyncGetRuleFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::rule_file_info>::Create(channel_.get(), cq, rpcmethod_GetRuleFile_, context, request, false, nullptr);
}

::grpc::ClientWriter< ::buaa::file::rule_file_chk>* Reasoning::Stub::LoadRuleFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response) {
  return ::grpc::internal::ClientWriterFactory< ::buaa::file::rule_file_chk>::Create(channel_.get(), rpcmethod_LoadRuleFile_, context, response);
}

::grpc::ClientAsyncWriter< ::buaa::file::rule_file_chk>* Reasoning::Stub::AsyncLoadRuleFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::rule_file_chk>::Create(channel_.get(), cq, rpcmethod_LoadRuleFile_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::buaa::file::rule_file_chk>* Reasoning::Stub::PrepareAsyncLoadRuleFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::rule_file_chk>::Create(channel_.get(), cq, rpcmethod_LoadRuleFile_, context, response, false, nullptr);
}

::grpc::ClientReader< ::buaa::file::fact_list>* Reasoning::Stub::GetFactSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request) {
  return ::grpc::internal::ClientReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), rpcmethod_GetFactSlots_, context, request);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_list>* Reasoning::Stub::AsyncGetFactSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_GetFactSlots_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_list>* Reasoning::Stub::PrepareAsyncGetFactSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_GetFactSlots_, context, request, false, nullptr);
}

::grpc::ClientWriter< ::buaa::file::fact_list>* Reasoning::Stub::SetFactSlotsRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response) {
  return ::grpc::internal::ClientWriterFactory< ::buaa::file::fact_list>::Create(channel_.get(), rpcmethod_SetFactSlots_, context, response);
}

::grpc::ClientAsyncWriter< ::buaa::file::fact_list>* Reasoning::Stub::AsyncSetFactSlotsRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_SetFactSlots_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::buaa::file::fact_list>* Reasoning::Stub::PrepareAsyncSetFactSlotsRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_SetFactSlots_, context, response, false, nullptr);
}

::grpc::ClientReader< ::buaa::file::fact_file_info>* Reasoning::Stub::GetFactFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request) {
  return ::grpc::internal::ClientReaderFactory< ::buaa::file::fact_file_info>::Create(channel_.get(), rpcmethod_GetFactFile_, context, request);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_file_info>* Reasoning::Stub::AsyncGetFactFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_file_info>::Create(channel_.get(), cq, rpcmethod_GetFactFile_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_file_info>* Reasoning::Stub::PrepareAsyncGetFactFileRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_file_info>::Create(channel_.get(), cq, rpcmethod_GetFactFile_, context, request, false, nullptr);
}

::grpc::ClientWriter< ::buaa::file::fact_file_chk>* Reasoning::Stub::LoadFactFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response) {
  return ::grpc::internal::ClientWriterFactory< ::buaa::file::fact_file_chk>::Create(channel_.get(), rpcmethod_LoadFactFile_, context, response);
}

::grpc::ClientAsyncWriter< ::buaa::file::fact_file_chk>* Reasoning::Stub::AsyncLoadFactFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::fact_file_chk>::Create(channel_.get(), cq, rpcmethod_LoadFactFile_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::buaa::file::fact_file_chk>* Reasoning::Stub::PrepareAsyncLoadFactFileRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::fact_file_chk>::Create(channel_.get(), cq, rpcmethod_LoadFactFile_, context, response, false, nullptr);
}

::grpc::ClientReader< ::buaa::file::fact_list>* Reasoning::Stub::GetSelectedSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request) {
  return ::grpc::internal::ClientReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), rpcmethod_GetSelectedSlots_, context, request);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_list>* Reasoning::Stub::AsyncGetSelectedSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_GetSelectedSlots_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_list>* Reasoning::Stub::PrepareAsyncGetSelectedSlotsRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_list>::Create(channel_.get(), cq, rpcmethod_GetSelectedSlots_, context, request, false, nullptr);
}

::grpc::ClientReader< ::buaa::file::fact_var>* Reasoning::Stub::GetVariableListRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request) {
  return ::grpc::internal::ClientReaderFactory< ::buaa::file::fact_var>::Create(channel_.get(), rpcmethod_GetVariableList_, context, request);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_var>* Reasoning::Stub::AsyncGetVariableListRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_var>::Create(channel_.get(), cq, rpcmethod_GetVariableList_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::buaa::file::fact_var>* Reasoning::Stub::PrepareAsyncGetVariableListRaw(::grpc::ClientContext* context, const ::buaa::dss::placeholder& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::buaa::file::fact_var>::Create(channel_.get(), cq, rpcmethod_GetVariableList_, context, request, false, nullptr);
}

::grpc::ClientWriter< ::buaa::file::mapper>* Reasoning::Stub::SetMappingListRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response) {
  return ::grpc::internal::ClientWriterFactory< ::buaa::file::mapper>::Create(channel_.get(), rpcmethod_SetMappingList_, context, response);
}

::grpc::ClientAsyncWriter< ::buaa::file::mapper>* Reasoning::Stub::AsyncSetMappingListRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::mapper>::Create(channel_.get(), cq, rpcmethod_SetMappingList_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::buaa::file::mapper>* Reasoning::Stub::PrepareAsyncSetMappingListRaw(::grpc::ClientContext* context, ::buaa::dss::placeholder* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::buaa::file::mapper>::Create(channel_.get(), cq, rpcmethod_SetMappingList_, context, response, false, nullptr);
}

Reasoning::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::facts::result>(
          std::mem_fn(&Reasoning::Service::GetReasoningResult), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Reasoning::Service, ::buaa::facts::sim_start, ::buaa::dss::placeholder>(
          std::mem_fn(&Reasoning::Service::StartReasoning), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[2],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::file::rule_file_info>(
          std::mem_fn(&Reasoning::Service::GetRuleFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[3],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< Reasoning::Service, ::buaa::file::rule_file_chk, ::buaa::dss::placeholder>(
          std::mem_fn(&Reasoning::Service::LoadRuleFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[4],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::file::fact_list>(
          std::mem_fn(&Reasoning::Service::GetFactSlots), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[5],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< Reasoning::Service, ::buaa::file::fact_list, ::buaa::dss::placeholder>(
          std::mem_fn(&Reasoning::Service::SetFactSlots), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[6],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::file::fact_file_info>(
          std::mem_fn(&Reasoning::Service::GetFactFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[7],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< Reasoning::Service, ::buaa::file::fact_file_chk, ::buaa::dss::placeholder>(
          std::mem_fn(&Reasoning::Service::LoadFactFile), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[8],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::file::fact_list>(
          std::mem_fn(&Reasoning::Service::GetSelectedSlots), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[9],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< Reasoning::Service, ::buaa::dss::placeholder, ::buaa::file::fact_var>(
          std::mem_fn(&Reasoning::Service::GetVariableList), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Reasoning_method_names[10],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< Reasoning::Service, ::buaa::file::mapper, ::buaa::dss::placeholder>(
          std::mem_fn(&Reasoning::Service::SetMappingList), this)));
}

Reasoning::Service::~Service() {
}

::grpc::Status Reasoning::Service::GetReasoningResult(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::buaa::facts::result* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::StartReasoning(::grpc::ServerContext* context, const ::buaa::facts::sim_start* request, ::buaa::dss::placeholder* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::GetRuleFile(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::grpc::ServerWriter< ::buaa::file::rule_file_info>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::LoadRuleFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::buaa::file::rule_file_chk>* reader, ::buaa::dss::placeholder* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::GetFactSlots(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::grpc::ServerWriter< ::buaa::file::fact_list>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::SetFactSlots(::grpc::ServerContext* context, ::grpc::ServerReader< ::buaa::file::fact_list>* reader, ::buaa::dss::placeholder* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::GetFactFile(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::grpc::ServerWriter< ::buaa::file::fact_file_info>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::LoadFactFile(::grpc::ServerContext* context, ::grpc::ServerReader< ::buaa::file::fact_file_chk>* reader, ::buaa::dss::placeholder* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::GetSelectedSlots(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::grpc::ServerWriter< ::buaa::file::fact_list>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::GetVariableList(::grpc::ServerContext* context, const ::buaa::dss::placeholder* request, ::grpc::ServerWriter< ::buaa::file::fact_var>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Reasoning::Service::SetMappingList(::grpc::ServerContext* context, ::grpc::ServerReader< ::buaa::file::mapper>* reader, ::buaa::dss::placeholder* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace buaa
}  // namespace dss
