clear
clc
A = [1 -2;-2 2];
b=[-4 0]';
x0=[0 0]';
max_iter=5;
[y,iter]=cgm (A,b,x0,max_iter);
fprintf('\nsetp:%d \n',iter);
fprintf('output: \n');
fprintf('%10.6f',y);

function [x,iter] = cgm (A,b,x0,max_iter)
x=x0;
epsilon=1.0e-6;
fprintf('\n x0= ');
fprintf('   %10.6f',x0);
r=b-A*x;
d=r;
for k=0:max_iter
    alpha=(r'*r)/(d'*A*d);
    xx=x+alpha*d;
    rr=b-A*xx;
    if (norm(rr,2)/norm(b,2))<= epsilon
        iter = k+1;
        x=xx;
        r=rr;
        fprintf('\n x%d = ',k+1);
        fprintf('   %10.6f',x);
        fprintf('\n r%d = ',k+1);
        fprintf('   %10.6f',r);
        return
    end
    beta=(rr'*rr)/(r'*r);
    d=rr+beta*d;
    x=xx;
    r=rr;
    fprintf('\n x%d = ',k+1);
    fprintf('   %10.6f',x);
end
iter = max_iter;
end
