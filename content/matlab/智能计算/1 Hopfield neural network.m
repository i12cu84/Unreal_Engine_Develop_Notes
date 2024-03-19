Clc;
clear; 
desktop_text_CN=10;
[desktop_text_dislist,Clist]=tsp(desktop_text_CN);
 
desktop_text_A=500;desktop_text_B=500;
desktop_text_C=200;desktop_text_D=500;
desktop_text_F=1;desktop_text_m=0.02;
desktop_text_la=0.00001;desktop_text_EN=1000;
 desktop_text_y=zeros(desktop_text_CN,desktop_text_CN);
for desktop_text_i=1:desktop_text_CN
    desktop_text_y(desktop_text_i,desktop_text_i)=1;
end
desktop_text_z=-desktop_text_m/2*log(9)*ones(desktop_text_CN,desktop_text_CN);
delu=0.1*desktop_text_m*rand(desktop_text_CN,desktop_text_CN);
 figure(1);
for k=1:desktop_text_EN
    desktop_text_z=desktop_text_z+desktop_text_la*delu;
    for desktop_text_u=1:desktop_text_CN
        for desktop_text_i=1:desktop_text_CN
            desktop_text_y(desktop_text_u,desktop_text_i)=1/(1+exp(-2*desktop_text_z(desktop_text_u,desktop_text_i)/desktop_text_m));
        end
    end
    for desktop_text_u=1:desktop_text_CN
        for desktop_text_i=1:desktop_text_CN
            desktop_text_A1=0;
            desktop_text_B1=0;
            for desktop_text_aa=1:desktop_text_CN
                desktop_text_A1=desktop_text_A1+desktop_text_y(desktop_text_u,desktop_text_aa);
                desktop_text_B1=desktop_text_B1+desktop_text_y(desktop_text_aa,desktop_text_i);
            end
            desktop_text_A1=desktop_text_A1-desktop_text_y(desktop_text_u,desktop_text_i);
            desktop_text_B1=desktop_text_B1-desktop_text_y(desktop_text_u,desktop_text_i);
            desktop_text_C1=0;
            for desktop_text_aa=1:desktop_text_CN
                for bb=1:desktop_text_CN
                    desktop_text_C1=desktop_text_C1+desktop_text_y(desktop_text_aa,bb);
                end
            end
            desktop_text_C1=desktop_text_C1-desktop_text_CN;
            desktop_text_D1=0;
            for desktop_text_x=1:desktop_text_CN
                if desktop_text_x~=desktop_text_u
                    if desktop_text_i==1
                        desktop_text_D1=desktop_text_D1+desktop_text_dislist(desktop_text_u,desktop_text_x)*(desktop_text_y(desktop_text_x,2)+desktop_text_y(desktop_text_x,desktop_text_CN));
                    elseif desktop_text_i==desktop_text_CN
                        desktop_text_D1=desktop_text_D1+desktop_text_dislist(desktop_text_u,desktop_text_x)*(desktop_text_y(desktop_text_x,1)+desktop_text_y(desktop_text_x,desktop_text_CN-1));
                    else
                        desktop_text_D1=desktop_text_D1+desktop_text_dislist(desktop_text_u,desktop_text_x)*(desktop_text_y(desktop_text_x,desktop_text_i+1)+desktop_text_y(desktop_text_x,desktop_text_i-1));
                    end
                end
            end
            delu(desktop_text_u,desktop_text_i)=-desktop_text_z(desktop_text_u,desktop_text_i)*desktop_text_F-desktop_text_A*desktop_text_A1-desktop_text_B*desktop_text_B1-desktop_text_C*desktop_text_C1-desktop_text_D*desktop_text_D1;
        end
    end
end
function [desktop_text_DLn,desktop_text_cityn]=tsp(desktop_text_n)
 if desktop_text_n==10
    desktop_text_city10=[0.4 0.4439;0.2439 0.1463;0.1707 0.2293;0.2293 0.761;0.5171 0.9414;
        0.8732 0.6536;0.6878 0.5219;0.8488 0.3609;0.6683 0.2536;0.6195 0.2634];
    for desktop_text_i=1:10
        for desktop_text_j=1:10
            DL10(desktop_text_i,desktop_text_j)=((desktop_text_city10(desktop_text_i,1)-desktop_text_city10(desktop_text_j,1))^2+(desktop_text_city10(desktop_text_i,2)-desktop_text_city10(desktop_text_j,2))^2)^0.5;
        end
    end
    desktop_text_DLn=DL10;
    desktop_text_cityn=desktop_text_city10;
end 
if desktop_text_n==30
    desktop_text_city30=[41 94;37 84;54 67;25 62;7 64;2 99;68 58;71 44;54 62;83 69;64 60;18 54;22 60;
        83 46;91 38;25 38;24 42;58 69;71 71;74 78;87 76;18 40;13 40;82 7;62 32;58 35;45 21;41 26;44 35;4 50];
    for desktop_text_i=1:30
        for desktop_text_j=1:30
            desktop_text_DL30(desktop_text_i,desktop_text_j)=((desktop_text_city30(desktop_text_i,1)-desktop_text_city30(desktop_text_j,1))^2+(desktop_text_city30(desktop_text_i,2)-desktop_text_city30(desktop_text_j,2))^2)^0.5;
        end
    end
    desktop_text_DLn=desktop_text_DL30;
    desktop_text_cityn=desktop_text_city30;
