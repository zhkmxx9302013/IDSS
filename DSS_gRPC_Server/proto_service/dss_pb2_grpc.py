# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import clips_facts_pb2 as clips__facts__pb2
import dss_pb2 as dss__pb2
import file_pb2 as file__pb2


class ReasoningStub(object):
  """CLIPS Reasoning Service
  """

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.GetReasoningResult = channel.unary_unary(
        '/buaa.dss.Reasoning/GetReasoningResult',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=clips__facts__pb2.result.FromString,
        )
    self.StartReasoning = channel.unary_unary(
        '/buaa.dss.Reasoning/StartReasoning',
        request_serializer=clips__facts__pb2.sim_start.SerializeToString,
        response_deserializer=dss__pb2.placeholder.FromString,
        )
    self.GetRuleFile = channel.unary_stream(
        '/buaa.dss.Reasoning/GetRuleFile',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=file__pb2.rule_file_info.FromString,
        )
    self.LoadRuleFile = channel.stream_unary(
        '/buaa.dss.Reasoning/LoadRuleFile',
        request_serializer=file__pb2.rule_file_chk.SerializeToString,
        response_deserializer=dss__pb2.placeholder.FromString,
        )
    self.GetFactSlots = channel.unary_stream(
        '/buaa.dss.Reasoning/GetFactSlots',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=file__pb2.fact_list.FromString,
        )
    self.SetFactSlots = channel.stream_unary(
        '/buaa.dss.Reasoning/SetFactSlots',
        request_serializer=file__pb2.fact_list.SerializeToString,
        response_deserializer=dss__pb2.placeholder.FromString,
        )
    self.GetFactFile = channel.unary_stream(
        '/buaa.dss.Reasoning/GetFactFile',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=file__pb2.fact_file_info.FromString,
        )
    self.LoadFactFile = channel.stream_unary(
        '/buaa.dss.Reasoning/LoadFactFile',
        request_serializer=file__pb2.fact_file_chk.SerializeToString,
        response_deserializer=dss__pb2.placeholder.FromString,
        )
    self.GetSelectedSlots = channel.unary_stream(
        '/buaa.dss.Reasoning/GetSelectedSlots',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=file__pb2.fact_list.FromString,
        )
    self.GetVariableList = channel.unary_stream(
        '/buaa.dss.Reasoning/GetVariableList',
        request_serializer=dss__pb2.placeholder.SerializeToString,
        response_deserializer=file__pb2.fact_var.FromString,
        )
    self.SetMappingList = channel.stream_unary(
        '/buaa.dss.Reasoning/SetMappingList',
        request_serializer=file__pb2.mapper.SerializeToString,
        response_deserializer=dss__pb2.placeholder.FromString,
        )


class ReasoningServicer(object):
  """CLIPS Reasoning Service
  """

  def GetReasoningResult(self, request, context):
    """@stub -param: facts -return: resoning results
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def StartReasoning(self, request, context):
    """@stub
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def GetRuleFile(self, request, context):
    """@stub -param:  -return:rule file list
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def LoadRuleFile(self, request_iterator, context):
    """@stub -param: the rule files that wanna loaded  -return:null
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def GetFactSlots(self, request, context):
    """@stub Get the list of slots according to the chosen rule files
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def SetFactSlots(self, request_iterator, context):
    """@stub Set the list of slots that selected by user
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def GetFactFile(self, request, context):
    """@stub -param: the rule files that wanna loaded  -return:optional rule list
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def LoadFactFile(self, request_iterator, context):
    """@stub -param: optional rule list  -return:null
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def GetSelectedSlots(self, request, context):
    """@stub Get the Slot list that selected before
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def GetVariableList(self, request, context):
    """@stub Get the optional variables from the facts file
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def SetMappingList(self, request_iterator, context):
    """@stub Set the <slot:variable> kv mapping
    """
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_ReasoningServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'GetReasoningResult': grpc.unary_unary_rpc_method_handler(
          servicer.GetReasoningResult,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=clips__facts__pb2.result.SerializeToString,
      ),
      'StartReasoning': grpc.unary_unary_rpc_method_handler(
          servicer.StartReasoning,
          request_deserializer=clips__facts__pb2.sim_start.FromString,
          response_serializer=dss__pb2.placeholder.SerializeToString,
      ),
      'GetRuleFile': grpc.unary_stream_rpc_method_handler(
          servicer.GetRuleFile,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=file__pb2.rule_file_info.SerializeToString,
      ),
      'LoadRuleFile': grpc.stream_unary_rpc_method_handler(
          servicer.LoadRuleFile,
          request_deserializer=file__pb2.rule_file_chk.FromString,
          response_serializer=dss__pb2.placeholder.SerializeToString,
      ),
      'GetFactSlots': grpc.unary_stream_rpc_method_handler(
          servicer.GetFactSlots,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=file__pb2.fact_list.SerializeToString,
      ),
      'SetFactSlots': grpc.stream_unary_rpc_method_handler(
          servicer.SetFactSlots,
          request_deserializer=file__pb2.fact_list.FromString,
          response_serializer=dss__pb2.placeholder.SerializeToString,
      ),
      'GetFactFile': grpc.unary_stream_rpc_method_handler(
          servicer.GetFactFile,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=file__pb2.fact_file_info.SerializeToString,
      ),
      'LoadFactFile': grpc.stream_unary_rpc_method_handler(
          servicer.LoadFactFile,
          request_deserializer=file__pb2.fact_file_chk.FromString,
          response_serializer=dss__pb2.placeholder.SerializeToString,
      ),
      'GetSelectedSlots': grpc.unary_stream_rpc_method_handler(
          servicer.GetSelectedSlots,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=file__pb2.fact_list.SerializeToString,
      ),
      'GetVariableList': grpc.unary_stream_rpc_method_handler(
          servicer.GetVariableList,
          request_deserializer=dss__pb2.placeholder.FromString,
          response_serializer=file__pb2.fact_var.SerializeToString,
      ),
      'SetMappingList': grpc.stream_unary_rpc_method_handler(
          servicer.SetMappingList,
          request_deserializer=file__pb2.mapper.FromString,
          response_serializer=dss__pb2.placeholder.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'buaa.dss.Reasoning', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))
