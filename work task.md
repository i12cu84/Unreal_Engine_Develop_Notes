now:
梯子可移动(物理效果)
存档与联机 的冲突问题
耐久度未设定显示随机(单level随机)
菜单中心显示文字
测量->水平->

仅作教学:不需要去选工具->

新游戏->模式->写名字->服装->工具

框架问题:PlayerController是可被替换的
记住PlayerController是可被替换的，不同的关卡里也可能是不一样的。PlayerController也不一定存在，考虑一下如果把马里奥做成联机游戏，那么对方玩家被同步过来的将只有PlayerState，对方玩家的PlayerController只在服务器上存在。所以这个时候，如果你把金币数据放在PlayerController里的话就非常尴尬了。所以为了扩展性来说，还是根据职责分明的原则来正确划分业务逻辑会比较好。在任一刻，Player:PlayerController:PlayerState是1:1:1的关系。但是PlayerController可以有多个备选用来切换，PlayerState也可以相应多个切换。UPlayer的概念会在之后讲解，但目前可以简单理解为游戏里一个全局的玩家逻辑实体，而PlayerController代表的就是玩家的意志，PlayerState代表的是玩家的状态。

will:
粒子特效
骨骼动画/静态网格互相替换(骨骼动画的启动与暂停)
