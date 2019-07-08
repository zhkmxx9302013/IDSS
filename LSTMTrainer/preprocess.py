import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

class Preprocess():
    """数据预处理"""

    def LSTM_preprocess(self):
        """为LSTM预处理的时序数据"""
        file_paths = ['data/1.csv',
                      'data/2.csv',
                      'data/3.csv',
                      'data/4.csv',
                      'data/5.csv']

        height_mapping = {
            'attr1': 3,
            'attr2': 2,
            'attr3': 1}

        dataframes = []

        for file in file_paths:
            raw_dataset = pd.read_csv(file, encoding='gb2312')
            raw_dataset = raw_dataset[['attr1','attr2','attr3','attr4','attr5','attr6','attr7','attr8','attr9','attr10']]
            raw_dataset['attr3'] = raw_dataset['attr3'].map(height_mapping)
            raw_dataset['attr1'] = raw_dataset.apply(lambda x: (x[2] == 2 and x[3]) or (x[2] == 3 and x[4]) or x[5],
                                                     axis=1)
            new_col = raw_dataset['attr1']
            raw_dataset.drop(labels=['attr1'], axis=1, inplace=True)
            raw_dataset.insert(1, 'attr1', new_col)
            raw_dataset.drop(labels=['m1','m2','m3'], axis=1, inplace=True)
            dataframes.append(raw_dataset)
        i = 0
        for df in dataframes:
            i = i + 1
            filename = 'processed_data/out{}.csv'.format(i)
            df.to_csv(filename,index=False,columns=['attr1','attr2','attr3','attr4','attr5','attr6','attr7','attr8'])

    def unit_test(self):
        list = [[1,2,3],[2,2,3],[3,2,3]]
        # df = pd.DataFrame(list)
        # print(df)
        # df[0] = df[0] - 10
        # print(df)
        list = np.array(list)
        print(list)
        print(list[:,[0 + item for item in range(3) if item%1==0] ])

        # print(len(pd.read_csv('processed_data/out1.csv',encoding="gb2312")))

if __name__ == '__main__':
    preprocess = Preprocess()
    # preprocess.unit_test()
    preprocess.LSTM_preprocess()