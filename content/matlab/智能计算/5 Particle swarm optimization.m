liziqunsuanfa_text_N=6; 
liziqunsuanfa_text_citys=randn(liziqunsuanfa_text_N,2); 
save citys.mat
function change=liziqunsuanfa_text_position_minus_position(liziqunsuanfa_text_best,liziqunsuanfa_text_pop)
for liziqunsuanfa_text_i=1:size(liziqunsuanfa_text_best,1)
    for liziqunsuanfa_text_j=1:size(liziqunsuanfa_text_best,2)
        change(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=find(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,:)==liziqunsuanfa_text_best(liziqunsuanfa_text_i,liziqunsuanfa_text_j));
        temp=liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j);
        liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=liziqunsuanfa_text_pop(liziqunsuanfa_text_i,change(liziqunsuanfa_text_i,liziqunsuanfa_text_j));
        liziqunsuanfa_text_pop(liziqunsuanfa_text_i,change(liziqunsuanfa_text_i,liziqunsuanfa_text_j))=temp;
    end
end
end
 
function liziqunsuanfa_text_change = liziqunsuanfa_text_constant_times_velocity(liziqunsuanfa_text_constant,liziqunsuanfa_text_change)
for liziqunsuanfa_text_i=1:size(liziqunsuanfa_text_change,1)
    for liziqunsuanfa_text_j=1:size(liziqunsuanfa_text_change,2)
        if rand>liziqunsuanfa_text_constant
            liziqunsuanfa_text_change(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=0;
        end
    end
end
end
 
function liziqunsuanfa_text_pop = position_plus_velocity(liziqunsuanfa_text_pop,liziqunsuanfa_text_v)
for liziqunsuanfa_text_i=1:size(liziqunsuanfa_text_pop,1)
    for liziqunsuanfa_text_j=1:size(liziqunsuanfa_text_pop,2)
        if liziqunsuanfa_text_v(liziqunsuanfa_text_i,liziqunsuanfa_text_j)~=0
            liziqunsuanfa_text_temp=liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j);
            liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_v(liziqunsuanfa_text_i,liziqunsuanfa_text_j));
            liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_v(liziqunsuanfa_text_i,liziqunsuanfa_text_j))=liziqunsuanfa_text_temp;
        end
    end
end
end
clear all;
clc;
load citys.mat;
liziqunsuanfa_text_D=[  0,1078,119,263,398,401;
    1078,0,963,989,1096,1381;
    119,963,0,262,426,504;
    263,989,262,0,171,394;
    398,1096,426,171,0,341;
    401,1381,504,394,341,0];
liziqunsuanfa_text_n=6; 
liziqunsuanfa_text_c1=0.1;
liziqunsuanfa_text_c2=0.075; 
liziqunsuanfa_text_w=1; 
liziqunsuanfa_text_m=500; 
liziqunsuanfa_text_pop=zeros(liziqunsuanfa_text_m,liziqunsuanfa_text_n); 
liziqunsuanfa_text_v=zeros(liziqunsuanfa_text_m,liziqunsuanfa_text_n); 
liziqunsuanfa_text_gen=1; 
liziqunsuanfa_text_genmax=2000; 
liziqunsuanfa_text_fitness=zeros(liziqunsuanfa_text_m,1);
liziqunsuanfa_text_Pbest=zeros(liziqunsuanfa_text_m,liziqunsuanfa_text_n); 
liziqunsuanfa_text_Pbest_fitness=zeros(liziqunsuanfa_text_m,1);
liziqunsuanfa_text_Gbest=zeros(liziqunsuanfa_text_genmax,liziqunsuanfa_text_n); 
liziqunsuanfa_text_Gbest_fitness=zeros(liziqunsuanfa_text_genmax,1);
liziqunsuanfa_text_Length_ave=zeros(liziqunsuanfa_text_genmax,1); 
liziqunsuanfa_text_ws=1; 
liziqunsuanfa_text_we=0.8;
for liziqunsuanfa_text_i=1:liziqunsuanfa_text_m
    liziqunsuanfa_text_pop(liziqunsuanfa_text_i,:)=randperm(liziqunsuanfa_text_n);
    liziqunsuanfa_text_v(liziqunsuanfa_text_i,:)=randperm(liziqunsuanfa_text_n);
end
for liziqunsuanfa_text_i=1:liziqunsuanfa_text_m
    for liziqunsuanfa_text_j=1:liziqunsuanfa_text_n-1
        liziqunsuanfa_text_fitness(liziqunsuanfa_text_i)=liziqunsuanfa_text_fitness(liziqunsuanfa_text_i) + liziqunsuanfa_text_D(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j),liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j+1));
    end
    liziqunsuanfa_text_fitness(liziqunsuanfa_text_i)=liziqunsuanfa_text_fitness(liziqunsuanfa_text_i) + liziqunsuanfa_text_D(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,end),liziqunsuanfa_text_pop(liziqunsuanfa_text_i,1));
