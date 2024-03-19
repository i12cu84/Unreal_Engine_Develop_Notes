A=[2 -1 0 0 0;
   -1 2 -1 0 0;
   0 -1 2 -1 0;
   0 0 -1 2 -1;
   0 0 0 -1 2];
b=[1;0;0;0;6];
for i=1:5
    E(i)=A(i,i);
    if i<5
        F(i)=A(i,i+1);
        D(i+1)=A(i+1,i);
    end
end
r(1)=E(1);
for i=2:5
     l(i)=D(i)/r(i-1);
     r(i)=E(i)-l(i)*F(i-1);
end
L=eye(5);
for i=2:5
    L(i,i-1)=l(i);
end
U=eye(5)-eye(5);
for i=1:5
    U(i,i)=r(i);
    if i<5
        U(i,i+1)=F(i);
    end
end
L
U
Y(1)=b(1);
for i=2:5
    Y(i)=b(i,1)-L(i)*Y(i-1);
end
Y
for i=1:5
    X(i)=Y(i)/r(i);
end
X
