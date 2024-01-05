
#对附件一所给的数据中挖掘出的数据进行特征工程处理，同时找出最优的学习率和#训练集分组
import  numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D
from sklearn.model_selection import train_test_split
from sklearn.svm import LinearSVR#使用线性SVM来处理回归问题
from sklearn.svm import SVR#传入不同的核函数进行计算
from sklearn.preprocessing import StandardScaler#标准化
from sklearn.pipeline import Pipeline
from sklearn import metrics
a4=pd.read_excel(r'C:\Users\LENOVO\Desktop\国赛\B数据.xlsx') 
a4=a4[['回扣率','蓝票率','资产转化率','净利润占比','信誉评级']]
a4.loc[(a4['信誉评级']=='A')]['信誉评级']=4
for i in range(123):#对将信誉评级数据化
    if a4.loc[i,'信誉评级']=='A':
        a4.loc[i,'信誉评级']=3
    elif a4.loc[i,'信誉评级']=='B':
        a4.loc[i,'信誉评级']=2
    elif a4.loc[i,'信誉评级']=='C':
        a4.loc[i,'信誉评级']=1
    else:
        a4.loc[i,'信誉评级']=0
w=(a4-np.min(a4))/(np.max(a4)-np.min(a4))#数据归一化处理
w.to_excel(r'C:\Users\LENOVO\Desktop\国赛\B学习数据.xlsx', encoding='utf_8_sig')#保存文件


data=pd.read_excel(r'C:\Users\LENOVO\Desktop\国赛\B学习数据.xlsx')
data_y=data[['信誉评级']]
data_x=data.drop(labels='信誉评级',axis=1)#

batch_size=[]
learn_rates=[]
result=[]

for i in range(20):
    for j in range(50):
        batch_size.append(0.1+0.01*i)
        learn_rates.append(80+j)
        train_X, test_X, train_Y, test_Y = train_test_split(data_x, data_y, test_size=0.1+0.01*i, random_state=80+j)
        def std(e=0.2):
            return Pipeline([
                ("std_scaler", StandardScaler()),
                ("kinearSvr", LinearSVR(epsilon=e))
            ])
        sss = std(0.1)
        sss.fit(train_X, train_Y)
        print(sss.score(test_X, test_Y))
        predict_test_y = sss.predict(test_X)
        pd.set_option('display.max_columns', None)  # 显示所有行
        pd.set_option('display.max_rows', None)  # 显示所有列
        result.append(metrics.mean_squared_error(predict_test_y, test_Y))
        # print('平均绝对误差:{}'.format(metrics.mean_squared_error(predict_test_y, test_Y)))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
n = 100
ax.scatter(batch_size, learn_rates, result, s=20, c=None, depthshade=True)
ax.set_xlabel('batch_size')
ax.set_ylabel('learn_rates')
ax.set_zlabel('result')
idx=result.index(min(result))
print('最小的情况：')
print(result[idx])
print(batch_size[idx])
print(learn_rates[idx])
plt.show()#绘制三维空间图