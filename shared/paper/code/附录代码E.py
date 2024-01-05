
#根据附录代码D中所得到的最优训练集分割和最优学习率对附件二中所得数据进行预测，对每家企业进行信誉评级预测
import  numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import LinearSVR#使用线性SVM来处理回归问题
from sklearn.svm import SVR#传入不同的核函数进行计算
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.svm import LinearSVR#使用线性SVM来处理回归问题
from sklearn.svm import SVR#传入不同的核函数进行计算
from sklearn.preprocessing import StandardScaler#标准化
from sklearn.pipeline import Pipeline
from sklearn import metrics


data=pd.read_excel(r'C:\Users\LENOVO\Desktop\国赛\B学习数据.xlsx')#训练数据
preds=pd.read_csv(r'C:\Users\LENOVO\Desktop\国赛\C\论文文件\附录C的数据.csv')
preds=preds.drop(labels='企业代号',axis=1)
w=(preds-np.min(preds))/(np.max(preds)-np.min(preds))#归一化处理

data_y=data[['信誉评级']]
data_x=data.drop(labels='信誉评级',axis=1)#
train_X,test_X,train_Y,test_Y = train_test_split(data_x,data_y,test_size=0.11,random_state=109)#最优学习率和测试分割
def std(e=0.2):
    return Pipeline([
        ("std_scaler",StandardScaler()),
        ("kinearSvr",LinearSVR(epsilon=e))
        ])
sss=std(0.1)
sss.fit(train_X,train_Y)
# print(sss.score(test_X,test_Y))
predict_result = sss.predict(w)
W=pd.DataFrame(predict_resulty,columns=['信誉评价因子'])

W.to_excel(r'C:\Users\LENOVO\Desktop\国赛\C\附录C信誉评级预测.xlsx')