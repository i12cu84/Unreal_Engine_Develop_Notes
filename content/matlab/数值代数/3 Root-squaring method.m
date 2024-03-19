A=[16 4 8;
    4 5 -4;
    8 -4 22];
b=[-4;3;10];
for i=1:3
    E(i)=A(i,i);
    if i<3
        F(i)=A(i,i+1);
        D(i+1)=A(i+1,i);
    end
end
r(1)=E(1);
for i=2:3
     l(i)=D(i)/r(i-1);
     r(i)=E(i)-l(i)*F(i-1);
end
L=eye(3);
for i=2:3
    L(i,i-1)=l(i);
end
U=eye(3)-eye(3);
for i=1:3
    U(i,i)=r(i);
    if i<3
        U(i,i+1)=F(i);
    end
end
D=[U(1,1) 0 0;0 U(2,2) 0;0 0 U(3,3)];
U=inv(D)*U;
L;
D;
U;
D=D^0.5;
L1=L*D
L2=D*U
Y(1)=b(1);
for i=2:3
    Y(i)=b(i,1)-L1(i)*Y(i-1);
end
Y
for i=1:3
    X(i)=Y(i)/U(i,i);;
end
X
