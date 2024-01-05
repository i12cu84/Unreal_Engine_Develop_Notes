clear
x=[16 9 4 1];
y=[1 2 3 4];
dy=[1/2 1/8];
xx=5;
n = length(x);
for i = 1:n-1
    h(i) = x(i+1)-x(i);
end
for i = 1:n-2
    lemda(i) = h(i+1)/(h(i)+h(i+1));
end
for i = 1:n-2
    miu(i) = 1 - lemda(i);
end
 
x2=x(1:2);
y2=y(1:2);
n1=length(x2);
data=zeros(n1);
for j = 1:n1
    for i = 1:n1        
        if j == 1
            data(i,1) = y2(i);
        else 
            if i + j - 1<=n1
                data(i+j-1,j) = (data(i + j - 2,j-1)-data(i + j - 1,j-1))...
                    /(x2(i + j - 1 - (j - 1))-x2(i + j - 1));
            else 
                break;
            end
        end
    end   
end
temp1 = diag(data)';
 
x3=x(n-1:n);
y3=y(n-1:n);
n1=length(x3);
data=zeros(n1);
for j = 1:n1
    for i = 1:n1        
        if j == 1
            data(i,1) = y3(i);
        else 
            if i + j - 1<=n1
                data(i+j-1,j) = (data(i + j - 2,j-1)-data(i + j - 1,j-1))...
                    /(x3(i + j - 1 - (j - 1))-x3(i + j - 1));
            else 
                break;
            end
        end
    end   
end
temp2 = diag(data)';
d=[];
 
d(1) = 6*(temp1(2)-dy(1))/h(1);
d(n) = 6*(temp2(2)-dy(2))/(-h(n-1));
 
for i = 2:n-1
    %²îÉÌ3
    x4=x(i-1:i+1);
    y4=y(i-1:i+1);
    n1=length(x4);
    data=zeros(n1);
    for j = 1:n1
        for t = 1:n1        
            if j == 1
                data(t,1) = y4(t);
            else 
                if t + j - 1<=n1
                    data(t+j-1,j) = (data(t + j - 2,j-1)-data(t + j - 1,j-1))...
                        /(x4(t + j - 1 - (j - 1))-x4(t + j - 1))
                else 
                    break;
                end
            end
        end   
    end
    temp3 = diag(data)'
    d(i) = 6*temp3(3);
end
 
A = zeros(n,n);
A(1,2) = 1;
A(n,n-1) = 1;
for i = 1:n
    A(i,i) = 2;
    if i>=2 && i <=n-1
        A(i,i+1) = lemda(i-1);
        A(i,i-1) = miu(i-1);
    end
end
M = d/A;
syms xi
S=[];
x
y
for i = 1:3 
    s = M(i)*(x(i+1)-xi)/(6*h(i)) + M(i+1)*(xi-x(i))^3/(6*h(i))+(y(i)-(M(i)*h(i)^2)/6)*(x(i+1)-xi)/h(i) + (y(i+1)-(M(i+1)*h(i)^2)/6)*(xi-x(i))/h(i);
    s=simplify(s);
    S = [S,s];
end
S 
yi=[];
for i = 1:n-1
    if x(i) < xx && x(i+1) > xx
        yi = vpa(subs(S(i),'xi',xx),4);
    end
end
