# coding=utf-8
from failure_service import FailureService
import planning_control_pb2

class FailureController:
    def __init__(self):
        self.fail_srv = FailureService()
        pass

    def generate_failure(self, std_str, dlg_str):
        """
        筛选构建故障信息
        :param dlg_str: 故障编码
        :param std_str: 故障信息
        :return:
        """

        self.fail_srv.BuildFailure(std_str, dlg_str)


    def get_failure_info(self):
        """
        获取故障信息GRPC实例
        :return:
        """
        is_failure, failure_level, failure_info, failure_type, failure_datetime = self.fail_srv.GetFailureInfo()
        #"""测试用，未走模型"""
        airport_lat=124
        airport_lon=73
        #"""""""""""""""""""
        return planning_control_pb2.failure(is_failure=is_failure,
                                            failure_info=failure_info,
                                            failure_type=failure_type,
                                            failure_level=failure_level,
                                            failure_datetime=failure_datetime,
                                            airport_lat=airport_lat,
                                            airport_lon=airport_lon)


