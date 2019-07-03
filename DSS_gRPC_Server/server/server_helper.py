# _*_ coding: utf-8 _*_
# GRPC 服务端接口层
import dss_pb2
import dss_pb2_grpc
from clips_controller import RuleController
from lstm_controller import LstmController
from failure_controller import FailureController

import sys
reload(sys)
sys.setdefaultencoding('utf8')


class Receiver(dss_pb2_grpc.ReasoningServicer):
    def __init__(self):
        self.fc = FailureController()  # 故障控制器
        self.rc = RuleController(self.fc)  # CLIPS控制器
        self.lc = LstmController()  # DLSTM控制器


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
            self.rc.reset()
            self.lc.reset()
            self.rc.on_sim_start()
        return dss_pb2.placeholder()

    def GetReasoningResult(self, request, context):
        """Override  获取推理结果及停止标志位(前端每拍调用)"""
        # self.lc.get_chart_data()
        clips_res = self.rc.get_reasoning_result()   # 触发CLIPS服务更新
        return clips_res



    # ============== LSTM ================
    def OnChartSim(self, request, context):
        """Override  触发LSTM服务更新(前端每拍调用)"""
        self.lc.get_chart_data()
        return dss_pb2.placeholder()

    def GetGtChartData(self, request, context):
        """Override  获取LSTM预测图像值真值序列，直传序列暂未做分页"""

        y_gt = self.lc.get_gt_data()
        # print("GetGtChartData")
        if len(y_gt) > 0:
            for item in y_gt:
                yield item

    def GetPredChartData(self, request, context):
        """Override  获取LSTM预测图像值预测值序列，直传序列暂未做分页"""
        y_pred = self.lc.get_pred_data()
        # print("GetPredChartData")
        if len(y_pred) > 0:
            for item in y_pred:
                yield item

    def GetErrChartData(self, request, context):
        """Override  获取LSTM预测图像值误差值序列，直传序列暂未做分页"""
        y_err = self.lc.get_err_data()
        # print("GetErrChartData")
        if len(y_err) > 0:
            for item in y_err:
                yield item

    def SetChartType(self, request, context):
        """Override 设置图表类型"""
        self.lc.set_chart_type(request.type)
        return dss_pb2.placeholder()



    # ==============PLANNING =====================
    def GetFailureInfo(self, request, context):
        """Override 获取故障信息"""
        print("[GET]")
        return self.fc.get_failure_info()