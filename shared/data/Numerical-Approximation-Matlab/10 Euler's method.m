clear;
a = 0;b = 1;h = 0.2;d = 1;
n = (b-a)/h;x0 = a;x1 = a;y0 = d;
result(1,1) = x0;
result(2,1) = y0;
for m = 0:n-1
    x1 = x1 + h;
    f0 = y0-2*x0/y0;
    d = y0 + h*f0;
    f1 = d - 2*x1/d;
    y1 = y0 + h/2*(f0+f1);
    x0 = x1;y0 = y1;
    result(1, m+2) = x0;
    result(2, m+2) = y0;
end
x = result(1,:);
y = result(2,:);
z = [1,  1.1832, 1.3416, 1.4832,  1.6125, 1.7321];
y(2,:) = z;
subplot(2,2,1)
plot(x, y);


clear;
a = 0;b = 1;h = 0.1;d = 1;
n = (b-a)/h;x0 = a;x1 = a;y0 = d;
result(1,1) = x0;
result(2,1) = y0;
for m = 0:n-1
    x1 = x1 + h;
    f0 = y0-2*x0/y0;
    d = y0 + h*f0;
    f1 = d - 2*x1/d;
    y1 = y0 + h/2*(f0+f1);
    x0 = x1;y0 = y1;
    result(1, m+2) = x0;
    result(2, m+2) = y0;
end
x = result(1,:);
y = result(2,:);
z = [1, 1.0954, 1.1832, 1.2649, 1.3416, 1.4142, 1.4832, 1.5492, 1.6125, 1.6733, 1.7321];
y(2,:) = z;
subplot(2,2,2)
plot(x, y);


clear;
a = 0;b = 1;h = 0.5;d = 1;
n = (b-a)/h;x0 = a;x1 = a;y0 = d;
result(1,1) = x0;
result(2,1) = y0;
for m = 0:n-1
    x1 = x1 + h;
    f0 = y0-2*x0/y0;
    d = y0 + h*f0;
    f1 = d - 2*x1/d;
    y1 = y0 + h/2*(f0+f1);
    x0 = x1;y0 = y1;
    result(1, m+2) = x0;
    result(2, m+2) = y0;
end
x = result(1,:);
y = result(2,:);
z = [1, 1.4142, 1.7321];
y(2,:) = z;
subplot(2,2,3)
plot(x, y);

clear;
a = 0;b = 1;h = 0.1;d = 1;
n = (b-a)/h;x0 = a;x1 = a;y0 = d;
result(1,1) = x0;
result(2,1) = y0;
for m = 0:n-1
    x1 = x1 + h;
    f0 = y0-2*x0/y0;
    d = y0 + h*f0;
    f1 = d - 2*x1/d;
    y1 = y0 + h/2*(f0+f1);
    x0 = x1;y0 = y1;
    result(1, m+2) = x0;
    result(2, m+2) = y0;
end
x = result(1,:);
y = result(2,:);
z = [1, 1.09, 1.18, 1.26, 1.34, 1.41, 1.48, 1.54, 1.61, 1.67, 1.73];
y(2,:) = z;
subplot(2,2,4)
plot(x, y);