end
if desktop_text_n==50
    desktop_text_city50=[31 32;32 39;40 30;37 69;27 68;37 52;38 46;31 62;30 48;21 47;25 55;16 57;
        17 63;42 41;17 33;25 32;5 64;8 52;12 42;7 38;5 25; 10 77;45 35;42 57;32 22;
        27 23;56 37;52 41;49 49;58 48;57 58;39 10;46 10;59 15;51 21;48 28;52 33;
        58 27;61 33;62 63;20 26;5 6;13 13;21 10;30 15;36 16;62 42;63 69;52 64;43 67];
    for desktop_text_i=1:50
        for desktop_text_j=1:50
            desktop_text_DL50(desktop_text_i,desktop_text_j)=((desktop_text_city50(desktop_text_i,1)-desktop_text_city50(desktop_text_j,1))^2+(desktop_text_city50(desktop_text_i,2)-desktop_text_city50(desktop_text_j,2))^2)^0.5;
        end
    end
    desktop_text_DLn=desktop_text_DL50;
    desktop_text_cityn=desktop_text_city50;
end
 
if desktop_text_n==75
    city75=[48 21;52 26;55 50;50 50;41 46;51 42;55 45;38 33;33 34;45 35;40 37;50 30;
        55 34;54 38;26 13;15 5;21 48;29 39;33 44;15 19;16 19;12 17;50 40;22 53;21 36;
        20 30;26 29;40 20;36 26;62 48;67 41;62 35;65 27;62 24;55 20;35 51;30 50;
        45 42;21 45;36 6;6 25;11 28;26 59;30 60;22 22;27 24;30 20;35 16;54 10;50 15;
        44 13;35 60;40 60;40 66;31 76;47 66;50 70;57 72;55 65;2 38;7 43;9 56;15 56;
        10 70;17 64;55 57;62 57;70 64;64 4;59 5;50 4;60 15;66 14;66 8;43 26];
    for desktop_text_i=1:75
        for desktop_text_j=1:75
            DL75(desktop_text_i,desktop_text_j)=((city75(desktop_text_i,1)-city75(desktop_text_j,1))^2+(city75(desktop_text_i,2)-city75(desktop_text_j,2))^2)^0.5;
        end
clear
clc
desktop_text_array_one=[-1 -1 -1 -1 1 1 -1 -1 -1 -1;-1 -1 -1 -1 1 1 -1 -1 -1 -1;
    -1 -1 -1 -1 1 1 -1 -1 -1 -1;-1 -1 -1 -1 1 1 -1 -1 -1 -1;
    -1 -1 -1 -1 1 1 -1 -1 -1 -1;-1 -1 -1 -1 1 1 -1 -1 -1 -1;
    -1 -1 -1 -1 1 1 -1 -1 -1 -1;-1 -1 -1 -1 1 1 -1 -1 -1 -1;
    -1 -1 -1 -1 1 1 -1 -1 -1 -1;-1 -1 -1 -1 1 1 -1 -1 -1 -1];
desktop_text_array_two=[-1 1 1 1 1 1 1 1 1 -1;-1 1 1 1 1 1 1 1 1 -1;
    -1 -1 -1 -1 -1 -1 -1 1 1 -1;-1 -1 -1 -1 -1 -1 -1 1 1 -1;
    -1 1 1 1 1 1 1 1 1 -1;-1 1 1 1 1 1 1 1 1 -1;
    -1 1 1 -1 -1 -1 -1 -1 -1 -1;-1 1 1 -1 -1 -1 -1 -1 -1 -1;
    -1 1 1 1 1 1 1 1 1 -1;-1 1 1 1 1 1 1 1 1 -1];
T=[desktop_text_array_one;desktop_text_array_two]';
net=newhop(T); 
noisy_array_one = desktop_text_array_one;
noisy_array_two = desktop_text_array_two;
for desktop_text_i=1:100
    desktop_text_a=rand;
    if (desktop_text_a<0.1)
    noisy_array_one(desktop_text_i)=-desktop_text_array_one(desktop_text_i);
    noisy_array_two(desktop_text_i)=-desktop_text_array_two(desktop_text_i);
    end
end 
desktop_text_noisy_one={(noisy_array_one)'};
desktop_text_identify_one=sim(net,{10,10},{},desktop_text_noisy_one);
desktop_text_identify_one{10}';
desktop_text_noisy_two={(noisy_array_two)'};
desktop_text_identify_two=sim(net,{10,10},{},desktop_text_noisy_two);
desktop_text_identify_two{10}';

desktop_text_Array_one=imresize(array_one,20);
subplot(3,2,1)
imshow(desktop_text_Array_one)
title('standard(num1)')
desktop_text_Array_two=imresize(array_two,20);
subplot(3,2,2)
imshow(desktop_text_Array_two)
title('standard(num2)')
subplot(3,2,3)
desktop_text_Noisy_array_one=imresize(noisy_array_one,20);
imshow(desktop_text_Noisy_array_one)
title('noise(num1)')
subplot(3,2,4)
desktop_text_Noisy_array_two=imresize(noisy_array_two,20);
imshow(desktop_text_Noisy_array_two)
title('noise(num2)')
subplot(3,2,5)
imshow(imresize(desktop_text_identify_one{10}',20))
title('recognition(num1)')
subplot(3,2,6)
imshow(imresize(desktop_text_identify_two{10}',20))
title('recognition(num2)')
