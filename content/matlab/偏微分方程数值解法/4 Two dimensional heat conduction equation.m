clear all;
close all;
clc;
t = 1;    
x = 1;y = 1;    
m = 100;        
n = 10;        
k = 10;      
ht = t/(m-1);   
hx = x/(n-1);   
hy = y/(k-1);   
f=[];
N = n;
x = linspace(0,1,N);
y = linspace(0,1,N);
for i = 1:N
    for j = 1:N
        f(i,j) = x(i)*x(j);
    end
end
u = zeros(m,n,k);
 
[x,y] = meshgrid(0:hx:1,0:hy:1);
u(1,:,:) = f;
 
for ii=1:m-1
    for jj=2:n-1
        for kk=2:k-1
            u(ii+1,jj,kk) = ht*(u(ii,jj+1,kk)+u(ii,jj-1,kk)-2*u(ii,jj,kk))/hx^2 + ...
                ht*(u(ii,jj,kk+1)+u(ii,jj,kk-1)-2*u(ii,jj,kk))/hy^2 + u(ii,jj,kk);
        end
    end
end
 
for i=1:m
    figure(1);
    mesh(x,y,reshape(u(i,:,:),[n k]));
    axis([0 1 0 1 -2 2]);
end
