%init.m
function [L A]=init(D,min_sup)   
[m n]=size(D); 
A=eye(m,n);  
B=(sum(D))';  
i=1;  
while(i<=m)  
    if B(i)<min_sup  
        B(i)=[];  
        A(i,:)=[];  
        m=m-1;  
    else  
        i=i+1;  
    end  
end  
L=[A B];  

%apriori_gen.m 
function [C]=apriori_gen(A,k) 
[m n]=size(A);  
C=zeros(0,n); 
for i=1:1:m  
    for j=i+1:1:m  
        flag=1;  
        for t=1:1:k-1  
            if ~(A(i,t)==A(j,t))  
                flag=0;  
                break;  
            end  
        end  
        if flag==0 break;  
        end  
        c=A(i,:)|A(j,:);  
        flag=isExit(c,A);
        if(flag==1)C=[C;c];  
        end  
    end  
end  

%isExit.m
function flag=isExit(c,A)
[m n]=size(A);  
b=c;  
for i=1:1:n  
    c=b;  
    if c(i)==0 continue  
    end  
    c(i)=0;  
    flag=0;  
    for j=1:1:m  
        A(j,:);  
        a=sum(xor(c,A(j,:)));
        if a==0   
            flag=1;  
            break;  
        end  
    end  
    if flag==0 return   
    end  
end  

%get_k_itemset.m
function [L C]=get_k_itemset(D,C,min_sup)
m=size(C,1);  
M=zeros(m,1);  
t=size(D,1);  
i=1;  
while i<=m  
    C(i,:);  
    H=ones(t,1);  
    ind=find(C(i,:)==1); 
    n=size(ind,2);  
    for j=1:1:n  
        D(:,ind(j));  
        H=H&D(:,ind(j));  
    end  
        x=sum(H');  
        if x<min_sup  
            C(i,:)=[];  
            M(i)=[];  
            m=m-1;  
        else  
            M(i)=x;  
            i=i+1;  
        end  
end  
L=[C M];  

%apriori.m
function [L]=apriori(D,min_sup)  
[L A]=init(D,min_sup)
k=1;  
C=apriori_gen(A,k) 
while ~(size(C,1)==0)  
[M C]=get_k_itemset(D,C,min_sup)
if ~(size(M,1)==0)L=[L;M]     
end  
k=k+1;  
C=apriori_gen(C,k)
end  



