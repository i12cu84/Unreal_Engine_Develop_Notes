%XOR operation
x = [0 0 1 1;0 1 0 1];
d = [0,1,1,0];
net = newff(minmax(x),[3,1],{'tansig','purelin'},'traingd');
net.trainParam.epochs = 5000;
net.trainParam.goal = 1e-5;
Lp.lr = 0.1;
net.trainParam.show = 20;
net = train(net,x,d);
out = sim(net,x);
lwsy1 = net.IW{1};
lwsy2 = net.LW{2};
yz = net.b;

%Approximating nonlinear functions
mapminmax_text_p=linspace(0,2*pi,1000);
mapminmax_text_t=cos(mapminmax_text_p+6)+7;
plot(mapminmax_text_p,mapminmax_text_t,'-')
hold on
[mapminmax_text_p1,mapminmax_text_ps] = mapminmax(mapminmax_text_p);
[mapminmax_text_t1,mapminmax_text_ts] = mapminmax(mapminmax_text_t);
mapminmax_text_dex = [];
mapminmax_text_test_index = [];
for i = 1:1000
    if rand(1)<0.95
        mapminmax_text_dex = [mapminmax_text_dex i]
    end
end
mapminmax_text_temp = 1:1:1000
for i = 1:1000
    if ismember(mapminmax_text_temp(i),mapminmax_text_dex) ~= 1
        mapminmax_text_test_index = [mapminmax_text_test_index i]
    end
end
mapminmax_text_in = mapminmax_text_p1(mapminmax_text_dex)
mapminmax_text_st = mapminmax_text_p1(mapminmax_text_test_index)
mapminmax_text_ttrain = mapminmax_text_t1(mapminmax_text_dex)
ttest = mapminmax_text_t1(mapminmax_text_test_index)
net = newff(minmax(mapminmax_text_p1),[3,3,3,1],{'tansig','tansig','tansig','purelin'},'trainlm');
net.trainParam.epochs = 2000
net.trainParam.goal = 1e-5
Lp.lr = 0.1
net.trainParam.show=25
[net,tr]=train(net,mapminmax_text_in,mapminmax_text_ttrain)
mapminmax_text_out=sim(net,mapminmax_text_in)
mapminmax_text_test=sim(net,mapminmax_text_st)
mapminmax_text_rain_=mapminmax('reverse',mapminmax_text_out,mapminmax_text_ts)
mapminmax_text_st_=mapminmax('reverse',mapminmax_text_test,mapminmax_text_ts)
mapminmax_text_y = [mapminmax_text_rain_,mapminmax_text_outtest_]
mapminmax_text_y = zeros(1,1000)
mapminmax_text_y(mapminmax_text_dex) = mapminmax_text_rain_
mapminmax_text_y(mapminmax_text_test_index) = mapminmax_text_outtest_
plot(mapminmax_text_p,mapminmax_text_y,'g-')
mapminmax_text_1 = norm(mapminmax_text_rain_-mapminmax_text_t(mapminmax_text_dex),2)
mapminmax_text_2 = norm(mapminmax_text_outtest_-mapminmax_text_t(mapminmax_text_test_index),2)