end
liziqunsuanfa_text_Pbest_fitness=liziqunsuanfa_text_fitness;
liziqunsuanfa_text_Pbest=liziqunsuanfa_text_pop;
[liziqunsuanfa_text_Gbest_fitness(1),liziqunsuanfa_text_min_index]=min(liziqunsuanfa_text_fitness);
liziqunsuanfa_text_Gbest(1,:)=liziqunsuanfa_text_pop(liziqunsuanfa_text_min_index,:);
liziqunsuanfa_text_Length_ave(1)=mean(liziqunsuanfa_text_fitness);
while liziqunsuanfa_text_gen<liziqunsuanfa_text_genmax
    liziqunsuanfa_text_gen=liziqunsuanfa_text_gen+1;
    liziqunsuanfa_text_w = liziqunsuanfa_text_ws - (liziqunsuanfa_text_ws-liziqunsuanfa_text_we)*(liziqunsuanfa_text_gen/liziqunsuanfa_text_genmax)^2;
    liziqunsuanfa_text_change1=liziqunsuanfa_text_position_minus_position(liziqunsuanfa_text_Pbest,liziqunsuanfa_text_pop);
    liziqunsuanfa_text_change1=liziqunsuanfa_text_constant_times_velocity(liziqunsuanfa_text_c1,liziqunsuanfa_text_change1);
    change2=liziqunsuanfa_text_position_minus_position(repmat(liziqunsuanfa_text_Gbest(liziqunsuanfa_text_gen-1,:),liziqunsuanfa_text_m,1),liziqunsuanfa_text_pop);
    change2=liziqunsuanfa_text_constant_times_velocity(liziqunsuanfa_text_c2,change2);
    liziqunsuanfa_text_v=liziqunsuanfa_text_constant_times_velocity(liziqunsuanfa_text_w,liziqunsuanfa_text_v);
    for liziqunsuanfa_text_i=1:liziqunsuanfa_text_m
        for liziqunsuanfa_text_j=1:liziqunsuanfa_text_n
            if liziqunsuanfa_text_change1(liziqunsuanfa_text_i,liziqunsuanfa_text_j)~=0
                liziqunsuanfa_text_v(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=liziqunsuanfa_text_change1(liziqunsuanfa_text_i,liziqunsuanfa_text_j);
            end
            if change2(liziqunsuanfa_text_i,liziqunsuanfa_text_j)~=0
                liziqunsuanfa_text_v(liziqunsuanfa_text_i,liziqunsuanfa_text_j)=change2(liziqunsuanfa_text_i,liziqunsuanfa_text_j);
            end
        end
    end
    liziqunsuanfa_text_pop=position_plus_velocity(liziqunsuanfa_text_pop,liziqunsuanfa_text_v);
    liziqunsuanfa_text_fitness=zeros(liziqunsuanfa_text_m,1);
    for liziqunsuanfa_text_i=1:liziqunsuanfa_text_m
        for liziqunsuanfa_text_j=1:liziqunsuanfa_text_n-1
            liziqunsuanfa_text_fitness(liziqunsuanfa_text_i)=liziqunsuanfa_text_fitness(liziqunsuanfa_text_i) + liziqunsuanfa_text_D(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j),liziqunsuanfa_text_pop(liziqunsuanfa_text_i,liziqunsuanfa_text_j+1));
        end
        liziqunsuanfa_text_fitness(liziqunsuanfa_text_i)=liziqunsuanfa_text_fitness(liziqunsuanfa_text_i) + liziqunsuanfa_text_D(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,end),liziqunsuanfa_text_pop(liziqunsuanfa_text_i,1));
    end
    for liziqunsuanfa_text_i=1:liziqunsuanfa_text_m
        if liziqunsuanfa_text_fitness(liziqunsuanfa_text_i)<liziqunsuanfa_text_Pbest_fitness(liziqunsuanfa_text_i)
            liziqunsuanfa_text_Pbest_fitness(liziqunsuanfa_text_i)=liziqunsuanfa_text_fitness(liziqunsuanfa_text_i);
            liziqunsuanfa_text_Pbest(liziqunsuanfa_text_i,:)=liziqunsuanfa_text_pop(liziqunsuanfa_text_i,:);
        end
    end
    [liziqunsuanfa_text_minvalue,liziqunsuanfa_text_min_index]=min(liziqunsuanfa_text_fitness);
    if liziqunsuanfa_text_minvalue<liziqunsuanfa_text_Gbest_fitness(liziqunsuanfa_text_gen-1)
        liziqunsuanfa_text_Gbest_fitness(liziqunsuanfa_text_gen)=liziqunsuanfa_text_minvalue;
        liziqunsuanfa_text_Gbest(liziqunsuanfa_text_gen,:)=liziqunsuanfa_text_pop(liziqunsuanfa_text_min_index,:);
    else
        liziqunsuanfa_text_Gbest_fitness(liziqunsuanfa_text_gen)=liziqunsuanfa_text_Gbest_fitness(liziqunsuanfa_text_gen-1);
        liziqunsuanfa_text_Gbest(liziqunsuanfa_text_gen,:)=liziqunsuanfa_text_Gbest(liziqunsuanfa_text_gen-1,:);
    end
    liziqunsuanfa_text_Length_ave(liziqunsuanfa_text_gen)=mean(liziqunsuanfa_text_fitness);
