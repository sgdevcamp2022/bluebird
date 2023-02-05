// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProtocolMatch.proto

#include "ProtocolMatch.pb.h"

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

PROTOBUF_PRAGMA_INIT_SEG
namespace Match {
constexpr Header::Header(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : size_(0u)
  , state_(0)
{}
struct HeaderDefaultTypeInternal {
  constexpr HeaderDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~HeaderDefaultTypeInternal() {}
  union {
    Header _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT HeaderDefaultTypeInternal _Header_default_instance_;
constexpr Data::Data(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : id_(int64_t{0})
  , level_(0)
  , room_(0)
  , state_(false){}
struct DataDefaultTypeInternal {
  constexpr DataDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~DataDefaultTypeInternal() {}
  union {
    Data _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT DataDefaultTypeInternal _Data_default_instance_;
constexpr Success::Success(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : id_(int64_t{0})
  , room_(0)
  , gameport_(0){}
struct SuccessDefaultTypeInternal {
  constexpr SuccessDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~SuccessDefaultTypeInternal() {}
  union {
    Success _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT SuccessDefaultTypeInternal _Success_default_instance_;
}  // namespace Match
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ProtocolMatch_2eproto[3];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_ProtocolMatch_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ProtocolMatch_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ProtocolMatch_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Match::Header, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Match::Header, size_),
  PROTOBUF_FIELD_OFFSET(::Match::Header, state_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Match::Data, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Match::Data, id_),
  PROTOBUF_FIELD_OFFSET(::Match::Data, level_),
  PROTOBUF_FIELD_OFFSET(::Match::Data, room_),
  PROTOBUF_FIELD_OFFSET(::Match::Data, state_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Match::Success, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::Match::Success, id_),
  PROTOBUF_FIELD_OFFSET(::Match::Success, room_),
  PROTOBUF_FIELD_OFFSET(::Match::Success, gameport_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::Match::Header)},
  { 7, -1, sizeof(::Match::Data)},
  { 16, -1, sizeof(::Match::Success)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Match::_Header_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Match::_Data_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::Match::_Success_default_instance_),
};

const char descriptor_table_protodef_ProtocolMatch_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023ProtocolMatch.proto\022\005Match\"3\n\006Header\022\014"
  "\n\004size\030\001 \001(\r\022\033\n\005state\030\002 \001(\0162\014.Match.STAT"
  "E\">\n\004Data\022\n\n\002id\030\001 \001(\003\022\r\n\005level\030\002 \001(\005\022\014\n\004"
  "room\030\003 \001(\005\022\r\n\005state\030\004 \001(\010\"5\n\007Success\022\n\n\002"
  "id\030\001 \001(\003\022\014\n\004room\030\002 \001(\005\022\020\n\010gamePort\030\003 \001(\005"
  "*^\n\005STATE\022\010\n\004NULL\020\000\022\013\n\007C_LOGIN\020\001\022\014\n\010C_CA"
  "NCLE\020\002\022\010\n\004FAIL\020\003\022\013\n\007S_LOGIN\020\004\022\013\n\007S_MATCH"
  "\020\005\022\014\n\010S_CANCLE\020\006b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ProtocolMatch_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ProtocolMatch_2eproto = {
  false, false, 304, descriptor_table_protodef_ProtocolMatch_2eproto, "ProtocolMatch.proto", 
  &descriptor_table_ProtocolMatch_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_ProtocolMatch_2eproto::offsets,
  file_level_metadata_ProtocolMatch_2eproto, file_level_enum_descriptors_ProtocolMatch_2eproto, file_level_service_descriptors_ProtocolMatch_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ProtocolMatch_2eproto_getter() {
  return &descriptor_table_ProtocolMatch_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ProtocolMatch_2eproto(&descriptor_table_ProtocolMatch_2eproto);
namespace Match {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* STATE_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_ProtocolMatch_2eproto);
  return file_level_enum_descriptors_ProtocolMatch_2eproto[0];
}
bool STATE_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Header::_Internal {
 public:
};

Header::Header(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Match.Header)
}
Header::Header(const Header& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&size_, &from.size_,
    static_cast<size_t>(reinterpret_cast<char*>(&state_) -
    reinterpret_cast<char*>(&size_)) + sizeof(state_));
  // @@protoc_insertion_point(copy_constructor:Match.Header)
}

void Header::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&size_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&state_) -
    reinterpret_cast<char*>(&size_)) + sizeof(state_));
}

Header::~Header() {
  // @@protoc_insertion_point(destructor:Match.Header)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Header::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Header::ArenaDtor(void* object) {
  Header* _this = reinterpret_cast< Header* >(object);
  (void)_this;
}
void Header::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Header::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Header::Clear() {
// @@protoc_insertion_point(message_clear_start:Match.Header)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&size_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&state_) -
      reinterpret_cast<char*>(&size_)) + sizeof(state_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Header::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 size = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .Match.STATE state = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_state(static_cast<::Match::STATE>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* Header::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Match.Header)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 size = 1;
  if (this->size() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_size(), target);
  }

  // .Match.STATE state = 2;
  if (this->state() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      2, this->_internal_state(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Match.Header)
  return target;
}

size_t Header::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Match.Header)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 size = 1;
  if (this->size() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32Size(
        this->_internal_size());
  }

  // .Match.STATE state = 2;
  if (this->state() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_state());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Header::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Match.Header)
  GOOGLE_DCHECK_NE(&from, this);
  const Header* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Header>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Match.Header)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Match.Header)
    MergeFrom(*source);
  }
}

void Header::MergeFrom(const Header& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Match.Header)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.size() != 0) {
    _internal_set_size(from._internal_size());
  }
  if (from.state() != 0) {
    _internal_set_state(from._internal_state());
  }
}

