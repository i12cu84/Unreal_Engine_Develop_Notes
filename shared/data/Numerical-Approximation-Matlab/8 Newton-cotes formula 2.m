n=7;n=n+1;A0=0;fxx=0;
for i=linspace(a,b,n)
    up=1;down=1;
    for j=linspace(a,b,n)
        if ~(i==j)
            up=up.*(x-j);
            down=down.*(i-j);
        end
    end
    fx=(int(up/down,a,b))./((b-a)/(n-1));
    if i==0
        A0=fx
    end
    fx=fx./A0;
    fxx=fxx+int(up/down,a,b)*subs(y,'x',i);
end
disp(fxx)
