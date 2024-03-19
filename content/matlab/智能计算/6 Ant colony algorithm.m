iter_max=100; 
m=30;       
Alpha=1;       
Beta=5;       
Rho=0.8;        
Q=10;         
Eta=1./D;        
Tau=ones(n,n);   
Tabu=zeros(m,n);  
nC=1;        
R_best=zeros(iter_max,n);
L_best=inf.*ones(iter_max,1);
L_ave=zeros(iter_max,1);     
 
while nC<=iter_max    
    Randpos=[];
    for i=1:(ceil(m/n))     
        Randpos=[Randpos,randperm(n)];
    end
 Tabu(:,1)=(Randpos(1,1:m))'; 
  for j=2:n 
     for  i=1:m
        visited=Tabu(i,1:(j-1)); 
        J=zeros(1,(n-j+1));      
        P=J;                       
        Jc=1;                    
       for k=1:n    
          if  length(find(visited==k))==0
            J(Jc)=k;
            Jc=Jc+1;   
          end
       end
       for k=1:length(J) 
         P(k)=(Tau(visited(end),J(k))^Alpha)*(Eta(visited(end),J(k))^Beta);
       end
         P=P/(sum(P));  
         Pcum=cumsum(P); 
         Select=find(Pcum>=rand); 
       if  isempty(Select) 
         Tabu(i,j)=round(1+(n-1)*rand);
       else
         next_visit=J(Select(1)); 
         Tabu(i,j)=next_visit;   
       end
     end
  end
    if nC>=2;Tabu(1,:)=R_best(nC-1,:);end  
 L=zeros(m,1);
  for i=1:m;
      R=Tabu(i,:);
    for j=1:(n-1)
      L(i)=L(i)+D(R(j),R(j+1));
    end
      L(i)=L(i)+D(R(1),R(n));   
  end
  L_best(nC)=min(L);        
  pos=find(L==L_best(nC));    
  R_best(nC,:)=Tabu(pos(1),:);
  L_ave(nC)=mean(L);        
  nC=nC+1;
   
 Delta_Tau=zeros(n,n);
   for i=1:m
      for j=1:(n-1)    
        Delta_Tau(Tabu(i,j),Tabu(i,j+1))=Delta_Tau(Tabu(i,j),Tabu(i,j+1))+Q/L(i);
      end
        Delta_Tau(Tabu(i,n),Tabu(i,1))=Delta_Tau(Tabu(i,n),Tabu(i,1))+Q/L(i);
   end
Tau=(1-Rho).*Tau+Delta_Tau;  
 
Tabu=zeros(m,n);
end
 
Pos=find(L_best==min(L_best)); 
Shortest_Route=R_best(Pos(1),:)
Shortest_Length=L_best(Pos(1)) 
 
figure(1) 
x=linspace(0,iter_max,iter_max);
y=L_best(:,1);
plot(x,y,'-','LineWidth',2);
xlabel('step'); ylabel('short');
 
figure(2) 
Shortest_Route=[Shortest_Route Shortest_Route(1)];
plot([citys(Shortest_Route,1)],[citys(Shortest_Route,2)],'o-');
grid on
for i = 1:size(citys,1)
    text(citys(i,1),citys(i,2),['   ' num2str(i)]);
end
xlabel('pos x'); 
ylabel('pos y');  

x=0:0.01:4;
y=1-cos(3*x).*exp(-x);
figure
plot(x, y)
hold on
 
function sants = edgeselection(ants, tau, P0, lamda, xl, xu, yl, yu)
sants = ants;
[taubest, ~] = max(tau);
p = abs((taubest - tau) / taubest);
lsindex = find(p < P0);
gsindex = find(p >= P0);

r = rand(length(lsindex), 2);
sants(lsindex, :) = sants(lsindex, :) + (2 .* r - 1) .* lamda;

r = rand(length(gsindex), 2);
gedge = repmat([xu-xl, yu-yl], length(gsindex), 1);
sants(gsindex,:) = sants(gsindex,:) + gedge .* (r - 0.5);

sants(sants(:, 1) < xl, 1) = xl;
sants(sants(:, 1) > xu, 1) = xu;
sants(sants(:, 2) < yl, 2) = yl;
sants(sants(:, 2) > yu, 2) = yu;

objvalue = calObjFun(ants);
sobjvalue = calObjFun(sants);
tindex = find(sobjvalue < objvalue);
sants(tindex, :) = ants(tindex, :);

function objval = calObjFun(X)

objval = 1-cos(3*x(:,1)).*exp(-x(:,2));

function ants = initant(num, xl, xu, yl, yu)

ants = rand(num, 2);
ants(:,1) = xl + (xu - xl) .* ants(:,1);
ants(:,2) = yl + (yu - yl) .* ants(:,2);


%main fun:
clear;
clc;

Ant     =   300;  
Times   =   80;  
Rho     =   0.9;  
P0      =   0.2;  
xl = 0; xu = 4; 
yl = -1; yu = 3;
step = 0.05;

ants = initant(Ant, xl, xu, yl, yu);  
tau = calObjFun(ants);             
firstants = ants;

for t = 1:Times
    ants = edgeselection(ants, P0, tau, 1/t, xl, xu, yl, yu);
    tau = (1 - Rho) .* tau + calObjFun(ants);   
end

figure(1);
plotobjfun(xl, xu, yl, yu, step);
hold on;
plot3(firstants(:,1), firstants(:,2), calObjFun(firstants), 'b*');
hold on;
plot3(ants(:,1), ants(:,2), calObjFun(ants), 'r*');
hold off;
