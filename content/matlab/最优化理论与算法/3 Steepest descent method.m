syms x y
Fx=x^2+2*y^2;
epson=1e-12;
k=0;
xy=[2 1];
Gk=[diff(Fx,'x'),diff(Fx,'y')];
gk=sqrt(subs(Gk(1),x,xy(1))^2+subs(Gk(2),y,xy(2))^2);
while(1)
    if gk<=epson
    disp(gk)
    error("success")
    end
    Gk2=[diff(diff(Fx,'x'),'x'),diff(diff(Fx,'x'),'y');
        diff(diff(Fx,'x'),'y'),diff(diff(Fx,'y'),'y')];
    gk=sqrt(subs(Gk2(1),x,xy(1))^2+subs(Gk2(2,2),y,xy(2))^2);
    
    p = -inv(Gk2).*[4,4]';        
    yy = subs(Fx,{'x','y'}, {xy(1)+x*p(1),xy(2)+x*p(2)});
    P=diff(yy);
    a=roots(sym2poly(P));
    xy(1) = xy(1) + a*p(1);
    xy(2) = xy(2) + a*p(2,1);
    k=k+1;
end