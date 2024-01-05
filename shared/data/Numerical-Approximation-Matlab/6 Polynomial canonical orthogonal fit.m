
%Legendre
    syms x n
    a = input('a');
    b = input('b');
    y = input('y');
    m = input('m');
    for i = 1:m
        phing = legendreP(i-1,x)/sqrt(2/(2*i-1));
        B(i) = int(str2sym(y)*phing,-1,1);
    end
    number = 0;
    hit = eval(y);
    c=inv(eye(m))*B';
    Q = 0;
    for i = 1:m
        Q = Q + c(i)*legendreP(i-1,x)/sqrt(2/(2*i-1));
    end
    x = linspace(a,b,m+1);
    t = x;
    for i = 1:m+1
        x = t(i);
        number = number + (hit(i)-eval(Q))^2;
    end
    number=t;
    disp(number);
    x = linspace(a,b,200);
    y1 = eval(Q);
    plot(x,y1);
    hold on
end
%once fun
    syms x n
    P = x^n;
    a = input('a');
    b = input('b');
    y = input('y');
    m = input('m');
    A = zeros(m,m);
    for i = 1:m
        for j = 1:m
            phing = subs(P,'n',i-1);
            phiing = subs(P,'n',j-1);
            A(i,j) = int(phing*phiing,a,b);
        end
    end
    B = zeros(1,m);
    for i = 1:m
        phing = subs(P,'n',i-1);
        B(i) = int(str2sym(y)*phing,a,b);
    end
    c = inv(A)*B';
    Q = 0;
    for i = 1:m
        Q = Q + c(i)*subs(P,'n',i-1);
    end
    number = 0;
    x = linspace(a,b,m+1);
    ht = eval(y);
    t = x;
    for i = 1:m+1
        x = t(i);
        number = number + (ht(i)-eval(Q))^2;
    end
    number = toc;
    disp(number);
    x = linspace(a,b,200);
    y1 = eval(Q);
    plot(x,y1);
    hold on
