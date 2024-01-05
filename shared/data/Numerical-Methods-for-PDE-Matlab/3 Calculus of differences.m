clear
clc
% y'' + P(x)y' + Q(x)y = R(x)
R = @(x)(-sin(x)/sin(1));
n = 20;
x_0 = 0;
x_n = 1;
y_x_0 = 0;
y_x_n = 0;
h = (x_n-x_0)/n;
x = x_0+h:h:x_n;
 
%Ax = B 
A = zeros(n-1,n-1);
B = zeros(n-1,1);
for i = 1:(n-1)
    B(i) = h .^ 2 * R(x(i));
    if(i == 1)
        B(1) = B(1) - 1*y_x_0;
        A(1,1:2) = [-2 , 1];
    elseif(i == n-1)
        B(i) = B(i) - 1*y_x_n;
        A(i,end-1:end) = [1 , -2];
    else
        A(i,i-1:i-1+2) = [1 , -2 , 1];
    end
end
 
y = [y_x_0;A\B;y_x_n]
xx = [x_0,x]';
plot(xx,y,'.-')
