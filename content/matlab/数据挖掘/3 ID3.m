clc;
clear all;
close all;
%input
data = [0,2,0,0,0;
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

%tree
make_tree(data);
function  make_tree(train_data)
 
[m,n] = size(train_data);
disp('original data');
disp(train_data);
class_list = train_data(:,n);
class_first = 1;
 
for i = 2:m
   if train_data(i,n) ==  class_list(1,:)
%    if strcmp(train_data(i,n),class_list(1,:))
        class_first = class_first + 1;
    end
end

if class_first == m || n == 1
    disp('final data');
    disp(train_data);
    return;
end

bestfeat = choose_bestfeat(train_data);
 
disp(['bestfeature:',num2str(bestfeat)]);
 
featvalue = unique(train_data(:,bestfeat));
 
featvalue_num = length(featvalue);
 
for i = 1:featvalue_num
    make_tree(splitData(train_data,bestfeat,featvalue(i,:)));
    disp('--------------------------------------------');
end
end

%splitData.m
function [subSet] = splitData(data, j, value)
subSet = data;
subSet(:,j) = [];
k = 0;
for i = 1:size(data,1)
    if data(i,j) ~= value
        subSet(i-k,:) =[];
        k = k + 1;
    end
end

%calc_entropy.m
function [entropy] = calc_entropy(train_data)
 
[m,n] = size(train_data);
 
label_value = train_data(:,n);
label = unique(label_value);
label_number = zeros(length(label),2);
label_number(:,1) = label';
for i = 1:length(label)
    label_number(i,2) = sum(label_value == label(i));
end
 
label_number (:,2) = label_number(:,2) ./ m;
entropy = 0;
entropy = sum(-label_number(:,2).*log2 (label_number(:,2)));
end

%choose_bestfeat.m
function [best_feature] = choose_bestfeat(data)
 
[m,n] = size(data);
feature_num = n - 1;
baseentropy = calc_entropy(data);
 
best_gain = 0;
best_feature = 0;
 
for j =1:feature_num
    feature_temp = unique(data(:,j));
    num_f = length(feature_temp);
    new_entropy = 0;
    for i = 1:num_f
        subSet = splitData(data, j, feature_temp(i,:));
        [m_s,n_s] = size(subSet);
        prob = m_s./m;
        new_entropy = new_entropy + prob * calc_entropy(subSet);
    end
    inf_gain = baseentropy - new_entropy;
    if inf_gain > best_gain
        best_gain = inf_gain;
        best_feature = j;
    end
end
End
