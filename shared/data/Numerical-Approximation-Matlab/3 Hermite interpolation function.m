for t=2:7
    xfirst=0:pi/t:pi;
    yfirst=sin(xfirst)+cos(xfirst);
    syms x;
    yf=0;
    ydiff=diff(sin(xfirst)+cos(xfirst));
    n=length(xfirst)-1;
    for i=1:n
        list=1;
        for j=1:n
            if i~=j
                list=(x-xfirst(j))/(xfirst(i)-xfirst(j))*list;
            end
        end
        a=list^2*(1-2*subs(diff(list),'x',xfirst(i))*(x-xfirst(i)));
        b=list^2*(x-xfirst(i));
        yf=yf+a*yfirst(i)+b*ydiff(i);
    end
    t
    yf=simplify(yf)
    xsecond=0:pi/t:pi;
    ysecond=subs(yf,'x',xsecond)
    plot(xsecond,ysecond)
    title('Ñ¡È¡t=2µ½6½Úµã')
    subplot(2,3,t-1)
end
plot(xfirst,yfirst)
subplot(2,3,t-1)
