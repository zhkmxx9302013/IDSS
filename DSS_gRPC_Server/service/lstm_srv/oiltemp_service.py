# -*- coding: utf-8 -*-
from lstm_service import LstmService
# from lstm_service_factory import LstmServiceFactory


class OilTempService:
    """
    滑油温度服务类
    """
    def __init__(self):
        model_path = '../data/NN/oiltemp/normed_param50@80@30_step60@30_ep25_batch128_model.h5'  # 训练好的模型加载路径
        weight_path = '../data/NN/oiltemp/normed_param50@80@30_step60@30_ep25_batch128_weight.h5' # 训练好的模型权重加载路径
        pickle_path = '../data/preprocess/oiltemp/scaler_py2.pkl'                                 # 训练时归一化比例参数
        invert_scale = 45.0                                                                       # 线上指标调节参数
        features =  [u'feature1',u'feature2', u'feature3']                                        # 模型需要的特征变量

        self.__obj = LstmService()                                                                # 使用基类LSTM
        self.__obj.set_config(model_path=model_path,                                              # 加载特定模型的配置
                              weight_path=weight_path,
                              scalar_pickle_path=pickle_path,
                              invert_scale=invert_scale,
                              feature_size=len(features),
                              features=features)

        # self.y_hat, self.y_gt, self.gh_err = list(), list(), list()

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


