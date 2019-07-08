# encoding: utf-8

'''
使用 matplotlib动态更新
'''

from matplotlib import pyplot as plt
import numpy as np
import pandas as pd

df = pd.DataFrame([[0, 1.9, 2.9, 3.9],
                   [1, 2, 3, 4],
                   [2, 2.1, 3.1, 4.1],
                   [3, 2.4, 3.2, 4.3]])

print(df)

df = df.shift(3)
df.dropna(inplace=True)
print(df)
