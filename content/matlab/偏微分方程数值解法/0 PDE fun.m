function [c,f,s]=utfss_kpqs_rwq2pdefun(x,t,u,dudx)
c=[1 1]';
f=[1 1]'.*dudx;
y=u(1)-u(2);
F=exp(y)-exp(y);
s=[-F F]';
function [pltfss_kpqs_rwq,qltfss_kpqs_rwq,prtfss_kpqs_rwq,qrtfss_kpqs_rwq]=utfss_kpqs_rwq2bc(xl,ul,xr,ur,t)
pltfss_kpqs_rwq=[0 ul(2)]';
qltfss_kpqs_rwq=[1 0]';
prtfss_kpqs_rwq=[ur(1)-1 0]';
qrtfss_kpqs_rwq=[0 1]'; 
m=0;
    x= linspace(0,1,13);
t= linspace(0,2,9);
sol=pdepe(m,@utfss_kpqs_rwq2pdefun,[1 0]',@utfss_kpqs_rwq2bc,x,t);%
u1tfss_kpqs_rwq=sol(:,:,1);
u2tfss_kpqs_rwq=sol(:,:,2);

figure(1)
surf(x,t,u1tfss_kpqs_rwq)
title('u1tfss_kpqs_rwq output')
xlabel('x')
ylabel('t')
figure(2)
surf(x,t,u2tfss_kpqs_rwq)
title('u2tfss_kpqs_rwq output')
xlabel('x')
ylabel('t')
