clc;
clear all;

naive_bayes_classifier_input = [   0,2,0,0,0;
                %0,2,0,1,0;
                0,2,0,1,0;
                1,2,0,0,1;
                2,1,0,0,1;
                2,0,1,0,1;
                2,0,1,1,0;
                1,0,1,1,1;
                0,1,0,0,0;
                0,0,1,0,1;
                2,1,1,0,1;
                0,1,1,1,1;
                1,1,0,1,1;
                1,2,1,0,1;
                2,1,0,1,0];
%sunuy    0,overcast  1,rain  2
%cool       0,midd      1,hot    2
%high      0,nomal     1
%week     0,strong    1
%no         0,yes          1
 
[l,w]=size(naive_bayes_classifier_input);
naive_bayes_classifier_count = zeros(2,w);

for i=1:1:l
    for j=1:1:w
        if naive_bayes_classifier_input(i,j)==1 && naive_bayes_classifier_input(i,end)==1
            naive_bayes_classifier_count(1,j)=naive_bayes_classifier_count(1,j)+1;
        elseif naive_bayes_classifier_input(i,j)==1 && naive_bayes_classifier_input(i,end)==0
            naive_bayes_classifier_count(2,j)=naive_bayes_classifier_count(2,j)+1;
        end
    end
end
naive_bayes_classifier_count(2,end)=l-naive_bayes_classifier_count(1,end);
naive_bayes_classifier_testdata = [0,2,0,1,0];
%X={Outlook=Sunny，Temperature=Hot，Humidity=High，Wind=Strong}
naive_bayes_classifier_answer = [0,0];
 
naive_bayes_classifier_temp = 1;
for i=1:1:w-1
    if naive_bayes_classifier_testdata(i)==1
        naive_bayes_classifier_temp=naive_bayes_classifier_temp*naive_bayes_classifier_count(1,i)/naive_bayes_classifier_count(1,end);
    else
        naive_bayes_classifier_temp=naive_bayes_classifier_temp*(1-naive_bayes_classifier_count(1,i)/naive_bayes_classifier_count(1,end));
    end
end
naive_bayes_classifier_answer(1)=naive_bayes_classifier_count(1,end)/l*naive_bayes_classifier_temp;
 
naive_bayes_classifier_temp = 1;
for i=1:1:w-1
    if naive_bayes_classifier_testdata(i)==1
        naive_bayes_classifier_temp=naive_bayes_classifier_temp*naive_bayes_classifier_count(2,i)/naive_bayes_classifier_count(2,end);
    else
        naive_bayes_classifier_temp=naive_bayes_classifier_temp*(1-naive_bayes_classifier_count(2,i)/naive_bayes_classifier_count(2,end));
    end
end
naive_bayes_classifier_answer(2)=naive_bayes_classifier_count(2,end)/l*naive_bayes_classifier_temp;
naive_bayes_classifier_answer
if naive_bayes_classifier_answer(1)>naive_bayes_classifier_answer(2)
    disp("do")
else
    disp("no")
end

