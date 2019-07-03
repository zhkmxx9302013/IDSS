# coding=utf-8

class  FailureModel():
    """
    异常触发模型层，定义异常消息结构
    """
    def __init__(self):
        self.is_failure = False  # 是否发生故障
        self.failure_info = '' # 故障信息
        self.failure_type = ''  # 故障类型
        self.failure_datetime = '' # 故障发生时间
        self.failure_level = 2 # 故障等级，1级为返航，其他不返航
        self.airport_lat = 0.0 # 机场位置 默认0，使用前端值
        self.airport_lon = 0.0 # 同上


    def SetFailureInfo(self, is_failure, failure_level, failure_info, failure_type, failure_datetime):
        """
        设置故障信息
        :param is_failure: 是否发生故障
        :param info_dict: 故障信息dict
        :return:
        """
        self.is_failure = is_failure
        self.failure_level = failure_level
        self.failure_info = failure_info
        self.failure_type = failure_type
        self.failure_datetime = failure_datetime

    def GetFailureInfo(self):
        """
        返回故障信息
        :return:
        """
        return self.is_failure, self.failure_level, self.failure_info, self.failure_type, self.failure_datetime

    def SetAirportInfo(self, lat, lon):
        """
        设置返回机场位置
        :param lat:
        :param lon:
        :return:
        """
        self.airport_lat = lat
        self.airport_lon = lon

    def GetAiportInfo(self):
        return self.airport_lat, self.airport_lon