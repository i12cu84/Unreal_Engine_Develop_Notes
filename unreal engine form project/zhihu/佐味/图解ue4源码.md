
<details>
<summary>【图解UE4源码】其一 UCharacterMovementComponent的移动逻辑</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/368613242
前言
为啥要写这篇文章呢？
其实网上已经有几个大佬贴了详细的源码解说文了，但是大佬终归是大佬吧，经验丰富，代码和逻辑一大坨地就是甩起来。看完之后总感觉似懂非懂，好像自己学到了东西了，其实因为「文章体量太大，信息量过多」，反而容易造成读者最后可能只看懂了文中零零散散的片段，而没法对整个逻辑有个宏观的了解。
看不懂大佬文章，只好自己硬啃咯。
啃完便整理出来了这篇文章。这篇文章力求能够给读者一个宏观上的概念，了解移动逻辑大概是怎样的，而不会过多地设计技术细节，当然读者也不要想着能在这里能够了解到什么技术细节。一来是这一块涉及其他功能太多了，涵盖了RootMotion、动画、物理等等，如果深入研究这文章也就变得太臃肿了（我自己也没时间一次就看这么多逻辑，以后想到再补个大而全的吧）；二来我这次看源码的速度很快，做记录也很快，很多东西没有仔细地经过考证，难免会有些小错误小疏漏，所以千万不要把这篇文章当做教科书去看，权当做一个小菜鸡做的个人笔记去看就好了。希望这篇小文可以对大家入门有帮助，真要抠细节，还得靠自己看源码。
本文纲要
从宏观上讲一下移动逻辑是怎么实现的，只是想看个大概的读者，可以止步于此
稍微详尽地分析移动逻辑的每个步骤是怎么实现的，有兴趣者可以深入看看
角色位移的驱动方式
要让角色动起来，可以有两种驱动方式：
给予一个初速度，让它在加速度和摩擦力的作用下自行改变。例如调用ACharacter::LaunchCharacter()设置一个初速度，来实现角色的跳跃。
使用RootMotion的位移来驱动角色，移动组件会每帧读取动画的RootMotion的位移，把这个位移应用到角色身上
移动组件每帧在做什么——宏观逻辑
移动组件当然每帧是在移动角色了。这部分代码在UCharacterMovementComponent::PerformMovement()中。
这里先放一个图，从宏观上描述每一帧的移动逻辑。
忽略掉其他零碎的逻辑，它的主要逻辑分为三个部分。
第一部分，处理Pending数据。我们在调用LaunchCharacter发射角色的时候，会将初速度写入到字段PendingLaunchVelocity中。在这个部分的逻辑中，如果发现PendingLaunchVelocity存在，会直接将它赋值到当前速度上。（也就是LaunchCharacter设置的速度要下一帧才会生效）。Pending数据处理完后，会被清理掉。
第二部分，获取RootMotion数据。RootMotion数据分为两种，一种是移动组件的字段FRootMotionSourceGroup CurrentRootMotion这个结构体中带的数据，根据知乎大佬的文章这部分是广义的RootMotion数据（非动画携带的RootMotion数据）；第二种是动画携带的RootMotion数据，需要每帧从动画那边获取最新的数据并保存起来。
第三部分自然就是将速度应用起来移动角色了。简单地说，在这里会继续算出一个最终的速度，然后将这个速度乘以时间，得到位移量，然后调用我们熟悉的UMovementComponent::SafeMoveUpdatedComponent()了，它最终更新UpdatedComponent的位置，达到移动角色新的效果。
简而言之虽然代码那么多，做的不外乎就是：获得本帧速度，算得本帧位移，更新角色位移。
觉得满意的读者已经不必继续往下阅读了，大概的思路就这样，后面有空再研究也行，读代码嘛不要给自己太大压力。
移动组件每帧在做什么——稍微详解
接下来会把上面说的三个部分稍微扩展出来讲。
先贴个图吓一下人。
根据上面宏观逻辑，把它分为三部分来看会心理压力小一些。
处理Pending数据
这部分包括四个函数。
ApplyAccumulatedForce
UpdateCharacterStateBeforeMovement 主要是处理下蹲状态
HandlePendingLaunch 这里就是处理LaunchCharacter设置的初速度了。可以看到它是直接把PendingLaunchVelocity赋值给了Velocity，然后直接把角色置为浮空状态(MOVE_Falling)
ClearAccumulatedForces 清除Pending数据
获取RootMotion信息
RootMotion信息可能来自两个地方：
大佬说的广义的RootMotion信息，我也不知道是啥，储存在FRootMotionSourceGroup UCharacterMovementComponent::CurrentRootMotion结构体内。一般不会用到（还是我太菜还不知道怎么用），所以这里直接忽略它
角色动画所带来的RootMotion信息
对于广义的RootMotion信息，就下面这个步骤会用到，我也懒得看，就这样吧。
我们直接讨论动画RootMotion是如何获得的。
在动画有RootMotion的情况下，会执行一个很重要的函数，它就是TickCharacterPose()。
看上图，这个函数其中的关键还是调用了CharacterMesh->TickPose()，也就是USkeletalMeshComponent::TickPose()。这个函数大概会更新当前帧动画的信息，这其中就包括了RootMotion相关的信息。
为了满足部分同学的好奇心（其实是我自己的好奇心），这里把USkeletalMeshComponent::TickPose()做的逻辑简单地贴一下，看下图。
总之呢，最终就是拿了角色动画的UAnimInstance，调用它的UpdateAnimation。
好奇的同学我这里再讲一下。这里面会更新三种AnimInstance，其中只有AnimScriptInstance使我们常用到的那个，可以自己断点一下。
经过UAnimInstance::UpdateAnimation()之后，我们就得到了RootMotion的Transform信息了。（具体是怎么得到的，以后有精力自然会去看，可能会在别的文章写出来了，追更啊同学们）。
回到上上张图，动画更新之后，调用USkeletalMeshComponent::ConsumeRootMotion()来分析动画，得到当前帧动画的RootMotion信息，然后把信息变换和存储到自己的字段UCharacterMovementComponent::RootMotionParams中。
再唠叨一句，CurrentRootMotion是广义RootMotion信息，RootMotionParams是动画RootMotion信息。
应用位移
得到了速度和位移的基础信息之后，接下来就要把这些数据应用起来，让角色产生位移。
首先，假如有RootMotion的话，要先确定RootMotion产生的最终速度。
RootMotion分为我们上面说的两种，一种从CurrentRootMotion中直接获取速度就好，另一种则需要稍微经过计算才能得到最终速度。
计算流程大概是这样：
把位移从动画的LocalSpace转移到世界的WorldSpace
将位移除以时间，得到速度
根据某些条件对速度加以限制
计算得到速度之后，就要产生位移了。
角色位移的关键代码在UCharacterMovementComponent::StartNewPhysics()。它会switch当前的运动状态，并调用对应的PhysXXX()函数。这里我们以走路的PhysWalking()为例。
虽然不是很重要，不过这里要先提一个概念「时间分片」。对于移动模拟来说以一帧为跨度来计算位移，可能会不太精确。假设角色距离墙壁有1m，而当前帧的速度乘以当前帧的deltatime刚好大于等于1m，那么就会出现角色在墙壁面前1m就停下来的奇怪情况。为了能够使移动模拟更加精细，移动组件采用了把一帧的时间分成更细的分片的方案。首先模拟一帧的1/2的时间，然后模拟1/4, 1/8的时间（直到时间片小于某个阈值，就不再分割成更小的时间片了）。在这些小时间片里面做计算，能够提高模拟的精度。
在每个时间片里，要做的事情也简单，就是将速度 * 时间片，得到该时间片内的位移，然后调用SafeMoveUpdatedComponent更新角色的位置。
往细里说（这里逻辑太杂了忍不住还是用了列举法）：
首先因为是Walking模式，所以要保证速度是水平的，把速度的z方向去掉
然后看有没有RootMotion，如果没有动画RootMotion，是需要做特殊处理的。这个特殊处理就是用移动组件配置的加速度和摩擦力对当前的速度做衰减（或者提速）；当然如果有动画RootMotion，那就直接用上面RootMotion算出来的速度
（不重要）把CurrentRootMotion的速度应用出来
位移 = 速度 * 时间，算出Delta位移
如果位移量不是零，就代表着得做位移了，调用UCharacterMovementComponent::MoveAlongFloor()，后者会做一系列的碰撞检测，如果合法，那么最终调用SafeMoveUpdatedComponent()，完成该时间片的位移
不知道大家看懂了没有，反正我是大概懂了。
处理完位移后，当然同理，也得处理角色转向。同样分为两种情况，有RootMotion和没RootMotion的。这不是本文的重点，所以就不展开来讲了。
后记
复习一下，三个步骤：
处理Pending数据
计算RootMotion数据中的速度信息
把速度 * 时间得到位移，应用到角色上
预告一下下一次要写的题：RootMotion的位移信息是怎么被获取到的。
</code></pre>
</details>

<details>
<summary>【图解UE4源码】AI行为树系统 目录</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/368889019
</code></pre>
</details>

<details>
<summary>【图解UE4源码】AI行为树系统 其零 主要类的职能及其关系</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/368889239
</code></pre>
</details>

<details>
<summary>【图解UE4源码】AI行为树系统 其一 行为树节点的单例设计</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/369100301
</code></pre>
</details>

<details>
<summary>【图解UE4源码】AI行为树系统 其二 一棵行为树是怎么被运行起来的</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/370452770
</code></pre>
</details>

<details>
<summary>【图解UE4源码】 其三（〇）行为树系统执行任务的流程 概述</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/371623309
</code></pre>
</details>

<details>
<summary>【图解UE4源码】 其三（一）行为树系统执行任务的流程 发起执行请求</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/372256253
</code></pre>
</details>

<details>
<summary>【图解UE4源码】 其三（二）行为树系统执行任务的流程 处理请求</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/373072168
</code></pre>
</details>

<details>
<summary>【图解UE4源码】 其三（三）行为树系统执行任务的流程 执行待执行节点</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/373310323
</code></pre>
</details>

<details>
<summary> </summary>
<pre><code>

</code></pre>
</details>