global Dis zq_num Pjc Pby
Dis = xlsread('/Users/Chru/Desktop/distance.xlsx',1);
number1_tsp_city_num = size(Dis,1);
zq_num = 40;
number1_tsp_zq = zeros(zq_num,number1_tsp_city_num);
for number1_tsp_i = 1:zq_num
    randperm(6);
    number1_tsp_zq(number1_tsp_i,:) = randperm(6);
end
number1_tsp_tr_max = 500;
Pjc = 0.9;
Pby = 0.02;
number1_tsp_td = 1;
number1_tsp_suzq = [];
number1_tsp_beiwang_D=[];
number1_tsp_beiwang_Z = [];
while (number1_tsp_td <= number1_tsp_tr_max)
    number1_tsp_dis = countdis(number1_tsp_zq);
    number1_tsp_index1 = lunpan(number1_tsp_dis);
    for number1_tsp_i = 1:zq_num
        if number1_tsp_index1(number1_tsp_i) ~= 0
            for j = 1:number1_tsp_index1(number1_tsp_i)
                number1_tsp_suzq = [number1_tsp_suzq;number1_tsp_zq(number1_tsp_i,:)];
            end
        end
    end
    number1_tsp_suzq = jiaocha(number1_tsp_suzq);
    number1_tsp_zq = number1_tsp_suzq;
    number1_tsp_suzq = [];
    number1_tsp_beiwang_D = [number1_tsp_beiwang_D mean(number1_tsp_dis)];
    number1_tsp_beiwang_Z = [number1_tsp_beiwang_Z min(number1_tsp_dis)];
    number1_tsp_td = number1_tsp_td + 1;
end
plot(1:1:number1_tsp_tr_max,number1_tsp_beiwang_D);
hold on 
plot(1:1:number1_tsp_tr_max,number1_tsp_beiwang_Z);
legend('平均解','最优解')
 

function number1_prop_pro = prop(number1_prop_dis)
number1_prop_a = length(number1_prop_dis);
number1_prop_M = max(number1_prop_dis);
number1_prop_pro = [];
for number1_prop_i = 1:number1_prop_a
    number1_prop_pro(number1_prop_i) = -(number1_prop_dis(number1_prop_i) - number1_prop_M) + 1e-3;
end
 
 
 

function number1_lunpan_Index = lunpan(number1_lunpan_dis)
global zq_num
number1_lunpan_F = 1./(number1_lunpan_dis.^10);
number1_lunpan_P   = number1_lunpan_F./sum(number1_lunpan_F);
number1_lunpan_Q = cumsum(number1_lunpan_P);
number1_lunpan_Index = zeros(length(number1_lunpan_F),1);
for number1_lunpan_j = 1:zq_num
    number1_lunpan_r = rand;
    number1_lunpan_temp = find(number1_lunpan_r <= number1_lunpan_Q);
    number1_lunpan_Index(number1_lunpan_temp(1)) = number1_lunpan_Index(number1_lunpan_temp(1)) + 1;
end
number1_lunpan_Index;
 
 
 

function number1_jiaocha_ans = jiaocha(number1_jiaocha_q)
global zq_num Pjc
number1_jiaocha_temp = randperm(zq_num);
number1_jiaocha_zh = zeros(zq_num/2,2);
for number1_jiaocha_i = 1:zq_num/2
    number1_jiaocha_zh(number1_jiaocha_i,1) = number1_jiaocha_temp(2*number1_jiaocha_i-1);
    number1_jiaocha_zh(number1_jiaocha_i,2) = number1_jiaocha_temp(2*number1_jiaocha_i);
