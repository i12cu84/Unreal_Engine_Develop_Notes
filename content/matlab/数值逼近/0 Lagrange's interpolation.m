x=[1 2 3 4 5];
xi=input("input ")
y=[2 15 1.3333 1.25 1.2];
yi=0;
n=length(x);
for i = 1:n
    t = ones(1,n);
    for j = 1:n
        if i ~= j
            t(j) = (xi - x(j))/(x(i)-x(j));
        end
    end
    t(i) = y(i) * prod(t);
    yi = yi + t(i);
end
yi
