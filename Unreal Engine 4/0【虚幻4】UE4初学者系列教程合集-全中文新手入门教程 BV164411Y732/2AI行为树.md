P54-P58

导航网络

导航网格体

体积->导航网格边界体积 (绿色区域 AI移动范围) 快捷键P 显示消失的替换

静态 预先设定 和动态 实时计算 

工具栏->设置->项目设置->导航网格体->运行时->运行时生成->静态/动态修改

蓝图实现AI随即移动

对人物蓝图类 ctrl+w复制一个用以AI的BP

打开AIBP蓝图类 删去摄像机和所有节点

AI随机移动的功能 AI move to节点

    pawn让谁移动 移动的对象self

    destination 对象移动的目标(向量) 进行跟踪移动？

    target actor 朝着对象移动(和上面二选一)

    acceptance radius 半径为？的范围内停止

    stop on overlap 靠近范围是否停下

    成功时 

    失败时

get random 获取导航网格半径内的随机点 的节点

范围内随机浮点 (min,max)

AI行为树实现随机和跟随移动

创建->人工智能->黑板+行为树

创建->蓝图->搜索AI control 

AI行为树 写AI的行为逻辑

    根 出发点
        selector 选择 是/否
        sequence 序列 依次进行下去 一些序列多个选择
            blackboard based condition 黑板中的变量调用过来进行判断 右边选择变量(...)
            both(优先级同级)

黑板 存储变量的地方 AI行为树内的数据

    新建bool 是否看到玩家
    新建vector 位置坐标 要去的地方
AI 执行者

    AI行动的模型蓝图

AI control 控制器

    左上角组件 AI感知组件 用于感知周边的东西 右边AI感知 AI视力配置(看到玩家 然后的决策)
        scene 视线半径 视力或者听力之后操作 ... 视野角度...等等
        目标感知更新时(事件)
            中断AI simulus