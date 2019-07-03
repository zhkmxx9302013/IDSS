# -*- coding: utf-8 -*-
import sys
import os

os.environ['KERAS_BACKEND'] = 'cntk'
import numpy as np
# from common_utils import SCALAR_PICKLE_PATH
import time
import pandas as pd
from keras.models import load_model
from sklearn.externals import joblib
from file_model import FileModel

reload(sys)
sys.setdefaultencoding('utf8')

np.random.seed(2018)


class LstmService():
    def __init__(self):
        self.model = None  # Prediction model
        self.model_path = '../data/NN/model.h5'
        self.weight_path = '../data/NN/weight.h5'
        self.SCALAR_PICKLE_PATH = '../data/preprocess/scaler_py2.pkl'
        self.feature_list = []
        self.iter_count = 0 # sim trigger引用计数
        self.pred_interval = 20 # 预测间隔 < self.pred_length
        self.pred_step = 5 # 读文件步长，每隔50ms更新基础数据

        self.sequence_init_weight = 2 # 初始储备buffersize权重 >= 2
        self.sequence_length = 60  # 10s 的数据进行预测
        self.pred_length = 30  # 预测出未来5s       60 ~ 5s
        self.gt_grpc_bufsize = (20 * 12) + 2   # 传回给 grpc的事实数据系列 buf_size = 100s * 12个数据/s = 1200
        self.pred_grpc_bufsize = (20 + 10) * 12 + self.pred_length  # 传回给 grpc的预测数据系列 buf_size = 110s * 12个数据/s = 1380
        self.invert_scale = 2000.0 # 归一化的缩放比例

        self.iter_csv = None
        self.gt_buf = np.array([])  # 实际数据缓冲区
        self.pred_buf = np.array([])  # 预测数据缓冲区
        self.gt_grpc_buf = np.array([])  # 传回给 grpc的事实数据系列
        self.pred_grpc_buf = np.array([])  # 传回给 grpc的预测数据系列
        self.error_grpc_buf = np.array([])  # 传回给 grpc的误差数据系列

        self.FEATURE_SIZE = 3
        self.y_cols = []
        self.scaler = None
        self.fileModel = FileModel()
        pass

    def set_config(self, model_path, weight_path, scalar_pickle_path, invert_scale, feature_size, features):
        """
        @Impl 设置网络参数
        :param model_path:  模型路径
        :param weight_path: 权值路径
        :param scalar_pickle_path:  归一化或标准化pickle路径
        :param invert_scale:    预测参数尺度缩放比例
        :param feature_size:    特征数量
        :param features: 特征名称列表(unicode)，将预测列放在最后一列 [a,b,pred], 次序与训练时候的次序相同
        :return:
        """
        self.model_path = model_path    # '../data/NN/model.h5'
        self.weight_path = weight_path  #'../data/NN/weight.h5'
        self.__load_model(self.model_path)
        self.__load_weight(self.weight_path)
        self.SCALAR_PICKLE_PATH = scalar_pickle_path
        self.invert_scale = invert_scale
        self.FEATURE_SIZE = feature_size
        self.feature_list = features
        self.reset()
        pass

    def reset(self):
        """
        reset
        :return:
        """
        self.gt_buf = np.array([])
        self.pred_buf = np.array([])
        self.gt_grpc_buf = np.array([])
        self.pred_grpc_buf = np.array([])
        self.iter_count = 0
        self.pred_interval = self.pred_length - 1 if self.pred_interval > self.pred_length else self.pred_interval
        self.scaler = joblib.load(self.SCALAR_PICKLE_PATH)
        self.y_cols =[item for item in range(self.pred_length * (self.FEATURE_SIZE)) if (item + 1) % (self.FEATURE_SIZE) == 0]  # 选取预测的列

    def __load_weight(self, path=''):
        """
        @private: Load LSTM trained weight
        :param path: weight file path
        :return:
        """
        self.model.load_weights(path)
        pass

    def __filter_attr(self, dataframe):
        """
        从数据集中过滤属性
        :param dataframe:
        :return:
        """

        df = pd.DataFrame(dataframe, columns=self.feature_list)
        return df

    def __load_model(self, path=''):
        """
        @private: Load LSTM model
        :param path: model file path
        :return:
        """
        self.model = load_model(path)
        pass

    def __prediction(self, X_gt):
        """
        @private: 执行模型预测
        :param X_gt: 输入真实值
        :return:  输出预测值
        """
        y_hat = self.model.predict(x=X_gt)

        y_hat = self.__make_seqbatch2seq(y_hat)
        return np.array(y_hat)
        # y_hat = np.array(y_hat)
        # if y_hat.size > 0:
        #     return np.array(y_hat[0])
        # else:
        #     return np.array(y_hat)

    def __series_to_supervised(self, data, n_in=60, n_out=0):
        """
        @private: Convert series to supervised learning
        :return:
        """
        """Convert series to supervised learning"""
        data = pd.DataFrame(data)
        cols = list()
        # input sequence (t-n, ... t-1)
        for i in range(n_in, 0, -1):
            cols.append(data.shift(i))

        # forecast sequence (t, t+1, ... t+n)
        for i in range(0, n_out):
            cols.append(data.shift(-i))

        agg = pd.concat(cols, axis=1)

        if True:
            agg.dropna(inplace=True)
        return agg

    def __make_seqbatch2seq(self, in_seqbatch):
        """
        @private: 将多组长时间预测转化为一个 [1,2,3],[2,3,4] => [1,2]
        :param in_seqbatch:
        :return:
        """
        # seq_batch = in_seqbatch.copy()
        seq = []
        for item in in_seqbatch:
            seq.append(item[0])
        return np.array(seq)

    def __get_groundtruth(self, pred_step=1):
        """
        @private: 每拍读取pred_step行文件获取ground truth
        :param pred_step: 多长时间预测一次
        :return: 返回真实的一拍数据，攒60拍后开始预测
        """
        try:
            dataset = self.fileModel.get_data_frame() #self.iter_csv.get_chunk(pred_step)
            dataset = self.__filter_attr(dataset)
        except StopIteration:
            return None

        values = dataset.values
        # scaled_vals = self.scaler.fit_transform(values)

        return np.array(values)

    def on_sim_trigger(self):
        """
        每拍触发
        :return:
        """

        y_hat = np.array([])
        gt = self.__get_groundtruth(pred_step=self.pred_step)[0]  # 获取groundtruth
        self.gt_buf = np.vstack((self.gt_buf, gt)) if self.gt_buf.size > 0 else gt  # .append()
        y_gt_step = gt[self.FEATURE_SIZE - 1]  # type = double

        if (len(self.gt_buf) >= self.sequence_length * self.sequence_init_weight) and (self.iter_count % self.pred_interval == 0):
            reframed = self.__series_to_supervised(self.gt_buf, self.sequence_length)
            values = reframed.values

            X_gt, y_gt = values, values[:, self.y_cols]  # x_gt gt:ground truth
            X_gt = self.scaler.transform(X_gt)
            X_gt = X_gt.reshape((X_gt.shape[0], 1, X_gt.shape[1]))

            # do prediction ::@ test proc time 0.01s
            y_hat = self.__prediction(X_gt)  # 未来5s的数据
            y_hat[y_hat < 0.0] = 0.01
            y_hat = y_hat * self.invert_scale

            self.pred_buf = y_hat

            # 事实buf向前移动一位
            self.gt_buf = self.gt_buf[1:]

        self.iter_count = self.iter_count + 1 # 引用计数加1
        self.get_grpc_buf(y_gt_step, y_hat)

        return self.gt_grpc_buf, self.pred_grpc_buf, self.error_grpc_buf

    def get_grpc_buf(self, y_gt, y_hat):
        """
        获取传回给grpc的buffer数据用于曲线显示
        :param y_gt: 真实值
        :param y_hat: 预测
        :return:
        """
        # y_hat = y_hat.tolist()
        # :block:   gt part
        if self.gt_grpc_buf.size < self.gt_grpc_bufsize:
            self.gt_grpc_buf = np.hstack([self.gt_grpc_buf, y_gt])
        else:
            self.gt_grpc_buf = np.delete(self.gt_grpc_buf, 0)
            self.gt_grpc_buf = np.hstack([self.gt_grpc_buf, y_gt])


        # :block:   pred part
        # : y_hat无数据时补0
        if (self.pred_grpc_buf.size <= self.sequence_length * self.sequence_init_weight) and y_hat.size <= 0:
            self.pred_grpc_buf = np.hstack([self.pred_grpc_buf, 0.0])

        elif (self.pred_grpc_buf.size <= self.sequence_length * self.sequence_init_weight) and y_hat.size > 0:
                self.pred_grpc_buf = np.hstack([self.pred_grpc_buf, y_hat])
        elif (self.pred_grpc_buf.size < self.pred_grpc_bufsize):
            if y_hat.size > 0:
                self.pred_grpc_buf = np.hstack([self.pred_grpc_buf, y_hat[-self.pred_interval:]])
        else:
            if y_hat.size > 0:
                self.pred_grpc_buf = np.delete(self.pred_grpc_buf, np.arange(0, self.pred_interval))
                self.pred_grpc_buf = np.hstack([self.pred_grpc_buf, y_hat[-self.pred_interval:]])

        # :block:   error part
        self.error_grpc_buf = self.gt_grpc_buf - self.pred_grpc_buf[:self.gt_grpc_buf.size]

        pass

