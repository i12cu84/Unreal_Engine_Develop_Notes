#疫情
y=[]
import pandas as pd
a7=pd.read_excel(r'C:\Users\LENOVO\Desktop\第三题数据.xlsx')
a7['贷款份额占比']=0
cov=a7[['企业代号','信誉评级','资产转化率','疫情','净利润占比','贷款份额占比']]
cov_1_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='正')&(cov['资产转化率']>35.802693)]
cov_2_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='无')&(cov['资产转化率']>35.802693)]
cov_3_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='负')&(cov['资产转化率']>35.802693)]
cov_4_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='正')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_5_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='无')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_6_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='负')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_7_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='正')&(cov['资产转化率']<1)]
cov_8_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='无')&(cov['资产转化率']<1)]
cov_9_a=cov.loc[(cov['信誉评级']=='A')&(cov['疫情']=='负')&(cov['资产转化率']<1)]
w=[cov_1_a,cov_2_a,cov_3_a,cov_4_a,cov_5_a,cov_6_a,cov_7_a,cov_8_a,cov_9_a]
v=[5,3,2,3,2,1,2,1,0.5]
xx=0
for i in range(9):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='正')&(cov['资产转化率']>103.394277)]
cov_2_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='无')&(cov['资产转化率']>103.394277)]
cov_3_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='负')&(cov['资产转化率']>103.394277)]
cov_4_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='正')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_5_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='无')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_6_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='负')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_7_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='正')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
cov_8_b=cov.loc[(cov['信誉评级']=='B')&(cov['疫情']=='负')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
w=[cov_1_b,cov_2_b,cov_3_b,cov_4_b,cov_5_b,cov_6_b,cov_7_b,cov_8_b]
v=[3,2,1,2,1,0.5,1,0.5]
xx=0
for i in range(8):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='正')&(cov['资产转化率']>207.84796)]
cov_2_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='无')&(cov['资产转化率']>207.84796)]
cov_3_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='负')&(cov['资产转化率']>207.84796)]
cov_4_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='正')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_5_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='无')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_6_c=cov.loc[(cov['信誉评级']=='C')&(cov['疫情']=='正')&(cov['资产转化率']<2.744126)&
(cov['资产转化率']>1)]
w=[cov_1_c,cov_2_c,cov_3_c,cov_4_c,cov_5_c,cov_6_c]
v=[2,1,0.5,1,0.5,0.5]
xx=0
for i in range(6):
xx=xx+len(w[i])*v[i]
y.append(xx)
print(10000/sum(y))
cov_1_a['贷款份额占比']=5/232
cov_2_a['贷款份额占比']=3/232
cov_3_a['贷款份额占比']=2/232
cov_4_a['贷款份额占比']=3/232
cov_5_a['贷款份额占比']=2/232
cov_6_a['贷款份额占比']=1/232
cov_7_a['贷款份额占比']=2/232
cov_8_a['贷款份额占比']=1/232
cov_8_a['贷款份额占比']=1/232/2
#v=[5,3,2,3,2,1,2,1,0.5]
cov_1_b['贷款份额占比']=3/232
cov_2_b['贷款份额占比']=2/232
cov_3_b['贷款份额占比']=1/232
cov_4_b['贷款份额占比']=2/232
cov_5_b['贷款份额占比']=1/232
cov_6_b['贷款份额占比']=1/232/2
cov_7_b['贷款份额占比']=1/232
cov_8_b['贷款份额占比']=1/232/2
#v=[3,2,1,2,1,0.5,1,0.5]
cov_1_c['贷款份额占比']=2/232
cov_2_c['贷款份额占比']=1/232
cov_3_c['贷款份额占比']=1/232/2
cov_4_c['贷款份额占比']=1/232
cov_5_c['贷款份额占比']=1/232/2
cov_6_c['贷款份额占比']=1/232/2
#v=[2,1,0.5,1,0.5,0.5]
cov_virus=cov_1_a.append(cov_2_a).append(cov_3_a).append(cov_4_a).append(cov_5_a).
append(cov_6_a).append(cov_7_a).append(cov_8_a).append(cov_9_a).append(cov_1_b).
append(cov_2_b).append(cov_3_b).append(cov_4_b).append(cov_5_b).append(cov_6_b).
append(cov_7_b).append(cov_8_b).append(cov_1_c).append(cov_2_c).append(cov_3_c).
append(cov_4_c).append(cov_5_c).append(cov_6_c)
cov_virus['净利润占比占比']=cov_virus['净利润占比']/cov_virus['净利润占比'].sum()
cov_virus['实际信贷份额系数']=(cov_virus['净利润占比占比']+cov_virus['贷款份额占比'])/2
cov_virus['贷款额度']=cov_virus['实际信贷份额系数']*(10000/sum(y))
cov_virus['贷款额度']=cov_virus['贷款额度']*(10000/cov_virus['贷款额度'].sum())
cov_virus[['企业代号','信誉评级','资产转化率','疫情','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop
\题目3突发疫情的数据.csv', encoding='utf_8_sig')
a7=pd.read_csv(r'C:\Users\LENOVO\Desktop\题目3突发疫情的数据.csv')

ww=0
print(a7["贷款额度"].sum())
for i in range(len(a7)):
if a7.loc[i,"贷款额度"]>100:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
elif a7.loc[i,"贷款额度"]<0:
ww=ww+a7.loc[i,"贷款额度"]-10
a7.loc[i,"贷款额度"]=10
elif a7.loc[i,"贷款额度"]<10:
ww=ww-10
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
elif a7.loc[i,"贷款额度"]+10<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
ww=ww-10
else:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
while ww>0:
for i in range(len(a7)):
if ww==0:
break
if a7.loc[i,"贷款额度"]<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+1
ww=ww-1
for i in range(len(a7)):
a7.loc[i,"贷款额度"]=int( a7.loc[i,"贷款额度"]+0.2)
a7[['企业代号','信誉评级','资产转化率','疫情','净利润占比','贷款份额占比','净利润占比占比',
'实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop\国赛\C\论文文件\题目3突发疫情
的最终数据.csv', encoding='utf_8_sig')
#美国制裁
y=[]
import pandas as pd
a7=pd.read_excel(r'C:\Users\LENOVO\Desktop\第三题数据.xlsx')
a7['贷款份额占比']=0
cov=a7[['企业代号','信誉评级','资产转化率','美国制裁','净利润占比','贷款份额占比']]
cov_1_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='正')&(cov['资产转化率']>35.802693)]
cov_2_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='无')&(cov['资产转化率']>35.802693)]
cov_3_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='负')&(cov['资产转化率']>35.802693)]
cov_4_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='正')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_5_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='无')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_6_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='负')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_7_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='正')&(cov['资产转化率']<1)]
cov_8_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='无')&(cov['资产转化率']<1)]
cov_9_a=cov.loc[(cov['信誉评级']=='A')&(cov['美国制裁']=='负')&(cov['资产转化率']<1)]
w=[cov_1_a,cov_2_a,cov_3_a,cov_4_a,cov_5_a,cov_6_a,cov_7_a,cov_8_a,cov_9_a]
v=[5,3,2,3,2,1,2,1,0.5]
xx=0
for i in range(9):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='正')&(cov['资产转化率']>103.394277)]
cov_2_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='无')&(cov['资产转化率']>103.394277)]
cov_3_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='负')&(cov['资产转化率']>103.394277)]
cov_4_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='正')&(cov['资产转化率']<103.394277)
&(cov['资产转化率']>2.03622)]
cov_5_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='无')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_6_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='负')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_7_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='正')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
cov_8_b=cov.loc[(cov['信誉评级']=='B')&(cov['美国制裁']=='负')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
w=[cov_1_b,cov_2_b,cov_3_b,cov_4_b,cov_5_b,cov_6_b,cov_7_b,cov_8_b]
v=[3,2,1,2,1,0.5,1,0.5]
xx=0
for i in range(8):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='正')&(cov['资产转化率']>207.84796)]
cov_2_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='无')&(cov['资产转化率']>207.84796)]
cov_3_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='负')&(cov['资产转化率']>207.84796)]
cov_4_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='正')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_5_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='无')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_6_c=cov.loc[(cov['信誉评级']=='C')&(cov['美国制裁']=='正')&(cov['资产转化率']<2.744126)&
(cov['资产转化率']>1)]
w=[cov_1_c,cov_2_c,cov_3_c,cov_4_c,cov_5_c,cov_6_c]
v=[2,1,0.5,1,0.5,0.5]
xx=0
for i in range(6):
xx=xx+len(w[i])*v[i]
y.append(xx)
print(10000/sum(y))
cov_1_a['贷款份额占比']=5/232
cov_2_a['贷款份额占比']=3/232
cov_3_a['贷款份额占比']=2/232
cov_4_a['贷款份额占比']=3/232
cov_5_a['贷款份额占比']=2/232
cov_6_a['贷款份额占比']=1/232
cov_7_a['贷款份额占比']=2/232
cov_8_a['贷款份额占比']=1/232
cov_8_a['贷款份额占比']=1/232/2
#v=[5,3,2,3,2,1,2,1,0.5]
cov_1_b['贷款份额占比']=3/232
cov_2_b['贷款份额占比']=2/232
cov_3_b['贷款份额占比']=1/232
cov_4_b['贷款份额占比']=2/232
cov_5_b['贷款份额占比']=1/232
cov_6_b['贷款份额占比']=1/232/2
cov_7_b['贷款份额占比']=1/232
cov_8_b['贷款份额占比']=1/232/2
#v=[3,2,1,2,1,0.5,1,0.5]
cov_1_c['贷款份额占比']=2/232
cov_2_c['贷款份额占比']=1/232
cov_3_c['贷款份额占比']=1/232/2
cov_4_c['贷款份额占比']=1/232
cov_5_c['贷款份额占比']=1/232/2
cov_6_c['贷款份额占比']=1/232/2
#v=[2,1,0.5,1,0.5,0.5]
cov_virus=cov_1_a.append(cov_2_a).append(cov_3_a).append(cov_4_a).append(cov_5_a).
append(cov_6_a).append(cov_7_a).append(cov_8_a).append(cov_9_a).append(cov_1_b).
append(cov_2_b).append(cov_3_b).append(cov_4_b).append(cov_5_b).append(cov_6_b).
append(cov_7_b).append(cov_8_b).append(cov_1_c).append(cov_2_c).append(cov_3_c).
append(cov_4_c).append(cov_5_c).append(cov_6_c)
cov_virus['净利润占比占比']=cov_virus['净利润占比']/cov_virus['净利润占比'].sum()
cov_virus['实际信贷份额系数']=(cov_virus['净利润占比占比']+cov_virus['贷款份额占比'])/2
cov_virus['贷款额度']=cov_virus['实际信贷份额系数']*(10000/sum(y))
cov_virus['贷款额度']=cov_virus['贷款额度']*(10000/cov_virus['贷款额度'].sum())
cov_virus[['企业代号','信誉评级','资产转化率','美国制裁','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop\
题目3突发美国制裁的数据.csv', encoding='utf_8_sig')
a7=pd.read_csv(r'C:\Users\LENOVO\Desktop\题目3突发美国制裁的数据.csv')
ww=0
print(a7["贷款额度"].sum())
for i in range(len(a7)):
if a7.loc[i,"贷款额度"]>100:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
elif a7.loc[i,"贷款额度"]<0:
ww=ww+a7.loc[i,"贷款额度"]-10
a7.loc[i,"贷款额度"]=10
elif a7.loc[i,"贷款额度"]<10:
ww=ww-10
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
elif a7.loc[i,"贷款额度"]+10<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
ww=ww-10
else:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
while ww>0:
for i in range(len(a7)):
if ww==0:
break
if a7.loc[i,"贷款额度"]<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+1
ww=ww-1
for i in range(len(a7)):
a7.loc[i,"贷款额度"]=int( a7.loc[i,"贷款额度"]-0.002)
a7[['企业代号','信誉评级','资产转化率','美国制裁','净利润占比','贷款份额占比','净利润占比占比',
'实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop\国赛\C\论文文件\
题目3突发美国制裁的最终数据.csv', encoding='utf_8_sig')
#金融危机
y=[]
import pandas as pd
a7=pd.read_excel(r'C:\Users\LENOVO\Desktop\第三题数据.xlsx')
a7['贷款份额占比']=0
cov=a7[['企业代号','信誉评级','资产转化率','金融危机','净利润占比','贷款份额占比']]
cov_1_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='正')&(cov['资产转化率']>35.802693)]
cov_2_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='无')&(cov['资产转化率']>35.802693)]
cov_3_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='负')&(cov['资产转化率']>35.802693)]
cov_4_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='正')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_5_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='无')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_6_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='负')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_7_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='正')&(cov['资产转化率']<1)]
cov_8_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='无')&(cov['资产转化率']<1)]
cov_9_a=cov.loc[(cov['信誉评级']=='A')&(cov['金融危机']=='负')&(cov['资产转化率']<1)]
w=[cov_1_a,cov_2_a,cov_3_a,cov_4_a,cov_5_a,cov_6_a,cov_7_a,cov_8_a,cov_9_a]
v=[5,3,2,3,2,1,2,1,0.5]
xx=0
for i in range(9):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='正')&(cov['资产转化率']>103.394277)]
cov_2_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='无')&(cov['资产转化率']>103.394277)]
cov_3_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='负')&(cov['资产转化率']>103.394277)]
cov_4_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='正')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_5_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='无')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_6_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='负')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_7_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='正')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
cov_8_b=cov.loc[(cov['信誉评级']=='B')&(cov['金融危机']=='负')&
(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
w=[cov_1_b,cov_2_b,cov_3_b,cov_4_b,cov_5_b,cov_6_b,cov_7_b,cov_8_b]
v=[3,2,1,2,1,0.5,1,0.5]
xx=0
for i in range(8):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='正')&(cov['资产转化率']>207.84796)]
cov_2_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='无')&(cov['资产转化率']>207.84796)]
cov_3_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='负')&(cov['资产转化率']>207.84796)]
cov_4_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='正')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_5_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='无')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_6_c=cov.loc[(cov['信誉评级']=='C')&(cov['金融危机']=='正')&(cov['资产转化率']<2.744126)&
(cov['资产转化率']>1)]
w=[cov_1_c,cov_2_c,cov_3_c,cov_4_c,cov_5_c,cov_6_c]
v=[2,1,0.5,1,0.5,0.5]
xx=0
for i in range(6):
xx=xx+len(w[i])*v[i]
y.append(xx)
print(10000/sum(y))
cov_1_a['贷款份额占比']=5/232
cov_2_a['贷款份额占比']=3/232
cov_3_a['贷款份额占比']=2/232
cov_4_a['贷款份额占比']=3/232
cov_5_a['贷款份额占比']=2/232
cov_6_a['贷款份额占比']=1/232
cov_7_a['贷款份额占比']=2/232
cov_8_a['贷款份额占比']=1/232
cov_8_a['贷款份额占比']=1/232/2
#v=[5,3,2,3,2,1,2,1,0.5]
cov_1_b['贷款份额占比']=3/232
cov_2_b['贷款份额占比']=2/232
cov_3_b['贷款份额占比']=1/232
cov_4_b['贷款份额占比']=2/232
cov_5_b['贷款份额占比']=1/232
cov_6_b['贷款份额占比']=1/232/2
cov_7_b['贷款份额占比']=1/232
cov_8_b['贷款份额占比']=1/232/2
#v=[3,2,1,2,1,0.5,1,0.5]
cov_1_c['贷款份额占比']=2/232
cov_2_c['贷款份额占比']=1/232
cov_3_c['贷款份额占比']=1/232/2
cov_4_c['贷款份额占比']=1/232
cov_5_c['贷款份额占比']=1/232/2
cov_6_c['贷款份额占比']=1/232/2
#v=[2,1,0.5,1,0.5,0.5]
cov_virus=cov_1_a.append(cov_2_a).append(cov_3_a).append(cov_4_a).append(cov_5_a)
.append(cov_6_a).append(cov_7_a).append(cov_8_a).append(cov_9_a).append(cov_1_b).
append(cov_2_b).append(cov_3_b).append(cov_4_b).append(cov_5_b).append(cov_6_b).
append(cov_7_b).append(cov_8_b).append(cov_1_c).append(cov_2_c).append(cov_3_c).
append(cov_4_c).append(cov_5_c).append(cov_6_c)
cov_virus['净利润占比占比']=cov_virus['净利润占比']/cov_virus['净利润占比'].sum()
cov_virus['实际信贷份额系数']=(cov_virus['净利润占比占比']+cov_virus['贷款份额占比'])/2
cov_virus['贷款额度']=cov_virus['实际信贷份额系数']*(10000/sum(y))
cov_virus['贷款额度']=cov_virus['贷款额度']*(10000/cov_virus['贷款额度'].sum())
cov_virus[['企业代号','信誉评级','资产转化率','金融危机','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop\
题目3突发金融危机的数据.csv', encoding='utf_8_sig')
a7=pd.read_csv(r'C:\Users\LENOVO\Desktop\题目3突发金融危机的数据.csv')
ww=0
print(a7["贷款额度"].sum())
for i in range(len(a7)):
if a7.loc[i,"贷款额度"]>100:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
elif a7.loc[i,"贷款额度"]<0:
ww=ww+a7.loc[i,"贷款额度"]-10
a7.loc[i,"贷款额度"]=10
elif a7.loc[i,"贷款额度"]<10:
ww=ww-10
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
elif a7.loc[i,"贷款额度"]+10<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
ww=ww-10
else:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
while ww>0:
for i in range(len(a7)):
if ww==0:
break
if a7.loc[i,"贷款额度"]<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+1
ww=ww-1
for i in range(len(a7)):
a7.loc[i,"贷款额度"]=int( a7.loc[i,"贷款额度"]+0.2)
a7[['企业代号','信誉评级','资产转化率','金融危机','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop
\国赛\C\论文文件\题目3突发金融危机的最终数据.csv', encoding='utf_8_sig')
#自然灾害
y=[]
import pandas as pd
a7=pd.read_excel(r'C:\Users\LENOVO\Desktop\第三题数据.xlsx')
a7['贷款份额占比']=0
cov=a7[['企业代号','信誉评级','资产转化率','自然灾害','净利润占比','贷款份额占比']]
cov_1_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='正')&(cov['资产转化率']>35.802693)]
cov_2_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='无')&(cov['资产转化率']>35.802693)]
cov_3_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='负')&(cov['资产转化率']>35.802693)]
cov_4_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='正')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_5_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='无')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_6_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='负')&(cov['资产转化率']<35.802693)&
(cov['资产转化率']>1)]
cov_7_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='正')&(cov['资产转化率']<1)]
cov_8_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='无')&(cov['资产转化率']<1)]
cov_9_a=cov.loc[(cov['信誉评级']=='A')&(cov['自然灾害']=='负')&(cov['资产转化率']<1)]
w=[cov_1_a,cov_2_a,cov_3_a,cov_4_a,cov_5_a,cov_6_a,cov_7_a,cov_8_a,cov_9_a]
v=[5,3,2,3,2,1,2,1,0.5]
xx=0
for i in range(9):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='正')&(cov['资产转化率']>103.394277)]
cov_2_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='无')&(cov['资产转化率']>103.394277)]
cov_3_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='负')&(cov['资产转化率']>103.394277)]
cov_4_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='正')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_5_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='无')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_6_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='负')&(cov['资产转化率']<103.394277)&
(cov['资产转化率']>2.03622)]
cov_7_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='正')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
cov_8_b=cov.loc[(cov['信誉评级']=='B')&(cov['自然灾害']=='负')&(cov['资产转化率']<2.03622)&
(cov['资产转化率']>1)]
w=[cov_1_b,cov_2_b,cov_3_b,cov_4_b,cov_5_b,cov_6_b,cov_7_b,cov_8_b]
v=[3,2,1,2,1,0.5,1,0.5]
xx=0
for i in range(8):
xx=xx+len(w[i])*v[i]
y.append(xx)
cov_1_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='正')&(cov['资产转化率']>207.84796)]
cov_2_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='无')&(cov['资产转化率']>207.84796)]
cov_3_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='负')&(cov['资产转化率']>207.84796)]
cov_4_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='正')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_5_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='无')&(cov['资产转化率']<207.84796)&
(cov['资产转化率']>2.744126)]
cov_6_c=cov.loc[(cov['信誉评级']=='C')&(cov['自然灾害']=='正')&(cov['资产转化率']<2.744126)&
(cov['资产转化率']>1)]
w=[cov_1_c,cov_2_c,cov_3_c,cov_4_c,cov_5_c,cov_6_c]
v=[2,1,0.5,1,0.5,0.5]
xx=0
for i in range(6):
xx=xx+len(w[i])*v[i]
y.append(xx)
print(10000/sum(y))
cov_1_a['贷款份额占比']=5/232
cov_2_a['贷款份额占比']=3/232
cov_3_a['贷款份额占比']=2/232
cov_4_a['贷款份额占比']=3/232
cov_5_a['贷款份额占比']=2/232
cov_6_a['贷款份额占比']=1/232
cov_7_a['贷款份额占比']=2/232
cov_8_a['贷款份额占比']=1/232
cov_8_a['贷款份额占比']=1/232/2
#v=[5,3,2,3,2,1,2,1,0.5]
cov_1_b['贷款份额占比']=3/232
cov_2_b['贷款份额占比']=2/232
cov_3_b['贷款份额占比']=1/232
cov_4_b['贷款份额占比']=2/232
cov_5_b['贷款份额占比']=1/232
cov_6_b['贷款份额占比']=1/232/2
cov_7_b['贷款份额占比']=1/232
cov_8_b['贷款份额占比']=1/232/2
#v=[3,2,1,2,1,0.5,1,0.5]
cov_1_c['贷款份额占比']=2/232
cov_2_c['贷款份额占比']=1/232
cov_3_c['贷款份额占比']=1/232/2
cov_4_c['贷款份额占比']=1/232
cov_5_c['贷款份额占比']=1/232/2
cov_6_c['贷款份额占比']=1/232/2
#v=[2,1,0.5,1,0.5,0.5]
cov_virus=cov_1_a.append(cov_2_a).append(cov_3_a).append(cov_4_a).append(cov_5_a)
.append(cov_6_a).append(cov_7_a).append(cov_8_a).append(cov_9_a).append(cov_1_b)
.append(cov_2_b).append(cov_3_b).append(cov_4_b).append(cov_5_b).append(cov_6_b)
.append(cov_7_b).append(cov_8_b).append(cov_1_c).append(cov_2_c).append(cov_3_c)
.append(cov_4_c).append(cov_5_c).append(cov_6_c)
cov_virus['净利润占比占比']=cov_virus['净利润占比']/cov_virus['净利润占比'].sum()
cov_virus['实际信贷份额系数']=(cov_virus['净利润占比占比']+cov_virus['贷款份额占比'])/2
cov_virus['贷款额度']=cov_virus['实际信贷份额系数']*(10000/sum(y))
cov_virus['贷款额度']=cov_virus['贷款额度']*(10000/cov_virus['贷款额度'].sum())
cov_virus[['企业代号','信誉评级','资产转化率','自然灾害','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop\
题目3突发自然灾害的数据.csv', encoding='utf_8_sig')
a7=pd.read_csv(r'C:\Users\LENOVO\Desktop\题目3突发自然灾害的数据.csv')
ww=0
print(a7["贷款额度"].sum())
for i in range(len(a7)):
if a7.loc[i,"贷款额度"]>100:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
elif a7.loc[i,"贷款额度"]<0:
ww=ww+a7.loc[i,"贷款额度"]-10
a7.loc[i,"贷款额度"]=10
elif a7.loc[i,"贷款额度"]<10:
ww=ww-10
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
elif a7.loc[i,"贷款额度"]+10<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+10
ww=ww-10
else:
ww=ww+a7.loc[i,"贷款额度"]-100
a7.loc[i,"贷款额度"]=100
while ww>0:
for i in range(len(a7)):
if ww==0:
break
if a7.loc[i,"贷款额度"]<100:
a7.loc[i,"贷款额度"]=a7.loc[i,"贷款额度"]+1
ww=ww-1
for i in range(len(a7)):
a7.loc[i,"贷款额度"]=int( a7.loc[i,"贷款额度"]+0.2)
a7[['企业代号','信誉评级','资产转化率','自然灾害','净利润占比','贷款份额占比',
'净利润占比占比','实际信贷份额系数','贷款额度']].to_csv(r'C:\Users\LENOVO\Desktop
\国赛\C\论文文件
\题目3突发自然灾害的最终数据.csv', encoding='utf_8_sig')