%%
H=[6,-1;-1,2];
f=[0;0.4];
A=[-1.2,-0.9;0,1];
b=[-1.1;0.7];
Aeq=[1,1];beq=1;
[X,fval,exitflag]=quadprog(H,f,A,b,Aeq,beq)
%%
H=[2 -2;-2 4];
f=[-2;-6];
A=[1 1;-1 2];
b=[2;2];
Aeq=[];beq=[];
lb=[0;0];ub=[];
[X,fval,exitflag]=quadprog(H,f,A,b,Aeq,beq,lb,ub)
%%
H=[2 -2;-2 4];
f=[-4;-12];
A=[1 1;-1 2;2 1];
b=[2;2;3];
lb=zeros(2,1);
[x,fval,exitflag]=quadprog(H,f,A,b,[],[],lb)
