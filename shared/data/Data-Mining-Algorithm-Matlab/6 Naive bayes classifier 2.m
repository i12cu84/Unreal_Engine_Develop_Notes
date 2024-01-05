clc;clear
Outlook=[1,1,3,2,2,2,3,1,1,2,1,3,3,2]';  
Temperature=[1,1,1,2,3,3,3,2,3,3,2,2,1,2]';  
Humidity=[1,1,1,1,2,2,2,1,2,2,2,1,2,1]';  
Windy=[0,1,0,0,0,1,1,0,0,0,1,1,0,1]'; 
PlayGolf=[0,0,1,1,1,0,1,0,1,1,1,1,1,0]';

temp=[Outlook Temperature Humidity Windy PlayGolf];
yes=find(temp(:,5)==1);
no=find(temp(:,5)==0);
[a,b]=size(yes);  
p_yes=a/14;
p_no=(15-a)/14;

sunny_yes=size(find(temp(yes,1)==1),1)   %2
sunny_no=size(find(temp(no,1)==1),1)   %3
hot_yes=size(find(temp(yes,2)==1),1)   %2
hot_no=size(find(temp(no,2)==1),1)
high_yes=size(find(temp(yes,3)==1),1)
high_no=size(find(temp(no,3)==1),1)
strong_yes=size(find(temp(yes,4)==1),1)
strong_no=size(find(temp(no,4)==1),1)

p_x_yes=sunny_yes*hot_yes*high_yes*strong_yes/(a*a*a*a)
p_x_no=sunny_no*hot_no*high_no*strong_no/((14-a)^4)

if p_x_yes*p_yes>p_x_no*p_no
 disp('do')
else
 disp('no')
end
