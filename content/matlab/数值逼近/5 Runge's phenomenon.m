clear
clc
t=15;
syms x0 x1 y x n x_para
x0=-1:0.002:-0.25;
y=1./(1+66*x0.^4);
n=9;
k=0:n; 
x(k+1)=-1+2*k/n; 
for i=1:(n+1)  
    pax(i)=(x_para-x(i));  
end
for i=1:(n+1)  
Wx1(i)=1;
    for j=1:(n+1)
        if i~=j
            Wx1(i)=Wx1(i)*(x(i)-x(j));  
        end
    end
end
Wx(n+1)=prod(pax);
for j=1:(n+1)
    lgx(j)=(1/(1+25*(x(j)^2))) * Wx(n+1) / ( (x_para-x(j))*(Wx1(j)) );
end
LGX=sum(lgx);
xter=-0.9999:0.0002:-0.2499;
LGX=subs(LGX,x_para,xter);
plot(x0,y);
hold on
plot(xter,LGX);
x0=-0.25:0.002:0.25;
y=1./(1+66*x0.^4);
n=t;
k=0:n; 
x(k+1)=-1+2*k/n; 
for i=1:(n+1)  
    pax(i)=(x_para-x(i));  
end
for i=1:(n+1)  
Wx1(i)=1;
    for j=1:(n+1)
        if i~=j
            Wx1(i)=Wx1(i)*(x(i)-x(j));  
        end
    end
end
Wx(n+1)=prod(pax);
for j=1:(n+1)
    lgx(j)=(1/(1+25*(x(j)^2))) * Wx(n+1) / ( (x_para-x(j))*(Wx1(j)) );
end
LGX=sum(lgx);
xter=-0.2499:0.002:0.2499;
LGX=subs(LGX,x_para,xter);
plot(x0,y);
hold on
plot(xter,LGX);
x0=0.25:0.002:1;
y=1./(1+66*x0.^4);
n=t;
k=0:n; 
x(k+1)=-1+2*k/n; 
for i=1:(n+1)  
    pax(i)=(x_para-x(i));  
end
for i=1:(n+1)  
Wx1(i)=1;
    for j=1:(n+1)
        if i~=j
            Wx1(i)=Wx1(i)*(x(i)-x(j));  
        end
    end
end
Wx(n+1)=prod(pax);
for j=1:(n+1)
    lgx(j)=(1/(1+25*(x(j)^2))) * Wx(n+1) / ( (x_para-x(j))*(Wx1(j)) );
end
LGX=sum(lgx);
xter=0.2501:0.002:0.9999;
LGX=subs(LGX,x_para,xter);
plot(x0,y);
hold on
plot(xter,LGX);