end
number1_jiaocha_ra = 4;
for number1_jiaocha_i = 1:zq_num/2
    if rand(1) < Pjc 
        number1_jiaocha_t1 = number1_jiaocha_q(number1_jiaocha_zh(number1_jiaocha_i,1),:);
        number1_jiaocha_t2 = number1_jiaocha_q(number1_jiaocha_zh(number1_jiaocha_i,2),:);
        number1_jiaocha_x1 = number1_jiaocha_t1;
        number1_jiaocha_x2 = number1_jiaocha_t2;
        number1_jiaocha_temp = randperm(6);
        number1_jiaocha_x2(number1_jiaocha_temp(1:number1_jiaocha_ra)) = number1_jiaocha_t1(number1_jiaocha_temp(1:number1_jiaocha_ra));
        number1_jiaocha_t = 1;
        for number1_jiaocha_i = 1:length(number1_jiaocha_temp)
            if double(ismember(number1_jiaocha_t1(number1_jiaocha_temp(1:number1_jiaocha_ra)),number1_jiaocha_t2(number1_jiaocha_i))) == 0 & number1_jiaocha_t<=3
                number1_jiaocha_x2(number1_jiaocha_temp(number1_jiaocha_ra+number1_jiaocha_t)) = number1_jiaocha_t2(number1_jiaocha_i);
                number1_jiaocha_t = number1_jiaocha_t+1;
            end
        end
        number1_jiaocha_x1(number1_jiaocha_temp(1:number1_jiaocha_ra)) = number1_jiaocha_t2(number1_jiaocha_temp(1:number1_jiaocha_ra));
        number1_jiaocha_t=1;
        for number1_jiaocha_i = 1:length(number1_jiaocha_temp)
            if double(ismember(number1_jiaocha_t2(number1_jiaocha_temp(1:number1_jiaocha_ra)),number1_jiaocha_t1(number1_jiaocha_i))) == 0 & number1_jiaocha_t<=3
                number1_jiaocha_x1(number1_jiaocha_temp(number1_jiaocha_ra+number1_jiaocha_t)) = number1_jiaocha_t1(number1_jiaocha_i);
                number1_jiaocha_t = number1_jiaocha_t+1;
            end
        end
        if countdis(number1_jiaocha_t1) >= number1_jiaocha_x1
            number1_jiaocha_q(number1_jiaocha_zh(number1_jiaocha_i,1),:) = number1_jiaocha_x1;
        end
        if countdis(number1_jiaocha_t2) >= number1_jiaocha_x2
            number1_jiaocha_q(number1_jiaocha_zh(number1_jiaocha_i,2),:) = number1_jiaocha_x2;
        end
    end
end
number1_jiaocha_ans = number1_jiaocha_q;       
       

function number1_countdis_dis = countdis(number1_countdis_q)
global Dis
number1_countdis_dis = [];
[number1_countdis_a number1_countdis_b] = size(number1_countdis_q);
for number1_countdis_i = 1:number1_countdis_a
    number1_countdis_sum = 0;
    for number1_countdis_j = 1:number1_countdis_b
        number1_countdis_temp1 = number1_countdis_q(number1_countdis_i,number1_countdis_j);
        if number1_countdis_j == number1_countdis_b
            temp2 = number1_countdis_q(number1_countdis_i,1);
        else
            temp2 = number1_countdis_q(number1_countdis_i,number1_countdis_j+1);
        end
        number1_countdis_sum = number1_countdis_sum + Dis(number1_countdis_temp1,temp2);
    end
    number1_countdis_dis(number1_countdis_i) = number1_countdis_sum;
end


function number_bianyi_ans = bianyi(number_bianyi_q)
global Pby
[number_bianyi_a number_bianyi_b] = size(number_bianyi_q);
number_bianyi_num = round(number_bianyi_a*number_bianyi_b*Pby);
for number_bianyi_i = 1:number_bianyi_a
    if rand(1)<Pby
        number_bianyi_temp = randperm(6);
        number_bianyi_yuan = number_bianyi_q(number_bianyi_i,number_bianyi_temp(1:number_bianyi_num));
        number_bianyi_hou = fliplr(number_bianyi_yuan);
        number_bianyi_q(number_bianyi_i,number_bianyi_temp(1:number_bianyi_num))=number_bianyi_hou;
    end
end
number_bianyi_ans = number_bianyi_q;
