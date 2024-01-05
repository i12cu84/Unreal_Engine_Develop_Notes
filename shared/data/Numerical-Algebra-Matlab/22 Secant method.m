for k=0:5
    x0=0;
    x1=1;
    x=zeros(2,k+2);
    x(1,3:k+2)=1:k;
    x(2,1)=x0;
    x(2,2)=x1;
    p=[];
    f=inline('x*exp(x)-1','x');
    h=inline('x(2)-(p(2)*(x(2)-x(1)))/(p(2)-p(1))','x','p');
    for i = 1:k
        p(i)=f(x(2,i));
        p(i+1)=f(x(2,i+1));
        x(2,i+2)=h([x(2,i) x(2,i+1)],[p(i) p(i+1)]);
        disp(['第',num2str(i),'次迭代结果为:']);
        x(2,i+2)
    end
end