end
[liziqunsuanfa_text_Shortest_Length,liziqunsuanfa_text_index] = min(liziqunsuanfa_text_Gbest_fitness);
liziqunsuanfa_text_Shortest_Route = liziqunsuanfa_text_Gbest(liziqunsuanfa_text_index,:);
disp(['short:' num2str(liziqunsuanfa_text_Shortest_Length)]);
disp(['distance:' num2str([liziqunsuanfa_text_Shortest_Route liziqunsuanfa_text_Shortest_Route(1)])]);
figure(1)
plot([liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route,1);liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(1),1)],...
     [liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route,2);liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(1),2)],'o-');
grid on
for liziqunsuanfa_text_i = 1:size(liziqunsuanfa_text_citys,1)
    text(liziqunsuanfa_text_citys(liziqunsuanfa_text_i,1),liziqunsuanfa_text_citys(liziqunsuanfa_text_i,2),['   ' num2str(liziqunsuanfa_text_i)]);
end
text(liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(1),1),liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(1),2),'       起点');
text(liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(end),1),liziqunsuanfa_text_citys(liziqunsuanfa_text_Shortest_Route(end),2),'       终点');
xlabel('pos x')
ylabel('pos y')
title(['distance(output:' num2str(liziqunsuanfa_text_Shortest_Length) ')'])
 
figure(2)
plot(1:liziqunsuanfa_text_genmax,liziqunsuanfa_text_Gbest_fitness,'b',1:liziqunsuanfa_text_genmax,liziqunsuanfa_text_Length_ave,'r:')
legend('short','average')
xlabel('step')
ylabel('distance')
title('compare')
liziqunsuanfa_text_D=[  0 2.2 18.1 4.8 9.2 8.4 5.2 0.4 9.3 11.3 10.2 0.4 10.4;
     2.2 0 17.5 2.8 7.9 6.6 3.3 1.8 8.5 9.8 8.7 2.4 9.6;
    18.1 17.5 0 14.7 9.6 10.9 14.2 18.2 9.1 7.6 8.7 18.3 8.0;
    4.8 2.8 14.7 0 5.4 3.8 0.5 4.4 6.4 7.0 6.0 5.1 7.4;
    9.2 7.9 9.6 5.4 0 2.4 4.9 9.0 1.7 2.3 1.2 9.5 2.2;
    8.4 6.6 10.9 3.8 2.4 0 3.3 8.1 4.1 3.3 2.5 8.7 4.6;
    5.2 3.3 14.2 0.5 4.9 3.3 0 4.8 6.0 6.6 5.5 5.5 6.9;
    0.4 1.8 18.2 4.4 9.0 8.1 4.8 0 9.2 11.1 10.0 0.6 10.3;
    9.3 8.5 9.1 6.4 1.7 4.1 6.0 9.2 0 3.3 2.5 9.6 1.1;
    11.3 9.8 7.6 7.0 2.3 3.3 6.6 11.1 3.3 0 1.2 11.7 2.8;
    10.2 8.7 8.7 6.0 1.2 2.5 5.5 10.0 2.5 1.2 0 10.5 2.5;
    0.4 2.4 18.3 5.1 9.5 8.7 5.5 0.6 9.6 11.7 10.5 0 10.7;
10.4 9.6 8.0 7.4 2.2 4.6 6.9 10.3 1.1 2.8 2.5 10.7 0];
 
