import pandas as pd
import numpy as np
a5=pd.read_excel(r"C:\Users\LENOVO\Desktop\国赛\第二题数据处理的表.xlsx")
a6=a5.loc[(a5['净利润占比']>0)&(a5['信誉评级']!='D')][['净利润占比','信誉评级']]#a6是对a5按照一定条件筛选的结果
a6['净利润占比占比']=0
a6.to_excel(r'C:\Users\LENOVO\Desktop\国赛\中间文件a.xlsx')
a6=pd.read_excel(r"C:\Users\LENOVO\Desktop\国赛\中间文件a.xlsx")
for i in range(210):
    if a6.loc[i,"信誉评级"]=='A':
        a6.loc[i,"净利润占比占比"]=a6.loc[i,"净利润占比"]*5
    elif a6.loc[i,"信誉评级"]=='B':
        a6.loc[i,"净利润占比占比"]=a6.loc[i,"净利润占比"]*3
    else:
        a6.loc[i,"净利润占比占比"]=a6.loc[i,"净利润占比"]*2
a6['净利润占比占比']=a6['净利润占比占比']/a6['净利润占比占比'].sum()
a6['分配额']=0
a6['分配额']=a6['净利润占比占比']*10000
for i in range(210):
    a6.loc[i,"分配额"]=int(a6.loc[i,"分配额"]+0.467)
a6.to_excel(r'C:\Users\LENOVO\Desktop\国赛\C\附录代码F的数据.xlsx')