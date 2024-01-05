clear all;
clc;
X = [3,3;4,3;1,1];
x_1 = X(:,1);
x_2 = X(:,2);
Y = [1,1,-1];
m = size(X);
for i = 1:m(1,1)
    X(i,:) = X(i,:)*Y(1,i);
end
H = X*X';
f = [-1;-1;-1];
A = Y;
b = 0;
lb = zeros(3,1);
[x,fval,exitflag,output,lambda] = quadprog(H,f,[],[],A,b,lb);
n = size(x);
w = x' * X;
for i = 1:n(1,1)
    if x(i,1) > 0
        b = Y(1,i)-w*X(i,:)'*Y(1,i);
        break;
    end
end
y_1 = [0,4];
for i = 1:2
    y_2(1,i) = (-b-w(1,1)*y_1(1,i))./w(1,2);
end
hold on
plot(y_1,y_2);
for i = 1:3
    if Y(1,i) == 1
        plot(x_1(i,:),x_2(i,:),'+b');
    elseif Y(1,i) == -1
        plot(x_1(i,:),x_2(i,:),'ob');
    end
end
axis([0,7,0,7])
hold off
