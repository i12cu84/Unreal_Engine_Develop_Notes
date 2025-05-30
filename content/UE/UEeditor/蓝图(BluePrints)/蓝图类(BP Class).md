<details>
<summary>AIController</summary>
<pre><code>
AI控制蓝图
</code></pre>
</details>




<details>
<summary>ActorComponent</summary>
<pre><code>
Actor组件的模板
(用于Actor蓝图添加组件时使用的通用模板)
</code></pre>
</details>




<details>
<summary>BTTask_BlueprintBase</summary>
<pre><code>
AI行为树创建任务事件的蓝图节点模板
</code></pre>
</details>




<details>
<summary>DefaultPawn</summary>
<pre><code>
默认Pawn
</code></pre>
</details>




<details>
<summary>GameInstance</summary>
<pre><code>
活跃于整个进程的蓝图
更替关卡时,该蓝图的内容不会被清除
</code></pre>
</details>




<details>
<summary>GameMode</summary>
<pre><code>
游戏模式
</code></pre>
</details>




<details>
<summary>GameModeClass</summary>
<pre><code>
游戏模式(用于存储了一组类,包括DefaultPawn/HUD/PlayerController/GameState/PlayerState/Spectator)
</code></pre>
</details>




<details>
<summary>GameStateClass</summary>
<pre><code>
游戏状态,管理了所有已连接的客户端，并且实时追踪游戏层面的属性并把它们分发给远程客户端
</code></pre>
</details>




<details>
<summary>GrippableSkeletalMeshActor</summary>
<pre><code>
</code></pre>
</details>




<details>
<summary>GrippableStaticMeshActor</summary>
<pre><code>
静态网格体蓝图
</code></pre>
</details>




<details>
<summary>HUD</summary>
<pre><code>
平视显示信息:游戏过程中覆盖在屏幕上的状态及信息(类似于只读的窗口UI,用于显示游戏状态,类似于血条等...)

与UI用户界面有区别:菜单和其他的交互性元素
</code></pre>
</details>




<details>
<summary>PlayerController</summary>
<pre><code>
玩家控制中心
</code></pre>
</details>




<details>
<summary>PlayerStateClass</summary>
<pre><code>
记录单个玩家的属性和状态(以玩家为单位)
</code></pre>
</details>




<details>
<summary>PlyaerControllerClass</summary>
<pre><code>
玩家控制中心
</code></pre>
</details>




<details>
<summary>SaveGame</summary>
<pre><code>
保存数据的蓝图(用于数据回归)

Save Game to Slot(以Slot保存数据[二进制])
Load Game from Slot()

保存路径:项目/Saved/SaveGames/[Slot名字].sav

注:经过实测,蓝图中无法保存各类型的引用[指针]对象,只能保存一些常规变量(例:布尔,整数,浮点等)
</code></pre>
</details>




<details>
<summary>SpectatorPawn</summary>
<pre><code>
不带重力漫游的Pawn
</code></pre>
</details>




<details>
<summary>Ue4ASP_Character</summary>
<pre><code>
应该是源于Animation Starter Pack(虚幻商城 -> 动画新手包)的蓝图类

用于设定(敌人)人物蓝图
</code></pre>
</details>




<details>
<summary>UserWidget</summary>
<pre><code>
UMG的基本模板(用户窗口)
</code></pre>
</details>




<details>
<summary>VRCharacter</summary>
<pre><code>
VR人物蓝图
源于OpenXR插件 特定蓝图

组件
Right / Left Mointion Controller 左右遥感感知
VRReplicated Camera 摄像机感知

蓝图
Sphere Trace By Channel     球型检测
区别
Grip Object by Interface    能应用到静态网格体（GrippableStaticMeshActor）的细节面板参数
Grip Object                 不会应用到静态网格体（GrippableStaticMeshActor）的细节面板参数，可以自定义
</code></pre>
</details>




<details>
<summary>VRPlayerController</summary>
<pre><code>
VR输入映射
</code></pre>
</details>




