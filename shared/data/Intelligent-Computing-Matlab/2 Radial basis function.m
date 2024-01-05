clear
filename = 'D:\irisdata.txt';
[yingweihua_property__1, yingweihua_property__2,yingweihua_property__3, yingweihua_property__4, class] = textread(filename,'%f %f %f %f %s','delimiter',',');
yingweihua_property_1 =[yingweihua_property__1(1:30,:);yingweihua_property__1(51:80,:);yingweihua_property__1(101:130,:)];
yingweihua_property_2 =[yingweihua_property__2(1:30,:);yingweihua_property__2(51:80,:);yingweihua_property__2(101:130,:)];
yingweihua_property_3 =[yingweihua_property__3(1:30,:);yingweihua_property__3(51:80,:);yingweihua_property__3(101:130,:)];
yingweihua_property_4 =[yingweihua_property__4(1:30,:);yingweihua_property__4(51:80,:);yingweihua_property__4(101:130,:)];
class1 =[class(1:30,:);class(51:80,:);class(101:130,:)];
yingweihua_property_5 =[yingweihua_property__1(31:50,:);yingweihua_property__1(81:100,:);yingweihua_property__1(131:150,:)];
yingweihua_property_6 =[yingweihua_property__2(31:50,:);yingweihua_property__2(81:100,:);yingweihua_property__2(131:150,:)];
yingweihua_property_7 =[yingweihua_property__3(31:50,:);yingweihua_property__3(81:100,:);yingweihua_property__3(131:150,:)];
yingweihua_property_8 =[yingweihua_property__4(31:50,:);yingweihua_yingweihua_property__4(81:100,:);yingweihua_yingweihua_property__4(131:150,:)];
class2 =[class(31:50,:);class(81:100,:);class(131:150,:)];
for i = 1:length(class1)
   switch class1{i};
       case 'Setosa'   
           Class(i,:)=[1 0 0];
       case 'Versicolor'
           Class(i,:)=[0 1 0];
       otherwise 'Virginica';
           Class(i,:)=[0 0 1];
   end
end
for i = 1:length(class2)
   switch class2{i};
       case 'Setosa'   
           yingweihua_property_textClass(i,:)=[1 0 0];
       case 'Versicolor'
           yingweihua_property_textClass(i,:)=[0 1 0];
       otherwise 'Virginica';
           yingweihua_property_textClass(i,:)=[0 0 1];
   end
end
yingweihua_property_textClass = yingweihua_property_textClass';
for i = 1:length(Class)
    P(i,:) =[yingweihua_property_1(i,:),yingweihua_property_2(i,:),yingweihua_property_3(i,:),yingweihua_property_4(i,:)];
    T(i,:) = Class(i,:);
end
    P = P';
    T = T';
    Class = Class';
for i = 1:length(yingweihua_property_5*3)
    textP(i,:) =[yingweihua_property_5(i,:),yingweihua_property_6(i,:),yingweihua_property_7(i,:),yingweihua_property_8(i,:)];
end
textP = textP';
net = newrb(P,Class); 
Rbfoutput = sim (net,textP) 
[s1,s2] = size(Rbfoutput);
count = 0;
for i = 1:s2
    [m ,index] = max(Rbfoutput(:,i));
    [l,std] = max(yingweihua_property_textClass(:,i));  
    if(index==std)
        count = count + 1;
    end 
end
sprintf('output%3.3f%%',100*count/s2)
 
clear,clc;
x1=0:0.1:1;
x2=1:0.1:2;
f=20+x1.*x1-10.*cos(2.*pi.*x1)-10.*cos(2.*pi.*x2);
net=newrb([x1;x2],f,0.001,2); 
y=net([x1;x2]);
t=[x1;x2];
plot(t,y,'r');

