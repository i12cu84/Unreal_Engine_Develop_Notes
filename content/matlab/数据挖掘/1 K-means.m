s = rng(5,'v5normal');
mu = round((rand(3,2)-0.5)*19)+1;
sigma = round(rand(3,2)*40)/10+1;
X = [mvnrnd(mu(1,:),sigma(1,:),200); ...
     mvnrnd(mu(2,:),sigma(2,:),300); ...
     mvnrnd(mu(3,:),sigma(3,:),400)];

P1 = figure;clf;
scatter(X(:,1),X(:,2),10,'ro');
title('output')    

[cidx2,cmeans2,sumd2,D2] = kmeans(X,2,'dist','sqEuclidean');
P2 = figure;clf;
[silh2,h2] = silhouette(X,cidx2,'sqeuclidean');    

[cidx3,cmeans3,sumd3,D3] = kmeans(X,3,'dist','sqEuclidean');
P4 = figure;clf;
[silh3,h3] = silhouette(X,cidx3,'sqeuclidean');  
