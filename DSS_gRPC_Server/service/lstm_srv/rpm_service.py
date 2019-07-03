# -*- coding: utf-8 -*-
# from lstm_service_factory import LstmServiceFactory
from lstm_service import LstmService

class RpmService:
    """
    转速预测服务类
    """
    def __init__(self):

        model_path = '../data/NN/rpm/double_normalized14_100_50_model.h5'
        weight_path = '../data/NN/rpm/double_normalized14_100_50_weight.h5'
        pickle_path = '../data/preprocess/rpm/scaler_py2.pkl'
        invert_scale = 1800.0
        features = [u'feature1',u'feature2', u'feature3']

        self.__obj = LstmService()
        self.__obj.set_config(model_path=model_path,
                            weight_path=weight_path,
                            scalar_pickle_path=pickle_path,
                            invert_scale=invert_scale,
                            feature_size=len(features),
                            features=features)

        self.y_hat, self.y_gt, self.gh_err = list(), list(), list()

    def reset(self):
        # self.obj.reset()
        self.__obj.reset()

    def get_chart_data(self):
        """
        获取前端图像展示的数据集包括预测、真实值、误差值 (builtin list 类型)
        :return:
        """
        # return self.__obj.get_chart_data()
        return self.__obj.on_sim_trigger()


