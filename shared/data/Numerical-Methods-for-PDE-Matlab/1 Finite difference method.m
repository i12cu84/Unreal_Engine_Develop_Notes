clear
% y'' + P(x)y' + Q(x)y = R(x)
P = @(x)(x);
Q = @(x)(sin(x));
R = @(x)(x^2);
n = 100;
x_0 = 1;
x_n = 2;
y_x_0 = 4;
y_x_n = 10;
h = (x_n-x_0)/n;
x = x_0+h:h:x_n;

%Ax = B
A = zeros(n-1,n-1);
B = zeros(n-1,1);
for i = 1:(n-1)
    B(i) = h .^ 2 * R(x(i));
    if(i == 1)
        B(1) = B(1) - (1-h/2*P(x(i)))*y_x_0;
        A(1,1:2) = [h.^2*Q(x(i))-2 , (1+h/2*P(x(i)))];
    elseif(i == n-1)
        B(i) = B(i) - (1+h/2*P(x(i)))*y_x_n;
        A(i,end-1:end) = [(1-h/2*P(x(i))) , h.^2*Q(x(i))-2];
    else
        A(i,i-1:i-1+2) = [(1-h/2*P(x(i))) , h.^2*Q(x(i))-2 , (1+h/2*P(x(i)))];
    end
end

y = [y_x_0;A\B;y_x_n];
xx = [x_0,x]';
plot(xx,y,'.-')
