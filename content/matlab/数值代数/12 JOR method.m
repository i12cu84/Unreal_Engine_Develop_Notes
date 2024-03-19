A=[20 2 3;1 8 1;2 -3 15];
b=[25 10 14];
x0=[0.125 0.4 -0.6];
omg=0.9;
t=4;
n=length(A);
x=zeros(n+1,t+1);
x(1,2:t+1)=1:t;
x(2:n+1,1)=x0;
for k = 1:t
    for i = 1:n
        if i==1
            x(i+1,k+1)=-omg*(1/A(i,i))*(sum(A(i,i+1:n)*x(i+2:n+1,k))-b(i));
        end
        if i~=1
            x(i+1,k+1)=-omg*(1/A(i,i))*(sum(A(i,1:i-1)*x(2:i,k))+sum(A(i,i+1:n)*x(i+2:n+1,k))-b(i));
        end
    end
    x(2:n+1,k+1);
end
x
