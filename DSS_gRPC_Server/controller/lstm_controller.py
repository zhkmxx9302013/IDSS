# -*- coding: utf-8 -*-
from rpm_service import RpmService
from oiltemp_service import OilTempService
from base_controller import BaseController
import lstm_prediction_pb2 as grpcNN


class LstmController(BaseController):
    def __init__(self):
        BaseController.__init__(self)
        self.rpm_lstm_obj = None
        self.oiltemp_lstm_obj = None
        self.y_hat, self.y_gt, self.gh_err = list(), list(), list()
        self.reset()
        self.chart_type = 0
        self.chart_type_list = [
                                    self.rpm_lstm_obj,
                                    self.oiltemp_lstm_obj
                               ]


    def reset(self):
        """
        reset
        :return:
        """
        self.rpm_lstm_obj = RpmService()
        self.oiltemp_lstm_obj = OilTempService()
        self.y_hat, self.y_gt, self.gh_err = list(), list(), list()
        self.chart_type = 0


    def set_chart_type(self, type):
        """
        设置图表类型
        :param type: 图表类型 (0~n)
        :return:
        """
        self.chart_type = type


    def get_chart_data(self):
        """
        获取前端图像展示的数据集包括预测、真实值、误差值 (builtin list 类型)
        :return:
        """
        # self.y_hat, self.y_gt, self.gh_err = self.chart_type_list[self.chart_type].get_chart_data()
        for idx, chartType in enumerate(self.chart_type_list):
            if idx == self.chart_type:
                self.y_gt, self.y_hat, self.gh_err = self.chart_type_list[self.chart_type].get_chart_data()
            else:
                self.chart_type_list[idx].get_chart_data()

    def get_gt_data(self):
        """
        获取真实值序列 (GRPC 类型)
        :return:
        """
        res = []
        for item in self.y_gt:
            obj = grpcNN.gtVal(val=item)
            res.append(obj)
        return res

    def get_pred_data(self):
        """
        获取预测值序列 (GRPC 类型)
        :return:
        """
        res = []
        for item in self.y_hat:
            res.append(grpcNN.predVal(val=item))
        return res

    def get_err_data(self):
        """
        获取误差值序列 (GRPC 类型)
        :return:
        """
        res = []
        for item in self.gh_err:
            res.append(grpcNN.errVal(val=item))
        return res


    def on_sim_start(self):
        """
        @ Implement
        :return:
        """
        pass