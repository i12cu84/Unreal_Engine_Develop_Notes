function number2_bianyi_ans = bianyi(number2_bianyi_q)
global Pby
[number2_bianyi_a number2_bianyi_b] = size(number2_bianyi_q);
number2_bianyi_num = round(number2_bianyi_a*number2_bianyi_b*Pby);
for number2_bianyi_i = 1:number2_bianyi_a
    if rand(1)<Pby
        number2_bianyi_temp = randperm(number2_bianyi_b);
        number2_bianyi_yuan = number2_bianyi_q(number2_bianyi_i,number2_bianyi_temp(1:number2_bianyi_num));
        number2_bianyi_hou = fliplr(number2_bianyi_yuan);
        number2_bianyi_q(number2_bianyi_i,number2_bianyi_temp(1:number2_bianyi_num))=number2_bianyi_hou;
    end
end
number2_bianyi_ans = number2_bianyi_q;
        

function number2_bianyi_ans = jiaocha(number2_bianyi_q)
global zq_num Pjc
number2_bianyi_t = randperm(zq_num);
number2_bianyi_zh = zeros(zq_num/2,2);
for number2_bianyi_i = 1:zq_num/2
    number2_bianyi_zh(number2_bianyi_i,1) = number2_bianyi_t(2*number2_bianyi_i-1);
    number2_bianyi_zh(number2_bianyi_i,2) = number2_bianyi_t(2*number2_bianyi_i);
end
number2_bianyi_ra = 12;
for number2_bianyi_i = 1:zq_num/2
    if rand(1) < Pjc 
        number2_bianyi_t1 = number2_bianyi_q(number2_bianyi_zh(number2_bianyi_i,1),:);
        number2_bianyi_t2 = number2_bianyi_q(number2_bianyi_zh(number2_bianyi_i,2),:);
        number2_bianyi_x1 = number2_bianyi_t1;
        number2_bianyi_x2 = number2_bianyi_t2;
        number2_bianyi_t = randperm(13);
        number2_bianyi_t = 1;
        for j = 1:length(number2_bianyi_t)
            if double(ismember(number2_bianyi_x2(number2_bianyi_t(1:number2_bianyi_ra)),number2_bianyi_t1(j))) == 0 & number2_bianyi_t<=13-number2_bianyi_ra
                number2_bianyi_x2(number2_bianyi_t(number2_bianyi_ra+number2_bianyi_t)) = number2_bianyi_t1(j);
                number2_bianyi_t = number2_bianyi_t+1;
            end
        end
        number2_bianyi_t=1;
        for j = 1:length(number2_bianyi_t)
            if double(ismember(number2_bianyi_x1(number2_bianyi_t(1:number2_bianyi_ra)),number2_bianyi_t2(j))) == 0 & number2_bianyi_t<=13-number2_bianyi_ra
                number2_bianyi_x1(number2_bianyi_t(number2_bianyi_ra+number2_bianyi_t)) = number2_bianyi_t2(j);
                number2_bianyi_t = number2_bianyi_t+1;
            end
        end
        if countdis(number2_bianyi_t1) >= countdis(number2_bianyi_x1)
            number2_bianyi_q(number2_bianyi_zh(number2_bianyi_i,1),:) = number2_bianyi_x1;
        end
        if countdis(number2_bianyi_t2) >= countdis(number2_bianyi_x2)
            number2_bianyi_q(number2_bianyi_zh(number2_bianyi_i,2),:) = number2_bianyi_x2;
        end
    end
end
number2_bianyi_ans = number2_bianyi_q;  
