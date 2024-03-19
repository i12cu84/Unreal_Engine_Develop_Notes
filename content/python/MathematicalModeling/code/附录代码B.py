import pandas as pd
a1= pd.read_excel(r"C:\Users\LENOVO\Desktop\国赛C\附件1：123家有信贷记录企业的相关数据.xlsx",sheet_name='进项发票信息')
a11=pd.read_excel(r"C:\Users\LENOVO\Desktop\国赛C\附件1：123家有信贷记录企业的相关数据.xlsx",sheet_name='销项发票信息')
a3= pd.read_excel(r"C:\Users\LENOVO\Desktop\国赛C\附件1：123家有信贷记录企业的相关数据.xlsx",sheet_name='企业信息')
x=[]
for i in range(123):
    x.append('E'+str(i+1))
num=0
a3['进项金额增加']=0
a3['进项金额减少']=0
a3['销项金额增加']=0
a3['销项金额减少']=0
a3['回扣率']=0
a3['蓝票率']=0
for i in x:
    a3.loc[num,"进项金额增加"]=a1.loc[(a1["企业代号"]==i)&(a1["金额"]>0)&(a1["发票状态"]!='作废发票')]['金额'].sum()
    a3.loc[num,"进项金额减少"]=a1.loc[(a1["企业代号"]==i)&(a1["金额"]<0)&(a1["发票状态"]!='作废发票')]['金额'].sum()
    a3.loc[num,"销项金额增加"]=a11.loc[(a11["企业代号"]==i)&(a11["金额"]>0)&(a11["发票状态"]!='作废发票')]['金额'].sum()
    a3.loc[num,"销项金额减少"]=a11.loc[(a11["企业代号"]==i)&(a11["金额"]<0)&(a11["发票状态"]!='作废发票')]['金额'].sum()
    a3.loc[num,"回扣率"]=a11.loc[(a11["企业代号"]==i)&(a11["金额"]<0)&(a11["发票状态"]!='作废发票')].shape[0]/a11.loc[(a11["企业代号"]==i)].shape[0]
    a3.loc[num,"蓝票率"]=a11.loc[(a11["企业代号"]==i)]['发票状态'].value_counts()[0]/a11.loc[(a11["企业代号"]==i)]['发票状态'].value_counts().sum()
    num=num+1
a3['进项金额净增加']=a3['进项金额增加']+a3['进项金额减少']
a3['销项金额净增加']=a3['销项金额增加']+a3['销项金额减少']
a3['净利润']=a3['销项金额净增加']-a3['进项金额净增加']
a3['资产转化率']=a3['销项金额净增加']/a3['进项金额净增加']
a3['净利润占比']=a3['净利润']/a3['净利润'].sum()
a3['蓝票率']=1-a3['蓝票率']
a3[['企业代号','回扣率','蓝票率','资产转化率','净利润占比']].to_csv(r'C:\Users\LENOVO\Desktop\国赛\C\附录B的数据.csv', encoding='utf_8_sig')
# a3.to_csv(r'C:\Users\LENOVO\Desktop\国赛C\附录B的数据.csv', encoding='utf_8_sig')
