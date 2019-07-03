# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
from common_utils import RULE_FILE_PREFIX, TEMP_FILE_PREFIX, FACT_FILE_PREFIX

class Singleton(type):
    def __init__(self, *args, **kwargs):
        print "__init__"
        self.__instance = None
        super(Singleton,self).__init__(*args, **kwargs)

    def __call__(self, *args, **kwargs):
        print "__call__"
        if self.__instance is None:
            self.__instance = super(Singleton,self).__call__(*args, **kwargs)
        return self.__instance

class FileModel():
    """
    单例类
    """
    __metaclass__ = Singleton

    def __init__(self):
        self.dataframe = pd.DataFrame   # 数据集
        self.data_per_frame = pd.DataFrame  # 每拍数据
        self.chunksize = 5
        self.is_rear = False
        self.reset()
        pass

    def reset(self):
        self.dataframe = pd.DataFrame  # 数据集
        self.data_per_frame = pd.DataFrame  # 每拍数据
        self.chunksize = 5
        self.is_rear = False

    def load_data(self, filenamelist):
        """
        @public: Load fact file into dataframe
        :param filenamelist: 文件名列表
        :return: dataframe
        """
        if len(filenamelist) <= 0:
            return
        file = filenamelist[0] # 暂时用一个文件
        df = pd.read_csv(FACT_FILE_PREFIX + file, encoding='gb2312', iterator=True, chunksize=self.chunksize)
        self.dataframe = df
        # i = 0
        # for file in filenamelist:
        #     df = pd.read_csv(FACT_FILE_PREFIX + file, encoding='gb2312')
        #     if i == 0:
        #         self.dataframe = df
        #         i = i + 1
        #     else:
        #         pd.concat([self.dataframe, df], axis=1, join='inner')
        return self.dataframe

    def update_data(self):
        """
        更新数据
        """
        try:
            self.data_per_frame = self.dataframe.get_chunk()
        except StopIteration:
            self.is_rear = True
            # return True

        self.is_rear = False

    def get_data(self):
        """
        获取每拍数据(NDarray格式)
        :return:
        """
        return (self.data_per_frame.values)[0]

    def get_data_frame(self):
        """
        获取每拍数据(Dataframe格式)
        :return:
        """
        return self.data_per_frame[:1]

    def is_EOF(self):
        """
        是否到文件尾
        :return:
        """
        return self.is_rear

    def get_dataframe_header(self):

        return self.data_per_frame.columns.values