function Powell()
syms x1 x2 x3 a;f=10*(x1+x2-5)^4+(x1-x2+x3)^2 +(x2+x3)^6;error=10^(-4);D=eye(3);x0=[1 1 1]'; 
for k=1:1:10^6
    MaxLength=0;x00=x0;m=0;
    if k==1,s=D;end
    for i=1:3
            x=x0+a*s(:,i);ff=subs(f,{x1,x2,x3},{x(1),x(2),x(3)});fdiv=ff;xdiv=a;
            if nargin<4,ndiv=1e-6;end
            if nargin<3,mdiv=0;end
            stepdiv=ndiv;t0div=mdiv;ft0div=subs(fdiv,{xdiv},{t0div});t1div=t0div+stepdiv;ft1div=subs(fdiv,{xdiv},{t1div});
            if ft0div>=ft1div
                t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
                while ft1div>ft2div
                    t0div=t1div;t1div=t2div;ft1div=ft2div;stepdiv=2*stepdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
                end
            else 
                stepdiv=-stepdiv;tdiv=t0div;t0div=t1div;t1div=tdiv;ftdiv=ft0div;ft1div=ftdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
                while ft1div>ft2div
                    t0div=t1div;t1div=t2div;ft1div=ft2div;stepdiv=2*stepdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
                end
            end
            t=[t0div,t2div];fone=ff;xone=a;sone=t;
            if nargin<4,rone=1e-6;end
            aone=sone(1);bone=sone(2);a1one=aone+0.382*(bone-aone);fa1one=subs(fone,{xone},{a1one});a2one=aone+0.618*(bone-aone);fa2one=subs(fone,{xone},{a2one});
            while abs((bone-aone)/bone)>rone && abs((fa2one-fa1one)/fa2one)>rone
              if fa1one<fa2one
                 bone=a2one;a2one=a1one;fa2one=fa1one;a1one=aone+0.382*(bone-aone);fa1one=subs(fone,{xone},{a1one});
              else
                 aone=a1one;a1one=a2one;fa1one=fa2one;a2one=aone+0.618*(bone-aone);fa2one=subs(fone,{xone},{a2one});
              end
            end
            opone=(aone+bone)/2;aa=opone;xx=x0+aa*s(:,i);fx0=subs(f,{x1,x2,x3},{x0(1),x0(2),x0(3)});fxx=subs(f,{x1,x2,x3},{xx(1),xx(2),xx(3)});length=fx0-fxx;
            if length>MaxLength,MaxLength=length;m=m+1;end
            x0=xx;
    end
    ss=x0-x00;ReflectX=2*x0-x00;f1=subs(f,{x1,x2,x3},{x00(1),x00(2),x00(3)});f2=subs(f,{x1,x2,x3},{x0(1),x0(2),x0(3)});f3=subs(f,{x1,x2,x3},{ReflectX(1),ReflectX(2),ReflectX(3)});
    if f3<f1&&(f1+f3-2*f2)*(f1-f2-MaxLength)^2<0.5*MaxLength*(f1-f3)^2
        x=x0+a*ss;ff=subs(f,{x1,x2,x3},{x(1),x(2),x(3)});fdiv=ff;xdiv=a;
        if nargin<4,ndiv=1e-6;end
        if nargin<3,mdiv=0;end
        stepdiv=ndiv;t0div=mdiv;ft0div=subs(fdiv,{xdiv},{t0div});t1div=t0div+stepdiv;ft1div=subs(fdiv,{xdiv},{t1div});
        if ft0div>=ft1div
            t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
            while ft1div>ft2div
                t0div=t1div;t1div=t2div;ft1div=ft2div;stepdiv=2*stepdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
            end
        else 
            stepdiv=-stepdiv;tdiv=t0div;t0div=t1div;t1div=tdiv;ftdiv=ft0div;ft1div=ftdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
            while ft1div>ft2div
                t0div=t1div;t1div=t2div;ft1div=ft2div;stepdiv=2*stepdiv;t2div=t1div+stepdiv;ft2div=subs(fdiv,{xdiv},{t2div});
            end
        end
        t=[t0div,t2div];fone=ff;xone=a;sone=t;
        if nargin<4,rone=1e-6;end
        aone=sone(1);bone=sone(2);a1one=aone+0.382*(bone-aone);fa1one=subs(fone,{xone},{a1one});a2one=aone+0.618*(bone-aone);fa2one=subs(fone,{xone},{a2one});
        while abs((bone-aone)/bone)>rone && abs((fa2one-fa1one)/fa2one)>rone
          if fa1one<fa2one
             bone=a2one;a2one=a1one;fa2one=fa1one;a1one=aone+0.382*(bone-aone);fa1one=subs(fone,{xone},{a1one});
          else
             aone=a1one;a1one=a2one;fa1one=fa2one;a2one=aone+0.618*(bone-aone);fa2one=subs(fone,{xone},{a2one});
          end
        end
        opone=(aone+bone)/2;aa=opone;x0=x0+aa*ss;
        for j=m:(3-1),s(:,j)=s(:,j+1);end
        s(:,3)=ss;
    else
        if f2>f3, x0=ReflectX;end
    end
   if norm(x00-x0)<error,break;end
end
opx=x0;val=subs(f,{x1,x2,x3},{opx(1),opx(2),opx(3)});
disp('most£º');opx'
disp('val£º');val
disp('step£º');k