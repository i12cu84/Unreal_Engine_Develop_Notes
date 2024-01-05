
clear all;
clc;
two_dimensional_adi_t = 1; 
two_dimensional_adi_x = 1;two_dimensional_adi_y = 1;
two_dimensional_adi_m = 1000;      
two_dimensional_adi_n = 10;       
two_dimensional_adi_k = 10;        
two_dimensional_adi_ht = two_dimensional_adi_t/(two_dimensional_adi_m-1);   
two_dimensional_adi_hx = two_dimensional_adi_x/(two_dimensional_adi_n-1);
two_dimensional_adi_hy = two_dimensional_adi_y/(two_dimensional_adi_k-1);   
two_dimensional_adi_f=[];
two_dimensional_adi_N = two_dimensional_adi_n;
two_dimensional_adi_x = linspace(0,1,two_dimensional_adi_N);
two_dimensional_adi_y = linspace(0,1,two_dimensional_adi_N);
for i = 1:two_dimensional_adi_N
    for j = 1:two_dimensional_adi_N
        two_dimensional_adi_f(i,j) = two_dimensional_adi_x(i)*two_dimensional_adi_x(j);
    end
end
two_dimensional_adi_u = zeros(two_dimensional_adi_m,two_dimensional_adi_n,two_dimensional_adi_k);
[two_dimensional_adi_x,two_dimensional_adi_y] = meshgrid(0:two_dimensional_adi_hx:1,0:two_dimensional_adi_hy:1);
two_dimensional_adi_u(1,:,:) = two_dimensional_adi_f;
two_dimensional_adi_r = two_dimensional_adi_ht/(2*two_dimensional_adi_hx^2);
two_dimensional_adi_dia = repmat(1+2*two_dimensional_adi_r,[1,two_dimensional_adi_n-2]);
two_dimensional_adi_dia1 = repmat(two_dimensional_adi_r,[1,two_dimensional_adi_n-3]);
two_dimensional_adi_A = diag(two_dimensional_adi_dia,0);
two_dimensional_adi_A = two_dimensional_adi_A + diag(two_dimensional_adi_dia1,-1);
two_dimensional_adi_A = two_dimensional_adi_A + diag(two_dimensional_adi_dia1,1);
for ii=1:two_dimensional_adi_m-1
    for kk=2:two_dimensional_adi_k-1
        two_dimensional_adi_b=[];
        for i = 1:two_dimensional_adi_n-2
            j=i+1;
            two_dimensional_adi_b(i) = two_dimensional_adi_u(ii,j,kk) + two_dimensional_adi_r*(two_dimensional_adi_u(ii,j,kk+1)+two_dimensional_adi_u(ii,j,kk-1)-...
                2*two_dimensional_adi_u(ii,j,kk));
        end
        two_dimensional_adi_b(1) = two_dimensional_adi_b(1) + two_dimensional_adi_r*two_dimensional_adi_u(ii,1,kk);
        two_dimensional_adi_b(two_dimensional_adi_n-2) = two_dimensional_adi_b(two_dimensional_adi_n-2) + two_dimensional_adi_r*two_dimensional_adi_u(ii,two_dimensional_adi_n,kk);
        temp = inv(two_dimensional_adi_A)*two_dimensional_adi_b';
        two_dimensional_adi_b2=[];
        for i = 1:two_dimensional_adi_n-2
            j=i;
            if j == 1
                two_dimensional_adi_b2(i) = temp(j) + two_dimensional_adi_r*(temp(j+1)+0-2*temp(j));
            elseif j==two_dimensional_adi_n-2
                two_dimensional_adi_b2(i) = temp(j) + two_dimensional_adi_r*(temp(j-1)+0-2*temp(j));
            else
                two_dimensional_adi_b2(i) = temp(j) + two_dimensional_adi_r*(temp(j+1)+temp(j-1)-2*temp(j));
            end
        end
        two_dimensional_adi_temp2 = inv(two_dimensional_adi_A)*two_dimensional_adi_b2';
        for i = 2:two_dimensional_adi_n-1
            j = i-1;
            two_dimensional_adi_u(ii+1,i,kk) = two_dimensional_adi_temp2(j);
        end
    end
end
for i=1:two_dimensional_adi_m
    figure(1);
    mesh(two_dimensional_adi_x,two_dimensional_adi_y,reshape(two_dimensional_adi_u(i,:,:),[two_dimensional_adi_n two_dimensional_adi_k]));
    axis([0 1 0 1 -2 2]);
end
