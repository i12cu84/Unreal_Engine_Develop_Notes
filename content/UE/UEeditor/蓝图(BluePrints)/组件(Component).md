<details>
<summary>Collision</summary>
<pre><code>
碰撞 Collision

Simulation Generates Hit Events -> 发生碰撞时是否发射"命中"事件

Phys Material Override ->

Generate Overlap Events ->

Can Character Step Up On ->


碰撞预设 ->

    Default：默认值

    Custom：自定义

    No Collision：无碰撞
    【自身视为WorldStatic】

    BlockAll：对所有类型的物体进行 区块碰撞
    【自身视为WorldStatic】

    OverlapAll：对所有类型的物体进行 重叠
    【自身视为WorldStatic】

    BlockAllDynamic：对所有类型的物体进行 区块碰撞
    【自身视为WorldDynamic】

    OverAllDynamic：对所有类型的物体进行 重叠
    【自身视为WorldDynamic】

    IgnoreOnlyPawn：对碰撞类型为（除了Pawn，Vehicle（载具）） 的物体进行 区块碰撞
    （Pawn，Vehicle（载具）进行忽视处理 ）
    【自身视为WorldDynamic】

    OverlapOnlyPawn：对碰撞类型为（除了Pawn，Vehicle） 的物体进行 区块碰撞
    （忽略Pawn，Vehicle（载具））
    （Camera进行忽视处理）
    【自身视为WorldDynamic】

    Pawn：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为Pawn】

    Spectator：对所有碰撞类型为 “WorldStatic” 的物体进行 区块碰撞
    （忽略其余的碰撞类型）
    【自身视为Pawn】

    CharacterMesh：对碰撞类型为（除了Pawn，Vehicle（载具）） 的物体进行 区块碰撞
    （忽略Pawn，Vehicle（载具））
    【自身视为Pawn】

    PhysicalBody：对所有碰撞类型的物体进行 区块碰撞
    【自身视为PhysicalBody】

    Destructible（可破坏物）：对所有碰撞类型的物体进行 区块碰撞
    【自身视为Destructible】

    InvisibleWall：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldStatic】

    InvisibleWallDynamic：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldDynamic】

    Trigger（触发器）：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldDynamic】

    Ragdoll（模拟骨架网格体组件）：对碰撞类型为（除了Pawn） 的物体进行 区块碰撞
    （忽略物体的可见性）
    （忽略Pawn）
    【自身视为PhysicalBody】

    Vehicle：对所有碰撞类型的物体进行 区块碰撞
    【自身视为Vehicle】
</code></pre>
</details>




<details>
<summary>Particle System</summary>
<pre><code>
粒子效果(Set Active[激活])
</code></pre>
</details>




<details>
<summary>PawnSensing</summary>
<pre><code>
AI的感知组件(听/看),视野角度等
</code></pre>
</details>




<details>
<summary>Physics</summary>
<pre><code>
物理 Physics

Simulate Physics -> 是否启用物理模拟

Mass -> 质量

Linear Damping -> 线速度运动拖拽力

Angular Damping -> 角速度运动拖拽力

Enable Gravity -> 启用重力


约束 ->

Ignore Radial Impulse ->

Ignore Radial Force ->

Apply Impulse on Damage ->

Replicate Physics to Autonomous Pro... ->

Async Physics Tick Enabled ->


高级 ->
</code></pre>
</details>




<details>
<summary>Spline</summary>
<pre><code>
样条插值线条

注:使用完后,记得使用Clear Spline Points节点(否则会内存泄漏,已实测)
</code></pre>
</details>




<details>
<summary>StaticMesh</summary>
<pre><code>
静态网格体
</code></pre>
</details>




<details>
<summary>WeidgetInteraction</summary>
<pre><code>
设定模型射线用于与(Widget组件)蓝图进行交互
细节设置->调试->Show Debug(可以展示射线用于检测交互UI)
</code></pre>
</details>




<details>
<summary>Widget</summary>
<pre><code>
设定3D窗口(用于进行3D交互)
</code></pre>
</details>




