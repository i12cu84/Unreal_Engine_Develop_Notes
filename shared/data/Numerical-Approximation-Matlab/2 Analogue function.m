x=[1 2 3 4 5];
syms xi;
y=[2 15 4/3 1.25 1.2];
yi=0;
n=length(x);
for i = 1:n
    t1=1;t2=1;t3=1;t4=1;t5=1;
    for j = 1:n
        if i ~= j
            if j==1
                t1 = (xi - x(j))/(x(i)-x(j));
            end
            if j==2
                t2 = (xi - x(j))/(x(i)-x(j));
            end
            if j==3
                t3 = (xi - x(j))/(x(i)-x(j));
            end
            if j==4
                t4 = (xi - x(j))/(x(i)-x(j));
            end
            if j==5
                t5 = (xi - x(j))/(x(i)-x(j));
            end
        end
    end
    if i==1
        t1= y(i)  * t1*t2*t3*t4*t5;
    end
    if i==2
        t2= y(i)  * t1*t2*t3*t4*t5;
    end
    if i==3
        t3= y(i)  * t1*t2*t3*t4*t5;
    end
    if i==4
        t4= y(i)  * t1*t2*t3*t4*t5;
    end
    if i==5
        t5= y(i)  * t1*t2*t3*t4*t5;
    end
    if i==1
        yi = yi + t1;
    end
    if i==2
        yi = yi + t2;
    end
    if i==3
        yi = yi + t3;
    end
    if i==4
        yi = yi + t4;
    end
    if i==5
        yi = yi + t5;
    end
end 
simplify(yi)
