x=[1 2 3 4 5];
xi=input("input")
y=[2 15 1.3333 1.25 1.2];
n = length(x);M=ones(n);
for j = 1:n
    for i = 1:n        
        if j == 1
            break;
        else 
            if i<j
                M(i,j)=xi - x(i);
            end
        end
    end
end
temp = prod(M);
yi = 0;
n=length(x);
data=zeros(n);
f = [];
for j = 1:n
    for i = 1:n        
        if j == 1
            data(i,1) = y(i);
        else 
            if i + j - 1<=n
                data(i+j-1,j) = (data(i + j - 2,j-1)-data(i + j - 1,j-1))/(x(i + j - 1 - (j - 1))-x(i + j - 1));
            else 
                break;
            end
        end
    end   
end
f = diag(data)';
for i = 1:n
    yi = yi + temp(i)*f(i);
end
yi
