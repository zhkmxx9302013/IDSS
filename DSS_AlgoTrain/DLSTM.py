import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math
from sklearn.externals import joblib
from sklearn.model_selection import train_test_split
from sklearn.svm import SVR
from skbayes.rvm_ard_models import RVR
from sklearn.preprocessing import StandardScaler, MinMaxScaler
import time
from sklearn.metrics import mean_squared_error

from keras.models import Sequential
from keras import losses
from keras.models import load_model
from keras.layers import Dense, Activation
from keras.layers import LSTM
import keras.callbacks
from keras.layers import Dropout

import tensorflow as tf
from keras import backend as K

num_cores = 4
num_CPU = 1
num_GPU = 0
config = tf.ConfigProto(intra_op_parallelism_threads=num_cores,\
        inter_op_parallelism_threads=num_cores, allow_soft_placement=True,\
        device_count = {'CPU' : num_CPU, 'GPU' : num_GPU})
session = tf.Session(config=config)
K.set_session(session)

np.random.seed(2018)

class DLSTM():
    """双层LSTM构建"""
    def __init__(self):
        self.df_size = 0
        self.X_train = None
        self.y_train = None
        self.X_test = None
        self.y_test = None
        self.scaler = StandardScaler() # Minmax
        pass

    def load_data(self, dataset_path='', sequence_length=120, pred_length=60, test_rto=0.1):
        """squence_length = 120 大约为 10s的时间序列长度"""
        FEATURE_NUM = 7
        dataset = pd.read_csv(dataset_path, encoding='gb2312', header=0)
        dataset = dataset[~dataset.index.duplicated()]
        dataset = dataset.drop(['时间'], axis=1)
        dataset = pd.DataFrame(dataset, index=range(0, dataset.shape[0], 5))

        t_num = int(len(dataset) * 0.8)
        values = dataset.values

        reframed = self.series_to_supervised(values, dataset, sequence_length, pred_length)

        # split into train and test sets
        values = reframed.values
        train = values[:t_num, :]
        test = values[t_num:, :]

        # split into input and outputs
        y_cols = [sequence_length * FEATURE_NUM + item for item in range(pred_length * FEATURE_NUM) if (item+1)%FEATURE_NUM==0] #选取预测的转速列

        Scalar = StandardScaler()
        self.X_train, self.y_train = train[:, :sequence_length* FEATURE_NUM], train[:, y_cols]
        self.X_test, self.y_test = test[:, :sequence_length* FEATURE_NUM], test[:, y_cols]

        self.X_train = Scalar.fit_transform(self.X_train)
        self.y_train = self.y_train / 5000.0
        self.X_test = Scalar.transform(self.X_test)
        self.y_test = self.y_test / 5000.0

        self.X_train = self.X_train.reshape((self.X_train.shape[0], 1, self.X_train.shape[1]))
        self.X_test = self.X_test.reshape((self.X_test.shape[0], 1, self.X_test.shape[1]))

        print(self.X_train.shape, self.y_train.shape, self.X_test.shape, self.y_test.shape)

    def load_train_data(self, dataset_path='', sequence_length=60, pred_length=60, test_rto=0.1):
        """squence_length = 120 大约为 10s的时间序列长度"""
        FEATURE_NUM = 7
        dataset = pd.read_csv(dataset_path, encoding='gb2312', header=0)
        dataset = dataset.append(pd.read_csv('processed_data/out1.csv', encoding='gb2312', header=0))
        dataset = dataset.drop(['时间'],axis=1)
        dataset = dataset[~dataset.index.duplicated()]
        print(dataset.shape)
        dataset = pd.DataFrame(dataset, index=range(0,dataset.shape[0], 5))
        values = dataset.values

        reframed = self.series_to_supervised(values, dataset, sequence_length, pred_length)

        # split into train and test sets
        values = reframed.values
        train = values[:, :]

        # split into input and outputs

        y_cols = [sequence_length * FEATURE_NUM + item for item in range(pred_length * FEATURE_NUM) if (item+1)%FEATURE_NUM==0] #选取预测的转速列
        self.X_train, self.y_train = train[:, :sequence_length* FEATURE_NUM], train[:, y_cols]

        # 标准化，归一化
        self.X_train = self.scaler.fit_transform(self.X_train)
        joblib.dump(self.scaler, 'scaler_py2.pkl', protocol=2)  # save to disk
        self.y_train = self.y_train / 5000.0

        # reshape input to be 3D [samples, timesteps, features]
        self.X_train = self.X_train.reshape((self.X_train.shape[0], 1, self.X_train.shape[1]))

        print(self.X_train.shape, self.y_train.shape)

    def load_test_data(self, dataset_path='', sequence_length=60, pred_length=60, test_rto=0.1):
        """squence_length = 120 大约为 10s的时间序列长度"""
        FEATURE_NUM = 7
        dataset = pd.read_csv(dataset_path, encoding='gb2312', header=0)
        dataset = dataset.drop(['时间'],axis=1)
        dataset = dataset[~dataset.index.duplicated()]
        dataset = pd.DataFrame(dataset, index=range(0, dataset.shape[0], 5))
        values = dataset.values
        reframed = self.series_to_supervised(values, dataset, sequence_length, pred_length)

        # split into train and test sets
        values = reframed.values
        test = values[:, :]

        # split into input and outputs
        y_cols = [sequence_length * FEATURE_NUM + item for item in range(pred_length * FEATURE_NUM) if (item+1)%FEATURE_NUM==0] #选取预测的转速列

        #归一化
        self.X_test, self.y_test = test[:, :sequence_length* FEATURE_NUM], test[:, y_cols]
        self.X_test = self.scaler.transform(self.X_test)
        self.y_test = self.y_test / 5000.0

        # reshape input to be 3D [samples, timesteps, features]
        self.X_test = self.X_test.reshape((self.X_test.shape[0], 1, self.X_test.shape[1]))

        print(self.X_test.shape, self.y_test.shape)

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



    def build_model(self, n_batch=512):
        """构建LSTM"""
        model = Sequential()
        layers = [4, 100, 30, 50, 1]
        model.add(LSTM(
            layers[1],
            input_shape=(self.X_train.shape[1], self.X_train.shape[2]),
            return_sequences=True
        ))
        model.add(Dropout(0.1)) # 0.2

        # model.add(LSTM(
        #     layers[2],
        #     input_shape=(self.X_train.shape[1], self.X_train.shape[2]),
        #     return_sequences=True
        # ))
        # model.add(Dropout(0.2))

        model.add(LSTM(
            layers[2],
            return_sequences=False))
        # model.add(Dropout(0.1))

        model.add(Dense(
            self.y_test.shape[1]))
        model.add(Activation("linear"))

        start = time.time()
        model.summary()
        model.compile(loss=losses.mean_squared_error, optimizer="adam")
        print("Compilation Time : ", time.time() - start)
        return model

    def make_seqbatch2seq(self, in_seqbatch):
        """将多组长时间预测转化为一个 [1,2,3],[2,3,4] => [1,2]"""
        seq_batch = in_seqbatch.copy()
        seq = []
        for item in seq_batch:
            seq.append(item[0])
        return np.array(seq)

    def do_predict(self, path=''):
        self.load_data(path, sequence_length=60, pred_length=30)
        x = self.X_train
        y = self.y_train
        # batch_size = 512
        model = load_model('model/double_normalized14_100_100_1s_model.h5')
        model.load_weights('model/double_normalized14_100_100_1s_weight.h5')
        y_hat = model.predict(x=x)

        y = self.make_seqbatch2seq(y)
        y_hat = self.make_seqbatch2seq(y_hat)

        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.arange(1, len(y) + 1, 1), y, color='g', linewidth=1, label='ground truth')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat, color='y', linewidth=1, label='predict')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat - y, color='r', linewidth=1, label='E')
        ax.legend()
        plt.title('Prediction')
        plt.show()

        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.arange(1, len(y) + 1, 1), y * 5000.0, color='g', linewidth=1, label='ground truth')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat * 5000.0, color='y', linewidth=1, label='predict')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat * 5000.0 - y * 5000.0, color='r', linewidth=1, label='E')
        ax.legend()
        plt.title('Inverse Prediction')
        plt.show()


    def run_network(self, datapath='', pretrained=False):
        """
        训练网络
        :param model:
        :param data:
        :return:
        """
        model_path = 'model/double_normalized14_100_100_1s_model.h5'
        weight_path = 'model/double_normalized14_100_100_1s_weight.h5'#'./model/' + str(time.strftime('%Y%m%d:%H_%M',time.localtime(time.time()))) + '_DLSTM.h5'

        epochs = 15
        batch_size = 256
        ratio = 0.1
        sequence_length = 60
        pred_length = 30


        print('Loading data... ')
        # self.load_data(path_to_dataset, sequence_length, 60, ratio)
        self.load_train_data('processed_data/out4.csv', sequence_length, pred_length, ratio)
        self.load_test_data('processed_data/out2.csv', sequence_length, pred_length, ratio)


        print(self.scaler.mean_, self.scaler.var_)
        print('\nData Loaded. Compiling...\n')

        tb_cb = keras.callbacks.TensorBoard(log_dir='log/double_normalized14_100_100_1s_unstateful', histogram_freq=10)
        cbks = [tb_cb]

        model = self.build_model(n_batch=batch_size)
        if pretrained:
            model.load_weights(weight_path)
            print('weight loaded')

        model.save(model_path)
        history = model.fit(
            self.X_train, self.y_train,
            batch_size=batch_size, epochs=epochs, validation_split=0.2, verbose=1, shuffle=True, callbacks=cbks)
        model.save_weights(weight_path)
        # model.save(model_path)
        cv_X = np.reshape(self.X_test, (len(self.X_test), self.X_test.shape[1], self.X_test.shape[2]))

        y_hat_rnn = model.predict(cv_X)
        testScore = math.sqrt(mean_squared_error(self.y_test, model.predict(self.X_test)))
        print('Test Score: %.2f RMSE' % (testScore))

        y_test = self.make_seqbatch2seq(self.y_test)
        y_hat_rnn = self.make_seqbatch2seq(y_hat_rnn)

        self.__plot_result(y_test=y_test, y_hat=y_hat_rnn, history=history)


    def __plot_result(self, y_test, y_hat, history):
        """
        绘制图像
        @:param y_test ground truth数据标签
        @:param y_hat 网络预测标签
        @:param history 网络loss集合
        """
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.arange(1, len(y_test) + 1, 1), y_test, color='g', linewidth=1, label='ground truth')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat, color='y', linewidth=1, label='predict')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat - y_test, color='r', linewidth=1, label='E')
        ax.legend()
        plt.title('Prediction')
        plt.show()



        y_hat = y_hat * 5000.0
        y_test = y_test * 5000.0
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(np.arange(1, len(y_test) + 1, 1), y_test, color='g', linewidth=1, label='ground truth')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat, color='y', linewidth=1, label='predict')
        ax.plot(np.arange(1, len(y_hat) + 1, 1), y_hat - y_test, color='r', linewidth=1, label='E')
        ax.legend()
        plt.title('Prediction inverse_norm')
        plt.show()

        fig = plt.figure()
        ax = fig.add_subplot(111)
        plt.title('loss')
        ax.plot(history.history['loss'], label='train')
        ax.plot(history.history['val_loss'], label='test')
        ax.legend()
        plt.show()


if __name__ == '__main__':
    lstm = DLSTM()

    lstm.run_network()
    # lstm.run_network(datapath='processed_data/out1.csv', pretrained=True)
    # lstm.do_predict('processed_data/out5.csv')
