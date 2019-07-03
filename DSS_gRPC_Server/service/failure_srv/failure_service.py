# coding=utf-8
from failure_model import FailureModel
import datetime
class FailureService:
    def __init__(self):
        self.fail_lv = 2
        self.is_fail = False
        self.failmodel = None
        pass

    def BuildFailure(self, std_str, dlg_str):
        """
        筛选构建故障信息
        :param dlg_str: 故障编码
        :param std_str: 故障信息
        :return:
        """
        self.failmodel = FailureModel()
        fail_list = self.__GetFirstLevelList()
        # 一级故障匹配，匹配到一级故障才返航，二级不用管只负责前端显示
        for item in fail_list:
            if item in dlg_str:
                self.fail_lv = 1
            else:
                self.fail_lv = 2
        #
        if len(std_str) > 1:
            self.is_fail = True
        else:
            self.is_fail = False

        dt = str(datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
        self.failmodel.SetFailureInfo(self.is_fail, self.fail_lv, std_str, dlg_str, dt)

    def GetFailureInfo(self):
        """
        获取故障信息，传回给controller层做grpc封装
        :return:
        """
        if not self.failmodel:
            return False, 2, '', '', ''
        else:
            return self.failmodel.GetFailureInfo()



    def __GetFailureModel(self):
        """
        @ private
        获取故障实体
        :return:
        """
        return self.failmodel

    def __GetFirstLevelList(self):
        """
        @ private
        获取一级故障代码列表
        :return:
        """
        return ['FC:COLLANT2ERROR2', 'FC:COLLANT2ERROR1']