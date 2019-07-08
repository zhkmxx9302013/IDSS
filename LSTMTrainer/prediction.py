import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math
# import Queue

from sklearn.model_selection import train_test_split
from sklearn.svm import SVR
from skbayes.rvm_ard_models import RVR
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import time
from sklearn.metrics import mean_squared_error

from keras.models import Sequential

from keras.models import load_model
from keras.layers import Dense, Activation
from keras.layers import LSTM
import keras.callbacks
from keras.layers import Dropout

np.random.seed(2018)

class DLSTM():
    """双层LSTM构建"""
    def __init__(self):
        self.df_size = 0
        self.X_train = None
        self.y_train = None
        self.X_test = None
        self.y_test = None
        self.scaler = None # Minmax
        pass

    def load_data(self, dataset_path='', sequence_length=60, pred_length=60, test_rto=0.1):
        """squence_length = 120 大约为 10s的时间序列长度"""
        dataset = pd.read_csv(dataset_path, encoding='gb2312', header=0, index_col=0)
        print(dataset)
        dataset.drop(labels=['attr1'], axis=1, inplace=True)
        dataset['attr3'] = dataset['attr3'] / 80.0  
        dataset['attr2'] = dataset['attr2'] * 10.0  
        temp = dataset['attr4']
        dataset.drop(labels=['attr4'], axis=1, inplace=True)
        dataset.insert(4, 'attr4', temp)

        t_num = int(len(dataset) * 0.8)
        test_num = len(dataset) - t_num
        values = dataset.values
        self.scaler = MinMaxScaler(feature_range=(0, 1)).fit_transform(values)

        reframed = self.series_to_supervised(self.scaler, dataset, sequence_length, pred_length)

        # split into train and test sets
        values = reframed.values
        train = values[:t_num, :]
        test = values[t_num:, :]
        # split into input and outputs
        y_cols = [sequence_length + item for item in range(pred_length * 5) if (item+1)%5==0] #选取预测的列
        self.X_train, self.y_train = train[:, :sequence_length * 5], train[:, y_cols]
        self.X_test, self.y_test = test[:, :sequence_length * 5], test[:, y_cols]

        # reshape input to be 3D [samples, timesteps, features]
        self.X_train = self.X_train.reshape((self.X_train.shape[0], 1, self.X_train.shape[1]))
        self.X_test = self.X_test.reshape((self.X_test.shape[0], 1, self.X_test.shape[1]))

        print(self.X_train.shape, self.y_train.shape, self.X_test.shape, self.y_test.shape)

    def series_to_supervised(self, data, dataset, n_in=1, n_out=1, dropnan=True):
        """Convert series to supervised learning"""
        n_vars = 1 if type(data) is list else data.shape[1]
        namelist = dataset.columns.values.tolist()
        data = pd.DataFrame(data)
        cols, names = list(), list()
        # input sequence (t-n, ... t-1)
        for i in range(n_in, 0, -1):
            cols.append(data.shift(i))
            names += [('%s(t-%d)' % (namelist[j], i)) for j in range(n_vars)]
        # forecast sequence (t, t+1, ... t+n)
        for i in range(0, n_out):
            cols.append(data.shift(-i))
            if i == 0:
                names += [('%s(t)' % (namelist[j])) for j in range(n_vars)]
            else:
                names += [('%s(t+%d)' % (namelist[j], i)) for j in range(n_vars)]
        # put it all together
        agg = pd.concat(cols, axis=1)
        agg.columns = names
        # drop rows with NaN values
        if dropnan:
            agg.dropna(inplace=True)
        return agg




    def make_seqbatch2seq(self, in_seqbatch):
        """将多组长时间预测转化为一个 [1,2,3],[2,3,4] => [1,2]"""
        seq_batch = in_seqbatch.copy()
        seq = []
        for item in seq_batch:
            seq.append(item[0])
        return np.array(seq)

    def do_predict(self, data=None):
        self.load_data('processed_data/out2.csv')
        x = self.X_train
        y = self.y_train
        model = load_model('model.h5')
        model.load_weights('weight.h5')
        plt.figure()
        plt.ion()
        plt.legend()
        plt.grid(color='black', linestyle='--', linewidth=1, alpha=0.3)
        plt.title('Prediction')
        plt.grid(True)
        plt.legend()
        history_x_seq = []
        history_y_seq = []#Queue.Queue()
        for i, xi in enumerate(x):
            # history_x_seq.append(xi)
            # history_y_seq.append(y[i])
            if i >= 60 and (i % 60 == 0):
                curr_x = x[i-60: i]
                curr_y = y[i-60: i]
                y_hat = model.predict(x=curr_x)
                y_hat = self.make_seqbatch2seq(y_hat)
                curr_y = self.make_seqbatch2seq(curr_y)

                # print("==hat:")
                # print(y_hat)
                # print("==gd:")
                # print(curr_y)
                # print("==error:")
                # print(y_hat - curr_y)
                plt.cla()
                plt.plot(np.arange(i, i+len(curr_y), 1), curr_y, color='g', linewidth=2, label='ground truth')
                plt.plot(np.arange(i, i+len(y_hat), 1), y_hat, color='y', linewidth=2, label='predict')
                plt.plot(np.arange(i, i+len(y_hat), 1), y_hat - curr_y, color='r', linewidth=2, label='Error')

                plt.pause(0.00001)
                plt.show()

        # batch_size = 512
        # y = self.make_seqbatch2seq(y)
        # y_hat = self.make_seqbatch2seq(y_hat)
        # plt.pause(0.0001)








    def __plot_result(self, y_test, y_hat, history):
        """
        绘制图像
        @:param y_test ground truth数据标签
        @:param y_hat 网络预测标签
        @:param history 网络loss集合
        """
        fig = plt.figure(dpi=300)
        ax = fig.add_subplot(111)
        ax.plot(np.arange(1, len(y_test) + 1, 1), y_test, color='g', linewidth=1, label='ground truth')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat, color='y', linewidth=1, label='predict')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat - y_test, color='r', linewidth=1, label='E')
        ax.legend()
        plt.title('Prediction')
        plt.show()

        fig = plt.figure(dpi=300)
        ax = fig.add_subplot(111)
        plt.title('loss')
        ax.plot(history.history['loss'], label='train')
        ax.plot(history.history['val_loss'], label='test')
        ax.legend()
        plt.show()


if __name__ == '__main__':
    lstm = DLSTM()

    # lstm.run_network(datapath='processed_data/out3.csv')
    # lstm.run_network(datapath='processed_data/out1.csv', pretrained=True)
    lstm.do_predict()
