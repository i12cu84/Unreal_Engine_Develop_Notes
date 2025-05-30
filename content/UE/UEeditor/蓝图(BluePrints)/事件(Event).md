<details>
<summary>Actor Begin Overlap</summary>
<pre><code>
Actor碰撞事件(返回Other Actor对象 即碰撞到的对象)
</code></pre>
</details>




<details>
<summary>AnyDamage</summary>
<pre><code>
Actor对象受到任意伤害后触发该事件(即其他蓝图中触发了该Actor的Damage节点)
</code></pre>
</details>




<details>
<summary>Costom Event</summary>
<pre><code>
自定义事件
</code></pre>
</details>




<details>
<summary>EnhancedInputAction [InputAction(输入操作文件名)]</summary>
<pre><code>
Triggered 按下(不松开)后,会持续使出(tick级别)
Started 按下后马上触发一次
Ongoing 按下并长按触发器操作(IA文件中设置触发器长按),按下后会持续响应
Canceled 按下并且长按但时间不足未触发Ongoing操作(IA文件中设置触发器长按),输出一次
Completed 从"已触发"到"无"后,触发一次(类似长按后松开触发)
Action Value 输出值(这与IA文件设置的参量有关)
Elapsed Seconds 经过几秒
Triggerd Seconds 触发几秒
Input Action IA对象

[详情内容见](../输入(Inputs)/输入映射情境.md)
</code></pre>
</details>




<details>
<summary>Event ActorBeginCursorOver</summary>
<pre><code>
鼠标悬停在此Actor上时调用的事件
</code></pre>
</details>




<details>
<summary>Event ActorEndCursorOver</summary>
<pre><code>
鼠标从此Actor上移开时调用的事件
</code></pre>
</details>




<details>
<summary>Event BeginPlay</summary>
<pre><code>
蓝图加载开始时调用一次
</code></pre>
</details>




<details>
<summary>Event Construct</summary>
<pre><code>
UI控件事件蓝图,只有游戏运行时才会调用
</code></pre>
</details>




<details>
<summary>Event Destruct</summary>
<pre><code>
发生摧毁事件
</code></pre>
</details>




<details>
<summary>Event Hit</summary>
<pre><code>
碰撞触发事件(碰撞双方都会触发调用)
</code></pre>
</details>




<details>
<summary>Event Pre Construct</summary>
<pre><code>
UI控件事件蓝图,调试时即调用
</code></pre>
</details>




<details>
<summary>Event TIck</summary>
<pre><code>
蓝图存在时,每帧调用一次
</code></pre>
</details>




<details>
<summary>On Clicked</summary>
<pre><code>
窗口被点击事件
</code></pre>
</details>




<details>
<summary>On Head Noise</summary>
<pre><code>
PawnSensing组件事件,AI对象听到声音触发

Location (声源位置)
</code></pre>
</details>




<details>
<summary>On Component Hit</summary>
<pre><code>
物理命中事件
</code></pre>
</details>




<details>
<summary>On Component Begin Overlap</summary>
<pre><code>
物理重叠事件
</code></pre>
</details>




<details>
<summary>On Component End Overlap</summary>
<pre><code>
物理重叠结束事件
</code></pre>
</details>




<details>
<summary>On Component Wake</summary>
<pre><code>
唤醒底层物理事件
</code></pre>
</details>




<details>
<summary>On Component Sleep</summary>
<pre><code>
休眠底层物理事件
</code></pre>
</details>




<details>
<summary>On Component Physics State Changed</summary>
<pre><code>
修改组件的物理效果后触发事件
</code></pre>
</details>




<details>
<summary>On Hovered</summary>
<pre><code>
窗口悬停事件
</code></pre>
</details>




<details>
<summary>On Pressed</summary>
<pre><code>
窗口被按下事件
</code></pre>
</details>




<details>
<summary>On Released</summary>
<pre><code>
窗口被点击后松开事件
</code></pre>
</details>




<details>
<summary>On See Pawn</summary>
<pre><code>
PawnSensing组件事件,AI对象看到Pawn触发

返回的Pawn即看到的对象
</code></pre>
</details>




<details>
<summary>On Unhovered</summary>
<pre><code>
窗口悬停后离开事件
</code></pre>
</details>




<details>
<summary>Receive Abort</summary>
<pre><code>
AI的行为树中Tasks->Reset Player节点可展开Receive Abort事件用于放弃行为任务
Finish Abort即完成(退出该行为蓝图)
</code></pre>
</details>




<details>
<summary>Receive Execute</summary>
<pre><code>
AI的行为树中Tasks->Reset Player节点可展开Receive Execute事件用于新建行为任务
Finish Execute即完成(退出该行为蓝图)
</code></pre>
</details>




<details>
<summary>Touch [Num]</summary>
<pre><code>
num同时触摸事件触发
</code></pre>
</details>




<details>
<summary>Touch</summary>
<pre><code>
显示为InputTouch 
触摸屏事件,可以获取坐标
</code></pre>
</details>




