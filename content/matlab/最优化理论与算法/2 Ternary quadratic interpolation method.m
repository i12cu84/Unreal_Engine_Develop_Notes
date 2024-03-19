clc
syms x y;
a=26;
fx=x^2+a*y^2;
xy=[2,1];
xgm=0.001;
while(true)
g=[diff(fx,x),diff(fx,y)];
if ((subs(g(1),x,xy(1))).^2+(subs(g(2),y,xy(2))).^2).^0.5 <= xgm
        disp(xy);
        disp(subs(subs(fx,x,xy(2)),y,xy(2)))
        error("error");
end
d=[-subs(g(1),x,xy(1)) -subs(g(2),y,xy(2))];
a=roots(sym2poly(diff(subs(fx,{'x','y'},{xy(1)+x*d(1),xy(2)+x*d(2)}))));
xy(1)=xy(1)+a*d(1);
xy(2)=xy(2)+a*d(2);
end

%output
%   1.0e-03 *
%    0.4436   -0.0013
%259281336376992541387544687469123/5575186299632655785383929568162090376495104
 
