# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: clips_facts.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


import flight_control_pb2 as flight__control__pb2
import comm_link_pb2 as comm__link__pb2

from flight_control_pb2 import *
from comm_link_pb2 import *

DESCRIPTOR = _descriptor.FileDescriptor(
  name='clips_facts.proto',
  package='buaa.facts',
  syntax='proto3',
  serialized_pb=_b('\n\x11\x63lips_facts.proto\x12\nbuaa.facts\x1a\x14\x66light_control.proto\x1a\x0f\x63omm_link.proto\"[\n\x05\x66\x61\x63ts\x12&\n\x08\x66\x63_facts\x18\x01 \x01(\x0b\x32\x14.buaa.facts.fc_facts\x12*\n\ncomm_facts\x18\x02 \x01(\x0b\x32\x16.buaa.facts.comm_facts\"\xec\x03\n\x08\x66\x63_facts\x12\x34\n\x08velocity\x18\x01 \x01(\x0b\x32\".buaa.facts.flightcontrol.velocity\x12\x34\n\x08\x61ltitude\x18\x02 \x01(\x0b\x32\".buaa.facts.flightcontrol.altitude\x12\x42\n\x0fradio_altitude1\x18\x03 \x01(\x0b\x32).buaa.facts.flightcontrol.radio_altitude1\x12\x42\n\x0fradio_altitude2\x18\x04 \x01(\x0b\x32).buaa.facts.flightcontrol.radio_altitude2\x12\x46\n\x11pressure_altitude\x18\x05 \x01(\x0b\x32+.buaa.facts.flightcontrol.pressure_altitude\x12\x38\n\ngear_state\x18\x06 \x01(\x0b\x32$.buaa.facts.flightcontrol.gear_state\x12\x34\n\x08\x63oolant1\x18\x07 \x01(\x0b\x32\".buaa.facts.flightcontrol.coolant1\x12\x34\n\x08\x63oolant2\x18\x08 \x01(\x0b\x32\".buaa.facts.flightcontrol.coolant2\"\x92\x02\n\ncomm_facts\x12\'\n\x04\x63_up\x18\x01 \x01(\x0b\x32\x19.buaa.facts.commlink.c_up\x12+\n\x06\x63_down\x18\x02 \x01(\x0b\x32\x1b.buaa.facts.commlink.c_down\x12\'\n\x04u_up\x18\x03 \x01(\x0b\x32\x19.buaa.facts.commlink.u_up\x12+\n\x06u_down\x18\x04 \x01(\x0b\x32\x1b.buaa.facts.commlink.u_down\x12)\n\x05ku_up\x18\x05 \x01(\x0b\x32\x1a.buaa.facts.commlink.ku_up\x12-\n\x07ku_down\x18\x06 \x01(\x0b\x32\x1c.buaa.facts.commlink.ku_down\"\x1a\n\tsim_start\x12\r\n\x05start\x18\x01 \x01(\x08\"G\n\x06result\x12\x0b\n\x03res\x18\x01 \x01(\x0c\x12\x0b\n\x03\x65nd\x18\x02 \x01(\x08\x12#\n\x04\x64\x61ta\x18\x03 \x01(\x0b\x32\x15.buaa.facts.fact_data\"\x19\n\tfact_data\x12\x0c\n\x04\x64\x61ta\x18\x01 \x01(\x0cP\x00P\x01\x62\x06proto3')
  ,
  dependencies=[flight__control__pb2.DESCRIPTOR,comm__link__pb2.DESCRIPTOR,],
  public_dependencies=[flight__control__pb2.DESCRIPTOR,comm__link__pb2.DESCRIPTOR,])




_FACTS = _descriptor.Descriptor(
  name='facts',
  full_name='buaa.facts.facts',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='fc_facts', full_name='buaa.facts.facts.fc_facts', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='comm_facts', full_name='buaa.facts.facts.comm_facts', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=72,
  serialized_end=163,
)


_FC_FACTS = _descriptor.Descriptor(
  name='fc_facts',
  full_name='buaa.facts.fc_facts',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='velocity', full_name='buaa.facts.fc_facts.velocity', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='altitude', full_name='buaa.facts.fc_facts.altitude', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='radio_altitude1', full_name='buaa.facts.fc_facts.radio_altitude1', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='radio_altitude2', full_name='buaa.facts.fc_facts.radio_altitude2', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='pressure_altitude', full_name='buaa.facts.fc_facts.pressure_altitude', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='gear_state', full_name='buaa.facts.fc_facts.gear_state', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='coolant1', full_name='buaa.facts.fc_facts.coolant1', index=6,
      number=7, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='coolant2', full_name='buaa.facts.fc_facts.coolant2', index=7,
      number=8, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=166,
  serialized_end=658,
)


