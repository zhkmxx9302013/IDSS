# IDSS

### 1.文件组织

**DSS_Client** 为IDSS智能决策支持系统客户端代码(QT+grpc)

**DSS_Server**为IDSS智能决策支持系统服务端代码(Python+Keras+grpc+CLIPS)

* 服务端代码包括工厂模式的多网络模型扩展
* grpc服务
* MVC结构
* CLIPS专家系统集成

**DSS_AlgoTrain**为IDSS预测部分训练代码及相关训练、线上效果

无敏感文件，提供框架模式代码及算法训练代码，不提供数据集，客户端不提供界面资源文件，但提供部分仪表代码。

### 