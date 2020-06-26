// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc.proto

#include "rpc.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace rpc {
class KVRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<KVRequest> _instance;
} _KVRequest_default_instance_;
class KVResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<KVResponse> _instance;
} _KVResponse_default_instance_;
}  // namespace rpc
static void InitDefaultsscc_info_KVRequest_rpc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::rpc::_KVRequest_default_instance_;
    new (ptr) ::rpc::KVRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::rpc::KVRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_KVRequest_rpc_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_KVRequest_rpc_2eproto}, {}};

static void InitDefaultsscc_info_KVResponse_rpc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::rpc::_KVResponse_default_instance_;
    new (ptr) ::rpc::KVResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::rpc::KVResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_KVResponse_rpc_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_KVResponse_rpc_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_rpc_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_rpc_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_rpc_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_rpc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::rpc::KVRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::rpc::KVRequest, key_),
  PROTOBUF_FIELD_OFFSET(::rpc::KVRequest, value_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::rpc::KVResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::rpc::KVResponse, message_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::rpc::KVRequest)},
  { 7, -1, sizeof(::rpc::KVResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::rpc::_KVRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::rpc::_KVResponse_default_instance_),
};

const char descriptor_table_protodef_rpc_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\trpc.proto\022\003rpc\"\'\n\tKVRequest\022\013\n\003key\030\001 \001"
  "(\t\022\r\n\005value\030\002 \001(\t\"\035\n\nKVResponse\022\017\n\007messa"
  "ge\030\001 \001(\t2\206\001\n\002KV\022)\n\004Read\022\016.rpc.KVRequest\032"
  "\017.rpc.KVResponse\"\000\022(\n\003Put\022\016.rpc.KVReques"
  "t\032\017.rpc.KVResponse\"\000\022+\n\006Delete\022\016.rpc.KVR"
  "equest\032\017.rpc.KVResponse\"\000B(\n\024io.grpc.exa"
  "mples.rpcB\010rpcProtoP\001\242\002\003HLWb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_rpc_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_rpc_2eproto_sccs[2] = {
  &scc_info_KVRequest_rpc_2eproto.base,
  &scc_info_KVResponse_rpc_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_rpc_2eproto_once;
static bool descriptor_table_rpc_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_rpc_2eproto = {
  &descriptor_table_rpc_2eproto_initialized, descriptor_table_protodef_rpc_2eproto, "rpc.proto", 275,
  &descriptor_table_rpc_2eproto_once, descriptor_table_rpc_2eproto_sccs, descriptor_table_rpc_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_rpc_2eproto::offsets,
  file_level_metadata_rpc_2eproto, 2, file_level_enum_descriptors_rpc_2eproto, file_level_service_descriptors_rpc_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_rpc_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_rpc_2eproto), true);
namespace rpc {

// ===================================================================

void KVRequest::InitAsDefaultInstance() {
}
class KVRequest::_Internal {
 public:
};

KVRequest::KVRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:rpc.KVRequest)
}
KVRequest::KVRequest(const KVRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_key().empty()) {
    key_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.key_);
  }
  value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_value().empty()) {
    value_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.value_);
  }
  // @@protoc_insertion_point(copy_constructor:rpc.KVRequest)
}

void KVRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_KVRequest_rpc_2eproto.base);
  key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

KVRequest::~KVRequest() {
  // @@protoc_insertion_point(destructor:rpc.KVRequest)
  SharedDtor();
}

void KVRequest::SharedDtor() {
  key_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  value_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void KVRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const KVRequest& KVRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_KVRequest_rpc_2eproto.base);
  return *internal_default_instance();
}


void KVRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:rpc.KVRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  key_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  value_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

const char* KVRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string key = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_key();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "rpc.KVRequest.key"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string value = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "rpc.KVRequest.value"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KVRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:rpc.KVRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string key = 1;
  if (this->key().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_key().data(), static_cast<int>(this->_internal_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "rpc.KVRequest.key");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_key(), target);
  }

  // string value = 2;
  if (this->value().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_value().data(), static_cast<int>(this->_internal_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "rpc.KVRequest.value");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:rpc.KVRequest)
  return target;
}

size_t KVRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:rpc.KVRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string key = 1;
  if (this->key().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_key());
  }

  // string value = 2;
  if (this->value().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_value());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KVRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:rpc.KVRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const KVRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KVRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:rpc.KVRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:rpc.KVRequest)
    MergeFrom(*source);
  }
}

void KVRequest::MergeFrom(const KVRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:rpc.KVRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.key().size() > 0) {

    key_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.key_);
  }
  if (from.value().size() > 0) {

    value_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.value_);
  }
}

void KVRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:rpc.KVRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KVRequest::CopyFrom(const KVRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:rpc.KVRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KVRequest::IsInitialized() const {
  return true;
}

void KVRequest::InternalSwap(KVRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  key_.Swap(&other->key_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  value_.Swap(&other->value_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata KVRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void KVResponse::InitAsDefaultInstance() {
}
class KVResponse::_Internal {
 public:
};

KVResponse::KVResponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:rpc.KVResponse)
}
KVResponse::KVResponse(const KVResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_message().empty()) {
    message_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.message_);
  }
  // @@protoc_insertion_point(copy_constructor:rpc.KVResponse)
}

void KVResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_KVResponse_rpc_2eproto.base);
  message_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

KVResponse::~KVResponse() {
  // @@protoc_insertion_point(destructor:rpc.KVResponse)
  SharedDtor();
}

void KVResponse::SharedDtor() {
  message_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void KVResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const KVResponse& KVResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_KVResponse_rpc_2eproto.base);
  return *internal_default_instance();
}


void KVResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:rpc.KVResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  message_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

const char* KVResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string message = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_message();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "rpc.KVResponse.message"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* KVResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:rpc.KVResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string message = 1;
  if (this->message().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_message().data(), static_cast<int>(this->_internal_message().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "rpc.KVResponse.message");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_message(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:rpc.KVResponse)
  return target;
}

size_t KVResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:rpc.KVResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string message = 1;
  if (this->message().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_message());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void KVResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:rpc.KVResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const KVResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<KVResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:rpc.KVResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:rpc.KVResponse)
    MergeFrom(*source);
  }
}

void KVResponse::MergeFrom(const KVResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:rpc.KVResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.message().size() > 0) {

    message_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.message_);
  }
}

void KVResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:rpc.KVResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void KVResponse::CopyFrom(const KVResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:rpc.KVResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KVResponse::IsInitialized() const {
  return true;
}

void KVResponse::InternalSwap(KVResponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  message_.Swap(&other->message_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata KVResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace rpc
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::rpc::KVRequest* Arena::CreateMaybeMessage< ::rpc::KVRequest >(Arena* arena) {
  return Arena::CreateInternal< ::rpc::KVRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::rpc::KVResponse* Arena::CreateMaybeMessage< ::rpc::KVResponse >(Arena* arena) {
  return Arena::CreateInternal< ::rpc::KVResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
