function [x,minf] = minRosen(f,A,b,x0,var,eps)
format long;
if nargin == 5
    eps = 1.0e-6;
end
syms l;
x0 = transpose(x0);
n = length(var);
sz = size(A);
m = sz(1);
gf = jacobian(f,var);
bConti = 1;

while bConti
    k = 0;
    s = 0;
    A1 = A;
    A2 = A;
    b1 = b;
    b2 = b;
    for i=1:m
        dfun = A(i,:)*x0 - b(i);
        if abs(dfun)<0.000000001
            k = k + 1;
            A1(k,:) = A(i,:);
            b1(k,1) = b(i);
        else
            s = s+1;
            A2(s,:) = A(i,:);
            b2(s,1) = b(i);
        end
    end
    if k > 0
        A1 = A1(1:k,:);
        b1 = b1(1:k,:);
    end
    if s > 0
        A2 = A2(1:s,:);
        b2 = b2(1:s,:);
    end
   
    while 1
        P = eye(n,n);
        if k > 0
            tM = transpose(A1);
            P = P - tM*inv(A1*tM)*A1;
        end
        gv = Funval(gf, var, x0);
        gv = transpose(gv);
        d = -P*gv;
        if d == 0
            if k == 0
                x = x0;
                bConti = 0;
                break;
            else
                w = inv(A1*tM)*A1*gv;
                if w>=0
                    x = x0;
                    bConti = 0;
                    break;
                else
                    [u,index] = min(w);
                    sA1 = size(A1);
                    if sA1(1) == 1
                        k = 0;
                    else
                        k = sA1(2);
                A1 =[ A1(1:(index-1),:); A1((index+1):sA1(2),:)];
                    end
                end
            end
        else
            break;
        end
    end
    yl = x0 + l*d;
    tmpf = Funval(f,var,yl);
    bb = b2 - A2*x0;
    dd = A2*d;
    if dd >= 0
        [tmpI,lm] = minJT(tmpf,0,0.1);
    else
        lm = inf;
        for i=1:length(dd)
            if dd(i) < 0
                if bb(i)/dd(i) < lm
                    lm = bb(i)/dd(i);
                end
            end
        end
    end
    [xm,minf] = minHJ(tmpf,0,lm,1.0e-14);
    tol = norm(xm*d);
    if tol < eps
        x = x0;
        break;
    end
    x0 = x0 + xm*d; 
end
       
minf = Funval(f,var,x);

%use fun
function fv = Funval(f,varvec,varval)
var = findsym(f);
varc = findsym(varvec);
s1 = length(var);
s2 = length(varc);
m =floor((s1-1)/3+1);
varv = zeros(1,m);
if s1 ~= s2
for i=0: ((s1-1)/3)
k = findstr(varc,var(3*i+1));
index = ceil((k-1)/3);
varv(i+1) = varval(index+1);
end
fv = subs(f,var,varv);
else
fv = subs(f,varvec,varval);
end

function [x,minf] = minHJ(f,a,b,eps) 
format long; 
ifnargin == 3 
eps = 1.0e-6; 
end 
 l = a + 0.382*(b-a); 
u = a + 0.618*(b-a); 
k=1; 
tol = b-a; 
whiletol>eps&& k<100000 
fl = subs(f , findsym(f), l); 
fu = subs(f , findsym(f), u); 
iffl>fu 
 a = l; 
 l = u; 
 u = a + 0.618*(b - a); 
else 
 b = u; 
 u = l; 
 l = a + 0.382*(b-a); 
end 
 k = k+1; 
tol = abs(b - a); 
end 
if k == 100000 
disp('not find'); 
 x = NaN; 
minf = NaN; 
return; 
end 
x = (a+b)/2; 
minf = subs(f, findsym(f),x); 
format short; 
 
function [minx,maxx] = minJT(f,x0,h0,eps) 
format long; 
ifnargin == 3 
eps = 1.0e-6; 
end 
x1 = x0; 
k = 0; 
h = h0; 
while 1 
x4 = x1 + h; 
 k = k+1; 
 f4 = subs(f, findsym(f),x4); 
 f1 = subs(f, findsym(f),x1); 
if f4 < f1 
x2 = x1; 
x1 = x4; 
 f2 = f1; 
 f1 = f4; 
 h = 2*h; 
else 
if k==1 
 h = -h; 
x2 = x4; 
f2 = f4; 
else 
x3 = x2; 
x2 = x1; 
x1 = x4; 
break;

syms x1 x2; 
f=x1^3+x2^2-2*x1-4*x2+6;   
[x,mf]=minRosen(f,[2,-1;1,1;-1,0;0,-1],[1;2;0;0],[1 2],[x1 x2]) 
