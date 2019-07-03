# -*- coding: utf-8 -*-

import numpy as np
import pandas as pd

class BaseModel:
    """
     @Interface class: need to be impl
    """
    def __init__(self):
        self.modelType = None
        pass

    def load_data(self):
        pass

    def model_type(self, type):
        """
        设置模型类型
        :param type: 数据库、文件、序列化数据
        :return:
        """
        self.modelType = type
        pass