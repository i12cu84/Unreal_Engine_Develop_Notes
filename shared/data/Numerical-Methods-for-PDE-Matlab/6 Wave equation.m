a = 2*pi;
b = 1;
c = 1;
n = 101;
m = 101;
h = a/(n-1);
k = b/(m-1);
r = c*k/h;
r2 = r^2;
r22 = r^2/2;
s1 = 1 - r^2;
s2 = 2 - 2*r^2;
U = zeros(n,m);
f = @(x)sin(pi*x);
g = @(x)cos(pi*x);
for i = 2:n-1
    U(i,1) = feval(f,h*(i-1));
    U(i,2) = s1*feval(f,h*(i-1))+k*feval(g,h*(i-1))...
        +r22*(feval(f,h*i)+feval(f,h*(i-2)));
end
for j = 3:m
    for i = 2:n-1
        U(i,j) = s2*U(i,j-1) + r2*(U(i-1,j-1)+U(i+1,j-1))-U(i,j-2);
    end
end
U = U';
x = linspace(0,1,m);
t = linspace(0,2*pi,n);
[X Y] = meshgrid(x,t);
mesh(X,Y,U);

