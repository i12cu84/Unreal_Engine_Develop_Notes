换装系统笔记

GameMode 场景的游戏模式

Actor 放置世界中的物体 不会被操控（比如子弹
Pawn 继承自Actor 多一些功能 有操控 相应外部输入能力 与场景可以交互
Character 人形Pawn

PlayerController 逻辑 控制器（玩家的意愿 游戏逻辑 动的能力）智能决策（动）
Pawn 固有行为逻辑 前进后退 播放动画 碰撞检测 （能）
例如：A、B炮车都是Character PlayerController用于追踪蓝图等 Pawn写入不同的攻击（开炮）方式

capsule collision 胶囊体碰撞盒
skeletal mesh 骨骼网格体
![](../../assets/2022-03-06-14-08-50.png)


Set Master Pose Component 设置总姿势组件
![](../../assets/2022-03-06-14-16-37.png)

CustomEvent....自定义事件

Skeletal Mesh 骨骼网络体

更换传入的mesh
![](../../assets/2022-03-06-15-23-49.png)
![](../../assets/2022-03-06-15-31-58.png)
![](../../assets/2022-03-06-15-32-02.png)
![](../../assets/2022-03-06-15-32-09.png)

Set members in ()名字  设置(名字)中的成员

存储数据蓝图(关卡切换时 保存数据)
![](../../assets/2022-03-06-15-48-15.png)

蓝图类GameInstance(存储数据类)
进入游戏后 该类将会被创建 且只创建一个 不管怎么切换关卡 一直存在的对象

事件图表传入数据
![](../../assets/2022-03-06-15-53-09.png)

定义函数传出数据
![](../../assets/2022-03-06-15-53-22.png)

事件开始运行 强转GameInstance数据
![](../../assets/2022-03-06-15-56-09.png)

NewWidgetBlueprint UI界面定义

create widget 构建None 创建控件
add to viewport 添加到视口
![](../../assets/2022-03-06-16-26-33.png)

set input mode UI only 设置仅输入模式UI（只允许UI输入
show mouse cursor 显示鼠标光标
![](../../assets/2022-03-06-17-15-12.png)
返回Actor
![](../../assets/2022-03-06-17-17-40.png)

![](../../assets/2022-03-06-18-09-24.png)

get owning player 获取拥有的玩家
获取数据
![](../../assets/2022-03-06-18-13-41.png)

Flip Flop A/B间断返回
![](../../assets/2022-03-06-18-29-24.png)

设定枚举值
![](../../assets/2022-03-06-18-33-57.png)

同理设定
![](../../assets/2022-03-06-18-41-30.png)

之前蓝图自定义事件勘误补正
![](../../assets/2022-03-06-18-51-39.png)

compare int 比较当前int
![](../../assets/2022-03-06-19-10-58.png)

切换材质
![](../../assets/2022-03-06-19-14-34.png)

选定启用
![](../../assets/2022-03-06-19-21-34.png)

controller 控制更新外观
![](../../assets/2022-03-06-19-23-50.png)

保存更新内容
![](../../assets/2022-03-06-19-25-08.png)

关卡跳转（？）
![](../../assets/2022-03-06-19-28-27.png)

按钮切换服装的材质
![](../../assets/2022-03-06-19-30-20.png)

开始游戏 更新关卡
![](../../assets/2022-03-06-19-33-08.png)

bug修正后的蓝图
![](../../assets/2022-03-06-21-02-06.png)