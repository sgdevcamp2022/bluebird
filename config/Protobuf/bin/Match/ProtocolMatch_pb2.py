# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: ProtocolMatch.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='ProtocolMatch.proto',
  package='Match',
  syntax='proto3',
  serialized_options=None,
  create_key=_descriptor._internal_create_key,
  serialized_pb=b'\n\x13ProtocolMatch.proto\x12\x05Match\"3\n\x06Header\x12\x0c\n\x04size\x18\x01 \x01(\r\x12\x1b\n\x05state\x18\x02 \x01(\x0e\x32\x0c.Match.STATE\"\x15\n\x05\x43heck\x12\x0c\n\x04type\x18\x01 \x01(\x05\"$\n\x07\x43_Login\x12\n\n\x02id\x18\x01 \x01(\x03\x12\r\n\x05level\x18\x02 \x01(\x05\"3\n\x08\x43_Cancel\x12\n\n\x02id\x18\x01 \x01(\x03\x12\r\n\x05level\x18\x02 \x01(\x05\x12\x0c\n\x04room\x18\x03 \x01(\x05\"3\n\x08S_Cancel\x12\n\n\x02id\x18\x01 \x01(\x03\x12\x0c\n\x04room\x18\x02 \x01(\x05\x12\r\n\x05state\x18\x03 \x01(\x08\"$\n\x07S_Login\x12\n\n\x02id\x18\x01 \x01(\x03\x12\r\n\x05level\x18\x02 \x01(\x05\"3\n\x07S_Match\x12\x0c\n\x04room\x18\x01 \x01(\x05\x12\r\n\x05level\x18\x02 \x01(\x05\x12\x0b\n\x03ids\x18\x03 \x03(\x03*i\n\x05STATE\x12\x08\n\x04NULL\x10\x00\x12\x0b\n\x07\x43_LOGIN\x10\x01\x12\x0c\n\x08\x43_CANCEL\x10\x02\x12\x08\n\x04\x46\x41IL\x10\x03\x12\x0b\n\x07S_LOGIN\x10\x04\x12\x0b\n\x07S_MATCH\x10\x05\x12\x0c\n\x08S_CANCLE\x10\x06\x12\t\n\x05\x43HECK\x10\x07\x62\x06proto3'
)

