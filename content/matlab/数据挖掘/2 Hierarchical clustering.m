%once step
X=randn(6,2);
Figure(1)
plot(X(:,1),X(:,2),'bo');
x=reshape(X,12,1); 
y=randn(12,1);
T=clusterdata([x,y],2); 
temp1 = find(T==1)
figure
plot(x(temp1),y(temp1),'rd','markersize',10,'markerfacecolor','r')
hold on
temp1=find(T==2)
plot(x(temp1),y(temp1),'yd','markersize',10,'markerfacecolor','y')
legend('cluster 1','cluster 2')

%more step
dist = pdist(X);%j计算欧式距离
z=linkage(dist)