clc
clear all
liziqunsuanfa_text_x=0:0.01:4;
liziqunsuanfa_text_y=1-cos(3*liziqunsuanfa_text_x).*exp(-liziqunsuanfa_text_x);
figure
plot(liziqunsuanfa_text_x, liziqunsuanfa_text_y)
hold on 
liziqunsuanfa_text_c1 = 1.49445;
liziqunsuanfa_text_c2 = 1.49445; 
liziqunsuanfa_text_maxgen = 50; 
liziqunsuanfa_text_sizepop = 10; 
liziqunsuanfa_text_Vmax = 0.5; 
liziqunsuanfa_text_Vmin = -0.5;  
liziqunsuanfa_text_popmax = 2; 
liziqunsuanfa_text_popmin = 1;
fun=@(x)1-cos(3*x).*exp(-x);
for liziqunsuanfa_text_i = 1:liziqunsuanfa_text_sizepop
    liziqunsuanfa_text_pop(liziqunsuanfa_text_i,:) = (rands(1) + 1) / 2 + 1;
    liziqunsuanfa_text_V(liziqunsuanfa_text_i,:) = 0.5 * rands(1);
    liziqunsuanfa_text_fitness(liziqunsuanfa_text_i) = fun(liziqunsuanfa_text_pop(liziqunsuanfa_text_i,:));   
end
[liziqunsuanfa_text_bestfitness liziqunsuanfa_text_bestindex] = max(liziqunsuanfa_text_fitness);
liziqunsuanfa_text_zbest = liziqunsuanfa_text_pop(liziqunsuanfa_text_bestindex,:); 
liziqunsuanfa_text_gbest = liziqunsuanfa_text_pop; 
liziqunsuanfa_text_fitnessgbest = liziqunsuanfa_text_fitness;
liziqunsuanfa_text_fitnesszbest = liziqunsuanfa_text_bestfitness;
for liziqunsuanfa_text_i = 1:liziqunsuanfa_text_maxgen 
    for liziqunsuanfa_text_j = 1:liziqunsuanfa_text_sizepop
        liziqunsuanfa_text_V(liziqunsuanfa_text_j,:) = liziqunsuanfa_text_V(liziqunsuanfa_text_j,:) + liziqunsuanfa_text_c1*rand*(liziqunsuanfa_text_gbest(liziqunsuanfa_text_j,:) - liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:)) + liziqunsuanfa_text_c2*rand*(liziqunsuanfa_text_zbest - liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:));
        liziqunsuanfa_text_V(liziqunsuanfa_text_j,find(liziqunsuanfa_text_V(liziqunsuanfa_text_j,:)>liziqunsuanfa_text_Vmax)) = liziqunsuanfa_text_Vmax;
        liziqunsuanfa_text_V(liziqunsuanfa_text_j,find(liziqunsuanfa_text_V(liziqunsuanfa_text_j,:)<liziqunsuanfa_text_Vmin)) = liziqunsuanfa_text_Vmin;
        liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:) = liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:) + liziqunsuanfa_text_V(liziqunsuanfa_text_j,:);
        liziqunsuanfa_text_pop(liziqunsuanfa_text_j,find(liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:)>liziqunsuanfa_text_popmax)) = liziqunsuanfa_text_popmax;
        liziqunsuanfa_text_pop(liziqunsuanfa_text_j,find(liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:)<liziqunsuanfa_text_popmin)) = liziqunsuanfa_text_popmin; 
        liziqunsuanfa_text_fitness(liziqunsuanfa_text_j) = fun(liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:)); 
    end    
    for liziqunsuanfa_text_j = 1:liziqunsuanfa_text_sizepop    
        if liziqunsuanfa_text_fitness(liziqunsuanfa_text_j) > liziqunsuanfa_text_fitnessgbest(liziqunsuanfa_text_j)
            liziqunsuanfa_text_gbest(liziqunsuanfa_text_j,:) = liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:);
            liziqunsuanfa_text_fitnessgbest(liziqunsuanfa_text_j) = liziqunsuanfa_text_fitness(liziqunsuanfa_text_j);
        end        
        if liziqunsuanfa_text_fitness(liziqunsuanfa_text_j) > liziqunsuanfa_text_fitnesszbest
            liziqunsuanfa_text_zbest = liziqunsuanfa_text_pop(liziqunsuanfa_text_j,:);
            liziqunsuanfa_text_fitnesszbest = liziqunsuanfa_text_fitness(liziqunsuanfa_text_j);
        end
    end 
    yy(liziqunsuanfa_text_i) = liziqunsuanfa_text_fitnesszbest;          
end
[liziqunsuanfa_text_fitnesszbest liziqunsuanfa_text_zbest]
plot(liziqunsuanfa_text_zbest, liziqunsuanfa_text_fitnesszbest,'r*') 
figure
plot(yy)
title('output','fontsize',12);
xlabel('step','fontsize',12);ylabel('output','fontsize',12);
 
liziqunsuanfa_text_x=0:0.0001:4;
liziqunsuanfa_text_y=1-cos(3.*liziqunsuanfa_text_x).*exp(-liziqunsuanfa_text_x);
[liziqunsuanfa_text_ymax,liziqunsuanfa_text_xmax]=max(liziqunsuanfa_text_y)


