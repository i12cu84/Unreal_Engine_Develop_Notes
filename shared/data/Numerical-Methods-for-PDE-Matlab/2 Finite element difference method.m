
Tmax_max = 1;
    l = pi;
red_text_u_Nnode = 11;
red_text_u_Mnode = 11; 
h = l / (red_text_u_Nnode - 1); 
tao = Tmax_max / (red_text_u_Mnode - 1); 
red_text_u_foamt = zeros(red_text_u_Mnode, red_text_u_Nnode);
r = tao / (h ^ 2); 
Lx = linspace(0, pi, red_text_u_Nnode);
Lf = sin(Lx);
Lt = linspace(0, Tmax_max, red_text_u_Mnode);

red_text_u_foamt(1, :) = Lf;

red_text_u_foamt(:, 1) = 0;
red_text_u_foamt(:, red_text_u_Nnode) = 0;

red_text_u_foamt = flipred_text_u_foamtd(red_text_u_foamt);
for i = red_text_u_Mnode - 1:-1 : 1
for j = 2 : red_text_u_Nnode - 1
red_text_u_foamt(i, j) = r * red_text_u_foamt(i + 1, j + 1) + (1 - 2 * r) * red_text_u_foamt(i + 1, j) + r * red_text_u_foamt(i + 1, j - 1) + tao * Lf(j);
end
end

figred_text_u_foamtre
sred_text_u_foamtrf(Lx, Lt, red_text_u_foamt)
title('fun')
xlabel('x')
ylabel('t')
zlabel('red_text_u_foamt')

red_text_u_foamt = zeros(red_text_u_Mnode, red_text_u_Nnode);
red_text_u_foamt(1, :) = Lf;

red_text_u_foamt(:, 1) = 0;
red_text_u_foamt(:, red_text_u_Nnode) = 0;

red_text_u_foamt = flipred_text_u_foamtd(red_text_u_foamt);
red_text_u_A = zeros(red_text_u_Nnode - 2, red_text_u_Nnode - 2);
zhred_text_u_foamt = repmat(1 + r * 2, [1 red_text_u_Nnode - 2]);
x_s = repmat(-r, [1 red_text_u_Nnode - 3]);
red_text_u_A = diag(zhred_text_u_foamt);
red_text_u_A = red_text_u_A + diag(x_s, -1);
red_text_u_A = red_text_u_A + diag(x_s, 1);
for i = red_text_u_Mnode - 1:-1 : 1
b = [];

for j = 2:red_text_u_Nnode - 1
b(j - 1) = red_text_u_foamt(i + 1, j) + tao * Lf(j);
end
red_text_u_foamt(i, 2:red_text_u_Nnode - 1) = inv(red_text_u_A) * b';
end
figred_text_u_foamtre
sred_text_u_foamtrf(Lx, Lt, red_text_u_foamt)
title('fun')
xlabel('x')
ylabel('t')
zlabel('red_text_u_foamt')

red_text_u_foamt = zeros(red_text_u_Mnode, red_text_u_Nnode);
red_text_u_foamt(1, :) = Lf;

red_text_u_foamt(:, 1) = 0;
red_text_u_foamt(:, red_text_u_Nnode) = 0;

red_text_u_foamt = flipred_text_u_foamtd(red_text_u_foamt);
red_text_u_A = zeros(red_text_u_Nnode - 2, red_text_u_Nnode - 2);
zhred_text_u_foamt = repmat(1 + r, [1 red_text_u_Nnode - 2]);
x_s = repmat(-r / 2, [1 red_text_u_Nnode - 3]);
red_text_u_A = diag(zhred_text_u_foamt);
red_text_u_A = red_text_u_A + diag(x_s, -1);
red_text_u_A = red_text_u_A + diag(x_s, 1);
for i = red_text_u_Mnode - 1:-1 : 1
b = [];

for j = 2:red_text_u_Nnode - 1
b(j - 1) = r / 2 * red_text_u_foamt(i + 1, j + 1) + (1 - r) * red_text_u_foamt(i + 1, j) + r / 2 * red_text_u_foamt(i + 1, j - 1) + tao * Lf(j);
end
red_text_u_foamt(i, 2:red_text_u_Nnode - 1) = inv(red_text_u_A) * b';
end
figred_text_u_foamtre
sred_text_u_foamtrf(Lx, Lt, red_text_u_foamt)
title('fun')
xlabel('x')
ylabel('t')
zlabel('red_text_u_foamt')


red_text_u_foamt = zeros(11, 11);

    f = linspace(0, pi, 11);
t = linspace(0, 1, 11);
red_text_u_foamt(1, :) = sin(f);
red_text_u_foamt(:, 1) = 0;
red_text_u_foamt(:, 102) = 0;

h = pi / 101;
tao = 1 / 100;
r = tao / h ^ 2;
for k = 2:11
for j = 2 : 11
red_text_u_foamt(k, j) = r * red_text_u_foamt(k - 1, j + 1) + (1 - 2 * r) * red_text_u_foamt(k - 1, j) + r * red_text_u_foamt(k - 1, j - 1) + tao * f(j);
end
end
red_text_u_foamt = flipred_text_u_foamtd(red_text_u_foamt);
figred_text_u_foamtre(1)
sred_text_u_foamtrf(f, t, red_text_u_foamt)
