syms x n xi
a = 0;b = 1;fx =x^3*sin(x);rou = 1;
fxx = sym(fx);rouu = sym(rou);
A = [int(x*rouu,a,b),int(rouu,a,b);int(rouu*x^2,a,b),int(rouu*x,a,b)];
B = [int(rouu*x^2,a,b); int(rouu*x^3,a,b)];
xx = inv(A)*(-B);
pnx = poly2sym([1 xx']);
X = roots(sym2poly(pnx));
Y = subs(fxx,'x',X);
for i = 1:length(X)
    l=1;
    for j = 1:length(X)
        if i ~= j
            l=(xi - X(j))/(X(i) - X(j))*l;
        end
    end
    AA(1,i) = int(l^2*rou,a,b);
end
XX = subs(fxx,'x',X);
At=[vpa(AA*XX,8)-vpa(int(fx,a,b),8),vpa(AA*XX,8);]
