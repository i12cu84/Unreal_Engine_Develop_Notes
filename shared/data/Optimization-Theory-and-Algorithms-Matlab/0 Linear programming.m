[x,fval]=linprog([-3;1;1],[1 -2 1;4 -1 -2],[11 -3],[2 0 -1],-1,[0 0 0])
% x =
%     4.0000
%     1.0000
%     9.0000
% fval =
%    -2.0000
% max value 2

[x,fval]=linprog([-2;-4],[2 2;1 2],[12 8],[],[],[0 0],[4 3])
% x =
%      4
%      2
% fval =
%    -16
% max value 16

[x,fval]=linprog([-2;-3],[4 0],16,[],[],[0 0],[])
% x =
%      []
% fval =
%      []
% Problem is unbounded.

[x,fval]=linprog([-2;-3],[2 2;-1 -2],[6 -7],[],[],[0,0],[])
% x =
%      []
% fval =
%      []
% Linprog stopped because no point satisfies the constraints.

[x,favl]=linprog([6;3;4],[],[],[1 1 1],[120],[30 0 20],[Inf 50 Inf])
% x =
%     30
%     50
%     40
% favl =
%    490
% max or min 490

[x,fval]=linprog([13;9;10;11;12;8],[0.4 1.1 1 0 0 0 ;0 0 0 0.5 1.2 1.3],[800;900],[1 0 0 1 0 0 ;0 1 0 0 1 0;0 0 1 0 0 1],[400;600;500],zeros(1,6),[])
% x =
%          0
%   600.0000
%          0
%   400.0000
%          0
%   500.0000
% fval =
%        13800
% out 13800  