void Header::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Match.Header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Header::CopyFrom(const Header& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Match.Header)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Header::IsInitialized() const {
  return true;
}

void Header::InternalSwap(Header* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Header, state_)
      + sizeof(Header::state_)
      - PROTOBUF_FIELD_OFFSET(Header, size_)>(
          reinterpret_cast<char*>(&size_),
          reinterpret_cast<char*>(&other->size_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Header::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolMatch_2eproto_getter, &descriptor_table_ProtocolMatch_2eproto_once,
      file_level_metadata_ProtocolMatch_2eproto[0]);
}

// ===================================================================

class Data::_Internal {
 public:
};

Data::Data(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Match.Data)
}
Data::Data(const Data& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&state_) -
    reinterpret_cast<char*>(&id_)) + sizeof(state_));
  // @@protoc_insertion_point(copy_constructor:Match.Data)
}

void Data::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&state_) -
    reinterpret_cast<char*>(&id_)) + sizeof(state_));
}

Data::~Data() {
  // @@protoc_insertion_point(destructor:Match.Data)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Data::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Data::ArenaDtor(void* object) {
  Data* _this = reinterpret_cast< Data* >(object);
  (void)_this;
}
void Data::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Data::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Data::Clear() {
// @@protoc_insertion_point(message_clear_start:Match.Data)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&state_) -
      reinterpret_cast<char*>(&id_)) + sizeof(state_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Data::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 level = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          level_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 room = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          room_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bool state = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          state_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* Data::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Match.Data)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_id(), target);
  }

  // int32 level = 2;
  if (this->level() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_level(), target);
  }

  // int32 room = 3;
  if (this->room() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_room(), target);
  }

  // bool state = 4;
  if (this->state() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(4, this->_internal_state(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Match.Data)
  return target;
}

size_t Data::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Match.Data)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_id());
  }

  // int32 level = 2;
  if (this->level() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_level());
  }

  // int32 room = 3;
  if (this->room() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_room());
  }

  // bool state = 4;
  if (this->state() != 0) {
    total_size += 1 + 1;
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Data::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Match.Data)
  GOOGLE_DCHECK_NE(&from, this);
  const Data* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Data>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Match.Data)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Match.Data)
    MergeFrom(*source);
  }
}

void Data::MergeFrom(const Data& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Match.Data)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.level() != 0) {
    _internal_set_level(from._internal_level());
  }
  if (from.room() != 0) {
    _internal_set_room(from._internal_room());
  }
  if (from.state() != 0) {
    _internal_set_state(from._internal_state());
  }
}

void Data::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Match.Data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Data::CopyFrom(const Data& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Match.Data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Data::IsInitialized() const {
  return true;
}

void Data::InternalSwap(Data* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Data, state_)
      + sizeof(Data::state_)
      - PROTOBUF_FIELD_OFFSET(Data, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Data::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolMatch_2eproto_getter, &descriptor_table_ProtocolMatch_2eproto_once,
      file_level_metadata_ProtocolMatch_2eproto[1]);
}

// ===================================================================

class Success::_Internal {
 public:
};

Success::Success(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:Match.Success)
}
Success::Success(const Success& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&gameport_) -
    reinterpret_cast<char*>(&id_)) + sizeof(gameport_));
  // @@protoc_insertion_point(copy_constructor:Match.Success)
}

void Success::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&gameport_) -
    reinterpret_cast<char*>(&id_)) + sizeof(gameport_));
}

Success::~Success() {
  // @@protoc_insertion_point(destructor:Match.Success)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Success::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Success::ArenaDtor(void* object) {
  Success* _this = reinterpret_cast< Success* >(object);
  (void)_this;
}
void Success::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Success::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Success::Clear() {
// @@protoc_insertion_point(message_clear_start:Match.Success)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&gameport_) -
      reinterpret_cast<char*>(&id_)) + sizeof(gameport_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Success::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 room = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          room_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 gamePort = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          gameport_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
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

::PROTOBUF_NAMESPACE_ID::uint8* Success::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Match.Success)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 id = 1;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_id(), target);
  }

  // int32 room = 2;
  if (this->room() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_room(), target);
  }

  // int32 gamePort = 3;
  if (this->gameport() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_gameport(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Match.Success)
  return target;
}

size_t Success::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Match.Success)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int64 id = 1;
  if (this->id() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_id());
  }

  // int32 room = 2;
  if (this->room() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_room());
  }

  // int32 gamePort = 3;
  if (this->gameport() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_gameport());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Success::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Match.Success)
  GOOGLE_DCHECK_NE(&from, this);
  const Success* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Success>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Match.Success)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Match.Success)
    MergeFrom(*source);
  }
}

void Success::MergeFrom(const Success& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Match.Success)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.room() != 0) {
    _internal_set_room(from._internal_room());
  }
  if (from.gameport() != 0) {
    _internal_set_gameport(from._internal_gameport());
  }
}

void Success::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Match.Success)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Success::CopyFrom(const Success& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Match.Success)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Success::IsInitialized() const {
  return true;
}

void Success::InternalSwap(Success* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Success, gameport_)
      + sizeof(Success::gameport_)
      - PROTOBUF_FIELD_OFFSET(Success, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Success::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ProtocolMatch_2eproto_getter, &descriptor_table_ProtocolMatch_2eproto_once,
      file_level_metadata_ProtocolMatch_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Match
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Match::Header* Arena::CreateMaybeMessage< ::Match::Header >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Match::Header >(arena);
}
template<> PROTOBUF_NOINLINE ::Match::Data* Arena::CreateMaybeMessage< ::Match::Data >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Match::Data >(arena);
}
template<> PROTOBUF_NOINLINE ::Match::Success* Arena::CreateMaybeMessage< ::Match::Success >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Match::Success >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