_COMM_FACTS = _descriptor.Descriptor(
  name='comm_facts',
  full_name='buaa.facts.comm_facts',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='c_up', full_name='buaa.facts.comm_facts.c_up', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='c_down', full_name='buaa.facts.comm_facts.c_down', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='u_up', full_name='buaa.facts.comm_facts.u_up', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='u_down', full_name='buaa.facts.comm_facts.u_down', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ku_up', full_name='buaa.facts.comm_facts.ku_up', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='ku_down', full_name='buaa.facts.comm_facts.ku_down', index=5,
      number=6, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=661,
  serialized_end=935,
)


_SIM_START = _descriptor.Descriptor(
  name='sim_start',
  full_name='buaa.facts.sim_start',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='start', full_name='buaa.facts.sim_start.start', index=0,
      number=1, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=937,
  serialized_end=963,
)


_RESULT = _descriptor.Descriptor(
  name='result',
  full_name='buaa.facts.result',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='res', full_name='buaa.facts.result.res', index=0,
      number=1, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='end', full_name='buaa.facts.result.end', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='data', full_name='buaa.facts.result.data', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=965,
  serialized_end=1036,
)


_FACT_DATA = _descriptor.Descriptor(
  name='fact_data',
  full_name='buaa.facts.fact_data',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='data', full_name='buaa.facts.fact_data.data', index=0,
      number=1, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value=_b(""),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=1038,
  serialized_end=1063,
)

_FACTS.fields_by_name['fc_facts'].message_type = _FC_FACTS
_FACTS.fields_by_name['comm_facts'].message_type = _COMM_FACTS
_FC_FACTS.fields_by_name['velocity'].message_type = flight__control__pb2._VELOCITY
_FC_FACTS.fields_by_name['altitude'].message_type = flight__control__pb2._ALTITUDE
_FC_FACTS.fields_by_name['radio_altitude1'].message_type = flight__control__pb2._RADIO_ALTITUDE1
_FC_FACTS.fields_by_name['radio_altitude2'].message_type = flight__control__pb2._RADIO_ALTITUDE2
_FC_FACTS.fields_by_name['pressure_altitude'].message_type = flight__control__pb2._PRESSURE_ALTITUDE
_FC_FACTS.fields_by_name['gear_state'].message_type = flight__control__pb2._GEAR_STATE
_FC_FACTS.fields_by_name['coolant1'].message_type = flight__control__pb2._COOLANT1
_FC_FACTS.fields_by_name['coolant2'].message_type = flight__control__pb2._COOLANT2
_COMM_FACTS.fields_by_name['c_up'].message_type = comm__link__pb2._C_UP
_COMM_FACTS.fields_by_name['c_down'].message_type = comm__link__pb2._C_DOWN
_COMM_FACTS.fields_by_name['u_up'].message_type = comm__link__pb2._U_UP
_COMM_FACTS.fields_by_name['u_down'].message_type = comm__link__pb2._U_DOWN
_COMM_FACTS.fields_by_name['ku_up'].message_type = comm__link__pb2._KU_UP
_COMM_FACTS.fields_by_name['ku_down'].message_type = comm__link__pb2._KU_DOWN
_RESULT.fields_by_name['data'].message_type = _FACT_DATA
DESCRIPTOR.message_types_by_name['facts'] = _FACTS
DESCRIPTOR.message_types_by_name['fc_facts'] = _FC_FACTS
DESCRIPTOR.message_types_by_name['comm_facts'] = _COMM_FACTS
DESCRIPTOR.message_types_by_name['sim_start'] = _SIM_START
DESCRIPTOR.message_types_by_name['result'] = _RESULT
DESCRIPTOR.message_types_by_name['fact_data'] = _FACT_DATA
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

facts = _reflection.GeneratedProtocolMessageType('facts', (_message.Message,), dict(
  DESCRIPTOR = _FACTS,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.facts)
  ))
_sym_db.RegisterMessage(facts)

fc_facts = _reflection.GeneratedProtocolMessageType('fc_facts', (_message.Message,), dict(
  DESCRIPTOR = _FC_FACTS,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.fc_facts)
  ))
_sym_db.RegisterMessage(fc_facts)

comm_facts = _reflection.GeneratedProtocolMessageType('comm_facts', (_message.Message,), dict(
  DESCRIPTOR = _COMM_FACTS,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.comm_facts)
  ))
_sym_db.RegisterMessage(comm_facts)

sim_start = _reflection.GeneratedProtocolMessageType('sim_start', (_message.Message,), dict(
  DESCRIPTOR = _SIM_START,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.sim_start)
  ))
_sym_db.RegisterMessage(sim_start)

result = _reflection.GeneratedProtocolMessageType('result', (_message.Message,), dict(
  DESCRIPTOR = _RESULT,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.result)
  ))
_sym_db.RegisterMessage(result)

fact_data = _reflection.GeneratedProtocolMessageType('fact_data', (_message.Message,), dict(
  DESCRIPTOR = _FACT_DATA,
  __module__ = 'clips_facts_pb2'
  # @@protoc_insertion_point(class_scope:buaa.facts.fact_data)
  ))
_sym_db.RegisterMessage(fact_data)


# @@protoc_insertion_point(module_scope)
