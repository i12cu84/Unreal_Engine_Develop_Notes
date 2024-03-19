k=10;
x0=10;
x=zeros(2,k+1)
x(1,2:k+1)=1:k;
x(2,1)=x0;
h=inline('log(x)+3','x');
for i = 1:k
    x(2,i+1)=h(x(2,i));
    disp(['tip',num2str(i),'output:']);
    x(2,i+1)
end
