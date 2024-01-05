syms x;y=x^7;a=0;b=1;n=5;
y1=(1/2)*(b-a)*(subs(y,'x',a)+subs(y,'x',b))
y2=(1/3)*((b-a)/2)*(subs(y,'x',a)+4*subs(y,'x',(a+b)/2)+subs(y,'x',b))
y3=((b-a)/n)*((subs(y,'x',a)+subs(y,'x',b))*(1/2));
for m=1:n-1
    y3=y3+((b-a)/n)*subs(y,'x',a+m*((b-a)*(1/2)));
end
disp(y3)
y4=(1/3)*((b-a)/n)*(subs(y,'x',a)+subs(y,'x',b));
for m=1:n-1
   if mod(m,2)
       y4=y4+(1/3)*((b-a)/n)*4*subs(y,'x',a+m*(b-a)/n);
   else
       y4=y4+(1/3)*((b-a)/n)*2*subs(y,'x',a+m*(b-a)/n);
   end
end
disp(y4)
