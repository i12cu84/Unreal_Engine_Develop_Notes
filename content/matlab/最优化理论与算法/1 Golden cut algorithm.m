%step1
a=1;
b=2;
t=0.001;
lmd=a+0.382*(b-a);
miu=a+0.618*(b-a);
failmd=cos(3*lmd);
faimiu=cos(3*miu);
k=1;

%step2
while(true)
    while(failmd>=faimiu)
        %step3
        if((b-lmd)<=t)
            disp(miu);
            disp(cos(3*miu));
            %down,print(miuk) end
            error('step3 success')
        else
            a=lmd;
            lmd=miu;
            failmd=faimiu;
            miu=a+0.618*(b-a);
            faimiu=cos(3*miu);
            %back step2
        end

    end

    %step4
    if((miu-a)<=t)
        disp(lmd);
        disp(cos(3*lmd));
        %down,print(miuk) end
        error('step4 success')
    else
        b=miu;
        miu=lmd;
        faimiu=failmd;
        lmd=a+0.382*(b-a);
        failmd=cos(3*lmd);
        %go to step2
    end
end