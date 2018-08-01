# _*_ coding: utf-8 _*_

import grpc
import dss_pb2
import dss_pb2_grpc
import rule_controller
import time
from concurrent import futures

_ONE_DAY_IN_SECONDS = 60 * 60 * 24


class Receiver(dss_pb2_grpc.ReasoningServicer):
    def __init__(self):
        self.rc = rule_controller.rule_controller()

    def GetReasoningResult(self, request, context):
        """Override  获取推理结果及停止标志位"""
        return self.rc.get_reasoning_result()

    def GetRuleFile(self, request, context):
        """Override  获取可用规则库文件信息列表"""
        rule_list = self.rc.get_rulefile_list()
        print(rule_list)
        if len(rule_list) > 0:
            for item in rule_list:
                yield item

    def LoadRuleFile(self, request_iterator, context):
        """Override  加载规则库"""
        filelist = []
        for item in request_iterator:
            filelist.append(str(item.filename))

        self.rc.load_rulefiles(filelist)
        return dss_pb2.placeholder()

    def GetFactSlots(self, request, context):
        """Override  获取Slot列表"""
        fact_list = self.rc.get_slots()
        if len(fact_list) > 0:
            for item in fact_list:
                yield item

    def SetFactSlots(self, request_iterator, context):
        """Override  设置已选的slot列表"""
        template_list = []
        for item in request_iterator:
            template_list.append(str(item.template_name))
        self.rc.set_templates(template_list)
        return dss_pb2.placeholder()

    def GetFactFile(self, request, context):
        """Override  获取事实库文件列表"""
        fact_list = self.rc.get_factfile_list()
        print(fact_list)
        if len(fact_list) > 0:
            for item in fact_list:
                yield item

    def LoadFactFile(self, request_iterator, context):
        """Override  加载已选的事实库文件"""
        filelist = []
        for item in request_iterator:
            filelist.append(str(item.filename))

        self.rc.load_factfiles(filelist)
        return dss_pb2.placeholder()

    def GetSelectedSlots(self, request, context):
        """Override 获取已选的Slot列表"""
        fact_list = self.rc.get_selected_slots()

        if len(fact_list) > 0:
            for item in fact_list:
                yield item

    def GetVariableList(self, request, context):
        """Override 获取事实库变量列表(表头加第一行数据)"""
        var_list = self.rc.get_variables()
        if len(var_list) > 0:
            for item in var_list:
                yield item

    def SetMappingList(self, request_iterator, context):
        """Override 设置slot与事实库变量名称的映射关系，用以生成事实"""
        mapper_list = []
        for item in request_iterator:
            mapper_list.append(item)
        self.rc.set_mapping_list(mapper_list)
        return dss_pb2.placeholder()

    def StartReasoning(self, request, context):
        """Override 仿真开始"""
        if request.start:
            self.rc.on_sim_start()
        return dss_pb2.placeholder()


if __name__ == '__main__':
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    dss_pb2_grpc.add_ReasoningServicer_to_server(Receiver(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print('server start...')
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)