_STATE = _descriptor.EnumDescriptor(
  name='STATE',
  full_name='Match.STATE',
  filename=None,
  file=DESCRIPTOR,
  create_key=_descriptor._internal_create_key,
  values=[
    _descriptor.EnumValueDescriptor(
      name='NULL', index=0, number=0,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='C_LOGIN', index=1, number=1,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='C_CANCEL', index=2, number=2,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='FAIL', index=3, number=3,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='S_LOGIN', index=4, number=4,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='S_MATCH', index=5, number=5,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='S_CANCLE', index=6, number=6,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
    _descriptor.EnumValueDescriptor(
      name='CHECK', index=7, number=7,
      serialized_options=None,
      type=None,
      create_key=_descriptor._internal_create_key),
  ],
  containing_type=None,
  serialized_options=None,
  serialized_start=341,
  serialized_end=446,
)
_sym_db.RegisterEnumDescriptor(_STATE)

STATE = enum_type_wrapper.EnumTypeWrapper(_STATE)
NULL = 0
C_LOGIN = 1
C_CANCEL = 2
FAIL = 3
S_LOGIN = 4
S_MATCH = 5
S_CANCLE = 6
CHECK = 7



_HEADER = _descriptor.Descriptor(
  name='Header',
  full_name='Match.Header',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='size', full_name='Match.Header.size', index=0,
      number=1, type=13, cpp_type=3, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='state', full_name='Match.Header.state', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=30,
  serialized_end=81,
)


_CHECK = _descriptor.Descriptor(
  name='Check',
  full_name='Match.Check',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Match.Check.type', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=83,
  serialized_end=104,
)


_C_LOGIN = _descriptor.Descriptor(
  name='C_Login',
  full_name='Match.C_Login',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Match.C_Login.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='level', full_name='Match.C_Login.level', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=106,
  serialized_end=142,
)


_C_CANCEL = _descriptor.Descriptor(
  name='C_Cancel',
  full_name='Match.C_Cancel',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Match.C_Cancel.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='level', full_name='Match.C_Cancel.level', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='room', full_name='Match.C_Cancel.room', index=2,
      number=3, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=144,
  serialized_end=195,
)


_S_CANCEL = _descriptor.Descriptor(
  name='S_Cancel',
  full_name='Match.S_Cancel',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Match.S_Cancel.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='room', full_name='Match.S_Cancel.room', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='state', full_name='Match.S_Cancel.state', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=197,
  serialized_end=248,
)


_S_LOGIN = _descriptor.Descriptor(
  name='S_Login',
  full_name='Match.S_Login',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='Match.S_Login.id', index=0,
      number=1, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='level', full_name='Match.S_Login.level', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=250,
  serialized_end=286,
)


_S_MATCH = _descriptor.Descriptor(
  name='S_Match',
  full_name='Match.S_Match',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  create_key=_descriptor._internal_create_key,
  fields=[
    _descriptor.FieldDescriptor(
      name='room', full_name='Match.S_Match.room', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='level', full_name='Match.S_Match.level', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
    _descriptor.FieldDescriptor(
      name='ids', full_name='Match.S_Match.ids', index=2,
      number=3, type=3, cpp_type=2, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR,  create_key=_descriptor._internal_create_key),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=288,
  serialized_end=339,
)

_HEADER.fields_by_name['state'].enum_type = _STATE
DESCRIPTOR.message_types_by_name['Header'] = _HEADER
DESCRIPTOR.message_types_by_name['Check'] = _CHECK
DESCRIPTOR.message_types_by_name['C_Login'] = _C_LOGIN
DESCRIPTOR.message_types_by_name['C_Cancel'] = _C_CANCEL
DESCRIPTOR.message_types_by_name['S_Cancel'] = _S_CANCEL
DESCRIPTOR.message_types_by_name['S_Login'] = _S_LOGIN
DESCRIPTOR.message_types_by_name['S_Match'] = _S_MATCH
DESCRIPTOR.enum_types_by_name['STATE'] = _STATE
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Header = _reflection.GeneratedProtocolMessageType('Header', (_message.Message,), {
  'DESCRIPTOR' : _HEADER,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.Header)
  })
_sym_db.RegisterMessage(Header)

Check = _reflection.GeneratedProtocolMessageType('Check', (_message.Message,), {
  'DESCRIPTOR' : _CHECK,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.Check)
  })
_sym_db.RegisterMessage(Check)

C_Login = _reflection.GeneratedProtocolMessageType('C_Login', (_message.Message,), {
  'DESCRIPTOR' : _C_LOGIN,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.C_Login)
  })
_sym_db.RegisterMessage(C_Login)

C_Cancel = _reflection.GeneratedProtocolMessageType('C_Cancel', (_message.Message,), {
  'DESCRIPTOR' : _C_CANCEL,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.C_Cancel)
  })
_sym_db.RegisterMessage(C_Cancel)

S_Cancel = _reflection.GeneratedProtocolMessageType('S_Cancel', (_message.Message,), {
  'DESCRIPTOR' : _S_CANCEL,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.S_Cancel)
  })
_sym_db.RegisterMessage(S_Cancel)

S_Login = _reflection.GeneratedProtocolMessageType('S_Login', (_message.Message,), {
  'DESCRIPTOR' : _S_LOGIN,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.S_Login)
  })
_sym_db.RegisterMessage(S_Login)

S_Match = _reflection.GeneratedProtocolMessageType('S_Match', (_message.Message,), {
  'DESCRIPTOR' : _S_MATCH,
  '__module__' : 'ProtocolMatch_pb2'
  # @@protoc_insertion_point(class_scope:Match.S_Match)
  })
_sym_db.RegisterMessage(S_Match)


# @@protoc_insertion_point(module_scope)
