b = 5;
% r = t/h^2;
r = 0.5;
x = linspace(0,1,51);
h = 1/50;
t1 = r*h^2;
t = 0:t1:0.1;

u = zeros(size(t,2),51);
loc = find(x == 0.5);
u(1,1:loc) = x(1:loc);
u(1,loc+1:end) = (1-x(loc+1:end));
u(:,1) = 0;
u(:,end) = 0;

for i = 1:size(t,2)-1
    for j = 1:49
        u(i+1,j+1) = r*(u(i,j+2)-2*u(i,j+1)+u(i,j)) + u(i,j+1) -...
            t1*(b/2*h)*(u(i,j+2)-u(i,j));
    end
end

u = flipud(u); 
x = linspace(0,1,51);
t = linspace(0,1,size(t,2));
surf(x,t,u);  
xlabel('x');
ylabel('y');
zlabel('u');
