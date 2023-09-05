
<details>
<summary>游戏开发入门总结</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34114662
第一篇文章本来想直接写UE4专栏的，但是最近工作太忙，就先简单对游戏开发入门做个总结吧~

进入游戏行业两年多了，处于一边实践一边学习的状态，一开始身边没有牛人引导感觉确实浪费了一些时间。偶然在Gad上看到一个游戏开发入门系列的视频，觉得内容挺全面的，就定了一个月的计划把这些课程都看完了，收获不小，对游戏开发有了更为全面的认识。

如果你想进入游戏行业，觉得学习资料太多很难入门，那不妨先看看这个系列的视频。我对每个课程都做了笔记，如果课程中遇到了什么问题，随时可以向我提问。（也许你更倾向于问知乎上的各类大神~）

链接：

游戏开发入门系列（目录） - Jerish的博客 - CSDN博客
​blog.csdn.net/u012999985/article/details/79118198
看完这些，你应该对游戏开发有一个大致的了解（配合游戏引擎架构这本书效果更佳），算是踏入游戏行业一半了。然后，参考一下Milo大神给出的游戏开发必备的学习书单 ，按照你想深入的方向开始潜心修炼吧!

在这篇文章里，我试着概括性的对游戏开发做一个总结，希望让大家对游戏开发能有一个基本的认识，也欢迎各位提出意见和建议~

游戏开发基本功：

数学基础：根据你所做内容来决定，一般上层逻辑比较少的去考虑到积分等高数内容。但是如果想搞图形学，矩阵线性代数，高数必须要有一定的功底
算法：常见的排序，查找需要理解并掌握，进一步常见的还有分治，贪心，动态规划，有时候现学现卖也是可以的。另外，除了这些基本的算法，在游戏领域还是有很多其他领域不太常用的算法，比如八叉树查找，碰撞检测，A*。还有一些很特殊的情况需要开发者自己去寻找合适的算法。
C++（C#）：基本语法，代理，命名空间，const，继承，内存结构，虚表，引用，断言，宏定义等
数据结构：首先是掌握链表，数组，队列，堆，栈，图，树等数据结构，然后是各种排序，查找，遍历等算法。这些掌握了以后可以很快的熟悉stl或者类似的基本库原，用的时候可以更准确的选择合适的数据结构
设计模式：一般来说，我们需要设计模式来快速的搭建游戏逻辑框架，比如前面提到的各种逻辑系统。而且还需要通过设计模式来理解引擎各个模块的设计思路。当然，如果你想设计游戏引擎，那更不能少了设计模式了。
对引擎各个模块由一定深入的理解：这个不用多说，看一遍游戏引擎架构吧，不理解写出的代码经常会出现各种问题（比如同步问题），编辑器各种功能也用不好。
内存管理：可能很多引擎或者语言已经尽可能的帮你处理内存了，但是你难免需要在一些特殊情况下自己处理，内存池技术，各种C++的new的使用，不得不会。
对开发工具的熟悉：这里并不是指只是对某一个引擎使用熟练，而且对不同引擎相关的内容都有一定理解，可以很快的触类旁通。
编译原理，链接，第三方库：经常会遇到各种链接错误，编译错误，打包错误，这需要你有一定的相关知识与经验去解决这些问题。
性能分析与性能优化： 主要就是三个方面——内存，CPU，GPU。着手点有渲染批次，渲染实例化，布料优化，网络同步数据量，物理开销等，加载资源优化（包的合并），裁剪，声音文件加载，LOD，美术资源制作规范化等。调试的时候可以使用引擎内置工具，进一步的细节可以采用Intel的VTune工具（有时间我可能写一个相关的使用文档）
对游戏的理解：虽然不玩游戏也一样能参与游戏开发，但玩过游戏的人还是有优势的。最明显的是玩过游戏的人会对游戏有更多的想法与意见，也习惯去主动学习其他的游戏的技术与优点。（程序这样，策划更是如此）
开发经验：这个就比较宽泛了，难以只言片语说清。比如你的游戏莫名其妙的出现了一些bug，新手完全无从下手，而有经验的人会有各种手段去调试并解决。经验丰富的老手有时真的抵得上N个新手的，所以这需要各位不断的学习与实践了。


游戏模块总结：

游戏逻辑模块系统：游戏玩法核心，包括各种武器，状态，技能，背包，战斗等逻辑系统
动画模块系统：状态机，Montage，动画融合，IK等
物理模块：给需要交互表现的对象赋予物理特性（包括刚体，流体，粒子，布料等），调整重力大小等各种参数，调整交互中力的大小，调整物理约束
AI模块： AI导航，与玩家交互等，玩家的很多功能系统也需要给AI来使用，更深层次的可以考虑将机器学习相关的内容融入
UI模块：搭建各种界面框架（背包，捏脸，地图等），非常耗时间与精力，后期需要不断调整
渲染模块：客户端表现核心，不用多说，内容非常多且深
网络模块：底层架构，同步，网络连接
场景模块：包括地形，关卡，植被，角色管理与优化等
输入与输入处理模块：将玩家输入处理转换成逻辑，需要注意的有组合键，输入法切换等
游戏登录与更新：一般这是专门的工具组来做，比如我们常见的各种游戏登录器，在线更新等。
这里面的除了网络基本上都需要美术，策划，程序共同参与与合作。

技术点：

存储与序列化（protobuf）
单机玩家的游戏存档如何实现？通过序列化 socket 搭建基本的TCP/UDP通信系统
反外挂
保证游戏公平性，一般服务器上做各种校验措施，这个东西真的很难，而且又麻烦，很希望有高人指点一二，身边懂得人真的不多
多线程
一般用于渲染，物理，网络同步等，减少开销，增加cpu利用率
打包流水线，包的大小优化，包的多层递归引用优化等
数据库
什么数据要存在数据库里面，什么存在本地就可以。应该选择什么数据库？之后会不会出现游戏合服数据库合并？合并的Key怎么处理？
CDN /服务器的部署与运行等
这个也很复杂，又要考虑成本又想容纳更多玩家（网游），有时可能需要用到CDN技术来优化网络同步，另外还要考虑成本等问题来决定是否租用云服务器
网络穿透
对于玩家自己开房间类的游戏，需要我们提供网络穿透的手段，才能让两个内网的玩家链接并通信。有的时候，网络穿透技术平台会提供，不需要自己造轮子。
其他：

版本控制
一般使用git或者svn
性能分析工具
前面提到了性能优化，优化前我们需要各种工具来辅助我们找到影响游戏效率的瓶颈（如VTune）
配置
需要大量策划配置的数据存放在哪里？配置文件？XML？这需要构建一套小的系统（或者引擎提供）
声音数据处理
一般引擎提供基本的音乐与音效处理，但是有的引擎对音频方面处理的更深入，效果更好
平台对接
游戏需要发布到不同的平台，这个平台不仅仅指硬件平台(Android,iOS,PS4,PC,XBOX)还包括各种软件平台(各种应用商店，如PC上的Steam,WeGame。安卓上的应用宝，各种软件管家等)该过程其实也相当繁琐，有一些平台的审核非常严格，需要积累一定的经验才能快速的处理相关内容
国际化与本地化
简单来说，就是不同国家的语言版本不同。如果你的游戏不是只卖给英国美国，你就不得不面对本地化，坑很多
日志系统
开发与运营 游戏上线一定很多bug，你又没办法去玩家电脑上调试，如何快速定位bug，日志系统很有效
调试与维护
开发期 断点调试（最有效）、日志调试、dump调试 、控制台调试，可视化调试（在场景内绘制特定的几何体），截图录屏调试（一般用于调试渲染，动画等）
上线期 日志调试、服务器可以用dump调试，也可以想办法把客户端的dump传送到服务器（做一个内置的自动收集客户端dump程序） 、管理员GM调试（非常重要，可以避免重启服务器）
bug处理
严重损失的bug：有时候已经发生的造成玩家严重损失的bug（如玩家投入大量时间、金钱获取的）无法改变，又不能及时修复，想要弥补玩家，可以通过GM来给予玩家补偿。
游戏崩溃性bug：需要在游戏上线的前两天，把发生概率高的所有Bug通过Dump调试后尽快修复并更新
脚本
简单逻辑代码，热更新
工具开发
针对特殊需求开发特定的工具来提高程序、美术、策划的开发效率
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》开篇</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34256771
前言
接触虚幻4两年左右，基本上完整地参与了一个虚幻游戏项目的开发。从一开始的各种跳坑，到慢慢熟悉引擎多个模块，解决问题，确实收获很多。开这个专栏的目的就是希望把自己工作与学习中相关积累做一个系统的整理，一来加深自己的理解，二来分享给大家，互相学习与进步。



这个专栏不讲什么？
这里不会讲解引擎的入门操作，因为虚幻4的官方文档以及youtube视频在这方面内容上已经相当完善。



这个专栏讲什么？
概念理解 帮助初学者或入门不深的朋友加深对某个模块的认识与理解
经验总结 根据自己的工作与学习经历，分享在某个模块或工具上所积累的经验，避免一些常见的坑
原理分析 尽可能的从源码层面上总结与分析虚幻引擎的各个模块的基本实现原理
由于不同的读者想看的内容不同，我会在每篇文章标题的后面添加文章类型，方便大家快速筛选。

专栏涉及的内容包括且不限于网络同步，Onlinesubsystem，物理，移动组件，AI，场景加载，摄像机，存储，序列化，配置文件等。如果后面大家确实想要看某个特定方面的文章，笔者也可以优先花时间去研究一下。另外，由于整个虚幻引擎真的相当复杂，笔者本人也还处于学习与成长之中，文中也难免有一些纰漏之处，还希望大家能多多提出意见与建议。



当前目录索引：

移动：

移动组件详解[原理分析]
RootMotion详解【原理分析】
工具：

配置文件详解[原理分析]
关卡：

流关卡与无缝地图切换[经验总结]
网络：

Session与Onlinesubsystem[概念理解]
关于网络同步的理解与思考[概念理解]
网络同步原理深入(上)[原理分析]
网络同步原理深入(下)[原理分析]
动画：

RootMotion详解【原理分析】
物理：

物理模块浅析[原理分析]
GamePlay：

摄像机系统解析[经验总结]
多线程：

多线程机制详解[原理分析]
废话太多不如来点干货，开篇先附上一张笔者学习虚幻4总结的类图（其实封面就是），主要针对Gameplay的相关内容。虽然并不算是严格意义的类图，不过对大家梳理虚幻引擎的架构内容还是多少有些帮助的。


UE4引擎架构类图（部分模块）


学习资料相关链接


文档与论坛

虚幻官方文档：最权威，资料最丰富的地方了

官方视频网站：虽然没有那么全，但是每个视频讲的都非常好，有中文字幕

官方论坛：可以多逛逛，说不定就能找到你想要的东西

官方问答中心：经常会有人提问与解答，可能覆盖你70%的问题

官方wiki：相当于官方博客，各种教程，非常详细。现在有目录了，直接搜索关键词就行。



视频

Youtube：强烈推荐，各种教学视频，非常全面了（需翻墙）

B站UE4官方：没有广告，虽然相比Youtube教学视频还是太少

虚幻4免费视频教学资源汇总：有些链接已经失效

UE4谌嘉诚 ：有很多入门教学视频，非常适合初学者



文章与博客

我的CSDN博客：基本上与专栏保持同步

UE4随笔: 网易同事写的，很多内容受益匪浅

图形游戏和宅: 对ue4渲染分析的非常细致

UE4引擎模块学习:对网络同步，物理等模块写的很深入

Shootertutorial：里面有很多基础功能的实现教程

风蚀之月：最近发的文章比较多，质量也相当不错

InsideUE4：不用多说了，大家都应该知道

游戏开发杂谈：吕老师是引擎专家，里面的内容都比较深适合有一定基础的朋友阅读

虚幻4现代C++编程实践 / 深入蓝图开发：燕良大佬的文章，对UE C++和蓝图深入有很大帮助，可以提升一些引擎设计的技巧和能力

aigo的博客：虽然已经不更新了，但是里面有大量的相关博客可供大家学习

Neil Wang：有各种使用UE4的经验文章，涉及到很多细节

漫游UE4：作者多多个模块做了比较深入的分析， 对我很有启发

UE4入门与精通：对垃圾回收，虚拟机等方面写的非常深入了

痞子龙UE编程：虽然是转载，但是汇总了不少UE相关资料

燕良的博客 ：里面有一些VR与ARPG游戏相关的教学

FLYING TREE：文章比较短小，不过可以参考



书籍

书籍：看的不多，有一些入门的个人觉得看前面的教程与文档就可以。国外的Unreal C++入门推荐 Mastering Unreal Engine 4.X。国内的这本 大象无形:虚幻引擎程序设计浅 也推荐一下。更深入一点的书籍目前还没有看到过。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》移动组件详解[原理分析]（2019.7.14更新）</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34257208
前言
这篇文章对UE4的移动组件做了非常详细的分析。主要从移动框架与实现原理，移动的网络同步，移动组件的改造三个方面来写。



目录
一．深刻理解移动组件的意义

二．移动实现的基本原理
2.1 移动组件与玩家角色
2.2 移动组件继承树
2.3 移动组件相关类关系简析

三．各个移动状态的细节处理
3.1 Walking
3.2 Falling
3.2.1 Jump
3.3 Swimming
3.4 Flying
3.5 FScopedMovementUpdate延迟更新

四．移动同步解决方案
4.1 服务器角色正常的移动流程
4.2 Autonomous角色
4.2.1 SavedMoves与移动合并
4.3 Simulated角色（更新）
4.4 关于物理托管后的移动

五．特殊移动模式的实现思路
5.1 二段跳，多段跳的实现
5.2 喷气式背包的实现
5.3 爬墙的实现
5.4 爬梯子的实现


一．深刻理解移动组件的意义
在大部分游戏中，玩家的移动是最最核心的一个基本操作。UE提供的GamePlay框架就给开发者提供了一个比较完美的移动解决方案。由于UE采用了组件化的设计思路，所以这个移动解决方案的核心功能就都交给了移动组件来完成。移动可能根据游戏的复杂程度有不同的处理，如果是一个简单的俯视视角RTS类型的游戏，可能只提供基本的坐标移动就可以了；而对于第一人称的RPG游戏，玩家可能上天入地，潜水飞行，那需要的移动就要更复杂一些。但是不管是哪一种，UE都基本上帮我们实现了，这也得益于其早期的FPS游戏的开发经验。

然而，引擎提供的基本移动并不一定能完成我们的目标，我们也不应该因此局限我们的设计。比如轻功的飞檐走壁，魔法飞船的超重力，弹簧鞋，喷气背包飞行控制，这些效果都需要我们自己去进一步的处理移动逻辑，我们可以在其基础上修改，也可以自定义自己的移动模式。不管怎么样，这些操作都需要对移动组件进行细致入微的调整，所以我们就必须要深刻理解移动组件的实现原理。

再者，在一个网络游戏中，我们对移动的处理会更加的复杂。如何让不同客户端的玩家都体验到流畅的移动表现？如何保证角色不会由于一点点的延迟而产生“瞬移”？UE对这方面的处理都值得我们去学习与思考。

移动组件看起来只是一个和移动相关的组件，但其本身涉及到状态机，同步解决方案，物理模块，不同移动状态的细节处理，动画以及与其他组件（Actor）之间的调用关系等相关内容，足够花上一段时间去好好研究。这篇文章会从移动的基本原理，移动状态的细节处理，移动同步的解决方案几个角度尽可能详细的分析其实现原理，然后帮助大家快速理解并更好的使用移动组件。最后，给出几个特殊移动模式的实现思路供大家参考。



二．移动实现的基本原理


2.1 移动组件与玩家角色
角色的移动本质上就是合理的改变坐标位置，在UE里面角色移动的本质就是修改某个特定组件的坐标位置。图2-1是我们常见的一个Character的组件构成情况，可以看到我们通常将CapsuleComponent(胶囊体)作为自己的根组件，而Character的坐标本质上就是其RootComponent的坐标，Mesh网格等其他组件都会跟随胶囊体而移动。移动组件在初始化的时候会把胶囊体设置为移动基础组件UpdateComponent，随后的操作都是在计算UpdateComponent的位置。


图2-1 一个默认Character的组件构成
当然，我们也并不是一定要设置胶囊体为UpdateComponent，对于DefaultPawn（观察者）会把他的SphereComponent作为UpdateComponent，对于交通工具对象AWheeledVehicle会默认把他的Mesh网格组件作为UpdateComponent。你可以自己定义你的UpdateComponent，但是你的自定义组件必须要继承USceneComponent（换句话说就是组件得有世界坐标信息），这样他才能正常的实现其移动的逻辑。



2.2 移动组件继承树
移动组件类并不是只有一个，他通过一个继承树，逐渐扩展了移动组件的能力。从最简单的提供移动功能，到可以正确模拟不同移动状态的移动效果。如图2-2所示


图2-2 移动组件继承关系类图
移动组件类一共四个。首先是UMovementComponent，作为移动组件的基类实现了基本的移动接口SafeMovementUpdatedComponent()，可以调用UpdateComponent组件的接口函数来更新其位置。

bool UMovementComponent::MoveUpdatedComponentImpl( const FVector& Delta, const FQuat& NewRotation, bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
{
    if (UpdatedComponent)
    {
        const FVector NewDelta = ConstrainDirectionToPlane(Delta);
        return UpdatedComponent->MoveComponent(NewDelta, NewRotation, bSweep, OutHit, MoveComponentFlags, Teleport);
    }

    return false;
}
通过上图可以看到UpdateComponent的类型是UScenceComponent，UScenceComponent类型的组件提供了基本的位置信息——ComponentToWorld，同时也提供了改变自身以及其子组件的位置的接口InternalSetWorldLocationAndRotation()。而UPrimitiveComponent又继承于UScenceComponent，增加了渲染以及物理方面的信息。我们常见的Mesh组件以及胶囊体都是继承自UPrimitiveComponent，因为想要实现一个真实的移动效果，我们时刻都可能与物理世界的某一个Actor接触着，而且移动的同时还需要渲染出我们移动的动画来表现给玩家看。

下一个组件是UNavMovementComponent，该组件更多的是提供给AI寻路的能力，同时包括基本的移动状态，比如是否能游泳，是否能飞行等。

UPawnMovementComponent组件开始变得可以和玩家交互了，前面都是基本的移动接口，不手动调用根本无法实现玩家操作。UPawnMovementComponent提供了AddInputVector()，可以实现接收玩家的输入并根据输入值修改所控制Pawn的位置。要注意的是，在UE中，Pawn是一个可控制的游戏角色（也可以是被AI控制），他的移动必须与UPawnMovementComponent配合才行，所以这也是名字的由来吧。一般的操作流程是，玩家通过InputComponent组件绑定一个按键操作，然后在按键响应时调用Pawn的AddMovementInput接口，进而调用移动组件的AddInputVector()，调用结束后会通过ConsumeMovementInputVector()接口消耗掉该次操作的输入数值，完成一次移动操作。

最后到了移动组件的重头了UCharacterMovementComponent，该组件可以说是Epic做了多年游戏的经验集成了，里面非常精确的处理了各种常见的移动状态细节，实现了比较流畅的同步解决方案。各种位置校正，平滑处理才达到了目前的移动效果，而且我们不需要自己写代码就会使用这个完成度的相当高的移动组件，可以说确实很适合做第一，第三人称的RPG游戏了。

其实还有一个比较常用的移动组件，UProjectileMovementComponent ，一般用来模拟弓箭，子弹等抛射物的运动状态。不过，这篇文章不将重点放在这里。



2.3 移动组件相关类关系简析
前面主要针对移动组件本身进行了分析，这里更全面的概括一下移动的整个框架。（参考图2-3）


图2-3 移动框架相关类图
在一个普通的三维空间里，最简单的移动就是直接修改角色的坐标。所以，我们的角色只要有一个包含坐标信息的组件，就可以通过基本的移动组件完成移动。但是随着游戏世界的复杂程度加深，我们在游戏里面添加了可行走的地面，可以探索的海洋。我们发现移动就变得复杂起来，玩家的脚下有地面才能行走，那就需要不停的检测地面碰撞信息（FFindFloorResult，FBasedMovementInfo）；玩家想进入水中游泳，那就需要检测到水的体积（GetPhysicsVolume()，Overlap事件，同样需要物理）；水中的速度与效果与陆地上差别很大，那就把两个状态分开写（PhysSwimming，PhysWalking）；移动的时候动画动作得匹配上啊，那就在更新位置的时候，更新动画（TickCharacterPose）；移动的时候碰到障碍物怎么办，被其他玩家推怎么处理（MoveAlongFloor里有相关处理）；游戏内容太少，想增加一些可以自己寻路的NPC，又需要设置导航网格（涉及到FNavAgentProperties）；一个玩家太无聊，那就让大家一起联机玩（模拟移动同步FRepMovement，客户端移动修正ClientUpdatePositionAfterServerUpdate）。

这么一看，做一个优秀移动组件还真不简单。但是不管怎么样，UE基本上都帮你实现了。通过上面的描述，你现在也大体上了解了移动组件在各个方面的处理，不过遇到具体的问题也许还是无从下手，所以咱们继续往下分析。



三．各个移动状态的细节处理
这一节我们把焦点集中在UCharacterMovementComponent组件上，来详细的分析一下他是如何处理各种移动状态下的玩家角色的。首先肯定是从Tick开始，每帧都要进行状态的检测与处理，状态通过一个移动模式MovementMode来区分，在合适的时候修改为正确的移动模式。移动模式默认有6种，基本常用的模式有行走、游泳、下落、飞行四种，有一种给AI代理提供的行走模式，最后还有一个自定义移动模式。


图3-1 单机模式下的移动处理流程
3.1 Walking
行走模式可以说是所有移动模式的基础，也是各个移动模式里面最为复杂的一个。为了模拟出出真实世界的移动效果，玩家的脚下必须要有一个可以支撑不会掉落的物理对象，就好像地面一样。在移动组件里面，这个地面通过成员变量FFindFloorResult CurrentFloor来记录。在游戏一开始的时候，移动组件就会根据配置设置默认的MovementMode，如果是Walking，就会通过FindFloor操作来找到当前的地面，CurrentFloor的初始化堆栈如下图3-2（Character Restart()的会覆盖Pawn的Restart()）：


图3-2
下面先分析一下FindFloor的流程，FindFloor本质上就是通过胶囊体的Sweep检测来找到脚下的地面，所以地面必须要有物理数据，而且通道类型要设置与玩家的Pawn有Block响应。这里还有一些小的细节，比如我们在寻找地面的时候，只考虑脚下位置附近的，而忽略掉腰部附近的物体；Sweep用的是胶囊体而不是射线检测，方便处理斜面移动，计算可站立半径等（参考图3-3，HitResult里面的Normal与ImpactNormal在胶囊体Sweep检测时不一定相同）。另外，目前Character的移动是基于胶囊体实现的，所以一个不带胶囊体组件的Actor是无法正常使用UCharacterMovementComponent的。


图3-3
找到地面玩家就可以站立住么？不一定。这又涉及到一个新的概念PerchRadiusThreshold，我称他为可栖息范围半径，也就是可站立半径。默认这个值为0，移动组件会忽略这个可站立半径的相关计算，一旦这个值大于0.15，就会做进一步的判断看看当前的地面空间是否足够让玩家站立在上面。

前面的准备工作完成了，现在正式进入Walking的位移计算，这一段代码都是在PhysWalking里面计算的。为了表现的更为平滑流畅，UE4把一个Tick的移动分成了N段处理（每段的时间不能超过MaxSimulationTimeStep）。在处理每段时，首先把当前的位置信息，地面信息记录下来。在TickComponent的时候根据玩家的按键时长，计算出当前的加速度。随后在CalcVelocity()根据加速度计算速度，同时还会考虑地面摩擦，是否在水中等情况。

// apply input to acceleration
Acceleration = ScaleInputAcceleration(ConstrainInputAcceleration(InputVector));
算出速度之后，调用函数MoveAlongFloor()改变当前对象的坐标位置。在真正调用移动接口SafeMoveUpdatedComponent()前还会简单处理一种特殊的情况——玩家沿着斜面行走。正常在walking状态下，玩家只会前后左右移动，不会有Z方向的移动速度。如果遇到斜坡怎么办？如果这个斜坡可以行走，就会调用ComputeGroundMovementDelta()函数去根据当前的水平速度计算出一个新的平行与斜面的速度，这样可以简单模拟一个沿着斜面行走的效果，而且一般来说上坡的时候玩家的水平速度应该减小，通过设置bMaintainHorizontalGroundVelocity为false可以自动处理这种情况。

现在看起来我们已经可以比较完美的模拟一个移动的流程了，不过仔细想一下还有一种情况没考虑到。那就是遇到障碍的情况怎么处理？根据我们平时游戏经验，遇到障碍肯定是移动失败，还可能沿着墙面滑动一点。UE里面确实也就是这么处理的，在角色移动的过程中（SafeMoveUpdatedComponent），会有一个碰撞检测流程。由于UPrimitiveComponent组件才拥有物理数据，所以这个操作是在函数UPrimitiveComponent::MoveComponentImpl里面处理的。下面的代码会检测移动过程中是否遇到了障碍，如果遇到了障碍会把HitResult返回。

FComponentQueryParams Params(PrimitiveComponentStatics::MoveComponentName, Actor);
FCollisionResponseParams ResponseParam;
InitSweepCollisionParams(Params, ResponseParam);
bool const bHadBlockingHit = MyWorld->ComponentSweepMulti(Hits, this, TraceStart, TraceEnd, InitialRotationQuat, Params);
在接收到SafeMoveUpdatedComponent()返回的HitResult后，会在下面的代码里面处理碰撞障碍的情况。

如果Hit.Normal在Z方向上有值而且还可以行走，那说明这是一个可以移动上去的斜面，随后让玩家沿着斜面移动
判断当前的碰撞体是否可以踩上去，如果可以的话就试着踩上去，如果过程中发现没有踩上去，也会调用SlideAlongSurface()沿着碰撞滑动。
// UCharacterMovementComponent::PhysWalking
else if (Hit.IsValidBlockingHit())
{
    // We impacted something (most likely another ramp, but possibly a barrier).
    float PercentTimeApplied = Hit.Time;
    if ((Hit.Time > 0.f) && (Hit.Normal.Z > KINDA_SMALL_NUMBER) && IsWalkable(Hit))
    {
        // Another walkable ramp.
        const float InitialPercentRemaining = 1.f - PercentTimeApplied;
        RampVector = ComputeGroundMovementDelta(Delta * InitialPercentRemaining, Hit, false);
        LastMoveTimeSlice = InitialPercentRemaining * LastMoveTimeSlice;
        SafeMoveUpdatedComponent(RampVector, UpdatedComponent->GetComponentQuat(), true, Hit);
        const float SecondHitPercent = Hit.Time * InitialPercentRemaining;
        PercentTimeApplied = FMath::Clamp(PercentTimeApplied + SecondHitPercent, 0.f, 1.f);
    }

    if (Hit.IsValidBlockingHit())
    {
        if (CanStepUp(Hit) || (CharacterOwner->GetMovementBase() != NULL && CharacterOwner->GetMovementBase()->GetOwner() == Hit.GetActor()))
        {
            // hit a barrier, try to step up
            const FVector GravDir(0.f, 0.f, -1.f);
            if (!StepUp(GravDir, Delta * (1.f - PercentTimeApplied), Hit, OutStepDownResult))
            {
                UE_LOG(LogCharacterMovement, Verbose, TEXT("- StepUp (ImpactNormal %s, Normal %s"), *Hit.ImpactNormal.ToString(), *Hit.Normal.ToString());
                HandleImpact(Hit, LastMoveTimeSlice, RampVector);
                SlideAlongSurface(Delta, 1.f - PercentTimeApplied, Hit.Normal, Hit, true);
            }
            else
            {
                // Don't recalculate velocity based on this height adjustment, if considering vertical adjustments.
                UE_LOG(LogCharacterMovement, Verbose, TEXT("+ StepUp (ImpactNormal %s, Normal %s"), *Hit.ImpactNormal.ToString(), *Hit.Normal.ToString());
                bJustTeleported |= !bMaintainHorizontalGroundVelocity;
            }
        }
        else if ( Hit.Component.IsValid() && !Hit.Component.Get()->CanCharacterStepUp(CharacterOwner) )
        {
            HandleImpact(Hit, LastMoveTimeSlice, RampVector);
            SlideAlongSurface(Delta, 1.f - PercentTimeApplied, Hit.Normal, Hit, true);
        }
    }
}
基本上的移动处理就完成了，移动后还会立刻判断玩家是否进入水中，或者进入Falling状态，如果是的话立刻切换到新的状态。
由于玩家在一帧里面可能会从Walking，Swiming，Falling的等状态不断的切换，所以在每次执行移动前都会有一个iteration记录当前帧的移动次数，如果超过限制就会取消本次的移动模拟行为。



3.2 Falling
Falling状态也算是处理Walking以外最常见的状态，只要玩家在空中（无论是跳起还是下落），玩家都会处于Falling状态。与Walking相似，为了表现的更为平滑流畅，Falling的计算也把一个Tick的移动分成了N段处理（每段的时间不能超过MaxSimulationTimeStep）。在处理每段时，首先计算玩家通过输入控制的水平速度，因为玩家在空中也可以受到玩家控制的影响。随后，获取重力计算速度。重力的获取有点意思，你会发现他是通过Volume体积获取的，

float UMovementComponent::GetGravityZ() const
{
    return GetPhysicsVolume()->GetGravityZ();
}
APhysicsVolume* UMovementComponent::GetPhysicsVolume() const
{
    if (UpdatedComponent)
    {
        return UpdatedComponent->GetPhysicsVolume();
    }
    return GetWorld()->GetDefaultPhysicsVolume();
}
Volume里面会取WorldSetting里面的GlobalGravityZ，这里给我们一个提示，我们可以通过修改代码实现不同Volume的重力不同，实现自定义的玩法。注意，即使我们没有处在任何一个体积里面，他也会给我们的UpdateComponent绑定一个默认的DefaultVolume。那为什么要有一个DefaultVolume？因为在很多逻辑处理上都需要获取DefaultVolume以及里面的相关的数据。比如，DefaultVolume有一个TerminalLimit，在通过重力计算下降速度的时候不可以超过这个设置的速度，我们可以通过修改该值来改变速度的限制。默认情况下，DefaultVolume里面的很多属性都是通过ProjectSetting里面的Physics相关配置来初始化的。参考图3-4，


图3-4
通过获取到的Gravity计算出当前新的FallSpeed（NewFallVelocity里面计算，计算规则很简单，就是单纯的用当前速度-Gravity*deltaTime）。随后再根据当前以及上一帧的速度计算出位移并进行移动，公式如下

FVector Adjusted = 0.5f*(OldVelocity + Velocity) * timeTick; 
SafeMoveUpdatedComponent( Adjusted, PawnRotation, true, Hit);
前面我们计算完速度并移动玩家后，也一样要考虑到移动碰撞问题。

第一种情况就是正常落地，如果玩家计算后发现碰撞到一个可以站立的地形，那直接调用ProcessLanded进行落地操作（这个判断主要是根据碰撞点的高度来的，可以筛选掉墙面）。

第二种情况就是跳的过程中遇到一个平台，然后检测玩家的坐标与当前碰撞点是否在一个可接受的范围（IsWithinEdgeTolerance），是的话就执行FindFloor重新检测一遍地面，检测到的话就执行落地流程。

第三种情况是就是墙面等一些不可踩上去的，下落过程如果碰到障碍，首先会执行HandleImpact给碰到的对象一个力。随后调用ComputeSlideVector计算一下滑动的位移，由于碰撞到障碍后，玩家的速度会有变化，这时候重新计算一下速度，再次调整玩家的位置与方向。如果玩家这时候有水平方向上的位移，还会通过LimitAirControl来限制玩家的速度，毕竟玩家在空中是无法自由控制角色的。对第三种情况做进一步的延伸，可能会出现碰撞调整后又碰到了另一个墙面，这里Falling的处理可以让玩家在两个墙面找到一个合适的位置。但是仍然不能解决玩家被夹在两个斜面但是却无法落地的情况（或者在Waling和Falling中不断切换）。如果有时间，我们后面可以尝试解决这个问题，解决思路可以从FindFloor下的ComputeFloorDist函数入手，目的就是让这个情况下玩家可以找到一个可行走的地面。


图3-5 夹在缝隙导致不停的切换状态
3.2.1 Jump
提到Falling，不得不提跳跃这一基本操作。下面大致描述了跳跃响应的基本流程，
1. 绑定触发响应事件

void APrimalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}
void ACharacter::Jump()
{
    bPressedJump = true;
    JumpKeyHoldTime = 0.0f;
}

void ACharacter::StopJumping()
{
    bPressedJump = false;
    ResetJumpState();
}
2.一旦按键响应立刻设置bPressedJump为true。TickComponent的帧循环调用ACharacter::CheckJumpInput来立刻检测到是否执行跳跃操作

①执行CanJump()函数，处理蓝图里面的相关限制逻辑。如果蓝图里面不重写该函数，就会默认执行ACharacter::CanJumpInternal_Implementation()。这里面是控制玩家能否跳跃的依据，比如蹲伏状态不能跳跃，游泳状态不能跳跃。另外，有一个JumpMaxHoldTime表示玩家按键超过这个值后不会触发跳跃。JumpMaxCount表示玩家可以执行跳跃的段数。（比如二段跳）
②执行CharacterMovement->DoJump(bClientUpdating)函数，执行跳跃操作，进入Falling，设置跳跃速度为JumpZVelocity，这个值不能小于0。
③ 判断const bool bDidJump = canJump && CharacterMovement &&
DoJump;是否为真。做一些其他的相关操作。
const bool bDidJump = CanJump() && CharacterMovement->DoJump(bClientUpdating);
if (!bWasJumping && bDidJump)
{
    JumpCurrentCount++;
    OnJumped();
}
3.在一次PerformMovement结束后，就会执行ClearJumpInput，设置设置bPressedJump为false。但是不会清除JumpCurrentCount这样可以继续处理多段跳。

4.玩家松开按键p也会设置bPressedJump为false，清空相关状态。如果玩家仍在空中，那也不会清除JumpCurrentCount。一旦bPressedJump为false，就不会处理任何跳跃操作了。

5.如果玩家在空中按下跳跃键，他也会进入ACharacter::CheckJumpInput，如果JumpCurrentCount小于JumpMaxCount，玩家就可以继续执行跳跃操作了。


图3-6
3.3 Swiming
各个状态的差异本质有三个点：

1.速度的不同
2.受重力影响的程度
3.惯性大小
游泳状态表现上来看是一个有移动惯性（松手后不会立刻停止），受重力影响小（在水中会慢慢下落或者不动），移动速度比平时慢（表现水有阻力）的状态。而玩家是否在水中的默认检测逻辑也比较简单，就是判断当前的updateComponent所在的Volume是否是WaterVolume。（在编辑器里面拉一个PhysicsVolume，修改属性WaterVolume即可）

CharacterMovement组件里面有浮力大小配置Buoyancy，根据玩家潜入水中的程度（ImmersionDepth返回0-1）可计算最终的浮力。随后，开始要计算速度了，这时候我们需要获取Volume里面的摩擦力Friction，然后传入CalcVelocity里面，这体现出玩家在水中移动变慢的效果。随后在Z方向通过计算浮力大小该计算该方向的速度，随着玩家潜水的程度，你会发现玩家在Z方向的速度越来越小，一旦全身都浸入了水中，在Z轴方向的重力速度就会被完全忽略。

// UCharacterMovementComponent::PhysSwimming
const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction * Depth;
CalcVelocity(deltaTime, Friction, true, BrakingDecelerationSwimming);
Velocity.Z += GetGravityZ() * deltaTime * (1.f - NetBuoyancy);

// UCharacterMovementComponent::CalcVelocity Apply fluid friction
if (bFluid)
{
    Velocity = Velocity * (1.f - FMath::Min(Friction * DeltaTime, 1.f));
}



图3-7 角色在水体积中飘浮
速度计算后，玩家就可以移动了。这里UE单独写了一个接口Swim来执行移动操作，同时他考虑到如果移动后玩家离开了水体积而且超出水面过大，他机会强制把玩家调整到水面位置，表现会更好一些。

接下来还要什么，那大家可能也猜出来了，就是处理移动中检测到碰撞障碍的情况。基本上和之前的逻辑差不多，如果可以踩上去（StepUp()）就调整玩家位置踩上去，如果踩不上去就给障碍一个力，然后顺着障碍表面滑动一段距离（HandleImpact，SlideAlongSurface）。

那水中移动的惯性表现是怎么处理的呢？其实并不是水中做了什么特殊处理，而是计算速度时有两个传入的参数与Walking不同。一个是Friction表示摩擦力，另一个是BrakingDeceleration表示刹车的反向速度。
在加速度为0的时候（表示玩家的输入已经被清空），水中的传入的摩擦力要远比地面摩擦里小（0.15:8），而刹车速度为0（Walking为2048），所以ApplyVelocityBraking在处理的时候在Walking表现的好像立刻刹车一样，而在Swim和fly等情况下就好像有移动惯性一样。

// Only apply braking if there is no acceleration, or we are over our max speed and need to slow down to it.
if ((bZeroAcceleration && bZeroRequestedAcceleration) || bVelocityOverMax)
{
    const FVector OldVelocity = Velocity;

    const float ActualBrakingFriction = (bUseSeparateBrakingFriction ? BrakingFriction : Friction);
    ApplyVelocityBraking(DeltaTime, ActualBrakingFriction, BrakingDeceleration);

    //Don't allow braking to lower us below max speed if we started above it.   
    if (bVelocityOverMax && Velocity.SizeSquared() < FMath::Square(MaxSpeed) && FVector::DotProduct(Acceleration, OldVelocity) > 0.0f)
    {
        Velocity = OldVelocity.GetSafeNormal() * MaxSpeed;
    }
}


3.4 Flying
终于讲到了最后一个移动状态了，如果你想调试该状态的话，在角色的移动组件里面修改DefaultLandMovementMode为Flying即可。
Flying和其他状态套路差不多，而且相对更简单一些，首先根据前面输入计算Acceleration，然后根据摩擦力开始计算当前的速度。速度计算后调用SafeMoveUpdatedComponent进行移动。如果碰到障碍，就先看能不能踩上去，不能的话处理碰撞，沿着障碍表面滑动。

//UCharacterMovementComponent::PhysFlying
//RootMotion Relative
RestorePreAdditiveRootMotionVelocity();

if( !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
{
    if( bCheatFlying && Acceleration.IsZero() )
    {
        Velocity = FVector::ZeroVector;
    }
    const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction;
    CalcVelocity(deltaTime, Friction, true, BrakingDecelerationFlying);
}
//RootMotion Relative
ApplyRootMotionToVelocity(deltaTime);
有一个关于Flying状态的现象大家可能会产生疑问，当我设置默认移动方式为Flying的时候，玩家可以在松开键盘后进行滑行一段距离（有惯性）。但是使用GM命令的时候，为什么就像Walking状态一样，松开按键后立刻停止？
其实时代码对cheat Flying做了特殊处理，玩家松开按键后，加速度变为0，这时候强制设置玩家速度为0。所以使用GM的表现与实际上的不太一样。



3.5 FScopedMovementUpdate延迟更新
FScopedMovementUpdate并不是一种状态，而是一种优化移动方案。因为大家在查看引擎代码时，可能会看到在执行移动前会有下面这样的代码：

// Scoped updates can improve performance of multiple MoveComponent calls.
{
    FScopedMovementUpdate ScopedMovementUpdate(UpdatedComponent, bEnableScopedMovementUpdates ? EScopedUpdate::DeferredUpdates : EScopedUpdate::ImmediateUpdates);

    MaybeUpdateBasedMovement(DeltaSeconds);

    //......其他逻辑处理，这里不给出具体代码

    // Clear jump input now, to allow movement events to trigger it for next update.
    CharacterOwner->ClearJumpInput();
    // change position
    StartNewPhysics(DeltaSeconds, 0);

    //......其他逻辑处理，这里不给出具体代码

    OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
} // End scoped movement update
为什么要把移动的代码放到这个大括号里面，FScopedMovementUpdate又是什么东西？仔细回想一下我们前面具体的移动处理逻辑，在一个帧里面，我们由于移动的不合法，碰到障碍等可能会多次重置或者修改我们的移动。如果只是简单修改胶囊体的位置，其实没什么，不过实际上我们还要同时修改子组件的位置，更新物理体积，更新物理位置等等，而计算过程中的那些移动数据其实是没有用的，我们只需要最后的那个移动数据。

因此使用FScopedMovementUpdate可以在其作用域范围内，先锁定不更新物理等对象的移动，等这次移动真正的完成后再去更新。（等到FScopedMovementUpdate析构的时候再处理）用到FScopedMovementUpdate的地方有很多，基本上涉及到移动回滚的逻辑都会有。



四．移动同步解决方案
前面关于移动逻辑的细节处理都是在PerformMovement里面实现的，我们可以把函数PerformMovement当成一个完整的移动处理流程。这个流程无论是在客户端还是在服务器都必须要执行，或者作为一个单机游戏，这一个接口基本上可以满足我们的正常移动了。不过，在网络游戏中，为了让所有的玩家体验一个几乎相同的世界，需要保证一个具有绝对权威的服务器，这个服务器可以修正客户端的不正常移动行为，保证各个客户端的一致性。相关同步的操作都是基于UCharacterMovement组件实现的，所以我们的角色必须要使用这个移动组件。

移动组件的同步全都是基于RPC不可靠传输的，你会在UCharacterMovement头文件里面看到多个以Server或者Client开头的RPC函数。

关于移动组件的同步思路，建议选阅读一下官方文档的内容，https://docs.unrealengine.com/latest/CHN/Gameplay/Networking/CharacterMovementComponent/index.html 回头看可能更为清晰一点。现在我们把整个移动细节作为一个接口封装起来，宏观的研究移动组件的同步细节。

另外，如果还没有完全搞清ROLE_Authority，ROLE_AutonomousProxy，ROLE_SimulatedProxy的概念，请参考 UE4网络同步详解(一)——理解同步规则。这里举个例子，一个服务器上有一个玩家ServerA和一个NPC ServerB，客户端上拥有从服务器复制过来的这个玩家ClientA与NPC ClientB。由于ServerA与ServerB都是在服务器上生成的，所以他们两在服务器上的所有权Role都是ROLE_Authority。ClientA在客户端上由于被玩家控制，他的Role是ROLE_AutonomousProxy。ClientB在客户端是完全通过服务器同步来控制的，他的Role就是ROLE_SimulatedProxy。



4.1 服务器角色正常的移动流程
第三章节里面的图3-1就是单机或者ListenServer服务器执行的移动流程。作为一个本地控制的角色，他只需要认真的执行正常的移动（PerformMovement）逻辑处理即可，所以ListenServer服务器移动不再赘述。

但是对于DedicateServer，他的本地没有控制的角色，对移动的处理就有差异了。分为两种情况：

该角色在客户端是模拟(Simulate)角色，移动完全由服务器同步过去，如各类AI角色。这类移动一般是服务器上行为树主动触发的
该角色在客户端是拥有自治(Autonomous)权利的Character，如玩家控制的主角。这类移动一般是客户端接收玩家输入数据本地模拟后，再通过RPC发给服务器进行模拟的
从下面的代码可以了解到这两种情况的处理（注意注释）：

// UCharacterMovementComponent:: TickComponent
// simulate的角色在服务器执行IsLocallyControlled也会返回true
// Allow root motion to move characters that have no controller.
if( CharacterOwner->IsLocallyControlled() || (!CharacterOwner->Controller && bRunPhysicsWithNoController) || (!CharacterOwner->Controller && CharacterOwner->IsPlayingRootMotion()) )
{
    {
        SCOPE_CYCLE_COUNTER(STAT_CharUpdateAcceleration);

        // We need to check the jump state before adjusting input acceleration, to minimize latency
        // and to make sure acceleration respects our potentially new falling state.
        CharacterOwner->CheckJumpInput(DeltaTime);

        // apply input to acceleration
        Acceleration = ScaleInputAcceleration(ConstrainInputAcceleration(InputVector));
        AnalogInputModifier = ComputeAnalogInputModifier();
    }

    if (CharacterOwner->Role == ROLE_Authority)
    {
        // 单机或者DedicateServer控制simulate角色移动
        PerformMovement(DeltaTime);
    }
    else if (bIsClient)
    {
        ReplicateMoveToServer(DeltaTime, Acceleration);
    }
}
else if (CharacterOwner->GetRemoteRole() == ROLE_AutonomousProxy)
{
    //DedicateServer控制自治客户端角色移动
    // Server ticking for remote client.
    // Between net updates from the client we need to update position if based on another object,
    // otherwise the object will move on intermediate frames and we won't follow it.
    MaybeUpdateBasedMovement(DeltaTime);
    MaybeSaveBaseLocation();

    // Smooth on listen server for local view of remote clients. We may receive updates at a rate different than our own tick rate.
    if (CharacterMovementCVars::NetEnableListenServerSmoothing && !bNetworkSmoothingComplete && IsNetMode(NM_ListenServer))
    {
        SmoothClientPosition(DeltaTime);
    }
}
这两种情况详细的流程我们在下面两个小结分析。



4.2 Autonomous角色
一个客户端的角色是完全通过服务器同步过来的，他身上的移动组件也一样是被同步过来的，所以游戏一开始客户端的角色与服务器的数据是完全相同的。对于Autonomous角色，大致的实现思路如下：

客户端通过接收玩家的Input输入，开始进行本地的移动模拟流程，移动前首先创建一个移动预测数据结构FNetworkPredictionData_Client_Character，执行PerformMovement移动，随后保存当前的移动数据（速度，旋转，时间戳以及移动结束后的位置等信息）到前面的FNetworkPredictionData里面的SavedMoves列表里面，并通过RPC将当前的Move数据发送该数据到服务器。然后继续进行TickComponent操作，重复这个流程。

客户端在发送给服务器RPC消息的同时，本地还会不断的执行移动模拟。SavedMoves列表里面的数据也就越来越多。如果这时候收到了一个ClientAckGoodMove调用，那么表示服务器接收了对应时间戳的客户端移动，客户端就将这个时间戳之前的SavedMoves全部移除。如果客户端收到了ClientAdjustPosition调用，那么表示对应这个时间戳的移动有问题，客户端需要修改成服务器传过来的位置，并重新播放那些还没被确认的SaveMoves列表里面的移动。


图4-1
整个流程如下图所示：


图4-2 Autonomous角色移动流程图


4.2.1 SavedMoves与移动合并
仔细阅读源码的朋友对上面给出的流程可能并不是很满意，因为除了ServerMove你可能还看到了ServerMoveDual以及ServerMoveOld等函数接口。而且除了SavedMoves列表，还有PendingMove，FreeMove这些移动列表。他们都是做什么的？

简单来讲，这属于移动带宽优化的一个方式，将没有意义的移动合并，减少消息的发送量。

当客户端执行完本次移动后，都会把当前的移动数据以一个结构体保存到SavedMove列表，然后会判断当前的这个移动是否可以被延迟发送（CanDelaySendingMove(),默认为true），如果可以就会继续判断当前的客户端网络速度如何。如果当前的速度有一点慢或者上次更新的时间很短，移动组件就会将当前的移动赋值给PendingMove（表示将要执行的移动）并取消本次给服务器消息的发送。

const bool bCanDelayMove = (CharacterMovementCVars::NetEnableMoveCombining != 0) && CanDelaySendingMove(NewMove);

if (bCanDelayMove && ClientData->PendingMove.IsValid() == false)
{
    // Decide whether to hold off on move
    // send moves more frequently in small games where server isn't likely to be saturated
    float NetMoveDelta;
    UPlayer* Player = (PC ? PC->Player : nullptr);
    AGameStateBase const* const GameState = GetWorld()->GetGameState();

    if (Player && (Player->CurrentNetSpeed > 10000) && (GameState != nullptr) && (GameState->PlayerArray.Num() <= 10))
    {
        NetMoveDelta = 0.011f;
    }
    else if (Player && CharacterOwner->GetWorldSettings()->GameNetworkManagerClass) 
    {
        //这里会根据网络管理的配置以及客户端网络速度来决定是否延迟发送
        NetMoveDelta = FMath::Max(0.0222f,2 * GetDefault<AGameNetworkManager>(CharacterOwner->GetWorldSettings()->GameNetworkManagerClass)->MoveRepSize/Player->CurrentNetSpeed);
    }
    else
    {
        NetMoveDelta = 0.011f;
    }

    if ((GetWorld()->TimeSeconds - ClientData->ClientUpdateTime) * CharacterOwner->GetWorldSettings()->GetEffectiveTimeDilation() < NetMoveDelta)
    {
        // Delay sending this move.
        ClientData->PendingMove = NewMove;
        return;
    }
}
当客户端进去下次Tick的时候，就会判断当前的新的移动是否能与上次保存的PendingMove合并。如果可以，就可以减少一次消息的发送。如果不能合并，那么在本次移动结束后给服务器发送一个两次移动（ServerMoveDual），就是单纯的执行两次ServerMove。

服务器在受到两次移动的时候对第一次移动不进行任何校验，只对第二个移动进行正常的校验，判断是否是第一次的标准就是ClientPosition是不是FVector(1.f,2.f,3.f)。通过下面的代码就可以了解了

void UCharacterMovementComponent::ServerMoveDual_Implementation(
    float TimeStamp0,
    FVector_NetQuantize10 InAccel0,
    uint8 PendingFlags,
    uint32 View0,
    float TimeStamp,
    FVector_NetQuantize10 InAccel,
    FVector_NetQuantize100 ClientLoc,
    uint8 NewFlags,
    uint8 ClientRoll,
    uint32 View,
    UPrimitiveComponent* ClientMovementBase,
    FName ClientBaseBone,
    uint8 ClientMovementMode)
{
    ServerMove_Implementation(TimeStamp0, InAccel0, FVector(1.f,2.f,3.f), PendingFlags, ClientRoll, View0, ClientMovementBase, ClientBaseBone, ClientMovementMode);
    ServerMove_Implementation(TimeStamp, InAccel, ClientLoc, NewFlags, ClientRoll, View, ClientMovementBase, ClientBaseBone, ClientMovementMode);
}
其实，UE的思想就是，将所有的移动的关键信息都数据化，这样移动就可以自由的存储和回放。为了节省带宽，提高效率，我们也就可以想出各种办法来减少发送不必要的消息，对于一个没有移动过的玩家，理论上我们甚至都可以不去同步他的移动信息。


图4-3 移动预测及保存的数据结构示意图


4.3 Simulated角色
首先看一下官方文档对Simulate角色移动的描述：

对于那些不由人类控制的人物，其动作往往会通过正常的 PerformMovement() 代码在服务器（此时充当了主控者）上进行更新。Actor 的状态，如方位、旋转、速率和其他一些选定的人物特有状态（如跳跃）都会通过正常的复制机制复制到其他机器，因此，它们不必在每一帧都经由网络传送。为了在远程客户端上针对这些人物提供更流畅的视觉呈现，该客户端机器将在每一帧为模拟代理执行一次模拟更新，直到新的数据（由服务器主控）到来。本地客户端查看其他远程人类玩家时也是如此；远程玩家将其更新发送给服务器，后者为该玩家执行一次完整的动作更新，然后定期复制数据给所有其他玩家。 这个更新的作用是根据复制的状态来模拟预期的动作结果，以便在下一次更新前“填补空缺”。所以，客户端并没有在新的位置放置由服务器发送的代理，然后将它们保留到下次更新到来（可能是几个后续帧），而是通过应用速率和移动规则，在每一帧模拟出一次更新。在另一次更新到来时，客户端将重置本地模拟并开始新一次模拟。
简单来说，Simulate角色的在服务器上的移动就是正常的PerformMovement流程。而在客户端上，该角色的移动分成两个步骤来处理——收到服务器的同步数据时就直接进行设置。在没有收到服务器消息的时候根据上一次服务器传过来的数据（包括速度与旋转等）在本地执行Simulate模拟，等着下一个同步数据到来。Simulate角色采用这样的机制，本质上是为了减小同步带来的开销。下面代码展示了所有Character的同步属性

void ACharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
    {
        Super::GetLifetimeReplicatedProps( OutLifetimeProps );
        DOREPLIFETIME_CONDITION( ACharacter, RepRootMotion,COND_SimulatedOnlyNoReplay);
        DOREPLIFETIME_CONDITION( ACharacter, ReplicatedBasedMovement,   COND_SimulatedOnly );
        DOREPLIFETIME_CONDITION( ACharacter, ReplicatedServerLastTransformUpdateTimeStamp, COND_SimulatedOnlyNoReplay);

        DOREPLIFETIME_CONDITION( ACharacter, ReplicatedMovementMode,    COND_SimulatedOnly );
        DOREPLIFETIME_CONDITION( ACharacter, bIsCrouched,           COND_SimulatedOnly );

        // Change the condition of the replicated movement property to not replicate in replays since we handle this specifically via saving this out in external replay data
        DOREPLIFETIME_CHANGE_CONDITION(AActor,ReplicatedMovement,COND_SimulatedOrPhysicsNoReplay);


    }

void APawn::PostNetReceiveVelocity(const FVector& NewVelocity)
{
	if (GetLocalRole() == ROLE_SimulatedProxy)
	{
		UMovementComponent* const MoveComponent = GetMovementComponent();
		if ( MoveComponent )
		{
			MoveComponent->Velocity = NewVelocity;
		}
	}
}

void ACharacter::PostNetReceiveLocationAndRotation()
{
	if(GetLocalRole() == ROLE_SimulatedProxy)
	{
		// Don't change transform if using relative position (it should be nearly the same anyway, or base may be slightly out of sync)
		if (!ReplicatedBasedMovement.HasRelativeLocation())
		{
			const FRepMovement& ConstRepMovement = GetReplicatedMovement();
			const FVector OldLocation = GetActorLocation();
			const FVector NewLocation = FRepMovement::RebaseOntoLocalOrigin(ConstRepMovement.Location, this);
			const FQuat OldRotation = GetActorQuat();

			CharacterMovement->bNetworkSmoothingComplete = false;
			CharacterMovement->bJustTeleported |= (OldLocation != NewLocation);
			CharacterMovement->SmoothCorrection(OldLocation, OldRotation, NewLocation, ConstRepMovement.Rotation.Quaternion());
			OnUpdateSimulatedPosition(OldLocation, OldRotation);
		}
		CharacterMovement->bNetworkUpdateReceived = true;
	}
}
ReplicatedMovement记录了当前Character的位置旋转，速度等重要的移动数据，这个成员（包括其他属性）在Simulate或者开启物理模拟的客户端才执行（可以先忽略NoReplay，这个和回放功能有关）。同时，我们可以看到Character大部分的同步属性都是与移动同步有关，而且基本都是SimulatedOnly，这表示这些属性只在模拟客户端才会进行同步。除了ReplicatedMovement属性以外，ReplicatedMovementMode同步了当前的移动模式，ReplicatedBasedMovement同步了角色所站在的Component的相关数据，ReplicatedServerLastTransformUpdateTimeStamp同步了最新的服务器移动更新帧，也就相当于最后一次服务器更新移动的时间（在ACharacter::PreReplication里会将服务器当前的移动数据赋值给ReplicatedServerLastTransformUpdateTimeStamp然后进行同步）。

了解了这些同步的数据后，我们开始分析其移动流程。流程如下图所示（RootMotion的情况我在上一章节已经描述，这里不再赘述）。其实其基本思路与普通的移动处理相似，只不过是调用SimulateTick去根据当前的速度等条件模拟客户端移动，但是有一点非常重要的差异就是Simulate的角色的胶囊体移动与Mesh移动是分开进行的。这么做的原因是什么呢？我们稍后再解释。


图4-4 Simulate角色移动流程图
详细一点的流程描述：

1.移动组件先进行TickComponent根据条件Role == ROLE_SimulatedProxy判断进入SimulatedTick

2.先判断是否是回放模式，是的话直接进入SmoothClientPosition，并且不需要处理任何回放纠正逻辑

3.判断是否处于播放rootmotion montage状态，是的话要进入Rootmotion的特殊处理，可以参考我最新的文章；

4.判断目前是否处于平滑未完成阶段，是的话在本次SimulateMovement里面不要更新mesh的位置并记录当前根组件的位置与旋转，通过FScopedPreventAttachedComponentMove实现

5.SimulateMovement开始执行，如果是物理状态或者不是Movable状态直接返回/如果当前坐标旋转速度都是0返回/如果客户端玩家脚下没有找到踩的东西，但是服务器却有直接返回（GetReplicatedBasedMovement().IsBaseUnresolved()）

6.在触发本地的移动之前会声明一个特殊的变量FScopedMovementUpdate，他是局部变量，作用是限制其作用域内UpdateBounds(), OnUpdateTransform(), UpdatePhysicsVolume(), UpdateChildTransforms()的更新（默认通过bEnableScopedMovementUpdates开启）这个好处就是确保上面那些函数只会执行一次。不过这里可能会有疑问，我就是一阵操作为什么会执行多次？因为移动组件的模拟完全是基于物理的，所以玩家很有可能在模拟移动遇到不合法的位置与障碍进而触发移动回滚，这样就会造成性能上的损耗。

7.判断最近一帧是否收到网络更新消息bNetworkUpdateReceived，是的话就表示这一帧收到了相关的更新信息，会进一步检测是否应该修改Movementmode或者执行传送teleport等


8.到这一步就表示要真正的执行本地模拟了，这里会读取ReplicatedMovement.LinearVelocity，如果为0就会设置当前模拟速度为0。

9.尝试更新BasedMovement，即Character脚下所踩的东西

10.尝试本地模拟，可以通过属性bNetworkSkipProxyPredictionOnNetUpdate以及控制台变量NetEnableSkipProxyPredictionOnNetUpdate来决定是否要进行模拟

11.执行MoveSmooth，根据传入的速度与deltatime计算位移（FVector Delta = InVelocity * DeltaSeconds;），这里会根据当前的移动状态是walking还是flying决定执行MoveAlongFloor还是直接SafeMoveUpdatedComponent

12.如果在地面上移动，还会计算触碰到的地面组件，找不到的话触发MOVE_Falling

13.整个模拟过程结束后，做一些回调OnMovementUpdated，CallMovementUpdateDelegate。记录一下当前的坐标旋转速度

14.SimulateMovement结束，由于前面第4步移动根组件的时候通过FScopedMovementUpdate限制了子Mesh的移动，所以这里要重新更新一下Mesh。当前这里可能会有问题，这个时候立刻更新mesh移动，那和更新完胶囊体顺便更新子组件有什么区别，不也没有什么平滑么？首先，这样做解决了前面说到了胶囊体移动可能触发回滚的损耗。其次，真正的平滑是在后面的SmoothClientPosition里面执行的。

15.模拟移动后，触发SmoothClientPosition。这里会默认执行两个函数，SmoothClientPosition_Interpolate(DeltaSeconds); SmoothClientPosition_UpdateVisuals；本质上这两个函数是为了给Mesh做插值，让simulated客户端看起来移动平滑。如果是线性模式的话，会与服务器同步的数据与时间有紧密的关系，后面会详细描述

SmoothClientPosition_Interpolate是真正的执行插值的逻辑，而SmoothClientPosition_UpdateVisuals执行的是更新Mesh的逻辑。

16.SmoothClientPosition_Interpolate无论哪种插值，本质上都是修改ClientData->MeshRotationOffset与ClientData->MeshTranslationOffset，Clientdata是一个用于同步预测的自定义数据，后面详细描述。所以你会发现，Mesh的平滑更新本质上是更新其相对胶囊体的偏移。

17.SmoothClientPosition_UpdateVisuals会根据上面的偏移去处理Mesh的位置，达到平滑的效果。



客户端的模拟我们大致了解了流程，那么接收服务器数据并修正是在哪里处理的呢？答案是AActor::OnRep_ReplicatedMovement。Simulateticked客户端是完全走属性同步的，客户端在接收到服务器同步的ReplicatedMovement时，会产生回调函数触发SmoothCorrection的执行，从当前客户端的位置平滑的过度到服务器同步的位置。同时会通过APawn::PostNetReceiveVelocity修改当前的移动速度，随后的客户端在Simulate时就可以用这个速度进行模拟。SmoothCorrection是插值的核心函数之一。（参考ACharacter的PostNetReceiveLocationAndRotation）


那么这里描述一下：SmoothCorrection到底做了什么？

SmoothCorrection：

1.Replay会直接返回，Disabled Mode会直接设置胶囊体位置

2.GetPredictionData_Client_Character客户端获取预测数据结构体，第一次会主动创建。这里面会保存一段时间内的移动数据以及时间戳，还有各种位置和旋转的偏移用于平滑

下面的平滑修改的都是Mesh相对胶囊体的偏移

3.记录一个旧坐标到新坐标的偏移NewToOldVector，同时算出一个二维的距离。如果偏移距离太大，可能不去设置偏移。如果小于MaxSmoothNetUpdateDist，就设置MeshTranslationOffset为当前的值加上NewToOldVector

void UCharacterMovementComponent::SmoothCorrection(const FVector& OldLocation, const FQuat& OldRotation, const FVector& NewLocation, const FQuat& NewRotation)
{
  //忽略其他代码
  ClientData->MeshTranslationOffset = ClientData->MeshTranslationOffset + NewToOldVector;	
}
4.如果是线性插值，先将当前的OriginalMeshTranslationOffset设置为前面刚计算的MeshTranslationOffset；设置OriginalMeshRotationOffset以及MeshRotationOffset都为OldRotation，设置MeshRotationTarget为NewRotation，设置胶囊体到新的坐标（不修改其rotation，也不修改Mesh的位置）

5.如果是指数插值，记录相对新的Rotation的MeshRotationOffset，直接同时设置胶囊体的location以及Rotation

处理时间戳

6.如果当前的客户端smooth时间戳大于服务器的，就把当前的时间戳lerp到服务器。

7.获取服务器同步的ReplicatedServerLastTransformUpdateTimeStamp，然后赋值给SmoothingServerTimeStamp

8.计算服务器两次传递数据的时间差，根据默认的配置得到一个MaxDelta

9.设置SmoothingClientTimeStamp，范围在SmoothingServerTimeStamp - MaxDelta与SmoothingServerTimeStamp之间

10.记录客户端与服务器的时间差，LastCorrectionDelta，其实可以认为服务器领先客户端的时间。同时还有一个被服务器的纠正时间LastCorrectionTime，也就是当前客户端的时间



所以这里我们就明白了前面提到的胶囊体与Mesh的移动分开处理，其目的就是提高代理模拟的流畅度。而且在官方文档上有简单的例子，

比如这种情况，一个 replicated 的状态显示当前的角色在时间为 t=0 的时刻以速度 (100, 0, 0) 移动，那么当时间更新到 t=1 的时候，这个模拟的代理将会在 X 方向移动 100 个单位，然后如果这时候服务端的角色在发送了那个 (100, 0, 0) 的 replcated 信息后立刻不动了，那么这个 replcated 信息则会使到服务端角色的位置和客户端的模拟位置处于不同的点上。
为了避免这种“突变”情况，UE采用了Mesh网格的平滑操作。胶囊体的移动正常进行，但是其对应的Mesh网格不随胶囊体移动，而要通过simulateTick的SmoothClientPosition处理。在SmoothNetUpdateTime时间内，移动组件会通过ClientData->MeshTranslationOffset去差值平滑Mesh相对胶囊体的偏移而并不会修改胶囊体的坐标，这样在通常情况下玩家在视觉上就不会觉得代理角色的位置突变。通过FScopedPreventAttachedComponentMove类可以限制某个组件暂时不跟随父类组件移动。（可参考：UCharacterMovementComponent的SmoothClientPosition_UpdateVisuals）

另外，有一点需要注意，目前模拟客户端的移动更新有几种模式，线性、指数以及replay回放，他们的差值方式不同，对角色的移动处理也有所不同。比如，线性模式就会做外插值（也就是在没有服务器数据的时候也会进行扩展插值），replay属于回放系统的处理方式，则会读取所有回放数据进行线性插值，但是没有外差值。

这里我们以常见的线性插值来做分析：

1.SmoothClientPosition是simulated客户端Tick执行的，里面包括两个重要的函数一个SmoothClientPosition_Interpolate插值函数，另一个SmoothClientPosition_UpdateVisuals应用插值更新Mesh的函数

2.在SmoothClientPosition_Interpolate里面，会用到前面的ClientData里面记录了服务器领先时间LastCorrectionDelta，客户端上次处理时间戳SmoothingClientTimeStamp，收到的服务器时间戳SmoothingServerTimeStamp

3.SmoothClientPosition_Interpolate执行Tick来更新SmoothingClientTimeStamp（+= DeltaSeconds），由于支持外插值，所以客户端运行0.15比例的外插。当客户端的时间戳大于服务器的话，就会最大外插0.15比例的offset

4.假如我们还是客户端落后与服务器，那么就会按照 DeltaSeconds/LastCorrectionDelta的比例计算插值

5.如果插值比例接近1或者大于1，就要判断一下当前的速度是否为0，为0的话就直接设置offset为0，反之就继续插值。如果比例远小于1，就正常按照比例插值。

6.由于前面一直是把数据记录在ClientData里面而没有处理，所以在SmoothClientPosition_Interpolate结束后需要调用SmoothClientPosition_UpdateVisuals真正的应用这些数据。

7.根据当前的MeshRotationOffset以及MeshTranslationOffset反向计算一个Mesh的新的相对位置，用于正确的处理位置偏移以及rotation的偏移

8.如果Rotation几乎没有变化，那么直接设置相对位置即可。如果Rotation变化比较大，那么就需要先设置前面计算的相对位置，再去设置新的rotation（这时候Mesh的Rotation会随着胶囊体一起旋转）

最后再通过下面的图理解一下就非常清晰了



Smooth平滑方式如下，默认我们采用Exponential：

/** Smoothing approach used by network interpolation for Characters. */
    UENUM(BlueprintType)

     enum class ENetworkSmoothingMode : uint8
     {
       /** No smoothing, only change position as network position updates are received. */
       Disabled     UMETA(DisplayName="Disabled"),

       /** Linear interpolation from source to target. */
       Linear           UMETA(DisplayName="Linear"),

       /** Exponential. Faster as you are further from target. */
       Exponential      UMETA(DisplayName="Exponential"),

       /** Special linear interpolation designed specifically for replays. Not intended as a selectable mode in-editor. */
       Replay           UMETA(Hidden, DisplayName="Replay"),
     };


4.4 关于物理托管后的移动
一般情况下我们是通过移动组件来控制角色的移动，不过如果给玩家角色的胶囊体（一般Mesh也是）勾选了SimulatePhysics，那么角色就会进入物理托管而不受移动组件影响，组件的同步自然也是无效了，常见的应用就是玩家结合布娃娃系统，角色死亡后表现比较自然的摔倒效果。相关代码如下：

// // UCharacterMovementComponent::TickComponent
// We don't update if simulating physics (eg ragdolls).
if (bIsSimulatingPhysics)
{
    // Update camera to ensure client gets updates even when physics move him far away from point where simulation started
    if (CharacterOwner->Role == ROLE_AutonomousProxy && IsNetMode(NM_Client))
    {
        APlayerController* PC = Cast<APlayerController>(CharacterOwner->GetController());
        APlayerCameraManager* PlayerCameraManager = (PC ? PC->PlayerCameraManager : NULL);
        if (PlayerCameraManager != NULL && PlayerCameraManager->bUseClientSideCameraUpdates)
        {
            PlayerCameraManager->bShouldSendClientSideCameraUpdate = true;
        }
    }
    return;
}
对于开启物理的Character，Simulate的客户端也是采取移动数据靠服务器同步的机制，只不过移动的数据不是服务器PerformMovement算出来的，而是从根组件的物理对象BodyInstance获取的，代码如下，

void AActor::GatherCurrentMovement()
{
    AttachmentReplication.AttachParent = nullptr;

    UPrimitiveComponent* RootPrimComp = Cast<UPrimitiveComponent>(GetRootComponent());
    if (RootPrimComp && RootPrimComp->IsSimulatingPhysics())
    {
        FRigidBodyState RBState;
        RootPrimComp->GetRigidBodyState(RBState);

        ReplicatedMovement.FillFrom(RBState, this);
        ReplicatedMovement.bRepPhysics = true;
    }
}
五．特殊移动模式的实现思路
这一章节不是详细的实现教程，只是给大家提供常见游戏玩法的一些设计思路，如果有时间的话也会考虑做一些实现案例。如果大家有什么特别的需求，欢迎提出来，可以和大家一起商讨合理的解决方案。



5.1 二段跳，多段跳的实现
其实4.14以后的版本里面已经内置了多段跳的功能，找到Character属性JumpMaxCount，就可以自由设置了。当然这个实现的效果有点简陋，只要玩家处于Falling状态就可以进行下一次跳跃。实际上常见的多段跳都是在上升的阶段才可以执行的，那我们可以在代码里加一个条件判断当前的速度方向是不是Z轴正方向，还可以对每段跳跃的速度做不同的修改。具体如何修改，前面3.2.1小结已经很详细的描述了跳跃的处理流程，大家理解了就能比较容易的实现了。



5.2 喷气式背包的实现
喷气式背包表现上来说就是玩家可以借助背包实现一个超高的跳跃，然后可以缓慢的下落，甚至是飞起来，这几个状态是受玩家操作影响的。如果玩家不操作背包，那肯定就是自然下落了。

首先我们分析一下，现有的移动状态里有没有适合的。比如说Fly，如果玩家进入飞行状态，那么角色就不会受到重力的影响，假如我在使用喷气背包时进入Flying状态，在不使用的时候切换到Falling状态，这两种情况好像可以达到效果。不过，如果玩家处于下落中，然后缓慢下落或者几乎不下落的时候，玩家应该处于Flying还是Falling？这时候突然切换状态是不是会很僵硬？

所以，最好整个过程是一个状态，处理上也会更方便一些。那我们试试Falling如何？前面的讲解里描述了Falling的整个过程，其实就是根据重力不断的去计算Z方向的速度并修改玩家位置（NewFallVelocity函数）。重写给出一个接口MyNewFallVelocity来覆盖NewFallVelocity的计算，用一个开关控制是否使用我们的接口。这样，现在我们只需要根据上层逻辑来计算出一个合理的速度即可。可以根据玩家的输入操作（类似按键时间燃料值单位燃料能量）去计算喷气背包的推动力，然后将这个推动力与重力相加，再应用到MyNewFallVelocity的计算中，基本上就可以达到效果了。

当然，真正做起来其实还会复杂很多。如果是网络游戏，你要考虑到移动的同步，在客户端角色是Simulate的情况下，你需要在SimulateTick里面也处理NewFallVelocity的计算。再者，可能还要考虑玩家在水里应该怎么处理。



5.3 爬墙的实现
爬墙这个玩法在游戏里可以说是相当常见了。刺客信条，虐杀原形，各类武侠轻功甚至很多2D游戏里面也有类似的玩法。
在UE里面，由于爬墙也是一个脱离重力的表现，而且离开墙面玩家就应该进入下落状态，所以我们可以考虑借助Flying来实现。基本思路就是：

创建一个新的移动模式 爬墙模式
在角色执行地面移动（MoveAlongFloor）的时候，一旦遇到前面的障碍，就判断当前是否能进入爬墙状态
检测条件可以有，障碍的大小，倾斜度甚至是Actor类型等等。
如果满足条件，角色就进入爬墙状态，然后根据自己的规则计算加速度与速度，其他逻辑仿照Flying处理
修改角色动画，让玩家看起来角色是在爬墙（这一部分涉及动画系统，内容比较多）
这样基本上可以实现我们想要的效果。不过有一个小问题就是，玩家的胶囊体方向实际还是竖直方向的，因此碰撞与动画表现可能有一点点差异。如果想表现的更好，也可以对整个角色进行旋转。



5.4 爬梯子的实现
梯子是竖直方向的，所以玩家只能在Z轴方向产生速度与移动，那么我们直接使用Walking状态来模拟是否可以呢？很可惜，如果不加修改的话，Walking里面默认只有水平方向的移动，只有遇到斜面的时候才会根据斜面角度产生Z轴方向的速度。那我这里给出一个建议，还是使用Flying。（Flying好像很万能）

玩家在开始爬一个梯子的时候，首先要把角色的Attach到梯子上面，同时播放响应的动画来配合。一旦玩家爬上了梯子，就应该进入了特殊的 爬梯子状态。这个状态仔细想想，其实和前面的爬墙基本上相似，不同的就是爬梯子的速度，而且玩家可以随时停止。

随时停止怎么做？两个思路：

参考Walking移动的计算，计算速度CalcVelocity的时候使用自定义的摩擦系数Friction以及刹车速度（这两个值都设置大一些）
当玩家输入结束后，也就是Accceleration=0的时候，直接设置速度为0，不执行CalcVelocity
另外，要想让爬梯子表现的进一步好一些。看起来是一格一格的爬，就需要特殊的控制。玩家每次按下按钮的时候，角色必须完整的执行一定位移的移动（一定位移大小就是每个梯子格的长度）。这里可以考虑使用根骨骼位移RootMotion，毕竟动画驱动下比较容易控制位移，不过根骨骼位移在网络条件差的情况下表现很糟。
还有一个可以进一步优化的操作，就是使玩家的手一直贴着梯子。这个需要用IK去处理，UE商城里面有一个案例可以参考一下。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》配置文件详解[原理分析]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34397162
目录
一．总体概述
二．概念须知
2.1 概念
2.2 基本原理
2.2.1 配置文件结构
2.2.2 配置文件目录分析
三．使用流程
3.1 自动配置
3.2 手动编码配置
四．配置文件的存储流程
五．原理与特性分析
5.1 配置文件的意义
5.2 配置文件的存储原理
5.3 配置文件和继承
5.4 基于每个对象实例的配置
六．其他
一．配置总体概述
UE4中，配置文件（Config）其实就是.ini文件。可以用于设置加载时要初始化的属性的值，配置信息按照键值对的格式来实现。虚幻4官方文档只有简单的使用规则，要想深入了解还需要查看源代码才行，所以这里我把自己的学习成果分享给大家。一个完整的配置文件格式如下图1-1所示。




图1-1 配置文件格式示意图


我们所见到的配置文件一般只存在于以下四个路径。

1. \Engine\Config及其子目录

2. \Engine\Saved\Config及其子目录（引擎运行后生成）

3. Projects\[ProjectName]\Config及其子目录

4. Projects\[ProjectName]\Saved\Config及其子目录（游戏项目运行后生成）

如上面所标记的，路径2与路径4的配置信息都是后生成的。



二．概念须知
为了后面的描述清晰，这里需要先简单描述一些基本原理以及一些概念。



2.1 概念
Section：如上图1-1，每个配置文件里面有很多模块，每个模块的标题就是一个section。

Flush：在代码里面，类FConfigCacheIni有一个名为Flush()的方法。它的表面意思是冲洗，奔涌，在代码里面表示将内存信息（即缓存的配置信息）准确无误的书写到文件里面。

GConfig：全局空间的一个配置缓存变量。定义如下FConfigCacheIni* GConfig =NULL;在不同的情况下存储不同的信息，如图2-1，图2-2。关于GConfig的内容后面会有较为详细的讲解。




图2-1 运行纯引擎编辑器时GConfig存储的信息
SaveConfig函数：这个函数用来将配置信息保存到GConfig并保存到文件里面。（后面会详细解释他的使用以及参数的意义）。

LoadConfig函数：这个函数用来读取配置文件的信息并将该信息赋值给当前类对应的属性。（后面会进一步解释）

UCLASS(config=FileName)：表示这个类默认条件下将配置信息保存到哪个配置文件，config后面的文件名可以是任意字符串。

UCLASS(perObjectConfig)：表示这个类的配置信息将会基于每个实例进行存储。

UCLASS(config=XXX,configdonotcheckdefaults)：表示这个类对应的配置文件不会检查XXX层级上层的DefaultXXX配置文件是否有该信息（后面会解释层级），就直接存储到Saved目录下。

UPROPERTY(config)：不指定Section的情况下，标记config的这个属性在保存到配置文件里面的时候会保存在当前类对应的Section部分。同理，加载的时候也会从当前类对应的Section下加载。

UPROPERTY(globalconfig)：不指定Section的情况下，标记config的这个属性在保存到配置文件里面的时候会保存在基类对应的Section部分。同理，加载的时候也会从基类对应的Section下加载。

注：如果这里有些内容不太理解，可以等看完后面再回头来看这些概念



2.2 基本原理


2.2.1 配置文件结构
为了对配置文件有一个整体的了解，我们必须要弄清配置文件的结构。

1. 配置分类

Compat（兼容性）
DeviceProfiles（设备概述文件）
Editor（编辑器）
EditorGameAgnostic（编辑器游戏未知的配置信息）
EditorKeyBindings（编辑器按键绑定）
EditorUserSettings（编辑器用户设置）
Engine（引擎）
Game（游戏）
Input（输入）
Lightmass（灯光构建相关）
Scalability（可扩展性）
EditorLayout（编辑器布局）
SourceControlSettings（源码控制设置，只存在于引擎和工程的Save目录）
TemplateDefs（模板定义，只存在于引擎和工程的Save目录）
上面基本描述了所有配置文件的类型，不同类型的配置设置放在不同的文件里面。当

然上面这些只是UE4为我们提供的文件类型，我们也可以定义自己的配置文件，也可以把内容放到你想放的任意一个文件里面。

在文章的最后面的附录会大致描述当前项目不同目录下配置文件存储的信息内容。



2. 文件层次结构

配置文件读入时从Base.ini开始，文件结构中后面文件内的值覆盖之前的值。Engine文

件夹中的文件将应用于所有项目，而针对特定项目的文件应该位于项目目录中的文件内。最后，所有特定项目和特定平台的差异都被保存[ProjectDirectory]/Saved/Config/[Platform]/

[Category].ini文件中。下面是配置文件的Engine类的文件层次结构示例。

① Engine/Config/Base.ini 该文件一般是空的
② Engine/Config/BaseEngine.ini
③ Engine/Config/[Platform]/[Platform]Engine.ini
④ [ProjectDirectory]/Config/DefaultEngine.ini
⑤ [ProjectDirectory]/Config/[Platform]/[Platform]Engine.ini
⑥ [ProjectDirectory]/Saved/Config/[Platform]/Engine.ini
对上面的内容作一下解释：UE4本身给系统默认的一些配置文件建立了层次结构（如Engine，Game，Editor等，这里我们称每个类型为一个层次类型）。我们在读取某种层次类型配置文件信息的时候（比如说Engine类型），会按照上面的路径依次读取，因为后面层级的内容对于项目针对性逐步增强，所以层级越高里面的配置信息优先级越高。如果路径②与路径④某项属性配置信息不同，那么我们认为路径④的信息是准确的，从而忽略路径②的该项信息。如果我们发现在SaveConfig的时候该项属性信息与路径④的对应属性信息也不同，就把该配置信息存储到路径⑥下面。

同时要注意到UE4提供的这些基本配置文件的名称是固定的（中括号的除外），如果随意删除或者修改这些配置文件的名称就会导致层级信息缺失。

不过我们可以利用UE4的层级系统将配置信息存储到这些文件，也可以自己创建新的配置文件。下一条原理2.2.1会对这里做进一步的阐述。



2.2.1 配置文件目录分析
在总体概述里面，我们简单的描述了配置文件的目录，这里要拿出来作进一步分析。

我们所见到的配置文件一般只存在于以下四个路径。

\Engine\Config及其子目录
\Engine\Saved\Config及其子目录（引擎运行后生成）
Projects\[ProjectName]\Config及其子目录
Projects\[ProjectName]\Saved\Config及其子目录（游戏项目运行后生成）
下面先给出4个目录下的文件内容，作一个直观的了解，同时请大家牢牢记住这4个路径以及其对应的编号，后面会多次提到。



图2-2 Engine目录下配置文件的对比图（路径1与2）


图2-3 Project目录下配置文件的对比图（路径3与4）
那么这四个目录之间的关系是什么，有什么作用？

首先我们要知道路径1与路径3中的配置文件在引擎在运行的时候是不会生成的，所以这里面的文件以及信息需要你手动的添加，当然引擎路径1的配置文件都已经写好了一般不需要改动

但是当你新建一个空白项目时，引擎会为你在路径3里自动生成DefaultEngine.ini以及DefaultGame.ini 还可能会生成DefaultEditor.ini，如果使用提供的模板，同时还会生成DefaultEditor.ini和 DefaultInput.ini 配置文件
根据我上面给出的对比图，我们可以把引擎和项目分开来看。当你只是打开一个纯引擎的编辑器时，与项目是没有任何关系的。引擎会根据自身的代码逻辑以及路径1中的配置信息来生成路径2中的配置信息。同理，我们在运行工程的时候也会根据代码逻辑和路径3的配置信息来生成路径4的配置信息，不过有一点区别。因为我们刚刚看了原理2.2.1的文件层次结构，所以应该明白工程的配置文件（路径4下的）生成还与路径1中的引擎配置文件有间接关系（与路径2的无关系）。

另外，我们在上面对比的其实是路径3与路径4\windows，而路径4下的结构一般是下面这样的，除了平台文件夹还会有一个CleanSourceConfigs文件夹。




图2-4 Projects\[ProjectName]\Saved\Config目录结构图
我们生成的信息分布在这两个文件夹，CleanSource文件夹里面其实就是路径1和路径3配置信息的总和（也就是文件层次结构⑥之前的配置信息），其他与游戏本身，与平台相关的差异配置信息会最终存储到Windows（对应的平台）目录下。

总结一下，无论是引擎还是项目，在Config下的配置信息都是手动添加的，而Save/Config下的都是引擎或项目运行后生成的。

注意：如果删除了工程下的DefaultEngine.ini，会导致工程无法运行，提示如下的错误。（这表示Engine目录下的配置必须要有 [URL] GameName=ProjectName）。


图2-5 丢失DefaultEngine.ini的报错示意图
2.2.3 存储原理
配置文件的存储通过一个全局的变量GConfig来实现，GConfig是FConfigIni（配置信息缓存类）的一个实例化对象。他在程序启动时会加载所有的配置信息并保存在自身当中。我们通过修改该变量里面的信息并执行相关操作来完成配置信息的修改与保存。


图2-6
三．使用流程


3.1 SaveConfig与LoadConfig的使用
想正确的保存配置信息，就必须使用到SaveConfig()函数。不过这个函数在使用上有几点要注意，否则你可能在配置文件里面找不到你想存储的数据。




图3-1 SaveConfig的定义图
SaveConfig函数是UObject的一个方法，这就表示所有继承于UObject的类都可以使用它。根据图我们看到该函数有三个参数，第三个参数默认是GConfig（后面会讲到这个全局变量），一般不做修改。第一个参数默认是CPF_Config，我们也可以指定为CPF_GlobalConfig。表示我们要保存的是标记Config的属性还是标记Global的属性。

第二个参数要重点强调，他表示带有路径的文件名称，如果我们不写该参数，那么SaveConfig就会找到当前调用他的类的UCLASS(Config=XXX)所标记的这个XXX文件，并将信息保存到这个文件。如果我们给出了第二个参数，他就将信息保存到对应参数的文件里面。




图3-2 LoadConfig的定义图
LoadConfig的功能是从配置文件里面读取特定的属性值并赋给指定类的对应属性。第一个参数指定了要把值赋给哪个类的属性，第二个参数表示到哪个配置文件找对应的配置信息，第三个参数表示是哪种标记（Config还是GlobalConfig），第四个参数表示指定要赋值的属性。

如果不指定第4个参数，就会读取配置并给所有标记UProperty(Config)的属性赋值。

注：在后面的原理解析，会进一步的分析这两个函数。
3.2 自动配置
在UE4里面，我们利用引擎提供的特性，只需简单做一下配置就可以轻松实现配置信息的保存与读取。基本流程如下所示：


图3-3 自动实现属性配置流程图
1. 为指出应该从哪个配置文件中读取哪个变量，那么在包含这些变量的类的UCLASS

宏中应赋予Config标识符。




注意：必须为 Config 标识符提供类别（比如Game（游戏））。这确定了从哪个配置文件中读取类的变量及将其保存到哪个配置文件中。所有可能的分类都在类ConfigCacheIni（实际是GConfig对象）中进行定义。所有配置文件的分类列表在第二部分里面已经描述。
2. 要想指定读取和保存到配置文件中的某个变量，也必须为该属性UPROPERTY()宏提供Config标识符。如下图所示


对属性的Config标识符不提供任何分类。ExampleVariable属性现在可以从配置文件结构（第二部分有描述）的任意Game配置文件中读取， 只要信息由以下语法所指定（这里面的ModuleName指的是包Package，也可以理解为项目具体代码所在的文件夹名称 /Source下面的，ExampleClass就是对应的类名。）


3. 这一步在官方文档上说的很模糊。如果你只按照上面两个步骤做，就会发现，对应的配置文件里面还是没有你想要的变量。因为在引擎执行SaveConfig的时候会遍历一遍所有的标记Config的属性，判断当前对象的config属性是否与同属一类CDO的相同属性的值相同，如果相同证明没有任何修改，也就没有必要存储到配置文件里面去。

所以这里我们有两种办法修改属性的值，一是在一个方法里面修改该config属性的值，然后在游戏开始的时候调用。另一种是将这个config属性设置为蓝图可读写，在蓝图配置里面修改。最后，在这些修改操作执行之后一定要调用SaveConfig来保存配置信息（根据3.1的讲解，这里的SaveConfig我们一般不填第二个参数），同时就会将信息写到配置文件里面。如果上面的工作你都做了，但是没有执行SaveConfig是不会有任何效果的。

注：CDO即ClassDefaultObject。这涉及UE4每个对象的内部结构，系统在运行时会默认构造一个该类的对象，这个对象只执行了构造函数。下面图3-2给出一个CDO与当前实际对象的内部结构对比。


3.3 手动编码配置
除了上面描述的半自动配置的方法，我们也可以通过硬编码让配置信息保存到任意的文件里面。这里我们还是必须要用到SaveConfig函数，不过要设置好正确的参数。前面介绍过，SaveConfig()函数是UObejct方法，可以在任意继承于UObject并使用配置类修饰符的类上进行调用。一般来说，只要是借助UProperty并且调用由SaveConfig()实现自动保存的，保存的变量就会位于按照格式 [(package).(classname)] 命名的Section中。

例如，bDisableAILogging属性是Engine类的一个标记Config的UProperty属性，保存后就会位于DefaultEngine.ini 中的[/Script/Engine.Engine] 下面。




图3-4引擎目录下的Engine包


下面举例在GameMode中如何使用手动编码将信息保存到指定的位置。

1. 获取到全局的GConfig然后执行GConfig->SetBool(SectionStr,OptionStr,Value, GGameUserSettings); 操作，将该bool变量写到GConfig里面。当然引擎还提供了Set String，Integer，float等类型的配置变量。（SectionStr表示Section名称，OptionStr表示键值对的Key值）



2. 然后在GameMode初始化阶段，或者其他合适的位置执行步骤1并调用SaveConfig保存。

GGameUserSettingsIni是全局的FString，保存的是GameUserSetting配置文件的路径，所以这里我们就可以把GameMode的配置信息保存到GameUserSetting里面了。其他的配置文件路径对于的变量可以在Core.cpp里面搜索到。


这里要说明一下，GGameUserSettingsIni是全局的FString，保存的是最高层级的GameUserSetting配置文件的路径。其他的配置文件路径对应的变量可以在Core.cpp里面搜索到。引擎在运行的时候会自动的帮我们给这些路径赋值（见图3-7,3-8）。


图3-5保存不同配置文件路径的全局变量

图3-6 初始化配置文件路径的流程图
3.4 读取自定义文件并建立对应的层次结构
前面借助UCLASS等宏可以在Saved/Config目录下生产我们自定义名称的配置文件。但是如果我想在Project/Config下面建立自己的DefaultXXX.ini文件，如何读取并同样建立一个层次关系结构呢。比如想读取下图的DefaultConfig文件，


图3-7建立自定义配置文件
我们可以在合适的位置（GameInstance，GameMode，或者引擎的InitializeConfigSystem）调用FConfigCacheIni::LoadGlobalIniFile(GConfigIni, TEXT("Config"), NULL, NULL, true);函数。

之后代码就会给“Config”名称的文件建立一个层次结构，并在Saved/Config生成一个Config.ini文件。这里的GConfigIni是我们定义的全局路径，方便我们随时获取这个Config文件的位置。



四．配置文件的存储流程
前面我们已经介绍了配置文件的使用流程，也知道了自动配置和手动配置上流程的差异，这里用流程图简单梳理一下。如图4-1,4-2。




图4-1自动配置信息一般存储流程图

图4-2手动配置信息一般存储流程图
注：SaveConfig是UObject的方法，可以在任何标记Config的子类上调用。




五．原理与特性分析


5.1 配置文件的意义
在刚接触配置文件的时候，我最大的疑问就是配置文件一般是用来读的，为什么要生成这么多的配置文件以及信息？

这里可以这样理解：

第一次运行游戏项目，引擎会首先读取引擎目录\Config，游戏目录\Config里面的配置信息，以及配置文件路径（运行游戏时的配置路径就是[ProjectDirectory]/Saved/Config/[Platform]/）存储到GConfig里面。然后其他的配置信息会在各个模块执行其SaveConfig()的时候写到GConfig（前面有简单的描述）最后通过GConfig写到生成的配置文件里面。（注：这里生成的文件是指Projects\[ProjectName]\Saved\Config及其子目录，第二章节有讲解）

而第二次运行时，因为之前已经生成了配置文件。引擎首先会把所有的配置文件里面的数据读入到GConfig里面（包括第一次运行生成的），然后如果发现配置文件信息有遗漏或者有改动，就在执行SaveConfig()的时候再次写入到GConfig里面，同时再写到路径4（见2.2.1章节）配置文件里面。

通过上面，我们可以知道。其实我们修改后来生成的配置信息是没什么意义的，因为每次游戏运行的时候我们都想把配置信息存储成我们在代码或者工程想要的样子。这部分生成的配置信息我们可以在游戏运行后读取并加以利用。不过我们可以修改路径3（见2.2.1章节，工程默认配置）里面的信息，这里面的信息是我们想修改后就会立刻生效的。如果你事先把所有信息都写在了路径3下面，就会发现路径4里面的配置信息没有任何内容了。



5.2 配置文件的存储原理
GConfig前面已经出现了多次，我们有必要了解一下GConfig到底是什么。其实，GConfig就是一个配置信息缓存量，在运行时里面会一直保存所有的配置信息。

下面是GConfig所属的类以及继承关系图。




图5-1 GConfig继承关系图
从上面的图我们可以看出，GConfig可以说是一个三层结构的Map（最底层为MultiMap），依次存储了配置路径，配置section，配置属性与值。详细的结构我们可以通过下图来进一步了解。


图5-2 GConfig内容结构解析图
这里需要对FConfigFile这个类型做一下解释。从上面两个图可以看出，一个配置文件FConfigFile类由5个成员构成，这个5个成员可以解释前面的很多规则与现象

1.FName 记录这个配置文件的类型

2.SourceIniHierarchy 就如我们在第二章节2.2.1所说明的，这个成员变量描述了文件的层级结构，根据这个结构我们最后的差异信息才会存储到\Windows下面

3.SourceConfigFile 表示从本地最开始加载的配置内容（其实就是加载第二章节2.2.2中所说的路径1和路径4里面的配置信息）

4.dirty 文件是否被修改，在写文件的时候，如果这个值为False就不会重写配置文件

5.NoSave文件是否没有保存



5.2.2 UCLASS与UProperty中的Config解析
在自动配置中，我们通过UCLASS与UProperty宏里面添加Config来实现。这里就涉及到了UE4的反射系统，我们简单描述一下。

引擎编译是UBT（UnrealBuildTool）来控制的。首先调用UHT（UnrealHeaderTool）解析各个类中的UCLASS这样的宏，并生成对应的.generate.h以及.generate.cpp文件，这些文件代码都是宏，用来实现诸多有关UObject的功能。其次，才会调用C++的编译器来进行编译。

通上面的步骤会给每个UObject类型都绑定了一个Class类，同时注册所有Uproperty与UFunction，所有标记UProperty的属性会以链表的形式保存到这个Class类里面。然后我们可以通过GetClass()->PropertyLink方法可以获取到这个链表，HasAnyPropertyFlags可以判断当前属性是否有Config标记。通过对标记的处理我们可以判断是哪种标记，进而再判断当前对象的该属性值与对应的CDO属性值是否相同，最后就完成了SaveConfig中的判断流程。

对于UCLASS，我们可以在SaveConfig看到，如果没有给第二个参数指定文件名称，就会执行GetConfigFilename（this），然后通过这个函数来获取到他绑定Class的ClassConfigName。这个ClassConfigName也是通过反射系统来实现的。


图5-3 SaveConfig部分实现图

图5-4 反射部分相关类的继承关系图
5.3 配置文件和继承
Config UCLASS和UPROPERTY标识符都将被子类继承。这表示子类可以读取或保存父类中指定为Config的所有变量，并且它们将会位于相同的配置文件分类中。变量都会位于具有子类名称的部分下。例如，继承 ExampleClass 的 ChildExampleClass 的配置文件信息看起来如下方的代码行，并且将被保存在同一个Config配置文件中。

子类无法否定继承父类的Config标志，但是子类可以通过重新声明config 关键字并指定一个不同的文件名来更改这个.ini文件。


5-5 基于每个对象实例的配置
虚幻引擎 4 可以把一个对象的配置信息保存到任何所需的配置文件中。如果 PerObjectConfig 标识符用于 UCLASS 宏，那么这个类的配置信息将会基于每个对象实例进行存储，其中每个对象实例在.ini文件中都有一部分，该文件以这个对象的名字命名，格式如下 [ObjectName ClassName] 。 这个关键字会传递给子类。

这样的例子可以参考UDeviceProfile类，它的前置宏为UCLASS(config=DeviceProfiles, perobjectconfig, Blueprintable)。表示会产生名称为DeviceProfile.ini的配置文件，并且里面的信息如下所示。

[XboxOne DeviceProfile]
Key=Value
[iPhone5S DeviceProfile]
Key=Value
里面的代码细节其实就是在执行SaveConfig的时候，会判断这个当前对象是否用PerObjectConfig 进行标记，是的话就为这个对象单独标记一个配置信息（如Section = L" iPhone5S DeviceProfile "），否则就统一标记到这个类里面（如Section = L"/Script/

UdpMessaging.UdpMessagingSettings"）。



六．其他
1.配置文件的生成要远比内容写入早的多，如果是第一次运行，在工程运行的一开始就会通过GenerateDestIniFile生成空的配置文件。

2. FPaths包含了游戏工程的各种目录路径，如EngineDir，GameSavedDir，GameContentDir等，这对于配置信息的存储路径很重要。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》流关卡与无缝地图切换[经验总结]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34397446
目录
一．Level Streaming的使用与注意
1.流关卡的使用与注意
2.世界构成器 World Composition

二．地图切换流程分析
1.ClientTravel
2.ServerTravel
3.Browse

三．无缝地图切换
1.无缝切换流程
2.无缝切换时保存Actor
3.无缝切换时的一些问题与解决方法


一．Level Streaming的使用与注意
流关卡顾名思义，即关卡数据可以以数据流的形式加载到游戏中，这个过程就像加载其他的角色数据一样，非常平稳，对当前的关卡没有影响。具体的表现效果就是，当你在场景A中向场景B行走的时候，B场景会在你事先指定好的地点（或者其他条件）加载进来，而你感觉不到B场景的加载过程，好像原来B场景就存在一样，这样玩家就会觉得仿佛置身于一个大场景一样。

（注意：你可以把流关卡理解成一种“无缝加载”，但是这与UE里面官方文档里面的无缝加载并不是同一个东西，具体的差异在讲无缝加载时再分析）



1.1 流关卡的使用与注意
UE4官方文档关于流关卡的使用介绍的已经很详细，我这里只是就部分重要步骤做描述与讲解。
在UE4里面，每一个World里面至少有一个PersistentLevel以及0-N个StreamingLevels。在编辑器里面通过Windows—Levels窗口即可查看。在下面图1-1我们可以看到当前World里面只存在一个Persistentlevel，这个Persistentlevel就是当前我们打开的level。


图1-1

图1-2
通过Levels窗口我们可以开始创建流关卡了，点击Levels按钮，可以创建新的level或者是添加已经存在的level。对于添加进来的流关卡，我们可以设置其是和persistentlevel一起永久加载（alwaysloaded）还是在自定义条件下再加载。如图1-3


图1-3
控制流关卡的加载总体上来说有两种方式，一种是通过关卡流体积控制（LevelStreamingVolume），另一种是通过脚本（代码）逻辑控制。简单描述一下两个方法，第一种，LevelStreamingVolume相当于一个定制的触发器，当玩家摄像机（注意是玩家摄像机）进入LevelStreamingVolume体积内的时候，对应的流关卡就会加载（对应关系是通过下图操作设置的 点击levels旁边的按钮打开leveldetails窗口 inspectlevel找到需要加载的流关卡添加对应的LevelStreamingVolume）。第二种，就更随意了，你代码想怎么写就怎么写，简单的方式就是设一个触发器在玩家进入触发器的时候调用LoadStreamLevel，具体的教程的参考官方文档。


图1-4



图1-5
1.2 世界构成器 World Composition
流关卡给我们提供了一个大世界的解决方案，但是实际操作上由于每个level关卡都可能非常大，我们在编辑器里面一点点调整流关卡里面的Actor位置实在是过于麻烦，所以UE提供了世界构成器功能，简单来说就是帮你把N个关卡用拼图的形式拼接成一个大世界地图。
想使用这个功能，首先你需要在当前的WorldSetting里面勾选 Enable World Composition （这个有个小tips，如果当前你的world里面已经添加了子关卡，那么是无法开启该功能的）。当你开启该功能的时候他会弹出一个界面提示你将会把同一个文件夹内的所有level作为当前persistent level的流关卡，点击OK即可。


图1-6
这时候新加入的流关卡并没有激活，所以是灰色的。右键该地图选择Load选项，就会把NewMap加入当前的level里面，此时在编辑器里面你就可以看到子关卡的物件了。


图1-7
这时候有一个问题，你发现无论怎么设置，运行游戏的时候NewMap都会和Persistent Level一同加载到当前的Level里面。这是为什么呢？因为世界构成器默认的加载逻辑就是当玩家距离要加载的关卡满足一定数值时就会加载对应的子关卡。而由于你刚把NewMap加载到当前的World里面，没有设置地图拼图，所以NewMap的默认位置就是当前世界的原点位置，满足默认距离50000（500米），所以一开始运行的时候就会加载进来。
所以接下来，我们要去设置地图拼图。设置完世界构成器之后你会发现level界面多了一个按钮，点击这个按钮就打开了世界构成器的界面。官方文档上长的是这样的（图1-8）


图1-8



图1-9
然而当你满怀激动打开后却发现是这样的（如图1-9）？？？怎么啥都没有，我有场景的啊，这个箭头是什么意思？不要急，首先你可以先滑动鼠标滑轮，滑到最大。相比刚才，你会看到一个黄色的框，没错，这个框就是当前地图的选择框。然后，你去Load刚才新加入的NewMap，这时候你会发现大不相同了（如图1-10）


图1-10



图1-11
这个白栏框就是你的NewMap地图。前面说的那个箭头表示你当前摄像机所在的位置，可以看到当前的NewMap的尺寸是1638400*1638400，他的StreamingDistance是50000cm。现在我把NewMap的位置从中心向右侧移动一段距离（超过500米），点击运行游戏。会发现NewMap这回没有加载，然后控制角色向NewMap地图靠近。当满足条件时，NewMap被加载到当前关卡里面。（参考图1-11,1-12）


图1-12 未加载NewMap时



图1-13 加载NewMap时（NewMap光照不同，光照有变化，说明NewMap加载了）
解决完上面的问题，新的问题又出现了，我的场景明明很小，为什么在这个WorldComposition界面里面这么大？答案就是因为你的level里面有巨大的天空盒（sky sphere），也就是拼图中的白色部分。所以你可能立刻想到去修改天空盒的大小（修改Scale）,这个方法没什么问题。不过一般来说，天空盒是不需要调整的，所以这里有第二个办法，修改WorldComposition的相关属性。


图1-14
当我们在WorldSettings里面勾选EnableWorldComposition的时候，引擎会帮助我们在World里面创建一个新的Actor，这个Actor的默认名字是LevelBounds（图1-14），通过去掉AutoUpdateBounds属性并重新设置Scale大小，就可以自定义level的大小了。


图1-15
在使用拼图的功能时，我们还看到有一个图层功能，用来给各个关卡分类。点击“+”，可以创建新的图层，可以点自定义Streamingdistance。如果想把一个level添加到一个图层里面，需要右键这个level——AssignToLayer（图1-16）


图1-16



图1-17
最后提一点，关卡也可以添加Lod信息，但是需要Simplygon软件提供支持。

二．地图切换流程分析
上一章节从使用角度讲解了流关卡在UE里面的应用，虽然他看起来是一种“无缝地图”，但并不是UE官方所指的无缝，UE真正的无缝是指多人游戏时关卡切换客户端不断开与服务器的链接。而在讲解无缝地图切换前有必要先分析一下一般的地图切换流程，在官方文档——多人游戏中的关卡切换这一章节中，由于其讲解的不够详细可能对读者产生一些误导。

（这一章节会涉及到UE底层的一些代码逻辑，如果只是为了了解无缝链接的使用，可以有选择性的泛读一下）



首先，下面是关于地图切换相关类的类图，关键的函数也记录在了类里面。先对涉及到类有一个大致的印象，后面讲解的过程中也可以会头再看看这张类图。（关于WorldContext与World这些类之间的关系，建议先参考大钊先生的文章—— 《InsideUE4》GamePlay架构（二）Level和World 《InsideUE4》GamePlay架构（三）WorldContext，GameInstance，Engine 这里不会详细介绍。


图2-1
关于地图切换，仔细分个类的话，无非就是下面几种情况：

客户端断开链接自行切换地图，服务器地图不变
客户端断开链接加入新的服务器地图，原服务器地图不变
服务器切换地图，客户端跟随服务器切换地图
客户端，服务器都断开链接，各自切换到自己的新地图
而这几种情况都是通过ClientTravel，ServerTravel，Browse等调用来实现的，下面从各个接口着手分析上面的几种情况。



2.1 ClientTravel
这里的ClientTravel不是专门指接口APlayerController：：ClientTravel。而是指UEngine：：SetClientTravel。


官方文档上这一点描述有问题，原文是：APlayerController：：ClientTravel如果从客户端调用，则转移到新的服务器；如果从服务器调用，则要求特定客户端转移到新地图（但仍然连接到当前服务器）。
而实际上无论是客户端还是服务器调用这个接口，最后的效果都是一样的，都是通过RPC让客户端去调用 ClientTravelInternal_Implementation，让客户端转移到新的服务器的地图上。可以通过下面的方法测试：

新建一个第三人称模板的C++项目，在新创建的第三人称的Character里面添加一个BlueprintCallable函数如下。
UFUNCTION(BlueprintCallable, Category = “Level”)
void CharacterClientTavel(const FString& URL, enum ETravelType TravelType, bool bSeamless = false);
void ALevelTestCharacter::CharacterClientTavel(const FString& URL, ETravelType TravelType, bool bSeamless)
{
if (Controller && Cast(Controller))
{
Cast(Controller)->ClientTravel(URL, TravelType, bSeamless);
}
}
场景里面放置一个TriggerVolume，然后在第三人称的Character添加一个Overlap事件。

图2-2
按照我的方法测试完之后，大家可以回头再看一下ClientTravel里面的参数。
关于ClientTravel里面的URL以及TravelType参数，其实都很有讲究。简单来说，这个地方可以填写路径，地图名称，IP地址，端口（前面加冒号）等信息。这些信息只要格式正确，就会被识别并放到各个成员变量里面（图2-3）


图2-3
这里我只是简单的添加了一个地图名称，在运行的时候，执行端就会从本地文件夹里面搜索到这个地图并进行加载（并不一定会加载成功）。注意，如果他是一个纯客户端，在执行ClientTravel的时候URL只输入地图而不输入IP，而且TravelType是Relative，他就会加入本地默认的7777端口的服务器，并且服务器会在Welcome的消息里面返回正确的地图信息来纠正客户端。这样客户端可能就是重新加入了一次服务器。在这个过程中，客户端会清空NetDriver，重新生成PendingNetGame。通过TickWorldTravel 执行Browse来与服务器重新建立链接并重新打开地图（流程图见2-4）。如果他在URL里面输入了IP以及端口信息，那么他就会从当前服务器断开并Travel到目标地址的服务器上去，而这个就是ClientTravel负责完成的主要功能。想实现这个功能其实还有两个办法，一是就是在控制台命令里面输入 open 127.0.0.1:7777（假如服务器开在本地），你的客户端也会Travel到目标地址的服务器上。二是调用全局的static接口UGameplayStatics::OpenLevel。不论哪种方式，本质上都是调用引擎的UEngine：：SetClientTravel（UPendingNetGame*…）函数。

（注：UE默认端口是7777，多开的服务器进程端口会在7777上面累加，想查看端口占用Windows打开cmd，输入netstat -an即可）






图2-4 ClientTravel流程图（建议结合类图理解）



图2-5 控制台Open命令调用堆栈
上面的流程中，我们提到TravelType需要设置为Relative，这是为什么？我们要知道TravelType表示地图切换的方式，是相对上次的URL切换，还是完全按照当前绝对的URL切换。在执行SetClientTravel的时候会把TravelType赋值给WorldContext 的TravelType 。而这个TravelType会影响URL的创建。如果TravelType是Relative，URL就会设置Protocol，Host为原来的URL里面的对应信息。如果TravelType是Absolute，Host IP端口等信息就完全按照传入的URL设置，可能就是空的（因为我们只传入了一个地图名称）。如果当前Travel的URL没有任何IP信息，引擎就会把这个URL当成本地全局的URL（也就是不受服务器控制），因此客户端就可以自行打开一个地图。这就会造成与上面ClientTravel执行结果完全不同。
不过说实话，这样的操作没什么意义，因为一旦客户端自行加载了一个地图，而服务器没有加载，那就是客户端自己去另一个地图玩了，自己当自己的服务器，断开与原来服务器的链接，NetDriver设置为空，服务器也失去了与客户端的链接管理。下面代码是URL初始化时候根据TravelType的不同而做出不同的操作。

if( Type==TRAVEL_Relative )
    {
        check(Base);
        Protocol = Base->Protocol;
        Host     = Base->Host;
        Map      = Base->Map;
        Portal   = Base->Portal;
        Port     = Base->Port;
    }
    if( Type==TRAVEL_Relative || Type==TRAVEL_Partial )
    {
        check(Base);
        for( int32 i=0; i<Base->Op.Num(); i++ )
        {
            new(Op)FString(Base->Op[i]);
        }
    }
说了这么多，总结一句，ClientTravel的主要目的就是将客户端从一个服务器迁移到另一个服务器（也可以重新加入当前的服务器）。这个过程一定是要断开链接的（关于无缝操作下个章节再去讲）。而官方文档的第二个作用在我这里一直无法得到解释，暂时认为他是有问题的。



2.2 ServerTravel
讲解完了ClientTravel，ServerTravel也就相对容易一些了。UEngine::ServerTravel的主要功能就是让服务器去加载新的地图并且通知所有他连接下的客户端都跟着他进入到新的地图去（只能在客户端运行）。同样，ServerTravel也可以设置Relative还是Absolute，不过影响不大了，但是注意URL里面不要填写IP地址了，因为他的功能就是在本地切换地图，所以不需要添加IP地址相关信息（会崩溃）。服务器是首先需要自己加载地图，然后通知客户端执行SetClientTravel跟随服务器切换level，随后读取服务器发送的WelcomMessage消息并正确的加载响应的地图。执行完ServerTravel后，GameMode等所有Actor都应该是重新生成的，旧场景的对象会被在执行LoadMap时被垃圾回收掉。

在编辑器里面，总有一些表现可能比较奇怪。比如，编辑器下执行ServerTravelURL里面只填写地图名称会发现执行后发现客户端会卡主。其实是因为下面的代码，编辑器的GIsClient属性为true（正常一个DedicateServer一定为false），导致服务器在LoadMap的时候不能正常初始化监听的NetDriver，因此客户端无法与服务器建立连接而一直处于Pending状态。表现上就是客户端角色卡主的效果。

// Listen for clients.
    if (Pending == NULL && (!GIsClient || URL.HasOption(TEXT("Listen"))))
    {
        if (!WorldContext.World()->Listen(URL))
        {
            UE_LOG(LogNet, Error, TEXT("LoadMap: failed to Listen(%s)"), *URL.ToString());
        }
    }
另外，服务器初始化NetDriver必须通过UWorld::Listen。Listen函数在两个地方都会执行，一个是编辑器里面UGameInstance::StartPIEGameInstance。另一个是在服务器执行UEngine::LoadMap(）的时候。
（ServerTravel里面的URL不能带有符号 “%” , “:” , “\” ）

2.3 Browse
这个函数前面没有重点描述，但其实每次调用ClientTravel以及ServerTravel的时候都一定会用到（前提是不勾选无缝切换）。官方文档给出描述是Browse就像是加载新地图的硬重置，一定会断开客户端与服务器的连接，导致非无缝的切换。因为这里面会重置客户端的NetDriver，创建UPendingNetGame并进行相关初始化。所以，只要我们没有勾选无缝切换地图的选项，就一定会执行该操作。

最后再回头看一下前面说的几种切换地图的方式，应该就比较清晰了：

客户端断开链接自行切换地图，服务器地图不变
APlayerController：：ClientTravel 未设置IP Absolute
客户端断开链接加入新的服务器地图，原服务器地图不变
APlayerController：：ClientTravel 未设置IP（或者设置了IP） Relative
服务器切换地图，客户端跟随服务器切换地图
UWorld：：ServerTravel 只设置地图信息
客户端，服务器都断开链接，各自切换到自己的新地图
先执行情况1，再执行情况3
三．无缝地图切换
说了这么多，终于讲到无缝切换了。根据上面的讲解，现在大家应该已经了解了无缝切换的真正含义了——在不断开连接的情况下切换地图（注意：相当于切换PersistentLevel，不是加载子关卡）。仔细分析一下，这个定义里面其实是包含隐含条件的，如果客户端想切换地图，那么肯定是服务器先切换的地图，否则客户端无法在一个与服务器不同地图且保持连接的情况下正常游戏。如果是客户端从一个服务器切换到另一个服务器，那就更不用说了，必须重新建立到新服务器的连接。

所以无缝切换的正常情况只有一种：服务器切换地图，客户端与服务器在保持连接的情况下也跟着切换地图。（也就是上一章节的第三种切换地图的方式+保持连接不断）。无缝加载的使用情景类似于一个房间服务器，玩家们从A场景完成一项任务或者结束一次比赛后重新开始新的任务或比赛。而前面的流关卡更偏向与RPG式的大地图探索。

首先我们先考虑一种不合理的情况来加深理解：直接调用ClientTravel。可以看到ClientTravel的定义void APlayerController::ClientTravel(const FString& URL, ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid)。这里面有URL，TravelType以及是否无缝bSeamless。看起来参数很齐全啊，是不是直接调用就可以了呢？假如我们编辑器勾选Dedicate，URL为本地的一个新地图NewMap（当前是ThirdPersonExampleMap）勾选bSeamless，TravelType同时为Relative。这时候我们运行游戏并触发ClientTravel函数（参考第二章节的例子），你会发现客户端在不断开连接的情况下好像成功的进入了NewMap，但是有两个很严重的问题，第一个是服务器仍然是原地图，所以你的客户端里面的很多数据（物理数据等）都是不匹配的；第二个问题是，你的原地图的各种Actor很快就会被垃圾回收掉，然后你在新地图里什么也做不了了。

第二个问题是正常的，因为在无缝连接的进行时没有处理的Actor就会被删除，稍后我们再讲解。但是第一个问题是致命的，你的客户端在保持连接的情况下进入了一个与服务器不一样的地图，那可想而知，玩起来肯定到处是Bug。我举这个例子的原因就是想说——不要直接调用ClientTravel！如果你理解客户端与服务器之间的关系，你就会明白，二者必须要保持一致，所以只在客户端去执行无缝Travel是不合法的操作。正确的方式应该让服务器去调用ServerTravel同时勾选GameMode里面的UseSeamlessTravel（如果在编辑器里面操作，你需要一个继承当前GameMode的蓝图并在这个蓝图里面修改UseSeamlessTravel属性）。另外，需要提示你的是，编辑器模式下不支持SeamlessTravel。启用无缝切换，需要通过 UGameMapsSettings::TransitionMap 属性配置一个过度地图。该属性默认为空，不配置的话就会默认为过渡地图创建一个空地图。



3.1 无缝切换流程
无缝切换不会走Browse函数，自然也就不会断开连接，开启无缝后。整套切换流程有很大的变化，值得注意的是travel过程当中有一个过度地图TransitionMap ，所以先要把相关的Actor保存到TransitionMap ，再从TransitionMap 保存到目标场景中去。流程如下图3-1：


图3-1无缝切换流程图

图3-2客户端收到服务器通知执行无缝切换
3.2 无缝切换时保存Actor
前面提到无缝切换时会导致原来地图的Actor被删除，很多前后时候我们不想这样。UE默认会保存一些Actor，不过经过测试有一些与官方文档描述不符或者是理解上容易有歧义，我在下面标记了一下：

GameMode （服务器） （实际上默认GameMode并不会传递到新场景）
拥有一个有效的 PlayerState 的所有控制器（服务器）（其实还包括PlayerState本身）
所有 PlayerControllers （服务器）需要保证你的GameMode继承自GameMode类而且两个地图的PlayerController类型相同才行
所有本地 PlayerControllers （服务器和客户端）
如果我们想额外的保存其他Actor有两个函数处理：

通过 AGameMode::GetSeamlessTravelActorList 额外添加的任何Actor（服务器）
通过 APlayerController::GetSeamlessTravelActorList （在本地PlayerControllers上调用）额外添加的任何Actor（非专有服务器与客户端）
（具体的保存了流程与细节参考函数FSeamlessTravelHandler::Tick）


3.3 无缝切换时的一些问题与解决方法
a.我们知道无缝切换会保持链接，那他是如何保持链接的呢？

答：无缝切换通过一个FSeamlessTravelHandler类Tick操作覆盖了原本的Browse操作，这个过程中不会直接释放地图资源，而是通过一定机制将Map数据通过拷贝进行转移，可以看到在函数FSeamlessTravelHandler::CopyWorldData里面会将当前的World的NetDriver赋值给要加载的World，从而保持了连接不断。当然Map里面数据非常多，迁移要考虑的非常周到，具体细节还要跟随代码仔细查看。

b.在服务器无缝切换到新场景后，新连入的客户端会先跳到原来服务器的场景，再加入到新的场景，这个怎么处理？

答：这是因为游戏运行过程中始终需要一个场景，因为在Game.ini文件里面配置了默认场景。客户端在一开始运行时会先打开默认的场景，然后发送连接到服务器的请求，服务器确认后才能加载新的地图。为了避免这个情况，可以给其设置一个默认的空场景，这个场景只显示加载的过场动画。

c.调试的时候，有时候发现与正常操作不一样？

答：调试的时候，如果中断时间过长可能导致链接超时关闭，所以要仔细阅读服务器日志信息多次测试后再下定结论。如果想控制连接关闭时间或者设置为一直保持连接，可以在Engine/Config文件夹下找到BaseEngine.ini配置文件在里面搜索关键字[/Script/OnlineSubsystemUtils.IpNetDriver]（如下图3-3）
自定义ConnectionTimeOut连接断开时间 或者 设置bNoTimeOut为true，不断开连接。


图3-3 BaseEngine.ini
d.在APlayerController::GetSeamlessTravelActorList函数里面添加了当前控制的Actor，但是在无缝切换后并没有Travel过去？？

答：我测试也是这样，跟了一下代码，发现官方文档描述的确实过于简单了，很多细节都没有交代。首先，你要确认你当前控制的Actor（后面称为MyCharacter）是添加在函数AGameMode::GetSeamlessTravelActorList里还是APlayerController::GetSeamlessTravelActorList里面，对于前者客户端与服务器都可以正常调试，但是对于后者，DedicateServer上是不会执行的。

这里我们假设你把MyCharacter放在了APlayerController的函数里面，当服务器先执行Travel的时候，你会发现他需要遍历一遍场景中所有存在的Actor，如果这个Actor被标记为可以Travel的，那么就会保存，否则就会调用RouteEndPlay将他删除。一旦服务器将这个Actor删除，那么作为执行同步的客户端也就会把他删除（细节可能更复杂一点，可以在SetPawn里面加一个断点调试看看），所以这个MyCharacter并不会Travel到另一个地图，而在Travel过后，GameMode发现当前Controller的Pawn不存在，就给你重新生成了一个默认的Pawn。

进一步来讲，不仅仅是MyCharacter，所有你添加在函数APlayerController::GetSeamlessTravelActorList的Actor都会出现这个问题。如果你的Actor是通过服务器同步过来的，那么这个Actor在Travel之后一定会从客户端上消失。如果这个Actor不是同步的（比如场景中的一些静态模型），那么在Travel之后，这些Actor也只是存在于客户端上面。


图3-4 服务器清除MyCharacter调用堆栈

图3-5 客户端接收消息清除MyCharacter调用堆栈
e.在AGameModeBase::GetSeamlessTravelActorList函数里面添加了当前控制的Actor，但是在无缝切换后还是并没有Travel过去？？

答：是不是解决了上面的d问题，就可以正常的将MyCharacter传递过去呢？并不是，两个Level在切换的时候还会对Controller有特殊的处理，如果两个关卡的PlayerController的类型不同，就会在Travel的时候生成一个新地图的PlayerController并切换。一旦PlayerController切换，那么原来的PlayerController就会被删除，他所控制的MyCharacter也同样会被删除掉。这个逻辑在AGameMode::HandleSeamlessTravelPlayer处理（注意是GameMode，不是GameModeBase，两个类的逻辑有差异）。


图3-6 无缝切换Controller的切换调用堆栈
Tips：
FPackageName::SearchForPackageOnDisk(FString(URL) + FPackageName::
GetMapPackageExtension(), &MapFullName)
可以根据Map名称搜索到带相对路径的文件名字符串

const FString TargetWorldObjectName = FPackageName::GetLongPackageAssetName
(TargetWorldPackageName);
函数可以将带相对路径的文件名字符串转为Map名称

FPaths::GameDir() 游戏项目根目录
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》Session与Onlinesubsystem[概念理解]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34257172
想弄清UE里面的网络模块，始终绕不过OnlineSubsystem与Session这两个概念，我一开始对这一块也挺头疼的。后来花了点时间，参考网上的资料，对这一块进行了一个相对全面的分析，希望对大家能有所帮助。

总的来说，我暂时把UE网络分成三个部分：
第一个部分是网络同步，包括Actor同步机制，RPC等。
第二个部分是移动同步的模拟，这一块在基本上都在CharacterMovement里面。
第三个部分是网络连接，包括OnlineSubsystem与Session等。也就是这篇文章所要分析的内容。



一．OnlineSubsystem


1.1 什么是OnlineSubsystem？
OnlineSubsystem是一个多网络平台对接系统。其本身是抽象的，需要根据不同平台完成具体的实现。你可以通过他对接Steam，GooglePlay，Amazon，Xbox等，进而使用对应平台的各项自定义功能，如语音聊天，在线统计，游戏大厅与游戏匹配等。

总之，该系统的目的就是让开发者可以快速的切换到不同平台去发布游戏。需要注意的是，在UE里面，OnlineSubsystem与Session机制息息相关，后面Session部分会做进一步的介绍。



1.2 OnlineSubsystem的初始化流程
首先有一点要声明，4.8以前的的OnlineSubsystem是以一个Runtime模块集成在UE的源码里面的。而我看到4.13以后（具体从哪个版本没有确认）该系统改成了以插件Plugin的形式集成在引擎里面，所以Module的初始化不同版本可能会有差异。

在一开始执行引擎初始化的时候，FEngineLoop::PreInit函数会调用FEngineLoop::AppInit进行OnlineSubSystem的加载。（如果是以插件形式集成，就要通过IPluginManager:: Get()->LoadMoudlesForEnabledPlugins()来完成了）

//FEngineLoop::AppInit  LaunchEngineLoop.cpp
#if WITH_ENGINE
    // Earliest place to init the online subsystems
    // Code needs GConfigFile to be valid
    // Must be after FThreadStats::StartThread();
    // Must be before Render/RHI subsystem D3DCreate()
    // For platform services that need D3D hooks like Steam
    FModuleManager::Get().LoadModule(TEXT("OnlineSubsystem"));
    FModuleManager::Get().LoadModule(TEXT("OnlineSubsystemUtils"));
    // Init HighRes screenshot system.
    GetHighResScreenshotConfig().Init();
#endif
当执行LoadModule的时候，会将当前模块添加到FModuleMap Modules;里面并开始加载该模块，执行FOnlineSubsystemModule中的StartupModule函数。StartupModule函数决定当前使用哪个平台，并加载相应平台的模块并初始化，流程如下：

根据项目Project的Config目录下的DefaultEngine.ini中配置确定当前使用哪个平台，DefaultEngine.ini中的配置项如下，图1-1使用的是steam
调用LoadSubsystemModule，根据配置读取的字符串去加载对应的OnlineSubsystem +Name的Module，这里是OnlineSubsystemSteam
加载成功后还要继续调用对应平台Module的StartupModule函数。如果是steam，还需要到”../Engine/Binaries/ThirdParty/ Steamworks/Steamv132/Win64/”路径下去加载其平台的dll文件(路径可能有些偏差，具体看文件steam_api64.dll的位置) 代码如下：
上面对应平台的Dll如果加载成功，需要注册到基类FOnlineSubsystemModule里面。其实就是添加到其OnlineFactories列表里
前面完成了具体平台的Onlinesubsystem模块的加载，但是其实真正的系统还没有构建，只是创建并添加了其Factory而已。所以，继续执行GetOnlineSubsystem尝试获取真正的OnlineSubsystem对象，如果没有就通过Factory工厂进行创建
一般默认在非Shipping版本或者配置文件OnlineSubsystemSteam的bEnable为false的情况下在初始化OnlinesubsystemSteam的时候（包括其他平台），会CreateSubsystem失败，然后Destroy该Onlinesubsystem。这样引擎会默认创建OnlinesubsystemNull来替代 ，配置见图1-2
创建Onlinesubsystem成功且能正确获取到后设置DefaultPlatformService为当前平台

图1-1

图1-2
//对应上面流程第三步
FString RootSteamPath = GetSteamModulePath(); 
FPlatformProcess::PushDllDirectory(*RootSteamPath); 
SteamDLLHandle = FPlatformProcess::GetDllHandle(*(RootSteamPath + "steam_api64.dll ")); 


//OnlineSubsystemModule的启动代码
void FOnlineSubsystemModule::StartupModule()
{
    FString InterfaceString;
    // Load the platform defined "default" online services module
    if (GConfig->GetString(TEXT("OnlineSubsystem"), TEXT("DefaultPlatformService"), InterfaceString, GEngineIni) &&
        InterfaceString.Len() > 0)
    {
        FName InterfaceName = FName(*InterfaceString);
        UE_LOG(LogOnline, Warning, TEXT("Begint to load default OnlineSubsystem module %s, using NULL interface"), *InterfaceString);
        // A module loaded with its factory method set for creation and a default instance of the online subsystem is required  前面的步骤2到步骤5都在这里执行
        if (LoadSubsystemModule(InterfaceString).IsValid() &&
            OnlineFactories.Contains(InterfaceName) && 
            GetOnlineSubsystem(InterfaceName) != NULL)
        {
            DefaultPlatformService = InterfaceName;
        }
        else
        {
            UE_LOG(LogOnline, Warning, TEXT("Unable to load default OnlineSubsystem module %s, using NULL interface"), *InterfaceString);
            InterfaceString = TEXT("Null");
            InterfaceName = FName(*InterfaceString);
            // A module loaded with its factory method set for creation and a default instance of the online subsystem is required
            if (LoadSubsystemModule(InterfaceString).IsValid() &&
                OnlineFactories.Contains(InterfaceName) &&
                GetOnlineSubsystem(InterfaceName) != NULL)
            {
                DefaultPlatformService = InterfaceName;
            }
        }
    }
    else
    {
        UE_LOG(LogOnline, Warning, TEXT("No default platform service specified for OnlineSubsystem"));
    }
}
关于OnlineSubsystemsteam的启动：

如果Steam平台的Onlinesubsystem可以初始化成功(FOnlineSubsystemSteam::Init)，那么该函数会针对服务器和客户端分别对Steam平台进行初始化，即InitSteamworksServer以及InitSteamworksClient，另外还会进行官方服务器列表的启动更新操作。其中InitSteamworksClient函数除了在客户端模式下进行Steam的初始化，还会根据Steam平台的语言来设置游戏客户端的语言。（这里是读取配置文件的Culture信息，实际上要到本地化数据的位置去查找如图1-3）

另外，Steam模块还重写了IPNetDriver以及NetConnection的部分接口，所以启动steam后真正加载的是USteamNetDriver以及USteamNetConnection。（NetDriver通过CreateNamedNetDriver_Local创建，这里会首先根据配置文件DefaultEngine.ini里面的内容尝试加载配置的NetDriver，如果创建失败就会创建默认的NetDriver）


图1-3
1.3 OnlineSubsystem相关类关系

前面描述完流程后，可能觉得还是有点晕，下面整理了Onlinesubsystem相关类的类图。简单总结一下，

Onlinesubsystem系统属于UE众多Module（模块）的一个，所以需要通过一个管理类来管理所有Module的加载，这个管理类就是FMoudlemanager
FModuleManager::Get().LoadModule(TEXT(“OnlineSubsystem”));这里首先加载的模块是FOnlineSubsystemModule（各个OnlineSubsystemModule的基类），他会读取配置文件然后进一步加载指定的OnlineSubsystemModule（如FOnlineSubsystemSteamModule）
FOnlineSubsystemModule有一个接口 GetOnlineSubsystem，这里会根据对应Subsystem的FOnlineFactory（工厂模式）创建对应的FOnlineSubsystem
具体的OnlineSubsystem创建的成功表示他已经完成了相关的初始化Init()，不同的平台的初始化内容各不相同，比如steam是针对客户端与服务器分别执行初始化的
不同的OnlineSubsystem拥有不同的OnlineSession，因为不同平台对Session的处理有很大的差异，这个是由平台来决定的



图1-4
二．Session


2.1.什么是Session？
其实session在WEB领域应用的更为广泛，直译为会话。广义来讲，Session可以理解为一种客户端到服务器保持连接的一种解决方案。狭义来说，Session是一种数据，用来记录保持这个连接的相关内容。

进一步到UE里面，我们可以更形象的理解为游戏中的开房间。服务器运行后，就好比一个玩家开了一个房间，然后等待其他玩家的加入。其他玩家可以在网络上（包括局域网，互联网）搜索到这个房间并加入进去。所以，把房间换成Session，就可以简单理解为服务器创建一个Session，然后客户端搜索并加入这个Session。整个Session相关的各种类与数据就构成了Session机制，用于管理客户端与服务器的连接。

那么session是必须的么？并不是，在4.14版本里面，整个OnlineSubsystem系统被作为一个插件集成在引擎里面，完全可以关掉，其相关的session功能也就基本上无效了。理论上如果服务器不做任何限制，我们只要获取到服务器的IP与端口，我们客户端就可以连接上去。

由此看来，Session最基本的功能就是：在一个多人游戏中，客户端需要通过Session机制连接到服务器，以便服务器验证客户端的合法性，控制连接人数等等。



2.2. UE4中的Session
UE中带session的类确实不少，这可能给大家理解上带来很多困难。你可以看到在游戏初始化过程中有AGameSession，在OnlineSubsystem文件夹下有各种OnlineSessionXXX，我把最重要的几个类拿出来画了一个类图。如下图4-1：


图2-1
总体来说，上面几个类是Session机制的核心。

AGameSession顾名思义，其实其本身并不是Session信息的产生者与拥有者，他主要的目的就是负责Gameplay游戏逻辑与具体的底层Session机制的交互。比如游戏里面有一个在网络上寻找Session的功能，那么一般我们会通过游戏逻辑（比如UI按钮事件）调用GameSession的查找Session功能，GameSession会进一步从OnlineSubsystem里面查询Session。



二．OnlineSubsystem与Session是什么关系
我们可以认为，目前UE的机制里面，Session信息都是包含在OnlineSubsystem里面的。因为不同的平台有不同的验证机制，所以除了基本的IP地址端口等信息外，不同平台对Session的处理还可能有不同的内容，这样就出现了IOnlineSession接口以及对应平台的如FOnlineSubsystemNull这样的类，他把具体的Session信息封装，加入一些与当前OnlineSubsystem相关的操作与处理。

最后几个类（FOnineSession，FNamedOnlineSession, FOnlineSesssionInfo），其实就是具体的Session信息。里面都是常见的Session数据，比如用户唯一ID，服务器IP地址，玩家数量配置等。前面不管是GameSession或者是OnlineSubsystem，最终操作的都是这里的数据。

最后，还有需要注意的是区分客户端与服务器，Session的创建是在服务器上进行的，玩家的注册也是在服务器上进行的（参考RegisterServer与RegisterPlayer），但是不代表客户端没有Session。客户端也拥有图中的各项Session数据，而且客户端还可能通过搜索找到多个Session（OnlineSubsystemNull有FNamedOnlineSession的数组），每个Session表示不同的服务器，这就是我们在网络上搜索Session并加入其中的基本原理。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》关于网络同步的理解与思考[概念理解]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34721113
这篇文章可以帮助你更全面的理解虚幻4引擎的网络模块~



目录

一．关于Actor与其所属连接
-1. Actor的Role是ROLE_Authority就是服务端么？
-2. Owner是如何在RPC调用中生效的？

二．进一步理解RPC与同步
-1. RPC函数应该在哪个端执行？
-2. 客户端创建的Actor能调用RPC么？
-3. RPC与Actor同步谁先执行？
-4. 多播MultiCast RPC会发送给所有客户端么？
-5. RPC参数与返回值

三．合理使用COND_InitialOnly

四．客户端与服务器一致么？

五．属性同步的基本规则与注意事项
-1. 结构体的属性同步
-2. 属性回调
-3. UObject指针类型的属性同步

六．组件同步
一. 关于Actor与其所属连接
UE4官网关于网络链接这一块其实已经将的比较详细了，不过有一些内容没有经验的读者看起来可能还是比较吃力。

按照官网的顺序，我一点点给出我的分析与理解。首先，大家要简单了解一些客户端的连接过程。

主要步骤如下：
1.客户端发送连接请求
2.服务器将在本地调用 AGameMode::PreLogin。这样可以使 GameMode 有机会拒绝连接。
3.如果服务器接受连接，则发送当前地图
4.服务器等待客户端加载此地图，客户端如果加载成功，会发送Join信息到服务器
5.如果接受连接，服务器将调用 AGameMode::Login该函数的作用是创建一个PlayerController，可用于在今后复制到新连接的客户端。成功接收后，这个PlayerController 将替代客户端的临时PlayerController （之前被用作连接过程中的占位符）。
此时将调用 APlayerController::BeginPlay。应当注意的是，在此 actor 上调用RPC 函数尚存在安全风险。您应当等待 AGameMode::PostLogin 被调用完成。
6.如果一切顺利，AGameMode::PostLogin 将被调用。这时，可以放心的让服务器在此 PlayerController 上开始调用RPC 函数。
那么这里面第5点需要重点强调一下。我们知道所谓连接，不过就是客户端连接到一个服务器，在维持着这个连接的条件下，我们才能真正的玩“网络游戏”。通常，如果我们想让服务器把某些特定的信息发送给特定的客户端，我们就需要找到服务器与客户端之间的这个连接。这个链接的信息就存储在PlayerController的里面，而这个PlayerController不能是随随便便创建的PlayerController，一定是客户端第一次链接到服务器，服务器同步过来的这个PlayerController（也就是上面的第五点，后面称其为拥有连接的PlayerController）。进一步来说，这个Controller里面包含着相关的NetDriver，Connection以及Session信息。

对于任何一个Actor（客户端上），他可以有连接，也可以无连接。一旦Actor有连接，他的Role（控制权限）就是ROLE_AutonomousProxy，如果没有连接，他的Role（控制权限）就是ROLE_SimulatedProxy 。

那么对于一个Actor，他有三种方法来得到这个连接（或者说让自己属于这个连接）。

设置自己的owner为拥有连接的PlayerController，或者自己owner的owner为拥有连接的PlayerController。也就说官方文档说的查找他最外层的owner是否是PlayerController而且这个PlayerController拥有连接。
这个Actor必须是Pawn并且Possess了拥有连接的PlayerController。这个例子就是我们打开例子程序时，开始控制一个角色的情况。我们控制的这个角色就拥有这个连接。
这个Actor设置自己的owner为拥有连接的Pawn。这个区别于第一点的就是，Pawn与Controller的绑定方式不是通过Owner这个属性。而是Pawn本身就拥有Controller这个属性。所以Pawn的Owner可能为空。（Owner这个属性在Actor里面，蓝图也可以通过GetOwner来获取）
对于组件来说，那就是先获取到他所归属的那个Actor，然后再通过上面的条件来判断。

我这里举几个例子，玩家PlayerState的owner就是拥有连接的PlayerController，Hud的owner是拥有连接的PlayerController，CameraActor的owner也是拥有连接的PlayerController。而客户端上的其他NPC（一定是在服务器创建的）是都没有owner的Actor，所以这些NPC都是没有连接的，他们的Role就为ROLE_SimulatedProxy。

所以我们发现这些与客户端玩家控制息息相关的Actor才拥有所谓的连接。不过，进一步来讲，我们要这连接还有什么用？好吧，照搬官方文档。

连接所有权是以下情形中的重要因素：
1.RPC 需要确定哪个客户端将执行运行于客户端的 RPC
2.Actor 复制与连接相关性
3.在涉及所有者时的 Actor 属性复制条件
对于RPC，我们知道，UE4里面在Actor上调用RPC函数，可以实现类似在客户端与服务器之间发送可执行的函数的功能。最基本的，当我一个客户端拥有ROLE_AutonomousProxy权限的Actor在服务器代码里调用RPC函数（UFUNCTION(Reliable, Client)）时，我怎么知道应该去众多的客户端的哪一个里面执行这个函数。（RPC的用法不细说，参考官方文档）答案就是通过这个Actor所包含的连接。关于RPC进一步的内容，下个问题里再详细描述。

第二点，Actor本身是可以同步的，他的属性当然也是。这与连接所有权也是息息相关。因为有的东西我们只需要同步给特定的客户端，其他的客户端不需要知道，（比如我当前的摄像机相关内容）。

对于第三点，其实就是Actor的属性是否同步可以进一步根据条件来做限制，有时候我们想限制某个属性只在拥有ROLE_AutonomousProxy的Actor使用，那么我们对这个Actor的属性ReplicatedMovement写成下面的格式就可以了。

void AActor::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
  DOREPLIFETIME_CONDITION( AActor, ReplicatedMovement, COND_AutonomousOnly );
}
而经过前面的讨论我们知道ROLE_AutonomousProxy与所属连接是密不可分的。

最后，这里留一个思考问题：如果我在客户端创建出一个Actor，然后把它的Owner设置为带连接的PlayerController，那么他也有连接么？这个问题在下面的一节中回答。



1.Actor的Role是ROLE_Authority就是服务端么？
并不是，有了前面的讲述，我们已经可以理解，如果我在客户端创建一个独有的Actor(不能勾选bReplicate）。那么这个Actor的Role就是ROLE_Authority，所以这时候你就不能通过判断他的Role来确定当前调试的是客户端还是服务器。这时候最准确的办法是获取到NetDiver，然后通过NetDiver找到Connection。（事实上，GetNetMode()函数就是通过这个方法来判断当前是否是服务器的）对于服务器来说，他只有N个ClientConnections，对于客户端来说只有一个serverConnection。

如何找到NetDriver呢?可以参考下面的图片，从Outer获取到当前的Level，然后通过Level找到World。World里面就有一个NetDiver。当然，方法不止这一个了，如果有Playercontroller的话，Playercontroller上面也有NetConnection，可以再通过NetConnection再获取到NetDiver。






2.Owner是如何在RPC调用中生效的？
答案在AActor::GetFunctionCallspace里面，每次调用RPC函数时，会调用该函数判断当前是不是在远端调用，是的会就会通过网络发送RPC。GetFunctionCallspace里面会通过Owner找到connection信息。




二. 进一步理解RPC与同步


1. RPC函数应该在哪个端执行？
对于一个形如UFUNCTION(Reliable, Client)的RPC函数，我们知道这个函数应该在服务器调用，在客户端执行。可是如果我在Standalone的端上执行该函数的时候会发生什么呢？

答案是在服务器上执行。其实这个结果完全可以参考下面的这个官方图片。

刚接触RPC的朋友可能只是简单的记住这个函数应该从哪里调用，然后在哪里执行。不过要知道，即使我声明一个在服务器调用的RPC我还是可以不按套路的在客户端去调用（有的时候并不是我们故意的，而是编写者没有理解透彻），其实这种不合理的情况UE早就帮我想到并且处理了。比如说你让自己客户端上的其他玩家去调用一个通知服务器来执行的RPC，这肯定是不合理的，因为这意味着你可以假装其他客户端随意给服务器发消息，这种操作与作弊没有区别~所以RPC机制就会果断丢弃这个操作。


所以大家可以仔细去看看上面的这个图片，对照着理解一下各个情况的执行结果，无非就是三个变量：

在哪个端调用
当前执行RPC的Actor归属于哪个连接
RPC的类型是什么。


2. 客户端创建的Actor能调用RPC么？
不过看到这里，再结合上一节结尾提到的问题，如果我在客户端创建一个Actor。把这个Actor的Owner设置为一个带连接PlayerController会怎么样呢？如果在这里调用RPC呢？

我们确实可以通过下面这种方式在客户端给新生成的Actor指定一个Owner。


好吧，关键时候还是得搬出来官方文档的内容。

您必须满足一些要求才能充分发挥 RPC 的作用：
1. 它们必须从 Actor 上调用。
2. Actor 必须被复制。
3. 如果 RPC 是从服务器调用并在客户端上执行，则只有实际拥有这个 Actor 的客户端才会执行函数。
4. 如果 RPC 是从客户端调用并在服务器上执行，客户端就必须拥有调用 RPC 的 Actor。 5. 多播 RPC 则是个例外：
o 如果它们是从服务器调用，服务器将在本地和所有已连接的客户端上执行它们。
o 如果它们是从客户端调用，则只在本地而非服务器上执行。
o 现在，我们有了一个简单的多播事件限制机制：在特定 Actor 的网络更新期内，多播函数将不会复制两次以上。按长期计划，我们会对此进行改善，同时更好的支持跨通道流量管理与限制。


看完第二条，其实你就能理解了，你的Actor必须要被复制，也就是说必须是bReplicate属性为true， Actor是从服务器创建并同步给客户端的（客户端如果勾选了bReplicate就无法在客户端上正常创建，参考第4部分）。

所以，这时候调用RPC是失效的。我们不妨去思考一下，连接存在的意义本身就是一个客户端到服务器的关联，这个关联的主要目的就是为了执行同步。如果我只是在客户端创建一个给自己看的Actor，根本就不需要网络的连接信息（当然你也没有权限把它同步给服务器），所以就算他符合连接的条件，仍然是一个没有意义的连接。

同时，我们可以进一步观察这个Actor的属性，除了Role以外，Actor身上还有一个RemoteRole来表示他的对应端（如果当前端是客户端，对应端就是服务器，当前端是服务器，对应端就是客户端）。你会发现这个在客户端创建的Actor，他的Role是ROLE_Authority（并不是ROLE_AutonomousProxy），而他的RemoteRole是ROLE_None。这也说明了，这个Actor只存在于当前的客户端内。



3. RPC与Actor同步谁先执行？
下面我们讨论一下RPC与同步直接的关系，这里提出一个这样的问题

问题：服务器ActorA在创建一个新的ActorB的函数里同时执行自身的一个Client的RPC函数，RPC与ActorB的同步哪个先执行？(原答案不准确已修改)

答案是不确定。这个涉及到UE4网络消息的发送机制与发送时机，一般来说，RPC的数据会立刻塞到SendBuffer里面，而Actor的同步要等到NetDriver统一处理。所以RPC的消息是相对靠前的，不过由于存在丢包延迟等情况，这个结果在网络环境下不能确定。

那么这个问题会造成什么后果呢？

当你创建一个新的Actor的同时（比如在一个函数内），你将这个Actor作为RPC的参数传到客户端去执行，这时候你会发现客户端的RPC函数的参数为NULL。
你设置了一个bool类型属性A并用UProperty标记了一个回调函数OnRep_Use。你先在服务器里面修改了A为true，同时你调用了一个RPC函数让客户端把A置为true。结果就导致你的OnRep_Use函数没有执行。但实际上，这会导致你的OnRep_Use函数里面还有其他的操作没有执行。
如果你觉得上面的情况从来没有出现过，那很好，说明暂时你的代码没有类似的问题，但是我觉得有必要提醒一下大家，因为UE4代码里面本身就有这样的问题，你以后也很有可能遇到。下面举例说明实际可能出现的问题：

情况1：当我在服务器创建一个NPC的时候，我想让我的角色去骑在NPC上并控制这个NPC，所以我立刻就让我的Controller去Possess这个NPC。在这个过程中，PlayerController就会执行

UFUNCTION(Reliable, Client) 
void ClientRestart (APawn*NewPawn)
当客户端收到这个RPC函数回调的时候就发现我的APlayerController::ClientRestart_Implementation (APawn* NewPawn)里面的参数为空~原因就是因为这个NPC刚在服务器创建还没有同步过来。同理，对于刚出生的玩家来说是不是也存在这个问题呢？

确实存在。不过，UE4本身其实有考虑到这个问题，ClientRestart函数有特殊的处理，服务器在移动的时候会通过SafeRetryClientRestart让客户端执行ClientRetryClientRestart，如果发现Pawn不对（也就是第一次ClientRestart执行失败的话）就会触发再次执行。

更新：我们可以通过设置控制台变量net.DelayUnmappedRPCs 1允许客户端等到这个对象生成的时候再去执行，但是仅限于可靠的RPC。
情况2：对于Pawn里面的Controller成员声明如下

UPROPERTY(replicatedUsing=OnRep_Controller)
AController*Controller;

OnRep_Controller回调函数里面回去执行Controller->SetPawnFromRep(this);
进而执行
Pawn = InPawn;
OnRep_Pawn();
下面重点来了，OnRep_Pawn函数里面会执行

OldPawn->Controller= NULL;
将客户端之前Controller控制的角色的Controller设置为空。

到现在来看没有什么问题。那么现在结合上面第二个问题，如果一个RPC函数的执行发生在客户端的Controller同步前同时修改为正确的Controller，那么OnRep_Controller回调函数就不会执行。所以客户端的原来Controller控制的OldPawn的Controller就不会置为空，导致的结果是客户端和服务器竟然不一样。

实际上，确实存在这么一个函数，这个RPC函数就是ClientRestart。这看起来就很奇怪，因为ClientRestart如果没有正常执行的话，OnRep_Controller就会执行，进而导致客户端的oldPawn的Controller为空（与服务器不同，因为服务器并没有去设置OldPawn的Controller）。不知道这是不是引擎的一个bug。

不管怎么说，你需要清楚的是RPC的执行与同步的执行是有先后关系的，而这种关系会影响到代码的逻辑，所以之后的代码有必要考虑到这一点。

最后，对使用RPC的朋友做一个提醒，有些时候我们在使用UPROPERTY标记Server的函数时，可能是从客户端调用，也可能是从服务器调用。虽然结果都是在服务器执行，但是过程可完全不同。从客户端调用的在实际运行时是通过网络来处理的，一定会有延迟。而从服务器调用的则会立刻执行。



4. 多播MultiCast RPC会发送给所有客户端么？（已修改）
原答案：

看到这个问题，你可能想这还用说么？不发给所有客户端那要多播干什么？但事实上确实不一定。

考虑到服务器上的一个NPC，在地图的最北面，有两个客户端玩家。一个玩家A在这个NPC附近，另一个玩家B在最南边看不到这个NPC（实际上就是由于距离太远，服务器没有把这个Actor同步到这个B玩家的客户端）。我们现在在这个NPC上调用多播RPC通知所有客户端上显示一个提示消失“NPC发现了宝藏”。这个消息会不会发送到B客户端上面？

情况一：会。多播顾名思义就是通知所有客户端，不需要考虑发送到哪一个客户端，直接遍历所有的连接发送即可。
情况二：不会。RPC本来就是基于Actor的，在客户端B上面连这个Actor都没有，我还可以使用RPC不会很奇怪？
第一种情况强化了多播的概念，淡化了RPC基于Actor的机制，情况二则相反。所以看起来都有道理。实际上，UE4里面更偏向第二种情况，处理如下：

如果一个多播标记为Reliable，那么他默认会给所有的客户端执行该多播事件，如果其标记的是unreliable，他就会检测该NPC与客户端B的网络相关性（即在客户端B上是否同步）。但实际上，UE还是认为开发者不应该声明一个Reliable的多播函数。下面给出UE针对这个问题的相关注释：（相关的细节在另一篇进一步深入UE网络同步的文章里面去分析）

// Do relevancy check if unreliable.
// Reliables will always go out. This is odd behavior. On one hand we wish to garuntee "reliables always getthere". On the other
// hand, replicating a reliable to something on theother side of the map that is non relevant seems weird. 
// Multicast reliables should probably never beused in gameplay code for actors that have relevancy checks. If they are, the 
// rpc will go through and the channel will be closedsoon after due to relevancy failing.
修改答案：

我发现引擎在这块已经更改了，引擎已经不考虑多播函数是否是reliable了，只要不满足NetRelevant都不会发送，参考UNetDriver::ProcessRemoteFunction。


5. RPC参数与返回值
参数：RPC函数除了UObject类型的指针以及constFString&的字符串外，其他类型的指针或者引用都不可以作为RPC的参数。对于UObject指针类型我们可以在另一端通过GUID识别（后面第五部分有讲解），但是其他类型的指针传过去是什么呢？我们根本就无法还原其地址，所以不允许传输其指针或者引用。

而对于FString，传const原因我认为是为了不想让发送方与接收方两边对字符串进行修改，而传引用只是为了减少复制构造带来的开销。在FString发送与接收的处理细节里面并不在意其是否是const&，他只在意他的类型以及相对Object的偏移。

返回值：一个RPC函数是不能有返回值的，因为其本身的执行就是一次消息的传递。假如一个客户端执行一个Server RPC，如果有返回值的话，那么岂不是服务器执行后还要再发送一个消息给客户端？这个消息怎么处理？再发一次RPC？如果还有返回值那么不就无限循环了？因此RPC函数不可以添加返回值。

三. 合理使用COND_InitialOnly
前面提到过，Actor的属性同步可以通过这种方式来实现。

声明一个属性并标记

UPROPERTY(Replicated) 
uint8 bWeapon: 1;

UPROPERTY(Replicated)
uint8 bIsTargeting: 1;

void Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps ) const
{
    DOREPLIFETIME(Character,bWeapon );
    DOREPLIFETIME_CONDITION(Character, bIsTargeting, COND_InitialOnly
);
这里面的第一个属性一般的属性复制，第二个就是条件属性复制。条件属性复制无非就是告诉引擎，这个属性在哪些情况下同步，哪些情况下不同步。这些条件都是引擎事先提供好的。

这里我想着重的提一下COND_InitialOnly这个条件宏，汉语的官方文档是这样描述的：该属性仅在初始数据组尝试发送。而英文是这样描述的：This property will only attempt to send on the initial bunch。对比一下，果然还是英文看起来更直观一点。

经过测试，这个条件的效果就是这个宏声明的属性只会在Actor初始化的时候同步一次，接下来的游戏过程中不会再同步。所以，我们大概能想到这个东西在有些时候确实用的到，比如同步玩家的姓名，是男还是女等，这些游戏开始到结束一般都不会改变的属性。也就是说，上限一般调整的次数很少，如果真的有调整并需要同步，他会手动调用函数去同步该属性。这样就可以减少同步带来的压力。 然而，一旦你声明为COND_InitialOnly。你就要清楚，同步只会执行一次，客户端的OnRep回调函数就会执行一次。所以，当你在服务器创建了一个新的Actor的时候你需要第一时间把需要改变的值修改好，一旦你在下一帧（或是下一秒）去执行那么这个属性就无法正确的同步到客户端了。

四．客户端与服务器一致么？
我们已经知道UE4的客户端与服务器公用一套代码，那么我们在每次写代码的时候就有必要提醒一下自己。这段代码在哪个端执行，客户端与服务器执行与表现是否一致？

虽然，我很早之前就知道这个问题，但是写代码的时候还是总是忽略这个问题，而且程序功能经常看起来运行的没什么问题。不过看起来正常不代表逻辑正常，有的时候同步机制帮你同步一些东西，有时候会删除一些东西，有时候又会生成一些东西，然而你可能一点都没发现。

举个例子，我在一个ActorBeginPlay的时候给他创建一个粒子Emiter。代码大概如下：

void AGate::BeginPlay()
{
   Super::BeginPlay();
  //单纯的在当前位置创建粒子发射器
   GetWorld()->SpawnActor<AEmitter>(SpawnEmitter,GetActorLocation(), UVictoryCore::RTransform(SpawnEmitterRotationOffset,GetActorRotation()));
}
代码很简单，不过也值得我们分析一下。

首先，服务器下，当Actor创建的时候就会执行BeginPlay，然后在服务器创建了一个粒子发射器。这一步在服务器（DedicateServer）创建的粒子其实就是不需要的，所以一般来说，这种纯客户端表现的内容我们不需要在专用服务器上创建。

再来看一下客户端，当创建一个Gate的时候，服务器会同步到客户端一个Gate，然后客户端的Gate执行BeginPlay，创建粒子。这时候我们已经发现二者执行BeginPlay的时机不一样了。进一步测试，发现当玩家远离Gate的时候，由于UE的同步机制（只会同步一定范围内的Actor），客户端的Gate会被销毁，而粒子发射器也会销毁。而当玩家再次靠近的时候，Gate又被同步过来了，原来的粒子发射器也被同步过来。而因为客户端再次执行了BeginPlay，又创建了一个新的粒子，这样就会导致不断的创建新的粒子。

现在的版本里面并没有TemplateAllowActorSpawn这个接口，下面引用的内容已作废。

你觉得上面的描述准确么？并不准确，因为上述逻辑的执行还需要一个前置条件——这个粒子的bReplicate属性是为false的。有的时候，我们可能一不小心就写出来上面这种代码，但是表现上确实正常的，为什么？因为SpawnActor是否成功是有条件限制的，在生成过程中有一个函数
bool AActor::TemplateAllowActorSpawn(UWorld* World,const FVector& AtLocation, const FRotator& AtRotation, const struct FActorSpawnParameters& SpawnParameters) { return !bReplicates || SpawnParameters.bRemoteOwned||World->GetNetMode() != NM_Client; }
如果你是在客户端，且这个Actor勾选了bReplicate的话，TemplateAllowActorSpawn就会返回false，创建Actor就会失败。如果这个Actor没有勾选bReplicate的话，那么服务器只会创建一个，客户端就可能不断的创建，而且服务器上的这个Actor与客户端的Actor没有任何关系。
另外，还有一种常见的错误。就是我们的代码执行是有条件的，然而这个条件在客户端与服务器是不一样的（没同步）。如

void Gate::CreateParticle(int32 ID)
{
   if(GateID!= ID)
   {
      FActorSpawnParameters SpawnInfo;
      GetWorld()->SpawnActor<AEmitter>(SpawnEmitter, GetActorLocation(),GetActorRotation(), SpawnInfo);
   }
}
这个GateID是我们在GateBeginPlay的时候随机初始化的，然而这个GateID只在服务器与客户端是不同的。所以需要服务器同步到客户端，才能按照我们理想的逻辑去执行。

五. 属性同步的基本规则与注意事项
非休眠状态下的Actor的属性同步：只在服务器属性值发生改变的情况下执行
回调函数执行条件：服务器同步过来的数值与客户端不同
休眠的Actor：不同步
首先要认识到，同步操作触发是由服务器决定的，所以不管客户端是什么值，服务器觉得该同步就会把数据同步到客户端。而回调操作是客户端执行，所以客户端会判断与当前的值是否相同来决定是否产生回调。

然后是属性同步，属性同步的基本原理就是服务器在创建同步通道的时候给每一个Actor对象创建一个属性变化表（这里面涉及到FObjectReplicator，FRepLayout，FRepState，FRepChangedPropertyTracker相关的类，有兴趣可以进一步了解，在另一深入UE网络同步文章里有讲解），里面会记录一个当前默认的Actor属性值。之后，每次属性发生变化的时候，服务器都会判断新的值与当前属性变化表里面的值是否相同，如果不同就把数据同步到客户端并修改属性变化表里的数据。对于一个非休眠且保持连接的Actor，他的属性变化表是一直存在的，所以他的表现出来的同步规则也很简单，只要服务器变化就同步。

动态数组TArray在网络中是可以正常同步的，系统会检测到你的数组长度是否发生了变化，并通知客户端改变。



1. 结构体的属性同步
注意，UE里面UStruct类型的结构体在反射系统中对应的是UScriptStruct，他本身可以被标记Replicated并且结构体内的数据默认都会被同步，而且如果里面有还子结构体的话也仍然会递归的进行同步。如果不想同步的话，需要在对应的属性标记NotReplicated，而且这个标记只对UStruct有效，对UClass无效。

有一点特别的是，Struct结构内的数据是不能标记Replicated的。如果你给Struct里面的属性标记replicated，UHT在编译的时候就会提醒你编译失败。

最后，UE里面的UStruct不可以以成员指针的方式在类中声明。



2. 属性回调
问题：属性回调与RPC在使用结果上的差异？

属性回调理论上一定会执行，而RPC函数有可能由于错过执行时机而不再会执行。例如：我在服务器上面有一个宝箱，第一个玩家过去后，宝箱会自动开启。如果使用RPC函数，当第一个玩家过去后，箱子执行多播RPC函数触发开箱子操作。但是由于其他的玩家离这个箱子很远，所有这个箱子没有同步给其他玩家，其他玩家收不到这个RPC消息。（如果对结果有疑问参考第二节的第四个问题）当这些玩家之后再过去之后，会发现箱子还是关闭的。如果采用属性回调，但第一个玩家过去后，设置箱子的属性bOpen为true，然后同步到所有客户端，通过属性回调执行开箱子操作。这时候其他玩家靠近箱子时，箱子会同步到靠近的玩家，然后玩家在客户端上会收到属性bOpen，同时执行属性回调，这时候可以实现所有靠近的玩家都会发现箱子已经被别人开过了。

问题：服务器上生成一个Actor，他在客户端上的UObject类型指针的属性回调与他的Beginplay谁先执行？

这个问题这么看有点奇怪，我进一步描述一下。有一个类MyActor，他有一个指针属性PropertyB指向一个同步的MyActorB，同时这个指针属性有一个回调函数。现在我在服务器创建一个新的MyActor A，并设置A的PropertyB为MyActorB。那么在客户端上，是A的BeginPlay先执行，还是PropertyB的属性回调先执行？

答案是不确定，一开始的时候，我一直认为是属性回调在Actor的BeginPlay之前执行，测试了很多次也是这样的。但是某种情况下， BeginPlay会先执行。这个问题的意义就在于，一个Actor同步过去执行BeginPlay的时候，你发现他的属性还没有同步过来（而且只发现指针可能没有同步过来，其他内置类型都会在BeginPlay 前同步过来）。为什么指针没有同步过来？因为这个指针同步过来的时候，他指向的对象在客户端还不存在，他在客户端上也没有对应的GUID缓存 。由于找不到对应的对象，他只能先暂时记录下这个指针指向对象的GUID，然后在其他的Tick时间再回来检测这个对象是否存在。这种情况一般来说很难重现，不过这个问题有助于我们进一步加深对网络的理解。



3. UObject指针类型的属性同步
属性同步也好，RPC参数也好。我们都需要思考一下，我在传递一个UObject类型的指针时，这个UObject在客户端存在么？如果存在，我如何能通过服务器的一个指针找到客户端上相同UObject的指针？

答案是通过FNetworkGUID。服务器在同步一个对象引用（指针）的时候，会给其分配专门的FNetworkGUID并通过网络进行发送。客户端上通过识别这个ID，就可以找到对应UObject。

那么如此说来，是不是只有标记Replicate的对象才能同步其引用或指针呢？

也不是。对于直接从数据包加载出来的对象（如地图里面实现搭建好的建筑地形），我们可以直接认为服务器上的该地形对象与客户端上对应的地形对象就是一个对象，那么在服务器上指向该地形的指针发送到客户端也应该就是指向对应地形的指针。所以总结来说一个UObject对象是否可以通过网络发送他的引用有如下条件（参考官方文档）：

您通常可以按照以下原则来确定是否可以通过网络引用一个对象：
任何复制的 actor 都可以复制为一个引用
任何未复制的 actor 都必须有可靠命名（直接从数据包加载）
任何复制的组件都可以复制为一个引用
任何未复制的组件都必须有可靠命名。
其他所有 UObject（非actor 或组件）必须由加载的数据包直接提供

什么是拥有可靠命名的对象？
拥有可靠命名的对象指的是存在于服务器和客户端上的同名对象。
1.如果Actor 是从数据包直接加载(并非在游戏期间生成)，它们就被认为是拥有可靠命名。

2.满足以下条件的组件即拥有可靠命名：
● 从数据包直接加载
● 通过construction scripts脚本添加
● 采用手动标记（通过 UActorComponent::SetNetAddressable 设置）
● 只有当您知道要手动命名组件以便其在服务器和客户端上具有相同名称时，才应当使用这种方法（最好的例子就是 AActor C++ 构造函数中添加的组件）
最后总结一下就是有四种情况下UObject对象的引用可以在网络上传递成功

标记replicate
从数据包直接Load
通过Construction scripts添加或者C++构造函数里面添加
使用UActorComponent::SetNetAddressable标记（这个只针对组件，其实蓝图里面创建的组件默认就会执行这个操作）
六．组件同步
组件在同步上分为两大类：静态组件与动态组件。

对于静态组件：一旦一个Actor被标记为同步，那么这个Actor身上默认所挂载的组件也会随Actor一起“同步”到客户端（也需要序列化发送）。什么是默认挂载的组件?就是C++构造函数里面创建的默认组件或者在蓝图里面添加构建的组件。所以，这个过程与该组件是否标记为Replicate是没有关系的。注意，这里客户端虽然会得到一份与服务器相同的组件，但本质上并不算同步服务器的，而是利用构造函数创建的。

对于动态组件：就是我们在游戏运行的时候，服务器创建或者删除的组件。比如，当玩家走进一个洞穴时，给洞穴里面的火把生成一个粒子特效组件，然后同步到客户端上，当玩家离开的时候再删除这个组件，玩家的客户端上也随之删除这个组件。

对于动态组件，我们必须要attach到Actor上并设置他的Replicate属性为true，即通过函数 AActorComponent ::SetIsReplicated(true)来操作。而对于静态组件，如果我们不想同步组件上面的属性，我们就没有必要设置Replicate属性。

一旦我们执行了SetIsReplicated(true)。那么组件在属性同步以及RPC上与Actor的同步几乎没有区别，组件上也需要设置GetLifetimeReplicatedProps来执行属性同步，Actor同步的时候会遍历他的子组件查看是否标记Replicate以及是否有属性要同步。

注意：动态组件的同步是有限制的。由于组件里面的很多成员是无法同步的（比如skeletalmesh）导致很多组件服务器创建后并不会显示在客户端上面，所以客户端在收到之后还要再进行一些相关的处理，比如说把组件放到一个属性并在回调里面重新加载一遍skeletalmesh（记录skeletalmesh的TSoftObjectPtr并同步，客户端收到后执行LoadSynchronous本地加载）。

bool AActor::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
     check(Channel);
     check(Bunch);
     check(RepFlags);

     bool  WroteSomething = false;
     for(UActorComponent* ActorComp : ReplicatedComponents)
     {
         if(ActorComp && ActorComp->GetIsReplicated())
         {
           //Lets the component add subobjects before replicating its own properties.
            WroteSomething|= ActorComp->ReplicateSubobjects(Channel, Bunch,RepFlags); 
           //(this makes those subobjects 'supported', and from here on those objects mayhave reference replicated)  子对象（包括子组件）的同步，其实是在ActorChannel里进行
            WroteSomething |= Channel->ReplicateSubobject(ActorComp,*Bunch,*RepFlags);
         }
      }
     return  WroteSomething;
}


对于C++默认的组件，需要放在构造函数里面构造并设置同步，UE给出了一个例子：（这个例子表示给CharacterMovement设置同步后，CharacterMovement自身就可以支持属性同步以及RPC等功能。如果不标记为同步，客户端在同步创建的时候还是会正常构建该移动组件的。实际上，移动组件通常不需要同步，UE里面并没有给移动组件设置同步）

ACharacter::ACharacter()
{
   // Etc...
   CharacterMovement = CreateDefaultSubobject<UMovementComp_Character>(TEXT("CharMoveComp");
   if (CharacterMovement)
   {
     CharacterMovement->UpdatedComponent = CapsuleComponent;
     CharacterMovement->GetNavAgentProperties()->bCanJump = true;
     CharacterMovement->GetNavAgentProperties()->bCanWalk = true;
     CharacterMovement->SetJumpAllowed(true);
     //Make DSO components net addressable 实际上如果设置了Replicate之后，这句代码就没有必要执行了
     CharacterMovement->SetNetAddressable();
     // Enable replication by default
     CharacterMovement->SetIsReplicated(true);
    }
}
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》网络同步原理深入（上）[原理分析]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34723199
前言
UE同步是一块比较复杂而庞大的模块，里面设计到了很多设计思想，技巧，技术。我这里主要是从同步的流程分析，以同步的机制为讲解核心，给大家描述里面是怎么同步的，会大量涉及UE同步模块的底层代码，稍微涉及一点计算机网络底层（Socket相关）相关的知识。


PS：如果只是想知道怎么使用同步，建议阅读这篇文章 关于网络同步的理解与思考[概念理解] 另外，由于知乎每篇文章有字数限制，实在没办法在上一篇里面添加新的内容，所以就把网络同步深入这块拆成了两篇文章。这次更新主要是在网络数据包格式、PacketHandler、条件复制、可靠数据传输、ReplicationGraph等方面做了进一步的分析与阐述。

目录(上篇)
一．基本概念与架构特点（更新）
二．通信的基本流程（更新）
- 1. 数据包格式
三．连接的建立（更新）
- 1. 服务器网络模块初始化流程
- 2. 客户端网络模块初始化流程
- 3. 服务器与客户端建立连接流程
四．Actor的同步细节
- 1.组件（子对象）同步

下篇链接：《Exploring in UE4》网络同步原理深入（下）[原理分析]

一． 基本概念与架构特点
UE网络是一个相当复杂的模块，这篇文章主要是针对Actor同步，属性同步，RPC等大致的阐述一些流程以及关键的一些类。这里我尽可能将我的理解写下来。
在UE里面有一些和同步相关的概念与类，这里逐个列举一下并做解释：

基本网络通信：

NetDriver
网络驱动，实际上我们创建使用的是他的子类IPNetDriver，里面封装了基本的同步Actor的操作，初始化客户端与服务器的连接，建立属性记录表，处理RPC函数，创建Socket，构建并管理当前Connection信息，接收数据包等等基本操作。NetDriver与World一一对应，在一个游戏世界里面只存在一个NetDriver。UE里面默认的都是基于UDPSocket进行通信的。
Connection
表示一个网络连接。服务器上，一个客户端到一个服务器的一个连接叫一个ClientConnection。在客户端上，一个服务器到一个客户端的连接叫一个ServerConnection。
LocalPlayer
本地玩家，一个客户端的窗口ViewportClient对应一个LocalPlayer，Localplayer在各个地图切换时不会改变。
Channel
数据通道，每一个通道只负责交换某一个特定类型特定实例的数据信息。ControlChannel：客户端服务器之间发送控制信息，主要是发送接收连接与断开的相关消息。在一个Connection中只会在初始化连接的时候创建一个该通道实例。
VoiceChannel：用于发送接收语音消息。在一个Connection中只会在初始化连接的时候创建一个该通道实例。
ActorChannel：处理Actor本身相关信息的同步，包括自身的同步以及子组件，属性的同步，RPC调用等。每个Connection连接里的每个同步的Actor都对应着一个ActorChannel实例。
常见的只有这3种：枚举里面还有FileChannel等类型，不过没有使用。
PlayerController
玩家控制器，对应一个LocalPlayer，代替本地玩家控制游戏角色。同时对应一个Connection，记录了当前的连接信息，这和RPC以及条件属性复制都是密切相关的。另外，PlayerController记录他本身的ViewTarget（就是他控制额Character），通过与ViewTarget的距离（太远的Actor不会同步）来进行其他Actor的同步处理。
World
游戏世界，任何游戏逻辑都是在World里面处理的，Actor的同步也受World控制，World知道哪些Actor应该同步，保存了网络通信的基础设施NetDriver。
Actor
在世界存在的对象，没有坐标。UE4大部分的同步功能都是围绕Actor来实现的。
Dormant
休眠，对于休眠的Actor不会进行网络同步


底层通信：

Packet 从Socket读出来/输出的数据，一个Packet里面可能有多个Bunch数据或者Ack数据
Bunch 一个Bunch里面主要记录了Channel信息，NGUID。同时包含其他的附属信息如是否是完整的Bunch，是否是可靠等，可以简单理解为一个从逻辑上层分发下来的同步数据包，该数据包的数据可能不完整，Bunch分为属性Bunch以及RPCBunch。继承自FNetBitWriter InBunch：从Channel接收的数据流串 ，UNetConnection::ReceivedPacket的时候创建 OutBunch：从Channel产生的数据流串，UActorChannel::ReplicateActor()的时候创建
Ack Ack是与Bunch同级别概念的网络数据串，用于实现UDP的可靠数据传输
FBitWriter 字节流书写器，可以临时写入比特数据用于传输，存储等，继承自FArchive
FSocket 所有平台Socket的基类。 FSocketBSD：使用winSocket的Socket封装
UPackageMap 生成与维护Object与NGUID的映射，负责Object的序列化。每一个Connection对应一个UPackageMap
PacketHandler ：网络包预处理，比如加密，前向纠错，握手等。里面有一个或多个HandlerComponents来执行特殊的数据处理。目前内置的包括加密组件RSA，AES，以及必备的握手组件StatelessConnectHandlerComponent
（Packet与Bunch的区别：Bunch是Packet子集，Packet里面可能不包含Bunch信息，只包含Ack数据）

属性同步相关：

FObjectReplicator
属性同步的执行器，每个Actorchannel对应一个FObjectReplicator，每一个FObjectReplicator对应一个对象实例。设置ActorChannel通道的时候会创建出来。
FRepState
针对每个连接同步的历史数据，记录同步前用于比较的Object对象信息，存在于FObjectReplicator里面。
FRepLayOut
同步的属性布局表，记录所有当前类需要同步的属性，每个类或者RPC函数有一个。
FRepChangedPropertyTracker
属性变化轨迹记录，一般在同步Actor前创建，Actor销毁的时候删掉。
FReplicationChangelistMgr
存放当前的Object对象，保存属性的变化历史记录


架构特点：

客户端服务器共用一套代码
服务器为游戏逻辑服务器，单个服务器为核心，多个客户端连接
默认通信协议为UDP（应用层实现数据可靠的UDP）
收发UDP数据包都在主线程（GameThread）执行
二． 通信的基本流程
如果我们接触过网络通信，应该了解只要知道对方的IP地址以及端口号，服务器A上进程M_1_Server可以通过套接字向客户端B上的进程M_1_Client发送消息，大致的效果如下：


图2-1 远程进程通信图
而对于UE4进程内部服务器Server与客户端Client1的通信，与上面的模型基本相似：


图2-2 UE4远程进程通信图
那这个里面的Channel是什么意思呢？简单理解起来就是一个通信轨道。为了实现规范与通信效率，我们的一个服务器针对某个对象定义了Channel通道，这个通道只与客户端对应的Channel通道互相发送与接收消息。这个过程抽象起来与TCP/UDP套接字的传输过程很像，套接字是在消息发送到进程前就进行处理，来控制客户端进程A只会接收到服务器对应进程A的消息，而这里是在UnrealEditor.exe进程里面处理，让通道1只接收到另一端通道1发送的消息。
上面的只是针对一个服务器到客户端的传输流程，那么如果是多个客户端呢？


图2-3 Channel通信图
每一个客户端叫做一个Connection，如图，就是一个server连接到两个客户端的效果。对于每一个客户端，都会建立起一个Connection。在服务器上这个Connection叫做ClientConnection，对于客户端这个Connection叫做ServerConnection。每一个Channel都会归属于一个Connection，这样这个Channel才知道他对应的是哪个客户端上的对象。
接下来我们继续细化，图中的Channel只标记了1,2,3，那么实际上都有哪些Channel？这些Channel对应的都是什么对象？其实，在第一部分的概念里我已经列举了常见的3中Channel，分别是ControlChannel，ActorChannel,以及VoiceChannel。一般来说，ControlChannel与VoiceChannel在游戏中只存在一个，而ActorChannel则对应每一个需要同步的Actor，所以我们再次细化上面的示意图：


图2-4 Connection下的Channel通信图
到这里我们基本上就了解了UE4的基本通信架构了，下面我们进一步分析网络传输数据的流程。首先我们要知道，UE4的数据通信是建立在UDP-Socket的基础上的，与其他的通信程序一样，我们需要对Socket的信息进行封装发送以及接收解析。流程如图所示：


图2-5 发送同步信息流程图

图2-6 接收同步信息流程图
1.数据包格式概述
关于网络包的封装与解析，主要涉及到Bunch，RawBunch，Packet等概念，可以参考第一部分的基本概念去理解，最后一部分可靠数据传输还会讲到。每次通道最后发出去的包都成为一个Packet，Packet里面的信息是通过Bunch或者Ack塞进去的（也就是UNetConnection的Sendbuffer），里面可能有多个bunch与Ack，数量取决于你Flush的频率，默认情况下是在NetDriver Tick的时候或者buffer到达一定值的时候发送。

在Channel、Connection类里面有许多具体的函数通过处理Bunch/Packet实现了可靠传输，文章的最后一部分会做分析。


三． 连接的建立

前面的内容已经提到过，UE的网通通信是基于Channel的，而ControlChannel就是负责
控制客户端与服务器建立连接的通道，所以客户端与服务器的连接信息都是通过UControlChannel执行NotifyControlMessage函数处理的。下面首先从服务器与客户端的网络模块初始化说起，然后描述二者连接建立的详细流程：



1.服务器网络模块初始化流程
从创建GameInstance开始，首先创建NetDriver来驱动网络初始化，进而根据平台创建对应的Socket，之后在World里面监听客户端的消息。


图3-1 服务器网络模块初始化流程图
2.客户端网络模块初始化流程
客户端前面的初始化流程与服务器很相似，也是首先构建NetDriver，然后根据平台创建对应的Socket，同时他还会创建一个到服务器的ServerConnection。由于客户端没有World信息，所以要使用一个新的类来检测并处理连接信息，这个类就是UpendingNetGame。


图3-2 客户端网络模块初始化流程图
3.服务器与客户端建立连接流程
二者都完成初始化后，客户端就会开始发送一个Hello类型的ControlChannel消息给服务器（上面客户端初始化最后一步）。服务器接收到消息之后开始处理，然后会根据条件再给客户端发送对应的消息，如此来回处理几个回合，完成连接的建立，详细流程参考下图：
（该流程是本地局域网的连接流程，与在线查找服务器列表并加入有差异）


图3-3 客户端服务器连接建立流程图（已更新）
四． Actor的同步细节
Actor的同步可以说是UE4网络里面最大的一个模块了，里面包括属性同步，RPC调用等，这里为了方便我将他们拆成了3个部分来分别叙述。
有了前面的描述，我们已经知道NetDiver负责整个网络的驱动，而ActorChannel就是专门用于Actor同步的通信通道。
这里对Actor同步做一个比较细致的描述：服务器在NetDiver的TickFlush里面，每一帧都会去执行ServerReplicateActors来同步Actor的相关内容。在这里我们需要做以下处理:

获取到所有连接到服务器的ClientConnections，首先获取引擎每帧可以同步的最大Connection的数量，超过这个限制的忽略。然后对每个Connection几乎都要进行下面所有的操作
找到要同步的Actor，只有被放到World.NetworkActors里面的Actor才会被考虑，Actor在被Spawn时候就会添加到这个NetworkActors列表里面（新的版本里面已经把需要同的ACtor放到了NetDriver的NetworkObjects列表里面了）
找到客户端玩家控制的角色ViewTarget（ViewTaget与摄像机绑定在一起），这个角色的位置是决定其他Actor是否同步的关键
验证Actor，对于要销毁的以及所有权Role为ROLE_NONE的Actor不会同步
是否到达Actor同步时间，Actor的同步是有一定频率的，Actor身上有一个NetUpdateTime，每次同步前都会通过下面这个公式来计算下一次Actor的同步时间，如果没有到达这个时间就会放弃本次同步Actor->NetUpdateTime = World->TimeSeconds + FMath::SRand() * ServerTickTime + 1.f/Actor->NetUpdateFrequency;
如果这个Actor设置OnlyRelevantToOwner，那么就会放到一个特殊的列表里面OwnedConsiderList然后只同步给属于他的客户端。否则会把Actor放到ConsiderList里面
对于休眠状态的Actor不会进行同步，对于要进入休眠状态的Actor也要特殊处理关闭同步通道
查看当前的Actor是否有通道Channel，如果没有，还要看看Actor是否已经加在了场景，没有加载就跳过同步
接第8个条件——没有Channel的情况下，还会执行Actor::IsNetRelevantFor判断是否网络相关，对于不可见的或者太远的Actor会返回false，不会同步
Actor的同步数量可能非常大，所以有必要对所有的Actor进行一个优先级的排列
处理完上面的逻辑后会对优先级表里的所有Actor进行排序
排序后，如果连接没有加载此 actor 所在的关卡，则关闭通道（如果存在）并继续
每 1 秒钟调用一次 AActor::IsNetRelevantFor，确定 actor 是否与连接相关，如果不相关的时间达到 5 秒钟，则关闭通道
如果要同步的Actor没有ActorChannel就给其创建一个并绑定Actor，执行同步并更新NetUpdateTime = Actor->GetWorld()->TimeSeconds + 0.2f * FMath::FRand();
如果此连接出现饱和剩下的 actor会根据连接相关时间判断是否在下一个时钟更新
执行UActorChannel::ReplicateActor执行真正的Actor同步以及内部数据的同步，这里会将Actor（PackageMap->SerializeNewActor），Actor子对象以及其属性序列化（ReplicateProperties）封装到OutBunch并发送给客户端
（备注：我们当前版本下面的逻辑都是写在UNetDriver::ServerReplicateActors里面，4.12以后的UE4已经分别把Connection预处理，获取同步Actor列表，优先级处理等逻辑封装到单独的函数里了，详见ServerReplicateActors_BuildConsiderlist, ServerReplicateActors_PrioritizedActors, ServerReplicateActors_ProsessPrioritizedActors等函数
优先级排序规则是什么？答案是按照是否有controller，距离以及是否在视野。通过FActorPriority构造代码可以定位到APawn::GetNetPriority,这里面会计算出当前Actor对应的优先级，优先级越高同步越靠前，是否有Controller的权重最大）
总之，大体上Actor同步的逻辑就是在TickFlush里面去执行ServerReplicateActors，然后进行前面说的那些处理。最后对每个Actor执行ActorChannel::ReplicateActor将Actor本身的信息，子对象的信息，属性信息封装到Bunch并进一步封装到发送缓存中，最后通过Socket发送出去。
下面是服务器的同步Actor的发送Bunch堆栈：（代码修改过，与UE默认的有些不同）


图4-1 服务器同步Actor堆栈图
下面描述客户端是如何接收到服务器同步过来的Actor的。首先客户端TickDispatch检测服务器的消息，收到消息后通过Connection以及Channel进行解析，最后一步解析出完整数据的操作在UActorChannel::ProcessBunch执行，在这个函数里面：

如果发现当前的ActorChannel对应的Actor为NULL，就对当前的Bunch进行反序列化Connection->PackageMap->SerializeNewActor(Bunch, this, NewChannelActor);解析出Actor的内容并执行PostInitializeComponents。如果Actor不为NULL，跳过这一步（参考下面图一堆栈）
随后根据Bunch信息找到同步过来的属性值并对当前Actor对应的属性进行赋值
最后执行PostNetInit调用Actor的BeginPlay。（参考下面堆栈）
下面截取了客户端接收到同步Actor并初始化的调用堆栈：


图4-2 客户端接收并序列化同步的Actor堆栈图

图4-3 客户端初始化同步过来Actor堆栈图
从上面的描述来看，基本上我们可以很容易的分析出当前的Actor是否被同步，比如在UActorChannel::ReceivedBunch里面打个断点，看看当前通道里有没有你要的Actor就可以了。



1.组件（子对象）同步
组件（还有其他子对象）是挂在Actor上面的，所以组件的同步与Actor同步是紧密相连的，当一个Actor进行同步的时候会判断所有的子对象是否标记了Replicate，如果标记了，就对其以及其属性进行同步。

这些子对象同步方式（RPC等）也与Actor相差无几，实际上他们想要同步的话需要借助ActorChannel创建自己的FObjectReplicator以及属性同步的相关数据结构。简单来说，就是一个Actor身上的组件同步需要借用这个Actor的通道来进行。下面3段代码是服务器序列化子对象准备发送的逻辑：

//UActorChannel::ReplicateActor()  DataChannel.cpp
// The Actor
WroteSomethingImportant |= ActorReplicator->ReplicateProperties( Bunch, RepFlags );
// 子对象的同步操作
WroteSomethingImportant |= Actor->ReplicateSubobjects(this, &Bunch, &RepFlags);
//ActorReplication.cpp
boolAActor::ReplicateSubobjects(UActorChannel *Channel, FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
   check(Channel);
   check(Bunch);
   check(RepFlags);
   bool WroteSomething = false;

   for (int32 CompIdx =0; CompIdx < ReplicatedComponents.Num(); ++CompIdx )
   {
	UActorComponent * ActorComp = ReplicatedComponents[CompIdx].Get();
	//如果组件标记同步
	if (ActorComp && ActorComp->GetIsReplicated())
	{
	   WroteSomething |= ActorComp->ReplicateSubobjects(Channel, Bunch, RepFlags);		// Lets the component add subobjects before replicating its own properties.检测组件否还有子组件
	   WroteSomething |= Channel->ReplicateSubobject(ActorComp, *Bunch, *RepFlags);	// (this makes those subobjects 'supported', and from here on those objects may have reference replicated)	同步该组件	
	}
   }
   return WroteSomething;
}
//DataChannel.cpp
boolUActorChannel::ReplicateSubobject(UObject *Obj, FOutBunch&Bunch, constFReplicationFlags&RepFlags)
{
   if ( !Connection->Driver->GuidCache->SupportsObject( Obj ) )
   {
	FNetworkGUID NetGUID = Connection->Driver->GuidCache->AssignNewNetGUID_Server(Obj );	//Make sure he gets a NetGUID so that he is now 'supported'
   }

   bool NewSubobject = false;
   if (!ObjectHasReplicator(Obj))
   {
	Bunch.bReliable = true;
	NewSubobject = true;
   }
   //组件的属性同步需要先在当前的ActorChannel里面创建新的FObjectReplicator
   bool WroteSomething = FindOrCreateReplicator(Obj).Get().ReplicateProperties(Bunch, RepFlags);
   if (NewSubobject && !WroteSomething)
   {
      ......
   }
   return WroteSomething;
}
下面一段代码是客户端接收服务器同步过来的子对象逻辑：

// void UActorChannel::ProcessBunch( FInBunch & Bunch )DataChannel.cpp
// 该函数前面的代码主要是是进行反序列化当前Actor的相关操作
while ( !Bunch.AtEnd() && Connection != NULL&& Connection->State != USOCK_Closed )
{
   bool bObjectDeleted = false;
   //当前通道的Actor以及反序列化成功，这里开始继续从Bunch里面寻找子对象进行反序列化
   //如果当前Actor没有子组件，这里返回的就是Actor自身
   ......
   TSharedRef<FObjectReplicator>& Replicator = FindOrCreateReplicator( RepObj );
   bool bHasUnmapped = false;
   // 找到当前子对象（或当前Actor）的Replicator以后，这里开始进行属性值的读取了
   if ( !Replicator->ReceivedBunch( Bunch, RepFlags, bHasUnmapped ) )
   {
       ......
   }
   ......
}
前面Actor同步有提到，当从ActorChannel解析Bunch信息的时候就可以尝试对该数据流进行Actor的反序列化。从这段代码可以进一步看出，Actor反序列化之后会立刻开始判断Bunch里面是否存在其子对象，如果存在还会进一步读取子对象同步过来的属性值。如果没有子对象，就读取自身同步过来的属性。

关于子组件的反序列化还分为两种情况。要想理解这两种情况，还需要清楚两个概念——动态组件与静态组件。

对于静态组件：一旦一个Actor被标记为同步，那么这个Actor身上默认所挂载的组件也会随Actor一起同步到客户端（也需要序列化发送）。什么是默认挂载的组件?就是C++构造函数里面创建的默认组件或者在蓝图里面添加构建的组件。所以，这个过程与该组件是否标记为Replicate是没有关系的。

对于动态组件：就是我们在游戏运行的时候，服务器创建或者删除的组件。比如，当玩家走进一个洞穴时，给洞穴里面的火把生成一个粒子特效组件，然后同步到客户端上，当玩家离开的时候再删除这个组件，玩家的客户端上也随之删除这个组件。

对于动态组件，我们必须要设置他的Replicate属性为true，即通过函数 AActorComponent::SetIsReplicated(true)来操作。而对于静态组件，如果我们不想同步组件上面的属性，我们就没有必要设置Replicate属性。下面截取了函数ReadContentBlockHeader部分代码来区分这两种情况：

//静态组件，不需要客户端Spawn
FNetworkGUID NetGUID;
UObject * SubObj = NULL;
Connection->PackageMap->SerializeObject(Bunch, UObject::StaticClass(), SubObj, &NetGUID );
//动态组件，需要在客户端Spawn出来
FNetworkGUID ClassNetGUID;
UObject * SubObjClassObj = NULL;
Connection->PackageMap->SerializeObject(Bunch, UObject::StaticClass(), SubObjClassObj, &ClassNetGUID );
我们在这两段代码看到了FNetworkGUID的使用，因为这里涉及到UObject的引用（指针）同步。对于不同端的同一个对象，他们的内存地址肯定是不同的，那服务器上指向A的指针同步到客户端上如何也能正确的指向A呢？这就需要通过FNetworkGUID来解析，具体细节在下一节属性同步里面分析。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》摄像机系统解析[经验总结]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34897458
目录
一．摄像机工作原理
二．UE4摄像机关系梳理
-2.1 CameraComponent与CameraActor
-2.2 PlayerCameraManger
-2.2.1 ViewTarget
-2.3 CameraComponent，CamerActor与PlayerCameraManger
-2.4 PlayerController与PlayerCameraManger
三．摄像机更新方案
四．摄像机使用细节
-4.1 摄像机位置处理
-4.2 摄像机FOV处理
五．摄像机特殊处理
-5.1 摄像机震动
-5.2 摄像机镜头粒子特效
-5.3 摄像机碰撞
-5.4 摄像机模式切换
-5.5 摄像机后处理
六．其他
文章为原创，首发在CSDN

一. 摄像机工作原理
在游戏中，摄像机是玩家的眼睛，他控制了玩家的视点（POV即PointOfView，后面简称POV）位置以及玩家的视野大小（FOV即FieldOfView，后面简称FOV）。一句话，摄像机决定了我们去观察这个游戏世界。

游戏的类型多种多样，有第一人称的FPS游戏，有第三人称的动作游戏，还有需要统筹全局来观察的RTS游戏。简单来说，第一人称就是把POV放在人眼睛的位置，第三人称就是把POV放在人身后一定距离的位置，RTS就是把POV放到离地面很高的位置。这里说POV要比说摄像机更为准确，因为有的时候摄像机只是一个为了方便大家理解与观察的实体，其实他的位置可以随意，不过为了便于大家理解与使用，我们一般将摄像机位置与视点位置同步。下图的摄像机位置即为POV的位置，紫色的框即为FOV。


图1-1 值为90的FOV

图1-2 值为40的FOV
因为POV在游戏中是会随时变化的，所以我们需要在Tick里面去更新他的位置。所以，从本质上讲，调整摄像机就是不断地更新POV的位置，这样我们也能平滑流畅的观察游戏世界。如果，我们想要切换不同的视角，那就切换我们的POV。如果想要做一些镜头移动特效，就可以利用一些插值的算法来处理POV的位置。如果想要做一些视觉特效，可以直接在摄像机上加一些后处理效果。总之，还是那句话，摄像机决定你如何观察游戏世界。

二. UE4摄像机关系梳理


首先放一张摄像机相关类的关系图，


图2-1 摄像机相关类图
下面开始一一分析各个类之间的关系。

由于大家一般会先去看官方文档，这里就按照官方文档的顺序来解释。



2.1 CameraComponent与CameraActor
CameraComponent组件一般放在控制角色的根节点上，常规的行为与属性都可以在其中进行设置包括POV位置（即组件的位置），FOV，观察模式（分为正交模式和透视模式），宽高比，后处理效果等。

而CameraActor的作用更为简单，就是将CameraComponent组件封装到一个Actor里面来使其可以直接放到一个Level里面。


图2-2 Mods里面可以放置Camera
图2-2Mods里面可以放置Camera

CameraComponent组件里面还包括另外两个组件，一个是UDrawFrustumComponent，另一个是UStaticMeshComponent。UStaticMeshComponent大家很好理解，用来渲染Actor的对象模型，而UDrawFrustumComponent是用来显示摄像机视窗的。（图1-1的紫框，只在编辑器下有）。



2.2 PlayerCameraManger
从名字上理解，我们可以叫他为摄像机管理器，那么他管理的是什么？答案就是视点POV。POV位置真正的计算过程是在这里进行的，你可以在这里处理不同人称视角的POV计算流程，处理摄像机震动与碰撞，也可以对摄像机增加镜头粒子特效（溅血效果等）。

2.2.1 ViewTarget

顾名思义，即观察目标，也就是我们想让摄像机跟随的对象。对于一般的第三人称游戏，我们的摄像机一直是对准着我们控制的角色的，这个角色可以认为就是ViewTarget（不过ViewTarget不仅仅是一个Actor）。ViewTarget定义在PlayerCameraManager里面，负责提供给Manger一个理想的POV。一个ViewTarget结构包含一个Actor对象，该Actor对应的POV信息以及当前的PlayerState。换句话讲，我们一般通过ViewTarget包含的Actor的位置来计算摄像机POV的位置，并把计算后的结果再存储到ViewTarget里面的POV。


图2-3 ViewTarget内部结构
2.3 CameraComponent，CamerActor与PlayerCameraManger
经过前面的介绍，我们知道PlayerCameraManager通过绑定一个ViewTarget来计算POV的位置。一般来说，我们将CameraComponent放进的Actor就是我们理想的ViewTarget。同理，拥有CameraComponent的CameraActor也同样是ViewTarget。

PlayerCameraManager一般有几个摄像机模式（CameraStyle），如下图


而在构造时他默认的模式是另一个


默认模式下，PlayerCameraManager在更新POV的时候会调用Actor的CalcCamera。CalcCamera先判断是否有CameraComponent并且bFindCameraComponentWhenViewTarget是否为true，是的话就获取CameraComponent的位置与朝向，否则就获取ViewTarget的Actor的坐标与朝向来更新视点POV的信息。

其他的模式需要玩家去进一步做详细的计算。如果当前的ViewTarget是一个CameraActor的话，PlayerCameraManager就会直接获取CameraComponent的位置与朝向来更新POV。



2.4 PlayerController与PlayerCameraManger
我们知道，在UE4里面每个Pawn都会有一个对应的Controller，我们自然想让Controller拥有控制Rotation（朝向）的功能（为什么不控制Location？因为Location跟随Viewtarget就可以了）。所以这里有一个UpdateRotation函数来控制朝向。那么他是如何影响到PlayerCameraManager里面对视点的计算呢？

我们可以再回头看一下图2-1，通过观察，我们可以看到一个PlayerController里面有一个PlayerCameraManager属性。当我们旋转鼠标时，这个偏移量会通过AddControllerYawInput与AddControllerPitchInput传入RotationInput。在PlayerController执行UpdateRotation时会获取PlayerCameraManager并通过ProcessViewRotation计算出移动后（也就是将RotationInput计算进去）的Rotation，把这个Rotation赋值给ControlRotation以及Controller所控制的Pawn（也就包括他身上的CameraComponent组件）。


图2-4 Controller接收鼠标旋转流程
最后，经过上面流程，我们的CameraComponent朝向已经被修改，PlayerCameraManager在更新POV的Rotation时获取CameraComponent的朝向即可。（这个就是UE4默认情况下的摄像机处理流程）

假设我们没有任何CameraComponent组件呢？这其实也很简单，在图2-1可以看到一个PlayerCameraManager类会有一个PlayerController属性，这样PlayerCameraManager就可以随时获取当前ViewTarget对应的PlayerController。而且我们在图2-4的流程里面其实已经通过SerControlRotation的获取了当前摄像机计算后的朝向，所以在PlayerCameraManager更新POV朝向的时候，获取Controller的ControlRotation既可。这样，我们在更新POV朝向的时候就不需要获取CameraComponent的朝向了，没有借助任何CameraComponent或是CameraActor。

注：我们看到图2.4里面最后的两步是处理角色朝向的。经过该图里面的处理，玩家会随着摄像机的旋转而旋转。但是目前很多流行的游戏是通过玩家方向键来控制朝向的。
三. 摄像机更新方案
通过上面的介绍，我们基本上了解了摄像机相关类之间的关系。这里再重新梳理一下，

如果我们想实现摄像机的控制，有两个基本方案。

方案一：UE4官方教程，将一个CameraComponent放到我们想控制目标的身上。然后通过获取摄像机组件的位置与朝向更新POV。
方案二：控制的目标可以任意，Viewtarget身上没有CameraComponent。PlayercameraManager通过获取ViewTarget的位置+一定的偏移（PlayerCameraManager有一个TPVCameraOffset和一个FreeCamOffset）来确定POV的位置。而对于朝向，PlayerCameraManager通过获取PlayerController的ControlRotation既可。
我们要知道，PlayerCameraManager这里的计算其实是偏底层一些的。有的时候我们不需要去修改这里的计算也可以处理一些摄像机的设置，比如旋转角度限制，自定义的计算POV朝向这些可以写在PlayerController的CalcCamera里，并在UpdateCameraRotation里面调用。总而言之，我们需要弄清的就是视点POV的位置与朝向到底是如何计算的。

最后再总结一下，摄像机POV计算的要点有两个

一： 你要保证你的计算过程是在Update里面进行的
二： 你要在PlayercameraManager计算POV的时候能获取到你更新后的位置与旋转
有了上面两个条件，你就可以平滑的更新POV的位置与朝向了。

注：到这里，我们已经发现了两个CalcCamera，一个在Actor里面，是用来获取Actor或者他身上的CameraComponent组件位置与朝向的。另一个是PlayerController里的，用来进行自定义对摄像机POV进行处理计算的，默认是不调用的。

图3-1 摄像机更新视点POV流程
四. 摄像机使用细节


4.1 摄像机位置处理
2.4节我们简单提到过一种摄像机的使用流程。游戏初始化后，PlayerCameraManager会把玩家角色的Pawn设置为ViewTarget,然后获取ViewTarget的坐标作为一个基础值。基础值加上玩家身上的CameraOffset就得到了视点POV的位置。不过这里的CameraOffset是相对于ViewTarget局部坐标系的偏移，还要根据当前的角色的朝向以及Mutiplier来做进一步处理。

如果想让玩家在不同状态下调整不同的视角，可以增加多个CameraOffset（如果射击CameraOffset）。然后在不同的状态下切换不同的CameraOffset即可。



4.1 摄像机FOV处理
在很多游戏里面，如果使用弓箭，枪一类的武器，可以进行瞄准。瞄准的实现方法就是修改摄像机的FOV。可以在武器上设置一个OverrideFOV属性，通过在瞄准时更新当前的FOV可以实现瞄准的效果。

五. 摄像机特殊处理


5.1摄像机震动

图5-1 摄像机调整相关类图
这里我们把摄像机相关类图再拿出来看一下。观察到有一个继承于UObject的UCameraModifer类，他的作用就是对摄像机进行相关的调整，这里我们定义任意的Modify类型来继承于UCameraModifer，但实际上我们最常用的就是UCameraModifier_CameraShake（即摄像机震动），他是真正负责执行摄像机震动的类。

在PlayerCameraManager更新POV信息的时候，或根据条件判断是否调用CamraModifier，在该类中有一个TArray<classUCameraModifier*> ModifierList;来保存当前所有的Modifier。遍历的时候如果找到Modifier就会执行对应的修改。默认情况下，引擎提供了一个CameraModifier_CameraShake的Modifier，在执行PlayerManger初始化的时候会通过APlayerCameraManager::CreateCameraModifier添加到ModifierList里面。

同时，我们还可以看到一个UCameraShake类，这个类就是用来设置摄像机震动参数的类，包括震动时间震动幅度等。比如，在UGameplayStatics::PlayWorldCameraShake里 面。我们就需要传入一个TSubclassOf<classUCameraShake> Shake参数。PlayerController里面也有一个ClientPlayCameraShake方法让客户端去调用，里面也需要传入UCameraShake类型。其实，执行摄像机震动的基本原理就是根据传入的UCameraShake参数来添加一个FCameraShakeInstance。具体逻辑参考函数APlayerCameraManager::PlayCameraShake。


图5-2
FCameraShakeInstance是摄像机震动实例，在UCameraModifier_CameraShake里是以数组成员ActiveShakes的形式存在的。每次执行APlayerCameraManager::PlayCameraShake的时候，都会添加一个摄像机的震动实例，当震动结束后，实例会被从ActiveShakes移除。默认的相机震动UCameraModifier_CameraShake只能执行震动逻辑，并不能修改玩家的Rotation，但是CameraModifier里面预留了修改玩家Rotation的接口，UCameraModifier::ProcessViewRotation。我们可以通过修改CameraModifier的这个接口来在震动的同时调整玩家的朝向。

在游戏里面，我们可能调用摄像机震动的情况（及实现方法）有

靠近大型NPC（在NPC的动画蓝图里面添加Notify，通知客户端执行）
开枪（在武器上绑定UCameraShake）
玩家受伤
挥动武器击中目标时（在武器上绑定UCameraShake）
还有很多情况，根据项目需求来决定是否使用。



5.2摄像机镜头粒子特效
在PlayerCameraManager类定义中我们可以看到这样一个属性，他通过在摄像机前面绑定一个粒子特效来实现滴血等效果。通过ClientSpawnCameraLensEffect_Implementation可以使用。效果如下



图5-3 CameraLensEffect实现效果


5.3摄像机碰撞
摄像机的碰撞的逻辑可以写在了PlayerCameraManager的UpdateViewTarget里面（也就是更新视点POV信息的地方），他需要在最后做一个盒型的碰撞检测，如果碰到符合通道条件的物体就会更新视点的坐标。

5.4摄像机模式切换
前面介绍了UE4默认提供了几种摄像机模式给开发者使用，我们常用的有自由摄像机、第一人称、第三人称等。旁观者模式是类似一种自由摄像机的模式。

PlayerCameraManager里面在更新POV时会判断当前的CameraStyle，从而进行不同的计算，比如我们从第三人称视角切换到第一人称视角，POV相对玩家的位置就会改变（从背后变为眼睛附近）。

有一点也要注意一下，不同摄像机的碰撞检测通道可能是不同的。



5.5摄像机后处理
UE4里面的后处理可以通过两种方法完成。第一种是通过在场景里面添加PostProcessVolume，然后摄像机处于该体积内才能产生效果。第二种是在摄像机组件里面添加与设置，这样就不需要把摄像机放在某个特别的位置。前面图4-3的第一张图就是经过高斯模糊以及颜色混合的后处理效果。



5.6 摄像机平滑与延迟Lag
在大部分游戏中，为了得到更好的游戏体验，摄像机的移动都是平滑的。因为摄像机是在每帧都进行更新，所以我们只要保持与我们的ViewTarget固定的距离，就可以得到平滑的效果。

但是如果我们想从当前摄像机立刻切换到另一个摄像机机位，或者我们的ViewTarget发生瞬移，这时候如果不做任何处理，摄像机就会突然的切换（有的时候这样也没什么不好）。假如我们觉得这样切换有点突然，我们只要简单的处理一下就可以了。设置一个插值，让当前的位置逐渐插值到目标位置。（FMath::VInterpTo(当前位置,目标位置, DeltaTime,速度);）

同理，如果想做一个摄像机延迟效果（就是玩家可能突然用技能走出一大段位移，为了体现效果，想让摄像机慢慢的追上玩家），也可以使用类似的方法来实现。

如果有兴趣，可以参考一下UE4第三人称官方例程，然后找到弹簧组件，搜索EnableCameraLag属性，试试效果。当然也可以到代码里面看看他实现的细节。

六. 其他
1.UE4里面的DoUpdateCamera会处理相机viewTarget切换，如果当前摄像机要切换到另一个就在这里处理插值与混合，这个时候就不应该调用UpdateViewTarget。要切换的对象是PendingViewTarget，混合参数为BlendParams。
2.PlayerCameraManager是通过void APlayerController::SpawnPlayerCameraManager()生成的
3.把CameraManager的位置与旋转与视点同步到一起。这样，我们也可以通过摄像机的Manager获取视点的相关信息。同理，把PlayerController的朝向与视点同步，我们也可以获取PlayerController的朝向来获取视点的朝向。
4.下面流程图描述了角色是如何被PlayerCameraManger设置为ViewTarget的。

图6-1 设置玩家控制的Pawn为ViewTarget流程图
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》物理模块浅析[原理分析]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/35686607
目录 一．Mesh组件与物理
二．物理的创建时机
2.1 UStaticMeshComponent的物理创建
2.2 USkeletalMeshComponent的物理创建
三．物理对象的移动
四．UE4与PhysX
4.1 简单碰撞的物理创建
4.2 复杂碰撞的物理创建
4.3 物理创建的后续工作
五．物理约束Constraint
5.1 简单理解物理约束的原理
5.2 物理对象自身约束
5.3 物理约束Actor
5.4 物理约束组件
5.5 SkeletalMesh中的物理约束调整
5.6 UE中的物理约束
六．物理材质


一．Mesh组件与物理
关于UE物理的基本使用，官方文档以及我之前CSDN博客里已经做了较为详细的介绍。

这里主要是从代码方面，简单分析一下UE4里面的物理是如何使用与生效的，StaticMesh以及SkeletalMesh对应的物理都是如何产生与作用的。第四部分会涉及到一些PhyX引擎的内容，简单谈谈UE与PhysX间的交互。

这篇文章只讨论刚体物理。

首先，在游戏中常见的带有物理的物体一般有5种，虽然这5种类型本质上产生物理的规则都大同小异，但为了方便我们只针对StaticMesh与SkeletalMesh来总结。

胶囊体一类（USphereComponent，UBoxComponent，UCapsuleComponent）
静态网格物体StaticMesh
骨骼网格物体SkeletalMesh
Landscape地形
PhysicsVolume（BrushComponent）
对于直接放在场景的石块等，通常是通过3D建模软件导入到引擎中的资产。导入到引擎资源文件夹后就石块模型变成了UStaticMesh，从资源文件夹拖到场景中后就变成了StaticMeshActor。对于带动画表现的玩家模型，是通过3D建模软件导入的带骨骼信息的资产。导入到引擎资源文件夹后就变成了USkeletalMesh，从资源文件夹拖到场景中后就变成了SkeletalMeshActor。当然，单独把SkeletalMeshActor放在场景中就如一个StaticMeshActor一样，没有任何动画，也可能没有任何物理（如果没有特殊处理的话）。

由于UE4提倡组件式的开发，Actor身上的很多特性都是通过组件提供的，所以物理数据都是挂在组件上的而不是Actor上。任何Actor上面都可以挂上N多个组件，因此一个玩家身上就可以有多个UStaticMeshCompnent与USkeletalMeshCompnent（一般还有一个胶囊体作为根组件）。举个简单的例子，玩家自身的模型是一个USkeletalMeshCompnent，然后身上的衣服装备就可以用一个UStaticMeshCompnent来表示。二者最大的差别就是SkeletalMesh可以产生动画，因此他自身的每个骨骼物理也就需要跟随动画而改变，所以相比StaticMesh要复杂不少。

对于一个静态网格物体StaticMesh，他的物理一般在建模软件里面就应该创建好，导入到编辑器时UE就会根据导入的数据创建物理信息，当然UE4本身也提供了物理碰撞的创建，如图1-1所示。不过无论哪种做法，本质上都是在编辑器里给UStaticMeshComponent构建一个UBodySetup，在开始游戏的时候在创建运行时的基本物理数据UBodyInstance。


图1-1 UE编辑器添加碰撞
UBodySetup与UBodyInstance：我个人理解UBodySetup就是一个静态的物理数据，一般在在游戏运行前就已经构建好了[当然，你在游戏运行时创建也没什么问题]。你可以理解为一个类，编译以后就存在了。而UBodyInstance是一个在游戏时真正起作用的物理数据，可以理解为通过这个类创建的对象，运行时才真正出现。通过一个UBodySetup是可以创建出多个UBodyInstance的
而对于骨骼网格物体SkeletalMesh，由于数据比较多，他的物理数据存储在PhysicsAsset里面。在游戏运行的时候，SkeletalMeshComponent会读取物理资产里面的数据UBodySetup随后再通过UBodySetup给角色创建对应的基本物理数据UBodyInstance。再进一步深入就是NVIDA的PhysX物理引擎了（当然你也可以采用BOX2D物理引擎），这篇文章后面会有简单的讲解。

UE4里面除了SkeletalMeshComponent.cpp以外还有SkeletalMeshComponentPhysics.cpp，PhysAnim.cpp用来专门处理SkeletalMeshComponent物理相关的逻辑

图1-2 物理资产
下面的图片描述了Mesh、 Component与物理基本类的基本关系


图1-3 物理相关类图
如果对BodyInstance还是觉得比较陌生的话，不妨结合下面我们熟悉的图来理解。我们知道在给Mesh设置物理的时候需要设置准确的碰撞通道，才能让不同的物理之间有碰撞效果。仔细看一下，CollisionResponses，ObejctType这些其实都是FBodyInstance里面的成员，我们在编辑器里面设置的这些属性其实就是在给BodyInstance设置（进一步还会去给到PhysX里面的PxRigidActor，后面讲）。


图1-4
如果我们想在编辑器里直观的看到是否创建了物理就调用控制台命令Show Collision既可。下图就显示了角色的胶囊体碰撞以及对应的骨骼物理碰撞（多个胶囊体组合）。


图1-5
二．物理的创建时机
前面大致的描述了UE4里面基本组件与物理之间的逻辑关系，我们看到上面无论是Staticmesh还是SkeletalMesh都会通过BodySetup来创建物理，而BodySetup最终又会调用BodyInstance来产生真正的物理。下面我们从游戏内具体的物理初始化流程分析一下。



2.1 UStaticMeshComponent的物理创建
首先是UStaticMeshComponent，可以看到在场景里面加载Actor并注册UActorComponent的时候会对UPrimitiveComponent组件进行物理信息创建。其实除了SkeletalMeshComponent以外，所有继承自UPrimitiveComponent的组件（第一部分提到的那5种都是）都会在注册后就创建物理数据（对于直接继承自UActorComponent的组件，如移动组件就不会执行该操作）。因此除了SkeletalMeshComponent以外（这个后面再分析），其他继承自UPrimitiveComponent的组件物理创建的时机都很明确，也就是UActorComponent被注册的时候创建物理。（当然还有一些特殊情况也需要更新物理，比如更换模型的时候）


图2-1 加载场景StaticMesh物理的创建堆栈图


图2-2 玩家出生时胶囊体物理的创建堆栈图
在注册组件时是否要创建物理数据？可以参考下面代码。其实很明显的有三个条件，

是否已经创建过了
是否能获取到当前的物理场景（物理场景的变量为FPhysScene* PhysicsScene，理解为与游戏世界同时存在的一个物理世界。这个PhysicsScene一般是在初始化World信息，也就是在void InitWorld(const InitializationValues IVS= InitializationValues())时创建）
是否应该创建 ShouldCreatePhysicsState。很明显想控制是否给组件创建对应的物理数据，写在这里最合适不过了。比如，所有继承自UActorComponent而且没有重写该函数的组件都会直接返回false，而UPrimitiveComponent就重写了这个函数。

图2-3 注册时是否创建物理的条件代码截图
2.2 USkeletalMeshComponent的物理创建
USkeletalMeshComponent与其他带物理组件不同，一般来说我们并不会在玩家一出生就创建出所有的骨骼物理，也不会让玩家的骨骼物理一直存在着。原因很简单，就是为了提升性能。对于一般的带物理的组件，我们只需要给他配置一个简单的碰撞体既可（包括Sphere，Box，Capsule等）。这样一个简单的物理组件在游戏运行时的开销是很小的，然而对于一个USkeletalMeshComponent，我们为了精确几乎需要给所有的骨骼都创建一个基本的物理单位，一旦玩家或者NPC过多，这个消耗是非常可观的。然而，我们也不能放弃使用USkeletalMeshComponent的物理，因为一旦我们的游戏想实现精准的打击，攻击不同位置的效果不同的时候，就必须要用到骨骼的物理。因此，常见的解决方案就是在需要的时候创建物理，在不需要的时候就拿掉。

默认引擎的SkeletalMesh物理会一直存在 参考图1-5。实际上，也不是一定要动态创建于删除skeletalMesh组件的物理，要结合游戏考虑是否要优化这一部分。
我们还是从组件的注册说起，USkeletalMeshComponent的物理的初始化与前面的组件不同，他首先重载了void USkeletalMeshComponent::CreatePhysicsState()函数。并通过调用InitArticulated函数来对所有的骨骼来进行物理的初始化，这是组件初始化时的逻辑代码。我们简单分析一下，


图2-4 重载CreatePhysicsState代码截图
可以看到USkeletalMeshComponent创建物理有两个执行路径，一种是和其他组件一样使用基类UPrimitiveComponent的方法创建物理数据，另一种是用USkinnedMeshComponent里面的PhyiscsAsset数据。（bEnablePerPolyCollision这个变量默认是0，而且引擎没有修改过）

所以，可以看出，正常的USkeletalMeshComponent初始化物理是通过函数

void InitArticulated(FPhysScene* PhysScene,bool bForceOnDedicatedServer=false);
来对每一个骨骼来初始化物理的（Articulate表示关节连接的）。这里面会默认调用

BodyInst->CopyBodyInstancePropertiesFrom(&PhysicsAssetBodySetup->DefaultInstance);
根据PhysicsAsset的Default信息来初始化每一块碰撞的BodyInst，这个物理信息与蓝图中的CollisionPresets的设置没有任何关系，默认就是physicsbody。不过实际在运行的时候，碰撞检测以及射线检测使用的都是Mesh上面的CollisionPreset，与这个默认的设置无关。



一般来说，USkeletalMeshComponent在每帧TickComponent的时候都会调用到USkeletalMeshComponent::RefreshBoneTransforms函数，顾名思义就是更新骨骼的坐标旋转等。


图2-5 Tick更新骨骼Transform堆栈图
RefreshBoneTransforms函数里面，可以根据CPU核数等相关参数来决定是否开一个线程来单独更新动画以及相关物理数据（最后还是调用InitArticulated函数创建物理）。


图2-6 开启单独线程来处理动画物理数据
下面的堆栈图就是引擎通过单独开一个线程来处理物理等数据。


图2-7单独线程来处理动画物理数据调用堆栈图
前面我们提到要选择让物理在需要的时候去生成，而在一般状态下要拿掉。那这是如何做到的？其实我们可以在USkeletalMeshComponent::UpdateKinematicBonesToAnim 去处理，这个函数意义是根据动画的变换去更新当前的物理数据，每一帧都需要执行。基本思路就是，每帧都去检测是否需要骨骼物理数据，如果需要我们创建对应的物理数据（已经创建过了就直接返回）。如果检测到当前不再需要更新物理，就调用USkeletalMeshComponent::TermArticulated()删除物理数据。我们已经知道，运行中的物理数据全部存储在BodyInstance里面，而这个函数就会把我们当前存储在Bodies里面的所有BodyInstance数据全部清除。忘记Bodies的朋友可以回头看一USkeletalMeshComponent的类图。

同时这里还有一段注释可以参考一下:
// This below code produces some interesting result here
// - below codes update physics data, so if youdon't update pose, the physics won't have the right result
// - but if we just update physics bone withoutupdate current pose, it will have stale data
// If desired, pass the animation data to thephysics joints so they can be used by motors.
// See if we are going to need to update kinematics
const bool bUpdateKinematics = (KinematicBonesUpdateType != EKinematicBonesUpdateToPhysics::SkipAllBones); 可以把是否更新物理放到这个位置去处理。

另外，对于USkeletalMeshComponent，初始化物理时会bPhysicsRequiredOnDediServer等属性来控制在服务器模式下是否创建物理数据。

三．物理对象的移动
在UE里面，移动逻辑是通过移动组件来完成的。一般来说，一个可移动角色身上要至少挂一个移动组件（控制移动），一个胶囊体组件（也可以是球形等，作为移动组件控制的对象）。

胶囊体身上挂载着简单类型的物理碰撞，移动时必须要带着其身上的物理一起移动。图3-1是移动组件触发物理移动的调用堆栈。简单描述一下，移动组件通过调用胶囊体的InternalSetWorldLocationAndRotation来真实的更新其位置与旋转，更新后会通过函数OnUpdateTransform来触发其物理对象的更新，即UPrimitiveComponent::SendPhysicsTransform。这一步会执行胶囊体身上对应的BodyInstance位置与旋转的更新，再深入一些就是更新物理引擎里面的PxRigidActor对象了。


图3-1 一般的物理移动调用堆栈
如果你发现你的堆栈是图3-2样子的也不用担心，这是由于移动组件开启了bEnableScopedMovementUpdates属性。他等一次移动完全成功后再触发子对象移动，物理移动等，因为移动过程中可能出现移动不合法重置的情况。这个功能有助于提高移动性能。


图3-2 开启延迟更新后的调用堆栈
前面描述的是胶囊体这种简单类型的物理碰撞，如果是一个SkeletalMeshComponent组件呢？他的身上有与骨骼数量相等的BodyInstance，如何移动？

其实本质上差不多，通过堆栈可以看出USkeletalMeshComponent重写了函数OnUpdateTransform，随后会调用UpdateKinematicBonesToPhysics函数更新所有的物理数据。


图3-3 SkeletalMeshComponent更新移动
在更新动画的时候也会触发UpdateKinematicBonesToPhysics函数。


图3-4 更新动画时更新物理
如果开启了物理托管，那么角色的移动就完全交给物理引擎去处理。通过下面这个接口获取物理引擎返回的Transform并更新自己的位置。


图3-5
对于SkeletalMeshComponent，上面的操作只能让组件与根骨骼位置匹配。其他的骨骼还需要通过USkeletalMeshComponent::BlendInPhysics进一步计算，


图3-6
四．UE4与PhysX
前面我们已经了解到BodyInstance在UE逻辑里是一个运行时的物理的基本单位。而实际在PhysX引擎中，也同样存在一个物理基本单位，这个物理单位就PxRigidActor。一个BodyInstance对应一个PxRigidActor（实际上就是BodyInstance::InitBody时创建一个对应的PxRigidActor），这样我们就可以将UE引擎与PhysX引擎结合起来使用了。

这个时候，我再提出一个问题，真正的物理碰撞是如何检测的呢？
这个问题确实值得我们深思，而且不同情况下检测的方法是不一样的。举个例子，想知道两个球是否产生碰撞，那么只要判断两个球心的距离就可以了。而两个复杂模型的碰撞，可能需要通过判断两个三角面是否有交集来判断。我这里提出这个问题，只是想提醒大家，物理引擎里面的Actor也一样需要知道其本身的形状，然后进一步来处理碰撞逻辑。所以，在创建一个基本物理单位PxRigidActor之后，我们还需要给其创建基本的几何形状（在引擎里面叫做Shape），这个逻辑的处理就在函数UBodySetup::AddShapesToRigidActor（新版本叫UBodySetup::AddShapesToRigidActor_AssumesLocked）。看到这个函数，我们就知道Shape是通过UBodySetup来创建的，同时这个几何形状的数据也是存储在UBodySetup里面的。

PhysX里面提供的类型有下面几种，官方声称前四种是简单碰撞，第五种是复杂碰撞，而实际上凸面体碰撞的处理与三角面相似，所以也可以理解为复杂碰撞：

PxSphereGeometry 球形
PxBoxGeometry 盒子
PxCapsuleGeometry 胶囊体（SkeletalMesh常用）
PxConvexMeshGeometry 凸面体
PxTriangleMeshGeometry 三角面


4.1 简单碰撞的物理创建
这5种类型里面，前4种的生成好的物理数据都存储在UBodySetup的FKAggregateGeom AggGeom里面，按照官方文档的分类，我们称他们为简单碰撞类型。实际上，凸面体的碰撞处理并不像前面几个那样简单。

前三种碰撞的添加在代码实现上也比较简单，我们在编辑器添加碰撞的时候会通过函数GenerateSphereAsSimpleCollision，GenerateBoxAsSimpleCollision，GenerateSphylAsSimpleCollision分别将碰撞数据添加AggGeom的SphereElems，BoxElems，SphylElems里面。正如我前面所说的那样，判断两个球体是否碰撞很容易，所以这几种碰撞类型不需要很复杂的数据来记录与处理，PhysX引擎可以很容易的获取到这些碰撞类型对应的数据并做处理。

凸面体与前面三种碰撞类型都不同。由于其可以通过配置生成一个较为复杂的碰撞，而且碰撞体的顶点都是通过算法生成的，所以他需要经过一个物理Cook的过程。这个过程类似渲染，把所有的三角面的顶点信息和索引提供给PhysX引擎随后PhysX利用这些数据Cook出一个完整的碰撞模型，不过这个过程需要一定的时间来执行。一般来说，我们在游戏编辑器添加AutoConvexCollision碰撞并执行Apply的时候，就会执行这个凸面体的Cook过程。Cook的过程与三角面的Cook过程相似，后面再详细分析。（下图是简单类型碰撞的添加）


图4-1
我们知道SkeletonMeshComponent里面使用PhysicsAsset来创建骨骼动画的物理，那PhysicsAsset里面的BodySetup里面的数据是如何初始化的？他里面的shape类型是什么？看下面的两个堆栈，当我们导入一个带有动画的骨骼资产时，首先会判断该SkeletalMesh有没有物理资产。

如果没有就会调用图3-2创建物理资产，随后执行第二步，根据每个骨骼初始化对应的物理。当前引擎中，会针对没有物理资产的SkeletalMesh的每个骨骼默认初始化一个胶囊体类型的简单碰撞。这个类型是通过FPhysAssetCreateParams NewBodyData;初始化后作为参数传递给物理资产的，所以一般来说我们的角色的物理资产都是胶囊体的。


图4-2

图4-3
当然，当你导入模型之后。你也可以根据你的骨骼资产创建一个新的PhysicsAsset，在创建的时候右键骨骼资产文件——Create——CreatePhysicsAsset，随后会弹出下面的界面，可以根据需求针对每个骨骼创建一个指定类型的Shape碰撞。如果想单独调整个别骨骼的碰撞，就要打开PhysicsAsset在编辑界面里单独处理了。（SkeletonMeshComponent的物理并不一定就是简单的胶囊体碰撞，也可能复杂碰撞，下个小结分析）


图4-4

图4-5
4.2 复杂碰撞的物理创建
最后一种碰撞类型是复杂类型，那么有多复杂呢？其实就是根据Mesh的网格信息（也就是三角面的数量）来进行物理的生成，所以模型面数越多那自然就越复杂。生成好的三角面的物理数据都存储在UBodySetup的TriMesh与TriMeshNegX里面。


图4-6
看过官方文档碰朋友肯定知道，我们可以通过StaticMesh里面Collision
Complexity设置来改变其碰撞的复杂度，当我们标记为UseComplexAsSimple的时候，其实就会在此时去除简单碰撞，并给对应的Mesh资产创建一份复杂的物理碰撞，这个时候就会执行三角面的Cook过程。


图4-7

图4-8
看上面的函数堆栈，在更新上面的配置的时候需要重新创建PhysicsMeshs并获取到CookData。GetCookedData就会调用FDerivedDataPhysXCooker里面的FDerivedDataPhysXCooker:: BuildConvex处理凸面体物理或者FDerivedDataPhysXCooker::BuildTriMesh处理三角面的物理数据。更深入一步，在这个两个函数里又分别通过PhysX引擎IPhysXFormat接口里面的PxCooking调用cookConvexMesh函数以及cookTriangleMesh函数。

另外，想要执行Cook，我们一定要准确的获取到碰撞模型的所有顶点信息，对于StaticMesh三角面碰撞。这个顶点信息就是通过渲染的Lod信息来取到的，具体的操作在函数GetPhysicsTriMeshData里面，执行堆栈如下：


图4-9
复杂物理的生成与渲染很像，如果你需要动态的去生成与删除物理，那么一定要慎重考虑这个动态创建的过程消耗如何？我们平时对StaticMesh物理的Cook过程都是在编辑器里面就完成了。如果游戏中做这个操作很有可能造成卡顿，如果非要这么做也可以考虑使用异步线程FNonAbandonableTask来执行这个过程。



官方文档上可以看到静态模型是如何创建复杂物理的，但是好像没有说骨骼资产如何创建，骨骼模型是不是不可以创建？并不是。在4.8以后的版本里，我们打开骨骼资源文件找到bEnablePerPolyCollision属性并勾选既可。在旧版本4.5里面需要到角色蓝图找到对应的SkeletalMesh组件里勾选bEnablePerPolyCollision属性。

注：新版本skeletalMesh组件里也有这个属性，但是勾选无效，这是引擎的一个Bug


4.3 物理创建的后续工作
前面的操作是将函数UBodySetup::CreatePhysicsMeshes()展开，将物理Cook的过程执行完毕。随后，UBodySetup::AddShapesToRigidActor函数会获取AggGeom以及TriMesh里面已经Cook好的数据，创建对应的物理Shape。

另外，我们在创建物理的时候还分为静态与动态两种，他们通过组件上的OwnerComponent->Mobility
!= EComponentMobility::Movable来控制。很明显，静态碰撞与动态碰撞的消耗是不同的。

//创建静态PxRigidActor
GPhysXSDK->createRigidStatic(PTransform);
//创建动态PxRigidActor
GPhysXSDK->createRigidDynamic(PTransform);
截止到这里，我们已经基本上完成了物理数据的初始化。然而，我们知道在游戏里面，还有很多详细的设置，比如碰撞通道，碰撞类型等。这些数据也必须要及时更新与处理，这些逻辑与相关标记的处理在

FBodyInstance::UpdatePhysicsFilterData>FBodyInstance::UpdatePhysicsShapeFilterData()
UpdatePhysicsFilterData是总的物理数据的处理（因为可能还有其他的物理引擎，如Box2D等）。而UpdatePhysicsShapeFilterData是真正的UE逻辑与PhysX逻辑交互的地方。

实际上我们的平时做的碰撞设置CollisionEnabled对应到Physx里面就是这两个操作。

PShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE,true);
PShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);（参考后面的结构体）

图4-10
PhysX里面的Shape标记。

struct PxShapeFlag
{
  enum Enum
  {
    eSIMULATION_SHAPE = (1<<0),
    eSCENE_QUERY_SHAPE = (1<<1),
    eTRIGGER_SHAPE = (1<<2),
    eVISUALIZATION = (1<<3),
    ePARTICLE_DRAIN = (1<<4)
  };
};
关于UE与PhysX之间的交互，就简单介绍到这里。至于更详细的内容，大家有兴趣的话就去源码里面进一步了解吧。

五．物理约束Constraint
物理约束系统作为物理引擎的一项重要组成部分能够提供更真实与更丰富的模拟表现。

前面通过Mesh，胶囊体等组件总结了物理是以一个什么形式存在于游戏世界中的，UE中的物理对象与PhysX的对象是怎样的关系。但是我们没有分析游戏世界是如何模拟真实的物理现象的，比如我们常见的钟摆，弹簧，关门等。

对于两个完全分离的刚体，他们之间的作用是比较容易模拟的，只要在发生碰撞的位置给各自施加一个力就可以了，他们会根据受力情况各自进行模拟移动，不会相互影响。不过，如果我们想模拟一个钟摆的效果，目前的条件就无法完成了。所以，引擎提供了物理约束（Constraint）功能，可以将两个对象绑定在一起根据参数进行物理模拟，方便我们快速的模拟类似的效果。

在Unity中，物理约束更多的是以关节joint的概念存在。本质上物理约束的概念更大一些，关节是针对两个物体的约束，而物理约束可能只对一个物体产生约束。物理约束通常以关节的方式存在于引擎中。



5.1 简单理解物理约束的原理
物理约束顾名思义，是通过对刚体的各个自由度的移动限制来实现特殊的模拟效果。一个普通的刚体运动通过6个自由度来控制，分别是3个位置方向线性位移与3个轴方向的旋转。我们可以分别或者组合的对每个自由度进行控制，比如限制对象只能沿着XOZ平面移动，就可以实现类似摩天轮运动，钟摆的基本效果。

不过在游戏中，我们更对的是对两个对象进行物理约束（也就是关节），那么对两个物体产生物理约束有什么特点？答案是多个Actor的约束需要有特定的参照对象。一旦我们对两个对象进行约束，那么二者就必须有一个统一的约束参照对象，然后根据参照对象的坐标系来进行模拟。通常来说，这个参照对象就是ConstraintActor或者ConstraintComponent。

比如说，我用一个ConstraintActor对两个Actor进行约束，限制他们只能绕X轴旋转。不过，这两个Actor绕谁的X轴旋转？难道是世界坐标系的X轴？显然我们应该选择一个合适的可以配置的参考对象，这个对象就是上面的ConstraintActor，完成配置后Actor就会绕着ConstraintActor的X轴旋转了。



5.2 物理对象自身约束
物理自身约束比较容易理解，他只是单纯的限制自身的物理模拟的位置，不会对其他对象产生影响。所有包含物理数据的对象都可以进行设置，根据配置限制对象只能在某个轴或某个面产生模拟移动。如图5-1


图5-1


5.3 物理约束Actor
他本身是一个Actor对象，利用它可将两个Actors 连接起来（假定成一个物理模拟体），并应用限制和力度。引擎拥有一些默认关节类型 （球窝式ball-and-socket、铰链式hinge、棱柱式prismatic），区别只存在于它们的对Actor的6个自由度的限制差异。可任选一种关节开始，自行进行调整试验。里面的参数比较多，除了基本的限制操作外还可以通过Motor参数添加驱动力，后面会对一些常见的应用场景进行简单进行分析，其他的建议大家查阅相关资料后多去尝试。


图5-2
上图就是物理约束Actor的配置，一个物理约束Actor能且只能绑定两个Actor对象，这两个对象至少有一个要开启物理模拟。如果需要的话，我们也可以将一个SkeletalMesh的骨骼与另一个Actor绑定，甚至我们还可以指定一个Actor的某个组件与另一个Actor的某个组件绑定。具体的操作草考官方文档。

我们还可以对一个Actor进行多次约束绑定来模拟更多效果，举个例子：假如我要模拟一个秋千，剪断一边的绳子后，这边就会下落向另一边旋转。我们可以用两个ConstraintActor绑定秋千上面的支架与下面的秋千板，然后设置秋千支架不可移动。两个ConstraintActor都设置允许3个自由度的旋转（Angular Limits都设置为free），Z值做30cm限制（Linear limit的Zmotion设置为limited），分别放在绳子与木板相连的位置（很重要，因为两个ConstraintActor方向不同，导致其两个方向都不能旋转）。当玩家用道具砍掉一边的绳子后，对一个ConstraintActor解绑，就可以模拟一边被砍断的情形了。



5.4 物理约束组件
物理约束组件（Physics Constraint Components）的使用方法和 物理约束 Actors 相同，不同之处是其在蓝图中使用，可在 C++ 中进行创建。物理约束组件结合了蓝图的灵活和 C++ 的强大，您可利用它对项目中的任意物理形体设置约束。官方文档也有案例，不再赘述。



5.5 SkeletalMesh中的物理约束调整
打开物理资源文件（PhysicsAsset），默认是Body模式，点击按钮我们会看到有一个Constraint Mode，点击就会进入物理约束模式。


图5-3

图5-4
进入物理约束模式后，首先注意红色标记，我们有19个骨骼18个关节，同时也有18个物理约束。其实，这里可以猜出来，UE在创建对应的PhysicsAsset的同时会对每一个骨骼关节创建一个对应的物理约束，这正好符合我们的常识。

那是不是说，我们每次导入一个SkeletalMesh就会完美的创建一个带有物理约束的PhysicsAsset？并不是，每当我们根据一个SkeletalMesh创建一个物理体的时候，是会创建对应的物理资产，但是这个资产往往问题很多，无法使用，如图5-5。可以看到他的胶囊体数量很多，重叠严重，而且物理约束都是默认的值。


图5-5 默认创建的物理资产
在上面的菜单位置，我们可以看到4个默认的物理约束方式，下面一一描述。


图5-6
球窝式ball-and-socket：类似上面图片的效果，一个球状的骨骼塞到凹槽里面，可以在一定空间内旋转，类似人的肘关节。下面完全开放了3个旋转自由度，但通常情况我们经常要对各个方向做一定的限制。


图5-7
铰链式hinge：类似上面图片的效果，两个物体通过铰链相连，只能绕着固定方向旋转，如门的开关。这里完全打开了绕着X轴方向的旋转。


图5-8
棱柱式prismatic：两个刚体间的角度是固定的，只能在一个固定的轴上滑动。这里我们看到只能沿着X轴产生位移。


图5-9
角色关节 Skeletal：其实与球窝式很相似，但是在各个旋转方向上都有限制。


图5-10
下图是官方根据实际情况调整过后的物理约束：可以看出来他把沿着X轴方向的旋转给禁掉了，这样更符合现实情况（可以自己试一下）。

当然，我们可以根据自己的情况做特殊处理，比如角色的骨骼上可能绑定了一个武器，那么这个武器的物理约束就可以设置成6个自由度的。不过这些全都是我们在开启角色物理模拟时才会出现的效果。

在实际应用中，我们很多情况下需要固定一个物体，然后另一个物体相对进行移动或者旋转，比如门，钟摆等的实现。所以只需要开启一个物体的simulates即可。


图5-11
关于约束限制的驱动力，可以通过Motor来添加，有位移驱动与旋转驱动。具体可以参考官方的ContentExample的PhysicsMap。


图5-12


5.6 UE中的物理约束
在UE源码里面，物理约束Actor的类是APhysicsConstraintActor函数，物理约束组件是UPhysicsConstraintComponent。APhysicsConstraintActor本身也是使用约束组件的功能。

约束组件里面最重要的数据就是FConstraintInstance ConstraintInstance，该对象包含了我们在编辑器中所见的各项参数，同时会将相关的约束数据保存到PhysX引擎中的PxD6Joint类型的数据里面。具体细节请查看源码分析。


图5-13


六．物理材质
物理材质在官方上这样定义：用于定义当物理对象和世界进行动态交互时它所做出的反应。
说白了，就是他在游戏世界应该是什么材料的，虽然我们通过材质的表现可以看出来他是一块木头还是一块铁，但实质上普通的材质只是在视觉上达到了效果。真正要在木头上跑步，敲击，采集等等，你肯定还需要其他的逻辑去处理。UE里面提供了物理材质便于你去定义你的游戏世界里面的物理类型（即物理材质），物理材质的创建很简单，编辑器——AddNew——Physics——PhysicalMaterial。创建之后打开就是这样的，参数很少，基本上就是设置一下摩擦系数和物理表面类型，具体可以参考官方文档的介绍。


图6-1
关于表面类型，可以打开编辑器Edit——ProjectSettings——Physics——PhysicalSurface来查看与添加。


图6-2
物理材质添加完之后，需要赋给对应的材质、材质实例、StaticMesh、SkeletonMesh等等，在各个蓝图搜索physicalMaterial既可。另外，对于每一个Mesh（实际上BodyInstance）都存在一个PhysMaterialOverride，可以覆盖你前面设置的物理材质。

最后，简单说一下一般游戏里面的使用场景。

第一点是走路与落地的音效，在PrimalCharacter（玩家与动物通用）里面会通过GetFootPhysicalSurfaceType函数获取脚下地面的材质类型，进而根据检测到的类型播放事先预制好的音效。
第二点是武器击中不同物体对应的特效与音效，思路基本上相同。
</code></pre>
</details>

<details>
<summary>如何学习大型项目的源码？</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/38341879
原创： Jerish 微信公众号——游戏开发那些事



最近有朋友突然问我一个问题 "你怎么把UE4引擎代码看的那么深入的？"

看到问题后我还愣了一下，因为这是第一次有人给我打了个"深入UE4"的标签。其实我接触虚幻引擎满打满算也就两年，确实谈不上深入。只是靠着平时的学习习惯积累，写了一些相关的技术文章。

但这个事却让我突然意识到最容易被我忽略的学习习惯很可能是有一定价值和意义的。我只想着分享我对引擎学习的心得总结，却从没有想过分享我的学习方法，或许后者更为重要。

每一个人做事都有自己的风格与习惯。当你发现身边一个人很优秀的时候，你去看一下他的24小时是怎么度过的，然后再对比一下你的24小时，答案就很明了了。同理，如果你觉得学习源码很困难，不妨请教一下那些比较牛的"过来人"，看一下别人学习源码模块的流程。当然具体来说，影响一个事物的维度，细节，前提条件都很多，别人的方法照搬过来可能是行不通的，比如说别人能一天雷打不动地学10个小时，这个放到有些人身上几乎不可能。这些道理大家都明白，我也不过多阐述。

回归主题，既然标题是“如何学习大型项目的源码”，所以下面我把自己学习虚幻引擎源码（C++）的思路和过程给分享给大家。

虚幻引擎源码大概有几百万行(没有确切统计过，可以参考下面的纯代码加静态库文件夹截图)，最早可以追溯到1998年Epic自主研发的3D游戏——虚幻。对于一个提供了如此完善功能的游戏引擎，可以想象到他的代码是相当复杂的。所以，在学习的一开始你要明确，你的目的不应该是从头到尾地读遍他所有的源码，而是确定好学习目标后，抽丝剥茧地且有条理的整理出某一个具体模块的内容。


UE4纯源码文件夹信息
这里先给出简化版的总结，然后我会针对每条做进一步的阐述。

准备工作:建议准备大块且连续的时间（细碎的时间容易中断类关系的梳理），一个比较方便查找的IDE或工具（VS，Notepad++，UltraEdit，Source Insight等。评论区有朋友推荐Source Insight效果与VS+Visual AssistX差不多），类图工具（staruml，Edraw等）



学习步骤（简化版）:

1.决定要学习的模块，查找官方文档、相关的总结文章，整理出大概的学习内容与目标

2.运行程序，观察表现

3.运行源码，断点调试，从头跟一边源码的执行流程，注意函数堆栈

4.画类图、流程图，先把遇到的重要类记录下来，表明各个类的关系

5.记录问题，把不理解的类或者内容以问题的方式记录下来

6.写文章、笔记，尝试逐个解决之前遗留的问题

2-6可能需要持续的重复进行

学习步骤（详细版）:

1. 查找官方文档、相关的总结文章

比如说我想研究网络模块，首先去官方文档、论坛、wiki里面过一遍网络相关的所有内容，这时候遇到不懂的问题尽可能解决，解决不了的就把问题记下来，先去官方文档看我觉得是非常有必要的，因为这里的文章是最权威的，错误率非常低。然后，去Google、百度搜索相关的文章与帖子，同时可以加入一些技术qq群（有一些水群果断退了就行，保留一些优质的交流群），过一遍这些文章和资料。目前能看到比较好的技术网站大体上就是各个技术对应的官方网站（论坛）、StackOverflow、知乎、博客园、简书、CSDN、一些个人网站等，当然有些网站复制粘贴现象严重，需要自己筛选。建议能找到原文链接的尽量去原文里面看，因为你有可能从原创作者那里看到更多优秀的文章。

2. 在运行程序的时候，我们需要调整各种参数来执行不同的情况，进而观察其表现效果来验证我们的猜想与结论

比如说，对于一个处于休眠状态的Actor属性是否能正常同步，如果客户端属性与服务器一样是否还会执行回调函数等。执行程序可以快速的得到结论，然后根据结论我们可以更快速准确的进行分析。为了提高效率，最好在一开始就设置不同的配置、GM等来在项目运行时动态改变运行内容，因为大型项目一般都是编译型语言，我们可能可能需要频繁的修改代码编译再重新运行。

3.调试可以说是最为关键的一步了，80%的细节需要你在调试中去理解

函数什么时候执行到这里（函数断点）？每一步每一个属性值是多少？属性值什么时候发生变化（条件断点，内存断点）？一个完整的执行流程是什么样的（函数堆栈）？这些问题需要你一点一点的进行跟踪调试，最后再去解决。

4.画图的习惯可能很多人没有，但是我个人觉得这是一个必不可少的环节，因为他可以大幅度提高你对框架理解的速度

对于任何一个复杂的项目，每一个模块都会牵扯到大量的类（排除纯C项目），类的关系错综复杂，而且为了降低耦合还可能用到各种设计模式，这些都大大提高了代码的阅读难度，很有可能你看了3、4个类之后就完全搞混了他们都是干什么的。举例来说，我在看UE4属性同步模块的时候，完全被各个类之间的关系搞蒙了，所以我看到一个类就把他的类图画下来，看到相关的类就记录他们的关系，最后得到了下面这样一个简化的类图。经过梳理后，几句话我就可以概括他们之间的关系。

当然，除了类图以外，还有流程图、时序图，甚至是你自己为了方便发明的“模块关系图”，这时候图的种类与规范其实没有那么重要，只要能帮助你理解就行。


更新一下：我后来意识到VS其实是自带显示类图功能的，可以直接使用这个功能。点击菜单栏——视图——类视图，然后右键你要查看的项目——查看类视图。效果如下图，很明显问题比较多，一是格式太死板不方便阅读，二是不能很好的表示各个类间更进一步的关系（StarUML对于模板类支持的也不好），三是不方便修改。如果是一个小的模块倒是可以用它查看，比较方便。



5.记录的问题有两种：别人给你的问题以及你自己给自己的问题

别人给你的问题：你在阅读的时候不可能一帆风顺，可能在第一步的时候，就已经遇到了无数的问题。这时候不要着急，按照重要程度顺序依次解决，简单的问题直接网上搜一搜，解决不了可以找身边的大神，网上的牛人解决。如果还是不行，就把问题记下来，然后继续学习，当你深入到一定程度的时候，你的问题可能就不攻自破了。

自己给自己的问题：当你解决了别人给你的问题后，你应该已经理解了一大半了。不过，任何人写的文章都不可能覆盖到全部，你需要自己挖掘更多更深的问题，然后自己再去解答，这样你才能做到比别人了解的更多，更能体现出你自己的价值。

6.写文章和写笔记是有区别的，但是都很有意义

写文章这件事相比上面的步骤我觉得不算是必须的，这个适合那些追求完美还能挤出时间的人。你写的东西是要给别人看的，所以你的目的是给别人讲清楚。我在写文章的时候会去考虑这个东西我说的真的对么，有没有把握，考虑的是否全面。在这种自我拷问下，我会尽可能的完善我的知识体系，修改文章中那些看起来不够准确的内容。如果最后能做到给读者讲清楚的话，那你是真的会了。

写笔记相比写文章要轻松很多，我只是把我总结的内容，学习的收获记录下来，不需要考虑太多的东西。虽然没有写文章那么追求完美，但是这个过程中我们可能也会多了很多思考，在之后的学习过程中快速的回忆起自己学习的经验。

备注：第一次执行这个过程是相当漫长和艰难的，如果和我一样一开始知识储备不够，那么几乎每走一步都需要大量的学习和查资料。不过只要坚持下去，你最后会发现自己的收获非常大，阅读其他模块的源码也变得容易很多。
上面只是我学习源码的一个方法，可能并不适合所有人，也还有很多地方可以进一步完善。

最后，我再强调一点，如果只是为了使用好一个工具，你不需要彻彻底底的理解所有内容，因为你的时间是有限的。如果你真的是抱着学习的态度去研究源码细节，那请做好花费大量时间的准备并坚持下去。

有哪些更好的方法或者建议，欢迎留言评论。



更多内容欢迎关注同名微信公众号: 游戏开发那些事
关注后回复“gamebook”，可获取大量游戏开发相关书籍。回复“C++面试”，可获取笔者呕心沥血总结的C++/游戏面试知识。之后还会陆续更新更多关于面试，游戏开发，虚幻引擎等相关的学习资料~
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》多线程机制详解[原理分析]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/38881269
二．"标准"多线程
三．AsyncTask系统
3.1 FQueuedThreadPool线程池
3.2 Asyntask与IQueuedWork
3.3 其他相关技术细节
四．TaskGraph系统
4.1 从Tick函数谈起
4.2 TaskGraph系统中的任务与线程
4.3 TaskGraph系统中的任务与事件
4.4 其他相关技术细节
五．总结


一．概述


多线程是优化项目性能的重要方式之一，游戏也不例外。虽然经常能看到“游戏不适合利用多线程优化”的言论，但我个人觉得这句话更多的是针对GamePlay，游戏中多线程用的一点也不少，比如渲染模块、物理模块、网络通信、音频系统、IO等。下图就展示了UE4引擎运行时的部分线程，可能比你想象的还要多一些。


UE4运行时开启的线程
虽然UE4遵循C++11的标准，但是他并没有使用std::thread，而是自己实现了一套多线程机制（应该是从UE3时代就有了，未考证），用法上很像Java。当然，你如果想用std::thread也是完全没有问题的。

在UE4里面，我们可以自己继承FRunnable接口创建单个线程，也可以直接创建AsyncTask来调用线程池里面空闲的线程，还可以通过TaskGraph系统来异步完成一些自定义任务。虽然本质相同，但是用法不同，理解上也要花费不少时间，这篇文章会对里面的各个机制逐个分析并做出总结，但并不会深入讨论线程的实现原理、线程安全等内容。另外，由于个人接触多线程编程的时间不长，有一些内容可能不是很准确，欢迎大家一起讨论。



二．“标准”多线程


我们先从最基本的创建方式谈起，这里的“标准”只是一个修饰。其实就是创建一个继承自FRunnable的类，把这个类要执行的任务分发给其他线程去执行。FRunnable就是一个很简单的类，里面只有5，6个函数接口，为了与真正的线程区分，我这里称FRunnable为“线程执行体”。

//Runnable.h
class CORE_API FRunnable
{
public:
	/**
	 * Initializes the runnable object.
	 *
	 * This method is called in the context of the thread object that aggregates this, not the
	 * thread that passes this runnable to a new thread.
	 *
	 * @return True if initialization was successful, false otherwise
	 * @see Run, Stop, Exit
	 */
	virtual bool Init()
	{
		return true;
	}

	/**
	 * Runs the runnable object.
	 *
	 * This is where all per object thread work is done. This is only called if the initialization was successful.
	 *
	 * @return The exit code of the runnable object
	 * @see Init, Stop, Exit
	 */
	virtual uint32 Run() = 0;

	/**
	 * Stops the runnable object.
	 *
	 * This is called if a thread is requested to terminate early.
	 * @see Init, Run, Exit
	 */
	virtual void Stop() { }

	/**
	 * Exits the runnable object.
	 *
	 * Called in the context of the aggregating thread to perform any cleanup.
	 * @see Init, Run, Stop
	 */
	virtual void Exit() { }

	/**
	 * Gets single thread interface pointer used for ticking this runnable when multi-threading is disabled.
	 * If the interface is not implemented, this runnable will not be ticked when FPlatformProcess::SupportsMultithreading() is false.
	 *
	* @return Pointer to the single thread interface or nullptr if not implemented.
	 */
	virtual class FSingleThreadRunnable* GetSingleThreadInterface( )
	{
		return nullptr;
	}

	/** Virtual destructor */
	virtual ~FRunnable() { }
};
看起来这么简单个类，我们是不是可以不继承他，单独写一个类再把这几个接口放进去呢？当然不行，实际上，在实现多线程的时候，我们需要将FRunnable作为参数传递到真正的线程里面，然后才能通过线程去调用FRunnable的Run，也就是我们具体实现的类的Run方法（通过虚函数覆盖父类的Run）。所谓真正的线程其实就是FRunnableThread，不同平台的线程都继承自他，如FRunnableThreadWin，里面会调用Windows平台的创建线程的API接口。下图给出了FRunnable与线程之间的关系类图：




在实现的时候，你需要继承FRunnable并重写他的那几个函数，Run()里面表示你在线程里面想要执行的逻辑。具体的实现方式网上有很多案例，这里给出UE4Wiki的教程链接：

https://ue4community.wiki/legacy/multi-threading:-how-to-create-threads-in-ue4-0bsy2g96
​ue4community.wiki/legacy/multi-threading:-how-to-create-threads-in-ue4-0bsy2g96
三．AsyncTask系统


说完了UE4“标准”线程的使用，下面我们来谈谈稍微复杂一点的AsyncTask系统。AsyncTask系统是一套基于线程池的异步任务处理系统。如果你没有接触过UE4多线程，用搜索引擎搜索UE4多线程时可能就会看到类似下面这样的用法。

        //AsyncWork.h
        class ExampleAsyncTask : public FNonAbandonableTask
	{
		friend class FAsyncTask<ExampleAsyncTask>;

		int32 ExampleData;

		ExampleAsyncTask(int32 InExampleData)
		 : ExampleData(InExampleData)
		{
		}

		void DoWork()
		{
			... do the work here
		}

		FORCEINLINE TStatId GetStatId() const
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(ExampleAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
		}
	};

	void Example()
	{

		//start an example job

		FAsyncTask<ExampleAsyncTask>* MyTask = new FAsyncTask<ExampleAsyncTask>( 5 );
		MyTask->StartBackgroundTask();

		//--or --

		MyTask->StartSynchronousTask();

		//to just do it now on this thread
		//Check if the task is done :

		if (MyTask->IsDone())
		{
		}

		//Spinning on IsDone is not acceptable( see EnsureCompletion ), but it is ok to check once a frame.
		//Ensure the task is done, doing the task on the current thread if it has not been started, waiting until completion in all cases.

		MyTask->EnsureCompletion();
		delete Task;
	}
没错，这就是官方代码里面给出的一种异步处理的解决方案示例。不过你可能更在意的是这个所谓多线程的用法，看起来非常简单，但是却找不到任何带有“Thread”或“Runnable”的字样，那么他也是用Runnable的方式做的么？答案肯定是Yes。只不过封装的比较深，需要我们深入源码才能明白其中的原理。

注：Andriod多线程开发里面也会用到AsyncTask，二者的实现原理非常相似。
3.1 FQueuedThreadPool线程池
在介绍AsynTask之前先讲一下UE里面的线程池，FQueuedThreadPool。和一般的线程池实现类似，线程池里面维护了多个线程FQueuedThread与多个任务队列IQueuedWork，线程是按照队列的方式来排列的。在引擎PreInit的时候执行相关的初始化操作，代码如下

// FEngineLoop.PreInit   LaunchEngineLoop.cpp
if (FPlatformProcess::SupportsMultithreading())
{
	{
		GThreadPool = FQueuedThreadPool::Allocate();
		int32 NumThreadsInThreadPool = FPlatformMisc::NumberOfWorkerThreadsToSpawn();

		// we are only going to give dedicated servers one pool thread
		if (FPlatformProperties::IsServerOnly())
		{
		    NumThreadsInThreadPool = 1;
		}
		verify(GThreadPool->Create(NumThreadsInThreadPool, 128 * 1024));
	}
#ifUSE_NEW_ASYNC_IO
	{
		GIOThreadPool = FQueuedThreadPool::Allocate();
		int32 NumThreadsInThreadPool = FPlatformMisc::NumberOfIOWorkerThreadsToSpawn();
		if (FPlatformProperties::IsServerOnly())
		{
		    NumThreadsInThreadPool = 2;
		}
		verify(GIOThreadPool->Create(NumThreadsInThreadPool, 16 * 1024, TPri_AboveNormal));
	}
#endif// USE_NEW_ASYNC_IO

#ifWITH_EDITOR
	// when we are in the editor we like to do things like build lighting and such
	// this thread pool can be used for those purposes
	GLargeThreadPool = FQueuedThreadPool::Allocate();
	int32 NumThreadsInLargeThreadPool = FMath::Max(FPlatformMisc::NumberOfCoresIncludingHyperthreads() - 2, 2);
		
	verify(GLargeThreadPool->Create(NumThreadsInLargeThreadPool, 128 * 1024));
#endif
}
这段代码我们可以看出，专有服务器的线程池GThreadPool默认只开一个线程，非专有服务器的根据核数开（CoreNum-1）个线程。编辑器模式会另外再创建一个线程池GLargeThreadPool，包含（LogicalCoreNum-2）个线程，用来处理贴图的压缩和编码相关内容。

在线程池里面所有的线程都是FQueuedThread类型，不过更确切的说FQueuedThread是继承自FRunnable的线程执行体，每个FQueuedThread里面包含一个FRunnableThread作为内部成员。

相比一般的线程，FQueuedThread里面多了一个成员FEvent* DoWorkEvent，也就是说FQueuedThread里面是有一个事件触发机制的。那么这个事件机制的作用是什么？一般情况下来说，就是在没有任务的时候挂起这个线程，在添加并分配给该线程任务的时候激活他，不过你可以灵活运用它，在你需要的时候去动态控制线程任务的执行与暂停。前面我们在给线程池初始化的时候，通过FQueuedThreadPool的Create函数创建了多个FQueuedThread，然后每个FQueuedThread会执行Run函数，里面有一段逻辑如下：

//ThreadingBase.cpp
bool bContinueWaiting = true;
while(bContinueWaiting )
{				
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT( "FQueuedThread::Run.WaitForWork" ), STAT_FQueuedThread_Run_WaitForWork, STATGROUP_ThreadPoolAsyncTasks );
	// Wait for some work to do
	bContinueWaiting = !DoWorkEvent->Wait( 10 );
}
//windows平台下的wait
bool FEventWin::Wait(uint32 WaitTime, const bool bIgnoreThreadIdleStats/*= false*/)
{
	WaitForStats();

	SCOPE_CYCLE_COUNTER(STAT_EventWait );
	check(Event );

	FThreadIdleStats::FScopeIdleScope(bIgnoreThreadIdleStats );
	return (WaitForSingleObject( Event, WaitTime ) == WAIT_OBJECT_0);
}
我们看到，当DoWorkEvent执行Wait的时候，如果该线程的Event处于无信号状态（默认刚创建是无信号的），那么wait会等待10毫秒并返回false，线程处于While无限循环中。如果线程池添加了任务（AddQueuedWork）并执行了DoWorkEvent的Trigger函数，那么Event就会被设置为有信号，Wait函数就会返回true，随后线程跳出循环进而处理任务。

注：FQueuedThread里的DoWorkEvent是通过FPlatformProcess::GetSynchEventFromPool();从EventPool里面获取的。WaitForSingleObject等内容涉及到Windows下的事件机制，大家可以自行到网上搜索相关的使用，这里给出一个官方的使用案例。


目前我们接触的类之间的关系如下图：


3.2 Asyntask与IQueuedWork
线程池的任务IQueuedWork本身是一个接口，所以得有具体实现。这里你就应该能猜到，所谓的AsynTask其实就是对IQueuedWork的具体实现。这里AsynTask泛指FAsyncTask与FAutoDeleteAsyncTask两个类，我们先从FAsyncTask说起。

FAsyncTask有几个特点，

FAsyncTask是一个模板类，真正的AsyncTask需要你自己写。通过DoWork提供你要执行的具体任务，然后把你的类作为模板参数传过去
使用FAsyncTask就默认你要使用UE提供的线程池FQueuedThreadPool，前面代码里说明了在引擎PreInit的时候会初始化线程池并返回一个指针GThreadPool。在执行FAsyncTask任务时，如果你在执行StartBackgroundTask的时候会默认使用GThreadPool线程池，当然你也可以在参数里面指定自己创建的线程池
创建FAsyncTask并不一定要使用新的线程，你可以调用函数StartSynchronousTask直接在当前线程上执行任务
FAsyncTask本身包含一个DoneEvent，任务执行完成的时候会激活该事件。当你想等待一个任务完成时再做其他操作，就可以调用EnsureCompletion函数，他可以从队列里面取出来还没被执行的任务放到当前线程来做，也可以挂起当前线程等待DoneEvent激活后再往下执行
FAutoDeleteAsyncTask与FAsyncTask是相似的，但是有一些差异，

默认使用UE提供的线程池FQueuedThreadPool，可以通过参数指定使用其他线程池
FAutoDeleteAsyncTask在任务完成后会通过线程池的Destroy函数删除自身或者在执行DoWork后删除自身，而FAsyncTask需要手动delete
包含FAsyncTask的特点1和特点3
总的来说，AsyncTask系统实现的多线程与你自己字节继承FRunnable实现的原理相似，不过他在用法上比较简单，而且还可以直接借用UE4提供的线程池，很方便。

最后我们再来梳理一下这些类之间的关系：


AsyncTask系统相关类图
3.3 其他相关技术细节
大家在看源码的时候可能会遇到一些疑问，这里简单列举并解释一下

1. FScopeLock

FScopeLock是UE提供的一种基于作用域的锁，思想类似RAII机制。在构造时对当前区域加锁，离开作用域时执行析构并解锁。UE里面有很多带有“Scope”关键字的类，如移动组件中的FScopedMovementUpdate，Task系统中的FScopeCycleCounter，FScopedEvent等，他们的实现思路是类似的。

2. FNonAbandonableTask

继承FNonAbandonableTask的Task不可以在执行阶段终止，即使执行Abandon函数也会去触发DoWork函数。

       // FAutoDeleteAsyncTask
	virtual void Abandon(void)
	{
		if (Task.CanAbandon())
		{
			Task.Abandon();
			delete this;
		}
		else
		{
			DoWork();
		}
	}
	// FAsyncTask
	virtual void Abandon(void)
	{
		if (Task.CanAbandon())
		{
			Task.Abandon();
			check(WorkNotFinishedCounter.GetValue() == 1);
			WorkNotFinishedCounter.Decrement();
		}
		else
		{
			DoWork();
		}
		FinishThreadedWork();
	}
3.AsyncTask与转发构造

通过本章节开始的例子，我们知道创建自定义任务的方式如下

FAsyncTask<ExampleAsyncTask>*MyTask= new FAsyncTask<ExampleAsyncTask>(5);

括号里面的5会以参数转发的方式传到的ExampleAsyncTask构造函数里面，这一步涉及到C++11的右值引用与转发构造，具体细节可以去网上搜索一下。

/** Forwarding constructor. */
template <typename Arg0Type, typename... ArgTypes>
FAsyncTask(Arg0Type&& Arg0, ArgTypes&&... Args)
	: Task(Forward<Arg0Type>(Arg0), Forward<ArgTypes>(Args)...)
{
	Init();
}
四．TaskGraph系统


说完了FAsyncTask系统，接下来我们再谈谈更复杂的TaskGraph系统（应该不会有比他更复杂的了）。Task Graph 系统是UE4一套抽象的异步任务处理系统，可以创建多个多线程任务，指定各个任务之间的依赖关系，按照该关系来依次处理任务。具体的实现方式网上也有很多案例，这里先给出UE4Wiki的教程链接：

Multi-Threading: Task Graph System
​wiki.unrealengine.com/Multi-Threading:_Task_Graph_System
建议大家先了解其用法，然后再往下阅读。

4.1 从Tick函数谈起
平时调试的时候，我们随便找个Tick断点一下都能看到类似下图这样的函数堆栈。如果你前面的章节都看懂的话，这个堆栈也能大概理解。World在执行Tick的时候，触发了FNamedTaskThread线程去执行任务（FTickFunctionTask），任务FTickFunctionTask具体的工作内容就是执行ACtorComponent的Tick函数。其实，这个堆栈也说明了所有Actor与Component的Tick都是通过TaskGraph系统来执行的（在TG_PrePhysics阶段）。


组件Tick的函数堆栈
不过你可能还是会有很多问题，TaskGraph断点为什么是在主线程里面?FNamedTaskThread是什么意思？FTickFunctionTask到底是在哪个线程执行？答案在下一小节逐步给出。



4.2 TaskGraph系统中的任务与线程
既然是Task系统，那么应该能猜到他和前面的AsyncTask系统相似，我们可以创建多个Task任务然后分配给不同的线程去执行。在TaskGraph系统里面，任务类也是我们自己创建的，如FTickFunctionTask、FReturnGraphTask等，里面需要声明DoTask函数来表示要执行的任务内容，GetDesiredThread函数来表示要在哪个线程上面执行，大概的样子如下：

class FMyTestTask
{
        public:
         FMyTestTask()//send in property defaults here
        {
        }
        static const TCHAR*GetTaskName()
	{
		return TEXT("FMyTestTask");
	}
	FORCEINLINE static TStatId GetStatId()
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTestTask, STATGROUP_TaskGraphTasks);
	}
	/** return the thread for this task **/
	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}
 
	/*
        namespace ESubsequentsMode
       {
		enum Type
		{
			// 存在后续任务
			TrackSubsequents,
			// 没有后续任务
			FireAndForget
		};
	}
	*/
	static ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}
 
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		
	}
};
而线程在该系统里面称为FWorkerThread，通过全局的单例类FTaskGraphImplementation来控制创建和分配任务的，默认情况下会开启5个基本线程，额外线程的数量则由下面的函数NumberOfWorkerThreadsToSpawn来决定，FTaskGraphImplementation的初始化在FEngineLoop.PreInit里面进行。当然如果平台本身不支持多线程，那么其他的工作也会在GameThread里面进行。

FTaskGraphImplementation(int32)
{
	bCreatedHiPriorityThreads = !!ENamedThreads::bHasHighPriorityThreads;
	bCreatedBackgroundPriorityThreads = !!ENamedThreads::bHasBackgroundThreads;

	int32 MaxTaskThreads = MAX_THREADS;
	int32 NumTaskThreads = FPlatformMisc::NumberOfWorkerThreadsToSpawn();

	// if we don't want any performance-based threads, then force the task graph to not create any worker threads, and run in game thread
	if (!FPlatformProcess::SupportsMultithreading())
	{
		// this is the logic that used to be spread over a couple of places, that will make the rest of this function disable a worker thread
		// @todo: it could probably be made simpler/clearer
		// this - 1 tells the below code there is no rendering thread
		MaxTaskThreads = 1;
		NumTaskThreads = 1;
		LastExternalThread = (ENamedThreads::Type)(ENamedThreads::ActualRenderingThread - 1);
		bCreatedHiPriorityThreads = false;
		bCreatedBackgroundPriorityThreads = false;
		ENamedThreads::bHasBackgroundThreads = 0;
		ENamedThreads::bHasHighPriorityThreads = 0;
	}
	else
	{
		LastExternalThread = ENamedThreads::ActualRenderingThread;
	}
		
	NumNamedThreads = LastExternalThread + 1;

	NumTaskThreadSets = 1 + bCreatedHiPriorityThreads + bCreatedBackgroundPriorityThreads;

	// if we don't have enough threads to allow all of the sets asked for, then we can't create what was asked for.
	check(NumTaskThreadSets == 1 || FMath::Min<int32>(NumTaskThreads * NumTaskThreadSets + NumNamedThreads, MAX_THREADS) == NumTaskThreads * NumTaskThreadSets + NumNamedThreads);
	NumThreads = FMath::Max<int32>(FMath::Min<int32>(NumTaskThreads * NumTaskThreadSets + NumNamedThreads, MAX_THREADS), NumNamedThreads + 1);
        .......
}
//GenericPlatformMisc.cpp
int32 FGenericPlatformMisc::NumberOfWorkerThreadsToSpawn()
{
	static int32 MaxGameThreads = 4;
	static int32 MaxThreads = 16;

	int32 NumberOfCores = FPlatformMisc::NumberOfCores();//物理核数，4核8线程的机器返回的是4
	int32 MaxWorkerThreadsWanted = (IsRunningGame() || IsRunningDedicatedServer() || IsRunningClientOnly()) ? MaxGameThreads :MaxThreads;
	// need to spawn at least one worker thread (see FTaskGraphImplementation)
	return FMath::Max(FMath::Min(NumberOfCores - 1, MaxWorkerThreadsWanted), 1);
}

前面提到的FWorkerThread虽然可以理解为工作线程，但其实他不是真正的线程。FWorkerThread里面有两个重要成员，一个是FRunnableThread* RunnableThread，也就是真正的线程。另一个是FTaskThreadBase* TaskGraphWorker，即继承自FRunnable的线程执行体。FTaskThreadBase有两个子类，FTaskThreadAnyThread和FNamedTaskThread，分别表示非指定名称的任意Task线程执行体和有名字的Task线程执行体。我们平时说的渲染线程、游戏线程就是有名称的Task线程，而那些我们创建后还没有使用到的线程就是非指定名称的任意线程。


非指定名称的任意线程
在引擎初始化FTaskGraphImplementation的时候，我们就会默认构建24个FWorkerThread工作线程（这里支持最大的线程数量也就是24），其中里面有5个是默认带名字的线程，StatThread、RHIThread、AudioThread、GameThread、ActualRenderingThread，还有前面提到的N个非指定名称的任意线程，这个N由CPU核数决定。对于带有名字的线程，他不需要创建新的Runnable线程，因为他们会在其他的时机创建，如StatThread以及RenderingThread会在FEngineLoop.PreInit里创建。而那N个非指定名称的任意线程，则需要在一开始就手动创建Runnable线程，同时设置其优先级比前面线程的优先级要低。到这里，我们应该可以理解，有名字的线程专门要做他名字对应的事情，非指定名称的任意线程则可以用来处理其他的工作，我们在CreateTask创建任务时会通过自己写好的函数决定当前任务应该在哪个线程执行。


运行中所有的WorldThreads
现在我们可以先回答一下上一节的问题了，FTickFunctionTask到底是在哪个线程执行？答案是游戏主线程，我们可以看到FTickFunctionTask的Desired线程是Context.Thread，而Context.Thread是在下图赋值的，具体细节参考FTickTaskManager与FTickTaskLevel的使用。

/** return the thread for this task **/
FORCEINLINEENamedThreads::TypeGetDesiredThread()
{
	return Context.Thread;
}

context线程类型的初始化
这里我们再思考一下，如果我们将多个任务投放到一个线程那么他们是按照什么顺序执行的呢？这个答案需要分两种情况解答，对于投放到FTaskThreadAnyThread执行的任务会在创建的时候按照优先级放到IncomingAnyThreadTasks数组里面，然后每次线程完成任务后会从这个数组里面弹出未执行的任务来执行，他的特点是我们有权利随时修改和调整这个任务队列。而对于投放到FNamedTaskThread执行的任务，会被放到其本身维护的队列里面，通过FThreadTaskQueue来处理执行顺序，一旦放到这个队列里面，我们就无法随意调整任务了。


4.3 TaskGraph系统中的任务与事件
虽然前面已经比较细致的描述了TaskGraph系统的框架，但是一个非常重要的特性我们还没讲到，就是任务依赖的实现原理。怎么理解任务依赖呢？简单来说，就是一个任务的执行可能依赖于多个事件对象，这些事件对象都触发之后才会执行这个任务。而这个任务完成后，又可能触发其他事件，其他事件再进一步触发其他任务，大概的效果是下图这样。


任务与事件的依赖关系图
每个任务结束分别触发一个事件，Task4需要等事件A、B都完成才会执行，并且不会接着触发其他事件。Task5需要等事件B、C都完成，并且会触发事件D，D事件不会再触发任何任务。当然，这些任务和事件可能在不同的线程上执行。

这里再看一下Task任务的创建代码，分析一下先决依赖事件与后续等待事件都是如何产生的。

FGraphEventRef Join=TGraphTask<FVictoryTestTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady();
CreateTask的第一个参数就是该任务依赖事件数组（这里为NULL），如果传入一个事件数组的话，那么当前任务就会通过SetupPrereqs函数设置这些依赖事件，并且在所有依赖事件都触发后再将该任务放到任务队列里面分配给线程执行。

当执行CreateTask时，会通过FGraphEvent::CreateGraphEvent()构建一个新的后续事件，再通过函数ConstructAndDispatchWhenReady返回。这样我们就可以在当前的位置执行

FTaskGraphInterface::Get().WaitUntilTaskCompletes(Join, ENamedThreads::GameThread_Local);
让当前线程等待该任务结束并触发事件后再继续执行，当前面这个事件完成后，就会调用DispatchSubsequents()去触发他后续的任务。WaitUntilTaskCompletes函数的第二个参数必须是当前的线程类型而且是带名字的。


Task系统相关类图
4.4 其他相关技术细节
1.FThreadSafeCounter

通过调用不同平台的原子操作来实现线程安全的计数

int32 Add( int32 Amount )
{
	return FPlatformAtomics::InterlockedAdd(&Counter, Amount);
}
2. Task的构造方式

我们看到相比AsyncTask，TaskGraph的创建可谓是既新奇又复杂，首先要调用静态的CreateTask，然后又要通过返回值执行ConstructAndDispatchWhenReady。那么这么做的目的是什么呢？按照我个人的理解，主要是为了能把想要的参数都传进去。其实每创建一个任务，都需要传入两套参数，一套参数指定依赖事件，属于任务系统的自身特点，另一套参数传入玩家自定义任务的相关参数。为了实现这个效果，UE先通过工厂方法创建抽象任务把相关特性保存进去，然后通过内部的一个帮助类FConstructor构建一个真正的玩家定义的任务。如果C++玩的不溜，这样的方法还真难想出来。（这是我个人猜测，如果你有更好的理解欢迎留言评论）

3. FScopedEvent

在上一节讲过，带有Scope关键字的基本都是同一个思想，在构造的时候初始化析构的时候执行某些特殊的操作。FScopedEvent作用是在当前作用域内等待触发，如果没有激活该事件，就会一直处于Wait中。

4. WaitUntilTaskCompletes的实现机制

顾名思义，该函数的功能就是在任务结束之前保持当前线程的等待。不过他的实现确实很有趣，第一个参数是等待的事件Event，第二个参数是当前线程类型。如果当前的线程没有任何Task，他会判断传入的事件数组是否都完成了，完成即可返回，没有完成就会构建一个FReturnGraphTask类型的任务，然后执行ProcessThreadUntilRequestReturn等所有的依赖事件都完成后才会返回。

// named thread process tasks while we wait
TGraphTask<FReturnGraphTask>::CreateTask(&Tasks, CurrentThread).ConstructAndDispatchWhenReady(CurrentThread);
ProcessThreadUntilRequestReturn(CurrentThread);
如果当前的线程有Task任务，他就创建一个ScopeEvent，并执行TriggerEventWhenTasksComplete等待前面传入的Tasks都完成后再返回。

FScopedEvent Event;
TriggerEventWhenTasksComplete(Event.Get(), Tasks, CurrentThreadIfKnown);


五．总结


到这里，我们已经看到了三种使用多线程的方式，每种机制里面都有很多技术点值得我们深入学习。关于机制的选择这里再给出一点建议：

对于消耗大的，复杂的任务不建议使用TaskGraph，一是因为TaskGraph如果被分配到游戏线程，就会阻塞整个游戏线程的执行，二是即使你不在那几个有名字的线程上执行，也可能会影响到游戏的其他逻辑。比如物理计算相关的任务就是在非指定名称的线程上执行的（参考PhysScene_PhysX.cpp中的FPhysXTask）。这种复杂的任务，建议你自己继承Runnable创建线程，或者使用AsynTask系统，AsynTask使用的都是新建的线程池里面的线程，一般与游戏Tick是无关的。
而对于简单的任务，或者想比较方便的实现线程的之间的依赖等待关系，直接扔给TaskGraph就可以了。


FAutoConsoleTaskPriority 物理更新默认使用AnyThread
另外，不要在非GameThread线程内执行下面几个操作：

不要 Spawn / Modify/ delete UObjects or AActors
不要使用定时器 TimerManager
不要使用任何绘制接口，例如 DrawDebugLine
一开始我也不是很理解，所以就在其他线程里面执行了Spawn操作，然后就蹦在了下面的地方。可以看到，SpawnActor的时候会执行物理数据的初始化，而这个操作是必须要在主线程里面执行的，我猜其他的位置肯定还有很多类似的宏。至于原因，我想就是我们最前面提到的“游戏不适合利用多线程优化”，游戏GamePlay中各个部分非常依赖顺序，多线程没办法很好的处理这些关系。再者，游戏逻辑如此复杂，你怎么做到避免“竞争条件”呢？到处加锁么？我想那样的话，游戏代码就没法看了吧。


在其他线程Spawn导致崩溃
最后，我们再来一张全家福吧~


多线程系统类图（完整）
</code></pre>
</details>

<details>
<summary>史上最全的C++/游戏开发面试问题总结（一）——C++基础</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/47869981
笔者毕业两年多，前一阵通过猎头拿到了腾讯互娱以及网易游戏等多个客户端研发offer (UE4/C++）。在面试前夕，对C++进行了较为全面的复习和总结，乐观估计可以涵盖80%左右的面试基础问题。

这个系列的文章预计有《C++基础》、《内存、STL、虚函数相关》、《数据结构与算法》、《操作系统》、《计算机网络》、《面试准备与技巧》六篇（后续可能会调整），每篇都是以问答的形式分享并给出了参考资料的链接地址，这个系列的文章会先发布到我的微信公众号上，然后更新到知乎专栏。大部分问题回答的比较简洁，需要大家去仔细阅读参考资料的具体内容，当然也可以直接问我（人多的话会考虑建一个群）~

个人觉得如果这些问题你全部搞懂的话，大部分面试官在C++上就拿你没什么办法或者说不会再进一步为难你了。不过想彻底理解所有内容也并不容易，这里面涉及到操作系统、数据结构、计算机系统原理、汇编等基础内容，涉及到的书籍包括《C++ Primer》《Inside the C++ Object Model》《Effctive C++》《More Effctive C++》《C++ Template》《The Design and Evolution of C++》《STL源码剖析》《深入理解计算机系统》等。



问：了解const么？哪些时候用到const？与宏定义有什么差异？（提问概率：★★★★）

简单理解，const的目的就是定义一个“不会被修改的常量”，可以修饰变量、引用、指针，可以用于函数参数、成员函数修饰、成员变量，修饰成员函数本质上就是修饰“this”指针，所以不能修改函数内部的成员变量。使用const可以减少代码出错的概率，我们通常要注意的是区分常量指针（指向常量的指针）和指针常量（地址是常量，指针指向的地址不变）以及合理的在函数参数里面使用。具体的情况可以参考下面的书籍与资料。

const修饰的如果是普通对象，那么非const对象不可以随便赋值给const对象，因为const对象只会初始化一次。const对象如果修饰的是常量指针（const int* X），常量指针不可以赋值给非常量指针，因为赋值后，非常量指针就可以修改常量指针指向的那块内存。

相比宏定义，const在编译期也会起作用（宏定义只是预编译期），会做一些类型检查，方便调试。而且，const不需要在每个用到的地方都申请一块内存空间，要更节省内存。

实际上，从const的实现原理上来讲，const只是一个编译期的语言功能，做一些简单的常量替换以及赋值限制等，他在运行时不会对内存有什么限制。不合理的使用const_cast之所以会造成运行时崩溃，是由于const修饰的某些变量是位于常量区或者其他某些只读的内存页。

参考书籍与资料：《Effctive C++》

Const用法总结（快速区分指针常量与常量指针）https://blog.csdn.net/u012999985/article/details/49009531

C++ 中 const 的实现原理是什么？

const修饰的成员函数



问：reference和pointer的区别？哪些情况使用pointer？（提问概率：★★）

1.指针可以为空，而引用强烈建议不要指向空值，否则可能会出现下面的情况。

int* iptr = NULL;
int &irptr = *iptr;
irptr = 'b';//运行时崩溃

char* cptr = NULL;
char* &crptr = cptr;
*crptr = 'b';//运行时崩溃

2.指针可以不初始化，引用必须初始化。这意味着引用不需要检测合法性（是否为空）
3.指针可以随时更改指向的目标，而引用初始化后就不可以再指向任何其他对象
根据上面的情况我们知道大概知道哪些时候需要使用指针了。不过还有一种情况，在重载如[]符号的时候，建议返回引用，这样便于我们书写习惯也方便理解。因为平时我们都是这样使用， a[10] = 10;而不是*a[10] = 10;

参考书籍与资料：《More Effctive C++》



问：inline的优劣（提问概率：★★）

关于内联的总结可能有很多不恰当的地方，原文已经修改，具体可以参考我的新文章（被知乎大佬嘲讽后的一个月，我重新研究了一下内联函数），另外也可以参考文章可别总结 C++ 开发面试问题了。

优点：减少函数调用开销
缺点：增加函数体积，exe太大，占用CPU资源，可导致cache装不下(减小了cache的命中) ，不方便调试。debug模式下编译器一般不内联（也可以手动调整参数）， 每次修改会重新编译头文件增加编译时间 （经过进一步学习后这一条也不准确）
注意:inline只是一个请求，编译器有权利拒绝。有7种情况下都可能会拒绝，虚调用，体积过大，有递归，可变数目参数，通过函数指针调用，调用者异常类型不同，declspec宏等（这里描述不严谨，现代编译器会有更多的方式去采用inline去优化，比如虚调用也可能会被内联）


forceinline字面意思上是强制内联，一般可能只是对代码体积不做限制了，但是对于上面的那些情况仍然不会内联，如果没有内联他会返回一个警告。 构造函数析构函数不建议内联，里面可能会有编译器优化后添加的内容，比如说初始化列表里面的东西。

参考书籍与资料：

WiKi（https://zh.wikipedia.org/wiki/%E5%86%85%E8%81%94%E5%87%BD%E6%95%B0）

MSDN(https://msdn.microsoft.com/zh-cn/magazine/z8y1yy88(v=vs.110).aspx)



问：final和override的作用，以及使用场合（提问概率：★★）

final:禁止继承该类或者覆盖该虚函数
override:必须覆盖基类的匹配的虚函数


使用场合（final）:

不希望这个类被继承，比如vector，编码者可能不够了解vector的实现，或者说编写者不希望别人去覆盖某个虚函数.顾名思义，final就是最终么

不希望这个函数再被其他子类覆写


使用场合（override）:

第一种情况是你想覆写一个基类的函数，但是不小心参数不匹配或者名字拼错，结果导致写了一个新的虚函数。这时候如果你加上override关键字，编译器会帮你发现与基类函数不匹配从而给出编译错误的提示。

第二种，在使用别人的函数库，或者继承了别人写的类时，你想写一个新函数，但是可能碰巧与原来基类的函数名称一样，这样就会被编译器（以及其他人）误认为要重写基类的函数。如果大家都养成习惯重写基类函数时都加上override，别人在看到你的代码时就知道你当前的函数是否想重写基类里面的函数，也就容易发现你这个无意中重载的Bug。



参考书籍与资料：《C++ Primer》



问：The rule ofthree是什么？为什么这么做？（提问概率：★）

If you need to explicitly declare either the destructor,copy constructor or copy assignment operator yourself, you probably need toexplicitly declare all three of them.（析构函数，拷贝构造函数，赋值运算符尽可能一起声明。如果你只定义一个，编译器会帮助你定义另外两个，而编译器定义的版本也许不是你想要的）

参考书籍与资料：WIKI Rule of three

（https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)）



问：C++03/98有什么你不习惯或不喜欢的用法？C++11有哪些你使用到的新特性？（提问概率：★★★★★）

这个问题最简单的办法就是看下一个版本的C++有哪些特性，新的特性肯定是有意义的。

如：

auto，有一些迭代器或者map嵌套类型，遍历时比较麻烦，auto写起来很方便。

vector以及其他容器的列表初始化，原来想要像数组一样初始化的话，需要一个一个来，很麻烦。

类内初始值问题，总是需要放到构造函数里面初始化，初始化列表倒是不错，但是初始化数据太多就不行了。

nullptr，C++11前的NULL一般是是这样定义的 #define NULL 0，这可能会导致一些函数参数匹配问题。而nullptr可以避免这个问题。

thread，不需要再使用其他的库来写多线程了。

智能指针shareptr，一定程度上解决内存泄露问题。

右值引用，减少拷贝开销。

lambda function，简化那些结构简单的函数代码。
当然，你要是能说出一些还没有改正或者有待考虑的问题就更好了，比如内存管理的困难（没有GC），没有反射以及一些C#，java里面有而C++没有的特性等，要能深入一点说那就更好了

参考书籍与资料：《C++ Primer》 nullptr，0与NULL （https://www.cnblogs.com/porter/p/3611718.html）



问：Delete数组的一部分会发生什么？为什么出现异常？（提问概率：★★★★）

VC下是异常，实际删除的时候整个数组的内存不仅仅是数据大小还包括CRTHeader，数组长度等信息。如果删除一部分会从数量的位置开始传入，是有问题的。VC下数组的内存布局参考下面公式，

公式1）_CrtMemBlockHeader + <Your Data>+gap[nNoMansLandSize];这类数据用delete和delete[]都一样！

公式2）_CrtMemBlockHeader +数组元素个数+ <Your Data>+gap[nNoMansLandSize];

如果其他编译器，有可能不会报错。但是只释放一个数组对象也是有问题的，其他的对象既没有释放也没有析构。

参考书籍与资料：为何new出的对象数组必须要用delete[]删除，而普通数组delete和delete[]都一样（https://www.cnblogs.com/sura/archive/2012/07/03/2575448.html）



问：系统是如何知道指针越界的？（提问概率：★★）

VC下有一个结构体_CrtMemBlockHeader，里面有一个Gap属性，这个Gap数组放在你的指针数据的后面，默认为0xFD，当检测到你的数据后不是0xFD的时候就说明的你的数据越界了。

参考书籍与资料：为何new出的对象数组必须要用delete[]删除，而普通数组delete和delete[]都一样（https://www.cnblogs.com/sura/archive/2012/07/03/2575448.html）



问：C++编译器有哪些常见的优化？听说过RVO（NRVO）么？（提问概率：★★★）

1.常量替换如int a = 2; int b = a; return b;可能会优化为 int b=2; return b; 进一步会优化为return 2;

2.无用代码消除比如函数返回值以及参数与该表达式完全无关，直接会优化掉这段代码

3.表达式预计算和子表达式提取常量的乘法会在编译阶段就计算完毕，相同的子表达式也会被合并成一个变量来进行计算

4.某些返回值为了避免拷贝消耗，可能会被优化成一个引用并放到函数参数里面，如RVO，NRVO。

RVO：函数返回的对象如果是新构造的值类型就直接通过一个引用作为参数来构造，进而避免创建一个临时的“temp”对象。

NRVO：相比RVO进一步优化。对于RVO，如果函数在返回前创建了一个临时变量，这个临时变量还是会被构造的，参考下面代码

Point3d Factory()
{
Point3d po(1,2, 3);
return po;
}
//RVO优化后
void Factory(Point3d &_result)
{
Point3d po(1,2,3);
_result.Point3d::Point3d(po);
return;
}
//NRVO优化后
void Factory(Point3d &_result)
{
_result.Point3d::Point3d(1, 2, 3);
return;
}
NRVO则直接跳过临时对象的构造。

（补充：上面的优化有的时候不同编译器可能有差别，想一探究竟建议查看反汇编代码。一般来说函数返回的临时值类型对象是右值，通过寄存器存储，所以获取不到地址）

当然，优化还有很多，这里不一一列举。由于这些优化，你在调试过程中可能无法设置断点，所以需要关闭优化。还有一个小的技巧，static变量不会被优化。

参考书籍与资料：

《Inside the C++ Object Model》（深度探索C++对象模型）

RVO和NRVO的区别是什么？

（https://www.zhihu.com/question/32237405/answer/55440484）

Copy elision

（https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization）

RVO V.S. std::move

（https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move?lang=en）

C++中的RVO和NRVO

（https://blog.csdn.net/yao_zou/article/details/50759301）

详解RVO与NRVO

（https://blog.csdn.net/virtual_func/article/details/48709617）



问：听说过mangling么？（提问概率：★★）

mangling 指编译器给函数变量等添加很多的描述信息到名称上用于传递更多信息。常用函数重载，编译时可以把返回值类型等与原函数名称进行组合达到区分的效果，具体规则看编译器。

参考书籍与资料：《Inside the C++ Object Model》（深度探索C++对象模型）

Name mangling

(https://en.wikipedia.org/wiki/Name_mangling)

Why can't C functions be name-mangled?

（https://stackoverflow.com/questions/36621845/why-cant-c-functions-be-name-mangled）



问：成员函数指针了解么？可以转换为Void*么？为什么？（提问概率：★★★）

写法：函数指针 float (*my_func_ptr)(int, char *);

成员函数指针 float (SomeClass::*my_memfunc_ptr)(int,char *);

我们在实现delegate的时候通常要用到函数指针，函数指针可以让代码看起来简洁一些

成员函数指针不可以转换成Void（void*表示无类型指针通常可以与其他类型指针转换，在网络通信等方面经常使用），因为成员函数指针大小并不是4个字节（32位机器上），除了地址还需要this的delta，索引等信息。成员函数指针比较复杂，建议好好读一下下面给出的文章。

参考书籍与资料：

成员函数指针与高性能的C++委托（中文）（https://www.cnblogs.com/jans2002/archive/2006/10/13/528160.html）

Member Function Pointers and the Fastest Possible C++Delegates（英文）

（https://www.codeproject.com/Articles/7150/Member-Function-Pointers-and-the-Fastest-Possible）

https://www.zhihu.com/question/49529308

https://www.cnblogs.com/wuyudong/p/c-void-point.html

问：描述一下C/C++代码的编译过程？（提问概率：★★★★）

预处理——编译——汇编——链接。预处理器先处理各种宏定义，然后交给编译器；编译器编译成.s为后缀的汇编代码；汇编代码再通过汇编器形成.o为后缀的机器码（二进制）；最后通过链接器将一个个目标文件（库文件）链接成一个完整的可执行程序（或者静态库、动态库）。

参考书籍与资料：《深入理解计算机系统》

c++编译过程简介

（http://www.cnblogs.com/dongdongweiwu/p/4743709.html）



问：了解静态库与动态库么？说说静态链接与动态链接的实现思路（提问概率：★★★）

存在静态链接器和动态链接器，编译过程涉及到预编译器、编译器（词法分析、语法分析等）、汇编器、链接器，很多时候我们统一称为编译器。

静态链接：编译器和汇编器将多个文件（模块）生成多个可重定位的目标文件，静态链接器在链接时将多个可重定位目标文件链接成可执行的文件（exe，.out文件 ELF格式）




静态库文件可以在静态链接时和其他可重定位目标文件一同链接成可执行目标文件。




动态链接：动态链接器需要在链接时先通过静态连接器传入一些重定位和符号信息，后续在可执行文件加载或者运行的时候先加载动态链接器（.interp节中和包含动态连接器的路径，他本身就是一个共享库），随后根据重定位等信息将目标动态库文件加载到内存中。




静态库（.a/lib）、共享库(动态库.so/dll)都是由编译器生成

静态库：任意个.o文件的集合，程序link时，被复制到output文件。这个静态库文件是静态编译出来的，索引和实现都在其中，可以直接加到内存里面执行。

对于Windows上的静态库.lib有两种，一种和上面描述的一样，是任意个.o文件的集合。程序link时，随程序直接加载到内存里面。另一种是辅助动态链接的实现，包含函数的描述和在DLL中的位置。也就是说，它为存放函数实现的dll提供索引功能，为了找到dll中的函数实现的入口点，程序link时，根据函数的位置生成函数调用的jump指令。（Linux下.a为后缀）

动态库：包含一个或多个已被编译、链接并与使用它们的进程分开存储的函数。在程序编译时并不会被连接到目标代码中，而是在程序运行是才被载入。不同的应用程序如果调用相同的库，那么在内存里只需要有一份该共享库的实例，规避了空间浪费问题。（Linux下.so为后缀）

参考书籍与资料：《深入理解计算机系统》

Static library

（https://en.wikipedia.org/wiki/Static_library）

Dynamic-link library

（https://en.wikipedia.org/wiki/Dynamic-link_library）

lib与dll的关系

（https://blog.csdn.net/u012999985/article/details/50429715）

程序的静态链接，动态链接和装载 （https://www.cnblogs.com/acSzz/p/5743789.html）

程序运行流程——链接、装载及执行 （https://www.xuebuyuan.com/1730287.html）



问：知道内部链接与外部链接么？（提问概率：★★）

内部链接：如果一个名称对于他的编译单元是局部的，并且在链接时不会与其他的编译单元中同样的名字冲突，那么这个名称就拥有内部链接。

外部链接：一个多文件的程序中，一个实体可以在链接时与其他编译单元交互，那么这个实体就拥有外部链接。换个说法，那些编译单元（.cpp）中能想其他编译单元（.cpp）提供其定义，让其他编译单元(.cpp)使用的函数、变量就拥有外部链接

参考书籍与资料：What is external linkage and internallinkage?

（https://stackoverflow.com/questions/1358400/what-is-external-linkage-and-internal-linkage）

C++编译与链接（2）-浅谈内部链接与外部链接（https://www.cnblogs.com/magicsoar/p/3840682.html）

理解C++的链接：C++内链接与外链接的意义（https://blog.csdn.net/u012999985/article/details/50429769）



问：extern与static（提问概率：★★★）

extern 声明一个变量定义在其他文件，这样当前文件就可以使用这个变量，否则会编译失败，如果两个全局变量名称一样会出现链接失败。extern c的作用更重要，因为c++的编译方式与c是不同的，比如函数重载利用mangling的优化。

static变量，很多编译器优化后的效果就是声明一个全局变量，然后判断是否初始化，是的话之后就不需要再初始化了，但是不绝对，win7的全局变量与static的位置就有差异。static成员函数其实在编译后与class完全没有关系。static成员其实也没关系，但是private的需要通过类去调用。static全局变量需要注意，他只能在当前编译单元也就是.cpp内使用(内链接)。全局函数变量是外链接，可以跨单元调用。

static相关注意与理解：静态内存是在main前分配，在main后释放。当存在多个复杂的static变量时，你就不知道哪个先分配了，也控制不了。另外，关于static具体的存储位置，一般是我们常说的静态存储区（bss，数据区等），更贴切的说他是一个可执行文件里面的区域，到操作系统层面可能是另一种叫法，对不同的编译器、C++版本、操作系统可能都有所差异。我们一个程序编译链接好后会把一些静态数据写到exe、dll里面，注意这时候exe并没有放入到内存，所以，其实所谓的编译后内存位置就确定了只不过是一种“理解方式”，真正的静态区（全局变量、静态变量、常量）也是在程序运行后操作系统将这些数据装入内存后的一个位置，这个位置相对exe来说可以理解为静态的，然后当我们运行exe动态申请内存时就是我们 常说的堆区（也可以叫动态区、C++叫自由存储区等）

参考书籍与资料：《C++ primer》

extern "C"

（https://baike.baidu.com/item/extern%20%22C%22）



问：delegate是什么？实现思路？与event的区别？（提问概率：★★★）

代理简单来说就是让对象B去代理A执行A本身的操作，本质上就是通过指向其他成员函数或者全局函数的函数指针去代理执行。而函数指针有两种，成员函数指针与普通的函数指针，我们一般就是通过对这两种指针的封装来实现代理的效果。常见的实现方式有两种，一种是通过多态接口，另一种是通过宏。代理也分为单播代理与多播代理，单播就是一个调用只代理执行一个函数功能，多播代理就是一个调用可以绑定多个代理函数，可以触发多个代理的函数操作。
Event是一种特殊的多播delegate，只有声明事件的类可以调用事件的触发操作。最常见的也容易理解的就是MFC里面的按钮的鼠标点击事件了，他的调用只能在Button里面去执行。

参考书籍与资料：[C++]实现委托模型（https://www.cnblogs.com/zplutor/archive/2011/09/17/2179756.html）



问：使用过模板么？了解哪些特性？（提问概率：★★★★）

模板分为函数模板与类模板，其根本目的是将类型“参数化”，实现编译时的“动态化”，避免重复代码的书写。另一种运行时的“动态化”就是多态。

模板使用常见的特性有“特化”，“偏特化”，“非类型模板参数”，“设置模板参数默认类型”，“模板中的typename的使用”，“双重模板参数Template Template Parameters”，“成员模板Member Template”，理解这些内容我们就基本上可以看STL标准库了。

另外，模板的实例化过程也是需要理解的。

参考书籍与资料：“STL源码”，《C++ Template》，《C++ Primer》



问：模板代码如何组织？模板的编译（以及实例化）过程（提问概率：★★★）

一般来说，模板类的声明与定义不像普通类那样拆分成.h和cpp，而是要全部放在头文件里面（或者定义放在使用到模板的.cpp里），否则会发生编译错误。为什么？因为模板函数所在的cpp不能直接编译成相应的二进制代码，他并不知道模板参数是什么，所以需要一个“实例化”的过程。简单来说，C++标准规定，如果一个cpp里面没有任何显示调用过模板函数（或者使用类模板）的语句，就不会生成真正的拥有确切类型的类的定义，进而就不会生成任何二进制代码，所以其他cpp也无法链接到只包含定义的.cpp文件。下面的例子就会编译报错，除了把template.cpp放到头文件里面，这里放到main.cpp也是可以的

//-------------template.h----------------// 
template<typename T> 
class TemTest 
{ 
  public: 
    void TestFun(); 
}; 
//------------template.cpp-------------// 
#include “template.h” 
template<class T> 
void TemTest <T>::TestFun() //定义，但是不会生成二进制文件
{ 
  .....
} 
//---------------main.cpp---------------// 
#include “template.h” 
int main() 
{ 
  TemTest<int> t; 
  t. TestFun(); 
}


问：听说过转发构造么？（提问概率：★★）

通过foward关键字可以同时考虑到参数为左值以及右值的情况，然后把函数的参数完美的转发到其他函数的参数里面。这个里面涉及到左值、右值、move、forward、引用折叠等技术点。

参考书籍与资料：《C++ Primer》《Effective Modern C++》

The Forwarding Problem: Arguments

（http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2002/n1385.htm）

A Brief Introduction to Rvalue References （https://www.artima.com/cppsource/rvalue.html）

C++11 forward完美转发

（https://blog.csdn.net/rankun1/article/details/78354153）

Effective Modern C++ 条款28 理解引用折叠（https://blog.csdn.net/big_yellow_duck/article/details/52433305）

移动语义（move semantic）和完美转发（perfect forward）

（https://codinfox.github.io/dev/2014/06/03/move-semantic-perfect-forward/）



问：描述一下函数调用过程中栈的变化（提问概率：★★★★）

回答这个问题需要对栈的使用过程，函数调用，汇编都有一定的理解才行。首先，要清楚一个概念“栈帧”。

栈帧(stack frame)：机器用栈来传递过程参数，存储返回信息，保存寄存器用于以后恢复，以及本地存储。为单个过程(函数调用)分配的那部分栈称为栈帧。栈帧其实是两个指针寄存器，寄存器ebp为帧指针（指向该栈帧的最底部），而寄存器esp为栈指针（指向该栈帧的最顶部）。

然后我们再简单描述一下函数调用的机制，每个函数有自己的函数调用地址，里面会有各种指令操作（这端内存位于“代码段”部分），函数的参数与局部变量会被创建并压缩到“栈”的里面，并由两个指针分别指向当前帧栈顶和帧栈尾。当进入另一个子函数时候，当前函数的相关数据会被保存到栈里面，并压入当前的返回地址。子函数执行时也会有自己的“栈帧”，这个过程中会调用CPU的寄存机进行计算，计算后再弹出“栈帧”相关数据，通过“栈”里面之前保存的返回地址再回到原来的位置执行前面的函数。参考下图（改编自https://www.cnblogs.com/zlcxbb/p/5759776.html的图片）：




参考书籍与资料：《深入理解计算机系统》

函数调用栈帧过程带图详解

（https://blog.csdn.net/IT_10/article/details/52986350）

函数调用栈浅析

（https://www.cnblogs.com/coderland/p/5902719.html）

函数调用过程栈帧变化详解

（https://www.cnblogs.com/zlcxbb/p/5759776.html）



问：__cdecl/__stdcall是什么意思（提问概率：★★★）

常见的函数调用有如下

__cdecl/__stdcall/__thiscall/__fastcall。

cdecl按照c语言标准，从右到左，可以实现可变参数，调用者弹出参数。

stdcall（pascal调用约定）按照c++标准，函数参数从右到左，不支持可变参数，函数返回自动清空。但是有的时候编译器会识别并优化成cdecl。

Pascal语言中参数就是从左到右入栈的不支持可变长度参数

（注：__stdcall标记的函数结束后，ret 8表示清理8个字节的堆栈，函数自己恢复了堆栈）

参考书籍与资料：“建议查看反汇编代码”

x86 calling conventions

（https://en.wikipedia.org/wiki/X86_calling_conventions）

What is __stdcall?

（https://stackoverflow.com/questions/297654/what-is-stdcall）

__stdcall

（ https://msdn.microsoft.com/zh-cn/library/zxk0tw93.aspx）



问：C++中四种Cast的使用场景是什么？（提问概率：★★★★★）

constcast，去掉常量属性以及volatile，但是如果原来他就是常量去掉之后千万不要修改；比如你手里有一个常量指针引用，但是函数接口是非常量指针，可能需要转换一下；成员函数声明为const，你想用this去执行一个函数，也需要用constcast

staticcast，基本类型转换到void，转换父类指针到子类不安全

dynamiccast，判断基类指针或引用是不是我要的子类类型，不是强转结果就返回null，用于多态中的类型转换

reintercast，可以完成一些跨类型的转换，如int到void*，用于序列化网络包数据

参考书籍与资料：《C++ Primer》《The Design and Evolution of C++》（C++语言的设计与演化）



问：用过或很熟悉的设计模式有哪些？（提问概率：★★★★）

这个问题看好书写写代码就可以自由发挥了，下面给几个例子。

工厂模式，通过简单工厂生成NPC对象，简单处理的话可通过“字符串匹配”动态创建对象。如果有“反射机制”就可以直接传class来实现。当然可以进一步使用抽象工厂，处理不同的生产对象。

单例，实现全局唯一的一个对象。构造函数、静态指针都是私有的，使用前提前初始化或者加锁来保证线程安全。

Adaptor适配器，代码适配原来的相机移动最后调用的是原来的移动，现在加了适配器继承里面放了当前引擎的摄像机，然后覆盖原来摄像机的移动逻辑。

Observer，一个对象绑定多个观察者，然后这个对象一旦有消息就立刻公布给所有的观察者，观察者可以动态添加或删除。在UE4里面，行为树任务节点请求任务后进入执行状态，然后会立刻注册一个观察者observer到行为树（行为树本身就相当于前面提到的那个对象）的observer数组里面同时绑定一个代理函数。行为树tick检测消息发送给所有观察者，观察者收到消息执行代理函数。

参考书籍与资料：《Head First设计模式》《设计模式：可复用面向对象软件的基础》

常见设计模式的解析和实现C++ （https://wenku.baidu.com/view/7488c59f0508763231121295.html）

Design Patterns

(https://en.wikipedia.org/wiki/Design_Patterns)

问：为什么const修饰成员函数后不能修改成员变量

每个成员函数在调用的时候，都会把this作为第一个参数传进去。我们在用const修饰成员函数的时候，就相当于修饰了this，也就是说我们的第一个参数应该是

 const 类型* this 
所以我们不能去修改this的成员变量，编译器不允许通过。



问：编码了解么？unicode和utf-8的区别

编码的本质就是将二进制与符号一一映射，然后通过二进制码解析出对应的符号。一开始计算机只存在于欧美，所以他们理所应当的把英文（以及常见的符号）与二进制做了一个映射表，这就是ASCII码。后来，其他国家也开始使用，需要用到的二进制也越来越多，不同的国家都有不同的编码方式，比如中国的GBK。但是问题是各个国家都不统一，解析起来非常麻烦，因此一个ISO的组织就重新搞了一个包含所有文字与符号的编码方式，即Unicode。unicode全称"Universal Multiple-Octet Coded Character Set"，是一个全球统一的符号集，规定了每个符号对应的二进制编码，这个编码的长度是不确定的，由字符来决定。虽然如此，但是他却没有表示这个符号该如何存储，比如一个英文字符只需要一个字节就可以处理，而一个汉字可能就需要两个字符存储。问题是我在编码的时候并不知道这N个字节的二进制编码到底表示的是一个还是N个符号。这样，UTF-8出现了，他提供了一种Unicode的存储方式，它是一种变长的编码方式。它可以使用1~4个字节表示一个符号，根据不同的符号而变化字节长度。

UTF-8的编码规则只有二条：

1）对于单字节的符号，字节的第一位设为0，后面7位为这个符号的unicode码。因此对于英语字母，UTF-8编码和ASCII码是相同的。

2）对于n字节的符号（n>1），第一个字节的前n位都设为1，第n+1位设为0，后面字节的前两位一律设为10。剩下的没有提及的二进制位，全部为这个符号的unicode码。

这样，通过判断每个字节前面的几位，就可以判断其表示的是某个符号还是符号的一部分了。

参考资料：https://jerish.blog.csdn.net/article/details/77619368



更多内容欢迎关注微信公众号: 游戏开发那些事
之后还会陆续更新更多关于面试，游戏开发，虚幻引擎等相关的学习资料~
</code></pre>
</details>

<details>
<summary>被知乎大佬嘲讽后的一个月，我重新研究了一下内联函数</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/50812510
这绝不仅仅是一篇讲内联意义的文章，参考我的学习过程，可能对你的知识整合有很大帮助更多文章请关注：微信公众号——游戏开发那些事


之前写了一篇总结c++面试的文章，被大佬纠出来很多关于内联的问题与错误。抱着不误导别人以及学习的态度，我在之后的一个月里抽时间重新研究了一下内联函数，确实学到了很多以前不了解的知识。学习么~就是一个不断打破之前认知并重构知识的过程，每个人都是从一个什么都不懂的菜鸟逐渐成长为一个大牛的。

在这篇文章里，我会由浅入深的分析不同阶段的我对内联函数的认识，重构我的知识体系。即使你之前对inline不了解，也可以看得懂这篇文章。 文中会有很多引用的参考链接，我会统一放到文末的位置。

菜鸟阶段（初步学习计算机组成原理，C++语法，C语言语法，汇编语言等）：
上大学第一次接触C++，然后了解到了内联函数。啥是内联函数？简单理解就是编译时把函数的定义替换到调用的位置。

inline int Add(int a, int b)
{
   return a + b;
}
int main()
{
   int num1 = 1;
   int num2 = 2;
   int myNum = Add(num1, num2);
}
//这样的代码内联之后大概就是
int main()
{
   int num1 = 1;
   int num2 = 2;
   int myNum = num1 + num2;
}
好的，感觉好像还挺简单的。啥？你问我啥是编译？嗯。。编译就是把你的代码通过编译器分析一下然后转换成计算机能直接读懂的语言（汇编），最后生成一个可执行的程序（或可被调用的库）。

当然，我这么解释有点不太权威，咱们再看看维基百科关于内联函数的定义



在计算机科学中，内联函数（有时称作在线函数或编译时期展开函数）是一种编程语言结构，用来建议编译器对一些特殊函数进行内联扩展（有时称作在线扩展）；也就是说建议编译器将指定的函数体插入并取代每一处调用该函数的地方（上下文），从而节省了每次调用函数带来的额外时间开支。但在选择使用内联函数时，必须在程序占用空间和程序执行效率之间进行权衡，因为过多的比较复杂的函数进行内联扩展将带来很大的存储资源开支。【参考：内联函数维基百科】


那么内联函数有什么有点呢？当然是减少函数调用带来的开销了，几乎每本C++入门书籍、百科以及博客都是这么说的。不过，什么是函数调用开销？额，反正调用函数肯定要消耗CPU运算吧，肯定也有内存参与，肯定有开销，嗯。

另外，我还从书上了解一些相关的知识，如直接在类的头文件里面定义的函数都是自动内联的（并不对），内联相比宏定义有类型检查、可支持类的访问控制等优点。



这时候我知道的专业名词有：汇编、编译、内联、CPU、函数调用、内存地址，但是他们之间的关系几乎是一头雾水了。

这个阶段的知识图谱大概是：


初识阶段（学习了一些编译原理知识，稍微深入的了解了一些C++特性，有一些相关编码经验）：
之前总是说减少函数调用开销，那么这个调用开销到底是指什么？这时候的我发现有一些面试里面会问到这个问题，所以还真有必要理解一下了。



我们常说，C语言程序内存分为常量区、代码区、静态全局区、栈区、堆区。当我们的程序运行时，我们的编译后的二进制程序（这个二进制程序的分布格式差不多就是前面说的那几个区，里面会有各种汇编命令，可参考书籍《Windows核心编程》）就会被放到操作系统的内存里面，函数代码段被放在所谓的代码区，局部变量与函数参数被放在栈区。函数调用就发生在栈区里面，每次调用的时候会把当前函数的相关内容压入到栈里面处理寄存器相关的数据信息（所谓没有地址的右值很多情况就是指通过寄存器存储的数据）。然后，调用地址指向我们要执行的函数位置，开始处理函数内部的指令进行计算，当函数执行结束后，要弹出相关数据，处理栈内数据以及寄存器数据。【参考：浅谈C/C++堆栈指引——C/C++堆栈很强大】

这个过程也就是所谓的“函数调用开销”。


函数调用栈


这里我们再总结一下消除函数调用的直接好处【参考：Inline expansion 】：

1.它消除了函数调用过程中所需的各种指令：包括在堆栈或寄存器中放置参数，调用函数指令，返回函数过程，获取返回值，从堆栈中删除参数并恢复寄存器等。

2.由于不需要寄存器来传递参数，因此减少了寄存器溢出的概率。当使用引用调用（或通过地址调用或通过共享调用）时，它消除了必须传递引用然后取消引用它们。



当然缺点我们也应该了解，使用不当的话就会造成代码膨胀（也就是生成的可执行程序会变大），影响cache对数据的命中，如果你设计了一个函数库，调用你的内联函数还会造成客户代码的重新编译。一般高速缓存里面会分为指令缓存（instruction cache）以及数据缓存（data cache），inline的使用不当对二者都可能造成影响。首先，过多的内联代码会使原来本可以存储到ICache的指令分散，导致指令缓存的命中降低，从内存取数据会严重影响效率。其次，inline会导致代码膨胀，增加可执行程序（动态库、静态库）体积，造成额外的换页行为，进而可能会导致数据缓存的命中率降低。

上面说的缺点还比较抽象，很多情况好像都可以接受。而还有一些特定情况，内联将会造成很严重的后果，如递归函数的内联可能造成代码的无限inline循环。所以编译器在这些特殊情况下会拒绝内联，常见的包括虚调用，函数体积过大，有递归，可变数目参数，通过函数指针调用，调用者异常类型不同，declspec宏、使用alloca、使用setjump等。不过这些情况编译器也并不是一定会拒绝，虚调用在某些情况下就可以被内联，会在第三部分细说。



这时候，我认识到，其实内联inline只是建议性的关键字，编译器并不一定会听你的，毕竟他比你更了解你的代码编译后是什么样子的，而所谓的内联也不单单是指inline这个关键字了，他本质上是一种编译器的优化方式。另外，在windows上平台我还经常能看到【forceinline】（GCC上的【always_inline】）这样的关键字，字面意思是强制内联。不过经过查阅，发现一般只是对代码体积不做限制了，或者说在Debug模式（不不开启优化的情况）下也会尽量按照开发者的意愿去内联。无论如何，最终的决定权还是交给编译器去处理。



在这个阶段的学习过程中，我发现想理解程序的编译与运行，还不得不去看看程序的反汇编代码，看看编译器编译后的代码是什么样子的。毕竟很多时候，我们需要亲自手动操作才能真正的理解其中的原理。

虽然我上学时很讨厌这门课，但是我发现想大概看懂反汇编代码，并不需要非常完善的汇编知识，只要把常见的一些命令记住并理解就行了。【参考：手把手教你栈溢出从入门到放弃 】


VS查看反汇编


还是前面那段代码，测试在VS2017下的汇编代码（方法参考上图）

inline int Add(int a, int b)
{
    return a + b;
}
int main()
{
    int num1 = 1;
    int num2 = 2;
    int myNum = Add(num1, num2);
}


//Debug模式下无内联优化的汇编代码，需要跳到Add函数的地址去执行计算
int main()
{
01232530  push        ebp  
01232531  mov         ebp,esp  
01232533  sub         esp,0E4h  
01232539  push        ebx  
0123253A  push        esi  
0123253B  push        edi  
0123253C  lea         edi,[ebp-0E4h]  
01232542  mov         ecx,39h  
01232547  mov         eax,0CCCCCCCCh  
0123254C  rep stos    dword ptr es:[edi]  
0123254E  mov         ecx,offset _5BD3FBCE_consoleapplication2.cpp (01247008h)  
01232553  call        @__CheckForDebuggerJustMyCode@4 (0123142Eh)  

	int num1 = 1;
01232558  mov         dword ptr [num1],1  

	int num2 = 2;
0123255F  mov         dword ptr [num2],2  

	int myNum = Add(num1, num2);
01232566  mov         eax,dword ptr [num2]  
01232569  push        eax  
0123256A  mov         ecx,dword ptr [num1]  
0123256D  push        ecx  
0123256E  call        Add (01231726h)  
01232573  add         esp,8  
01232576  mov         dword ptr [myNum],eax  
}


 int Add(int a, int b)
{
00891E50  push        ebp  
00891E51  mov         ebp,esp  
00891E53  sub         esp,0C0h  
00891E59  push        ebx  
00891E5A  push        esi  
00891E5B  push        edi  
00891E5C  lea         edi,[ebp-0C0h]  
00891E62  mov         ecx,30h  
00891E67  mov         eax,0CCCCCCCCh  
00891E6C  rep stos    dword ptr es:[edi]  
00891E6E  mov         ecx,offset _5BD3FBCE_consoleapplication2.cpp (08A7008h)  
00891E73  call        @__CheckForDebuggerJustMyCode@4 (089142Eh)  
  return a + b;
00891E78  mov         eax,dword ptr [a]  
00891E7B  add         eax,dword ptr [b]  
}

//Debug模式下开启内联（/Ob2，参考上图）后的汇编代码，无需跳转到Add函数的位置，直接优化计算
int main()
{
00F41F50  push        ebp  
00F41F51  mov         ebp,esp  
00F41F53  sub         esp,0E4h  
00F41F59  push        ebx  
00F41F5A  push        esi  
00F41F5B  push        edi  
00F41F5C  lea         edi,[ebp-0E4h]  
00F41F62  mov         ecx,39h  
00F41F67  mov         eax,0CCCCCCCCh  
00F41F6C  rep stos    dword ptr es:[edi]  
00F41F6E  mov         ecx,offset _5BD3FBCE_consoleapplication2.cpp (0F57008h)  
00F41F73  call        @__CheckForDebuggerJustMyCode@4 (0F4142Eh)  

	int num1 = 1;
00F41F78  mov         dword ptr [num1],1  

	int num2 = 2;
00F41F7F  mov         dword ptr [num2],2  

	int myNum = Add(num1, num2);
00F41F86  mov         eax,dword ptr [num1]  
00F41F89  add         eax,dword ptr [num2]  
00F41F8C  mov         dword ptr [myNum],eax  
}


当然你也可以在【这里】试试其他的编译器，如GCC、ICC、Clang。关于VS控制内联的参数，可以看【这里】。



后来，我又看了《深入探索C++对象模型》这本书，印象很深的就是我们以为的代码在编译器处理后并不是我们以为的那样，里面有各种【mangling】，添加各种附加代码，那些看起来空空如也的的构造函数（析构函数同理）里面也可能有着几十行或者上百行的复杂代码。想象一下，你把这些构造代码内联的到处都是，你确定你的程序能得到优化么？（当然，实际情况可能更为复杂，单纯的全部内联或者全都拒绝内联都不会得到最佳优化，结论还是要看基准测试的结果才更有说服力）



到这里我发现我能稍微的理解高级语言与汇编语言之间的关系，函数调用的基本原理，程序与内存之间的关系等，不过这时候我对编译器所做的工作还是知之甚少。

现在知识图谱大概变成这样了：


进阶阶段（对C++以及编译器有了更深、更全面的理解）：


由于前一阵总结的文章被指出inline的总结内容有诸多不妥，所以我开始换一个角度去理解inline。说实话，大佬文章中很多名词我听都没听过，因为之前除了学完编译原理这门课之后就完全与编译器拜拜了（虽然我无时无刻不在用IDE提供的编译器）。



首先是关于内联的意义，前面说过内联的直接优点就是减少函数调用，这个是毋庸置疑的，但是他更大意义是它允许编译器进行进一步优化【参考：Inline expansion Reducing Indirect Function Call Overhead In C++ Programs CppCon 2014: Andrei Alexandrescu "Optimization Tips" 】。



这点是我之前没有去想过，因为我们平时都在写业务代码，大部分情况下不需要考虑语言层面的问题。不过，我个人处于游戏行业，对“优化”一词还是比较敏感的，每次编译引擎（项目）所花费的时间、运行时的效率、调试效率、游戏帧数、打包时间等这些其实与我们的业务是息息相关的。一个庞大的项目一旦编译起来就花费很长时间，所以会有Debug、Development、Shipping等各种版本来满足我们不同情况下的需求。想要调试一个项目，当然是尽可能把优化都关掉才好；对于一个发行出去的游戏，当然是越小巧、高度优化、执行效率越高越好了。然而这些工作其实都是编译器在默默的帮助我们去做的（也可以说是各位编译领域相关的大佬帮我们做的），这时候我突然觉得我们连Debug与Release配置都搞不清真的有点对不起他们的工作了。



还是拿刚才的代码来说，我们再看一下内联后的汇编代码。

int main()
{
//......省略
	int num1 = 1;
00F41F78  mov         dword ptr [num1],1  
	int num2 = 2;
00F41F7F  mov         dword ptr [num2],2  
	int myNum = Add(num1, num2);
00F41F86  mov         eax,dword ptr [num1]  
00F41F89  add         eax,dword ptr [num2]  
00F41F8C  mov         dword ptr [myNum],eax  
}
对于任何一个能看懂代码的人，我们都知道myNum就是2，所以集人类智慧于一身的编译器也应该知道。除了把函数return a+b这段代码内联过来之后还应该直接算出答案，这就是说inline后的代码与之前已经完全不同了，所以编译器有必要再看看这个地方有没有什么值得优化的。事实证明如果我把这个程序改为release版本的，这段代码就直接返回了，不客气的说，我连 myNum=2 这个都可以直接优化掉，因为这个局部变量看起来并没有什么意义。虽然不同的编译器的反汇编代码有所不一样，但是他们都在努力的用内联去调整编译后的结果。

朴素一点的理解，所谓的内联就是为了方便编译器看到更多源码信息，如果我们能把所有函数内联到Main函数里面，那理论上我们可以就可以得到最佳的优化代码，可能一段非常复杂的代码到最后只要一个指令就足够了。关于编译器的优化，方案非常多，十几甚至几十年前就有paper去做相关的研究与分析了。而且这些大佬们还在不断的深入并提出更多的解决方案，常见的有死代码删除、循环不变代码外提、常数折叠、内联缓存、分支预测等等。【参考：Category:Compiler optimizations Reducing Indirect Function Call Overhead In C++ Programs】



既然谈到新的优化方案，就正好说一下虚函数调用。在比较老的编译器上，我们不会去对虚函数内联，原因很简单，因为虚函数的执行属于运行时动态，我们需要动态查阅虚函数表来找到对应的虚函数。由于根本不知道运行的时候到底是哪个类会执行这个虚函数，当然也就不知道到底调用的是哪个子类下override的版本。但是，大佬们自然不会轻易放弃，能优化一点咱们就尽量优化一点。当我们的编译器可以分析出当前的程序，如

struct A 
{     
   virtual ~A() {}    
   virtual int foo() { return 0; } 
};

inline int do_something(A& obj)
{  
   return obj.foo(); 
}

struct B : A 
{    
   virtual ~B() {}     
   virtual int foo() { return 1; } 
};  

int main() 
{     
   B b;    
   return do_something(b); 
}
这样的代码的时候，我们就可以确定B就是继承树上的最终的子节点，也就可以将虚函数的查表调用改为直接调用进而进行内联优化，这种优化方式叫做Devirtualization。当然，这种代码确实过于理想的简单，我们常见的项目代码一定是分为多个编译单元的，编译器想进行跨编译单元的优化就还需要另一个方案，LTO（Link Time Optimization）即链接时优化。

【参考: C++ Devirtualization Devirtualization in LLVM and Clang】



LTO顾名思义，就是在编译器进行链接时进行相关的代码优化，不同编译单元在链接的时候将其内部表示转储到磁盘，然后组成单个模块并进行优化。也因此，之前大佬纠正我说“写在cpp里面的函数也可以内联，每次修改会重新编译头文件增加编译时间这句话也说错误的”。【参考：Link-time optimization for the kernel LLVM Link Time Optimization: Design and Implementation】

可是看完LTO相关资料后，我又产生了疑问，编译器优化不是还有IPO么。所谓IPO，Interprocedural Optimization，即过程间优化，传统的编译器是先将编译每个源文件成独立的目标文件，然后再通过链接器将目标文件链接成可执行文件（或库），其编译优化主要集中在每个源文件内部，而IPO可以打破这个局限对整个程序进行全局的优化。那么IPO与LTO是什么关系呢？看了wiki上的资料后，我大概理解为，LTO属于IPO的子集，IPO是一个可以在编译过程的任何阶段都能执行优化的解决方案，LTO只针对链接时优化，不过应该属于IPO一个最强有力的方案了。【参考：Interprocedural optimization 现代C/C++编译器有多智能？能做出什么厉害的优化？】另外，C/C++这种纯编译型语言都可以做到链接时内联优化，而对于C#、Java这种半编译半解释型的语言，其优化的时机岂不是可以更为灵活随意了？



这时候我才发现，这么多关于内联的调整的优化好像都是编译器在搞，无论什么语言、什么平台，本质上都逃不过编译器的审核与优化。



那么，我们显示声明inline还有什么意义呢？好像我们写不写inline，没什么意义啊。只要是发行出去的版本，编译器自己决定，分分钟给你各种优化，你的各种inline建议好像都没什么意义了。不过，带着疑问我又去查了查资料，发现好像还没问想的那么简单，最起码inline还有两点意义：

1. 编译器并不是万能的，有时候人工的内联建议确实能解决一些编译器优化的盲点【参考：libcxx修改1 、libcxx修改2 】

2. inline并不只是只有把函数内联到调用的地方这个意义，他还关系到ODR （定义与单一定义规则）。所谓ODR，就是任何变量、函数、类类型、枚举类型、概念 (C++20 起)或模板，在每个翻译单元中都只允许有一个定义（它们有些可以有多个声明，但定义只允许有一个）。不过具体一点的说又有很多种情况，对于非inline且odr-used的变量、函数，要求全局只能有一个定义；Inline变量、函数在每个编译单元都有有一个定义；需要使用类的时候，在每个翻译单元都需要一个定义。

例如：你如果把一个非成员函数放到.h文件里面并被多个编译单元包含，那么在链接的时候就会报错。因为非inline的全局函数在全局只能有一个定义，如果每个编译单元都有一个成员函数，编译器不知道链接哪一个。如果给这个函数加上inline的话，就可以解决这个问题。而如果你在多个cpp里面定义了函数签名完全相同的但是内容不同inline函数，也不会发生编译失败，不过具体链接到哪个版本的inline函数可能是未定义行为。【参考：One Definition Rule 既然编译器可以判断一个函数是否适合 inline，那还有必要自己加 inline 关键字吗？ 最近看到陈硕的一本书提了一个问题，“编译器如何处理inline函数中的static变量？”】



关于优化，这里还涉及到一个概念， zero-overhead abstraction，即“零代价的抽象”（Rust里面叫zero-cost abstractions），简单来说就是抽象的同时不需要付出额外的代价，比如说vector<int> 数组在优化理想的编译器的发行版本下与int类型的数组开销应该是几乎相同的。因此，我们可以认为C++中的zero-overhead abstraction与编译器的优化是密不可分的，更进一步的说，C++语言本身的优良与编译器也是密不可分的。每当C++新的标准出来后，各大编译器团队都要及时的去支持这些新的特性，并兼顾语言的优化问题。【参考：Rust所宣称的zero-cost abstractions是怎么回事？ Zero-cost abstractions abstraction and hand-crafted code】



最后，再简单提一下LLVM。前面的很多链接里面都提到了LLVM（很久以前，LLVM曾经是Low Level Virtual Machine的缩写，现在已经不是了），它是一个编译器基础设施框架，包含了我们编写编译器需要的一系列库（如程序分析、代码优化、机器代码生成等），并且提供了调用这些库的相关工具。Clang, llbc++, lld等项目就是基于LLVM开发的，Objective-C编译器也是基于LLVM开发的。LLVM的编译过程与传统的编译器有所差异（参考下图），中间会生成一套通用的与语言无关的中间语言LLVM IR，我们可以去阅读这个中间语言了解更多信息【参考：测试工具】，所以编译优化与使用方式也是非常灵活（我目前在VS上还没有找到可以阅读的单个编译单元编译后的文件）。

我没有深入了解，更多内容可以【参考：LLVM 谁说不能与龙一起跳舞：Clang / LLVM (1) 周末花了点时间看 LLVM IR, 闲扯几句 编译器LLVM浅浅玩 】


传统编译器编译与LLVM编译
这段时间查了各种资料，算是勉强到了一个新的阶段。这个阶段的我主要是开始关注了core language之外的东西——编译器，虽然研究的并不是很透彻，但是在概念的理解上确实与之前有很大的差异。

知识图谱又稍微修改了一下：


至于下个阶段，我还没达到，也不知道我会有哪些新的理解。不过如果哪天我进阶成功，我会再回来给大家分享一下的。



参考链接：
https://zh.wikipedia.org/wiki/%E5%86%85%E8%81%94%E5%87%BD%E6%95%B0

内联函数Wiki

https://blog.csdn.net/mynote/article/details/5835615

浅谈C/C++堆栈指引——C/C++堆栈很强大

https://en.wikipedia.org/wiki/Inline_expansion

内联扩展

https://docs.microsoft.com/zh-cn/cpp/cpp/inline-functions-cpp?view=vs-2017 Microsoft内联函数

https://zhuanlan.zhihu.com/p/25892385

手把手教你栈溢出从入门到放弃

https://docs.microsoft.com/zh-cn/cpp/build/reference/ob-inline-function-expansion?view=vs-2017

Microsoft Doc Inline Option

https://zh.wikipedia.org/wiki/%E5%90%8D%E5%AD%97%E4%BF%AE%E9%A5%B0 name mangling

https://harttle.land/2015/08/28/effective-cpp-30.html

Effective C++ 30：理解inline函数的里里外外

https://en.wikipedia.org/wiki/Interprocedural_optimization Interprocedural optimization

https://en.wikipedia.org/wiki/Category:Compiler_optimizations

编译器优化方案

https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Inline.html

An Inline Function is As Fast As a Macro

http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.27.5761&rep=rep1&type=pdf Reducing Indirect Function Call Overhead In C++ Programs

https://www.youtube.com/watch?v=Qq_WaiwzOtI

CppCon 2014: Andrei Alexandrescu "Optimization Tips"

https://reviews.llvm.org/D22782 、https://reviews.llvm.org/D22834

手动添加内联优化

https://lwn.net/Articles/512548/

Link-time optimization for the kernel

http://llvm.org/docs/LinkTimeOptimization.html

LLVM Link Time Optimization: Design and Implementation

https://www.zhihu.com/question/53082910

既然编译器可以判断一个函数是否适合 inline，那还有必要自己加 inline 关键字吗？

https://www.zhihu.com/question/43598164/answer/122186527

现代C/C++编译器有多智能？能做出什么厉害的优化？

https://www.zhihu.com/question/31645634

Rust所宣称的zero-cost abstractions是怎么回事？

https://ruudvanasseldonk.com/2016/11/30/zero-cost-abstractions

Zero-cost abstractions

https://stackoverflow.com/questions/20134585/interview-with-bjarne-stroustrup-

abstraction-and-hand-crafted-code Interview with Bjarne Stroustrup - abstraction and hand-crafted code

http://www.aosabook.org/en/llvm.html

LLVM架构讲解

https://zhuanlan.zhihu.com/p/21889573

谁说不能与龙一起跳舞：Clang / LLVM系列

https://medium.com/@zetavg/%E7%B7%A8%E8%AD%AF%E5%99%A8-llvm-%E6%B7%BA%E6%B7%BA%E7%8E%A9-42a58c7a7309

編譯器 LLVM 淺淺玩



工具：

https://godbolt.org/ 不同编译器汇编代码预览工具

http://ellcc.org/demo/index.cgi LLVM IR测试与查阅工具



最后吐槽一句，想好好写点东西确实很费时间~
</code></pre>
</details>

<details>
<summary>史上最全的C++/游戏开发面试问题总结（二）——虚函数，内存，STL</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/54136411
更多文章请关注：微信公众号——游戏开发那些事



这个系列的文章预计有《C++基础》（点击进入）、《内存、STL、虚函数相关》、《数据结构与算法》、《操作系统》、《计算机网络》、《面试准备与技巧》六篇（这是第二篇），每篇都是以问答的形式分享并给出了参考资料的链接地址。

大部分问题回答的比较简洁，需要大家去仔细阅读参考资料的具体内容。另外，如果发现文章中有哪些问题或错误，欢迎指出与讨论~

虚函数机制相关


问：virtual function的优缺点（提问概率：★★★★）

优点：实现多态
缺点：MFC中的消息机制以及Qt中都没有采用C++中的虚函数机制，原因大概如下~

1.在子类很少覆盖基类函数实现的时候内存开销太大，每个类需要产生一张虚表，每生成一个对象的时候，需要在对象里存放一个vptr。

2.基类指针指向派生类对象的情况下，不方便内联优化（有些情况可以内联，参考我前面的文章）

3.在执行效率上肯定多了一些开销，需要寻找函数地址

4.虚表的存在可能破坏一些封装安全，可以通过vptr绕过private的限制

参考书籍与资料：《C++ Primer》《The Design and Evolution of C++》（C++语言的设计与演化）



问：多继承的优缺点（提问概率：★★★）

好处：简单来讲就是为了实现多个基类特有的功能

缺点：菱形继承；二义性（可通过虚继承解决）

参考书籍与资料：《C++ Primer》《The Design and Evolution of C++》（C++语言的设计与演化）



问：为什么要用virtual destructor?为什么没有virtual constructor?（提问概率：★★★★）

问题一：

为了能正常调用子类的析构函数，否则会出现只调用基类析构函数而没有调用子类析构函数情况。（如果子类有指针成员且申请了堆空间，不调用子类调用析构函数就会造成内存泄漏）

class Base
{
public:
    virtual ~Base()
    {         
         cout<<"delete Base"<<endl;
    };
};

class Derive : public Base
{
  public:
    int* p;
    Derive()
    {
      p = new int;//构造时申请空间
    }
   ~Derive()
   {
       delete p;//析构时释放空间
       cout<<"delete Derive"<<endl;
   };
};

int main()
{
    Base *pbase = new Derive;
    delete pbase ;
    //如果析构函数不是virtual，就只会调用当前指针类型的析构函数（也就是基类Base的析构函数）。
    //反之，则会根据虚表找到派生类的析构函数并调用。
    //由于C++语言机制(或者说编译器会插入一些额外的代码)，调用完子类的析构函数后会自动调用基类的析构函数

    return 0;
}
问题二：

第一点，构造函数执行前，对象的内存信息都没有，vptr也没有初始化，如何找到虚函数表，实现虚调用。其次，需要理解虚函数的意义，他是为了实现多态，让子类去覆盖父类的操作，但是前提是你需要知道当前的类型是什么，而C++里面构造函数可以说决定了他的类型。另外，构造函数与析构函数的执行不同，他是从父类开始一步一步的构造成一个子类(即使父类没有构造函数也可能会被编译器合成一个)，所以你不能跳过父类的构造函数，子类的很多成员可能需要在父类的基础上去初始化。
不过，从设计的角度来考虑的话，虚构造的思想还是有意义的，和我们设计模式中的工厂模式有点类似，根据不同的类型去做不同的初始化。Delphi语言因为有一个祖先基类，所以可以做到虚构造，而C++从语言层面来讲不存在真正意义上的虚构造函数。

参考书籍与资料：《More Effective C++ 7.1》

构造函数不能是虚函数?

Delphi对象的产生和消亡过程 - findumars - 博客园

More C++ Idioms/Virtual Constructor



问：哪些函数不能是虚函数？

构造函数，上一个问题解释了。

static，虚函数为了实现多态需要通过this指针找到虚表，而static没有this指针。

inline，内联的话要看编译器，比较老的编译器可能不允许这样做，原因是内联过去的代码在编译时不清楚多态类型。不过目前的编译器已经可以对部分这样的情况作出优化，或者是拒绝内联。

友元函数，C++不支持友元函数的继承。



问：类的内存布局是什么样的？考虑有虚函数、多继承、虚继承几种情况。（提问概率：★★★★★）

简单总结一下就是类只有成员变量占用内存（静态成员不占类内部内存，函数不占内存）。如果有虚函数，每个类对象都会有一个虚函数指针Vptr（占用一个指针大小的内存），vptr指向一个虚函数表，表里面记录了各项标记virtual的函数，子类如果覆盖父类虚函数，对应虚表位置的虚函数会被子类的替换。如果是虚继承，还会有虚基类表记录当前对象相对虚基类的偏移，以及一个虚基类指针指向这个虚基类表。

虚表在编译完成时大小与布局就被决定了，加载时其内存位置也就被确定了。

1.单继承一个或多个类只有一个虚表一个虚指针
2.普通多继承会有基类的个数个虚表，基类的个数个虚指针。派生类自己独有的虚函数可能会放在第一个虚表的最后面
3.单个虚继承会有两个虚表（看情况）以及一个虚基类表，两个虚指针（这个可能与我们想象中的不一样，一个指向自己独有的虚函数的虚表，一个指向覆盖基类虚函数的虚表）以及一个虚基类指针与虚基类表 注意：如果派生类自己的虚函数与基类完全相同，可能只有一个虚表，一个虚指针
4.菱形多虚继承会有基类的个数个虚指针以及虚表（看情况，第3条有提到），有几个虚继承就有几个虚基类指针以及虚基类表
为了方便理解，转了几张图片https://www.cnblogs.com/demian/p/6538301.html（侵删）。不过，图片描述的不够详细，有一些情况没有考虑，可以的话建议看后面的代码示意。


单继承GrandChild——Child——Parent

多继承Derive——Base1；Derive——Base2；Derive——Base3 三个虚表，多余的虚函数会放到第一个虚表的后面

多继承菱形继承 D——B1 ；D——B2；B1——B；B2——B

多继承菱形虚继承D—— B1；D——B2；B1——B；B2——B
如果对对象的内存布局有疑问，可以自己写代码尝试。VS下面有命令可以方便的打印，/d1 reportSingleClassLayout+类名，/d1 reportAllClassLayout 放到项目属性的命令行里面，重新生成一下就会显示在控制台输出窗口里面，包括虚表结构。


class Base
{
public:
	int dataB;
	virtual void Get() {};
};

class B1 :virtual  public Base
{
public:
	int dataB1;
	virtual void GetB1() {};
};

class B2 :virtual  public Base
{
public:
	int dataB2;
	virtual void Get() {};
	virtual void GetB2() { dataB2++; };
};

class D : public B1, public B2
{
public:
	int dataD;
	virtual void GetD() {};
};

class B3 : public Base
{
public:
	int dataB3;
	virtual void GetB3() {};
};
//Vs打印的内存布局
class Base	size(8):
1>  	+---
1>   0	| {vfptr}
1>   4	| dataB
1>  	+---
1>
1>  Base::$vftable@:
1>  	| &Base_meta
1>  	|  0
1>   0	| &Base::Get
1>
1>  Base::Get this adjustor: 0
1>
1>  class B1	size(20):
1>  	+---
1>   0	| {vfptr}
1>   4	| {vbptr}
1>   8	| dataB1
1>  	+---
1>  	+--- (virtual base Base)
1>  12	| {vfptr}
1>  16	| dataB
1>  	+---
1>
1>  B1::$vftable@B1@:
1>  	| &B1_meta
1>  	|  0
1>   0	| &B1::GetB1
1>
1>  B1::$vbtable@:
1>   0	| -4
1>   1	| 8 (B1d(B1+4)Base)
1>
1>  B1::$vftable@Base@:
1>  	| -12
1>   0	| &Base::Get
1>
1>  B1::GetB1 this adjustor: 0
1>  vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>              Base      12       4       4 0
1>
1>  class B2	size(20):
1>  	+---
1>   0	| {vfptr}
1>   4	| {vbptr}
1>   8	| dataB2
1>  	+---
1>  	+--- (virtual base Base)
1>  12	| {vfptr}
1>  16	| dataB
1>  	+---
1>
1>  B2::$vftable@B2@:
1>  	| &B2_meta
1>  	|  0
1>   0	| &B2::GetB2
1>
1>  B2::$vbtable@:
1>   0	| -4
1>   1	| 8 (B2d(B2+4)Base)
1>
1>  B2::$vftable@Base@:
1>  	| -12
1>   0	| &B2::Get
1>
1>  B2::Get this adjustor: 12
1>  B2::GetB2 this adjustor: 0
1>  vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>              Base      12       4       4 0
1>
1>  class D	size(36):
1>  	+---
1>   0	| +--- (base class B1)
1>   0	| | {vfptr}
1>   4	| | {vbptr}
1>   8	| | dataB1
1>  	| +---
1>  12	| +--- (base class B2)
1>  12	| | {vfptr}
1>  16	| | {vbptr}
1>  20	| | dataB2
1>  	| +---
1>  24	| dataD
1>  	+---
1>  	+--- (virtual base Base)
1>  28	| {vfptr}
1>  32	| dataB
1>  	+---
1>
1>  D::$vftable@B1@:
1>  	| &D_meta
1>  	|  0
1>   0	| &B1::GetB1
1>   1	| &D::GetD
1>
1>  D::$vftable@B2@:
1>  	| -12
1>   0	| &B2::GetB2
1>
1>  D::$vbtable@B1@:
1>   0	| -4
1>   1	| 24 (Dd(B1+4)Base)
1>
1>  D::$vbtable@B2@:
1>   0	| -4
1>   1	| 12 (Dd(B2+4)Base)
1>
1>  D::$vftable@Base@:
1>  	| -28
1>   0	| &thunk: this-=4; goto B2::Get
1>
1>  D::GetD this adjustor: 0
1>  vbi:	   class  offset o.vbptr  o.vbte fVtorDisp
1>              Base      28       4       4 0
1>
1>  class B3	size(12):
1>  	+---
1>   0	| +--- (base class Base)
1>   0	| | {vfptr}
1>   4	| | dataB
1>  	| +---
1>   8	| dataB3
1>  	+---
1>
1>  B3::$vftable@:
1>  	| &B3_meta
1>  	|  0
1>   0	| &Base::Get
1>   1	| &B3::GetB3
1>
1>  B3::GetB3 this adjustor: 0
另外，sizeof（）可以计算一个出一个类对象的大小，大小一般是类中的所有成员的sizeof()大小之和，其实就是遵循上面提到的内存布局

参考书籍与资料：《The Design and Evolution of C++》（C++语言的设计与演化）《Inside the C++ Object Model》（深度探索C++对象模型）

虚继承及继承的内存布局





问：dynamic_cast是怎么实现的（提问概率：★★★★）

dynamic_cast属于RTTI,运行时类型识别的一个内容，他是c++realise1.0的主要扩充功能之一。主要内容是typeid与typeinfo的实现,基本思路就是在有虚函数的类的虚表的头部位置存放RTTI的相关信息。在VC里面可以看到是一个叫做RTTI Complete Object Locator的结构体里面存放相关的信息。在强转的时候，会读取里面对应的类的信息进而判断是否能转换成功。


参考书籍与资料：《The Design and Evolution of C++》（C++语言的设计与演化）

c _rtti机制深度剖析

Classes, Methodsand RTTI

Visual C++ RTTI Inspection



C++内存管理相关


问：C++内存模型是什么？如何理解自由存储区与堆的区别？（提问概率：★★★★）

在C++中，内存区分为5个区，分别是堆、栈、自由存储区、全局/静态存储区、常量存储区。malloc在堆上分配的内存，使用free释放内存，而new所申请的内存则是在自由存储区上，使用delete来释放，不过这只是表象。进一步来讲，基本上所有的C++编译器默认使用堆来实现自由存储，即缺省的全局运算符new和delete也会按照malloc和free的方式来被实现，这时藉由new运算符分配的对象，说它在堆上也对，说它在自由存储区上也正确。
所以，new所申请的内存区域在C++中称为自由存储区，如果是通过malloc实现的，那么他也是在堆上的。
参考书籍与资料：《The Design and Evolution of C++》（C++语言的设计与演化）

https://www.cnblogs.com/QG-whz/p/5060894.html



问：memory alignmentand padding, 内存对齐的原理与意义（提问概率：★★★★）

结构体以及类成员对齐，意义就是减少cpu读取的次数，提高效率。比如一个int变量长度为4个字节，cpu一次读4个字节，当然是一次读取比较好。但是如果前面有一个char，地址为0-1。那么这个int的地址就为1-4。导致cpu，分两次读取int值。
具体的对齐规则，要说的非常准确可能比较麻烦，简单来讲就是，每个变量看后面的变量，如果后面的变量大，就和后面的大小对齐并补充字节。最后一个变量，按照成员内最大的对齐值，对齐并补充字节。

参考书籍与资料：

对内存对齐的深一步理解

５分钟搞定内存字节对齐

内存对齐与内存分配原则



问：std::shared_ptr的实现，reference count在哪里定义（提问概率：★★★）

shared_ptr作为一种非侵入式智能指针（不需要在用户类中记录引用计数），本质上一个模板类，表现上与指针相同，是因为重载了&以及*这两个运算符（当然还有=等运算符）。由于其本身的计数机制，防止资源泄露上面很有意义。
Shareptr在实现上有两个核心的成员，一个是指向资源对象的指针变量，另一个是指向引用计数的指针变量。第一个参数不言而喻，第二个参数为什么也是指针？因为多个shared_ptr对象指向同一资源时，其中一个shared_ptr对象析构了count = count -1,是不会影响到其他shared_ptr对象的，所以使用指针可以达到多个shared_ptr对象指向同一资源的能够共享count计数的目的。另外，原生的shared_ptr的读写在多线程当中是不安全的，因为读写不具有原子性，所以多线程使用shared_ptr一定要加锁。循环引用会造成内存泄露。

参考书籍与资料：

std::shared_ptr

为什么多线程读写 shared_ptr 要加锁？

非侵入式指针



问：new expression,operator new和malloc的联系（提问概率：★★★★）

malloc：是从C语言移植过来的语义，表示申请一定大小的内存并返回void*指针，在堆上申请内存，申请失败会返回Null
new：C++里的关键字，针对对象而言，申请一块内存的然后并在内存上构造对应的对象，最后返回该对象的指针。深入：new是从自由存储区分配的内存，自由存储区可能不在堆上，在静态存储区（全局变量做的对象池）。申请失败会抛出异常。可以通过new[]对数组进行内存申请与构造
operator new：C++里面与Malloc类似的语义，只申请内存而不构造对象
New操作的第一步就是调用operator New来执行内存的申请。深入：operator new可以基于malloc实现，一般也都是这么做的，可以被重载

关于New的重载：我们可以重载operator new来使用自己的分配器，C++标准规定重载的operator new必须是类成员函数或全局函数。在全局中重载operator new会修改所有默认的new方式，具体类中的重载只会影响到该类的内存分配与释放，不过由于operator new是在类的具体对象被构建出来之前调用的，所以必须声明为static。operator new还有另一种声明，可以定位内存申请的文件与位置

void* operator new(size_t size, const char* file, int line); 
string* pStr = new (__FILE, __LINE__) string; 

参考书籍与资料： 《C++ Primer》《The Design and Evolution of C++》（C++语言的设计与演化）
http://blog.csdn.net/wudaijun/article/details/9273339
http://blog.jobbole.com/102002/#article-comment



问：placement new的意义（提问概率：★★★）

placement new作用不太像new，或者说只是一个不完整的new，因为他不分配内存，只是在给定地址上调用构造函数，在c++里面，placement new实际上就是operator new的一种重载方式之一。
一个普通的new可以拆分成两步，第一步，申请内存返回指针，执行一个非placement的operator new(可能通过malloc实现)。第二步，在指定位置上构造对象(这个操作一般是编译器帮我们做了，但是并不是执行placement new，虽然功能上差不多，这里面有细微的差别)。c++单独提供给我们一个placement new来做第二步操作，因为有的时候我们可能想使用自己的内存申请方式(比如malloc)，但是你发现除了placement new以外你好像没有其他办法在指定位置上调用构造函数。
另外，想要使用placement new，底层系统并不告诉你这个地址上是否已经有对象了，如果你在已经构造的对象上面执行，那么前一个对象就会被销毁，理论上析构函数也不会执行。总之，要避免这种情况。

参考书籍与资料：《Inside the C++ Object Model》（深度探索C++对象模型）

What uses are there for “placement new”?

Placement new operator in C++



问:allocator的实现与使用意义（提问概率：★★★）

c++11新标准里面加入，他本身是一个类模板，功能上其实就是把new拆开，把内存申请和对象构造分成两个步骤，是不是很熟悉？这不就是operator new和placement new么？实际上allocator就是利用operator new来实现的。
为什么要这么做？举个例子，假如我要new一个长度为100的string数组，那我在申请内存的同时还要构造100个string对象，而实际上我整个程序从开始到结束可能只用了10个string。那为了减小构造的开销，这里就将内存申请与对象构造分开，也就有了allocator。当然，我们也可以使用operator new来做这个操作，只不过allocator帮我们做了一些简单的封装，类型检查等。另外，说到allocator就不得不提一下stl里面的空间配置器alloc，他除了上面简单的封装外还还考虑到了以下三个方面：1.多线程内存分配(内存池互斥访问)2.内存分配失败的异常处理3.实现一个轻量级内存池来解决小块内存导致的内存碎片问题
第一种情况，基本的实现就是在构造时加锁，析构时解锁。
内存分配失败的话，给用户提供一个函数去定义异常时的处理逻辑。
针对内存碎片问题，sgi stl里面的allocator里面设计了一个双层配置器，当申请内存超过128byte，就认为足够大，直接调用malloc分配。反之，调用第二级配置器使用内存池来处理，内存池实现思路就是先申请一块比较大的内存，分成n块，每次有小的内存申请时就给他一块。

参考书籍与资料：《STL源码剖析》

https://en.cppreference.com/w/cpp/memory/allocator

https://zh.wikipedia.org/wiki/%E5%88%86%E9%85%8D%E5%99%A8_(C%2B%2B)



问：RAII是什么？有什么意义？应用场景？（提问概率：★★★★）

RAII 是 resource acquisition is initialization 的缩写，意为“资源获取即初始化”。其核心是把资源和对象的生命周期绑定，对象创建获取资源，对象销毁释放资源。常见的例子就是智能指针，通过声明一个包含资源对象指针的类，在这个类执行析构的时候释放指针指向的对象。

参考书籍与资料：

RAIIWiki

RAII cppreference.com





问：内存泄露是什么意思？如何检测与避免内存泄漏？（提问概率：★★★★）

指由于疏忽或错误造成程序未能释放已经不再使用的内存的情况。内存泄漏并非指内存在物理上的消失，而是应用程序分配某段内存后，由于设计错误，导致在释放该段内存之前就失去了对该段内存的控制，从而造成了内存的浪费

检测:windows可以使用crtdumpmemoryleaks替换free为freedebug还可以使用crtmemcheckpoint结合difference比较。一般不同的工具都会提供相应的内存泄漏检测的方法。

避免:智能指针，如ue4垃圾回收机制。

参考书籍与资料：C/C++内存泄漏及检测





问：成员函数调用delete this会发生什么？之后再进行读写会怎么样？（提问概率：★★★★）

在类的成员函数中能不能调用delete this？答案是肯定的，能调用，而且很多老一点的库都有这种代码。假设这个成员函数名字叫release，而delete this就在这个release方法中被调用，那么这个对象在调用release方法后，还能进行其他操作，如调用该对象的其他方法么？答案仍然是肯定的，调用release之后还能调用其他的方法，但是有个前提：被调用的方法不涉及这个对象的数据成员和虚函数。

如果这时候调用普通的成员函数应该没有问题，因为这些成员函数与普通函数区别不大也在代码段，也需要走函数栈的逻辑。

如果调用虚函数，那就需要获取类内存的虚函数指针，这就涉及到堆内存的操作了，因为这时候虚函数指针也会被设置成未初始化的值，会有问题。

如果操作非指针成员变量，可能读和写都没有问题。

如果操作指针成员变量，指针可能设置成未初始化的值，很可能指向不合法的地方，强制赋值可能会导致崩溃

简单来说就是不要再去操作他的内存数据，否则很有可能崩溃，因为释放后，这个内存不确定系统如何处理。

另外，delete this会去调用本对象的析构函数，而析构函数中又调用delete this，形成无限递归，造成堆栈溢出，系统崩溃。

参考书籍与资料：what will happen if you do “deletethis;” in a member function?

在类的成员函数中调用delete this



STL相关
问：vector的实现与增长（提问概率：★★★★★）

vector是stl提供的动态数组，想了解他就要从他的特性开始分析。首先，他是一个模板类，意味着可以存放各种类型的元素，同时他也是一个数组，存储是连续的。 里面保存了三个指针，分别指向头、数据尾、数组尾。


内存分配:常规的数组必须在定义的时候就分配好固定的大小，而vector可以动态的改变，也就说明他可以动态的申请与释放内存。我们要知道，频繁的申请与释放内存对程序的效率影响是非常大的，因为如果当前地址空间不够用的话，就需要重新找一块更大的空间来装数据，再把数据全部都拷贝过去。所以vector为了达到比较好的效果，在添加元素的时候会多申请一定大小的内存，从而减少内存分配的次数。capacity()返回的就是包括缓冲区在内的空间大小，而size()返回的就是当前实际使用的空间大小。

如果想主动的提前分配内存，可以使用reserve(n)，如果n大于当前的capacity就会强制重新分配一次内存，超出实际使用的部分就会成为缓存区。如果想直接构造出长度为n的动态数组可以使用resize(n)，会严格使其size大小为n，如果n比当前size小的话，大于size的数据都会被清空移除；如果n比当前size大比capacity小，就会添加额外的元素（新增的元素可以是默认值，也可以是传入的参数）；如果比capacity还大的话还会重新执行一次内存分配（并不一定要调用reverse，直接分配）新的空间的大小为_Oldcapacity + _Oldcapacity / 2（如果n>_Oldcapacity + _Oldcapacity / 2，那么新的内存空间大小就是n）

关于内存释放，如果只是简单的调用 clear()全部清空数据，erase()清空部分数据都只是单纯的清空里面的数据并不会释放掉。默认只会在调用vector的析构函数的时候才会真正释放空间，所以如果想强制释放内存空间，正式的做法是resize（0），然后调用C++11的shrink_to_fit()。C++11之前有一个特殊的方法，那就是新建一个空的vector，然后与这个vector使用swap进行内存交换，那么原来的vector就会释放。另外，由于涉及到模板，也就会涉及到迭代器，凡是重新申请过内存，插入删除数据的，迭代器都会失效，理解上也很容易就是指针可能指向的不是你原来的那个位置了。

参考书籍与资料：《STL源码解析》（SGI的STL），VC STL里面的源码（打开VS自己看，读起来比较吃力）

https://zh.cppreference.com/w/cpp/container/vector/resize



问：map的实现 unordered_map的原理；如果从空的table开始一直增加元素，会出现什么情况？（提问概率：★★★★★）

map分为有序map和无序map（unordered_map），实现的基本数据结构分别是红黑树与哈希表。(set同理)里面每一个元素是一个pair< const key_type,mapped_type >类型，注意key是const的，不可以修改。对于一个数据结构，常见的操作无非是查找，插入，删除。红黑树作为一种二叉搜索树，具有log(n)的查找效率，不过前提是数据具有足够的随机性。！！！
hashmap理想上则是具有常数平均时间的效率，或者说一次或几次就可以查到，当然如果数据量过大，散列表空间就不能和数据量保持1：1，这时候就要靠hash函数来处理数据，将数据尽可能的分散在不同的桶bucket里面。
sgi stl的hash使用的是开链操作来避免hash表空间过大又想保持一定效率的问题，开链就是在一个位置用链表来存储所有冲突项。其实hashmap里面常说的桶bucket就是vector数组的一个元素，每个桶里面的数据是以链表(开链)的形式存储，进一步来说这些操作与定义都是通过一个基本的数据结构hashtable来实现的，所有的无序关联容器都是。hashtable里面的hash函数就是常说的取模函数，根据存储数据key值(注意，是对key而不是value)对桶的长度取余数来存放。默认提供的hash函数无法处理常见内置类型以外的数据，如各种自定义类，其实string本身也算是特殊类型，但是语言内部可以转为const char*处理，他经过函数处理也会得到一个size类型（一般对字符串的哈希函数比较特别，参考各种字符串Hash函数比较）。

什么时候需要rehash？当你的桶里面的平均数量（Map大小/桶的数量）大于max(这个可以自己设置)，就需要rehash。也可以主动调用rehash(n),保证桶的数量大于n，注意n是桶的数量。改变桶的数量就相当于改变Vector的长度，如果超过vector的capacity就会调用Vector的扩容机制（但是实际上他每次hash的时候都会直接调用vector的reserve进行扩容）。
什么时候执行reserve（Java里好像是resize）？注意map的reserve与vector的reserve不一样，他的目的并不是扩容，而是希望当前哈希表里面可以容纳n个元素。如果n>桶的数量*负载因子的时候就会触发rehash，否则不会触发。rehash有可能进一步触发vector的扩容。参考下面的英文注释。

Request acapacity change Sets the number of buckets in the container
(bucket_count) to the most appropriate to contain at least n elements.
If n is greater than the current bucket_count multiplied by the
max_load_factor, the container’s bucket_count is increased and a
rehash is forced. If n is lower than that, the function may have no
effect.
不过我发现 VC的STL里面的处理方式好像不太一样，他是自动先检测是否满足当前负载因子>最大负载因子，满足就会先触发重新设置桶的数量，如果桶的数量小于512就直接乘以8，否则如果小于Vector容量的一半的话就乘以2。这个过程我们看到他直接设置桶的数量并没有调用rehash函数，如果是主动调用rehash的话是直接翻倍的。而且不论是手动还是自动调整桶的数量，他都会触发Vector的扩容函数。

//手动调用：重新分配桶的数量
void rehash(size_type _Buckets)
{  // rebuild table with at least _Bucketsbuckets
   size_type _Maxsize = _Vec.max_size() / 4;
   size_type _Newsize = _Min_buckets;
 
   for (; _Newsize < _Buckets && _Newsize <_Maxsize; )
        _Newsize *= 2;  // doubleuntil big enough
   if (_Newsize< _Buckets)
        _Xout_of_range("invalid hash bucket count");
   while (!(size() / max_load_factor() < _Newsize)
        && _Newsize < _Maxsize)
        _Newsize *= 2;  // doubleuntil load factor okay
 
   _Init(_Newsize);
   _Reinsert();
}

//自动检查：设置桶的数量
void _Check_size()
{  // grow table as needed
   if(max_load_factor() < load_factor())
   {   // rehash to bigger table
        size_type _Newsize = bucket_count();
 
        if (_Newsize <512)
            _Newsize *= 8;  //multiply by 8
        elseif (_Newsize <_Vec.max_size() / 2)
           _Newsize *= 2;  //multiply safely by 2
        _Init(_Newsize);
        _Reinsert();
   }
}

//重新分配桶的数量，同时进行扩容
void _Init(size_type _Buckets = _Min_buckets)
{  // initialize hash table with _Bucketsbuckets, leave list alone
   _Vec.reserve(2 * _Buckets); // avoidcurdling _Vec if exception occurs
   _Vec.assign(2 * _Buckets, _Unchecked_end());
   _Mask = _Buckets - 1;
   //赋值_Maxidx，重新设置桶的数量
   _Maxidx = _Buckets;
}
参考书籍与资料：《STL源码解析》（SGI的STL），VC STL里面的源码（打开VS查看）

std::map::erase



问：stl里deque是如何实现的？（提问概率：★★★）

其实deque由一段一段内存构成的，他是分段连续,而不是内存连续。当走向段的尾端时候自动跳到下一段。map记录着一系列的固定长度的数组的地址，这个map仅仅保存的是数组的地址,真正的数据在数组中存放着。deque先从map中央间的位置(因为双向队列，前后都可以插入元素，前面需要留出一定的空间)找到一个数组地址，向该数组中放入数据，数组不够时继续在map中找空闲的数组来存数据。当map也不够时重新分配内存当作新的map,把原来map中的内容copy的新map中。所以使用deque的复杂度要大于vector，尽量使用vector。（图片来自网络，侵删）



参考书籍与资料：《STL源码解析》（SGI的STL），VC STL里面的源码（打开VS查看）



问：stl里heap与priority_queue？（提问概率：★★）

heap是基于vector来实现的，不过他不属于容器组件，因为他的主要是为优先级队列priority_queue的实现提供基础结构。所谓的优先级队列，其实就是队首元素一定是当前队列中优先级最高的那一个，只能通过 top() 函数来访问队首元素。我们知道最大堆与最小堆拥有这种特性，所以很适合用来实现priority_queue，当然其他数据结构也可以实现，不过从实现复杂度与计算复杂度等方面heap最为合适。

参考书籍与资料：《STL源码解析》（SGI的STL），VC STL里面的源码（打开VS查看）

std::priority_queue



问：stl里面各个容器的基础数据结构是？（提问概率：★★★★）

图截自STL源码分析一书，常问的是优先级队列，hashmap，map底层的数据结构是什么。答案分别是Vector，hashtable以及RB—tree（红黑树），具体细节大家可以仔细看一下关于容器的这两章内容。




参考书籍与资料：“STL源码”，《STL源码剖析》
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》网络同步原理深入（下）[原理分析]</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/55596030
由于知乎每篇文章有字数限制，实在没办法在上一篇里面添加新的内容，所以就把网络同步深入这块拆成了两篇文章。这次更新主要是在网络数据包格式、PacketHandler、条件复制、可靠数据传输、ReplicationGraph等方面做了进一步的分析与阐述。（壁纸与上篇相对应~）

PS：如果只是想知道怎么使用同步，建议阅读这篇文章 关于网络同步的理解与思考[概念理解]

目录（下篇）
五．属性同步细节
- 1. 属性同步概述
- 2. 重要数据的初始化流程
- 3. 发送同步数据流程分析
- 4. 属性变化历史记录
- 5. 属性回调函数执行
- 6. 关于动态数组与结构体的同步
- 7. UObject指针类型的属性同步
- 8. UObject指针类型的属性更新（更新）
- 9. 条件复制（更新）
六．RPC执行细节
七 . 可靠数据传输（更新）
- 1. 数据包格式
- 2. PacketHandler
- 3. Bunch的发送时机
- 4. 可靠数据传输的实现
- 5. 属性的可靠传输
八 . ReplicationGraph系统（更新）
上篇链接：《Exploring in UE4》网络同步原理深入（上）[原理分析]

五． 属性同步细节
1.属性同步概述
属性同步是一个很复杂的模块，我在另一个关于UE4网络思考文章里面讲解了属性同步相关的使用逻辑以及注意事项。这里我尽可能的分析一下属性同步的实现原理。有一点需要先提前说明一下，服务器同步的核心操作就是比较当前的同步属性是否发生变化，如果发生就将这个数据通过到客户端。如果是普通逻辑处理，我们完全可以保存当前对象的一个拷贝对象，然后每帧去比较这个拷贝与真实的对象是否发生变化。不过，由于同步数据量巨大，我们不可能给每个需要同步的对象都创建一个新的拷贝，而且这个逻辑如果暴露到逻辑层的话会使代码异常复杂难懂，所以这个操作要统一在底层处理。那么，UE4的基本思路就是获取当前同步对象的空间大小，然后保存到一个buffer里面，然后根据属性的OffSet给每个需要同步的属性初始化。这样，就保存了一份简单的“拷贝”用于之后的比较。当然，我们能这么做的前提是存在UE的Object对象反射系统。

（注意：虽然UE4的底层是可靠的UDP，但是不代表我们所有的网络数据都是可靠的。属性同步其实就并不完全可靠，除了一开始同步Actor的时候，属性同步是可靠的，但是后期的发送并不是，但是引擎内部有一定的机制可以保证客户端能收到服务器最后同步的属性消息，文章的最后一部分会谈到这些）

下面开始进一步描述属性同步的基本思路：我们给一个Actor类的同步属性A做上标记Replicates（先不考虑其他的宏），然后UClass会将所有需要同步的属性保存到ClassReps列表里面，这样我们就可以通过这个Actor的UClass获取这个Actor上所有需要同步的属性，当这个Actor实例化一个可以同步的对象并开始创建对应的同步通道时，我们就需要准备属性同步了。

首先，我们要有一个同步属性列表来记录当前这个类有哪些属性需要同步（FRepLayout，每个需要同步的网络对象【一个actor对象或者一个RPC对象】有一个，从UClass里面初始化）；其次，我们需要针对每个对象保存一个缓存数据，来及时的与发生改变的Actor属性作比较，从而判断与上一次同步前是否发生变化（FRepState，里面有一个Staticbuff来保存）；然后，我们要有一个属性变化跟踪器记录所有发生改变同步属性的序号（可能是因为节省内存开销等原因所以不是保存这个属性），便于发送同步数据时处理（FRepChangedPropertyTracker，对各个Connection可见，被各个Connection的Repstate保存一个共享指针，新版本被FRepChangelistState替换）。最后，我们还需要针对每个连接的每个对象有一个控制前面这些数据的执行者（FObjectReplicator）。

这四个类就是我们属性同步的关键所在，在同步前我们需要对这些数据做好初始化工作，然后在真正同步的时候去判断与处理。

注：在4.12后的版本，新增了一个属性，FReplicationChangelistMgr。FReplicationChangelistMgr 里面保存了FRepChangelistState，FRepChangelistState属性可谓是兼顾FRepState以及FRepChangedPropertyTracker双重功能，他里面有一个Staticbuff来保存Object对象一个缓存数据，用来在服务器比较对象属性是否发生变化，同时又有一个FRepChangedHistory来记录所有发生过属性变化的历史记录[大小有限制]。然而，这不代表他能替代FRepState与FRepChangedPropertyTracker。目前，客户端在检测属性是否发生变化时使用的仍旧是RepState里面的Staticbuff。在处理条件属性复制时的判断使用的仍然是FRepChangedPropertyTracker
2.重要数据的初始化流程
下面的两个图分别是属性同步的服务器发送堆栈以及客户端的接收堆栈。


图5-1服务器发送属性堆栈图

图5-2客户端接收属性堆栈图
从发送堆栈中我们可以看到属性同步是在执行ReplicatActor的同时进行的，所以我们也可以猜到属性同步的准备工作应该与Actor的同步准备工作是密不可分的。前面Actor同步的讲解中我们已经知道，当Actor同步时如果发现当前的Actor没有对应的通道，就会给其创建一个通道并执行SetChannelActor。这个SetChannelActor所做的工作就是属性同步的关键所在，这个函数里面会对上面四个关键的类构造并做初始化，详细的内容参考下图：


图5-3 SetChannelActor流程解析图


图中详细的展示了几个关键数据的初始化，不过第一次看可能对这个几个类的关系有点晕，下面给大家简单画了一个类图。


图5-4属性同步相关类图
具体来说，每个ActorChannel在创建的时候会创建一个FObjectReplicator用来处理所有属性同步相关的操作，同时会把当前对应通道Actor的同步的属性记录在FRepLayOut的Parents数组里面（Parents记录了每个属性的UProperty，复制条件，在Object里面的偏移等）。

同时把这个RepLayOut存储到RepState里面，该RepState指针也会被存储到FObjectReplicator里面，RepState会申请一个缓存空间用来存放当前的Object对象（并不是完整对象，只包含同步属性，但是占用空间大小是一样的，用于客户端比较）

当然，FObjectReplicator还会保存一个指向FReplicationChangelistMgr的指针，指针对应对象里面的FRepChangelistState也申请一个缓存空间staticbuff用来存放当前的Object对象（用于服务器比较），同时还有一个ChangeHistory来保存属性的变化历史记录。

FRepChangedPropertyTracker在创建RepState的同时也被创建，然后通过FRepLayOut的Parents数量来初始化他的记录表的大小，主要记录对应的位置是否是条件复制属性，RepState里面保存一个指向他的指针。

关于Parents属性与CMD属性：Replayout里面，数组parents示当前类所有的需要同步的属性，而数组cmd会将同步的复杂类型属性（包括数组、结构体、结构体数组但不包括类类型的指针）进一步展开放到这里面。比如ClassA里面有一个StructB属性，这个属性被标记同步，StructB属性会被放到parents里面。由于StructB里面有一个Int类型C属性以及D属性，那么C和D就会被放到Cmd数组里面。有关结构体的属性同步第5部分还有详细描述
3.发送同步数据流程分析
前面我们基本上已经做好了同步属性的基本工作，下面开始执行真正的同步流程。


图5-5服务器发送属性堆栈图
再次拿出服务器同步属性的流程，我们可以看到属性同步是通过FObjectReplicator:: ReplicateProperties函数执行的，进一步执行RepLayout->ReplicateProperties。这里面比较重要的细节就是服务器是如何判断当前属性发生变化的，我们在前面设置通道Actor的时候给FObjectReplicator设置了一个Object指针，这个指针保存的就是当前同步的对象，而在初始化RepChangelistState的同时我们还创建了一个Staticbuffer，并且把buffer设置和当前Object的大小相同，对buffer取OffSet把对应的同步属性值添加到buffer里面。所以，我们真正比较的就是这两个对象，一般来说，staticbuffer在创建通道的同时自己就不会改变了，只有当与Object比较发现不同的时候，才会在发送前把属性值置为改变后的。这对于长期同步的Actor没什么问题，但是对于休眠的Actor就会出现问题了，因为每次删除通道并再次同步强制同步的时候这里面的staticbuff都是Object默认的属性值，那比较的时候就可能出现0不同步这样奇怪的现象了。真正比较两个属性是否相同的函数是PropertiesAreIdentical()，他是一个static函数。


图5-6 服务器同步属性流程图
4. 属性变化历史记录
ChangeHistory属性在在FRepState以及FRepChangelistState里面都存在，不过每次同步前都是先更新FRepChangelistState里面的ChangeHistory，随后在发送前将FRepChangelistState的本次同步发生变化数据拷贝到FRepState的ChangeHistory本次即将发送的变化属性对应的数组元素里面。简单来说，就是FRepState的ChangeHistory一般只保存当前这一次同步发生变化的属性序号，而FRepChangelistState可以保存之前所有的变化的历史记录（更准确的说是最近的64次变化记录）。


图5-7
注意：合并的过程可能会出现同一个属性都发生变化的情况，不过由于里面只是记录了他是否发生过变化，所以合并是不会发生冲突的，只要有一个历史记录里面有变化就认为合并后的结果也有变化。

5.属性回调函数执行
虽然属性同步是由服务器执行的，但是FObjectReplicator，RepLayOut这些数据可并不是仅仅存在于服务器，客户端也是存在的，客户端也有Channel，也需要执行SetChannelACtor。不过这些数据在客户端上的作用可能就有一些变化，比如Staticbuffer，服务器是用它存储上次同步后的对象，然后与当前的Object比较看是否发生变化。在客户端上，他是用来临时存储当前同步前的对象，然后再把通过过来的属性复制给当前Object，Object再与Staticbuffer对象比较，看看属性是否发生变化，如果发生变化，就在Replicator的RepState里面添加一个函数回调通知RepNotifies。 在随后的ProcessBunch处理中，会执行RepLayout->CallRepNotifies( RepState, Object );处理所有的函数回调，所以我们也知道了为什么接收到的属性发生变化才会执行函数回调了。


图5-8 客户端属性回调堆栈图
6.关于动态数组与结构体的同步
结构体：UE里面UStruct类型的结构体与C++的Struct不一样，在反射系统中对应的是UScriptStruct，他本身可以被标记Replicated并且结构体内的数据默认都会被同步，而且如果里面有还子结构体的话也也会递归的进行同步。如果不想同步的话，需要在对应的属性标记NotReplicated，而且这个标记只对UStruct有效，对UClass无效。这一段的逻辑在FRepLayout::InitFromObjectClass处理，ReplayOut首先会读取Class里面所有的同步属性并逐一的放到FRepLayOut的数组Parents里面，这个Parents里面存放的就是当前类的继承树里面所有的同步属性。随后对Parents里面的属性进一步解析（FRepLayout:: InitFromProperty_r），如果发现当前同步属性是数组或者是结构体就会对其进行递归展开，将数组的每一个元素/UStruct里面的每一个属性逐个放到FRepLayOut的Cmds数组里面，这个过程中如果遇到标记了NotReplicate的UStruct内部属性，就跳过。所以Cmds里面存放的就是对数组或者结构体进一步展开的详细属性。



图5-10 Cmds内部成员截图
Struct ：结构内的数据是不能标记Replicated的。如果你给Struct里面的属性标记Replicated，UHT在编译的时候就会提醒你编译失败”Struct members cannot be replicated”。这个提示多多少少会让人产生误解，实际上这个只是表明UStruct内部属性不能标记Replicated而已。最后，UE里面的UStruct不可以以成员指针的方式在类中声明。

数组：数组分为两种，静态数组与动态数组。静态数组的每一个元素都相当于一个单独的属性存放在Class的ClassReps里面，同步的时候也是会逐个添加到RepLayOut的Parents里面，参考上面的图5-9。UE里面的动态数组是TArray，他在网络中是可以正常同步的，在初始化RepLayOut的Cmds数组的时候，就会判断当前的属性类型是否是动态数组（UArrayProperty），并会给其cmd.type做上标记REPCMD_DynamicArray。后面在同步的时候，就会通过这个标记来对其做特殊处理。比如服务器上数组长度发生变化，客户端在接收同步过来的数组时，会执行FRepLayout::ReceiveProperties_DynamicArray_r来处理动态数组。这个函数里面会矫正当前对象同步数组的大小。



7.UObject指针类型的属性同步
上一节组件同步提到了FNetworkGUID，这引申出一个值得思考的细节。无论是属性同步，还是作为RPC参数。我们都可能产生疑问，我在传递一个UObject类型的指针时，这个UObject在客户端存在么？如果存在，我如何能通过服务器的一个指针找到客户端上相同UObject的指针？

这个处理就需要通过FNetworkGUID了。服务器在同步一个对象引用（指针）的时候，会给其分配专门的FNetworkGUID并通过网络进行发送。客户端上通过识别这个ID，就可以找到对应的UObject。

那么这个ID是什么时候分配的？如何发送的呢？

首先我们分析服务器，服务器在同步一个UObject对象时（包括属性同步，Actor同步，RPC参数同步三种情况），他都需要对这个对象进行序列化（UPackageMapClient::SerializeObject），而在序列化对象前，要检查GUID缓存表（TMap<FNetworkGUID, FNetGuidCacheObject>ObjectLookup;），如果GUID缓存表里面有，证明已经分配过，反之则需要分配一个GUID，并写到数据流里面。不过一般来说，GUID分配并不是在发送数据的时候才进行，而是在创建FObjectReplicator的时候（如图通过NetDriver的GuidCache分配）


图5-11 GUID的分配与注册
下面两段代码是服务器同步对象前检测或分配GUID的逻辑：

//UPackageMapClient::SerializeObjectPackageMapClient.cpp
//IsSaving表示序列化，即发送流程IsLoading表示反序列化，即接收流程
//由于知乎有字数限制，这里不粘贴完整代码
if (Ar.IsSaving())
{
   //获取或分配GUID
   FNetworkGUID NetGUID = GuidCache->GetOrAssignNetGUID(Object );
   if (OutNetGUID)
   {
	*OutNetGUID = NetGUID;
   }
   ......
}
// PackageMapClient.cpp
FNetworkGUIDFNetGUIDCache::GetOrAssignNetGUID(constUObject * Object )
{
    //查看当前UObject是否支持网络复制
    if( !Object || !SupportsObject( Object) )
    {  
      return FNetworkGUID();
    }
    ......
    //服务器注册该对象的GUID
     return AssignNewNetGUID_Server( Object );
}
下面我们再分析客户端的接收流程，客户端在接收到服务器同步过来的一个Actor时他会通过UPackageMapClient::SerializeNewActor对该Actor进行反序列化。如果这个Actor是第一次同步过来的，他就需要对这个Actor进行Spawn，Spawn结束后就会调用函数FNetGUIDCache::RegisterNetGUID_Client进行客户端该对象的GUID的注册。这样，服务器与客户端上“同”一个对象的GUID就相同了。下次，服务器再同步指向这个Actor的指针属性时就能正确的找到客户端对应的对象了。

不过等等，前面说的UObject，这里怎么就直接变成Actor了，如果是组件同步呢？他的GUID在客户端是怎么获取并注册的？

其实对于一个非Actor对象，客户端不需要在接收到完整的对象数据后再获取并注册GUID。他在收到一个函数GUID的Bunch串时就可以立刻执行GUID的注册，然后会通过函数FNetGUIDCache::GetObjectromNetGUID去当前的客户端里面寻找这个对象。找到之后，再去完善前面的注册信息。为什么要找而不是让服务器同步过来？因为有一些对象不需要同步，但是我们也知道他在客户端与服务器就是同一个UObject，比如地图里面的一座山。这种情况我们稍后讨论


图5-12 客户端收到消息立刻按照路径注册GUID
下面两段代码是客户端反序列化获取并注册GUID的逻辑：

// 情况一：客户端接收到服务器同步过来的一个新的Actor，需要执行Spawn spawn 成功后会执行RegisterNetGUID_Client进行GUID的注册
// UActorChannel::ProcessBunch DataChannel.cpp
bool SpawnedNewActor = false;
if( Actor == NULL)
{
    ......
    SpawnedNewActor = Connection->PackageMap->SerializeNewActor(Bunch,this,NewChannelActor);
    ......
}


// 情况二：客户端接收到一个含有GUID的消息立刻解析 解析成功后会执行RegisterNetGUIDFromPath_Client进行GUID的注册
//DataChannel.cpp
void UChannel::ReceivedRawBunch(FInBunch&Bunch, bool&bOutSkipAck)
{
   if( Bunch.bHasGUIDs )
   {
      Cast<UPackageMapClient>( Connection->PackageMap)->ReceiveNetGUIDBunch( Bunch );
      ......
   }
}
// UPackageMapClient::ReceiveNetGUIDBunchPackageMapClient.cpp
int32 NumGUIDsRead = 0;
while(NumGUIDsRead <NumGUIDsInBunch )
{
   UObject * Obj = NULL;
   InternalLoadObject(InBunch,Obj, 0 );
   ......
}


上面大部分讨论的都是标记Replicate的Actor或组件，但是并不是只有这样的对象才能分配GUID。对于直接从数据包加载出来的对象（前面说过如地图里面的山），我们可以直接认为服务器上的该地形对象与客户端上对应的地形对象就是一个对象。所以，我们看到还存在其他可以分配GUID的情况，官方文档上有介绍，我这里直接总结出来：

有四种情况下UObject对象的引用可以在网络上传递成功。

标记replicate
从数据包直接Load
通过Construction scripts添加或者C++构造函数里面添加
使用UActorComponent::SetNetAddressable标记（这个只针对组件，其实蓝图里面创建的组件默认就会执行这个操作）

下面这段代码展示了该UObject是否支持网络复制的条件，正好符合我上面的总结：

//PackageMapClient.cpp
boolFNetGUIDCache::SupportsObject(constUObject * Object )
{
  if( !Object )
  {
    return true;
  }
  FNetworkGUID NetGUID = NetGUIDLookup.FindRef(Object);
  //是否已经分配网络ID
  if( NetGUID.IsValid() )
  {
    return true;
  }
  //是否是数据包加载或者默认构造的
  if( Object->IsFullNameStableForNetworking())  
  {
    return true;
  }
  //不重载的情况下还是会走到IsFullNameStableForNetworking里面
  if( Object->IsSupportedForNetworking() )
  {
    return true;
  }
   return false;
}
我这里以地图里面的静态模型为例简单进行分析。对于地图创建好的一个静态模型，服务器只要发送该对象GUID以及对象的名称（带序号）即可。当客户端接收消息的时候，首先缓存GUID相关信息，随后通过函数FNetGUIDCache::GetObjectromNetGUID从本地找到对应的Object。（如图5-13里ObjectLookup[24]对应的StaticMeshActor_20，他就是一个非Replicate但是从数据包直接加载的对象）

下图5-13可以看出，分配GUID的对象不一定是游戏场景中存在的Actor，还可能是特定路径下某个资源对象，或者是一个蓝图类，或是一个CDO对象。进一步分析，一个在游戏里面实际存在的Actor想要同步的话，我们必须先将其资源文件，CDO对象先同步过去。然后再将实际的Actor同步，因为这样他才能正确的根据资源文件Spawn出来。而对于一个Actor的组件来说，他也需要等到他的Actor的资源文件，CDO对象先同步过去再进行同步。（由于网络包的异步性，这里并不是严格意义上的先后，而是指资源，CDO同步后，后面的Actor（组件）才能正常的反序列化成一个完整合法的对象）


图5-13 GUID缓存Map
最后再给出一个UObject作为RPC的参数发送前的GUID分配堆栈：


图5-14
关于动态组件的复制可能会有一些问题：我在文章《Exploring in UE4》关于网络同步的理解与思考[概念理解] 的最后有一些相关描述。

8.UObject指针类型的属性更新
一般来说，网络环境良好的情况下，网络包是按照我们发送的顺序反序列化的。但即使如此，我们还是会遇到各种与网络同步顺序相关的问题，大部分的问题都出在UObject类型的属性同步。

举个例子：服务器上有A和B两个replicated的Actor，A对象保存一个replicated的B类型属性，B对象保存一个A对象的replicated属性。A在同步的时候由于B没有同步过去，所以A的属性临时为空。当B同步到客户端的时候，会先执行Beginplay，但是这时候A对象里面的B属性仍然为空。

这样就会导致B::Beginplay里面找到属性A并尝试去处理A里面的B属性的相关逻辑失效。

那么为什么会这样？

首先，客户端每次收到数据包的时候会执行FObjectReplicator::ReceivedBunch去处理Bunch，这个函数有一个引用参数bOutHasUnmapped，函数会根据数据包的类型去处理Actor的Property或者RPC的Property，如果在反序列化的时候客户端上没有找到匹配的UObject，就会在引用参数里面标记bOutHasUnmapped并在UActorChannel::ProcessBunch里面将当前的actor的Replicator放到NetDriver的UnmappedReplicators数组里面。

拿Object类型的同步属性具体一点来说，FObjectReplicator::ReceivedBunch执行时会去尝试去反序列化该属性对应的UOBject（UPackageMapClient::SerializeObject），为了保持客户端与服务器对应属性的一致性服务器也会把GUID一同发送（Outer的GUID也可能在这个包里面），所以属性的GUID会在此刻被提前注册，虽然GUID可以注册成功，但是UObject对应的对象未必同步完成。如果反序列化失败就会把当前的GUID存放到TrackedUnmappedNetGuids里面。随后，就会判断TrackedUnmappedGuids的num是否大于0，是的话就会返回参数bOutHasUnmapped为true，另外还有一个引用参数bOutGuidsChanged表示其unmapped的GUID是否在同步过程中发生变化（比如该属性的Uobject对象发生改变）如果产生变化会调用UpdateGuidToReplicatorMap更新Netdiver的GuidToReplicatorMap，（关于GuidToReplicatorMap后面有进一步的描述）

其次，每个Actor在执行SerializeNewActor反序列化的时候都会将GUID放到GuidCache->ImportedNetGuids里面，表示当前帧新收到的Actor。（注册GUID的时候还会将GUID与对应的Object放到FNetGUIDCache的ObjectLookup里面。）每帧会在处理完收包以及所有对象的Tick之后通过TickFlush发送数据包，在发送之后会去处理unmapped的actor，这里会有一个比较复杂的筛选流程，

1.根据ImportedNetGuids确定当前帧所有新收到的actor
2.去全局的GuidToReplicatorMap里面查找新收到的actor是否属于之前unmapped的GUID，是的话，假如待处理数组
3.二次验证，根据UnmappedReplicators数据查找待处理数组是否处于其中，是的话执行Replicator->UpdateUnmappedObjects进行更新
筛选完成后通过函数FRepLayout::UpdateUnmappedObjects_r去遍历所有属性的FGuidReferences，判断是否有UnmappedGUIDs，有的话调用PackageMap->GetObjectFromNetGUID重新尝试获取unmapped的GUID，如果反序列化仍然失败，那么就保存其UnmappedReplicators，不做任何处理。如果成功，就会覆盖原来的值。并且如果当前Actor的所有属性的GUID都已经成功匹配，就会把自己从NetDriver的UnmappedReplicators移除。

处理完后调用UpdateGuidToReplicatorMap，再次遍历一下所有的UObject类型的同步属性，如果发现有新的unmapped的属性（比如新的RPC函数有UObject参数，或者属性发生改变），就会把当前unmapped属性的GUID以及当前对象的Replicator放到NetDriver的GuidToReplicatorMap里面，GuidToReplicatorMap是一个value为TSet< FObjectReplicator* >类型的数据结构。value为set的原因是当前unmapped属性可能在其他的ACtor里面也被引用，这样一个Unmapped的GUID可能会对应多个actor的Replicator。所以GuidToReplicatorMap是NetDriver控制的一个全局的对象，用来记录当前所有的unmapped对象的GUID以及他所在的actor。

这里的逻辑用前面的例子通俗一点来讲，A执行Beginplay的时候B没有同步过来，但是由于A有B的GUID，所以会先注册B的GUID，同时A的replicator会放到UnmappedReplicators并且将B的GUID与A的replicator组合成一个pair放到GuidToReplicatorMap里面。随后，B同步的时候会先通过收包执行Beginplay，Tick，最后执行发包的TickFlush。TickFlush的结尾，会通过ImportedNetGuids知道当前B是新来的对象，由于B在前面被放到了GuidToReplicatorMap里面，所以这里会找到A的replicator并执行更新，同时B也会去遍历看看有没有其他类型的Unmapped的对象，如果有会执行和前面A类型的操作。

所以，这个问题与整个引擎的逻辑执行顺序有关
1.TickDispatch收包
2.World对象Tick
3.TickFlush收包
对象的Beginplay执行在第一步，而unmapped的属性调整在第三步。



补充：Bunch缓存

有A和B两个Actor，A有一个replicated的属性B。

当A对象同步到客户端而B属性没有同步的时候，仍然会给B创建一个Channel的。而且这个数据包里面会有B的GUID，所以也会去给B注册GUID。

如果这个时候，客户端先收到了B的RPC或者其他属性的Bunch包，由于Actor还没有初始化（也就是GuidCache->IsGUIDLoaded为false）就需要临时把这个bunch缓存起来，放到ACtorChannel的queuebunches里面，同时把当前的ACtorChannel添加到当前Connection的TickChannel里面。（还有一种情况是他最先收到一个B的属性变化bunch，GUID甚至还没有注册）

每帧在发送数据包的时候（这时候已经确保收到了这一帧的所有网络包），去遍历所有的TickChannel的queuebunches，如果当前的ACtor已经被成功的反序列化就可以正常的处理这些queuebunches。

除了解决网络延迟造成的顺序不一致问题，我们也可以自定义的将某些包缓存存起来，通过函数ShouldQueueBunchesForActorGUID即可对某个特殊的Actor做bunch缓存，虚幻内置的回放系统就是这样处理的，在加载一个存档点的时候会有大量的数据包，为了避免卡顿，可以将大部分的包缓存起来逐帧处理。

9.条件复制
默认情况下所有的属性都是要同步的，除非我们设置条件复制。

void AActor::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
    DOREPLIFETIME_CONDITION( AActor, ReplicatedMovement, COND_SimulatedOnly );
}
上面的代码表示我们只在模拟客户端进行ReplicatedMovement属性的同步。当然，具体的同步控制条件还有很多。


如果想更自由的控制条件复制，就需要使用COND_Custom，并在当前Actor的PreReplication函数里面使用DOREPLIFETIME_ACTIVE_OVERRIDE，通过最后一个参数控制是否要进行同步。

DOREPLIFETIME_ACTIVE_OVERRIDE(AActor, ReplicatedMovement, bUseReplicatedMovement);
条件复制的基本原理是通过宏展开获取当前该属性的UProperty，然后封装放到参数OutLifetimeProps里面。

#define DOREPLIFETIME(c,v) \
{ \
	static UProperty* sp##v = GetReplicatedProperty(StaticClass(), c::StaticClass(),GET_MEMBER_NAME_CHECKED(c,v)); \
	for ( int32 i = 0; i < sp##v->ArrayDim; i++ )							\
	{																		\
		OutLifetimeProps.AddUnique( FLifetimeProperty( sp##v->RepIndex + i ) );	\
	}																		\
}
在每个ACtor的Replayout初始化的时候会去真正的调用GetLifetimeReplicatedProps并将LifetimeProps标记到对应的要同步的Parent数组里面（所以如果我们不在函数GetLifetimeReplicatedProps里面标记同步属性，这个属性即使标记了replicated也不会同步），同时LifetimeProps会把当前属性是否是条件复制（FRepParentCmd.Condition）放到Parent对应的标记里面。


另一边，在RepState初始化的时候会有一个ConditionMap来记录当前的条件复制情况。ConditionMap就是一个大小为enum ELifetimeCondition长度的bool数组，记录当前的复制条件。


现在，当我们正式进入序列化发送的时候，我们开始执行判断这个属性是否应该发送。判断方式就是找到当前属性的FRepParentCmd.Condition同时查看RepState的ConditionMap是否满足当前的条件。


从上面的堆栈可以看出，如果这时候不满足条件的话，当前的属性就不会写到序列化的bunch里面也就不会发送到当前的Connection里面。



六． RPC执行细节
RepLayOut参照表不止同步的对象有，函数也同样有，RPC的执行同样也是通过属性同步的这个框架。比如我们在代码里面写了一个Client的RPC函数ClientNotifyRespawned，那UHT会给我们生成一个.genenrate.cpp文件，里面会有这个函数的真正的定义如下：

void APlayerController::ClientNotifyRespawned(class APawn* NewPawn, bool IsFirstSpawn)
{
    PlayerController_eventClientNotifyRespawned_Parms Parms;
    Parms.NewPawn=NewPawn;
    Parms.IsFirstSpawn=IsFirstSpawn ? true : false;
    ProcessEvent(FindFunctionChecked(ENGINE_ClientNotifyRespawned),&Parms);
}
而我们在代码里的函数之所以必须要加上_Implementation，就是因为在调用端里面，实际执行的是.genenrate.cpp文件函数，而不是我们自己写的这个。

结合下面的RPC执行堆栈，我们可以看到在Uobject这个对象系统里，我们可以通过反射系统(通过名字在UClass里面查找，里面有一个存储TFunction的map)查找到函数对应的UFuntion结构，同时利用ProcessEvent函数来处理UFuntion。通过识别UFunction里面的标记，可以知道这个函数是不是一个RPC函数，是否需要发送给其他的端。 当我们开始调用CallRemoteFunction的时候，RPC相关的初始化就开始了。NetDiver会进行相关的初始化，并试着获取RPC函数的Replayout，那么问题是函数有属性么？正常来说，函数本身就是一个执行过程，函数名是一个起始的执行地址，他本身是没有内存空间，更不用说存储属性了。不过，在UE4的反射系统里面，函数可以被额外的定义为一个UFunction，从而保存自己相关的数据信息。RPC函数的参数就被保存在UFunction的基类Ustruct的属性链表PropertyLink里面，RepLayOut里面的属性信息就是从这里获取到的。 一旦函数的RepLayOut被创建，也同样会放到NetDiver的RepLayoutMap里面。随后立刻调用FRepLayout::SendPropertiesForRPC将RPC的参数序列化封装与RPC函数一同发送。

RPC中如果有指针参数，当RPC在客户端执行的时候，如果这个指针对应的actor还未在客户端生成，那么这个时候客户端拿到的RPC指针参数就是NULL。我们可以通过设置控制台变量net.DelayUnmappedRPCs 1允许客户端等到这个对象生成的时候再去执行，但是仅限于可靠的RPC。



图6-1 RPC函数的RepLayOut初始化堆栈图
关于RPC的发送，有一个地方需要特别注意一下，就是UIpNetDriver::ProcessRemoteFunction函数。这个函数处理了RPC的多播事件，如果一个多播标记为Reliable，那么他默认会给所有的客户端执行该多播事件，如果其标记的是unreliable，他就会检测执行该RPC的Actor与各个客户端的网络相关性，相关才会执行。简单总结来说，就是一般情况下多播RPC并不一定在所有的客户端都执行，他应该只在同步了触发这个RPC的Actor的端上执行。

//UIpNetDriver::ProcessRemoteFunction
//这里很详细的阐述UE这么做的原因
简单概括了RPC的发送，这里再说一下RPC的接收。当客户端收到上面的RPC发来的数据后，他需要一步一步的解析。首先，他会执行ReceivePropertiesForRPC来接收解析RPC函数传来的参数并做一些判断确定是否符合执行条件，如果符合就会通过ProcessEvent去处理传递过来的属性信息，找到对应的函数地址（或者说函数指针）等，最后调用该RPC函数。 这里的ReplayOut里面的Parents负责记录当前Function的属性信息以及属性位置，在网络同步的过程中，客户端与服务器保存一个相同的ReplayOut，客户端才能在反序列化的时候通过OffSet位置信息正确的解析出服务器传来的RPC函数的N个参数。


图6-2 接收RPC函数的传递的参数堆栈图

图6-3 客户端执行RPC函数堆栈图
最后客户端是怎样调用到带_Implementation的函数呢？这里又需要用到反射的机制。我们看到UHT其实会给函数生成一个.genenrate.h文件，这个文件就有下面这样的宏代码，把宏展开的话其实就是一个标准的C++文件，我们通过函数指针最后找到的就是这个宏里面标记的函数，进而执行我们自己定义的_Implementation函数。

virtual void ClientNotifyRespawned_Implementation(class APawn* NewPawn, bool IsFirstSpawn);\ 
DECLARE_FUNCTION(execClientNotifyRespawned) \
{ \
    P_GET_OBJECT(APawn,NewPawn); \
    P_GET_UBOOL(IsFirstSpawn); \
    P_FINISH; \
    this->ClientNotifyRespawned_Implementation(NewPawn,IsFirstSpawn); \
} \
RPC的数据包相比属性同步不同，是调用的时候立刻产生的Bunch并放到Sendbuffer里面的，按照UE4一帧的执行顺序（收包-Tick-发包），一般RPC的数据要比属性同步要早放到buffer里面，所以经常出现RPC与属性同步顺序不对导致的同步问题。

七． 可靠数据传输
UE4默认收发包都在主线程处理，收包可以通过控制CVarNetIpNetDriverUseReceiveThread来开启线程单独处理。


发包堆栈

收包堆栈
1.数据包格式
这里再次拿出来一般网络数据包的格式，可以看到虚幻里面的网络包是精确到bit的，这些信息都可以通过FBitWriter与FBitReader去读与写。


网络包分为Ack与Bunch两种

对于ActorChannel，Bunch分为属性Bunch与RPC Bunch

平时看函数堆栈的时候我们可能看到Bunch、RawBunch、Packet、RawPacket等。所谓的Bunch就是上面图所展示的（ActorChannel发送数据的Bunch分为属性Bunch与RPC Bunch），Bunch如果太大就会被拆分成很多个小的Bunch，一旦拆分成小的bunch那么这个bunch就不是一个完整的bunch（就可以叫做一个Rawbunch，具体逻辑在UChannel::SendBunchInner里面），这些bunch可以都被塞到一个Sendbuffer里面，如果这样直接发出去，就是一个Packet。每一个Sendbuffer发出前还可能会被PacketHandler处理，处理之后就是RawPacket。按照这样的理解，你就能看懂下面的堆栈了。


客户端与服务器通过ControlChannel建立连接的某次通信堆栈
另外，由于平时我们的发包都是按照最小单位Byte来发送的，UE4里面又精确到bit。所以会在Sendbuffer最后面添加1bit的结束标志位，另一端在收到包的时候就可以先找到最后一个为1的bit，把后面的0删除，前面剩下的就是原始的网络包。

2.PacketHandler
PacketHandler是用来对原始数据包（Packet）进行处理的一个“工具”，里面可以自由的添加组件来对原始数据包进行多层处理，目前引擎内置的组件有握手组件StatelessConnectHandlerComponent、各种加密组件FEncryptionComponent、可靠数据传输组件ReliabilityHandlerComponent等。由于组件的不确定性，所以网络的消息包头也是不确定的。比如加密组件可能会对一个Packet进行加密，然后在前面添加一个2bit的头部以及1bit的结束标志位，也因此各个组件应该固定的顺序处理packet。默认情况下回一直存在一个StatelessConnectHandlerComponent组件。

由于PacketHandle组件可能对原有的packet进行加密从而导致位发生变化，所以PacketHandle组件本身也会对处理过的数据后添加一个bit的结束标志位。


3.Bunch的发送时机
每次只要执行sendrawbunch（可能在netdrivertick里worldtick里面的代理tick，也可能在worldtick里tickgroup里面）就会设置TimeSensitive为true，就会触发flushnet，所以说只要每帧有数据就会发送。只要里面有sendbuffer或者到时间了就会触发lowlevelsend，调用socket的发送


4.可靠数据传输的实现
可靠数据传输的基本原理就是接收方对每一个包都要做Ack回应，如果接收方没收到Ack，那么就要进行重传。

UE4底层默认是主动重传，只要没有按顺序收到bunch就会重传。每个包有一个OutPacketId（记录在Connection里面），一个packet可能包括N个Bunch，每个bunch也会记录当前所在的OutPacketId。

简单来说，发送端会记录一个已经传送成功的序号（已经收到的Ack.OutAckPacketId）假如发送端发了10个包（1-10），接收端收到了1那么会回复一个ack，里面是OutAckPacketId 1。然后发生丢包，接收端收到了序号5，那么就会回复一个ack5，这时候发送端会更新当前的OutAckPacketId并重传序号2-4所有的packet（保存在connection的缓存里面）。所以，可以保证所有的包到上层都是严格有序的。

if( AckPacketId>OutAckPacketId )
{
	for (int32 NakPacketId = OutAckPacketId + 1; NakPacketId<AckPacketId; NakPacketId++, OutPacketsLost++, OutTotalPacketsLost++, Driver->OutTotalPacketsLost++)
	{
		UE_LOG(LogNetTraffic, Verbose, TEXT("   Received virtual nak %i (%.1f)"), NakPacketId, (Reader.GetPosBits()-StartPos)/8.f );
		ReceivedNak( NakPacketId );
	}
	OutAckPacketId = AckPacketId;
}
除了Bunch里面的OutPacketId外，每个channel里面的还有一套ChSequenceID，记录了当前通道内可靠数据包的序号，每次发送加1。每个Connection里面会有N个Channel，每个Channel发出去的可靠数据包的数量会以Connection->OutReliable数组的形式存储，而真正发出去与接收到的数据包会缓存在OutRec链表与InRec链表链表里面，每次发送一个数据包就会添加到OutRec里面并设置其Ack状态为0，收到一个Ack的时候就会遍历当前Channel的OutRec链表，将对应Ack设为1，调用Channel::ReceivedAcks()并清空OutRec中被确认过的前面的所有缓存。OutRec并没有限制大小，所以理论上这里会出现内存溢出的情况，不过在逻辑上层还有一些自己的处理机制，比如Channel可以设置阈值，超过阈值就退化成停等协议，具体内容请参考UChannel::SendBunchInner。

每个通过有一个ChIndex，connection在接收Bunch的时候可以通过这个Index找到对应的Channel再下发消息。

5.属性的可靠传输
首先要确认一点，属性同步本身并不是可靠的，也就是他的属性bunch所在的packet如果丢失并不会将这个packet重新发送。只有Actor在第一次同步的时候才会设置合格属性bunch为Reliable

// Send initial stuff.
//UActorChannel::ReplicateActor
if( OpenPacketId.First != INDEX_NONE && !Connection->bResendAllDataSinceOpen )
{       //第一次收到spawn的ack会把后面不可靠的属性也重新同步一遍
	if( !SpawnAcked && OpenAcked )
	{
		// After receiving ack to the spawn, force refresh of all subsequent unreliable packets, which could
		// have been lost due to ordering problems. Note: We could avoid this by doing it in FActorChannel::ReceivedAck,
		// and avoid dirtying properties whose acks were received *after* the spawn-ack (tricky ordering issues though).
		SpawnAck
ed = 1;
		for (auto RepComp = ReplicationMap.CreateIterator(); RepComp; ++RepComp)
		{
			RepComp.Value()->ForceRefreshUnreliableProperties();
		}
	}
}
else
{       //第一次同步是可靠的
	Bunch.bClose = Actor->bNetTemporary;
	Bunch.bReliable = true; // Net temporary sends need to be reliable as well to force them to retry
}
那么属性是怎样做到可靠的呢？我发现即使接收方即使接收到的Packet里面的bunch不是reliable的，在通道不关闭、不是拆分的Bunch等情况下还是会回复一个Ack的，所以发送端可以接收到一个Ack从而知道当前的属性是否被另一端接收到。

当发生丢包或者乱序的时候，发送方会接收到乱序的ACK进而RepState会记录当前Nak的数量，并对当前的同步发送历史信息进行标记

void FRepLayout::ReceivedNak( FRepState * RepState, int32 NakPacketId ) const
{
	if ( RepState == NULL )
	{
		return;		// I'm not 100% certain why this happens, the only think I can think of is this is a bNetTemporary?
	}

	for ( int32 i = RepState->HistoryStart; i < RepState->HistoryEnd; i++ )
	{
		const int32 HistoryIndex = i % FRepState::MAX_CHANGE_HISTORY;

		FRepChangedHistory & HistoryItem = RepState->ChangeHistory[ HistoryIndex ];

		if ( !HistoryItem.Resend && HistoryItem.OutPacketIdRange.InRange( NakPacketId ) )
		{
			check( HistoryItem.Changed.Num() > 0 );
			HistoryItem.Resend = true;
			RepState->NumNaks++;
		}
	}
}


当下一帧要进行属性同步的时候，就会把之前的历史记录合并到最新的历史记录里面，然后一起发出去，也就是说丢失属性和新的属性会一起发送，这样达到了不用重发丢失的bunch还能保证属性可靠的效果了。这一块的逻辑主要在FRepLayout::ReplicateProperties里面，关于属性变化的历史记录可以参考上面第五章第4小节。

八． ReplicationGraph
ReplicationGraph是Epci官方针对堡垒之夜网络同步优化而加入的新的插件系统，可以大大减少Actor的同步与遍历，比较适合对大世界场景进行网络同步优化。这一块已经有文章写的比较清晰了，所以我只是简单的列举其优化点与基本原理。

通常服务器在同步Actor到各个连接的时候，会遍历场景中所有标记Replicated的Actor，但是实际上与玩家距离比较远的根本就不需要遍历，更不用说同步，所以ReplicationGraph加入了GridSpatialization2D节点系统，把N*N的格子，并把Actor放到当前所有与他有关的格子里，这样一个玩家靠近他的时候就从当前子集所在的格子里面找一下有没有那个Actor就可以了（只遍历所有在这个格子里的Actor即可）


当然，作为一个系统不仅仅是提供这样一种功能和优化，其里面还内置了很多节点用于不同的同步需求（比如可以对不同的Connection进行某一个Actor的特定属性进行共享序列化），你也可以自定义一个节点专门处理某些需要特殊处理的Actor，严格控制它的同步时机。这一块可以参考官方的Shootergame项目。

注：ReplicationGraph是一个纯C++插件系统，使用的话需要修改配置文件DefaultEngine.ini里面的内容。
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》RootMotion详解【原理分析】</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/74554876
本篇文章适合有一定经验的虚幻/游戏开发者，不过为了照顾部分刚接触虚幻引擎的萌新（大佬），也会对一些引擎中的基本概念做出讲解。

RootMotion概述
RootMotion，根骨格位移，属于移动组与动画系统相结合的一个部分，表示角色的整体运动（包括物理）是由动画来驱动的。

一般来说，在大部分游戏的应用里面，玩家的移动与动画是分开的。移动系统只负责处理玩家的位置与旋转，动画系统只做对应的动画表现，只要移动的速度合适就可以与动画做到完美的匹配，也就是说，动画播放的位置（即Mesh的位置）是由角色移动来驱动的（UE4里面，动画是由胶囊体的位置数据来驱动）。这样的好处之一就是解耦，移动与动画之间不需要紧密的联合，只关注自己的内容即可。

动图封面
没有移动数据配合的动画
但是，有一些复杂的移动是很难模拟的，比如UE4官方给出的例子：一个举着锤子的人向前挥舞，一开始速度比较慢，中间挥舞时由于角色控制不住速度会很快，到最后锤子落地时，速度又变的很慢，角色会踉跄的走两步。


实际上，无论使用哪种方法，我们都很难找到一种可以处理所有类似表现的通用模拟方案。那么我们不模拟可以么？就让玩家动画播放到很远的位置再移动胶囊体呢？也不行，因为这样的话，如果中间有墙面，角色的动画就会因为没有碰撞而穿模过去。最理想的方法就是就是交给美术去做一个带有位移的动画，玩家的位置完全交给动画去处理，不同的动画可以有不同的移动表现。（还有一种通过曲线去处理的方法，不过两者其实是类似的）


因此，我们需要有RootMotion来应对部分复杂的动画，可以让角色的移动位置与动画完美匹配。

动图封面
3A游戏里面几乎都会用到Rootmotion
RootMotion操作与测试
概念介绍完后，不妨动手测试一下。我们可以直接下载官方的ContentExample并打开Animation Level的案例1.9进行测试。可以看到绿色Character开启了Rootmotion，胶囊体会一直跟随动画移动，而红色Character没有开启Rootmotion所以胶囊体没有发生位移，动画由于没有任何碰撞穿了过去。


打开其角色蓝图与动画蓝图，简单看一下蓝图上的处理逻辑。

1.通过事件先设置其MovementMode为Walk，然后找到其AnimInstance转换为动画蓝图并执行事先定义好的事件——PlayRootMotionExample


2.PlayRootMotionExample位于动画蓝图，只是执行了一个Montage的播放。该Montage是由一个带位移的动画合成的，动画由动画设计师在Maya里面制作并将导出的.fbx文件导入到UE4里面。同时，需要让Montage的slot插槽设置为FullBody的并在动画图表里面播放该slot



3.只导入动画资源是不够的，需要做一些配置。首先，角色的根骨格应该在原点且无旋转的。其次，可以看到在动画序列（资源）蓝图的左边有一个RootMotion的选项栏，要勾选上EnableRootmotion。最后，在动画蓝图的右边AnimPreviewEditor（动画预览编辑器）的下面有一个RootMotionMode，选择RootMotionFromMontagesOnly。

RootMotionMode有四个选项，含义如下：

NoRootMotionExtraction 表示不会处理其动画内含的Transform数据
IgnoreRootMotion 表示会解压出来Transform数据但是不应用
RootMotionFromEverything 表示解析所有含有Rootmotion动画资源都可以去解析其Transform数据并参与到整个动画系统的权重计算
RootMotionFromMontagesOnly 表示只取蒙太奇的Transform数据作为Rootmotion的计算



另外，值得注意的是，该系统是支持网络同步的。当我们开启多人模式的时候，表现依旧流畅，这也是这篇文章的分析重点之一。

理论上AnimSequence, Blendspace, AnimMontage都可以支持网络同步，但是这样在网络环境下会有几个问题，比如提高动画同步的复杂度、影响游戏性能、提高预测难度、容易破坏动画表现等，所以一般我们要关闭Montage以外的同步，将Root Motion Mode设置为Root Motion From Montages Only。如果开启了动画资源的Rootmotion但是不设置RootMotionMode会有卡顿的表现。

实际上，虽然Rootmotion支持Montages的网络同步，但是由于其预测难度远大于普通移动，在网络环境不稳定的情况下，表现是相当糟糕的。因此，在多人游戏的时候，要适度的使用Rootmotion。

至于同步的具体细节以及为什么会这样，后面会有详细的分析。

（Youtube上有很多关于Rootmotion的教学视频，这里给出一个从零开始搭建并根据玩家输入控制的案例）

UE4中RootMotion相关概念理解
前面从概念和使用上比较详细的做了讲解，下面我们开始深入源码。首先，不妨先思考一下Rootmotion的实现，其基本思路还是挺简单的，就是移动组件每帧不断的去读取动画数据里面的移动Transform，然后应用到实际的胶囊体上面。当然，具体实现起来可能与我们所想的有所差异，这里并不是直接获取坐标并设置。而且，涉及到的数据与类非常多，逻辑也比较复杂，我们需要同时理解动画系统以及移动组件的实现原理。

这里先给出涉及到的相关概念：

【动画系统相关】


USkeletalMeshComponent：对应一个包含骨骼动画的Mesh模型，可以以组件的形式Attach到一个玩家身上
UAnimInstance：动画实例，其实就是C++版本的动画蓝图，每个SkeletalMeshComponent组件都会有一个UAnimInstance Class类型的配置项以及一个UAnimInstance类型的指针，我们动画的大部分逻辑都是在这里处理的。
FAnimInstanceProxy：动画实例代理，属于多线程优化动画系统的核心对象。他可以分担动画蓝图的更新工作，将部分动画蓝图的任务分配到其他线程去做。
FAnimMontageInstance：Montage动画实例，播放时会在动画实例UAnimInstance里面存储一个FAnimMontageInstance数组用于记录该实例的所有Montage。

另存一个Map记录当前激活的Montage


另外，还有一个特殊的FAnimMontageInstance来记录当前正常播放含有RootMotion的那个动画


FRootMotionMovementParams：用于累积计算Rootmotion的自定义结构体，可以临时存储当前帧的RootmotionTransform数据。FAnimMontageInstance保存一个用于临时缓存Rootmotion数据的成员变量

FRootMotionExtractionStep：由于一个蒙太奇动画里面可能有多个动画序列组成，所以在提取RootMotion数据的时候需要记录当前所在的片段以及具体位置，FRootMotionExtractionStep就是将这些数据封装并整合成一个结构体
FSlotAnimationTrack：组成当前Montage插槽片段的集合，下图里面有两个FSlotAnimationTrack。

FAnimTrack：一个FAnimTrack表示一个动画轨道，每个轨道可以由一个或多个Animsequence片段构成，下图的动画轨道就由三个动画序列构成

FRepRootMotionMontage: Character身上用于同步RootMotion相关信息的属性，包括UAnimMontage、执行位置、旋转、速度等
FSimulatedRootMotionReplicatedMove：在Character上以数组的形式存储，记录最近一段时间每帧的Rootmotion信息，用于服务器到Simulated客户端的数据同步
以下几个属于非动画的Rootmotion，我们一般说的Rootmotion是指基于动画的rootmotion（即美术将位移写在动画资源里面），但是这样迭代比较慢，有一些定向移动的效果也无法实现，所以诞生了RootmotionSource。本篇文章不会使用到：

FRootMotionSource：广义上的Rootmotion，本质上没有具体的动画数据，通过模拟力产生每帧的Transform信息。比如说玩家受击产生位移，如果是使用普通的受力属于物理影响，同步效果比较差。在移动组件里面集成FRootMotionSource，就可以使用类似Rootmotion的方式非常流畅处理角色的移动，同时还可以兼顾网络同步。
FRootMotionSourceGroup： containing active root motion sources being applied to movement ，包含了一组RootmotionSource的结构体。同一时刻可能有多个不同的力（或者说RootmotionSource）作用于玩家，移动组件可以根据权重优先级等混合出一个合理的移动位置。
FRootMotionServerToLocalIDMapping:用于同步匹配客户端和服务器上面FRootMotionSourceGroup里面不同的RootmotionSource。


【移动组件相关】

UE4里面移动的能力是被封装到一个组件里面的（组件式设计，大部分功能都被封装到不同的组件里），与真正的玩家角色分离，不同的角色可以配置不同的组件并设置各自的参数从而实现不同的移动效果

ACharacter：玩家角色，可以以一个人物角色的表现存在于游戏世界中，默认包含了一个骨骼Mesh组件、一个角色移动组件、一个胶囊体组件、一个箭头指示组件，有基本的移动、物理碰撞、模型显示的功能。只有使用ACharacter，我们才能完整的使用Rootmotion所有的相关功能

UMovementComponent：移动组件的基类，只包含基本的移动位置处理
UCharacterMovementComponent：提供一套完整的角色移动的解决方案，包括行走、游泳、飞行等状态，网络同步，插值优化，Rootmotion等
关于移动组件，可以到我的另一篇文章里《Exploring in UE4》移动组件详解[原理分析]去查看，里面详细的描述了各种移动细节、同步流程、插值优化等

Rootmotion单机执行流程与原理
动画数据初始化：

【对于动画蓝图里面的动画数据】

1.绑定动画蓝图的Character进入场景时就已经开始了各种动画数据相关的初始化（UAnimInstance::InitializeAnimation），随后通过UpdateAnimation不断的更新动画蓝图里面的逻辑，同时把一部分逻辑交给了FAnimInstanceProxy处理。


【对于非动画蓝图里面的Montage数据】

2.一般是玩家手动触发Montage的播放，通过USkeletalMeshComponent找到对应的AnimInstance并执行UAnimInstance::Montage_Play

3.创建一个FAnimMontageInstance并进行相关的初始化，开始真正的播放蒙太奇

4.判断蒙太奇是否带有Rootmontion，是的话将赋值给RootMotionMontageInstance，用于后续的ACharacter::IsPlayingNetworkedRootMotionMontage判断


5.Montage初始化之后就会在后续每帧执行的AnimInstance::UpdateAnimation里面参与计算了。在通常情况下，只要我们的动画的更新方式不选择EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered（有四种），Montage都是会参与更新的，更新逻辑在UAnimInstance::UpdateMontage里面




移动组件PerformMovement ：

Prepare RootMotion阶段

1.移动组件在TickComponent的PerformMovement里，先判断其是否处于RootMotion的状态。满足下面两个条件之一即可先做一些Rootmotion相关数据的处理和清理：

a.CurrentRootMotion里面是否有ActiveRootMotionSources（即前面提到的非常规性的Rootmotion）
b.通过当前角色身上的Mesh组件函数USkeletalMeshComponent::IsPlayingRootMotion判断其是否处于Rootmotion状态

2.再次进行判断来确保是否要更新动画系统。如果上面的b条件再次成立，就开始做准备工作了，即更新动画执行TickCharacterPose（TickPose默认在Mesh组件里面会每帧都去调用的，这里由于其Tick时机与Mesh组件不同所以需要强制执行一次），这里面会调用UAnimInstance::UpdateAnimation更新动画，并在MontageInstance->Advance(DeltaSeconds, RootMotionParams, bUsingBlendedRootMotion)将当前Montage位移信息更新到AnimInstance的成员变量ExtractedRootmotion里面。



那么这里可能会有一个疑问，Montage动画里面的Transform数据具体是怎么解析出来的呢？答案都在UAnimMontage::ExtractRootMotionFromTrackRange这个函数里面。我们需要将这一帧动画播放前的播放位置以及当前Montage执行到的位置作为参数传递进去，Montage就会从当前的轨道SlotTrack里面获取到所有AnimSequence片段（也就是下面堆栈图中的FAnimSegment），判断当前Montage处于哪一个AnimSequence片段并解析出对应的FRootMotionExtractionStep（该对象其实只是封装了对应的AnimSequence以及这一帧播放的起始位置）。

最后，根据对应的AnimSequence以及当前播放的起始位置计算出RootMotion的DeltaTransform，需要注意的是这里面得到的是一个位移而不是一个位置。（通过UAnimSequence::GetBoneTransform获取）
3.假如我们现在已经将Montage的信息提取到ExtractedRootmotion里面，但是动画蓝图里面的AnimSequence、BlendSpace等动画数据怎么一起参与计算呢？在概念理解里面我们提到了多线程优化的核心类FAnimInstanceProxy，默认情况下，动画蓝图里面的大部分更新逻辑都被放到了FAnimInstanceProxy里面，无论是否是多线程，我们都需要通过FAnimInstanceProxy::TickAssetPlayerInstances去处理相关逻辑，并在这里根据权重去将所有的动画资源的Rootmotion数据提取到ExtractedRootMotion里面。

如果RootMotionMode为RootMotionFromEverything，那么我们在主线程Tick的时候就会立刻去更新TickAssetPlayerInstances，这样是为了能及时获取到每一帧的Rootmotion信息。


主线程更新
如果RootMotionMode是其他模式，那么TickAssetPlayerInstances就会被放到其他线程里面取执行。


其他线程更新
同理，如果RootMotionMode为RootMotionFromEverything，在Proxy更新完毕后，我们需要及时地根据权重将所有参与计算的资源数据提取到ExtractedRootMotion里面。


如果RootmotionMode不为RootMotionFromEverything，那么我们可以在FParallelAnimationCompletionTask里面去更新Rootmotion相关数据（不过下面的堆栈仍然是在主线程执行的）


应用阶段：

1.TickPose之后，如果角色处于IsPlayingRootMotion状态就会去执行ConsumeRootMotion消耗掉Animinstance在前面阶段产生的ExtractedRootmotion，其实也就是将前面得到的ExtractedRootmotion数据复制到新的变量RootMotion里面并清空ExtractedRootmotion

2.得到的新的Rootmotion数据会先根据ACharacter的AnimRootMotionTranslationScale进行缩放调整，同时把其相关数据拷贝到移动组件的成员变量 RootMotionParams 里面


3.对RootMotionParams 进行局部到世界的坐标转换

4.执行移动模拟，也就是将前面得到的Transform应用到移动组件里面。这里会先根据当前的Rootmotion的DeltaTransform以及deltaTime算出一个速度AnimRootMotionVelocity进行模拟，具体逻辑在StartNewPhysics里（包括PhysWalking、Flying等），这里面不同的移动状态都会判断Rootmotion进而处理速度。注意：这一步并不会更新其Rotation


5.模拟结束，读取RootMotionParams的Transform来更新Rotation

6.清除移动组件的成员RootMotionParams里面的数据




有一点需要强调一下，Rootmotion是逐渐积累的，也就是说每次我们得到的Transform都是当前Tick时间内其移动的位移，而不是指一个特定的坐标。Accumulate函数就是表示将当前传入的DeltaTransform赋值到我们当前记录的数据上。
另外，上面还提到了一个Character身上的配置AnimRootMotionTranslationScale。由于动画师制作的动画长度是固定的，而游戏里面的需求是变化的，我们能保证每次角色移动的距离就是动画师设计的那样么？不能，比如玩家翻越一个障碍，障碍的大小不可能是严格一致的，所以我们需要一个参数去做适配调整，这个参数就AnimRootMotionTranslationScale，可以通过函数SetAnimRootMotionTranslationScale设置。
RootMotion的同步

目前的引擎中，Rootmotion只支持Montage的同步，这里分析的也只是基于Montage的同步流程。同步分为Simulated客户端以及Autonomous客户端两种情况，也就是说你显示屏上其他的玩家与你本地控制的玩家执行Rootmotion的同步流程是有差异的，这与移动组件的实现密切相关。如果对Simulated或者Autonomous不懂，可以参考《Exploring in UE4》关于网络同步的理解与思考[概念理解]。


Simulated客户端同步

（没有收到服务器同步数据时与服务器的执行逻辑大致相同，只不过在SimulateTick里触发）

动画 Montage初始化：（同步只支持Montage）

1.服务器本地先触发执行MontagePlay并赋值给RootMotionMontageInstance

2.Simulated客户端在服务器触发MontagePlay后，通过属性回调随后触发MontagePlay

注意：这里第二步是需要开发者自己处理的，一般来说应该是服务器执行后修改某个属性，然后这个属性的回调函数触发客户端去执行MontagePlay，二者执行有一个短暂的网络延迟。

移动组件 SimulatedTick：

1.移动组件执行Tick ，UCharacterMovementComponent::SimulatedTick

2.如果当前玩家的Mesh对应的AnimScriptInstance→RootMotionMode为RootMotionFromMontagesOnly（也就是说其他三种ERootMotionMode不支持网络同步），触发Rootmotion在Simulated客户端的同步操作


3.TickCharacterPose，从动画当前位置里面解析出DeltaTransform，用AnimInstance上的ExtractedRootMotion提取出来。具体细节可以参考上面的单机流程


4.根据CharacterOwner->GetAnimRootMotionTranslationScale()设置RootMotion的Scale并提取到移动组件的RootMotionParams里面

5.调用SimulateRootMotion转换到世界坐标，计算Rootmotion的速度并开始调用StartNewPhysics进行模拟，与单机版本不同，其模拟流程都在函数SimulateRootMotion里面处理。这里有一点需要特别注意，由于Simulated客户端通过网络同步，可能因为网络波动而卡顿，所以这该函数只会先更新胶囊体的位置（bEnableScopedMovementUpdates为true即可），而不更新Mesh的位置，Mesh需要通过本地的Tick去平滑，其逻辑在下面会进一步描述。

6.模拟完毕后，如果Rotation不为默认值FQuat::Identity就会通过MoveUpdatedComponent修改，清除临时提取的RootMotionParams的相关数据

上面提到的是客户端模拟的流程，不过既然是同步，当然需要客户端与服务器交互了

注意：玩家身上有一个FRepRootMotionMontage RepRootMotion记录了每帧服务器的Rootmotion的运行信息，包括当前帧的坐标、旋转、Montage、速度、执行的位置等。这个属性是同步的（而且只在播放Rootmotion的时候同步），在服务器播放Rootmotion的时候每帧都会通过ACharacter::PreReplication处理这些数据并发送给Simulated客户端
数组TArray<FSimulatedRootMotionReplicatedMove> RootMotionRepMoves;存储了服务器发来中的所有Rootmotion的数据，前面提到的RepRootMotion在客户端的回调函数里会被提取数据并添加到RootMotionRepMoves数组里面。

7.客户端模拟移动后会开始根据服务器的Rootmotion信息开始校验，执行函数ACharacter::SimulatedRootMotionPositionFixup。这里会先判断客户端是否要用这个RootMotionRepMoves数组里面的数据（条件：小于0.5秒，在同一个Section片段，非循环Montage，服务器落后于客户端的位置最接近客户端的那个）


8.如果寻找到满足条件的数据RepRootMotion，就会先通过ACharacter::RestoreReplicatedMove按照服务器传递的数据修改本地角色的坐标与旋转。随后，按照当前服务器的位置以及客户端的位置执行ExtractRootMotionFromTrackRange实现Rootmotion的回滚，这里只是为了得到一个回滚的结果。

9.最后，根据deltaposition、playrate算出一个deltatime，再根据回滚结果LocalRootMotionTransform进行一次本地模拟SimulateRootMotion。

10.模拟之后调用SmoothCorrection进行平滑处理。前面提到SimulateRootMotion只会更新胶囊体位置而不更新Mesh的位置，就是为了在这里进行平滑。平滑的逻辑大概就是客户端记录一个ClientData数据去记录当前的Mesh偏移以及服务器的时间戳，在随后的每帧的Tick里面，不断的更新Offset偏移，让其逐渐为0，当偏移为0的时候Mesh就和胶囊体完全重合完成了平滑。具体的逻辑可以参考我的另一篇文章《Exploring in UE4》移动组件详解[原理分析]。


Autonomous客户端的同步流程

Montage初始化：

1.客户端本地先执行Montage播放，通过RPC通知服务器播放

2.服务器收到RPC触发MontagePlay并赋值给RootMotionMontageInstance

（当然，这里也可以采用类似simulated客户端的方式，先在服务器播放，通过属性回调触发Autonomous客户端进行播放）



移动组件 ReplicateMoveToServer（由于逻辑重复，这里会对一些步骤做简化）：

1.类似上面的simulated客户端执行TickComponent，不过这里每帧触发的函数不是SimulatedTick而是ReplicateMoveToServer。随后执行PerformMovement里面提取Rootmotion的信息（执行TickCharacterPose）


2.根据deltatime与DeltaTransform计算速度，调用StartNewPhysics进行Rootmotion移动模拟

3.更新Rotation，清除临时提取的RootMotionParams的相关数据。将本次移动的相关数据存放到FSavedMove_Character里面，记录这次移动并存储到SavedMoves数组里面（用于回滚等）

4.执行CallServerMove，将本地计算的数据发送到服务器，调用RPC函数ServerMove

（这里如果遇到了PendingMove执行优化移动的情况，则需要执行特殊的RPC ServerMoveDualHybridRootMotion）

服务器处理：

5.服务器根据客户端信息执行MoveAutonomous重新模拟计算，并根据结果判断客户端移动是否合法。

6.随后，在服务器执行UNetDriver::ServerReplicateActors的同步时，发送ACK（ClientAckGoodMove）或者Adjust（SendClientAdjustment）。如果这时候服务器正在播放Montage且发现客户端数据有问题，就会执行ClientAdjustRootMotionSourcePosition进行纠正。否则，就会执行正常的纠正逻辑。


7.客户端如果收到ClientAdjustRootMotionSourcePosition信息，首先会根据服务器传递来坐标等信息先更新移动组件的数据（执行ClientAdjustPosition），随后根据服务器传递的Montage Position来直接设置本地Montage动画的Position。

Autonomous客户端的同步流程其实也很复杂，建议先看一下官方文档或者我前面提到的文章来做一个大体的理解。


梳理上面的同步逻辑，其实我们发现RootMotion本质上走的还是移动组件的处理流程，只不过其移动数据是从动画里面提取的。而且很明显的可以看出，Rootmotion只支持Montage的同步，其他的模式根本走不进这套流程（IsPlayingNetworkedRootMotionMontage），其他模式也不会从动画蓝图Proxy里面提取相关的数据（FAnimInstanceProxy::TickAssetPlayerInstances）。

前面我们提到，之所以这么做根本原因是动画系统（或者说动画状态机）的同步是复杂而困难的，目前虚幻引擎通用的动画同步方法是客户端与服务器各自维护一个状态机以及几个同步的属性值，然后通过这些属性的判断来同步动画，这里的动画状态机并没有同步。一旦动画系统复杂起来，各个状态的间的切换与转变都会变得极为复杂，由于网络环境的不稳定，状态机的同步需要非常严密的设计与处理（当然，这也并不是说做不了），最好把每一帧的状态与触发事件都同步过去，再进一步做更多额外的校验工作。所以，我们看到很多游戏的动画除了基本的状态外，其他很多都是通过Montage来同步的，Montage之间可以打断而且独立，所以同步起来相对容易。

另外，因为Rootmotion本质上就是为了提高表现效果才使用的方案，单机模拟都比较困难，对于还需要预测的网络同步就更困难了，或者说除非是常规的线性运动的Rootmotion，其他的不规则的运动几乎无法预测。而如果不预测，我们就很难应对网络抖动，一旦网络一卡整个表现就不再流畅。所以，网络环境不好的情况下，Rootmotion的表现是相当差的。
</code></pre>
</details>

<details>
<summary>使用虚幻引擎4年，我想再谈谈他的网络架构【经验总结】</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/105040792
这是【所有Unreal网游开发者】都应该看的一篇技术文章。
WeChat：使用虚幻引擎四年，我想再谈谈他的网络架构
​mp.weixin.qq.com/s?__biz=MzkzNTIxMjMyNg==&mid=2247491564&idx=1&sn=cc823e3c096e74f22e8f0e8137794e13&chksm=c2b03ba5f5c7b2b33c8c902ba7c297062bdaf56c5719e82d06b6adbe7fb9260c6283efd241b5&token=1087467425&lang=zh_CN#rd
我从16年开始接触unreal，到如今已经4年了。最近看了不少关于网络同步的论文和书籍（详见：细谈网络同步在游戏历史中的发展变化（上）），总算是理解了Doom和Quake这种古董级游戏的发展历史，对其网络架构也有了更深一层的认识。这次想根据自己的工作和学习经验，以一个全局的视角来重新回顾一下虚幻的网络模块，并总结一些我们常见的问题，相信对UE同步细节模糊不清的你看完后一定会醍醐灌顶。使用虚幻引擎4年，我想再谈谈他的网络架构我从16年开始接触unreal，到如今已经4年了。最近看了不少关于网络同步的论文和书籍（详见：细谈网络同步在游戏历史中的发展变化（上）），总算是理解了Doom和Quake这种古董级游戏的发展历史，对其网络架构也有了更深一层的认识。这次想根据自己的工作和学习经验，以一个全局的视角来重新回顾一下虚幻的网络模块，并总结一些我们常见的问题，相信对UE同步细节模糊不清的你看完后一定会醍醐灌顶。

开始前，我先给初学者一个建议。如果你打算看UE4的同步源码，最好先大致阅读一遍这本书——《网络多人游戏架构与编程》，里面基本涵盖了UE4同步框架的大部分内容，可以让你少走不少弯路。


下面进入正题：
网络同步，就是使各个客户端上的角色表现保持一致，属于游戏引擎的高级功能，所以一般我们都将其归于Gameplay模块当中。不过具体的实现方案其实会深刻影响到底层的网络架构（甚至是整个游戏架构），我们既要决定通过哪种网络协议来完成，又要决定游戏各个模块的循环执行顺序，其实已经不单单是“Gameplay”层面的东西了。

虚幻引擎属于标准的CS架构（经过无数次改版的），内置状态同步功能，其同步频率与游戏的帧率相同，属于变长步更新。由于帧率完全受CPU、GPU性能的影响，所以网络同步的频率与整个项目的性能息息相关。不过，有一点我们要认识到，unreal已经是尽可能的按照自己最快的速度进行数据的发送与接收了，只要我们做好各方面的性能优化即可。

一、RPC与属性同步
在Unreal里面，同步有两种手段，即RPC与属性同步（很多服务器引擎都是如此）。与其说RPC是同步手段，不如说他是一种传输数据的方式，好处就是可以直接通过类的函数形式书写，方便理解。同时不需要你直接写Socket，也不需要你处理封包和拆包。在计算机网络的概念里面，RPC叫做“远程过程调用”，本质上就是一种传递数据的手段，而其实现方式既可以是应用层的Http，也可以是传输层的TCP/UDP。在虚幻里面，由于很多游戏的同步（比如FPS）对网络延迟要求比较苛刻，所以我们放弃了需要三次握手的TCP而改用UDP（更不可能考虑HTTP了）。RPC既可以标记为可靠，也可以标记为不可靠。可靠的RPC最终一定会到达目标终端，但不可靠的RPC除了在网络拥挤的环境下丢失，也可能在引擎限流的情况下被提前拦住。RPC本身并不是一个可以持续存在的对象，我们只能通过RPC参数“一次性”的将数据从一端发送到另一端，所以每个RPC调用只能“只执行一次”（可以理解为生命周期只有瞬间的）。如果RPC消息从网络中丢失，那么他就会永久的丢失（不可靠的RPC），所以并不适合游戏世界各种对象的状态恢复，必须要结合可以保持对象状态的属性才行。此外，UE4里面RPC并不支持回调，所有RPC函数的返回类型都是void。

属性同步，本质上属于一个比较上层的功能特性，是以每个对象为单位处理的（不支持更细粒度的同步，但理论上可以通过条件属性做部分调整，详见AACtor::PreReplicate）。unreal的服务器会按照一定频率的去执行同步对象属性的数据发送和接收，同时处理回调函数。属性同步的产生是为了维持对象的状态，是一个从概念上非常贴近“同步”二字的功能，一旦服务器上的同步属性发生了变化，就一定会发送给客户端（注意：属性同步只是服务器向客户端的同步，不存在客户端向服务器流通），也许中间会丢包会延迟（actor首次同步时是reliable的），但是其内置的机制会保证属性的值最终送达到客户端。借用一句经典的话来说就是，同步数据也许会迟到，但是永远不会缺席。

无论是RPC，还是属性同步，你会发现他都是基于UObject的，或者更确切的讲都是基于Actor的（以及其附属组件）。因为这两种功能一个是利用类中的函数，另一个是利用类对象的属性，他们都需要与某一个具体的对象作为媒介，而在UE的架构中，设计都是面向对象的，每个Actor都可以理解为现实世界的对象。既然是基于Actor的，那么整个同步就与GamePlay框架紧密相连。由于我们在发送同步数据的时候需要知道这个数据应该发向哪个客户端，而客户端与服务器的链接信息（IP等）又在Playercontroller里面，所以同步的逻辑与playercontroller密切相关。很多刚接触unreal的朋友经常会遇到RPC数据发不出去或者收不到的问题，就是没有认识到playercontroller其实是包含客户端与服务器的连接信息的。最典型的，假如你有服务器上连着10个玩家客户端，服务器上有一辆车，让他执行Client RPC，他怎么知道发给哪个客户端？当然是通过这个车找到控制他的playercontroller，然后找到对应客户端的IP，如果这个车不被任何客户端控制，那他就不知道要发给谁。

当然，RPC与属性同步的实现原理不同也决定了他们有很多差异。由于属性同步是跟着每一个实例对象走的，所以不存在“随用随发”。也就是说，属性同步需要在每帧特定的时机通过统一的引擎接口写到发送缓存（sendbuffer）里面。这样带来的问题就是，你在同一帧里面修改的属性只有最后的那个值会传到客户端那里，进而导致你的回调函数也只会执行一次。而RPC不同，每次执行时都会立刻将数据塞到发送缓存里面，从而保证不会丢失任何一次RPC的调用（假如RPC是可靠的）。


另外，这里面还有一个深坑，就是关于Actor以及Component的同步顺序问题。一个对象的同步首先要给客户端上的对象与服务器上的对象建立关联，这样服务器的A变化了才会告诉客户端上的A也去变化。但是A是一个对象，对象也是需要同步的，一个场景里面有那么多的对象，同步肯定是按顺序的来的。这样就会经常出现A的对象里面有很多指向B对象的同步指针属性，但是A对象出现的时候B还没同步过来，所以在A的Beginplay里面访问B是不行的。那么如何解决这个问题？答案是用属性回调，一旦执行了属性回调，就可以确保A的B指针是存在的。不过，属性回调并不能解决所有问题。假如B对象还有C对象的指针，回调的时候C还没同步过来，你想用B去访问C发现又是空指针。这问题目前在现在的虚幻引擎里面还没有完美的解决方案，所以我们要尽可能的避免这种情况（我本人正在尝试实现一些可行的方法）。类似引发的更细节的问题还有很多，后面我会列举一些。


二、移动同步
两种同步手段已经介绍完毕，我们现在把视角锁定在网络同步的解决方案上。游戏中同步本质上是同步客户端之间的表现，而RPC与属性同步都只是数据上的同步，我们需要将其与画面表现结合起来。画面表现说白了就是物体的显示与隐藏、动画、位置等，其中位置同步就是最复杂的一项，因为游戏中的角色可能是每帧都在移动的，移动组件（movementcomponent）就是为了解决这个问题而诞生的。

移动组件很复杂，他需要考虑到各种情况的延迟、抖动，需要解决不同客户端不同角色的流畅性问题，需要实现各种插值手段。在网络同步中，始终存在三种形式的角色，分别是本地玩家控制的、服务器控制的以及其他玩家控制的，在unreal中分别对应着Autonomous、Authority与Simulate。这三种类型的存在本质上代表着角色的控制者是谁（哪个端可以直接通过命令操作他），而从另一个角度讲这种分类其实是代表着玩家的操作是否有网络延迟以及延迟的大小。对于本地控制的Autonomous角色，他可以在本地直接响应你的操作，如果想把操作发给服务器，则需要经历一个client——server的延迟，而服务器想把这个操作同步给其他客户端又需要一个server——client的延迟。


同步中最难的其实就是如何有效的对抗这种延迟。所以，会诞生诸如延迟补偿这种同步策略，即服务器收到其他客户端射击消息的时候将本地的所有角色回滚到【当前时间 - 网络延迟时间】时的位置再进行消息的处理和计算。（UE4默认引擎里面没有这种操作，虚幻竞技场里面有。如下图）。


红色是当前端的具体位置，黄色是回滚预测的位置
移动组件本地客户端到服务器采用的是不可靠的RPC，而服务器到其他客户端采用的是属性同步。为什么使用RPC？因为客户端向服务器发送消息只能通过RPC，属性同步只是用来服务器同步给客户端用的。unreal在同步位置时记录了各个客户端以及服务器的时间戳，通过位置buffer缓存、每帧不停的发送位置、判断时间戳调整位置与回滚等操作实现比较理想的效果，本质上守望先锋的 帧同步（严谨点来说是借用帧同步的命令帧）+状态同步是相同的（详见：守望先锋架构与网络同步）。不过虚幻并没有采用ECS，并不能在架构上很好的支持所有逻辑的回滚。网络同步发展至今，其实基本已经成型。从早期的Lockstep到指令流水线化再到预测回滚TimeWarp，大体的同步优化手段都是这些，现在的趋势就是状态同步与帧同步里的各种机制互相借鉴互相促进。除了移动同步，其他的诸如动作同步和隐藏显示我们一般要求不那么苛刻，因为他们不需要每帧都做处理，一般采用RPC做一次性的通知修改就可以了。关于同步，还有一个大家平时不是很在意的细节，那就是同步频率。前面提到了UE4会按照尽可能快的速度去发送同步数据，如果客户端的性能非常好帧数非常高，那么一帧就会产生非常多的移动RPC。理论上来说，如果没有丢包的话，即使服务器帧率很低，服务器也会按照客户端发来数据逐个模拟，最后两端结果相同，仍然是流畅的。但是，如果中间丢失了部分移动的RPC（引擎内部就会对发送进行限流）就会造成客户端与服务器产生移动误差，同时由于服务器帧率较低不能及时处理客户端数据会导致误差逐渐被放大，进而不断拉回客户端，造成卡顿。

总的来说，RPC与属性同步有些场景是可以相互替代的。对于简单且实时性要求不高的使用RPC就可以，而对于需要服务器实时保有主控权且持续性同步的状态我们就可以使用属性同步。属性同步本身已经做了优化消耗没有那么大，你可以通过各种条件来设置他的同步规则。但是注意，量变产生质变，如果不加节制的全部使用属性同步，那么actor（以及属性）遍历的开销与会相当可观，所以还是合理的使用还是非常重要的。这块理论上有很多可以优化的地方，比如Actor可以设置同步的范围（类似AOI），距离玩家很远的对象不需要同步；Actor可以根据一些规则关闭对某些客户端的属性复制功能(Dormancy)，同时关闭ActorChannel并从NetConnection里移除；采用replicationgraph对空间进行划分，剔除相关性不强的对象从而减少带宽的占用（但是这个方案只适合大世界类型的游戏）。理论上，我们还可以添加更多的优化方式以及更细的粒度来进行调整，不过具体方案就要根据游戏类型来灵活处理了。


Replicationgraph示意，每个宝箱被放置到他所影响的所有格子里面。玩家只有进入这些格子里面才会收到宝箱的同步信息
三、回放系统
回放看起来是个很高大上的功能，但其实早在上世纪90年代就随着Lockstep算法一起诞生了。UE4内置了一套Demonetdriver系统来处理回放和录制，但由于采用的是状态同步而不是帧同步，所以实现起来比较复杂。基本思路就是在本地创建一个虚拟的服务器，录制的时候本地当成一个服务器，回放的时候本地又当做一个客户端。在游戏进行的时候，本地开始录制并把回放相关的数据序列化到数据流里面（可以是内存、磁盘或者是网络包），播放的时候再去对应的数据流里面读出来。虽然框架是有的，但还处于一个未完成的阶段，用起来坑也是相当的多（比如过期的多播事件在回放中不会被执行到）。对于死亡回放以及精彩镜头这种实时切换的需求，涉及到的逻辑要更复杂一些（比如真实世界和回放世界的切换与隐藏），这块有时间我会再写文章来仔细讲讲。【可以先参考：《守望先锋》回放技术-阵亡镜头、全场最佳和亮眼表现-腾讯游戏学院】


官方射击游戏Demo——ShooterGame中就含有一个简单的回放演示功能


四、网络框架
说完了上层的网络同步，再简单谈谈底层。虚幻引擎诞生于90年代，也肯定参考了很多其他游戏的设计，比如“雷神之锤（Quake）”，“星际围攻：部落（Tribe）”等。当时Quake是最早一批采用基于“CS架构状态同步”的游戏，而Tribe将模块进行拆分和封装，是第一个构建了比较完善的网络同步架构的游戏。UE4的架构与Tribe很像，通过NetDriver + NetConnection + Channel + Actor/Uobject抽象分层实现了目前的同步方式。很多人总是抱怨虚幻引擎把底层搞得太复杂，但这其实有很多历史原因以及技术上的权衡，官方团队在过去的20年里肯定也无数次地思考过这种问题，这里也不过多赘述。总之，从网络层面上说，UE4高度耦合的网络框架不适合帧同步（这里指lockstep），同时也很难改造成ECS架构。不过，我个人也同样觉得很多游戏没必要非要追求帧同步，两种同步开发各有各的坑，真做起来游戏其实都没那么简单（也许踩UE官方的坑可能会让你更不爽一点，毕竟不是自己写的）。

关于网络协议，游戏界经过大量的测试很早就公认——对于高频同步的游戏，使用UDP同步的效果要好于TCP。因此，unreal使用的就是UDP协议，但是为了保证数据的可靠性，需要在上层封装一个可靠的UDP，也就是NetDriver + NetConnection + Channel那一套。里面的逻辑很复杂而且涉及到很多模块，确实有一些冗余。此外，虽说是可靠的，但是在属性同步和RPC的处理方式上并不相同，属性同步只保证最后的数据是可靠的，中间的结果可能会丢失，而RPC则可以保证消息一定按序送达。针对其内置的RUDP的重发机制，UE其实已经做过很多次的优化和调整了，之前任何的丢包和乱序都会立刻触发重发，4.24里面已经添加了循环队列来收包矫正收包的次序，一定程度上减少了不必要的重传。消息的接收和发送默认还是在主线程处理的（我们可以决定是否启用多线程），由于UDP不需要监听多个Socket而且针对收包采用多线程意义也不大，所以也没有采用iocp或者其他异步IO的方式。在虚幻引擎中，网络包的更新顺序是“收数据——逻辑更新——发数据”，但并不是所有的同步更新逻辑都在收包的时候做，UObject类型同步属性的更新可能就是在发包前更新的（这块是一个坑，要注意），具体可以参考我的知乎文章“【《Exploring in UE4》网络同步原理深入（下）】” 中的第五部分第8小节。

​到此，我已经比较全面的把虚幻引擎的网络模块重新梳理一遍，更多细节请参考我专栏《Exploring in UE4》里面的相关文章。（还有一篇回放系统分析的待更。。。）

Jerish：《Exploring in UE4》关于网络同步的理解与思考[概念理解]
346 赞同 · 61 评论文章

Jerish：《Exploring in UE4》网络同步原理深入（上）[原理分析]
473 赞同 · 27 评论文章

Jerish：《Exploring in UE4》网络同步原理深入（下）[原理分析]
259 赞同 · 31 评论文章

Jerish：《Exploring in UE4》移动组件详解[原理分析]（2019.7.14更新）
595 赞同 · 35 评论文章

最后，我们再总结一些在同步中经常会遇到的问题，这些都是我踩了无数坑才总结出来的，拿大家的 “赞” 换一下不过分吧。

Client的RPC并不能保证一定在客户端执行。在服务器上，如果有一个没有connection信息的actor（比如不是同步的，完全由AI控制的。或者说他的remote role等于none），那么他的clientRPC只会在自己的客户端上面执行。最后可能造成的后果就是函数调用栈的无限循环进而崩溃。
beginplay在客户端服务器都会执行，如果在beginplay执行另外一个actor的生成。可能会触发客户端和服务器都生成一遍自己的actor，结果客户端存在了两个Actor（一个自己生成的，一个服务器生产的）。之后在调用RPC的时候很可能会出现RPC执行失败，因为本地生成的Actor没有任何connection信息。
客户端上对象的Beginplay是可能执行多次。在unreal中，如果一个actor是服务器创建并同步给客户端，那么服务器可以随时关闭这个对象的同步。一旦这个对象距离玩家角色非常远或者服务器主动关闭同步，客户端上的对象就会被删除掉。后期如果玩家又靠近了这个对象，那么就会重新同步到客户端，再执行一次Beginplay。这样某些数据进行两次初始化，可能不是我们想要的。
我们经常会遇到“游戏状态恢复”的场景，比如网络游戏中的断线重连。然后你就可能会遇到一些对象在重连后状态不对，因为很多对象的变化是通过RPC去做的，RPC是一次性的。当你重连后，RPC不会再执行一次，所以客户端重连的状态与服务器其实是不同的。这时候需要使用属性同步来解决问题，但是属性回调在断线重连的时候你也并不一定想执行，所以要重新审视一下回调函数里面的内容。
不要把随时可能被destroyed的对象传进RPC的参数里面，RPC参数里面没有判断对象是否是合法的。如果传递的过程中对象被destroy掉，后续可能触发序列化找不到NETGUID的相关崩溃。
一般情况下，onrep回调的执行顺序在同一个character内是严格按照属性的声明顺序的，不同actor无法保证先后
一般回调会调到的函数，要注意里面有没有判空return的情况，这个时候其他actor的指针是有可能为空的。
一个UObject指针类型的数组属性，可能会触发多次回调，最后一次可以确保所有指针都有值。
属性回调执行的前提是客户端与服务器的值不同，如果你本地先修改一个值，然后服务器修改的与客户端相同，那么是不会触发回调的。不过经评论区知友补充，可以采用DOREPLIFETIME_CONDITION_NOTIFY( AActor, XXX, COND_Custom, REPNOTIFY_Always ); 宏来强制客户端执行
一般来说当Actor与PC解绑后，Actor就无法保证RPC的执行了。这种情况往往发生在角色死亡后执行unpossess时，所以在这时应该注意RPC的执行情况。
如果属性没有同步到客户端或者不执行回调，注意一下是否使用了自定义的条件属性
所有设置定时器来判断同步属性是否收到的逻辑都是不规范的，一旦服务器或者客户端变卡（一开始没有表现，但是随着游戏内容的增加可能出现各种诡异的bug）就可能导致信息丢失
</code></pre>
</details>

<details>
<summary>游戏中到底是Z轴朝上还是Y轴朝上？</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/338314803
在谈到游戏世界中的坐标轴时，我们经常会看到这样的争论。

“游戏中Y轴是向上的好么？这你都不知道？”
“不对，空间直角坐标系不就是Z轴向上的么？”
“拜托，请搞清楚坐标系再来讨论好么？”.....
对于长期接触Z轴向上的空间直角坐标系的我也存在着同样的困惑，左右手坐标系已经够让人头大了，为什么连哪个轴向上都不能统一一下？而后当我试图通过搜索引擎寻找答案时，发现这个问题确实有不少人在讨论，也终于搞清楚了其中的缘由。





故事可能要从著名的三维建模软件3DS Max说起。3DS Max是公司AutoDesk第一款建模软件，它于1990年发布，主要用于设计和建筑领域。


在建筑学中，通常要先从平面图开始设计，所以先在2D网格上绘制X轴和Y轴，随后在将其拉伸成3D模型。很自然的，他们将下一个轴设置向上，即在3DMAX里面向上的便是Z轴（Z-Up）。这种思路与我们在学校时第一次从平面几何踏入空间几何的想法完全契合。


而在1998年，另一款著名的建模软件——Maya诞生了。Maya一开始主要作为动画软件系统发行，广泛用于动画电影当中。


与建筑领域相似，当时的动画通常也是2D的，即正面看Y轴向上，X轴向右。不过早期的迪士尼和其他动画作品为了能在不改变2D画面效果的条件下增加维度（例如2D平台游戏），保留了X轴和Y轴的朝向，新增的Z轴便成为了深度。当然，这里也有一定程度的历史原因——由于Maya一开始为SGI的（硅谷图形公司Silicon Graphics, Inc.）硬件开发，SGI早期提供的渲染引擎就是Y轴向上的，所以Maya就跟随SGI的标准制定坐标系（Y-Up）。


其实，造成这种差异的根本原因在于你是在屏幕空间中思考还是在世界空间中进行思考。

在屏幕空间中，给定X和Y的屏幕坐标，将Z作为深度可以方便的处理遮挡问题（即Y-Up）。许多渲染技术（DX、OpenGL）都使用“ Z缓冲区”之类的名称的来处理屏幕空间渲染（三维空间的渲染最后还是会输出到屏幕空间）。很明显，在二维环境中，Y轴向上的坐标系更有意义一些。




然而在世界空间中，我们通常希望像现实一样构建三维的世界。正常的三维空间示意图都将第三个坐标视为垂直方向的（即Z-Up）。要在世界空间中定义一个矩形，则要给出其长、宽、高。如果将Y视为垂直方向，那么就会陷入了一种不符合常识的情况，与我们多年来接触的笛卡尔坐标系相悖。




当你仔细调查一下目前流行的软件时，你会发现不同的软件其坐标系默认都是不一样的。除了前面提到的两款三维建模软件，另外两款著名的游戏引擎Unity与Unreal也有着不同的坐标系。受到历史因素的影响，Unreal诞生时3DS Max是当时大多数开发人员选择的建模工具包（Maya还没有诞生），所以采用了Z轴向上的左手系坐标。而Unity3D在2000以后才正式发布，采用的则是Y轴朝上左手坐标系。




由于标准的不同，导致我们在使用不同游戏引擎以及不同建模软件交互时需要手动处理坐标系的转换。而对于那些只接触过部分软件的人往往会保留“Z轴向上”或者“Y轴的向上”的固有印象，从而造成了前面提到的争论现象。无论哪种坐标系，都有其一定的道理，我们理解其中的缘由并能灵活的运用即可。



最后，再帮大家复习一下左手坐标系和右手坐标系（挥动双手的同时不妨点个赞支持一下）。
</code></pre>
</details>

<details>
<summary>游戏开发与设计中的“3C”是指什么？（Gameplay程序必看）</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/357621053
随着国内游戏行业的不断发展，越来越多国外的专业词汇被引入进来。“3C”作为一个比较重要的技术名词至今却仍然被不少游戏从业者所陌生。那么到底什么是3C？他在游戏设计以及游戏开发中有什么具体意义呢？

3C，最早是由育碧（Ubisoft）公司提出的游戏设计概念，其实就是指Character Camera Control（角色、相机、控制）三个单词的缩写，代表了大部分游戏设计中三种最为基本的元素。在13年出版的经典启蒙书籍——《通关！游戏设计之道》这本书中，作者Scott又对其进行更为详细了解释和拓展。


3C的概念与理解
从字面上来看，我们可以这样理解

Character，表示一个或多个游戏角色，玩家可以扮演该角色、也可以在游戏中可以观察该角色的行为。
Camera ，表示一个或多个摄像机，以此来辅助玩家观察游戏世界，增加玩家的体验感和沉浸感。
Control，表示用一个或多个控制设备，设置特定的交互规则来使玩家控制对应的角色。
动图封面
▷▶《奥日与黑暗森林》控制Ori移动

进一步来看，三者还有很多细节上的内容需要分析和深入。

Character（角色），一般是游戏中的主角，代表着玩家的物理容器，拥有着鲜明的形象特点（体型、剪影、配色、材质等）和行为方式（移动方式、战斗方式等），能够以最为简洁的表达向玩家提供游戏的基本信息。好的角色设计可以让玩家相对容易的根据外观、姓名、对话等来了解其有哪些能力、故事背景等等。

一个角色的诞生需要经过概念与背景设计、原画设计、三维模型设计（3D游戏）、动画设计、技能设计、程序实现、测试反馈等多个流程，同时我们还要考虑是否允许玩家自定义角色形象、设计内容是否与游戏背景冲突等。当然，游戏中角色通常不止一个，比如RPG中需要多个角色（流程是相似的）来构建故事和冲突，主角团之间不同角色还可以通过互补来丰富游戏的体验，如果是多人竞技游戏，还需要注意不同Character设计的平衡性。


▷▶《古剑奇谭3》的主角设计稿
我在之前的文章《为什么说“角色移动”看上去很简单，却需要极高的技术力与细节成本？》就提到，角色的移动与技能是游戏中非常重要且复杂的设计环节，走路、游泳、飞行、跳跃、驾驶等行为之间的切换与衔接非常复杂，需要程序和策划进行详细的规划与思考。


Camera（相机） ，用于展示玩家所看到的东西，决定了玩家观察游戏世界的方式。我们可以选择第一人称、第三人称或者是俯视的上帝视角等。第一人称的Camera可以有更强的代入感和沉浸感（常用于射击游戏、恐怖游戏、解密游戏等），但是一定程度上失去了对角色的形象展示而且容易让部分玩家感到眩晕；第三人称可以让玩家更好的欣赏角色和游戏世界（常见的RPG、ACT、格斗游戏），通过角色的代入也能很好融入到游戏内部，是比较常见的方案；而对于RTS这种需要观察多个角色的游戏类型，我们通常会采用等轴镜头、俯视镜头来设置相机的模式。



拍摄本身其实就是一个充满艺术设计的事儿，很多游戏为了达到理想的效果，都会找专门的影视从业者来设计镜头的位置、切换方式等。不过，观察视角的自由性是游戏区别于其他影视艺术本身的重要一环，所以在大部分游戏里面我们都会尽可能的把摄像机的控制权交给玩家，只在一些需要展示特殊的艺术表现时才夺回控制权（过场动画、处决的镜头等，有一些特殊情况会在后面提到）。


除了相机的切换，Camera还可以通过FOV变化（准镜瞄准）、特效变化、后处理变化、震动变化（ACT战斗）等方式来给玩家提供更多的信息和更丰富的体验，而这些效果变化的具体数值和时机是需要我们不断测试和优化的。


Control（控制），代表着输入到响应的整个过程。控制首先要考虑的就是交互按钮是否符合玩家习惯、人体工学。由于游戏设备经过几十年的发展已经基本成型（手柄、键鼠为主，还有VR、街机等），而且大部分游戏开发商只做游戏软件，所以很少需要我们去考虑硬件的设计。我们通常更关注的是按钮的匹配规则（比如玩家下蹲肯定不能对应一个向上的按钮），UI的交互方式（尤其是移动端现在面临屏幕小、按钮多的问题）等，这些通常会交给UX的同事去做设计。




其次，Control也涵盖了“当玩家进行操作时如何将表现反馈给玩家”这一点，这时候他更像是一个衔接玩家行为与游戏表现的抽象概念。具体来说，我们按下按钮后，玩家有多少时间进行下一步的反应？游戏中的角色的移动速度、镜头、UI、音效应该有怎样的变化？变化规则应该通过什么方式传递给玩家？这些内容与Character和Camera的设计是息息相关的。

概括来讲，3C表达了从玩家的输入到游戏角色的响应再到这一帧的画面如何被相机记录下来的过程。我们在上手一个游戏的时候，很快就能够从3C的差异上对该游戏进行分类和定义，比如他是第一人称还是第三人称，是ACT战斗还是射击类型。从某种程度上说3C展示了一个游戏最核心的体验，指导玩家学习并上手，很多情况下与我们常提到的Gameplay可以认为是等价的。

在设计游戏时候，我们可以简单的将游戏3C分为基础3C和高级3C，基础3C决定游戏的基本操作和交互方式，比如玩家按钮如何响应、角色的基本轮廓和特点、可以做哪些基本行为、我们的相机视角有哪些等。而高级3C是在基础3C上的拓展，角色可以有变化的形象、更丰富的移动方式以及更多样的镜头效果和反馈。比如，在战神4和蝙蝠侠中，我们移动使用的是第三人称的靠肩视角，角色屏占比为1/4的基础3C，可以给玩家营造角色魁梧、行为充满力量的厚重感。而战斗中动态变化的镜头以及可以扔出的斧头和勾爪则是属于高级3C，这些加强了游戏时的沉浸感和真实感，让玩家被代入到角色的行为与故事之中。

动图封面

当然，确实也存在一些游戏并没有完整的3C，甚至很多游戏的诞生要要远远早于3C的概念。比如俄罗斯方块以及消除类游戏中并不存在所谓的“角色”，互动文字类游戏也没有所谓的“相机”。

不过这并不是说这套理论就没有意义了，你也可以认为这些游戏类型只是在一定程度上限制住了Character和Camera的设计。假如我们仍然以这套理论为指导，将俄罗斯方块中的“方块”视为角色，将贯穿整个游戏的固定镜头视为相机，那么是不是就可以进一步地设计出更丰富的“方块角色”和更为丰富的“镜头”效果了？毕竟，任何理论都不是一成不变的。



还有一些游戏，融合了多种类型的3C设计，镜头上既有第一人称视角也有上帝视角，既能作为主角体验游戏世界也可以以独特的第三人称视角来观察故事的发展。如果一款游戏能将这些都完美的结合，那无疑会给玩家带来前所未有的游戏体验。我个人比较喜欢的《艾迪芬奇的记忆》就是这样一个充满艺术魅力并融合了多种3C设计的佳作。


▷▶《艾迪芬奇的记忆》
程序3C
谈完了游戏设计的中3C，我们不妨再从程序的角度来认识一下他。简单来说，每一款游戏都需要将前面提到的内容抽象到代码层面，封装好并交给策划去进行设计和拓展。比如虚幻引擎里面就内置了一个成熟的Gameplay系统，你可以看到Playercontroller、Cameramanager以及Character等等的C++类，这些类与前面提到的3C是非常相似的概念。游戏中所有拥有移动、碰撞能力的对象都应该继承自Character，响应按钮事件的逻辑应该存放在Controller里面，而摄像机的位置、特效、震动等逻辑都被封装到了CameraManager里面，这是Unreal多年来积累的一种面向对象的3C设计方案。


角色动画这块的系统非常复杂，所以需要被单独抽离出来。在大部分引擎中，动画一般是通过专门的动画系统来驱动角色身上的蒙皮骨骼模型进行模拟。


3C涉及游戏的核心系统，其内容是与游戏玩法高度相关的，所以不同的游戏的3C都有所不同，而且很可能差异很大。比如常见的ARPG，设计层面上要有一个完整的故事和一个个性鲜明的角色，而程序上我们需要实现一个可玩的有打击感的战斗系统（涉及到复杂的动画系统、特效系统、镜头处理、音效、震动反馈、后处理等）、角色成长系统（数值计算）、移动系统（攀爬、游泳、飞行等）、定制的动画以及分镜系统等。而在其他的游戏中，还可能有关卡生成系统（我的世界）、载具系统（极品飞车）、以及各种特殊的与游戏规则高度相关的定制系统（文明）。这些系统深入起来并不容易，但是却往往被大家所忽略。


拿FPS游戏举例，角色上我们需要考虑玩家的移动方式（包括行走、冲刺、翻越、爬行、死亡等状态的切换与打断，特殊状态如何进行设计和处理等）、武器与技能的制作和使用（包括武器的切换方式、数值计算规则、武器结构的拆分与组装等）、角色的第一人称和第三人称的模型效果（包括角色的形象设计与展示、如何在游戏中自由切换一三人称、第一人称是否能看到下半身等）、角色的动画表现（包括移动、交互、开火等行为以及各种道具的动画）；摄像机我们要考虑基本视角（第一人称）、镜头的切换（支持哪些特殊视角、不同视角的切换规则、是否有ADS瞄准状态）、镜头效果（包括屏幕后处理变化、后坐力震动效果设计）；控制上根据不同的平台要考虑不同的设计，比如按键的位置、大小、是否允许自定义按键，按键的响应规则和响应时间等等。总的来说，3C需要考虑的东西非常繁多且复杂。如果是网络游戏，这个工作量可能还要扩大一半左右。

动图封面
对于3C程序来说，确实存在一些相对通用的技术与功能，比如Gameplay框架、状态机FSM/HFSM（比如逻辑状态机用于衔接角色的行为表现），网络同步，动画系统，移动系统等，但是由于国内游戏行业的发展不够成熟以及这些内容并不适用用所有游戏，所以造成了很多Gameplay程序发展方向不明确的问题。此外，像一些其他技术如FOV分层渲染、描边、物理破碎、音效、界面特效等实现虽然可能会交给渲染、音频、UI等其他程序做，但3C程序理论上也要做到理解并负责将其整合到现有游戏的系统内。

实际项目中，游戏涉及到的技术很杂，很多时候不那么好划分，再加上项目的人力有限，3C程序也没有必要给自己限制在某些技术范围内，要根据个人发展以及项目情况适当了解和学习其他模块的知识，如渲染、物理、AI等内容。

总结
总的来说，高质量的3C是游戏坚实的基础，依据3C的理论我们可以从多个方向来思考并进一步丰富我们的游戏内容，进而让玩家处于一个专注且享受的“心流”状态。对于3C程序而言，我们需要根据游戏的类型搭建合适的3C框架，同时与策划不断的进行沟通和打磨，来构建一个更有魅力的游戏世界并给予玩家一个更为完美的游戏体验！


对游戏开发与设计感兴趣的朋友，可以通过下面链接获取《通关！游戏设计之道》以及更多游戏设计相关的电子书

原文链接：游戏设计书籍获取方式
</code></pre>
</details>

<details>
<summary>《Exploring in UE4》Unreal回放系统剖析</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/564017214
前段时间，在Epic举办的UnrealCircle会议上，我受邀分享了一场关于“UE4回放系统”的技术演讲。不过由于时长限制，很多细节都没有得到进一步的阐述。这篇文章会在演讲的基础上拓展更多内容，更好的帮助大家去理解虚幻引擎的回放系统，建议大家结合源码进行阅读和学习。（感兴趣的朋友可以到公众号去拿PPT）
[UnrealCircle]UE4回放系统剖析 | 网易游戏 Jerish_哔哩哔哩_bilibili
​www.bilibili.com/video/BV1Z34y1n72n/?spm_id_from=333.788

回放，是电子游戏中一项常见的功能，用于记录整个比赛过程或者展示游戏中的精彩瞬间。通过回放，我们可以观摩高手之间的对决，享受游戏中的精彩瞬间，甚至还可以拿到敌方玩家的比赛录像进行分析和学习。

从实现技术角度来讲，下面的这些功能本质上都属于回放的一部分

精彩瞬间展示: FIFA / 实况足球 / NBA2K / 守望先锋 / 极限竞速：地平线 / 跑跑卡丁车
死亡回放: 守望先锋 / 彩虹六号 / 使命召唤 / CODM
全局比赛录制、下载、播放: 守望先锋 / CSGO / Dota / LOL / 魔兽争霸 / 星际争霸 / 红色警戒 / 坦克世界 / 绝地求生 / 王者荣耀
观战（常用于非实时观战）: CSGo / 堡垒之夜 / Dota
时光倒流：Braid / 极限竞速：地平线

彩虹6号中的击杀回放
早在20世纪90年代，回放系统就已经诞生并广泛用于即时战略、第一人称射击以及体育竞技等类型的游戏当中，而那时存储器的容量非常有限，远远无法与当今动辄几十T的硬盘相提并论，面对一场数十分钟的比赛，比赛数据该如何存储和播放？回放该如何实现？这篇文章会通过剖析UE的回放系统，来由浅入深的帮助大家理解其中的原理和细节。

概述
其实实现回放系统有三种思路，分别是：

逐帧录制游戏画面
播放简单，方便分享
性能开销大，占用空间，不灵活
逐帧录制玩家的输入操作
录制数据小，灵活
跳跃、倒退困难，计算一致性处理复杂
定时录制玩家以及游戏场景对象的状态
录制数据较少，开销可控，灵活
逻辑复杂
三种方案各有优劣，但由于第一种录制画面的方案存在着“占用大量存储空间”、”加载速度慢”、“不够灵活”等比较严重的问题，我们通常采用后两种方式来实现游戏中的回放。

可以参考“游戏中的回放系统是如何实现的？”来进一步了解这三种方案
一、帧同步、快照同步与状态同步
虽然不同游戏里回放系统具体的实现方式与应用场景不同，但本质上都是对数据的记录和重现，这个过程与网络游戏里面的同步技术非常相似。举个例子，假如AB两个客户端进行P2P的连接对战，A客户端上开始时并没有关于B的任何信息。当建立连接后，B开始把自己的相关信息（坐标，模型，大小）发给A，A在自己的客户端上利用这个信息重新构建了B，完成了数据的同步。

思考一下，假如B不把这个信息发给A，而发给自己进行处理，是不是就相当于录制了自己的机器上的比赛信息再进行回放呢？


没错，网络游戏中的同步信息正是回放系统中的录制信息，因此网络同步就是实现回放系统的技术基础！

在正式介绍回放系统前，不妨先概括地介绍一下游戏开发中的网络同步技术。我们常说网络同步可以简单分为帧同步、快照同步和状态同步，但实际上这几个中文概念是国内开发者不断摸索和自创的名词，并非严格指某种固定的算法，他们有很多变种，甚至可以结合到一起去使用。

帧同步，对应的英文概念是LockStep/ Deterministic Lockstep。其基本思路是每固定间隔（如0.02秒）对玩家的行为进行一次采样得到一个“Input指令” 并发送给其他所有玩家，每个玩家都缓存来自其他所有玩家的“Input指令” ，当某个玩家收到所有其他玩家的“Input指令”后，他的本地游戏状态才会推进到下一帧。

快照同步，可以翻译成Snapshot Synchronization。其思想是服务器把当前这帧整个游戏世界的状态进行一个备份，然后把这个备份发送给所有客户端，客户端按照这个备份对自己的世界状态进行修改和纠正进而完成同步。（快照，对应的英文概念是SnapShot，强调的是某一时刻的数据状态或者备份。从游戏世界的角度理解，快照就是整个世界所有的状态信息，包括对象的数量、对象的属性、位置线信息等。从每个对象的角度理解，快照就是指整个对象的各种属性，比如生命值、速度这些。所以，不同场景下快照所指的内容可能是不同的。）

状态同步，可以翻译成State（State Based） Synchronization。其思想与快照同步相似，也是服务器将世界的状态同步给客户端。但不同的是状态同步的粒度变得非常小（以对象或者对象的属性为单位），服务器不需要把一帧里面所有的对象状态进行保存和同步，只需要把客户端需要的那些对象以及需要的属性进行保存和发送即可。

拓展：快照同步其实是状态同步的前身，那时候整个游戏需要记录的数据量还不是很大，人们也自然的使用快照来代表整个世界在某一时刻的状态，通过定时地同步整个世界的快照就可以做到完美的网络同步。但是这种直接把整个世界的状态进行同步的过程是很耗费流量和性能的，考虑到对象的数据是逐步产生变化的，我们可以只记录发生变化的那些数据，所以就有了基于delta的快照同步。更进一步的，我们可以把整个世界拆分一下，每一帧只针对需要的对象进行delta的同步，这样就完全将各个对象的同步拆分开来，再结合一些过滤可以进一步减少没必要的数据同步，最后形成了状态同步的方案。更多关于网络同步技术的发展和细节可以参考我的文章——《细谈网络同步在游戏历史中的发展变化》。
二、UE4网络同步基础
在虚幻引擎里面，默认实现的是一套相对完善的状态同步方案，场景里面的每个对象都称为一个Actor，每个Actor都可以单独设置是否进行同步（Actor身上还可以挂N个组件，也可以进行同步），Actor某一时刻的标记Replicated属性就是所谓的状态信息。服务器在每帧Tick的时候，会去判断哪些Actor应该同步给哪些客户端，哪些属性需要进行同步，然后统一序列化成二进制（可以理解为一个当前世界状态的增量快照）发给对应的客户端，客户端在受到后还可以调用回调函数进一步处理。这种通信方式我们称为属性同步。

此外，UE里面还有一个另一种通信方式叫RPC，可以像调用本地函数那样来调用远端的函数。RPC常用于做一些跨端的事件通知，虽然并不严格属于传统意义上状态同步的范畴，但也是UE网络同步里面不可缺少的一环。




为了实现上面两种同步方式，UE4通过抽象分层实现了一套NetDriver + NetConnection + Channel + Actor/Uobject的同步方式（如下图）。

NetDriver：网络驱动管理，封装了同步Actor的基本操作，还包括初始化客户端与服务器的连接，建立属性同步记录表，处理RPC函数，创建Socket，构建并管理Connection信息，接收数据包等等基本操作。
Connection：表示一个网络连接。服务器上，一个客户端到一个服务器的一个连接叫一个ClientConnection。在客户端上，一个服务器到一个客户端的连接叫一个ServerConnection。
Channel：数据通道，每一个通道只负责交换某一个特定类型特定实例的数据信息。比如一个ActorChannel只负责处理对应Actor本身相关信息的同步，包括自身的同步以及子组件，属性的同步，RPC调用等。
更多内容参考请我的知乎专栏https://www.zhihu.com/column/c_164452593

&gt;&gt;UE中的网络同步架构


三、回放系统框架与原理
3.1回放系统的核心与实现思路：
结合我们前面提到的网络同步技术，假如我们现在想在游戏里面录制一场比赛要怎么做呢？是不是像快照同步一样把每帧的状态数据记录下来，然后播放的时候再去读取这些数据呢？没错！利用网络同步的思想，把游戏本身当成一个服务器，游戏内容当成同步数据进行录制存储即可。

当然对于帧同步来说，我们并不会去记录不同时刻世界的状态信息，而是把关注点放在了玩家的行为指令上（Input队列）。帧同步会默认各个客户端的初始状态完全一致，只要保证同一时刻每个指令的相同，那么客户端上整个游戏世界的推进和表现也应该是完全一样的（需要解决浮点数精度、随机数一致性问题等）。由于只需要记录玩家的行为数据，所以一旦帧同步的框架完成，其回放系统的实现是非常方便和轻量化的。

无论哪种方式，回放系统都需要依靠网络同步框架来实现。虚幻系统本身是状态同步架构，所以我们后面会把重点都放在基于状态同步的回放系统中去。

如果你想深入UE4的网络同步，好好研究回放系统是一个不错的学习途径。官方文档链接：
https://docs.unrealengine.com/4.27/en-US/TestingAndOptimization/ReplaySystem/
根据上面的阐述，我们已经得到了实现回放系统的基本思路，

录制：就像服务器网络同步一样，每帧去记录所有对象（Actor）的状态信息，然后通过序列化的方式写到一个缓存里面。
播放：拿到那个缓存数据，反序列化后赋值给场景里面对应的Actor
序列化：把对象存储成二进制的形式
反序列化：根据二进制数据的内容，反过来还原当时的对象
3.2 UE4回放系统的简单使用：
为了能有一个直观的效果，我们先尝试动手录制并播放一段回放，步骤如下。

在EpicLancher里面下载引擎（我使用的是4.26版本），创建一个第三人称的模板工程命名为MyTestRec
点击Play进入游戏后，点击“~”按钮并在控制台命令执行demorec MyTestReplay开始录制回放
随便移动人物，30秒后再次打开控制台命令执行Demostop。
再次打开控制台，命令执行demoplay MyTestReplay，可以看到地图会被重新加载然后播放刚才录制的30秒回放‍

3.3 UE4中的回放系统架构：
虚幻在NetDriver + NetConnection + Channel的架构基础上（上一节有简单描述） ，拓展了一系列相关的类来实现回放系统（ReplaySystem）

UReplaySubsystem：一个全局的回放子系统，用于封装核心接口并暴露给上层调用。（注：Subsystem类似设计模式中的单例类）
DemoNetdriver：继承自NetDriver，专门用于宏观地控制回放系统的录制与播放。
Demonetconnection：继承自NetConnection，可以自定义实现回放数据的发送位置。
FReplayHelper：封装一些回放处理数据的接口，用于将回放逻辑与DemoNetDriver进行解耦。
XXXNetworkReplayStreamer：回放序列化数据的存储类，根据不同的存储方式有不同的具体实现。

3.3.1数据的存储和读取概述：

在前面的示例中，我们通过命令demorec将回放数据录制到本地文件，然后再通过命令demoplay找到对应名称的录制并播放，这些命令会被UWorld::HandleDemoPlayCommand解析，进而调用到回放系统的真正入口StartRecordingReplay/ StopRecordingReplay/ PlayReplay。


入口函数被封装在在UGameinstance上并且会最终执行到回放子系统UReplaySubsystem上（注：一个游戏客户端/服务器对应一个GameInstance）。


数据的存储：

当我们通过RecordReplay开始录制回放时，UReplaySubsystem会创建一个新的DemoNetDriver并初始化DemonetConnection、ReplayHelper、ReplayStreamer等相关的对象。接下来便会在每帧结尾时通过TickDemoRecord对所有同步对象进行序列化（序列化的逻辑完全复用网络同步框架）。

由于UDemoNetConnection重写了LowLevelSend接口，序列化之后这些数据并不会通过网络发出去，而是先临时存储在ReplayHelper的FQueuedDemoPacket数组里面



不过QueuedDemoPackets本身不包含时间戳等信息，还需要再通过FReplayHelper::WriteDemoFrame将当前Connection里面的QueuedDemoPacket与时间戳等信息一同封装并写到对应的NetworkReplayStreamer里面，然后再交给Streamer自行处理数据的保存方式，做到了与回放逻辑解耦的目的。




数据的读取：

与数据的存储流程相反，当我们通过PlayReplay开始播放回放时，需要先从对应的NetworkReplayStreamer里面取出回放数据，然后解析成FQueuedDemoPacket数组。随后每帧在TickDemoPlayback根据Packet里面的时间戳持续不断的进行反序列化来恢复场景里面的对象。


到这里，我们已经整理出了录制和回放的大致流程和入口位置。但为了能循序渐进的剖析回放系统，我还故意隐藏了很多细节，比如说NetworkReplayStreamer里面是如何存储回放数据的？回放系统如何做到从指定时间开始播放？想弄清这些问题就不得不进一步分析回放相关的数据结构与组织思想。


3.3.2回放数据结构的组织和存储：

无论通过哪种方式实现回放都一定会涉及到快进，暂停，跳转等类似的功能。然而，我们目前使用的方式并不能很好的支持跳转，主要问题在于虚幻引擎默认使用增量式的状态同步，任何一刻的状态数据都是前面所有状态同步数据的叠加，必须从最开始播放才能保证不丢失掉中间的任何一个数据包。比如下图的例子，如果我想从第20秒开始播放并且从第5个数据包开始加载，那么一定会丢失Actor1的创建与移动信息。


数据流在录制的时候中间是没有明确分割的，也就是所有的序列化数据都紧密的连接在一起的，无法进行拆分，只能从头开始一点点的读取并反序列化解析。中间哪怕丢了一个字节的数据都可能造成后面的数据解析乱掉。

为了解决这个问题，Unreal对数据流进行了分类

Checkpoint：存档点，即一个完整的世界快照（类似单机游戏中的存档），通过这个快照可以完全的回复当时的游戏状态。每隔一段时间（比如30s）存储一个checkpoint。
Stream：一段连续时间的数据流，存储着从上一个Checkpoint到当前的所有序列化录制数据
Event：记录一些特殊的自定义事件

通过这种方式，我们在任何时刻都可以找到一个临近的全局快照（Checkpoint）并进行加载，然后再根据最终目标的时间快速的读取后续的stream信息来实现目标位置的跳转。拿前面的案例来说，由于我现在在20s的时候可以通过Checkpoint的加载而得到前面Actor1在当前的状态，所以可以完美的实现跳转功能。在实际录制的时候，ReplayHelper的FQueuedDemoPacket其实有两个，分别用于存储Stream和Checkpoint。

//当前的时间DemoCurrentTime也会被序列化到FQueuedDemoPacket里面  
 TArray<FQueuedDemoPacket> QueuedDemoPackets;
 TArray<FQueuedDemoPacket> QueuedCheckpointPackets;
只有达到存储快照的条件时间时（可通过控制台命令设置CVarCheckpointUploadDelay InSeconds设置），我们才会调用SaveCheckpoint函数把表示Checkpoint的QueuedCheckpointPackets的写到NetworkReplayStreamer，其他情况下我们则会每帧把QueuedDemoPackets表示的stream数据进行写入处理。

void FReplayHelper::TickRecording(float DeltaSeconds, UNetConnection* Connection)
{
    //...省略部分代码
  FArchive* FileAr = ReplayStreamer->GetStreamingArchive();
    //...省略部分代码
    
    //录制这一帧，QueuedDemoPackets的数据写到ReplayStreamer里面
    RecordFrame(DeltaSeconds, Connection);

    // Save a checkpoint if it's time
    if (CVarEnableCheckpoints.GetValueOnAnyThread() == 1)
    {
        check(CheckpointSaveContext.CheckpointSaveState == FReplayHelper::ECheckpointSaveState::Idle);    
        if (ShouldSaveCheckpoint())
        {
            SaveCheckpoint(Connection);
        }
    }
}
每次回放开始前我们都可以传入一个参数用来指定跳转的时间点，随后就会开启一个FPendingTaskHelper的任务，根据目标时间找到前面最靠近的快照，并通过UDemoNetDriver:: LoadCheckpoint函数来反序列化恢复场景对象数据（这一步完成Checkpoint的加载）。

如果目标时间比快照的时间要大，则需要在ConditionallyReadDemoFrameInto PlaybackPackets快速的把这段时间差的数据包全部读出来并进行处理，默认情况下在一帧内完成，所以玩家并无感知（数据流太大的话会造成卡顿，可以考虑分帧）。

// Buffer up demo frames until we have enough time built-up
 while (ConditionallyReadDemoFrameIntoPlaybackPackets(*GetReplayStreamer()->GetStreamingArchive()))
 {
     
 }
// Process packets until we are caught up (this implicitly handles fast forward if DemoCurrentTime past many frames)
while (ConditionallyProcessPlaybackPackets())
{
    PRAGMA_DISABLE_DEPRECATION_WARNINGS
   DemoFrameNum++;
   PRAGMA_ENABLE_DEPRECATION_WARNINGS
   ReplayHelper.DemoFrameNum++;
}
前面提到的QueuedDemoPackets只是临时缓存在ReplayHelper里，那最终序列化的Stream和Checkpoint具体存储在哪里呢？答案就是我们多次提到的NetworkReplayStreamer。在NetworkReplayStreamer里面会一直维护着StreamingAr和CheckpointAr两个数据流，DemonetDriver里面对回放数据的存储和读取本质上都是对这两个数据流的修改。

Archive可以翻译成档案，在虚幻里面是用来存储序列化数据的类。其中FArchive是数据存储的基类，封装了一些序列化/反序列化等操作的接口。我们可以通过继承FArchive来实现自定义的序列化操作。
那这两个Archive具体是如何存储和维护的呢？为了能有一个直观的展示，建议大家先去按照2.3小结的方式去操作一下，然后就可以在你工程下/Saved/Demo/路径下得到一个回放的文件。这个文件主要存储的就是多个Stream和一个checkpoint，打开后大概如下图（因为是序列化成了2进制，所以是不可读的）


接下来我们先打开LocalFileNetworkReplayStreaming.h文件，并找到StreamAr和CheckpointAr这两个成员，查看FLocalFileStreamFArchive的定义。


FLocalFileStreamFArchive继承自FArchive类，并重写了Serialize(序列化)函数，同时声明了一个TArray<uint8>的数组来保存所有序列化的数据，那些QueuedDemoPacket里面的二进制数据最终都会写到这个Buffer成员里面。不过StreamAr和CheckpointAr并不会一直保存着所有的录制数据，而是定时的把数据通过Flush写到本地磁盘里面，写完后Archive里面的数据就会清空，接着存储下一段时间的回放信息。

而在读取播放时，数据的处理流程会有一些差异。系统会尝试一次性从磁盘加载所有信息到一个用于组织回放的数据结构中——FLocalFileReplayInfo，然后再逐步的读取与反序列化，因此下图的FLocalFileReplayInfo在回放开始后其实已经完整地保存着一场录制里面的所有的序列化信息了（Chunks数组里面就存储着不同时间段的StreamAr）



FLocalFileNetworkReplayStreamer是为了专门将序列化数据写到本地而封装的类，类似的还有的用于Http发送的FHttpNetworkReplayStreamer。这些类都继承自接口INetworkReplayStreamer，在第一次执行录制的时候会通过对应的工厂类进行创建。


Http：把回放的数据定时的通过Http发送到一个指定url的服务器上
InMemory：不断的将回放数据写到内存里面，可以随时快速地取出
LocalFile:写到本地指定目录的文件里面，维护了一个FQueuedLocalFileRequest队列不停地按顺序处理数据的写入和加载 NetWork:各种基类接口、基类工厂
Null：早期默认的存储方式，通过Json写到本地文件里面，但是效率比较低（已废弃）
SavGame：LocalFile的前身，现在已经完全继承并使用LocalFile的实现

我们可以通过在StartRecordingReplay/ PlayReplay的第三个参数（AdditionalOptions）里面添加“ReplayStreamerOverride=XXX”来设置不同类型的ReplayStreamer，同时在工程的Build.cs里面配置对应的代码来确保模块能正确的加载。

TArray<FString> Options;
Options.Add(TEXT("ReplayStreamerOverride=LocalFileNetworkReplayStreaming"));
UGameInstance* GameInstance = GetWorld()->GetGameInstance();
GameInstance->StartRecordingReplay("MyTestReplay", "MyTestReplay", Options);
//GameInstance->PlayReplay("MyTestReplay", GetWorld(), Options);

//MyTestReplay.build.cs
DynamicallyLoadedModuleNames.AddRange(
    new string[] {
        "NetworkReplayStreaming",
        "LocalFileNetworkReplayStreaming",
        //"InMemoryNetworkReplayStreaming",可选，按需配置加载
        //"HttpNetworkReplayStreaming"
    }
);
PrivateIncludePathModuleNames.AddRange(
    new string[] {
        "NetworkReplayStreaming"
    }
);
当然，在NetworkReplayStreamer还有许多重要的函数，比如我们每次录制或者播放回放的入口Startstream会事先设置好我们要存储的位置、进行Archive的初始化等，不同的Streamer在这些函数的实现上差异很大。

virtual void StartStreaming(const FStartStreamingParameters& Params, const FStartStreamingCallback& Delegate) = 0;
virtual void StopStreaming() = 0;
virtual FArchive* GetHeaderArchive() = 0;
virtual FArchive* GetStreamingArchive() = 0;
virtual FArchive* GetCheckpointArchive() = 0;
virtual void FlushCheckpoint(const uint32 TimeInMS) = 0;
virtual void GotoCheckpointIndex(const int32 CheckpointIndex, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) = 0;
virtual void GotoTimeInMS(const uint32 TimeInMS, const FGotoCallback& Delegate, EReplayCheckpointType CheckpointType) = 0;
0;

3.3.3 回放架构梳理小结

到此，我们已经对整个系统有了更深入的理解，再回头看整个回放的流程就会清晰很多。

游戏运行的任何时候我们都可以通过StartRecordingReplay执行录制逻辑，然后通过初始化函数创建DemonetDriver、DemonetConnection以及对应的ReplayStreamer。
DemonetDriver在Tick的时候会根据一定规则对当前场景里面的同步对象进行录制，录制的数据先存储到FQueuedDemoPacket数组里面，然后再写到自定义ReplayStreamer的FArcive里面缓存。
FArcive分为StreamAr和CheckpointAr，分别用持续的录制和特定时刻的全局快照保存，里面的数据到达一定量时我们就可以把他们写到本地或者发送出去，然后清空后继续录制。
当执行PlayReplay开始回放的时候，我们先根据时间戳找到就近的CheckpointAr进行反序列化，利用快照恢复整个场景后在使用Tick去读取StreamAr里面的数据并播放。
回放系统的Connection是100%Reliable的，Connection->IsInternalAck()为true

3.4 回放实现的录制与加载细节
上个小结我们已经从架构的角度上梳理了回放录制的原理和过程，但是等很多细节问题还没有深究，比如

回放时观看的视角如何设置？
哪些对象应该被录制？
录制频率如何设置？
RPC和属性都能正常录制么？
加载Checkpoint的时候要不要删除之前的actor？
快进和暂停如何实现？
这些问题看似简单，但实现起来却并不容易。比如我们在播放时需要动态的切换特定的摄像机视角，那就需要知道UE里面的摄像机系统，包括Camera的管理、如何设置ViewTarget，如何通过网络GUID找到对应的目标等，这些内容都与游戏玩法高度耦合，因此在分析录制加载细节前建议先回顾一下UE的Gameplay框架。

3.4.1 回放世界的Gameplay架构

虚幻的Gameplay基本是按照面向对象的方式来设计的，涉及到常见概念（类）如下

World：对应一个游戏世界
Level：对应一个子关卡，一个World可以有很多Level
Controller/PlayerController：玩家控制器，可以接受玩家输入，设置观察对象等。
Pawn/Character：一个可控的游戏单位，Character相比Pawn多了很多人型角色的功能，比如移动、下蹲、跳跃等。
CameraManager：所有摄像机相关的功能都通过CameraManager管理，比如摄像机的位置、摄像机震动效果等。
GameMode：用于控制一场比赛的规则。
PlayerState：用于记录每个玩家的数据信息，比如玩家的得分情况。
GameState：用于记录整场比赛的信息，比如比赛所处的阶段，各个队伍的人员信息等。

概括的讲，一个游戏场景是一个World，每个场景可以拆分成很多子关卡（即Level），我们可以通过配置Gamemode参数来设置游戏规则(只存在与于服务器)，在Gamestate上记录当前游戏的比赛状态和进度。对于每个玩家，我们一般至少会给他一个可以控制的的角色（即Pawn/character)，同时把这个角色相关的数据存储在Playerstate上。最后，针对每个玩家使用唯一的一个控制器Playercontroller来响应玩家的输入或者执行一些本地玩家相关的逻辑（比如设置我们的观察对象VIewTarget，会调用到Camermanager相关接口）。此外，PC是网络同步的关键，我们需要通过PC找到网络同步的中心点进而剔除不需要同步的对象，服务器也需要依靠PC才能判断不同的RPC应该发给哪个客户端。

回放系统Gameplay逻辑依然遵循UE的基础框架，但由于只涉及到数据的播放还是有不少需要注意的地方。

在一个Level里，有一些对象是默认存在的，称为StartupActor。这些对象的录制与回放可能需要特殊处理，比如回放一开始就默认创建，尽量避免动态的构造开销
UE的网络同步本身需要借助Controller定位到ViewTarget（同步中心，便于做范围剔除），所以回放录制时会创建一个新的DemoPlayerController（注意：所以在本地可能同时存在多个PC，获取PC时不要拿错了）。这个Controller的主要用途就是辅助同步逻辑，而且会被录制到回放数据里面

回放系统并不限制你的观察视角，但是会默认提供一个自由移动的观战对象（SpectatorPawn）。当我们播放时会收到同步数据并创建DemoPC，DemoPC会从GameState上查找SpectatorClass配置并生成一个用于观战的Pawn。我们通常会Possess这个对象并移动来控制摄像机的视角，当然也可以把观战视角锁定在游戏中的其他对象上。
回放不建议录制PlayerController（简称PC），游戏中的与玩家角色相关的数据也不应该放在PC上，最好放在PlayerState或者Character上面。为什么回放不处理PC？主要原因是每个客户端只有一个PC。如果我在客户端上面录制回放并且把很多重要数据放在PC上，那么当你回放的时候其他玩家PC上的数据你就无法拿到。
回放不会录制Gamemode，因为Gamemode只在服务器才有，并不做同步。

3.4.2 录制细节分析

录制Stream
TickDemoRecordFrame每一帧都会去尝试执行，是录制回放数据的关键。其核心思想就是拿到场景里面所有需要同步的Actor，进行一系列的过滤后把需要同步的数据序列化。步骤如下：

通过GetNetworkObjectList获取所有Replicated的Actor
找到当前Connection的DemoPC，决定录制中心坐标（用于剔除距离过远对象）
遍历所有同步对象，通过NextUpdateTime判断是否满足录制时间要求
通过IsDormInitialStartupActor排除休眠对象
判断相关性，包括距离判定、是不是bAlwaysRelevant等
加入PrioritizedActors进行同步前的排序
ReplicatePrioritizedActors对每个actor进行序列化
根据录制频率CVarDemoRecordHz/ CVarDemoMinRecordHz，更新下次同步时间NextUpdateTime
DemoReplicate Actor处理序列化，包括创建通道channel、属性同步等
LowLevelSend写入QueuedPacket
WriteDemoFrameFrom QueuedDemoPackets将QueuedPackets数据写入到StreamArchive
在同步每个对象时,我们可以通过CVarDemoRecordHz 和CVarDemoMinRecordHz两个参数来控制回放的录制频率，此外我们也可以通过Actor自身的NetUpdateFrequency来设置不同Actor的录制间隔。
上述的逻辑主要针对Actor的创建销毁以及属性同步，那么我们常见的RPC通信在何时录制呢？答案是在Actor执行RPC时。每次Actor调用RPC时，都会通过CallRemoteFunction来遍历所有的NetDriver触发调用，如果发现了用于回放的DemoNetdriver就会将相关的数据写到Demonet connection的QueuedPackets


bool AActor::CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack )
{
  bool bProcessed = false;
  FWorldContext* const Context = GEngine->GetWorldContextFromWorld(GetWorld());
  if (Context != nullptr)
  {
    for (FNamedNetDriver& Driver : Context->ActiveNetDrivers)
    {
      if (Driver.NetDriver != nullptr && Driver.NetDriver->ShouldReplicateFunction(this, Function))
{
        Driver.NetDriver->ProcessRemoteFunction(this, Function, Parameters, OutParms, Stack, nullptr);
        bProcessed = true;
      }
    }
  }
  return bProcessed;
}
然而在实际情况下，UDemoNetDriver重写了ShouldReplicateFunction/ ProcessRemoteFunction，默认情况下只支持录制多播类型的RPC。



为什么要这么做呢？

RPC的目的是跨端远程调用，对于非多播的RPC，他只会在某一个客户端或者服务器上面执行。也就是说，我在服务器上录制就拿不到客户端的RPC，我在客户端上录制就拿不到服务器上的RPC，总会丢失掉一些RPC。
RPC是冗余的，可能我们在回放的时候不想调用。比如服务器触发了一个ClientRPC（让客户端播放摄像机震动）并录制，那么回放的时候我作为一个观战的视角不应该调用这个RPC（当然也可以自定义的过滤掉）。
RPC是一个无状态的通知，一旦错过了就再也无法获取。回放中经常会有时间的跳转，跳转之后我们再就无法拿到前面的RPC了。如果我们过度依赖RPC做逻辑处理，就很容易出现回放表现不对的情况。
综上所述，我并不建议在支持回放系统的游戏里面频繁的使用RPC，最好使用属性同步来代替，这样也能很好的支持断线重连。



录制Checkpoint
在每帧执行TickDemoRecord时，会根据ShouldSaveCheckpoint来决定是否触发Checkpoint快照的录制，可以通过CVarCheckpointUpload DelayInSeconds命令行参数来设置其录制间隔，默认30秒。


存储Checkpoint的步骤如下：

通过GetNetworkObjectList获取所有Replicated的Actor
过滤掉PendingKill，非DemoPC等对象并排序
构建快照上下文CheckpointSaveContext，把Actor以及对应的LevelIndex放到PendingCheckpointActors数组里面
调用FReplayHelper:: TickCheckpoint，开始分帧处理快照的录制（避免快照录制造成卡顿）。实现方式是构建一个状态机，会根据当前所处的状态决定进入哪种逻辑，如果超时就会保存当前状态在下一帧执行的时候继续
第一步是ProcessCheckpoint Actors，遍历并序列化所有Actor的相关数据
进入SerializeDeleted StartupActors状态，处理那些被删掉的对象
缓存并序列化所有同步Actor的GUID
导出所有同步属性基本信息FieldExport GroupMap，用于播放时准确且能兼容地接收这些属性
通过WriteDemoFrame把所有QueuedPackets写到Checkpoint Archive里面
调用FlushCheckpoint把当前的StreamArchive和Checkpoint Archive写到目标位置（内存、本地磁盘、Http请求等）
enum class ECheckpointSaveState
{
  Idle,
  ProcessCheckpointActors,
  SerializeDeletedStartupActors,
  CacheNetGuids,
  SerializeGuidCache,
  SerializeNetFieldExportGroupMap,
  SerializeDemoFrameFromQueuedDemoPackets,
  Finalize,
};

3.4.3 播放细节分析

播放Stream：
当我们触发了PlayReplay开始回放后，每一帧都会在开始的时候尝试执行TickDemoPlayback来尝试读取并解析回放数据。与录制的逻辑相反，我们需要找到Stream数据流的起始点，然后进行反序列化的操作。步骤如下：

确保当前World没有进行关卡的切换，确保当前的比赛正在播放
尝试设置比赛的总时间SetDemoTotalTime
调用ProcessReplayTasks处理当前正在执行的任务，如果任务没有完成就返回（任务有很多种，比如FGotoTime InSecondsTask就是用来执行时间跳转的任务）
拿到StreamArchive，设置当前回放的时间（回放时间决定了当前回放数据加载的进度）
去PlaybackPackets查找是否还有待处理的数据，如果没有数据就暂停回放
ConditionallyReadDemo FrameIntoPlaybackPackets根据当前的时间，读取StreamArchive里面的数据，缓存到PlaybackPackets数组里面
ConditionallyProcess PlaybackPackets逐个去处理PlaybackPackets里面的数据，进行反序列化的操作（这一步是还原数据的关键，回放Actor的创建通常是这里触发的）
FinalizeFastForward处理快进等操作，由于我们可能在一帧的时候处理了回放N秒的数据（也就是快进），所以这里需要把被快进掉的回调函数（OnRep）都执行到，同时记录到底快进了多少时间


加载checkpoint：
在2.3.2小节，我们提到了UE的网络同步方式为增量式的状态同步，任何一刻的状态数据都是前面所有状态同步数据的叠加，所以必须从最开始播放才能保证不丢失掉中间的任何一个数据包。想要实现快进和时间跳跃必须通过加载最近的Checkpoint才能完成。

在每次开始回放前，我们可以给回放指定一个目标时间，然后回放系统就会创建一个FGotoTimeIn SecondsTask来执行时间跳跃的逻辑。基本思路是先找到附近的一个Checkpoint（快照点）加载，然后快速的读取从Checkpoint时间到目标时间的数据包进行解析。这个过程中有很多细节需要理解，比如我们从20秒跳跃到10秒的时候，20秒时刻的Actor是不是都要删除？删除之后要如何再去创建一个新的和10秒时刻一模一样的Actor？不妨带着这些问题去理解下面的流程。

FGotoTime InSecondsTask调用StartTask开始设置当前的目标时间，然后调用ReplayStreamer的GotoTimeInMS去查找要回放的数据流位置，这个时候暂停回放的逻辑
查找到回放数据流后，调用UDemoNetDriver:: LoadCheckpoint开始加载快照存储点
反序列化Level的Index，如果当前的Level与Index标记的Level不同，需要把Actor删掉然后无缝加载目标的Level
把一些重要的Actor设置成同步立刻处理AddNonQueued ActorForScrubbing，其他不重要的Actor同步数据可以排队慢慢的处理（备注：由于在回放的时候可能会立刻收到大量的数据，如果全部在一帧进行反序列并生成Actor就会导致严重的卡顿。所以我们可以通过AddNonQueued ActorForScrubbing/ AddNonQueued GUIDForScrubbing设置是否延迟处理这些Actor对应的二进制数据）
删除掉所有非StartUp（StartUp：一开始摆在场景里的）的Actor，StartUp根据情况选择性删除（在跳转进度的时候，整个场景的Actor可能已经完全不一样了，所以最好全部删除，对于摆在场景里面的可破坏墙，如果没有发生过变化可以无需处理，如果被打坏了则需要删除重新创建）
删除粒子
重新创建连接ServerConnection，清除旧的Connection关联信息（虽然我们在刚开始播放的时候创建了，但是为了在跳跃的时候清理掉Connection关联的信息，最好把彻底的把原来connection以及引用的对象GC掉）
如果没有找到CheckpointArchive（比如说游戏只有10s，Checkpoint每30秒才录制一个，加载5s数据的时候就取不到CheckpointArchive）
反序列化Checkpoint的时间、关卡信息等内容，将CheckpointArchive里面的回放数据读取到FPlaybackPacket数组
重新创建那些被删掉的StartUp对象
获取最后一个数据包的时间用作当前的回放时间，然后根据跳跃的时长设置最终的目标时间（备注：比如目标时间是35秒，Checkpoint数据包里面最一个包的时间是30.01秒。那么还需要快进跳跃5秒，最终时间是35.01秒，这个时间必须非常精确）
解析FPlaybackPacket，反序列所有的Actor数据
加载完Checkpoint之后，接下来的一帧TickDemoPlayback会快速的读取数据直到追上目标时间。同时处理一下加载Checkpoint Actor的回调函数
回放流程继续，TickDemoPlayback开始每帧读取StreamArchive里面的数据并进行反序列化
Checkpoint的加载逻辑里面，既包含了时间跳转，也涵盖了快进的功能，只不过这个快进速度比较快，是在一帧内完成的。
除此之外，我们还提到了回放的暂停。其实暂停分为两种，一种是暂停回放数据的录制/读取，通过UDemoNetDriver:: PauseRecording可以实现暂停回放的录制，通过PauseChannels可以暂停回放所有Actor的表现逻辑（一般是在加载Checkpoint、快进、没有数据读取时自动调用），但是不会停止Tick等逻辑执行。另一种暂停是暂停Tick更新（也可以用于非回放世界），通过AWorldSetting:: SetPauserPlayerState实现，这种暂停不仅会停止回放数据包的读取，还会停止WorldTick的更新，包括动画、移动、粒子等，是严格意义上的暂停。

//这里会检查GetPauserPlayerState是否为空
bool UWorld::IsPaused() const
{
  // pause if specifically set or if we're waiting for the end of the tick to perform streaming level loads (so actors don't fall through the world in the meantime, etc)
  const AWorldSettings* Info = GetWorldSettings(/*bCheckStreamingPersistent=*/false, /*bChecked=*/false);
  return ( (Info && Info->GetPauserPlayerState() != nullptr && TimeSeconds >= PauseDelay) ||
        (bRequestedBlockOnAsyncLoading && GetNetMode() == NM_Client) ||
        (GEngine->ShouldCommitPendingMapChange(this)) ||
        (IsPlayInEditor() && bDebugPauseExecution) );
}

//void UWorld::Tick( ELevelTick TickType, float DeltaSeconds ) 
bool bDoingActorTicks = 
    (TickType!=LEVELTICK_TimeOnly)
    &&  !bIsPaused
    &&  (!NetDriver || !NetDriver->ServerConnection || NetDriver->ServerConnection->State==USOCK_Open);
3.5 回放系统的跨版本兼容
3.5.1 回放兼容性的意义

回放的录制和播放往往不是一个时机，玩家可能下载了回放后过了几天才想起来观看，甚至还会用已经升级到5.0的游戏版本去播放1.0时下载的回放数据。因此，我们需要有一个机制来尽可能的兼容过去一段时间游戏版本的回放数据。

先抛出问题，为什么不同版本的游戏回放不好做兼容？


答：因为代码在迭代的时候，函数流程、数据格式、类的成员等都会发生变化（增加、删除、修改），游戏逻辑是必须要依赖这些内容才能正确执行。举个例子，假如1.0版本的代码中类ACharacter上有一个成员变量FString CurrentSkillName记录了游戏角色当前的技能名字，在2.0版本的代码时我们把这个成员删掉了。由于在1.0版本录制的数据里面存储了CurrentSkillName，我们在使用2.0版本代码执行的时候必须得想办法绕过这个成员，因为这个值在当前版本里面没有任何意义，强行使用的话可能造成回放正常的数据被覆盖掉。

其实不只是回放，我们日常在使用编辑器等工具时，只要同时涉及到对象的序列化（通用点来讲是固定格式的数据存储）以及版本迭代就一定会遇到类似的问题，轻则导致引擎资源无效重则发生崩溃。



3.5.2 虚幻引擎的回放兼容方案

在UE的回放系统里面，兼容性的问题还要更复杂一些，因为涉及到了虚幻网络同步的实现原理。

第一节我们谈到了虚幻有属性同步和RPC两种同步方式，且二者都是基于Actor来实现的。在每个Actor同步的时候，我们会给每个类创建一个FClassNetCache用于唯一标识并缓存他的同步属性，每个同步属性/RPC函数也会被唯一标识并缓存其相关数据在FFieldNetCache结构里面。由于同一份版本的客户端代码和服务器代码相同，我们就可以保证客户端与服务器每个类的FClassNetCache以及每个属性的FFieldNetCache都是相同的。这样在同步的时候我们只需要在服务器上序列化属性的Index就可以在客户端反序列化的时候通过Index找到对应的属性。


这种方案的实现前提是客户端与服务器的代码必须是一个版本的。假如客户端的类成员与服务器对应的类成员不同，那么这个Index在客户端上所代表的成员就与服务器上的不一致，最终的执行结果就是错误的。所以对于正常的游戏来说，我们必须要保持客户端与服务器版本相同。但是对于回放这种可能跨版本执行的情况就需要有一个新的兼容方案。

思路其实也很简单，就是在录制回放数据的时候，把这个Index换成一个属性的唯一标识符（标识ID），同时把回放中所有可能用到的属性标识ID的相关信息（FNetFieldExport）全部发送过去。


通过下图的代码可以看到，同样是序列化属性的标识信息，当这个Connection是InteralACk时（即一个完全可靠不会丢包的连接，目前只有回放里面的DemonetConnection符合条件），就会序列化这个属性的唯一标识符NetFieldExportHandle。


虽然这种方式增加了同步的开销和成本，但对于回放系统来说是可以接受的，而且回放的整个录制过程中是完全可靠的，不会由于丢包而发生播放时导出数据没收到的情况。这样即使我新版本的对象属性数量发生变化（比如顺序发生变化），由于我在回放数据里面已经存储了这个对象所有会被序列化的属性信息，我一定能找到对应的同步属性，而对于已经被删掉的属性，我回放时本地代码创建的FClassNetCache不包含它，因此也不会被应用进来。


&gt;&gt;发送NetFieldExports信息
从调用流程来说，兼容性的属性序列化走的接口是SendProperties_ BackwardsCompatible_r /ReceiveProperties_ BackwardsCompatible_r，会把属性在NetFieldExports里面标识符一并发送。而常规的属性同步序列化走的接口是SendProperties_r/ReceiveProperties_r，直接序列化属性的Index以及内容，不使用NetFieldExports相关结构。


到这里，我们基本上可以理解虚幻引擎对回放系统的向后兼容性案。然而即使有了上面的方案，我们其实也只是兼容了类成员发生改变的情况，保证了不会由于属性丢失而出现逻辑的错误执行。但是对于新增的属性，由于原来存储的回放文件里面根本不存在这个数据，回放的时候是完全不会有任何相关的逻辑的。因此，所谓回放系统的兼容也只是有一定限制的兼容，想很好地支持版本差异过大的回放文件还是相对困难许多的。

四、死亡回放/精彩镜头功能的实现
在FPS游戏里，一个角色被击杀之后，往往会以敌方的视角回放本角色被定位、瞄准、射击的过程，这就是我们常提到的死亡回放（DeathCameraReplay）。类似的，我们在各种体育游戏里面经常需要在一次得分后展示精彩瞬间，这种功能一般称为精彩镜头。


上一节案例使用的是基于本地文件存储的回放系统，每次播放时都需要重新加载地图。那有没有办法实现类似实况足球的实时精彩回放呢？有的，那就是基于DuplicatedLevelCollection和内存数据流的回放方案。

思考一下，通常射击游戏里的击杀镜头、体育竞技里的精彩时刻对回放的基本需求是什么？这类回放功能往往是在某个时间点可以无感知的立刻切换到回放镜头，并在回放结束后迅速的再切换到正常的游戏环境。同时，考虑到联机的情况，我们在回放时要保持游戏世界的正常运转，从而确保不错过任何服务器的同步信息，不影响其他玩家。

简单总结就是，

可以迅速的在真实游戏与回放镜头间切换
回放的时候不会影响真实游戏里面的逻辑变化
4.1 回放场景与真实场景分离
为了实现上述的要求，我们需要将回放的场景和真实的场景进行分离，在不重新加载地图的情况下快速地进行切换。虚幻引擎给出的方案是对游戏世界World进行进一步的拆分，把所有的Level组织到了三个LevelCollection里面，分别是

DynamicSourceLevels，存储真实世界的所有标记为Dynamic的Level（包含里面的所有Actor）
StaticLevels，存储了静态的actor，也就是回放过程中不会发生变化的对象，通常指那些不可破坏建筑（通过关卡编辑器里面的Static选项，可以设置任何一个SubLevel是属于DynamicSourceLevels还是StaticLevels的，PersistLevel永远是Dynamic的）
DynamicDuplicatedLevels，回放世界的Level（包含里面的所有Actor），会把DynamicSourceLevels里面的所有Level都复制一遍




在游戏地图Loading的时候，我们就会把这三种LevelCollection全部构建并加载进来（可以通过Experimental_ShouldPreDuplicateMap来决定某张地图是否可以复制Level到DynamicDuplicatedLevels），这样在进行回放的时候我们只要控制LevelCollection的显示和隐藏就可以瞬间对真实世界和回放世界进行切换了。


判断一个对象是否处于回放世界（DynamicDuplicatedLevels）也很简单

UWorld* World = WorldContextObject->GetWorld();
ULevel* Level = Cast<ULevel>(WorldContextObject->GetTypedOuter<ULevel>());
if (World && Level)
{
  FLevelCollection* const DuplicateCollection = World->FindCollectionByType(ELevelCollectionType::DynamicDuplicatedLevels);
  if (DuplicateCollection)
  {
    for (auto& TempLevel : DuplicateCollection->GetLevels())
    {
      if (TempLevel == Level)
      {
        return true;
      }
    }
  }
}
要注意的是，由于LevelCollection的引入，原来很多逻辑都变得复杂了。

不同LevelCollection的Tick是有先后顺序的，默认情况下是按照他们在数组的排列顺序DynamicSourceLevels-> StaticLevels-> DynamicDuplicatedLevels，这个顺序可能影响我们的代码逻辑或者摄像机更新时机
回放世界DynamicDuplicatedLevels里面也会有很多Actor，如果不加处理的话很有可能也被录制到回放系统中，造成嵌套录制
当一个DynamicDuplicatedLevels执行Tick的时候，会通过FScopedLevelCollectionContextSwitch来切换当前的ActiveCollection，进而修改当前World的GameState等指针，所以在回放时需要注意获取对象的正确性。（比如下图获取PC的迭代器接口，在DuplicatedLevels Tick时只能获取到回放世界的PC）
用于回放的UDemoNetDriver会绑定一个LevelCollection（通过传入PlayReplay的参数LevelPrefixOverride来决定）。当触发回放逻辑后，即UDemoNetDriver::TickDispatch每帧解析回放数据时，我们也会通过FScopedLevelCollectionContextSwitch主动切换到当前DemoNetDriver绑定的LevelCollection，保证解析回放数据时可以通过Outer找到回放场景（DynamicDuplicatedLevels）

////3/////
FScopedLevelCollectionContextSwitch::FScopedLevelCollectionContextSwitch(const FLevelCollection* const InLevelCollection, UWorld* const InWorld)
{
  if (World)
  {
    const int32 FoundIndex = World->GetLevelCollections().IndexOfByPredicate([InLevelCollection](const FLevelCollection& Collection)
    {
      return &Collection == InLevelCollection;
    });
    World->SetActiveLevelCollection(FoundIndex);
  }
}
void UWorld::SetActiveLevelCollection(int32 LevelCollectionIndex)
{
  ActiveLevelCollectionIndex = LevelCollectionIndex;
  const FLevelCollection* const ActiveLevelCollection = GetActiveLevelCollection();
  if (ActiveLevelCollection == nullptr)
  {
    return;
  }
  PersistentLevel = ActiveLevelCollection->GetPersistentLevel();
  GameState = ActiveLevelCollection->GetGameState();
  NetDriver = ActiveLevelCollection->GetNetDriver();
  DemoNetDriver = ActiveLevelCollection->GetDemoNetDriver();
 }

////4////
bool UDemoNetDriver::InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error)
{
  const TCHAR* const LevelPrefixOverrideOption = ConnectURL.GetOption(TEXT("LevelPrefixOverride="), nullptr);
  if (LevelPrefixOverrideOption)
  {
    SetDuplicateLevelID(FCString::Atoi(LevelPrefixOverrideOption));
  }

  if (GetDuplicateLevelID() == -1)
  {
    // Set this driver as the demo net driver for the source level collection.
    FLevelCollection* const SourceCollection = World->FindCollectionByType(ELevelCollectionType::DynamicSourceLevels);
    if (SourceCollection)
    {
      SourceCollection->SetDemoNetDriver(this);
    }
  }
  else
  {
    // Set this driver as the demo net driver for the duplicate level collection.
    FLevelCollection* const DuplicateCollection = World->FindCollectionByType(ELevelCollectionType::DynamicDuplicatedLevels);
    if (DuplicateCollection)
    {
      DuplicateCollection->SetDemoNetDriver(this);
    }
    }
  }
4.2 回放录制与播放分离
考虑到在死亡回放的时候不会影响正常比赛的进行和录制，所以我们通常也需要讲录制逻辑与播放逻辑完全分离。

简单来说，就是创建两个不同的Demonetdriver，一个用于回放的录制，另一个用于回放的播放。在游戏一开始的时候，就创建一个DemonetdriverA来开始录制游戏，当角色死亡触发回放的时候，这时候创建一个新的DemonetdriverB来进行回放数据的读取并播放，整个过程中DemonetdriverA一直在处于录制状态，不会受到任何影响。（需要我们手动重写GameInstance::PlayReplay函数，因为默认的逻辑每次创建一个新的Demonetdriver就会删掉原来的那个）


4.3 基于内存的回放数据流
当然，想要实现真正的快速切换，只将回放场景与真实世界的分离还不够，我们还需要保证回放数据的加载也能达到毫秒级别？所以这个时候就不能再使用前面提到的LocalFileNetworkReplayStreamer把数据放到磁盘上，正确的方案是采用基于内存数据流的ReplayStreamer来加快回放数据的读取。下面是InMemoryNetworkReplayStreamer对回放数据的组织方式，每帧的数据流会根据时间分段存储在StreamChunks里面，而不同时间点的快照则会存储在Checkpoints数组里面。对于射击游戏，我们通常会在比赛一开始就执行录制，录制的数据会不断写到下面的结构里面并在整场比赛中一直保存着，当玩家被击杀后就可以立刻从这里取出数据来进行回放。


//基于内存回放
TArray<FString> AdditionalOptions;
AdditionalOptions.Add(TEXT("ReplayStreamerOverride=InMemoryNetworkReplayStreaming"));
GameInstance->StartRecordingReplay("MyTestReplay", "MyTestReplay", Options);
//GameInstance->PlayReplay("MyTestReplay", GetWorld(), AdditionalOptions);

//MyProject.build.cs
DynamicallyLoadedModuleNames.AddRange(
    new string[] {
        "NetworkReplayStreaming",
        //"LocalFileNetworkReplayStreaming",可选，按需配置加载
        "InMemoryNetworkReplayStreaming",
        //"HttpNetworkReplayStreaming"
    }
);

关于死亡回放/精彩镜头其实还有很多细节问题，这里列举一些（最后一节会给出一些建议）：

引擎编辑器里面默认不支持DynamicDuplicatedLevels的创建，所以在不改源码的情况下无法在编辑器里面实现死亡回放功能。
回放世界与真实世界都是存在的，可以通过SetVisible来处理渲染，但是回放世界的物理怎么控制？
回放世界默认情况下不会复制Controller（容易和本地的Controller发生冲突），所以很多相关的接口都不能使用
由于不同Collection的Tick更新时机不同，但是Controller只有一个，所以回放的时候要注意Controller的更新时机
默认的录制逻辑都是在本地客户端实现的，可能对客户端有一定的性能影响
更多细节建议到GitHub参考虚幻竞技场的源码
https://github.com/EpicGames/UnrealTournament
五、Livematch观战系统
在CSGO、Dota、堡垒之夜等游戏里，都支持玩家观战的功能，即玩家可以通过客户端直接进入到某个正在进行的比赛的场景里进行实时观战。不过一般情况下并不是严格意义上的完全实时，通常根据情况会有一定程度的延迟。

实现该功能的一个简易方案就是让观战的玩家作为一个客户端连接进去，然后实时的接受服务器同步数据来进行观战。这种方式既简单，效果也好，但是问题也非常致命——观战的玩家可能会影响正常服务器性能，无法很好的支持大量的玩家进入。


所以大部分的游戏实现的都是另一种方案，即基于Webserver和回放的观战系统。这种方案的思路如下图，首先我们需要专门搭建一个用于处理回放数据的WebServer，源源不断的接收来自GameServer的回放录制数据。然后客户端在请求观战时不会去连接GameServer，而是直接通过Http请求当前需要播放的回放数据，从WebServer拿到数据后再进行本地的解析与播放。虽然会有一定的延迟，但是理想情况下效果和直接连入战斗服观战是一样的。


前面我们提到过基于Httpstream的数据流，正是为这种方案而实现的。去仔细的看一下FHttpNetworkReplayStreamer的接口实现，都是通过Http协议对回放数据进行封装而后通过固定的格式来发给WebServer的（格式可以按照需求修改，和WebServer的代码要事先规定统一）。

// FHttpNetworkReplayStreamer::StartStreaming 
// 开始下载时会发送一个特定的Http请求
const FString URL = FString::Printf(TEXT("%sreplay/%s/startDownloading?user=%s"), *ServerURL, *SessionName, *UserName);
HttpRequest->SetURL(URL);
HttpRequest->SetVerb(TEXT("POST"));
HttpRequest->OnProcessRequestComplete().BindRaw(this, &FHttpNetworkReplayStreamer::HttpStartDownloadingFinished);
// Add the request to start downloading
AddRequestToQueue(EQueuedHttpRequestType::StartDownloading, HttpRequest);
六、性能优化/使用建议
前面我们花了大量的篇幅，由浅入深的讲解了回放系统的概念以及原理，而后又对两个具体的实践案例（死亡回放、观战系统）做了进一步的分析，希望这样可以帮助大家更好的理解UE乃至其他游戏里面回放系统的思想思路。

文章的最后，我会根据个人经验给大家分享一些使用建议：

如果想创建自定义的DemonetDriver，需要在配置文件里面
//DefaultEngine.ini MyTestRec为项目名称
[/Script/Engine.Engine]
!NetDriverDefinitions=ClearArray
NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="/Script/OnlineSubsystemUtils.IpNetDriver",DriverClassNameFallback="/Script/OnlineSubsystemUtils.IpNetDriver")
+NetDriverDefinitions=(DefName="DemoNetDriver",DriverClassName="/Script/MyTestRec.MyTestRecDemoNetDriver",DriverClassNameFallback="/Script/MyTestRec.MyTestRecDemoNetDriver")

[/Script/Engine.DemoNetDriver]
NetConnectionClassName="/Script/Engine.DemoNetConnection"
DemoSpectatorClass="/Script/MyTestRec.MyTestRecSpectatorPC"
回放的录制既可以在客户端也可以在服务器
在回放中同步Controller要慎重，如果是在客户端录制回放数据最好不要同步Controller，因此玩家相关同步数据也最好不要放在Controller里面（PS代替）
RPC由于没有状态，所以很容易在回放里面丢失掉，对于有持续状态的同步效果（比如播放一个比较长的动画、道具的显示隐藏等），不要用RPC做同步（改为属性同步）。总的来说，整个项目代码里面都要克制地使用RPC。
死亡回放涉及到Level的拷贝，这回明显的增大游戏的内存使用，对于那些在回放中不会发生变化的物体（比如staticmesh的墙体），一定要放置到StaticLevels里面。
播放回放时会预先多加载5秒左右的数据（MAX_PLAYBACK_ BUFFER_SECONDS），在观战系统里面要注意这个间隔，如果Http发送不及时就很容易造成卡顿
回放里面很多NetStartActor的逻辑都是通过资源路径来定位的，使用不当很容易造成一些资源引用、垃圾回收以及资源查找的问题。举个例子，比如我们删除了一个NetStartActor对象（已经标记为Pendingkill了），但是通过StaticFindObject我们仍然能查到这个对象，这时候如果再拿这个路径去生成Actor就会报错并提示场景里面已经有一个一模一样的Actor了。
Checkpoint的加载可能会造成性能问题，可以考虑分帧去处理
回放有很多加载和生成对象的逻辑，很容易造成卡顿，建议项目内自己维护一个对象池来优化
死亡回放结束的时候一定要及时的清理回放数据，否则可能造成内存的持续增加，也可能造成一些残留的Actor对功能造成影响
回放世界和真实世界是同一个物理场景，需要避免碰撞
尽量避免在回放世界打开物理
通过设置PxFilterFlags并修改引擎的碰撞规则处理
序列化的操作要注意很多细节，比如结尾处是不是一个完整的字节。很多奇怪的Check在网络部分的崩溃八成都是序列化反序列化没有匹配造成的
临时拷贝尽量使用全局static，对于较大的数据，一定要压缩，效果明显
</code></pre>
</details>

