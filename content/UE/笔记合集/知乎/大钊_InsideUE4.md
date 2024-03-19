
<details>
<summary>目录</summary>
<pre><code>
    https://zhuanlan.zhihu.com/p/22813908?refer=insideue4
    UE4无疑是非常优秀的世界上最顶尖的引擎之一，性能和效果都非常出众，编辑器工作流也非常的出色，更难得宝贵的是完全的开源让我们有机会去从中吸取营养，学习世界上第一流游戏引擎的架构思想。
    本系列教程《InsideUE4》，希望从最最底层的C++源码剖析，到最最上层的蓝图节点，力求解释清楚各个选项的内部运作机理。希望做到知其然，而更要知其所以然。UE4也是一个非常博大精深的引擎，分析透彻各个具体模块的运作机理无疑也是个艰巨的任务，因此书写周期不定，尽量周更。
    计划（顺序不定）
    开篇
    基本概念
    GamePlay架构
    Actor 和 Component
    Level和World
    WorldContext，GameInstance，Engine
    Pawn
    Controller
    PlayerController和AIController
    GameMode和GameState
    Player
    GameInstance
    总结
    Subsystems
    UObject （当前正在写作中……）
    开篇
    类型系统概述
    类型系统设定和结构
    类型系统代码生成
    类型系统信息收集
    类型系统代码生成重构-UE4CodeGen_Private
    类型系统注册-第一个UClass
    类型系统注册-CoreUObject模块加载
    类型系统注册-InitUObject
    类型系统构造-再次触发
    类型系统构造-构造绑定链接
    类型系统-总结
    类型系统-反射实战
    加载启动
    模块机制
    独立
    编辑器
    客户端
    服务器
    编译系统
    链接第三方库
    Game
    Plugin
    反射 UObject
    UBT,UHT
    蓝图系统
    编译
    加载
    调用
    网络
    加入，事件
    物理
    碰撞处理，Overlap，Hit
    布料
    破坏
    UI
    Slate，UMG
    渲染
    流程
    Viewport
    相机管理，CameraManager
    灯光，烘培
    材质
    PostProcess
    模块
    输入事件
    骨骼动画，融合
    Matinee,Cinematics
    粒子系统
    音频
    AI,行为树，环境探测
    地形
    视频
    Log
    Profile
    本地化
    统计
    Paper2D
    资源管理
    加载机制
    uasset文件分析
    Level Streaming
    导入
    打包
    C++
    字符串处理FString
    Delegate
    GC
    序列化
    SlowTask多线程
    VR
    配置，头显
    扩展
    资源更新
    HotReload
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》开篇</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/22814051?refer=gameengine
前言
VR行业发展是越来越火热了，硬件设备上有HTC VIVE，Oculus rift，PS VR，各种魔镜；平台上有Steam VR，Gear VR，Google Daydream。而游戏引擎上则有两大阵营：Unreal Engine和Unity。Unity凭着先期的移动平台优势占领了一大部分移动平台的市场，所以目前上手机上的VR游戏也大部分是由Unity开发的。而PC平台上，Unreal Engine凭借着优异的性能，绚丽的渲染效果，源码开源的战略也抢占了目前大部分PC平台VR游戏的份额。参加一场ChinaJoy的VR游戏，会发现大部分也都是由UE4开发的。虽然UE4的授权分成费确实比Unity要昂贵一些，但也因为VR行业本身也还处以社会主义初级阶段，大家也都是在做Demo性质的产品，还没有形成非常客观的市场利润市场。所以盈利后的那些分成费在现阶段已经不太有所谓了。
大名鼎鼎的的虚幻引擎，从1998开始，到我们知道的UE3,UDK，一直是高大上的3A游戏和端游的渲染器引擎。然后到2013年，UE4大刀阔斧的改革，干掉了UnrealScript，引进了Blueprint蓝图系统，直接让策划美术也可以拖线实现游戏逻辑。更大的改变的是竟然开源了，受益于社区的回馈，版本更新的速度更是丧心病狂。小版本更新几乎是一两个月就一版。在学习了Unity的Marketplace和插件系统后，更是如虎添翼，焕发了新的生命力。
虽然官方一直非常努力的升级更新引擎，但UE4目前也存在了学习曲线陡峭，教程资源稀少的问题。笔者自己从事VR游戏开发，在学习UE4的过程中，基本上也只能硬啃官方文档，youtube上官方视频教程，还有一些寥寥的第三方的视频教程。而且更大的问题在于基本上所有的教程都是非常初级的，只是在教你怎么”用”这个引擎，所以一旦在使用过程中发现了问题，往往手足无措，不能高层建瓴的去解决问题。官方的文档虽然说已经挺详尽了，但大部分重点也只是在介绍表层的各种功能，对于引擎内部的结构和运作机理讳莫如深。如果把UE4当作Unity那样的一个黑盒子去用，在遇到Bug时也只能去各种试各种猜，那也无疑浪费了UE的一个大优势。
UE4无疑是非常优秀的世界上最顶尖的引擎之一，性能和效果都非常出众，编辑器工作流也非常的出色，更难得宝贵的是完全的开源让我们有机会去从中吸取营养，学习世界上第一流游戏引擎的架构思想。
源码面前，了无秘密 ——侯捷
所以笔者决定开始该系列教程《Inside UE4》，从最最底层的C++源码剖析，到最最上层的蓝图节点，力求解释清楚各个选项的内部运作机理。希望做到知其然，而更要知其所以然。UE4也是一个非常博大精深的引擎，光源码下载下来也都有1~2G，分析透彻各个具体模块的运作机理无疑也是个艰巨的任务，但我们努力一分也至少有一分的收获，有一分的甜蜜。
面向的读者：
不满足于目前世面上教程深度的。已经大概知道了引擎功能并使用，但是仍然想要知道得更多的人。
有一定的C++基础。UE4里的C++已经被Epic给魔改后又和C#厮混在一起，一方面得益于此，UE4里的C++实现了各种方便的功能，如反射，垃圾回收，编译系统等重量级的功能。一方面也加大了我们的阅读难度。所以需要你有良好的C++基础，至少看得懂各种C++模板，熟悉各种数据结构。
有一点点的C#语言能力，在涉及UE4编译系统的时候，会谈到一些C#，还好不是很多，也还好C#作为一门非常优秀的语言非常易读，不过你要是已经掌握C#，那就更好了。
了解3D游戏引擎的一些基础概念，如知道什么是材质，什么是骨骼动画融合等。所幸这些都是很容易知道的知识。
有一些基本的图形学知识，知道Mesh,Shader,RenderTarget……等等一些基本的概念。本教程在开始某个专题的时候，会简单讲解一下背景知识，但它不会变成基础图形学教程。
不适合的读者：
希望通过该教程学习快速上手UE4引擎的人，不适合你。目前快速上手UE4的最佳途径依然是官方文档和视频教程。
希望学习然后自己搭建具体游戏的，如FPS，VR游戏，样板间等。本系列教程不会教你从零开始搭建一个游戏示例，虽然会讲解VR的各种配置的内部机制原理。
希望学习某个模块具体案例的，如用材质编辑器实现各种效果。本教程会透彻分析材质编辑器内部的实现机制，也会讲解各个材质节点的功能和原理，有时也会看需要通过一些非常直接简单的示例来讲解。但目标从来都是讲解原理，而不是实现结果。
愿景和计划
从C++源码层次上分析整个游戏引擎的架构。了解清楚各个模块之间是怎么协作的，如果有闲情雅致，也甚至会具体到谈一谈某个很小的点为何这么设计。如UE4里的Delegate，Pointers，TArray等。
虽然源码剖析本来就是曲线陡峭的上升，但还是希望能尽量深入浅出的讲解，所以也会尽量结合实际的效果演示。
因为UE4比较庞大，所以会逐渐的展开各个专题展开，在讲解一个专题的源码时，会暂时忽略其它跟它协作模块。
虽然UE4也可以做移动平台的开发，但本教程还是主要专注于Windows的PC端游戏内容。
计划是连载周更，虽说已经有预定的专题讲解列表计划，但并不妨碍你留言告知你最想了解的下一个专题。我会酌情改变优先级。
本人也是才疏学浅，经验有限，如有错误纰漏之处，也请不吝赐教，共同学习进步，不胜感激。
一些准备工作
UnrealEngine官方Github地址
虽说官方已经提供了简便的launcher，但还是推荐自己自己Clone源码编译，也方便时不时的Debug和查看源码知道Why。而且有些时候其实是直接更改引擎源码来得更为方便便利的。
Clone下来之后先点 Setup.bat再点 GenerateProjectFiles.bat ，然后打开UE4.sln，按照默认选项DevelopmentEditor，等待最初半个小时的编译后，就可以开始源码之旅了。
引擎版本紧跟Github最新release，目前最新4.14
注意：因为UnrealEngine只是公开源码，但不是开源项目，依然是个私有项目。访问该Github地址，需要先链接你的Github到EpicGames的会员权限里，这个文档Linking your Github account说明了步骤。
UnrealEngine官方文档
本教程也会同时大量引用官方文档的内容，在官方文档简略的介绍的基础上，通过源码加深理解，再更加透彻的解释。
UnrealEngine官方Youtube频道
UnrealEngine官方优酷频道
有条件的话，还是建议自搭梯子，youtube的视频教程更新是最快的，而且也有高清。
一块大容量的SSD，UE用source build的话，特别是想调试引擎的话，一个配置编译出来都得耗用个好几个G，一个项目的编译20~30G轻轻松松。
其他的无关的话：
之前开源过一款自研的Medusa游戏引擎，一个人毕竟精力有限，也无法开工各种编辑器工作流。所以Medusa引擎目前只是作为自己的一个试验场，未来也会专注于2D游戏的一些探索。关于Medusa游戏引擎的内部架构，其实想讲的也挺多，希望以后在UE4的相关介绍后，得空顺便讲一些其他游戏引擎的架构思想，和C++的一些奇技淫巧。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》基础概念</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/22814098
创建测试项目
接上文的准备工作，双击生成的UE4Editor.exe，选择创建测试C++空项目Hello（以后的源码分析都会基于该最简单的项目）
项目文件结构
VS项目和文件目录：
可以看到，Config目录里带着3个最主要的配置，Editor,Engine,Game。代码方面自动生成了用于编译系统的3个.cs文件，C++代码方面生成了一个Hello "Game Module"，和HelloGameMode。
文件目录：
Binaries:存放编译生成的结果二进制文件。该目录可以gitignore,反正每次都会生成。
Config:配置文件。
Content:平常最常用到，所有的资源和蓝图等都放在该目录里。
DerivedDataCache：“DDC”，存储着引擎针对平台特化后的资源版本。比如同一个图片，针对不同的平台有不同的适合格式，这个时候就可以在不动原始的uasset的基础上，比较轻易的再生成不同格式资源版本。gitignore。
Intermediate：中间文件（gitignore），存放着一些临时生成的文件。有：
Build的中间文件，.obj和预编译头等
UHT预处理生成的.generated.h/.cpp文件
VS.vcxproj项目文件，可通过.uproject文件生成编译生成的Shader文件。
AssetRegistryCache：Asset Registry系统的缓存文件，Asset Registry可以简单理解为一个索引了所有uasset资源头信息的注册表。CachedAssetRegistry.bin文件也是如此。
Saved：存储自动保存文件，其他配置文件，日志文件，引擎崩溃日志，硬件信息，烘培信息数据等。gitignore
Source：代码文件。
编译类型
很多人在使用UE4的时候，往往只是依照默认的DevelopmentEditor，但实际上编译选项是非常重要的。
UE4本身包含网络模式和编辑器，这意味着你的工程在部署的时候将包含Server和Client，而在开发的时候，也将有Editor和Stand-alone之分；同时你也可以单独选择是否为Engine和Game生成调试信息，接着你还可以选择是否在游戏里内嵌控制台等。
依照官方介绍
每种编译配置包含两种关键字。第一种表明了引擎以及游戏项目的状态。第二个关键字表明正在编译的目标。
组合的各种情况：
所以为了我们的调试代码方便，我们选择DebugEditor来加载游戏项目，当需要最简化流程的时候用Debug来运行独立版本。
命名约定
客观来说，相比其他引擎的源码，UE4的源码还是非常清晰的，模块组织也比较明了。但阅读源码的学习曲线依然陡峭，我想有以下原因：
1. UE4包含的模块众多，拢共有几十个模块，虽然采用了Module架构来解耦，但难免还是要有依赖交叉的地方，在阅读的时候就很难理清各部分的关系。
2. UE4的功能优秀，作为业界顶尖的成熟游戏引擎，在一些具体的模块内部实现上就脱离了简单粗暴，而是采用了各种设计模式和权衡。同时也需要阅读的人有相关的业务知识。比如材质编辑器编译生成Shader的过程就需要读者拥有至少差不多的图形学知识。
3. 被魔改后的C++，UE4为了各平台的编译和其他考量（具体以后说到编译系统的时候再细讨论），对标准的C++和编译，进行了相当程度的改造，在UHT代码生成和各种宏的嵌套之后，读者就很难一下子看清背后的各种的机制了。
但万丈高楼平地起，咱们也可以从最简单的一步步开始学起，直到了解掌握整个引擎的内部结构。
在阅读代码之前，就必须去了解一下UE4的命名约定，具体的自己去查看官网文档，下面是一些基本需要知道的：
模版类以T作为前缀，比如TArray,TMap,TSet UObject派生类都以U前缀
AActor派生类都以A前缀
SWidget派生类都以S前缀
抽象接口以I前缀
枚举以E开头
bool变量以b前缀，如bPendingDestruction
其他的大部分以F开头，如FString,FName
typedef的以原型名前缀为准，如typedef TArray FArrayOfMyTypes;
在编辑器里和C#里，类型名是去掉前缀过的
UHT在工作的时候需要你提供正确的前缀，所以虽然说是约定，但你也得必须遵守。（编译系统怎么用到那些前缀，后续再讨论）
基础概念
和其他的3D引擎一样，UE4也有其特有的描述游戏世界的概念。在UE4中，几乎所有的对象都继承于UObject（跟Java,C#一样），UObject为它们提供了基础的垃圾回收，反射，元数据，序列化等，相应的，就有各种"UClass"的派生们定义了属性和行为的数据。
跟Unity（GameObject-Component）有些像的是，UE4也采用了组件式的架构，但细品起来却又有些不一样。在UE中，3D世界是由Actors构建起来的，而Actor又拥有各种Component，之后又有各种Controller可以控制Actor（Pawn）的行为。Unity中的Prefab，在UE4中变成了BlueprintClass，其实Class的概念确实更加贴近C++的底层一些。
Unity中，你可以为一个GameObject添加一个ScriptComponent，然后继承MonoBehaviour来编写游戏逻辑。在UE4中，你也可以为一个Actor添加一个蓝图或者C++ Component,然后实现它来直接组织逻辑。 UE4也支持各种插件。
其他的下篇再一一细说。
编译系统
UE4支持众多平台，包括Windows,IOS，Android等，因此UE4为了方便你配置各个平台的参数和编译选项，简化编译流程,UE4实现了自己的一套编译系统，否则我们就得接受各个平台再单独配置一套项目之苦了。
这套工具的编译流程结果，简单来说，就是你在VS里的运行，背后会运行UE4的一些命令行工具来完成编译，其他最重要的两个组件：
UnrealBuildTool（UBT，C#）：UE4的自定义工具，来编译UE4的逐个模块并处理依赖等。我们编写的Target.cs，Build.cs都是为这个工具服务的。
UnrealHeaderTool （UHT，C++）：UE4的C++代码解析生成工具，我们在代码里写的那些宏UCLASS等和#include "*.generated.h"都为UHT提供了信息来生成相应的C++反射代码。
一般来说，UBT会先调用UHT会先负责解析一遍C++代码，生成相应其他代码。然后开始调用平台特定的编译工具(VisualStudio,LLVM)来编译各个模块。最后启动Editor或者是Game.
更细的留待“编译系统”再细细讨论
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（一）Actor和Component</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/22833151
引言
如果让你来制作一款3D游戏引擎，你会怎么设计其结构？
尽管游戏的类型有很多种，市面上也有众多的3D游戏引擎，但绝大部分游戏引擎都得解决一个基本问题：抽象模拟一个3D游戏世界。根据基本的图形学知识，我们知道，为了展示这个世界，我们需要一个个带着“变换”的“游戏对象”，接着让它们父子嵌套以表现更复杂的结构。本质上，其他的物理模拟，游戏逻辑等功能组件，最终目的也只是为了操作这些“游戏对象”。
这件事，在Unity那里就直接成了“GameObject”和“Component”；在Cocos2dx那里是一个个的“CCNode”，操纵部分直接内嵌在了CCNode里面；那么在UE4的眼中，它是怎么看待游戏的3D世界的？
创世记
UE创世，万物皆UObject，接着有Actor。
UObject:
起初，UE创世，有感于天地间C++原始之气一片混沌虚无，便撷取凝实一团C++之气，降下无边魔力，洒下秩序之光，便为这个世界生成了坚实的土壤UObject，并用UClass一一为此命名。
藉着UObject提供的元数据、反射生成、GC垃圾回收、序列化、编辑器可见，Class Default Object等，UE可以构建一个Object运行的世界。（后续会有一个大长篇深挖UObject）
Actor:
世界有了土壤之后，但还少了一些生动色彩，如果女娲造人一般，UE取一些UObject的泥巴，派生出了Actor。在UE眼中，整个世界从此了有了一个个生动的“演员”，众多的“演员”们，一起齐心协力为观众上演一场精彩的游戏。
脱胎自Object的Actor也多了一些本事：Replication（网络复制）,Spawn（生生死死），Tick(有了心跳)。
Actor无疑是UE中最重要的角色之一，组织庞大，最常见的有StaticMeshActor, CameraActor和 PlayerStartActor等。Actor之间还可以互相“嵌套”，拥有相对的“父子”关系。
思考：为何Actor不像GameObject一样自带Transform？
我们知道，如果一个对象需要在3D世界中表示，那么它必然要携带一个Transform matrix来表示其位置。关键在于，在UE看来，Actor并不只是3D中的“表示”，一些不在世界里展示的“不可见对象”也可以是Actor，如AInfo(派生类AWorldSetting,AGameMode,AGameSession,APlayerState,AGameState等)，AHUD,APlayerCameraManager等，代表了这个世界的某种信息、状态、规则。你可以把这些看作都是一个个默默工作的灵体Actor。所以，Actor的概念在UE里其实不是某种具象化的3D世界里的对象，而是世界里的种种元素，用更泛化抽象的概念来看，小到一个个地上的石头，大到整个世界的运行规则，都是Actor.
当然，你也可以说即使带着Transform，把坐标设置为原点，然后不可见不就行了？这样其实当然也是可以，不过可能因为UE跟贴近C++一些的缘故，所以设计哲学上就更偏向于C++的哲学“不为你不需要的东西付代价”。一个Transform再加上附带的逆矩阵之类的表示，内存占用上其实也是挺可观的。要知道UE可是会抠门到连bool变量都要写成uint bPending:1;位域来节省一个字节的内存的。
换一个角度讲，如果把带Transform也当成一个Actor的额外能力可以自由装卸的话，那其实也可以自圆其说。经过了UE的权衡和考虑，把Transform封装进了SceneComponent,当作RootComponent。但在权衡到使用的便利性的时候，大部分Actor其实是有Transform的，我们会经常获取设置它的坐标，如果总是得先获取一下SceneComponent，然后再调用相应接口的话，那也太繁琐了。所以UE也为了我们直接提供了一些便利性的Actor方法，如(Get/Set)ActorLocation等，其实内部都是转发到RootComponent。
/*~
 * Returns location of the RootComponent 
 * this is a template for no other reason than to delay compilation until USceneComponent is defined
 */ 
template<class T>
static FORCEINLINE FVector GetActorLocation(const T* RootComponent)
{
    return (RootComponent != nullptr) ? RootComponent->GetComponentLocation() : FVector(0.f,0.f,0.f);
}
bool AActor::SetActorLocation(const FVector& NewLocation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport)
{
    if (RootComponent)
    {
        const FVector Delta = NewLocation - GetActorLocation();
        return RootComponent->MoveComponent(Delta, GetActorQuat(), bSweep, OutSweepHitResult, MOVECOMP_NoFlags, Teleport);
    }
    else if (OutSweepHitResult)
    {
        *OutSweepHitResult = FHitResult();
    }
    return false;
}
同理，Actor能接收处理Input事件的能力，其实也是转发到内部的UInputComponent* InputComponent;同样也提供了便利方法。
Component
世界纷繁复杂，光有一种Actor可不够，自然就需要有各种不同技能的Actor各司其职。在早期的远古时代，每个Actor拥有的技能都是与生俱有，只能父传子一代代的传下去。随着游戏世界的越来越绚丽，需要的技能变得越来越多和频繁改变，这样一组合，唯出身论的Actor数量们就开始爆炸了，而且一个个也越来越胖，最后连UE这样的神也管理不了了。终于，到了第4个纪元，UE窥得一丝隔壁平行宇宙Unity的天机。下定决心，让Actor们轻装上阵，只提供一些通用的基本生存能力，而把众多的“技能”抽象成了一个个“Component”并提供组装的接口，让Actor随用随组装，把自己武装成一个个专业能手。
看见UActorComponent的U前缀，是不是想起了什么？没错，UActorComponent也是基础于UObject的一个子类，这意味着其实Component也是有UObject的那些通用功能的。（关于Actor和Component之间Tick的传递后续再细讨论）
下面我们来细细看一下Actor和Component的关系：
TSet<UActorComponent*> OwnedComponents 保存着这个Actor所拥有的所有Component,一般其中会有一个SceneComponent作为RootComponent。
TArray<UActorComponent*> InstanceComponents 保存着实例化的Components。实例化是个什么意思呢，就是你在蓝图里Details定义的Component,当这个Actor被实例化的时候，这些附属的Component也会被实例化。这其实很好理解，就像士兵手上拿着把武器，当我们拥有一队士兵的时候，自然就一一对应拥有了不同实例化的武器。但OwnedComponents里总是最全的。ReplicatedComponents，InstanceComponents可以看作一个预先的分类。
一个Actor若想可以被放进Level里，就必须实例化USceneComponent* RootComponent。但如果你光看代码的话，OwnedComponents其实也是可以包容多个不同SceneComponent的，然后你可以动态获取不同的SceneComponent来当作RootComponent，只不过这种用法确实不太自然，而且也得非常小心维护不同状态，不推荐如此用。在我们的直觉印象里，一个封装过后的Actor应该是一个整体，它能被放进Level中，拥有变换，这一整个整体的概念更加符合自然意识，所以我想，这也是UE为何要在Actor里一一对应一个RootComponent的原因。
再来说说Component下面的家族（为了阐明概念，只列出了最常见的）：
ActorComponent下面最重要的一个Component就非SceneComponent莫属了。SceneComponent提供了两大能力：一是Transform，二是SceneComponent的互相嵌套。
思考：为何ActorComponent不能互相嵌套？而在SceneComponent一级才提供嵌套？
首先，ActorComponent下面当然不是只有SceneComponent，一些UMovementComponent，AIComponent，或者是我们自己写的Component，都是会直接继承ActorComponent的。但很奇怪的是，ActorComponent却是不能嵌套的，在UE的观念里，好像只有带Transform的SceneComponent才有资格被嵌套，好像Component的互相嵌套必须和3D里的transform父子对应起来。
老实说，如果让我来设计Entity-Component模式，我很可能会为了通用性而在ActorComponent这一级直接提供嵌套，这样所有的Component就与生俱来拥有了组合其他Component的能力，灵活性大大提高。但游戏引擎的设计必然也经过了各种权衡，虽然说架构上显得并不那么的统一干净，但其实也大大减少了被误用的机会。实体组件模式推崇的“组合优于继承”的概念确实很强大，但其实同时也带来了一些问题，如Component之间如何互相依赖，如何互相通信，嵌套过深导致的接口便利损失和性能损耗，真正一个让你随便嵌套的组件模式可能会在使用上更容易出问题。
从功能上来说，UE更倾向于编写功能单一的Component（如UMovementComponent）,而不是一个整合了其他Component的大管家Component（当然如果你偏要这么干，那UE也阻止不了你）。
而从游戏逻辑的实现来说，UE也是不推荐把游戏逻辑写在Component里面，所以你其实也没什么机会去写一个很复杂的Component.
思考：Actor的SceneComponent哲学
很多其他游戏引擎，还有一种设计思路是“万物皆Node”。Node都带变换。比如说你要设计一辆汽车，一种方式是车身作为一个Node,4个轮子各为车身的子Node，然后移动父Node来前进。而在UE里，一种很可能的方式就变成，汽车是一个Actor，车身作为RootComponent，4个轮子都作为RootComponent的子SceneComponent。请读者们细细体会这二者的区别。两种方式都可以实现出优秀的游戏引擎，只是有些理念和侧重点不同。
从设计哲学上来说，其实你把万物看成是Node，或者是Component，并没有什么本质上的不同。看作Node的时候，Node你就要设计的比较轻量廉价，这样才能比较没有负担的创建多个，同理Component也是如此。Actor可以带多个SceneComponent来渲染多个Mesh实体，同样每个Node带一份Mesh再组合也可以实现出同样效果。
个人观点来说，关键的不同是在于你是怎么划分要操作的实体的粒度的。当看成是Node时，因为Node身上的一些通用功能（事件处理等），其实我们是期望着我们可以非常灵活的操作到任何一个细小的对象，我们希望整个世界的所有物体都有一些基本的功能（比如说被拾取），这有点完美主义者的思路。而注重现实的人就会觉得，整个游戏世界里，有相当大一部分对象其实是不那么动态的。比如车子，我关心的只是整体，而不是细小到每一个车轱辘。这种理念就会导成另外一种设计思路：把要操作的实体按照功能划分，而其他的就尽量只是最简单的表示。所以在UE里，其实是把5个薄薄的SceneComponent表示再用Actor功能的盒子装了起来，而在这个盒子内部你可以编写操作这5个对象的逻辑。换做是Node模式，想编写操作逻辑的话，一般就来说就会内化到父Node的内部，不免会有逻辑与表现掺杂之嫌，而如果Node要把逻辑再用组合分离开的话，其实也就转化成了某种ScriptComponent。
思考：Actor之间的父子关系是怎么确定的？
你应该已经注意到了Actor里面的TArray<AActor*> Children字段，所以你可能会期望看到Actor:AddChild之类的方法，很遗憾。在UE里，Actor之间的父子关系却是通过Component确定的。同一般的Parent:AddChild操作原语不同，UE里是通过Child:AttachToActor或Child:AttachToComponent来创建父子连接的。
void AActor::AttachToActor(AActor* ParentActor, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
    if (RootComponent && ParentActor)
    {
        USceneComponent* ParentDefaultAttachComponent = ParentActor->GetDefaultAttachComponent();
        if (ParentDefaultAttachComponent)
        {
            RootComponent->AttachToComponent(ParentDefaultAttachComponent, AttachmentRules, SocketName);
        }
    }
}
void AActor::AttachToComponent(USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
    if (RootComponent && Parent)
    {
        RootComponent->AttachToComponent(Parent, AttachmentRules, SocketName);
    }
}
3D世界里的“父子”关系，我们一般可能会认为就是3D世界里的变换的坐标空间“父子”关系，但如果再度扩展一下，如上所述，一个Actor可是可以带有多个SceneComponent的，这意味着一个Actor是可以带有多个Transform“锚点”的。创建父子时，你到底是要把当前Actor当作对方哪个SceneComponent的子？再进一步，如果你想更细控制到Attach到某个Mesh的某个Socket（关于Socket Slot，目前可以简单理解为一个虚拟插槽，提供变换锚点），你就更需要去寻找到特定的变换锚点，然后Attach的过程分别在Location,Roator,Scale上应用Rule来计算最后的位置。
/** Rules for attaching components - needs to be kept synced to EDetachmentRule */
UENUM()
enum class EAttachmentRule : uint8
{
    /** Keeps current relative transform as the relative transform to the new parent. */
    KeepRelative,
    /** Automatically calculates the relative transform such that the attached component maintains the same world transform. */
    KeepWorld,
    /** Snaps transform to the attach point */
    SnapToTarget,
};
所以Actor父子之间的“关系”其实隐含了许多数据，而这些数据都是在Component上提供的。Actor其实更像是一个容器，只提供了基本的创建销毁，网络复制，事件触发等一些逻辑性的功能，而把父子的关系维护都交给了具体的Component，所以更准确的说，其实是不同Actor的SceneComponent之间有父子关系，而Actor本身其实并不太关心。
接下来的左侧派生链依次提供了物理，材质，网格最终合成了一个我们最普通常见的StaticMeshComponent。而右侧的ChildActorComponent则是提供了Component之下再叠加Actor的能力。
聊一聊ChildActorComponent
同作为最常用到的Component之一，ChildActorComponent担负着Actor之间互相组合的胶水。这货在蓝图里静态存在的时候其实并不真正的创建Actor，而是在之后Component实例化的时候才真正创建。
void UChildActorComponent::OnRegister()
{
    Super::OnRegister();
    if (ChildActor)
    {
        if (ChildActor->GetClass() != ChildActorClass)
        {
            DestroyChildActor();
            CreateChildActor();
        }
        else
        {
            ChildActorName = ChildActor->GetFName();
            USceneComponent* ChildRoot = ChildActor->GetRootComponent();
            if (ChildRoot && ChildRoot->GetAttachParent() != this)
            {
                // attach new actor to this component
                // we can't attach in CreateChildActor since it has intermediate Mobility set up
                // causing spam with inconsistent mobility set up
                // so moving Attach to happen in Register
                ChildRoot->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            }
            // Ensure the components replication is correctly initialized
            SetIsReplicated(ChildActor->GetIsReplicated());
        }
    }
    else if (ChildActorClass)
    {
        CreateChildActor();
    }
}
void UChildActorComponent::OnComponentCreated()
{
    Super::OnComponentCreated();
    CreateChildActor();
}
这就导致了一个问题，当你把一个ActorClass拖进Level后，这个Actor实际是已经实例化了,你可以直接调整这个Actor的属性。但是你把它拖到另一个Actor Class里，它只会给你空空白白的ChildActorComponent的DetailsPanel，你想调整Actor的属性，就只能等生成了之后，用蓝图或代码去修改。这一点来说，其实还是挺不方便的，我个人觉得应该是还有优化的空间。
修订
4.14 Child Actor Templates
UE终于听到了人民群众的呼声，在4.14里增加了Child Actor Templates来支持在子ChildActor的DetailsPannel里查看和修改属性。
/** The class of Actor to spawn */
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=ChildActorComponent, meta=(OnlyPlaceable, AllowPrivateAccess="true", ForceRebuildProperty="ChildActorTemplate"))
TSubclassOf<AActor>	ChildActorClass;
/** The actor that we spawned and own */
UPROPERTY(Replicated, BlueprintReadOnly, Category=ChildActorComponent, TextExportTransient, NonPIEDuplicateTransient, meta=(AllowPrivateAccess="true"))
TObjectPtr<AActor>	ChildActor;
/** Property to point to the template child actor for details panel purposes */
UPROPERTY(VisibleDefaultsOnly, DuplicateTransient, Category=ChildActorComponent, meta=(ShowInnerProperties))
TObjectPtr<AActor> ChildActorTemplate;
最新的UE代码里已经提供了ChildActorTemplate这个对象，来为ChildActorClass生成一个Actor模板，方便我们编辑属性，之后在生成ChildActor的时候，可以把ChildActorTemplate身上的属性拷贝给ChildActor，这样运作看起来就像生成了你配置的那个Actor，也比较流畅自然了。
后记
花了这么多篇幅，才刚刚讲到Actor和Component这两个最基本的整体设计，而关于Actor,Component生命周期，Tick，事件传递等机制性的问题，还都没有展开。UE作为从1代至今4代，久经磨练的一款成熟引擎，GamePlay框架部分其实也就不到十个类，而这些类之间怎么组织，为啥这么设计，有什么权衡和考虑，我相信这里面其实是非常有讲究的。如果是UE的总架构师来讲解的话，肯定能有非常多的心得体会故事。而我们作为学习者，也应该尽量去体会琢磨它的用心，一方面磨练我们自己的架构设计能力，一方面也让我们更能掌握这个游戏的引擎。
从此篇开始，会循序渐进的探讨各个部分的结构设计，最后再从整体的框架上讨论该结构的优劣点。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（二）Level和World</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/22924838
引言
上文谈到Actor和Component的关系，UE利用Actor的概念组成一片游戏对象森林，并利用Component组装扩展Actor的能力，让世界里拥有了形形色色的Actor们，拥有了自由表达3D世界的能力。
那么，这些Actor们，到底是怎么组织起来的呢？
既然提到了世界，我们的直觉反应是采用一个"World"对象来包容所有的Actor们。但是当游戏的虚拟世界非常巨大时，这种方式就捉襟见肘了。首先，目前虽然PC的性能日益强大，但是依然内存也限制了不能一下子加载进所有的游戏资源；其次，因为玩家的活动和可见范围有限，为了最优性能，把即使是很远的跟玩家无关的对象也考虑进来也明显是不明智的。所以我们需要一种更细粒度的概念来划分世界。
不同的游戏引擎们，看待这个过程的角度和理念也不一样。Cocos2dx会认为游戏世界是由Scene组成的，Scene再由一个个Layer层叠表现，然后再有一个Director来导演整个游戏。Unity觉得世界也是由Scene组成的，然后一个Application来扮演上帝来LoadLevel，后来换成了SceneManager。其他的，有的会称为关卡（Level）或地图（map）等等。而UE中把这种拆分叫做关卡（Level），由一个或多个Level组成一个World。
不要觉得这种划分好像很随意，只是个名字不同而已。实际上一个游戏引擎的“世界观”关系到了一整串后续的内容组织，玩家的管理，世界的生成，变换和毁灭。游戏引擎内部的资源的加载释放也往往都是和这种划分（Level）绑定在一起的。
Level
在UE的世界中，我们之前已经有了空气（C++）,土壤（UObject），物件（Actor）。而现在UE又施展神力创建了一片片大陆（Level），在这片大陆上（.map文件），Actor们秩序井然，各种地形拔地而起，植被繁茂，天空雾云缭绕，圣光普照，这也是玩家们降生开始精彩冒险的地方。
可以从ULevel的前缀U看出来Level（大陆）也确实是继承于UObject（土壤）的。那既然同属于Object下面的各Actor们都拥有了一定的智能能力（支持蓝图脚本），Level自然也得体现出大地的意志，所以默认带了一个土地公（ALevelScriptActor），允许我们在关卡里编写脚本，可以对本关卡里的所有Actor通过名字呼之则来，关卡蓝图实际上就代表着该片大陆上的运行规则。
在Level已经有了管理者之后，一开始大家都挺满意，但渐渐的就发现，好像各个Level需要的功能好像都差不多，都是修改一下光照，物理等一些属性。所以为了方便起见，UE便给每一个Level也都默认配了一个书记官（Info），他一一记录着本Level的各种规则属性，在UE需要的时候便负责相告。更重要的是，在Level需要有其他管理人员一起协助的时候，他也记录着“游戏模式”的名字来让UE可以指派。
前面我们说过，有一些Actor是不“显示”的（没有SceneComponent），是不能“摆放”到Level里的，但是它依然可以在关卡里出力。其中一个家族系列就是AInfo和其之类。今天我们只简单介绍一下跟Level直接相关的一位书记官：AWorldSettings。
其实虽然名字叫做WorldSettings，但其实只是跟Level相关，我猜可能是在上古时代，当时整个世界只有一块大陆，人们就以为当前的大陆就是整个世界，所以给这块大陆的设置就起名为WorldSettings，后来等技术进步了，发现必须有其他大陆了，这个名字已经用得太多反而不好改了，就只好遗留下来了。当然也有可能是因为当Level被添加进World后，这个Level的Settings如果是主PersistentLevel，那它就会被当作整个World的WorldSettings。
注意，Actors里也保存着AWorldSettings和ALevelScriptActor的指针，所以Actors实际上确实是保存了所有Actor。
思考：为何AWorldSettings要放进在Actors[0]的位置？而ALevelScriptActor却不用？
void ULevel::SortActorList()
{
    //[...]
    TArray<AActor*> NewActors;
    TArray<AActor*> NewNetActors;
    NewActors.Reserve(Actors.Num());
    NewNetActors.Reserve(Actors.Num());
    // The WorldSettings tries to stay at index 0
    NewActors.Add(WorldSettings);
    // Add non-net actors to the NewActors immediately, cache off the net actors to Append after
    for (AActor* Actor : Actors)
    {
        if (Actor != nullptr && Actor != WorldSettings && !Actor->IsPendingKill())
        {
            if (IsNetActor(Actor))
            {
                NewNetActors.Add(Actor);
            }
            else
            {
                NewActors.Add(Actor);
            }
        }
    }
    iFirstNetRelevantActor = NewActors.Num();
    NewActors.Append(MoveTemp(NewNetActors));
    Actors = MoveTemp(NewActors);   // Replace with sorted list.
    // Add all network actors to the owning world
    //[...]
}
实际上通过这一段代码可知，Actors们的排序依据是把那些“非网络”的Actor放在前面，而把“网络可复制”的Actor们放在后面，然后加一个起始索引标记iFirstNetRelevantActor，相当于为网络Actor划分了一个缓存，从而加速了网络复制时的检测速度。AWorldSettings因为都是静态的数据提供者，在游戏运行过程中也不会改变，不需要网络复制，所以也就可以一直放在前列，而如果再加个规则，一直放在第一个的话，也能同时把AWorldSettings和其他的前列Actor们再度区分开，在需要的时候也能加速判断。ALevelScriptActor因为是代表关卡蓝图，是允许携带“复制”变量函数的，所以也有可能被排序到后列。
思考：既然ALevelScriptActor也继承于AActor,为何关卡蓝图不设计能添加Component？
观察到，平常我们在创建Actor的时候，我们蓝图界面是可以创建Component的。
那为什么在关卡蓝图里，却不能这么做（没有提供该界面功能）？
我虽然在图里标出了Level中拥有ModelComponents，但那其实只是针对BSP应用的一个子集。通过源码发现，其实UE自己也是在C++里往ALevelScriptActor添加UInputComponent来实现关卡蓝图可以响应事件。
void ALevelScriptActor::PreInitializeComponents()
{
    if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
    {
        // create an InputComponent object so that the level script actor can bind key events
        InputComponent = NewObject<UInputComponent>(this);
        InputComponent->RegisterComponent();
        UInputDelegateBinding::BindInputDelegates(GetClass(), InputComponent);
    }
    Super::PreInitializeComponents();
}
其实既然ALevelScriptActor是个Actor，那意味着我们当然可以为它添加组件，实际上也确实可以这么做。比如你可以在关卡蓝图里这么干：
而如果你实际意识到关卡蓝图本身就是一个看不见的Actor，你就可以在上面用Actor的各种操作：
在关卡蓝图里的self其实也是个Actor！虽然一般这么干也没什么毛用。
那么好好想想，为啥UE要给你这么一个关卡蓝图界面呢？
在此，我也只能进行一番猜测，ALevelScriptActor作为一个特化的Actor,却把Components列表界面给隐藏了，说明UE其实是不希望我们去复杂化关卡构成的。
假设说UE开放了关卡Component，那么我们在创建组件时就必然要考虑一个问题：哪些是ActorComponent，哪些是LevelComponent，再怎么ALevelScriptActor本质是个Actor，但Level的概念还是要突出，ALevelScriptActor的Actor本质是要隐藏的。所以用户就会多一些心智负担，可能混淆。而如果像这样不开放，大家的思路就都转向先创建个Actor，然后再往之上添加component，思路会比较统一清晰。
再之，从游戏逻辑的组织上来说，Level其实更应该表现为一个Actor的容器。UE其实也是不鼓励在Level里编写太复杂的逻辑的。所以才接着会有了之后的GameMode,Controller那些真正的逻辑控制类（后续会再细讨论）。
所以游戏引擎也并不是说最大化的暴露一切功能给你就是最好的，有时候选择太多了反而容易出错。在这一点上，我觉得UE很好的保持了克制，为我们提供了一个优秀的清晰的不易出错的框架，同时也对高阶用户保留了灵活性。
World
终于，到了把大陆们（Level）拼装起来的时候了。可以用SubLevel的方式：
也支持WorldComposition的方式自动把项目里的所有Level都组合起来，并设置摆放位置：
具体摆放的操作和技巧并不是本文的重点。简单本质来说，就是一个World里有多个Level，这些Level在什么位置，是在一开始就加载进来，还是Streaming运行时加载。
UE里每个World支持一个PersistentLevel和多个其他Level：
Persistent的意思是一开始就加载进World，Streaming是后续动态加载的意思。Levels里保存有所有的当前已经加载的Level，StreamingLevels保存整个World的Levels配置列表。PersistentLevel和CurrentLevel只是个快速引用。在编辑器里编辑的时候，CurrentLevel可以指向其他Level，但运行时CurrentLevel只能是指向PersistentLevel。
思考：为何要有主PersistentLevel？
首先，World至少得有一个Level，就像你也得先出生在一块大陆上才可以继续谈起去探索别的新大陆。所以这块玩家出生的大陆就是主Level了。当然了，因为我们也可以同时配置别的Level一开始就加载进来，其实跟PersistentLevel是差不多等价的，但再考虑到另一问题：Levels拼接进World一起之后，各自有各自的worldsetting，那整个World的配置应该以谁的为主？
AWorldSettings* UWorld::GetWorldSettings( bool bCheckStreamingPesistent, bool bChecked ) const
{
    checkSlow(IsInGameThread());
    AWorldSettings* WorldSettings = nullptr;
    if (PersistentLevel)
    {
        WorldSettings = PersistentLevel->GetWorldSettings(bChecked);
        if( bCheckStreamingPesistent )
        {
            if( StreamingLevels.Num() > 0 &&
                StreamingLevels[0] &&
                StreamingLevels[0]->IsA<ULevelStreamingPersistent>()) 
            {
                ULevel* Level = StreamingLevels[0]->GetLoadedLevel();
                if (Level != nullptr)
                {
                    WorldSettings = Level->GetWorldSettings();
                }
            }
        }
    }
    return WorldSettings;
}
可以看出，World的Settings也是以PersistentLevel为主的，但这也并不意味着其他Level的Settings就完全没有作用了，本篇也无法一一列出所有配置选项来说明，简单来说，就是需要在整个世界范围内起作用的配置选项（比如VR的WorldToMeters，KillZ，WorldGravity其他大部分都是）就是需要从主PersistentLevel的配置中提取。而一些配置选项可以在单独Level中起作用的，比如在编辑Level时的光照质量配置就是一个个Level单独的，目前这种配置很少，但可能以后也会增加。在这里只是阐明一个为主其他为辅的Level配置系统。
思考：Levels们的Actors和World有直接关系吗？
当别的Level被添加进当前World之后，我们能直接在WorldOutliner里看到其他Level的Actor们。
但这并不代表着World直接引用了Level里的Actor们。TActorIteratorBase（World的Actor迭代器）内部的实现也只是在遍历Levels来获得所有Actor。当然World为了更快速的操作Controllers和Pawn也都保存了引用。但Levels却共享着World的一个PhysicsScene，这也意味着Levels里的Actors的物理实体其实都是在World里的，这也好理解，毕竟物理的碰撞之类的当然要是全局的了。再说到导航，World在拼接Level的时候，也是会同时把两个Level的导航网格给“拼接”起来的。当然目前还不是深入细节的时候，现在只要从大局上明白World-Level-Actor的关系。
思考：为什么要在Level里保存Actors，而不是把所有Map的Actors配置都生成在World一个总Actors里？
这肯定也是一种实现方式，好处是把整个World看成一个整体，所有的actors都从属于world，这样就不存在Level边界，可以更整体的处理Actors的作用范围和判定问题，实现上也少了拼接导航等步骤。当然坏处也是模糊了Level边界，这样在加载进一个Level之后，之后再动态释放，就需要再重新再从整体中抽离出部分来释放，这个筛选过程也会产生比较大的损耗。试着去理解UE的权衡，应该是尽量的把损耗平摊（这里是把Level加载释放的损耗尽量减小），才不会产生比较大的帧率波动，让玩家感觉到卡帧。
总结
Level作为Actor的容器，同时也划分了World，一方面支持了Level的动态加载，另一方面也允许了团队的实时协作，大家可以同时并行编辑不同的Level。一般而言，一个玩家从游戏开始到结束，UE会创造一个GameWorld给玩家并一直存在。玩家切换场景或关卡，也只是在这个World中加载释放不同的Level。既然Level拥有了管理者（LevelScriptActor），玩家可以编写特定关卡的逻辑，那么我们能否对World这种层次编写逻辑呢？答案是肯定的，不过本文篇幅有限，敬请期待下篇。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（三）WorldContext，GameInstance，Engine</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23167068
引言
前文提到说一个World管理多个Level，并负责它们的加载释放。那么，问题来了，一个游戏里是只有一个World吗？
WorldContext
答案是否定的，首先World就不是只有一种类型，比如编辑器本身就也是一个World，里面显示的游戏场景也是一个World，这两个World互相协作构成了我们的编辑体验。然后点播放的时候，引擎又可以生成新的类型World来让我们测试。简单来说，UE其实是一个平行宇宙世界观。
以下是一些世界类型：
namespace EWorldType
{
	enum Type
	{
		None,		// An untyped world, in most cases this will be the vestigial worlds of streamed in sub-levels
		Game,		// The game world
		Editor,		// A world being edited in the editor
		PIE,		// A Play In Editor world
		Preview,	// A preview world for an editor tool
		Inactive	// An editor world that was loaded but not currently being edited in the level editor
	};
}
而UE用来管理和跟踪这些World的工具就是WorldContext：
FWorldContext保存着ThisCurrentWorld来指向当前的World。而当需要从一个World切换到另一个World的时候（比如说当点击播放时，就是从Preview切换到PIE），FWorldContext就用来保存切换过程信息和目标World上下文信息。所以一般在切换的时候，比如OpenLevel，也都会需要传FWorldContext的参数。一般就来说，对于独立运行的游戏，WorldContext只有唯一个。而对于编辑器模式，则是一个WorldContext给编辑器，一个WorldContext给PIE（Play In Editor）的World。一般来说我们不需要直接操作到这个类，引擎内部已经处理好各种World的协作。
不仅如此，同时FWorldContext还保存着World里Level切换的上下文：
struct FWorldContext
{
    [...]
	TEnumAsByte<EWorldType::Type>	WorldType;
	FSeamlessTravelHandler SeamlessTravelHandler;
	FName ContextHandle;
	/** URL to travel to for pending client connect */
	FString TravelURL;
	/** TravelType for pending client connects */
	uint8 TravelType;
	/** URL the last time we traveled */
	UPROPERTY()
	struct FURL LastURL;
	/** last server we connected to (for "reconnect" command) */
	UPROPERTY()
	struct FURL LastRemoteURL;
}
这里的TravelURL和TravelType就是负责设定下一个Level的目标和转换过程。
// Traveling from server to server.
UENUM()
enum ETravelType
{
	/** Absolute URL. */
	TRAVEL_Absolute,
	/** Partial (carry name, reset server). */
	TRAVEL_Partial,
	/** Relative URL. */
	TRAVEL_Relative,
	TRAVEL_MAX,
};
void UEngine::SetClientTravel( UWorld *InWorld, const TCHAR* NextURL, ETravelType InTravelType )
{
	FWorldContext &Context = GetWorldContextFromWorldChecked(InWorld);
	// set TravelURL.  Will be processed safely on the next tick in UGameEngine::Tick().
	Context.TravelURL    = NextURL;
	Context.TravelType   = InTravelType;
    [...]
}
粗略的流程是UE在OpenLevel的时候， 先设置当前World的Context上的TravelURL，然后在UEngine::TickWorldTravel的时候判断TravelURL非空来真正执行Level的切换。具体的Level切换详细流程比较复杂，目前先从大局上理解整体结构。总而言之，WorldContext既负责World之间切换的上下文，也负责Level之间切换的操作信息。
思考：为何Level的切换信息不放在World里？
因为UE有一个逻辑，一个World只有一个PersistentLevel（见上篇），而当我们OpenLevel一个PersistentLevel的时候，实际上引擎做的是先释放掉当前的World，然后再创建个新的World。所以如果我们把下一个Level的信息放在当前的World中，就不得不在释放当前World前又拷贝回来一遍了。
而LoadStreamLevel的时候，就只是在当前的World中载入对象了，所以其实就没有这个限制了。
{
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject))
	{
		FLatentActionManager& LatentManager = World->GetLatentActionManager();
		if (LatentManager.FindExistingAction<FStreamLevelAction>(LatentInfo.CallbackTarget, LatentInfo.UUID) == nullptr)
		{
			FStreamLevelAction* NewAction = new FStreamLevelAction(true, LevelName, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentInfo, World);
			LatentManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, NewAction);
		}
	}
}
World->GetLatentActionManager()其实也算是保存在当前World里了。
思考：为何World和Level的切换要放在下一帧再执行？
首先Level的加载显然是比较慢的，需要载入Map，相应的Mesh，Material……等等。所以这个操作就必须异步化，异步的话其实就剩下两种方式，一种是先记录下来信息之后再执行；一种是命令模式立马往队列里压个命令之后再执行。注意，因为OpenLevel还要相应在主线程生成相应Actor对象，所以有些部分还是要在主线程完成的。这两种模式其实都可以达成需求，前者更加简单明了，后者相对统一。UE也是个进化过来的引擎，也并不是所有的代码都完美无缺。猜想其实也是一开始这么简单就这么做了，后来也没有特别大的改动的动力就一直这样了。引擎最终比的是生产效率的提高，确实也不是代码有多优雅。
GameInstance
那么这些WorldContexts又是保存在哪里的呢？追根溯源：
GameInstance里会保存着当前的WorldConext和其他整个游戏的信息。明白了GameInstance是比World更高的层次之后，我们也就能明白为何那些独立于Level的逻辑或数据要在GameInstance中存储了。
这一点其实也很好理解，大凡游戏引擎都会有一个Game的概念，不管是叫Application还是Director，它都是玩家能直接接触到的最根源的操作类。而UE的GameInstance因为继承于UObject，所以就拥有了动态创建的能力，所以我们可以通过指定GameInstanceClass来让UE创建使用我们自定义的GameInstance子类。所以不论是C++还是BP，我们通常会继承于GameInstance，然后在里面编写应用于整个游戏范围的逻辑。
因为经常有初学者会问到：我的Level切换了，变量数据就丟了，我应该把那些数据放在哪？再清晰直白一点，GameInstance就是你不管Level怎么切换，还是会一直存在的那个对象！
Engine
让我们继续再往上，终于得见UE大神：
此处UEngine分化出了两个子类：UGameEngine和UEditorEngine。众所周知，UE的编辑器也是UE用自己的引擎渲染出来的，采用的也是Slate那套UI框架。好处有很多，比如跨平台比较统一，UI框架可以复用一套控件库，Dogfood等等，此处不再细讲。所以本质上来说，UE的编辑器其实也是个游戏！我们是在编辑器这个游戏里面创造我们自己的另一个游戏。话虽如此，但比较编辑器和游戏还是有一定差别的，所以UE会在不同模式下根据编译环境而采用不同的具体Engine类，而在基类UEngine里通过一个WorldList保存了所有的World。
Standalone Game：会使用UGameEngine来创建出唯一的一个GameWorld，因为也只有一个，所以为了方便起见，就直接保存了GameInstance指针。
而对于编辑器来说，EditorWorld其实只是用来预览，所以并不拥有OwningGameInstance，而PlayWorld里的OwningGameInstance才是间接保存了GameInstance.
目前来说，因为UE还不支持同时运行多个World（当前只能一个，但可以切换），所以GameInstance其实也是唯一的。提前说些题外话，虽然目前网络部分还没涉及到，但是当我们在Editor里进行MultiplePlayer的测试时，每一个Player Window里都是一个World。如果是DedicateServer模式，那DedicateServer也会是一个World。
最后实例化出来的UEngine实例用一个全局的GEngine变量来保存。至此，我们已经到了引擎的最根处:
//UnrealEngine\Engine\Source\Runtime\Engine\Private\UnrealEngine.cpp
ENGINE_API UEngine*	GEngine = NULL;
GEngine可以说是一切开始的地方了。翻看引擎源码，到处也可以看见从GEngine->出来的引用。
GamePlayStatics
既然我们在引擎内部C++层次已经有了访问World操作Level的能力，那么在暴露出的蓝图系统里，UE为了我们的使用方便，也在Engine层次为我们提供了便利操作蓝图函数库。
UCLASS ()
class UGameplayStatics : public UBlueprintFunctionLibrary 
我们在蓝图里见到的GetPlayerController、SpawActor和OpenLevel等都是来至于这个类的接口。这个类比较简单，相当于一个C++的静态类，只为蓝图暴露提供了一些静态方法。在想借鉴或者是查询某个功能的实现时，此处往往会是一个入口。
总结
从结构上而言，我们已经来到了最根源的地方。GEngine仿佛就是一棵大树的根，当我们拎起它的时候，也会带出整个游戏世界的各个对象。但目前这些对象：Object->Actor+Component->Level->World->WorldContext->GameInstance->Engine，确实已经足够表达UE游戏世界的各个部分。
那作为GamePlay部分而言，我们还有一个问题：UE是如何把在该对象结构上表达游戏逻辑的？
如果说：“程序=数据+算法”的话，那UE的GamePlay我们已经讨论完了数据部分，而下篇我们将开始讨论UE的游戏逻辑“算法”部分。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（四）Pawn</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23321666
引言
欢迎来到GamePlay架构章节的下半部分！
在上一篇的内容里，我们谈到了UE的3D游戏世界是由Object->Actor+Component->Level->World->WorldContext->GameInstance->Engine来逐渐层层构建而成的。那么从这下半章节开始，我们就将要开始逐一分析，UE是如何在每一个对象层次上表达游戏逻辑的。和分析对象节点树一样，我们也将采用自底向上的方法，从最原始简单的对象开始。
首先需要明确的是，本部分接下来要讲述的UE的GamePlay逻辑框架部分，只是讨论UE的设计思想和理念，并不是表示其在所有其他游戏引擎中是最优最完美的方案，同时当然也不是开发人员务必遵守的金科玉律，你依然可以也应该根据自己实际情况灵活变通。UE经过了很多权衡设计和历史进化，最后选择了该设计方案，一方面和对象层级相辅相成，另一方面也提供了足够的自由度可以供你腾挪。
实现一个游戏业务功能的方式有多种，你应该尽量妥善的权衡你当前的现实情况，考虑生产效率、维护性、功能实现、易理解、性能等等多种因素，然后选择你认为最恰当的方式。如果你当前在制作一个快速原型Demo，你大可以简单粗暴，我也不赞成时刻谨遵教条主义一定要分层拆分如何如何；而如果是面对一个正式的比较大型项目，随着规模的扩大，我们就得利用清晰的概念来帮助我们减轻心智负担。UE作为一个老牌的经历了十几年风风雨雨的游戏引擎，也当然有它的一套GamePlay哲学。我们选择了UE，接受了在UE的工作流之下工作，如果我们能比较好的理解它的概念和思想，就能更加的“顺”着它的思路，得心应手海阔任鱼跃。而如果我们“逆”着这个框架来搞自己的一套，一是不免有无法充分利用UE的嫌疑，二也是以UE的庞大和根深错节难免让你碰一头灰费力不讨好。
Note1：虽然本部分会涉及到游戏的业务逻辑编写部分，但并不打算详细讨论AI（BehaviorTree，Navigation等）。AI也是一个很大的话题，值得专门开个大章节讨论，我们现在不应该委屈她。
Note2：本部分也不会细讨论输入事件的处理，游戏逻辑确实一大部分是由输入事件驱动起来的，不过我们此时只是简单聊一下概念，后续会有章节再细讨论输入事件的路由流程。
Note3：联机游戏的游戏逻辑自然也是非常重要的，但为了简化本章节的概念，所以网络联机的逻辑同步等也都不会涉及。留待后续网络章节再好好的阐述。
Component
Actor可以说是由Component组成的，所以Component其实是我们对象树里最底层的员工了。在UE里，Component表达的是“功能”的概念。比如说你要实现一个可以响应的WASD移动的功能，或者是VR里抓取的功能，甚至是嵌套另一个Actor的功能，这些都是一个个组件。正确理解“功能”和“游戏业务逻辑”的区分是理解Component的关键要点。
所以我们在这一个层级上要编写的逻辑，是实现一个个“与特定游戏无关”的功能。理想情况下，等你的一个游戏完成，你那些已经实现完成的Components是可以无痛迁移到下一个游戏中用的。换言之，一旦你发现你在Component中含有游戏的业务逻辑代码，这就是所谓的“Bad Smell”了，要警惕游戏架构是否恰当，是否没有很清晰的概念划分。
Actor
如果说UE是一个大国家的话，那Actor无疑就是人口最大的民族了。StaticMeshActor，CameraActor……我们天天口里嚷嚷的也都是它。和Unity的Prefab对应的，在UE里我们用的最多的也是BlueprintActor了，我们也常常自定义我们的Actor子类来组装其他Component和Actor，然后再编写一些协作逻辑代码，就似乎完成了一个骁勇善战的特种兵，接下来就可以撒豆成兵般的往Level中扔了。
用的越广泛越多，往往错的也越多。似乎是受到了一种朴素的子承父业的精神感染，也或许是我们的面向对象编程都学得太好的缘故，我们都非常倾向于直接在Actor里堆砌逻辑。右键一个BlueprintActor，刚添加完Component，就立马撸起袖子来，Event、Function和Variable一个个罗列开来，噼里啪啦无不快活！但是且慢，这是最好的方式了吗？让我们一路带着这个问题，试着从UE角度去推演一下，重走一下Actor进化之路。在本章节旅程的终点，我保证，我们可以比较清楚的回答这个问题。
其实所有的游戏引擎在构建完节点树之后，都会面临这么一个问题，我的游戏逻辑写在哪里？
有的原始的如Cocos2dx懒得想那么多，干脆就直接码在Node里面得了，所以你翻看Cocos2dx的源码你就会经常发现它的逻辑和表现往往是交杂在一起的，简单直接暴力美学，面向对象继承玩得溜。而面向组合阵营的领军Unity则干脆就把Component思想再应用极致一点，我的逻辑为什么不能也是一个组件？所以Unity里的ScriptComponent也是这种组合思想的体现，模型统一架构优雅，MonoBehavior立大功了！但是在一个Component（ScriptComponent）里去操作管理其他的Components，本身却其实并不是那么优雅，因为有些Component之上的协调管理的事务，从层次上来说，应该放在更高的一个概念上实现。UE在思考这个问题时，却是感觉有些理想主义，颇有些C++的理念，力求不为你不需要的东西付代价，宁愿有时候折衷，也想保住最优性能。UE的架构中也大量应用了各种继承，有些继承链也能拉得很长，同时一方面也吸纳了组合的优点，我们也能见到UE的源码中类的成员变量也是组合了好多其他对象。所以接下来的该介绍的就是UE综合应用这两种思想的设计产物。面向对象派生下来的Pawn和Character，支持组合的Controller们。
Pawn
那么第二个至关重要的的问题是，哪些Actor需要附加逻辑？
在游戏中，我们之所以会觉得一个角色生动，是因为它会响应我们的交互，并给出恰当的反应。而我们所谓的游戏业务逻辑，实际上编写的就是该如何对玩家的输入提供反馈。同样，一个Actor想要变得“生动”，就得有响应外部输入的能力，否则就只是自动运转麻木的机器人。但是在一个比较大型的3D游戏中，Actor有千千万万，然后并不是所有的Actor都需要和玩家互动，得宠的能直接面圣和玩家互动的Actor也是比较少的。我们经常都只是操作我们的“角色”，让“角色”和场景里的其他物体互动。比如FPS游戏里我们操作的主角或者是FlappyBird里的那只小鸟。所以从这一点上来看，UE中Actor就立马又可以划分出一个类别了，这些Actor们可谓是玩家们的宠儿，它们是玩家们的亲卫兵，对，它的名字就是Pawn!
同其他AInfo一样，UE也是从Actor中再派生出了APawn，并定义了3块基本的模板方法接口：
1. 可被Controller控制
2. PhysicsCollision表示
3. MovementInput的基本响应接口
为了更好理解这个概念，让我们看一下用搜索引擎搜一下Pawn得到的图：
没错，Pawn的英文翻译过来可以是兵卒，所以如果把UE游戏看作是一场棋盘上的游戏的话，那这些Pawn就可以看作是在UE的3D世界中玩家可以操纵的棋子，而其他的Actor则可以构成棋盘等。如果是人机对战的话，对方玩家是机器AI，同样需要控制Pawn棋子。所以Pawn就是那些可以被玩家（你或AI）控制的Actor！再考察到UE是做FPS游戏起家的，所以你可以想象这个Pawn就相当于战场里最基本的士兵的表示。一个士兵在战场中首先需要表达自身的存在（PhysicsCollision），可以移动（MovementInput），然后可以响应输入和处理逻辑（Controller），有了这三个基本要素，运用你的想象力，你就可以大概构想出一个被玩家控制的“兵卒”的模样和概念了。
要非常清楚一点的是，Actor是我们用来表示3D游戏中对象的，所以Pawn继承于Actor，概念的重点是在于更清楚的去表示，而不是重点在于Pawn被当作逻辑的载体，就像棋子本身只能简单的表达出出个棋子，但是该如何走还是得再靠外部的Controller机制。你也可以想象成提线木偶，那个木偶就是Pawn，而提线的是Controller。Pawn表达的最关键点是可被玩家操纵的能力。因为UE从FPS进化过来的关系，所以附带的物理表示和移动也一并加了进去，应该也是为了方便的缘故。就像我知道Damage这种业务逻辑部分按照纯粹性来说是不应该出现在引擎的代码里的，但是Actor里就是这么加上了，用的时候也确实能得到便利。游戏引擎是个工程，而不是科学研究，有时候确实模块划分也不是那么纯粹。
思考：为何Actor也能接受Input事件？
我上述的对Pawn的描述可能会让你觉得，似乎Pawn既然就是用来被玩家控制的，那么理所当然的我们应该在Pawn上同时实现对输入的接受。但我们会发现实际上EnableInput接口却是在Actor上的，同时InputComponent也是在Actor里面的，意味着实际上你也可以在Actor上绑定处理输入事件。官方的输入事件处理流程图也是表明了这一点：
（暂时不用细研究这个图，我们以后会再次见到的。）
我们在此暂不细讨论输入流程为何如此设计，只谈谈该如何理解这一事实。首先应该不难理解输入的处理功能可以实现化出InputComponent，而“输入”的种类也有很多(按键、摇杆、触摸和陀螺仪等等)，我们也不能确定和分类哪些Actor的子类该接受哪些种类的输入事件；同时又因为Actor也是由Component组件化组装而成的，UE不可能为了输入的处理就改变Component的组织方式，所以还不如泛泛的在Actor的基类里提供InputComponent的集成，这样反而保证了灵活性。
理解这个问题的要点在于正确区分“输入响应”和“逻辑控制”。比如说WASD移动，Actor拥有最基本的输入响应，它可以响应WASD的按键事件。但是按键了之后呢？该如何移动？Pawn就定义了一个基本的MovementInput套路，相当于把WASD的输入响应再往前包装处理了一步。而“逻辑控制”指的是更高层上的比如寻路或自动巡逻等行为。
作为GamePlay中至关重要的一个逻辑概念，让我再罗嗦强调一遍应该不为过吧。Pawn实现的是“可被控制”的概念。因为“被控制了”之后经常要被移动（UE对FPS是真爱啊），所以Pawn就索性把移动的接口也定义了一下（当然，为了灵活性，内部转交给MovementComponent再处理），既然能移动了，但也不能随便在地图里乱走吧，所以碰撞（物理表示）看来也是需要的啊，好吧，那就加上，齐活了。
DefaultPawn，SpectatorPawn，Character
让我一口气介绍下面这三位：
DefaultPawn
因为我们每次想自己搞Pawn都得从Pawn派生过来，然后再一个个添加组件。UE知道我们大家都很懒，所以提供了一个默认的Pawn：DefaultPawn，默认带了一个DefaultPawnMovementComponent、spherical CollisionComponent和StaticMeshComponent。也是上述Pawn阐述过的三件套，只不过都是默认套餐。
SpectatorPawn
UE的FPS做的太好了，就会有一些观众想要观战。观战的玩家们虽然也在当前地图里，但是我们并不需要真正的去表示它们，只要给他们一些摄像机“漫游”的能力。所以派生于DefaultPawn的SpectatorPawn提供了一个基本的USpectatorPawnMovement（不带重力漫游），并关闭了StaticMesh的显示，碰撞也设置到了“Spectator”通道。
Character
因为我们是人，所以在游戏中，代入的角色大部分也都是人。大部分游戏中都会有用到人形的角色，既然如此，UE就为我们直接提供了一个人形的Pawn来让我们操纵。
像人一样行走的CharacterMovementComponent， 尽量贴合的CapsuleComponent，再加上骨骼上蒙皮的网格。同样的三件套，不一样的配方。
有些人一开始的时候会困惑应该选择Pawn还是Character，其实从继承体系中就可以了解到Character只不过是Pawn的加强特化版本。一般来说，如果你控制的角色是人形的带骨骼的，那就选择Character吧。而如果是VR中的一双手（假设只有一双手），因为移动模式和显示都算不太上人形，顶多只能算是个漂浮的“幽灵”，所以还是用Pawn方便些。后期如果你想加上人形模型和IK了，那么再把Mesh替换成SkeletalMesh也就行了。Pawn因为是基础款，所以提供了最大的灵活性。
总结
本篇主要探讨了从Actor到Pawn的分化过程，请读者们也好好自己体会一下这一过程中UE的设计和思量。一个游戏引擎对3D游戏世界的抽象是建立在很多概念之上的，UE的逻辑和实现也都是基于对这些概念的实现和封装。而如果读者你并不清晰理解这些概念，那么就很难正确的应用和组织游戏的逻辑各个部分。本系列教程一如开篇所说，并不会教你应用的各种技巧，而把重点放在讨论UE背后的各种概念，这些才是让我们的头脑保持清晰的关键之处。
因为在下笔力有限，很遗憾，我们心心念念的Controller只好留待下篇了。我在谈Pawn的时候，因为Pawn和Controller是那么紧密的关联着，所以也不得不事先一再的剧透提到Controller。但Controller作为GamePlay逻辑的最最重要的一个载体，可探讨的点也非常的多，所以留待下篇吧。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（五）Controller</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23480071
引言
如上文所述，UE从Actor中分化了一些专门可供玩家“控制”的Pawn，那我们这篇就专门来谈谈该怎么个控制法！
所谓的控制，本质指的就是我们游戏的业务逻辑。比如说玩家按A键，角色自动找一个最近的敌人并攻击，这个自动寻找目标并攻击的逻辑过程，就是我们所谈的控制。
Note1：重申一下，Controller特别是PlayerController，跟网络，AI和Input的关系都非常的紧密，目前都暂且不讨论，留待各自模块章节再叙述。
MVC
不管是游戏，还是其他App，Web或Server等，本质上都是程序，所以也都是或多或少需要一些程序逻辑。从1843年拜伦的女儿Ada Lovelace用穿孔机编写第一个程序开始，到2016的今天我们能方便地用蓝图连线组织程序逻辑，应该归功于一代代软件工程师们孜孜不倦的探索。时代在发展，技术在进步，软件也愈趋于复杂多变，很多软件的庞大也已经超越了个人的理解容量极限（UE？），因此我们就越来越需要设计方法来让我们可管理庞大的复杂度。几十年的迭代，旧的模型被放弃，新的模型被提出验证，工程师们在这过程中总结积累出了一些设计模式。最负有盛名的应该是GOF的《设计模式》，以及MVC，MVP，MVVM等。本文的重点不在于细谈论各种设计模式，如果有对设计模式不清楚的读者，请务必仔细去研究学习，因UE如此庞大的代码框架也是充斥着各种设计模式的应用，设计模式理解得越好，也越能理解UE的框架设计。
言归正传，设计模式的本质就是抽象变化。如果依照纯朴的"程序=数据+算法"的结构来看，再算上用于用户显示和输入的界面，那么就得到“程序=数据+算法+显示”。这三大基本块（数据，算法，显示）构成了程序的三大变化，而如何把这三者“+”到一起，用的就是我们的种种设计框架模式。
典型的，对于游戏：
“显示”指的是游戏的UI，是屏幕上显示的3D画面，或是手柄上的输入和震动，也可以是VR头盔的镜片和定位，是与玩家直接交互的载体；
“数据”指的是Mesh，Material，Actor，Level等各种元素组织起来的内存数据表示；
“算法”可以是各种渲染算法，物理模拟，AI寻路，本文咱们就先暂时特指游戏开发者们编写的游戏业务逻辑。
抽象这三个变化，并归纳关系，就是典型的MVC模式了：
有些人可能会说MVC是UI专用的模式，如IOS的MVC或WPF的MVVM，也或者说因为游戏的类型千差万别所以一个通用的框架并不能都适用，因此就有一点点想要“返璞归真”的意味，觉得游戏引擎只需要提供一个基本的渲染框架，其他的逻辑框架不需要设计复杂，开发者们可自行根据游戏类型再设计。这种观点有一定的道理，对于简单的游戏或Demo，确实也还不到需要“设计”的地步；而对于复杂大型的游戏，需要的架构知识也确实远不是MVC这么简单。但缺点在于，说这话的人要嘛就已经是架构高手，各种设计模式信手拈来，早已经到了无招胜有招的地步；要嘛就是回避了问题，游戏也是软件，软件的固有复杂度摆在那里，总得需要个办法去解决，今天如果我们不是在探讨尝试用MVC模式去掌控它，也是在谈一个别的名字的模式。在我看来，一个好的游戏引擎，应该是能尽力的帮助用户，并减少麻烦。MV当然也有它的缺陷和不足，所以我们应该研究的是UE为何选择了MVC，有什么优点缺点，我们怎么利用和规避，让UE的Controller们尽责的为我们服务，少造成麻烦。
对于简单的游戏或者引擎来说，有时并不需要把这三者分的很清，如Cocos2dx就没有Controller，它的MVC就是混杂在一起，因为代码量少所以也还算勉强能凑合；Unity的MonoBehavior其实也相当于把MC放在了一起，用得方便的同时也得小心太顺手了出现组件之间互相网状引用一团乱麻的情况；UE在这个问题上的思考就有些一脉相承，既然Actor们形形色色，我们之前也谈过甚至有AInfo这种书记官，那为何不让一些Actor专门来承载逻辑呢？于是，Actor再度分化出Controller。下面我们就来一一介绍Actor旗下Controller家族的指挥官们。
AController
虽然我在之前已经一再的剧透过AController是继承自AActor的一个子类，但是为了更好理解思考UE里的Controller机制，请先把脑袋放空，也别去偷看UE里的源码，像张无忌一样暂时忘记AController这回事，问自己一个问题：如果我想实现一种机制去控制游戏里的Actor，该怎么设计？
巧妇难为无米之炊，咱们先来看看当前手上都有些什么：
UObject，反射序列化等机制
UActorComponent，功能的载体，一定程度的嵌套组装能力（SceneComponent）
AActor，基础的游戏对象，Component的容器
APawn，分化出来的AActor，物理表示和基本的移动能力，当前正翘首以待。
没了，在控制Actor这个层级，我们还暂时不需要去考虑Level等更高层次的对象
针对APawn，再想想我们希望达成的控制愿景，没事，你尽管放开想象的想，做不做得到咱们先放一边，但至少别在一开始就被想象力限制住了。“控制”本身虽然只是一段逻辑算法代码，但是它也需要有个载体去承载和运行，某种意义上来说也算得上是个实体。所以下面我们不妨就脑洞大开，以“控制”这个实体的视角口吻，讲讲“我，作为一个——控制”希望拥有哪一些本领：
能够和Pawn对应起来，理想情况下，极端的灵活性应该是多对多。我希望我能同时控制多个Pawn，当然，一个Pawn也可以被多个我的兄弟姐妹们一起控制。想想那些RTS游戏和多人协作游戏，你应该能明白我有时候需要协调调度Pawn们走个方阵，有时候也得多人合作才能操纵得了一台机甲。当然越灵活也往往意味着越容易出错，但总之我们需要一个和Pawn关联的机制。
多个控制实例，在需要的时候，我不介意可以克隆出多个我来，比如一段逻辑A，我们希望可以有多个实例在同时运行。就像行为树一样，可以有多个运行实例，彼此算法一样，但互不干扰。
可挂载释放，我可以选择当前控制PawnA，也可以选择之后把它释放掉不再控制让她自生自灭，然后再另寻新欢控制PawnB，我必须拥有灵活的运行时增删控制Pawn的能力。
能够脱离Pawn存在，我思故我在，就算当前没有任何Pawn控制，我也可以继续存在，这样我就可以延时动态的选择Pawn对象。有些Pawn值得我去等。
操纵Pawn生死的能力，谁规定必须一定去控制世界当前存在的Pawn才行。当世界里没有Pawn可供我控制时，我希望可以自己造一个出来。你要说她是玩具、亦或傀儡也好，我不在乎。有时候我很羡慕暗黑里的沉沦魔巫师，身边总是围绕着一群沉沦魔，一个沉沦魔挂了，他可以紧接着再复活一个出来，这样永远都不会感动寂寞，你说多好？那索性再霸道一点吧，要是我这个控制实体不在了，我希望可以选择是否带Pawn们跟我一起走，没了我，她们都傻得让人心疼。当然如果有哪个Pawn能让我这个霸道总裁爱上，我也愿意陪她一起去死。
根据配置自动生成，我（控制）虽然只是一段代码，但也不能无中生有，所以也得有个机制可以生成我这个控制实体，不过想来这应该是组织里更上层领导的事，但至少他应该知道怎么创建我出来。
事件响应，游戏事件的一些控制关心的事件应该能够传到我这里，我可以酌情处理。同样，Pawn也可以向我汇报，我会好好研究决定的，嗯。
持续的运行，没事的时候，我喜欢听世界大钟的每一次Tick，跟我的心跳同步起来，就仿佛真的活过来一样，可以自主的做一些我想做的事，这是我最自在的时候。
自身有状态，你累了要休息，我也一样。我可以选择自身的状态，选择工作或者是休息，也可以选择今天是哪个Pawn和心情最配。
拥有一定的扩展继承组合能力，一方面我希望我的家族开枝散叶繁荣昌盛，我的一身本领继承自我的父亲，而我也将有我的儿，大家各有天赋。另一方面，那些普通的Actor们都可以身背各个Component，更高贵的我当然也想有。
保存数据状态，听说金鱼的记忆只有7秒，可是我却想记住你一辈子。所以我希望我能拥有一些记忆，人的过去成就了现在，也将指引着未来。以前有一个人跟我说过，当你不能再拥有的时候，唯一能做的就是令自己不要忘记。
可在世界里移动，我可以选择帐中千里之外遥控Pawn，也可以选择附身在一个Pawn身上，这样我才能多角度无死角的观察我可爱的Pawn们，嘿嘿。
可探查世界的对象，我要有眼睛，让我干活，基本的我得看得见知道当前世界里已经有哪些对象吧，否则不就抓瞎了嘛。
可同步，这年头，要是不能适应网络环境，可真的没有竞争力。这个Object，Actor基本都有的能力，我当然也得有。位于服务器或客户端上的我也必须有能力在其他客户端上影分身，让他们都跟随我的步伐一致行动。
在仔细考察了"控制"的需求和手头上的原料之后，我们试着从UE的角度来权衡一下。
首先Controller不能是一个Component，一是因为Component的层级太低，表达的是功能的概念而非逻辑；二是Component必须依附于Actor存在，而我们的Controller希望能独立存在。
其次如果从UObject直接继承下来UController，倒是也可行，UObject也能复制同步，其他的控制Pawn的能力和事件响应等倒也是能改改接口想想办法，但是要想在世界里移动，就得有个位置表示，再加上还希望能容纳Components，这就麻烦了，基本就是把Actor的工作再做一套，有点累人，搞起来也怕两套班子出错闹矛盾。
再来考察下从AActor继承下来AController怎么样，Actor比Object多了一些我们正需要的配置动态生成、输入事件响应、Tick、可继承、可容纳Component、可在世界里出现、可在网络间同步。好了，现在就差控制Pawn的能力，那我们就在这个分化出来的AController增加一些控制Pawn的接口，这个思路正是和我们从Actor从分化出Pawn的时候不谋而合！现在我们来看看UE里的AController:
跟我们的设计八九不离十，我们再一一仔细验证一番：
关联Pawn的能力，有Possess和UnPossess，源码里也有PawnPendingDestroy等这些函数（未一一列出）；GameMode中也保存着AIControllerClass和PlayerControllerClass的配置，用于在适当的时候Spawn出Controller；继承于Actor也就有了EnableInput和Tick；Controller本身还可以继续派生下去（如AIController和PlayerController），也可以容纳Components；也带着一个SceneComponent所以可以摆放在世界中；自身也可以添加成员变量来记忆存储游戏状态；自身也有一个FName StateName（Playing、Spectating、Inactive），切换自身的状态（运行，观察，非激活）；因为跟Pawn是平级的关系，只在运行的时候引用关联，所以对彼此独立存在不做强制约束，提高了灵活性。一个Pawn自身上也可以配置策略：
namespace EAutoReceiveInput
{
    enum Type
    {
        Disabled,
        Player0,
        Player1,
        Player2,
        Player3,
        Player4,
        Player5,
        Player6,
        Player7,
    };
}
TEnumAsByte<EAutoReceiveInput::Type> AutoPossessPlayer;
enum class EAutoPossessAI : uint8
{
    /** Feature is disabled (do not automatically possess AI). */
    Disabled,
    /** Only possess by an AI Controller if Pawn is placed in the world. */
    PlacedInWorld,
    /** Only possess by an AI Controller if Pawn is spawned after the world has loaded. */
    Spawned,
    /** Pawn is automatically possessed by an AI Controller whenever it is created. */
    PlacedInWorldOrSpawned,
};
EAutoPossessAI AutoPossessAI;
TSubclassOf<AController> AIControllerClass;
这样在运行时UE也可以根据Pawn创建配套的Controller。毕竟只是为了阐明概念，而不是纠结技术细节，我对Controller的功能接口都只是粗略带过，如果读者自己去看Contoller的UE源码，顺便可以对我当前说的概念验证一下，还会发现一些Movement和ViewPoint的接口，这些也算是和控制移动和视角配套吧。
思考：Controller和Pawn必须1:1吗？
观察UE实现里我们发现Controller里只是保存了一个Pawn指针，而不是数组，这和一开始希望的多对多关系有些出入。理想和现实总是有差距，一个愿景落实到工程实践上也不免得有一些妥协。首先我们再来梳理理解一下这个Possess(拥有/占用)的概念。一个Controller能灵活的Possess/UnPossess一个Pawn，虽然一次只能控制一个，但在游戏中我们也可以在不同的Pawn中切换，比如操纵一个主角坐进然后控制一辆汽车，或者端起固定的机关枪扫射，这些功能琢磨一下其实只是涉及操作实体Pawn的变化。如果我们能妥善的用好Pawn和Controller的切换功能，大部分基本的游戏功能也是能够比较方便的实现的。那么有哪些是不太适合的呢？UE官方其实也承认了，见Controller文档说明：
By default, there is a one-to-one relationship between Controllers and Pawns; meaning, each Controller controls only one Pawn at any given time. This is acceptable for most types of games, but may need to be adjusted as certain types of games - real-time strategy comes to mind - may require the ability to control multiple entities at once.
对于RTS这种需要一下子控制多个单位的游戏来说，这种1v1的关系确实比较僵硬，就需要在Controller里自己实现扩展一下，额外保存多个Pawn，然后自己实现一些需要的控制实现，但总体上也只能说得绕一下，也算不上特别复杂，所以就也不能说UE做不了某一些类型的游戏，Epic是个游戏引擎公司，卖的毕竟是个通用游戏引擎。
OK，那UE为何不实现成多对多呢？我觉得理由往往很简单，就是想保持一定的简单。游戏引擎的每个模块的设计，甚至函数接口的设计，无时无刻不在权衡决定。太简单了概念清晰用起来方便但是灵活扩展力不足，太灵活扩展无限了往往也会让人无从适从容易出错。当前1:1的时候，我们的脑袋逻辑很清晰，我们可以在Controller里直接GetPawn，也可以在Pawn中GetController，都非常方便。调试逻辑Bug的时候，我们也能很快找到查错的目标。而对比想象，如果是M：N，灵活性是满满了，但是你能轻易的说出当前Pawn是被哪些Controller控制吗？你也得时时记着这个Controller当前控制了哪些Pawn。OMG！这些Pawn和Controller多对多的构成了网状结构，项目越庞大复杂，这张网也越能套住你。再从另一个方面说，一旦提供了这种多对多的直接支持，以我们人类的性格，免费现成的东西，我们总是倾向于去找机会能用上它，而不是去琢磨到底应不应该用。所以一旦就这么直接提供了，对于刚入门的新手，压根就没什么指引，怎么来好像都可以，就非常容易收不住把项目逻辑关系搞得不必要的复杂。所以以后UE就算想在这一方面优化加强，应该也会比较克制。
索性再聊开一些，我们用Unity来做一下对比。Unity就是GameObject+Component，你自己组合去吧，非常的灵活自由，也不做什么限制，但造成的后果就是常常各种Component互相引用来引用去，网状互联一团乱麻。另外几乎每个人都可以在上面搞出一套游戏系统出来，互相之间都是自成一派。所以经常网上就会有各种帖子问怎么在Unity中实现MVC模式的，也有分析炉石传说游戏逻辑框架的。Unity当然是个好引擎，目前来说热度也是比UE要高一些，但我们也不能因为它火用得人多，就权威崇拜从众的认为Unity各个方面都比别的引擎好。设计架构游戏的时候，工程师们要抵挡住灵活性的诱惑，保持克制往往是更难得珍贵的美德。要认识到，引擎的终极目的是方便人使用的，我们程序员往往很容易太沉迷于程序功能的灵活强大，而疏忽了易用性鲁棒性等社会工程需求。
思考：为何Controller不能像Actor层级嵌套？
我们都知道Actor可以藉着身上的SceneComponent互相嵌套。那么AController同样也是Actor，为何不也实现这么一个父子机制？从功能上来说，一个Controller可以有子Controllers，听起来也是非常灵活强大啊。但是冷静想一下，Controller表达的“控制”的概念，所以在这里你实际上想要表达的是一种“控制”互相嵌套的概念，感觉又给“控制”给分了层，有“大控制”，也有“小控制”，但是“控制”的“大小”又是个什么概念呢？我们应该怎么划分控制的大小？“控制”本质上来说就是一些代码，不管怎么设计，目的都是用来表达游戏游戏逻辑的。而针对游戏逻辑的复杂，怎么更好的管理组织逻辑代码，我们有状态机，分层状态机，行为树，GOAL（目标导向），甚至你还能搞些神经网络遗传算法机器学习啥的。所以在我们已经有这么多工具的基础上，徒增复杂性是很危险的做法。如果有必要，也可以把Controller本身再当作其他AI算法的容器，所以就没必要在对象层次上再做文章了。
思考：Controller可以显示吗？
既然Actor本身可以带着Mesh组件来渲染显示，那Controller可不可以呢？是不是Controller都是不可见的？这个答案可说是也可以说不是，因为Controller本身确实就是一个特殊点的Actor而已，你依然可以在Controller中添加Mesh组件，添加别的子Actor等，所以从这个方面说Controller是有可以渲染显示的能力的。但是一个控制者毕竟只是表达一个逻辑的概念，所以为了分工明确，UE就干脆在Controller的构造函数里把自己给隐藏了：
    bHidden = true;
#if WITH_EDITORONLY_DATA
    bHiddenEd = true;
#endif // WITH_EDITORONLY_DATA
事了拂衣去，深藏功与名。为了验证我的说法，读者你可以亲自在PlayController下挂一些Cube之类的Actor，然后在源码层把这两个值改为false，重新编译运行看下结果，看能否正确显示出来，这里我就不贴图了，留给读者验证，很好玩的哦。
思考：Controller的位置有什么意义？
既然Controller本身只是控制者，那它在场景中的位置和移动有什么意义吗？Controller为何还需要个SceneComponent?意义在于如果Controller本身有位置信息，就可以利用该信息更好的控制Pawn的位置和移动。
首先说下Controller的Rotation，这个比较好理解一点，如果我想让我的Pawn和Controller保持旋转朝向一致，因为是Controller作主控制Pawn的关系，所以Controller就得维护自己的Rotation。再来说位置，如果Controller有自己的位置，这样在Respawn重新生成Pawn的时候，你就可以选择在当前位置创建。因此为了自动更新Controller的位置，UE还提供了一个bAttachToPawn的开关选项，默认是关闭的，UE不会自动的更新Controller的位置信息；而如果打开，就会把Controller附加到Pawn的子节点里面去，让Controller跟随Pawn来移动。你可以把这两种模式想象成一种是上帝视角在千里之外心电感应控制Pawn，另一种是骑在Pawn肩上来指挥。
当然如果这个Controller确实只是纯朴的逻辑控制的话（如AIController），那确实位置也没什么意义。所以UE甚至还隐藏了Controller的一些更新位置的接口，尽量避免让人手动去操纵：
private:
    // Hidden functions that don't make sense to use on this class.
    HIDE_ACTOR_TRANSFORM_FUNCTIONS();
//展开后：
//////////////////////////////////////////////////////////////////////////
// Macro to hide common Transform functions in native code for classes where they don't make sense.
// Note that this doesn't prevent access through function calls from parent classes (ie an AActor*), but
// does prevent use in the class that hides them and any derived child classes.
#define HIDE_ACTOR_TRANSFORM_FUNCTIONS() private: \
    FTransform GetTransform() const { return Super::GetTransform(); } \
    FVector GetActorLocation() const { return Super::GetActorLocation(); } \
    FRotator GetActorRotation() const { return Super::GetActorRotation(); } \
    FQuat GetActorQuat() const { return Super::GetActorQuat(); } \
    FVector GetActorScale() const { return Super::GetActorScale(); } \
    bool SetActorLocation(const FVector& NewLocation, bool bSweep=false, FHitResult* OutSweepHitResult=nullptr) { return Super::SetActorLocation(NewLocation, bSweep, OutSweepHitResult); } \
    bool SetActorRotation(FRotator NewRotation) { return Super::SetActorRotation(NewRotation); } \
    bool SetActorRotation(const FQuat& NewRotation) { return Super::SetActorRotation(NewRotation); } \
    bool SetActorLocationAndRotation(FVector NewLocation, FRotator NewRotation, bool bSweep=false, FHitResult* OutSweepHitResult=nullptr) { return Super::SetActorLocationAndRotation(NewLocation, NewRotation, bSweep, OutSweepHitResult); } \
    bool SetActorLocationAndRotation(FVector NewLocation, const FQuat& NewRotation, bool bSweep=false, FHitResult* OutSweepHitResult=nullptr) { return Super::SetActorLocationAndRotation(NewLocation, NewRotation, bSweep, OutSweepHitResult); } \
    virtual bool TeleportTo( const FVector& DestLocation, const FRotator& DestRotation, bool bIsATest, bool bNoCheck ) override { return Super::TeleportTo(DestLocation, DestRotation, bIsATest, bNoCheck); } \
    virtual FVector GetVelocity() const override { return Super::GetVelocity(); } \
    float GetHorizontalDistanceTo(AActor* OtherActor)  { return Super::GetHorizontalDistanceTo(OtherActor); } \
    float GetVerticalDistanceTo(AActor* OtherActor)  { return Super::GetVerticalDistanceTo(OtherActor); } \
    float GetDotProductTo(AActor* OtherActor) { return Super::GetDotProductTo(OtherActor); } \
    float GetHorizontalDotProductTo(AActor* OtherActor) { return Super::GetHorizontalDotProductTo(OtherActor); } \
    float GetDistanceTo(AActor* OtherActor) { return Super::GetDistanceTo(OtherActor); }
UE这里其实想说的是，这些更新位置的操作还是让我来为你管理吧，我真的担心你会用错搞出什么乱子来。顺便再说些题外话，对于PlayerController来说，因为玩家需要一个视角来观察世界，所以常常PlayerController常常会扛着个摄像机出现（蓝图里没有，但是会运行时生成PlayerCameraManager和CameraActor），所以就算没有角色可供操作，玩家也依然希望是可以视角漫游观察整个世界的（试试看把默认Level里的PlayerStart删掉后运行看看）。这个时候PlayerController常常会默认创建出一个ASpectatorPawn或者DefaultPawn（根据GameMode里配置），我们虽然看不见Pawn，但依然可以观察世界，靠得就是跟Controller关联的旋转和摄像机。
思考：哪些逻辑应该写在Controller中？
如同当初我们在思考Actor和Component的逻辑划分一样，我们也得要划分哪些逻辑应该放在Pawn中，哪些应该放在Contrller中。上文我们也说过，Pawn也可以接收用户输入事件，所以其实只要你愿意，你甚至可以脱离Controller做一个特立独行的Pawn。那么在那些时候需要Controller？哪些逻辑应该由Controller掌管呢？可以从以下一些方面考虑：
从概念上，Pawn本身表示的是一个“能动”的概念，重点在于“能”。而Controller代表的是动到“哪里”的概念，重点在于“方向”。所以如果是一些Pawn本身固有的能力逻辑，如前进后退、播放动画、碰撞检测之类的就完全可以在Pawn内实现；而对于一些可替换的逻辑，或者智能决策的，就应该归Controller管辖。
从对应上来说，如果一个逻辑只属于某一类Pawn，那么其实你放进Pawn内也挺好。而如果一个逻辑可以应用于多个Pawn，那么放进Controller就可以组合应用了。举个例子，在战争游戏中，假设说有坦克和卡车两种战车（Pawn），只有坦克可以开炮，那么开炮这个功能你就可以直接实现在坦克Pawn上。而这两辆战车都有的自动寻找攻击目标功能，就可以实现在一个Controller里。
从存在性来说，Controller的生命期比Pawn要长一些，比如我们经常会实现的游戏中玩家死亡后复活的功能。Pawn死亡后，这个Pawn就被Destroy了，就算之后再Respawn创建出来一个新的，但是Pawn身上保存的变量状态都已经被重置了。所以对于那些需要在Pawn之外还要持续存在的逻辑和状态，放进Controller中是更好的选择。
APlayerState
我们上文提到过Controller希望也能有一些记忆，保存住一些游戏状态。那么到底应该怎么保存呢？AController自身当然可以添加成员变量来保存，这些变量也可以网络复制，一般来说也够用。但是终究还是遗忘了一个最重要的数据状态。整个游戏世界构建起来就是为了玩家服务的，而玩家在游戏过程中，肯定要存取产生一些状态。而Controller作为游戏业务逻辑最重要的载体，势必要和玩家的状态打交道。所以Controller如果可以动态存取玩家的状态就会大为方便了。因此我们会在Controller中见到：
 /** PlayerState containing replicated information about the player using this controller (only exists for players, not NPCs). */
    UPROPERTY(replicatedUsing=OnRep_PlayerState, BlueprintReadOnly, Category="Controller")
    class APlayerState* PlayerState;
而APlayerState的继承体系是：
至于为啥APlayerState是从AActor派生的AInfo继承下来的，我们聪明的读者相信也能猜得到了，所以也就不费口舌论证了。无非就是贪图AActor本身的那些特性以网络复制等。而AInfo们正是这种不爱表现的纯数据书呆子们的大本营。而这个PlayerState我们可以通过在GameMode中配置的PlayerStateClass来自动生成。
注意，这个APlayerState也理所当然是生成在Level中的，跟Pawn和Controller是平级的关系，Controller里只不过保存了一个指针引用罢了。注释里说的PlayerState只为players存在，不为NPC生成，指的是PlayerState是跟UPlayer对应的，换句话说当前游戏有多少个真正的玩家，才会有多少个PlayerState，而那些AI控制的NPC因为不是真正的玩家，所以也不需要创建生成PlayerState。但是UE把PlayerState的引用变量放在了Controller一级，而不是PlayerController之中，说明了其实AIController也是可以设置读取该变量的。一个AI智能能够读取玩家的比分等状态，有了更多的信息来作决策，想来也没有什么不对嘛。
Controller和网络的结合很紧密，很多机制和网络也非常强关联，但是在这里并不详细叙述，这里先可以单纯理解成Controller也可以当作玩家在服务器上的代理对象。把PlayerState独立构成一个Actor还有一个好处，当玩家偶尔因网络波动断线，因为这个连接不在了，所以该Controller也失效了被释放了，服务器可以把对应的该PlayerState先暂存起来，等玩家再紧接着重连上了，可以利用该PlayerState重新挂接上Controller，以此提供一个比较顺畅无缝的体验。至于AIController，因为都是运行在Server上的，Client上并没有，所以也就无所谓了。
思考：哪些数据应该放在PlayerState中？
从应用范围上来说，PlayerState表示的是玩家的游玩数据，所以那些关卡内的其他游戏数据就不应该放进来（GameState是个好选择），另外Controller本身运行需要的临时数据也不应该归PlayerState管理。而玩家在切换关卡的时候，APlayerState也会被释放掉，所有PlayerState实际上表达的是当前关卡的玩家得分等数据。这样，那些跨关卡的统计数据等就也不应该放进PlayerState里了，应该放在外面的GameInstance，然后用SaveGame保存起来。
总结
在游戏里，如果要评劳模，那Controller们无疑是最兢兢业业的，虽然有时候蛮横霸道了一些，但是经常工作在第一线，下面的Pawn们常常智商太低，上面的Level，GameMode们又有点高高在上，让他们直接管理数量繁多的Pawn们又有点太折腾，于是事无巨细的真正干那些脏活累活的还得靠Controller们。本文虽然没有在网络一块留太多笔墨，但是Controller也是同时作为联机环境中最重要的沟通渠道，身兼要职。
回顾总结一下本文要点，UE在Pawn这个层级演化构成了一个最基本和非常完善的Component-Actor-Pawn-Controller的结构：
通过分化出来后的Actor的互相控制，既充分利用了现有的机制功能，又提供了足够的灵活性，而且做的更改还很少，不用再设计额外另一套框架。读者朋友们，现在我们如果翻到第一小节，想想UE最初从Object分化出Actor的那一刻，是不是有很多感慨和感动呢？一个最初的很简单的游戏对象表示，慢慢演化派生充实起来，彼此之间通力配合，竟也能优雅的运转起来。
有时候架构的设计和搭建是一脉相承的，最初的时候选择了什么样的模型和骨架，后面再设计别的逻辑框架等其他模块，也基本上都得跟最初的设计配合着来。所以有时候往往也会发现，怎么感觉我架构设计的方案可选择数量并不多啊？其实是因为如果一开始铺垫的好，接下来的设计水到渠成自然而然，让你感觉不到用心设计的力气。UE以Actor的视角来看待世间万物，自然得到的是一个Actor繁荣昌盛的世界；Unity以Component来组装万物，得到的就是个各种插件组件组装出的世界；而如果如Cocos2dx一般万物都是Node,那么自然也会得到一棵挂满各种Node的世界之树。这也算是游戏引擎的基因吧。
本想着一篇介绍完Controller、PlayerController和AIController这三个对象，但是Controller本身是UE里极为重要的核心概念，自身的功能非常的丰富，牵扯的模块也比较多，因此想抽离阐述最核心的概念和功能并不是一件容易的事。花了这么长的篇幅，只讨论揣摩了Controller的设计过程和最基本的职责（还有输入网络等都没有解释），顺便先简单介绍了下PlayerState出场（PlayerState实际上是跟UPlayer关联更大一些，PlayerController等后续章节会继续讨论它），对于PlayerController和AIController，目前也只是语焉不详的含糊带过。不过还是希望读者们能从中吸取到设计的营养，把握清楚概念了，才能更好的组织游戏逻辑，开发出更好的游戏。
本系列教程的一个重点也是尝试介绍引擎各种概念背后的考量，而不是单纯的叙述解释各个模块功能。笔者始终认为，只有我们愿意不吝口舌的去讨论，愿意耐下心来去思考学习，这些概念的领悟才会了然在心中。否则若只是单纯的介绍Pawn功能有123，Controller可以ABC，相信读者在阅读完之后也并不会有什么深的印象，因为这些只是设计的结果，少了设计的过程。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（六）PlayerController和AIController</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23649987
引言
上文我们谈到了Component-Actor-Pawn-Controller的结构，追溯了AController整个家族的崛起和身负的使命。本篇我们继续来探讨Controller家族中最为人所知的PlayerController和AIController。
作为一个Controller，我们讨论的依然是该如何控制。我们已经知道了Controller可以Possess并控制Pawn，但是Controller本身又是怎么驱动起来的呢？一个游戏里的控制角色大抵都可以分为两类：玩家和AI。不管是单机游戏或者分屏多玩家，还是网络玩家联机对战，游戏都是为了玩家服务的，所以也必然会有一个或多个玩家，就算是如《山》那种纯看的游戏，也是有一个“可观察不可动”的玩家的。而AI的实体的数量就可以是零或者多个。
Note1：依旧重申：输入、网络、AI行为树等模块虽跟PlayerController和AIController关系紧密，但目前都暂且不讨论，留待各自模块章节再叙述。
APlayerController
让咱们先从简单的单机游戏开始讨论吧，比如一款单机FPS游戏，这个游戏里已经用各种各样的Actor们构建完成了世界场景，你的主角和敌人Pawn们也都在整装待发，这个时候你思考这么一个问题，我该怎么玩这个游戏？壮丽的舞台已经准备好了，就等你入场了。先抛开具体的引擎而言，首先你需要能看见（拥有Camera和位置），其次你必须能响应输入（玩家按WASD你应该能接收到），然后你可以根据输入操控一些Pawn（Possess然后传递Input），这样一个单机游戏中的简单玩家控制器就差不多了。一个游戏中只有一个PlayerController，在不同的关卡中你可以使用不同的PlayerController，但是同一时刻响应的只能是一个PlayerController。
插上多个手柄，咱们再拓展一下，比如像《街霸》那种单PC但是多玩家对抗或者协作的游戏。两个玩家可以分别用两个手柄，或者一个用键盘一个用鼠标，甚至是键盘上的不同区域，形式可以多种多样。这个时候如果依然只有一个PlayerController，实现起来其实也是可行的，把两个手柄——所有的输入都由这个PlayerController来接收，然后在PlayerController内部再分别根据情况去处理不同的Pawn。但是这种方式的缺点显然也在于很容易把玩家1、2的输入和控制混杂在一起，没有清晰的区分开。因此，为了支持这种情况，我们可以开始允许游戏中同时出现多个PlayerController，每个PlayerController甚至都可以拥有自己的Viewport（分屏或者不同窗口），这样我们通过配置，可以精确的路由手柄1的输入给玩家1，各自的逻辑也很好的区分和复用。
再插上网线继续，到了网游时代，我们的游戏就开始允许有多人联机对战了。玩家在自己的PC上控制的只是自己的本地的角色，而屏幕游戏里其他的玩家角色是由网线另一端的玩家控制的。为了更好的适应这种情况，我们就又得扩展一下PlayerController的概念，PlayerController不仅能控制本地的Pawn，而且还能“控制”远程的Pawn（实际上是通过Server上的PlayerController控制Server上的Pawn，然后再复制到远程机器上的Pawn实现的）。
因此我们来看看UE里的PlayerController：
PlayerController因为是直接跟玩家打交道的逻辑类，因此是UE里使用最多的类之一。UE4.13.2版本里1632行的.h文件和4686行的.cpp文件，里面实现了很多的功能，初阅读起来往往深陷其中不得要领。但是在上述的分析了之后，我们也可以在其中大概归纳出几个模块：
Camera的管理，目的都是为了控制玩家的视角，所以有了PlayerCameraManager这一个关联很紧密的摄像机管理类，用来方便的切换摄像机。PlayerController的ControlRotation、ViewTarget等也都是为了更新Camera的位置。因为跟Camera的关系紧密，而Camera最后输出的是屏幕坐标里的图像，所以为了方便一些拾取的HitResult函数也都是实现在这里面。渲染章节会再详细介绍UE的摄像机管理。
Input系统，包括构建InputStack用来路由输入事件，也包括了自己对输入事件的处理。所以包含了UPlayerInput来委托处理。
UPlayer关联，既然顾名思义是PlayerController，那自然要和Player对应起来，这也是PlayerController最核心的部分。一个UPlayer可以是本地的LocalPlayer，也可以是一个网络控制UNetConnection。PlayerController只有在SetPlayer之后，才可以开始正常工作。
HUD显示，用于在当前控制器的摄像机面前一直显示一些UI，这是从UE3迁移过来的组件，现在用UMG的比较多，等介绍UI模块的时候再详细介绍。
Level的切换，PlayerController作为网络里通道，在一起进行Level Travelling的时候，也都是先通过PlayerController来进行RPC调用，然后由PlayerController来转发到自己World中来实际进行。
Voice，也是为了方便网络中语音聊天的一些控制函数。
简单来说，PlayerController作为玩家直接控制的实体，很多的跟玩家直接相关的操作也都得委托它来完成。目前来说PlayerController里旗下的100+的函数也大概可以分为以上几大模块，也根据需要重载了Controller里的一些其他函数。
UE的思想是具象化一个“玩家实体”，并把所有的跟该玩家相关的操作和接口都交给它完成。一般其他的游戏引擎只是个“功能引擎”，提供了一些图形渲染UI系统等组件，但是在GamePlay这个层次就都非常欠缺了，一般都需要开发者自己搭建一套。而回想你写过的游戏，是不是也往往有一个Player类（一般是单件或者全局变量）？里面几乎是放着所有跟该玩家相关的业务逻辑代码。UE里的PlayerController就是这种概念，优点当然是直接方便好理解，缺点也如你所见，会代码膨胀得比较快。不过目前来说还算能接受，等某一块功能真的比较大了之后，可以再把它抽出一个单独的类来，如PlayerInput和PlayerCameraManager一样。
思考：哪些逻辑应该放在PlayerController中？
回想我们上篇的问题：“哪些逻辑应该写在Controller中？”，该处的答案观点在本处也依然适用。不过我还想再补充几点：
对实现游戏逻辑来说，如果是按照MVC的视角，那么View对应的是Pawn的表现，而PlayerController对应的是Controller的部分，那Model就是游戏业务逻辑的数据了。拿超级马里奥游戏来举例子，把问题先局限在一个关卡内，假设要实现的是金币的逻辑，那么View指的是游戏右上角的金币数目UI，而玩家用PlayerController来控制马里奥来蹦跳行走，而马里奥（Pawn）通过触碰金币的事件又上报给PlayerController来相应增加金币。而PlayerController存储金币的数据就是在PlayerState中。即PlayerState中有一个int coin，也有相应的AddCoin(int coin)。而PlayerController的职责应该是一边控制Pawn，一边负责内部正确的调用PlayerState的Coin接口。那么PlayerController里的成员变量有什么用？根据单一职责原则，我们写在哪个类里的变量应该尽量只符合该类的作用，所以PlayerController里的变量的意义在于更好的实现控制。比如假设玩家在一个关卡内可以按AABB来作弊获得100金币，但是限最多3次。那么这个按键的响应就应该由PlayerController来接收，然后调用AddCoin(100)，并更新PlayerController里的成员变量CoinCheatCount。也或者想实现马里奥的加速跑，也可以在PlayerController里增加Speed的成员变量。
记住PlayerController是可被替换的，不同的关卡里也可能是不一样的。比如马里奥在水下的时候控制的方式明显就不一样，所以就不能像“Player”单件类那样什么都往里面塞。这样一旦被替换掉了之后数据就都丢失了。
PlayerController也不一定存在，考虑一下如果把马里奥做成联机游戏，那么对方玩家被同步过来的将只有PlayerState，对方玩家的PlayerController只在服务器上存在。所以这个时候，如果你把金币数据放在PlayerController里的话就非常尴尬了。所以为了扩展性来说，还是根据职责分明的原则来正确划分业务逻辑会比较好。
在任一刻，Player:PlayerController:PlayerState是1:1:1的关系。但是PlayerController可以有多个备选用来切换，PlayerState也可以相应多个切换。UPlayer的概念会在之后讲解，但目前可以简单理解为游戏里一个全局的玩家逻辑实体，而PlayerController代表的就是玩家的意志，PlayerState代表的是玩家的状态。
AAIController
从某种程度上来说，AI也可以算是一个Player，只不过它不需要接收玩家的控制，可以自行决策行动。从玩家控制的逻辑需要有一个载体一样，AI的逻辑算法也需要有一个运行的实体。而这就是UE里的AIController：
同PlayerController对比，少了Camera、Input、UPlayer关联，HUD显示，Voice、Level切换接口，但也增加了一些AI需要的组件：
Navigation，用于智能根据导航寻路，其中我们常用的MoveTo接口就是做这件事情的。而在移动的过程中，因为少了玩家控制的来转向，所以多了一个SetFocus来控制当前的Pawn视角朝向哪个位置。
AI组件，运行启动行为树，使用黑板数据，探索周围环境，以后如果有别的AI算法方法实现成组件，也应该在本组件内组合启动。
Task系统，让AI去完成一些任务，也是实现GameplayAbilities系统的一个接口。目前简单来说GameplayAbilities是为Actor添加额外能力属性集合的一个模块，比如HP，MP等。其中的GamePlayEffect也是用来实现Buffer的工具。另外GamePlayTags也是用来给Actor添加标签标记来表明状态的一种机制。目前来说该两个模块似乎都是由Epic的Game Team在维护，所以完成度不是非常的高，用的时候也往往需要根据自己情况去重构调整。
本文重点不在于讨论AI内部的各种组件功能，因此我们先把目光聚焦在AIController对象本身上。同PlayerController一样，AIController也只存在于Server上（单机游戏也可看作是Server）。游戏里必须有玩家参与，而AI可以没有，所以AIController并不一定会存在。我们可以在Pawn上配置AIControllerClass来让该Pawn产生的时候自动为它分配一个AIController，之后自动释放。
思考：哪些逻辑应该放在AIController中？
我们依然要思考这个问题，大部分思想和原则和PlayerController是一样的，只不过AI算法的多种多样，所以我们推荐尽量利用UE提供的行为树黑板等组件实现，而不是直接在AIController硬编码再度实现。也请把目光仅仅局限在当前的Pawn身上，不要在里面写其他无关的逻辑。另外，因为AIController都是在关卡内比较短暂存在的，一般不太有跨Level的数据保存，所以你可以用AIController的成员变量来保存状态。而如果真的需要用到PlayerController的状态，则也可以引用一个PlayerState过来。如果想引用关卡的全局状态，也可以引用GameState，再更高级别的，甚至可以直接和GameInstance接触。
但是AIController也可以通过配置bWantsPlayerState来获得自己的PlayerState，所以PlayerState其实也并不是跟UPlayer绑定的，毕竟从本质上来说APlayerState也只是个AInfo（AActor），跟其他Actor一样可以有多个，并没有什么稀奇的，区别是你自己怎么创建并利用它。
总结
到此，我们也算讨论完了Actor（Pawn）层次的控制，在这个层次上，我们关注的焦点在于如何更好的控制游戏世界里各种Actor交互和逻辑。UE采用了分化Actor的思维创建出AController来控制APawn们，因为玩家玩游戏也全都是控制着游戏里的一个化身来行动，所以UE抽象总结分化了一个APlayerController来上接Player的输入，下承Pawn的控制。对于那些自治的AI实体，UE给予了同样的尊重，创建出AIController，包含了一些方便的AI组件来实现游戏逻辑。并利用PlayerState来存储状态数据，支持在网络间同步。
上图应该可以比较清晰的阐明，UE是如何充分利用Actor的本身机制来反过来实现对Actor的逻辑控制，相信亲爱的读者朋友们也能自行体会到它的优雅之处。对比其他的游戏引擎，往往它们都止步于Actor这一个层次，只提供了最基本的对象层次，美名其曰交给玩家控制。UE为我们提供了这一套简洁强大的机制，大大方便了我们编写逻辑的难度。
而下篇我们的逻辑之旅将再继续拔高一个层次，将开始讲解World层次的逻辑，这个世界的意志：GameMode！
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（七）GameMode和GameState</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23707588
引言
上文我们说到在Actor层次，UE用Controller来充当APawn的逻辑控制者，也有了可以接受玩家输入的PlayerController，和能自行行动的AIController。Actor的逻辑编写介绍完了，那么本篇，我们继续爬升，对于由Actors组成的Level这一层次，UE又是怎么控制的呢？
对Level记不太清楚的朋友，可以翻回去查看“GamePlay架构（二）Level和World”的讲述，简单概括就是World是由一个PersistentLevel和一些subLevels组成的，PersistentLevel切换了，相应的World也会切换。所以本文的关注点是在这么一个对象层次结构下，UE是怎么设计的，我们又能做些什么。
GameMode
Level，在游戏里的概念里，就是关卡的意思。同时作为游戏的玩家和开发者，我们总是会非常经常的提起关卡，但是关卡具体又是个什么定义呢？游戏里的哪些部分可以算是一个关卡？简单的我们都知道有《愤怒的小鸟》或《植物大战僵尸》的关卡，复杂的有大型FPS游戏里的关卡，而对于更大型的《暗黑3》或者大型无缝地图RPG游戏《巫师3》，甚至是号称超级广阔宇宙《无人深空》，我们能直接了当的说出哪部分是关卡吗？游戏行业发展如今，为了更好的组织游戏逻辑和内容资源，也发展出了一些概念来更好的理解和阐述，虽然叫法不同，不过含义理念都是相通的。比如，Cocos2dx会认为游戏就是由不同的Scene切换组成的，每个Scene又由Layer组成；Unity也认为游戏就是一个个Scene；而UE的视角的是，游戏是由一个个World组成的，World又是由Level组成的。这些概念有什么不同？
让我们从游戏本身的机制上分析：
游戏或玩家的节奏，游戏可以分成一个个阶段，马里奥里的关卡就是一个阶段，而RPG游戏的一个大地图也是一个阶段。一个游戏也可能只有一个阶段，比如一直在宇宙里漫游的游戏。通常一个阶段结束后，会有一个结算，阶段之间，玩家也能明显感觉到切换感。
游戏的机制，有时候即使是同样的场景，玩家却也能感觉就像在玩两个不同的游戏，比如MOBA里的同一张地图上的各种不同挑战模式。
游戏的资源划分，有时候也能遇见同一个玩法应用在不同的场景上，比如赛车游戏的不同跑道。有时候也会在游戏的大地图里从酷热的沙漠到寒冷的极地。游戏开发中也总是倾向于给游戏用到的资源划分成组的进行载入和释放。
通过以上的分析，也和以前的一贯思路一样，我们发现在思考“关卡”这件事情上，也是要保持头脑清晰的分清“表示”和“逻辑”。玩法就是“逻辑”，场景就是“表示”。所以我们如果以逻辑来划分游戏，得到的就是一个个World的概念；如果以表示来划分，得到就是一个个Level。一场游戏中，玩法再复杂但也只有一个，场景却可以无限大，所以可以有很多个表示拼接组装，因此是World包含Level，而不是反过来。现在回过头来回想一下Cocos2dx和Unity的世界观，它们的概念还只是在表示层，在游戏实例和关卡之间少了一个更高级的逻辑概念。
因此UE的世界观是，World更多是逻辑的概念，而Level是资源场景表示。以《巫师3》为例，有好几个国家之间通过传送切换，国家内大地图无缝漫游，显然我们知道不可能把一个国家的所有资源都加载进内存，因此在UE里，一个国家就是许多个Level拼接的，而一个国家就是一个World，它们可以有不同的模式玩法。但毕竟AAA游戏很少，通常的，我们的游戏比较简单的用一个Level就够了，否则这个场景表示的概念就应该叫Area更合适了，也因此通常的这里的Level也常常对应游戏里玩家面对的"关卡"，也因此UE里Level的Settings叫做WorldSettings了。
厘清了这些概念了之后，我们就知道，当我们在谈Level的业务逻辑控制的时候，我们实际上谈的是World的业务逻辑。按照UE的设计理念和经过Controller的经历，我想我也不用多解释了从Actor再派生出一个WorldController的方式了，可以直接的享受Actor已经提供的一切福利。一个World的Controller想不出有什么需要展示渲染的，因此可以直接从AInfo派生吧。哦，WorldController是我瞎编的，在UE3里它叫做GameInfo，到了UE4它改名为了GameMode。笼统的讲，一个World就是一个Game，把玩法叫做Mode，我们应该也能接受吧。那我们来看看它：
既然勇敢的承担了游戏逻辑的职责，说他是AInfo家族里的扛把子也不为过，因此GameMode身为一场游戏的唯一逻辑操纵者身兼重任，在功能实现上有许多的接口，但主要可以分为以下几大块：
Class登记，GameMode里登记了游戏里基本需要的类型信息，在需要的时候通过UClass的反射可以自动Spawn出相应的对象来添加进关卡中。前文说过的Controller的类型登记也是在此，GameMode就是比Controller更高一级的领导。
游戏内实体的Spawn，不光登记，GameMode既然作为一场游戏的主要负责人，那么游戏的加载释放过程中涉及到的实体的产生，包括玩家Pawn和PlayerController，AIController也都是由GameMode负责。最主要的SpawnDefaultPawnFor、SpawnPlayerController、ShouldSpawnAtStartSpot这一系列函数都是在接管玩家实体的生成和释放，玩家进入该游戏的过程叫做Login（和服务器统一），也控制进来后在什么位置，等等这些实体管理的工作。GameMode也控制着本场游戏支持的玩家、旁观者和AI实体的数目。
游戏的进度，一个游戏支不支持暂停，怎么重启等这些涉及到游戏内状态的操作也都是GameMode的工作之一，SetPause、ResartPlayer等函数可以控制相应逻辑。
Level的切换，或者说World的切换更加合适，GameMode也决定了刚进入一场游戏的时候是否应该开始播放开场动画（cinematic），也决定了当要切换到下一个关卡时是否要bUseSeamlessTravel，一旦开启后，你可以重载GameMode和PlayerController的GetSeamlessTravelActorList方法和GetSeamlessTravelActorList来指定哪些Actors不被释放而进入下一个World的Level。
多人游戏的步调同步，在多人游戏的时候，我们常常需要等所有加入的玩家连上之后，载入地图完毕后才能一起开始逻辑。因此UE提供了一个MatchState来指定一场游戏运行的状态，意义看名称也是不言自明的，就是用了一个状态机来标记开始和结束的状态，并触发各种回调。
/** Possible state of the current match, where a match is all the gameplay that happens on a single map */
namespace MatchState
{
extern ENGINE_API const FName EnteringMap; // We are entering this map, actors are not yet ticking
extern ENGINE_API const FName WaitingToStart; // Actors are ticking, but the match has not yet started
extern ENGINE_API const FName InProgress; // Normal gameplay is occurring. Specific games will have their own state machine inside this state
extern ENGINE_API const FName WaitingPostMatch; // Match has ended so we aren't accepting new players, but actors are still ticking
extern ENGINE_API const FName LeavingMap; // We are transitioning out of the map to another location
extern ENGINE_API const FName Aborted; // Match has failed due to network issues or other problems, cannot continue
}
思考：多个Level配置不同的GameMode时采用的是哪一个GameMode？
我们知道除了配置全局的GameModeClass之外，我们还能为每个Level单独的配置不同的GameModeClass。但是当一个World由多个Level组成的时候，这样就相当于配置了多个GameModeClass，那么应用的是哪一个？首先第一个原则需要记住的就是，一个World里只会有一个GameMode实例，否则肯定乱套了。因此当有多个Level的时候，一定是PersistentLevel和多个StreamingLevel，这时就算它们配置了不同的GameModeClass，UE也只会为第一次创建World时加载PersistentLevel的时候创建GameMode，在后续的LoadStreamingLevel时候，并不会再动态创建出别的GameMode，所以GameMode从始至终只有一个，PersistentLevel的那个。
思考：Level迁移时GameMode是否保持一致？
在在travelling的时候，如果下一个Level的配置的GameModeClass和当前的不同，那么迁移后是哪个GameMode？
无论travelling采用哪种方式，当前的World都会被释放掉，然后加载创建新的World。但这个过程中，有点区别的是根据bUseSeamlessTravel的不同，UE可以选择哪些Actor迁移到下一个World中去（实现方式是先创建个中间过渡World进行二段迁移（为了避免同时加载进两个大地图撑爆内存），具体见引用3）。分两种情况：
不开启bUseSeamlessTravel，那么在travelling的时候（ServerTravel或ClientTravel），当前的World会被释放，所以当前的GameMode就被释放掉。新的World加载，就会根据新的GameModeClass创建新的GameMode。所以这时是不同的。
开启bUseSeamlessTravel，travelling时，当前World的GameMode会调用GetSeamlessTravelActorList：
void AGameMode::GetSeamlessTravelActorList(bool bToTransition, TArray<AActor*>& ActorList)
{
	UWorld* World = GetWorld();
	// Get allocations for the elements we're going to add handled in one go
	const int32 ActorsToAddCount = World->GameState->PlayerArray.Num() + (bToTransition ?  3 : 0);
	ActorList.Reserve(ActorsToAddCount);
	// always keep PlayerStates, so that after we restart we can keep players on the same team, etc
	ActorList.Append(World->GameState->PlayerArray);
	if (bToTransition)
	{
		// keep ourselves until we transition to the final destination
		ActorList.Add(this);
		// keep general game state until we transition to the final destination
		ActorList.Add(World->GameState);
		// keep the game session state until we transition to the final destination
		ActorList.Add(GameSession);
		// If adding in this section best to increase the literal above for the ActorsToAddCount
	}
}
在第一步从CurrentWorld到TransitionWorld的迁移时候，bToTransition==true，这个时候GameMode也会迁移进TransitionWorld（TransitionMap可以在ProjectSettings里配置），也包括GameState和GameSession，然后CurrentWorld释放掉。第二步从TransitionWorld到NewWorld的迁移，GameMode（已经在TransitionWorld中了）会再次调用GetSeamlessTravelActorList，这个时候bToTransition==false，所以第二次的时候如代码所见当前的GameMode、GameState和GameSession就被排除在外了。这样NewWorld再继续InitWorld的时候，一发现当前没有GameMode，就会根据配置的GameModeClass重新生成一个出来。所以这个时候GameMode也是不同的。
结论是，UE的流程travelling，GameMode在新的World里是会新生成一个的，即使Class类型一致，即使bUseSeamlessTravel，因此在travelling的时候要小心GameMode里保存的状态丢失。不过Pawn和Controller默认是一致的。
思考：哪些逻辑应该写在GameMode里？哪些应该写在Level Blueprint里？
我们依旧要问这个老土的问题。根据我们前面的知识，我们知道每个Level其实也是有自己的LevelScriptActor的，那么这两个有什么区别？可以从这几个方面来回答：
概念上，Level是表示，World是逻辑，一个World如果有很多个Level拼在一起，那么也就是有了很多个LevelScriptActor，无法想象在那么多个地方写一个完整的游戏逻辑。所以GameMode应该专注于逻辑的实现，而LevelScriptActor应该专注于本Level的表示逻辑，比如改变Level内某些Actor的运动轨迹，或者某一个区域的重力，或者触发一段特效或动画。而GameMode应该专注于玩法，比如胜利条件，怪物刷新等。
组合上，同Controller应用到Pawn一样道理，因为GameMode是可以应用在不同的Level的，所以通用的玩法应该放在GameMode里。
GameMode只在Server存在（单机游戏也是Server），对于已经连接上Server的Client来说，因为游戏的状态都是由Sever决定的，Client只是负责展示，所以Client上是没有GameMode的，但是有LevelScriptActor，所以GameMode里不要写Client特定相关的逻辑，比如操作UI等。但是LevelScriptActor还是有的，而且支持RPC，即使如此，LevelScriptActor还是应该只专注于表现，比如网络中触发一个特效火焰。至于UI，可以通过PlayerController的RPC，然后转发到GameInstance来操作。
跟下层的PlayerController比较，GameMode关心的是构建一个游戏本身的玩法，PlayerController关心的玩家的行为。这两个行为是独立正交可以自由组合的。所以想想哪些逻辑属于游戏，哪些属于玩家，就应该清楚写在哪里了。
跟上层的GameInstance比较，GameInstance关注的是更高层的不同World之间的逻辑，虽然有时候他也把手伸下来做些UI的管理工作，不过严谨来说，在UE里UI是独立于World的一个结构，所以也还算能理解。因此可以把不同GameMode之间协调的工作交给GameInstance，而GameMode只专注自己的玩法世界。
GameState
上回说到了APlayerState用来保存玩家的游戏数据，那么同样的，对于一场游戏，也需要一个State来保存当前游戏的状态数据，比如任务数据等。跟APlayerState一样，GameState也选择从AInfo里继承，这样在网络环境里也可以Replicated到多个Client上面去。
比较简单，第一个MatchState和相关的回调就是为了在网络中传播同步游戏的状态使用的（记得GameMode在Client并不存在，但是GameState是存在的，所以可以通过它来复制），第二部分是玩家状态列表，同样的如果在Client1想看到Client2的游戏状态数据，则Client2的PlayerState就必须广播过来，因此GameState把当前Server的PlayerState都收集了过来，方便访问使用。
关于使用，开发者可以自定义GameState子类来存储本GameMode的运行过程中产生的数据（那些想要replicated的!），如果是GameMode游戏运行的一些数据，又不想要所有的客户端都可以看到，则也可以写在GameMode的成员变量中。重复遍，PlayerState是玩家自己的游戏数据，GameInstance里是程序运行的全局数据。
GameSession
是在网络联机游戏中针对Session使用的一个方便的管理类，并不存储数据，本文重点也不在网络，故不做过多解释，可暂时忽略，留待网络章节再讨论。在单机游戏中，也存在该类对象用来LoginPlayer，不过因为只是作为辅助类，那也可看作GameMode本身的功能，所以不做过多讨论。
总结
现在，我们也算讨论完了Level（World）层次的控制，对于一场游戏而言，我们最关心的是怎么协调好整个场景的表现（LevelBlueprint）和游戏玩法的编写（GameMode）。UE再次用Actor分化派生的思想，用同样套路的AGameMode和AGameState支持了玩法和表现的解耦分离和自由组合，并很好的支持了网络间状态的同步。同时也提供了一个逻辑的实体来负责创建关系内那些关键的Pawn和Controller们，在关卡切换（World）的时候，也有了一个负责对象来处理一些本游戏的特定情况处理。
我们的逻辑之旅还没到终点，让我们继续爬升，下篇将介绍Player。
修订
在笔者书写本篇的同时（UE4.13.2），UE同时也完成了4.14的preview3的工作，roadmap里“GameMode Cleanup”的工作也已经完成了，第二天发现4.14正式发布了。因此为了紧跟UE最新潮流时尚，以后要是文章内容所涉及内容被UE修改完善优化的，也会采用修订的方式进行补充说明，之后不再特意作此声明。
4.14 GameMode，GameState的清理
根据搜索到的最早记录"[Request/Improvment] GameMode cleanup."(09-14-2014)，是有人抱怨当前的GameMode实现了太多的默认逻辑（例如多人的Match），虽然方便了一些人使用，但是也确实加大了理解的难度，并且有时候还得去屏蔽删除一些默认逻辑。然后顺便吐槽了一番AActor里的Damage，笔者也表示这确实不是AActor应该管的事情。
言归正传，UE在2016-08-24的时候开始加进roadmap，并终于在4.14里实现完成了。如前所述，就是把GameMode和GameState的一些共同最基础部分抽到基类AGameModeBase和AGameStateBase里，并把现在的GameMode和GameState依然当作多人联机的默认实现。所以以后大家如果想实现一个比较简单的单机GameMode就可以直接从AGameModeBase里继承了。
可以看到，其实就是把MatchState给往下拉了一层，并把一些多玩家控制的逻辑，合起来就是网络联机游戏的默认逻辑给抽离开了。同样的对于GameState也做了处理：
把MatchState也抽离到了下层，并增加了几个方便的字段引用（如AuthorityGameMode）。总体功能职责架构上还是没有什么大变化的，吓死我了。
引用
GameMode
GameState
Travelling in Multiplayer
UE4.13.2
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（八）Player</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/23826859
引言
回顾上文，我们谈完了World和Level级别的逻辑操纵控制，如同分离组合的AController一样，UE在World的层次上也采用了一个分离的AGameMode来抽离了游戏关卡逻辑，从而支持了逻辑的组合。本篇我们继续上升一个层次，考虑在World之上，游戏还需要哪些逻辑控制？
暂时不考虑别的功能系统（如社交系统，统计等各种），单从游戏性来讨论，现在闭上眼睛，想象我们已经藉着UE的伟力搭建了好了一个个LevelWorld，嗯，就像《西部世界》一样，场景已经搭建好了，世界规则故事也编写完善，现在需要干些什么？当然是开始派玩家进去玩啦！
大家都是老玩家了，想想我们之前玩的游戏类型：
玩家数目是单人还是多人
网络环境是只本地还是联网
窗口显示模式是单屏还是分屏
输入模式是共用设备还是分开控制（比如各有手柄）
也许还有别的不同
假如你是个开发游戏引擎的，会怎么支持这些不同的模式？以笔者见识过的大部分游戏引擎，解决这个问题的思路就是不解决，要嘛是限制功能，要嘛就是美名其曰让开发者自己灵活控制。不过想了一下，这也不能怪他们，毕竟很少有引擎能像UE这样历史悠久同时又能得到足够多的游戏磨练，才会有功夫在GamePlay框架上雕琢。大部分引擎还是更关注于实现各种绚丽的功能，至于怎么在上面开展游戏逻辑，那就是开发者自己的事了。一个引擎的功能是否强大，是基础比拼指标；而GamePlay框架作为最高层直面用户的对接接口，是一个引擎的脸面。所以有兴趣游戏引擎研究的朋友们，区分一个引擎是否“优秀”，第二个指标是看它是否设计了一个优雅的游戏逻辑编写框架，一般只有基础功能已经做得差不多了的引擎开发者才会有精力去开发GamePlay框架，因为游戏引擎不止渲染！
言归正传，按照软件工程的理念，没有什么问题是不能通过加一个间接层解决的，不行就加两层！所以既然我们在处理玩家模式的问题，理所当然的是加个间接层，将玩家这个概念抽象出来。
那么什么是玩家呢？狭义的讲，玩家就是真实的你，和你身旁的小伙伴。广义来说，按照图灵测试理论，如果你无法分辨另一方是AI还是人，那他其实就跟玩家毫无区别，所以并不妨碍我们将网络另一端的一条狗当作玩家。那么在游戏引擎看来，玩家就是输入的发起者。游戏说白了，也只是接受输入产生输出的一个程序。所以有多少输入，这些输入归多少组，就有多少个玩家。这里的输入不止包括本地键盘手柄等输入设备的按键，也包括网线里传过来的信号，是广义的该游戏能接受到的外界输入。注意输出并不是玩家的必要属性，一个玩家并不一定需要游戏的输出，想象你闭上眼睛玩马里奥或者有个网络连接不断发送来控制信号但是从来不接收反馈，虽然看起来意义不大，但也确实不能说这就不是游戏。
在UE的眼里，玩家也是如此广义的一个概念。本地的玩家是玩家，网络联机时虽然看不见对方，但是对方的网络连接也可以看作是个玩家。当然的，本地玩家和网络玩家毕竟还是差别很大，所以UE里也对二者进行了区分，才好更好的管理和应用到不同场景中去，比如网络玩家就跟本地设备的输入没多大关系了嘛。
UPlayer
让我们假装自己是UE，开始编写Player类吧。为了利用上UObject的那些现有特性，所以肯定是得从UObject继承了。那能否是AActor呢？Actor是必须在World中才能存在的，而Player却是比World更高一级的对象。玩游戏的过程中，LevelWorld在不停的切换，但是玩家的模式却是脱离不变的。另外，Player也不需要被摆放在Level中，也不需要各种Component组装，所以从AActor继承并不合适。那还是保持简单吧：
如图可见，Player和一个PlayerController关联起来，因此UE引擎就可以把输入和PlayerController关联起来，这也符合了前文说过的PlayerController接受玩家输入的描述。因为不管是本地玩家还是远程玩家，都是需要控制一个玩家Pawn的，所以自然也就需要为每个玩家分配一个PlayerController，所以把PlayerController放在UPlayer基类里是合理的。
ULocalPlayer
然后是本地玩家，从Player中派生下来LocalPlayer类。对本地环境中，一个本地玩家关联着输入，也一般需要关联着输出（无输出的玩家毕竟还是非常少见）。玩家对象的上层就是引擎了，所以会在GameInstance里保存有LocalPlayer列表。
UE4里的ULocalPlayer也如图所见，ULocalPlayer比UPlayer多了Viewport相关的配置（Viewport相关的内容在渲染章节讲述），也终于用SpawnPlayerActor实现了创建出PlayerController的功能。GameInstance里有LocalPlayers的信息之后，就可以方便的遍历访问，来实现跟本地玩家相关操作。
关于游戏的详细加载流程目前不多讲述（按惯例在相应引擎流程章节讲述），现在简单了解一下LocalPlayer是怎么在游戏的引擎的各个环节发挥作用的。UE在初始化GameInstance的时候，会先默认创建出一个GameViewportClient，然后在内部再转发到GameInstance的CreateLocalPlayer：
ULocalPlayer* UGameInstance::CreateLocalPlayer(int32 ControllerId, FString& OutError, bool bSpawnActor)
{
	ULocalPlayer* NewPlayer = NULL;
	int32 InsertIndex = INDEX_NONE;
	const int32 MaxSplitscreenPlayers = (GetGameViewportClient() != NULL) ? GetGameViewportClient()->MaxSplitscreenPlayers : 1;
    //已略去错误验证代码，MaxSplitscreenPlayers默认为4
	NewPlayer = NewObject<ULocalPlayer>(GetEngine(), GetEngine()->LocalPlayerClass);
	InsertIndex = AddLocalPlayer(NewPlayer, ControllerId);
	if (bSpawnActor && InsertIndex != INDEX_NONE && GetWorld() != NULL)
	{
		if (GetWorld()->GetNetMode() != NM_Client)
		{
			// server; spawn a new PlayerController immediately
			if (!NewPlayer->SpawnPlayActor("", OutError, GetWorld()))
			{
				RemoveLocalPlayer(NewPlayer);
				NewPlayer = NULL;
			}
		}
		else
		{
			// client; ask the server to let the new player join
			NewPlayer->SendSplitJoin();
		}
	}
	return NewPlayer;
}
可以看到，如果是在Server模式，会直接创建出ULocalPlayer，然后创建出相应的PlayerController。而如果是Client（比如Play的时候选择NumberPlayer=2,则有一个为Client），则会先发送JoinSplit消息到服务器，在载入服务器上的Map之后，再为LocalPlayer创建出PlayerController。
而在每个PlayerController创建的过程中，在其内部会调用InitPlayerState：
void AController::InitPlayerState()
{
	if ( GetNetMode() != NM_Client )
	{
		UWorld* const World = GetWorld();
		const AGameModeBase* GameMode = World ? World->GetAuthGameMode() : NULL;
		//已省略其他验证和无关部分
		if (GameMode != NULL)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Owner = this;
			SpawnInfo.Instigator = Instigator;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnInfo.ObjectFlags |= RF_Transient;	// We never want player states to save into a map
			PlayerState = World->SpawnActor<APlayerState>(GameMode->PlayerStateClass, SpawnInfo );
			// force a default player name if necessary
			if (PlayerState && PlayerState->PlayerName.IsEmpty())
			{
				// don't call SetPlayerName() as that will broadcast entry messages but the GameMode hasn't had a chance
				// to potentially apply a player/bot name yet
				PlayerState->PlayerName = GameMode->DefaultPlayerName.ToString();
			}
		}
	}
}
这样LocalPlayer最终就和PlayerState对应了起来。而网络联机时其他玩家的PlayerState是通过Replicated过来的。
我们谈了那么久的玩家就是输入，体现在在每个PlayerController接受Player的时候：
void APlayerController::SetPlayer( UPlayer* InPlayer )
{
    //[...]
	// Set the viewport.
	Player = InPlayer;
	InPlayer->PlayerController = this;
	// initializations only for local players
	ULocalPlayer *LP = Cast<ULocalPlayer>(InPlayer);
	if (LP != NULL)
	{
		// Clients need this marked as local (server already knew at construction time)
		SetAsLocalPlayerController();
		LP->InitOnlineSession();
		InitInputSystem();
	}
	else
	{
		NetConnection = Cast<UNetConnection>(InPlayer);
		if (NetConnection)
		{
			NetConnection->OwningActor = this;
		}
	}
	UpdateStateInputComponents();
	// notify script that we've been assigned a valid player
	ReceivedPlayer();
}
可见，对于ULocalPlayer，APlayerController内部会开始InitInputSystem()，接着会创建相应的UPlayerInput，BuildInputStack等初始化出和Input相关的组件对象。现在先明白到LocalPlayer才是PlayerController产生的源头，也因此才有了Input就够了，特定的Input事件流程分析在后续章节再细述。
思考：为何不在LocalPlayer里编写逻辑？
作为游戏开发者，相信大家都有这么个体会，往往在游戏逻辑代码中总会有一个自己的Player类，里面放着这个玩家的相关数据和逻辑业务。可是在UE里为何就不见了这么个结构？也没见UE在文档里有描述推荐你怎么创建自己的Player。
这个可能有两个原因，一是UE从FPS-Specify游戏起家，不像现在的各种手游有非常重的玩家系统，在UE的眼中，Level和World才是最应该关注的对象，因此UE的视角就在于怎么在Level中处理好Player的逻辑，而非在World之外的额外操作。二是因为在一个World中，上文提到其实已经有了Pawn-PlayerController和PlayerState的组合了，表示、逻辑和数据都齐备了，也就没必要再在Level掺和进Player什么事了。当然你也可以理解为PlayerController就是Player在Level中的话事人。
凡事留一线，日后好相见。尽管如此，UE还是给了我们自定义ULocalPlayer子类的机会：
//class UEngine：
/** The class to use for local players. */
UPROPERTY()
TSubclassOf<class ULocalPlayer>  LocalPlayerClass;
/** @todo document */
UPROPERTY(globalconfig, noclear, EditAnywhere, Category=DefaultClasses, meta=(MetaClass="LocalPlayer", DisplayName="Local Player Class"))
FStringClassReference LocalPlayerClassName;
你可以在配置中写上LocalPlayer的子类名称，让UE为你生成你的子类。然后再在里面写上一些特定玩家的数据和逻辑也未尝不可，不过这部分额外扩展的功能就得用C++来实现了。
UNetConnection
非常耐人寻味的是，在UE里，一个网络连接也是个Player：
包含Socket的IpConnection也是玩家，甚至对于一些平台的特定实现如OculusNet的连接也可以当作玩家，因为对于玩家，只要能提供输入信号，就可以当作一个玩家。
追根溯源，UNetConnection的列表保存在UNetDriver，再到FWorldContext，最后也依然是UGameInstance，所以和LocalPlayer的列表一样，是在World上层的对象。
本篇先前瞻一下结构，对于网络部分不再细述。
总结
本篇我们抽象出了Player的概念，并依据使用场景派生出了LocalPlayer和NetConnection这两个子类，从此Player就不再是一个虚无缥缈的概念，而是UE里的逻辑实体。UE可以根据生成的Player对象的数量和类型的不同，在此上实现出不同的玩家控制模式，LocalPlayer作为源头Spawn出PlayerController继而PlayerState就是实证之一。而在网络联机时，把一个网络连接看作是一个玩家这个概念，把在World之上的输入实体用Player统一了起来，从而可以实现出灵活的本地远程不同玩家模式策略。
尽管如此，UPlayer却像是深藏在UE里的幕后功臣，UE也并不推荐直接在Player里编程，而是利用Player作为源头，来产生构建一系列相关的机制。但对于我们游戏开发者而言，知道并了解UE里的Player的概念，是把现实生活同游戏世界串联起来的很重要的纽带。我们在一个个World里向上仰望，还能清楚的看见一个个LocalPlayer或NetConnection仿佛在注视着这片大地，是他们为World注入了生机。
已经到头了？并没有，我们继续向上逆风飞翔，终将得见游戏里的神：GameInstance。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（九）GameInstance</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/24005952
引言
上篇我们讲到了UE在World之上，继续抽象出了Player的概念，包含了本地的ULocalPlayer和网络的UNetConnection，并以此创建出了World中的PlayerController，从而实现了不同的玩家模式策略。一路向上，依照设计里一个最朴素的原理：自己是无法创建管理自身的，所以Player也需要一个创建管理和存储的地方。另一方面，上文提到Player固然可以负责一些跟玩家相关的业务逻辑，但是对于World之上协调管理的逻辑却也仍然无处安放。
如果是有一定的游戏开发实战经验的朋友也一定能体会到，在自己开发的游戏中，往往除了我们上文提到的Player类，常常会创建一个Game类，比如BattleGame、WarGame或HappyGame等等。Game之前的名词往往都是游戏的开发代号。这倒不是因为我们如此热衷创建各种Manager类，而是确实需要一个大管家来干一些协调的活。一般的游戏引擎都只会暴露给你它自己引擎的管理类，如Director，Engine或Application之类的，但是却不会主动在Game类的创建管理上为你提供方便。游戏引擎的出现，最开始其实只是因为一些人发现游戏做着做着，有一大部分功能是可以复用的，于是就把它抽离了出来方便做下一款游戏。在那个时候，人们对游戏还是处于开荒探索的阶段，游戏引擎只是一大堆功能的复合体，就像叮当猫的口袋一样，互相比谁掏出的工具最强大。然而即使到了现代，绝大部分的引擎的思想却还停留在上个世纪，仍然执着于罗列Feature列表，却忘了真正的游戏开发人员天天面对的游戏业务逻辑编写，没有思考在那方面如何也下一番功夫去帮助开发者。人们对比UE和其他游戏引擎时，也会常常说出的一句话是：“别忘了Epic自己也是做游戏的”（虚幻竞技场，战争机器，无尽之剑……）。从这一点也可以看出，UE很大的得益于Epic实战游戏开发的反哺，这一方面Unity就有点吃亏了，没有自己亲自下手干脏活累活，就不懂得急人民群众之所急。所以如果一个游戏引擎能把GamePlay也做好了，那就不止是口袋了，而是知你懂你的叮当猫本身。
GameInstance
简单的事情就不用多讲了，UE提供的方案是一以贯之的，为我们提供了一个GameInstance类。为了受益于UObject的反射创建能力，直接继承于UObject，这样就可以依据一个Class直接动态创建出来具体的GameInstance子类。
我并不想罗列所有的接口，UGameInstance里的接口大概有4类：
1. 引擎的初始化加载，Init和ShutDown等（在引擎流程章节会详细叙述）
2. Player的创建，如CreateLocalPlayer，GetLocalPlayers之类的。
3. GameMode的重载修改，这是从4.14新增加进来改进，本来你只能为特定的某个Map配置好GameModeClass，但是现在GameInstance允许你重载它的PreloadContentForURL、CreateGameModeForURL和OverrideGameModeClass方法来hook改变这一流程。
4. OnlineSession的管理，这部分逻辑跟网络的机制有关（到时候再详细介绍），目前可以简单理解为有一个网络会话的管理辅助控制类。
而GameInstance是在GameEngine里创建的（先不谈UEditorEngine）：
void UGameEngine::Init(IEngineLoop* InEngineLoop)
{
    //[...]
	// Create game instance.  For GameEngine, this should be the only GameInstance that ever gets created.
	{
		FStringClassReference GameInstanceClassName = GetDefault<UGameMapsSettings>()->GameInstanceClass;
		UClass* GameInstanceClass = (GameInstanceClassName.IsValid() ? LoadObject<UClass>(NULL, *GameInstanceClassName.ToString()) : UGameInstance::StaticClass());
		if (GameInstanceClass == nullptr)
		{
			UE_LOG(LogEngine, Error, TEXT("Unable to load GameInstance Class '%s'. Falling back to generic UGameInstance."), *GameInstanceClassName.ToString());
			GameInstanceClass = UGameInstance::StaticClass();
		}
		GameInstance = NewObject<UGameInstance>(this, GameInstanceClass);
		GameInstance->InitializeStandalone();
	}
	//[...]
 }
//在BaseEngine.ini或DefaultEngine.init里你可以配置GameInstanceClass
[/Script/EngineSettings.GameMapsSettings]
GameInstanceClass=/Script/Engine.GameInstance
先从配置中取出GameInstanceClass，然后动态创建，一目了然。
思考：GameInstance只有一个吗？
一般而言，是的。对于我们自己开发的游戏而言，我们始终只需要关注自己的一亩三分地，那么你可以认为你子类化的那个GameInstance就像个单件一样，全局唯一只有一个，从游戏的开始到结束。但既然是本系列文章的读者，自然也是不甘于只了解这么多的。
正如把网络连接也当作Player这个概念一样，我们此时也需要重新审视一下Game这个概念。什么是一个Game?对于玩家而言，Game就是从打开到关闭的这整个过程说展现的内容。但是对于开发者来说，这个概念就需要扩充一下了。假设有个引擎支持双击图标一下子开出4个窗口来让4个玩家独立运行，你能说得清这是一个Game还是4个Game在运行吗？哪一种说法都能自圆其说，但关键是哪一种概念划分能更好的让我们管理组织结构。因此针对这种情况，如果是这4个窗口一点都不互相关联，或者只是单独的共用地图资源，那么用4个Game的概念来管理就更为合适。如果这4个窗口里运行的内容，实际上只是在同一个关卡里本地对战，内存里互相直接通信，那用一个Game加上4个Player的概念就会变得更合适。所以针对这点，你可以把Game理解为就像进程一样，进程可以在同一个exe上多开，Game也可以在同一份游戏资源上开出多个运行实例；进程之间可以互相通信协作，Game的不同实例也可以互相沟通，不管是内存中直接在Engine的协调下完成，还是通过Socket通信。
另一方面，一般游戏引擎都只是服务于游戏本身，而对于其配套的各种编辑器就像是对待外来的打工者一样，编辑器往往只负责最终输出游戏资源。由于应用场景的不同，编辑器的架构也常常根据相应平台而定，五花八门，有用Qt，MFC，WPF等各种平台UI框架。而对于另一些有大志向的引擎，比如Unity和UE，其编辑器就是采用引擎自绘的方案（其优劣暂不分析，以后聊到UI框架再细说）。所以游戏引擎这个时候，就更加的拔高了一个层次，就不再只是个“游戏”引擎了，而是个“程序”引擎了。因此UE本身的这套框架不光要服务游戏，还要服务编辑器，甚至是另外一些辅助程序。所以，Game的概念也就扩充到了更上层的“程序”，变得更广义了。
言归正传，因为UE的这套Editor自绘机制，还有PIE（PlayInEditor），进程里其实是可以同时有多个GameInstance的，如正在编辑的EditorWorld所属于的，和Play之后的World属于的。我想，这也就是为何UE把它叫做GameInstance而不是简单的Game的含义，其名字中就隐含了多个Instance的深意。我们现在再次回顾一下(GamePlay架构（三）WorldContext，GameInstance，Engine)最后的结构图，了解一下GameInstance又是被谁管理的：
当初我们是以数据的视角，在考察WorldContext的从属的时候讨论过这个结构。现在以逻辑的角度，明白了GameInstance也会被上层的Engine实例出来多个，就会有更深的理解了。
再扩充一下，在Engine之下允许同时运行多个GameInstance，还会有许多其他好处，就像操作系统允许一份资源运行多个进程实例一样，Engine就可以站在更高的层次上管理协调多个Game，同时也能更加的深入到Game内部去得到更多的优化。比如未来要实现游戏本地的host多开并管理，或者在Server同时Host一个Map的多个实例(现在只能一个……还是有很多工作要做啊)，这对于开发MMO网游是非常需要的功能，虽然目前UE在这一块的具体工作还有些薄弱，但至少可扩展的可能性是已经保证了的（动手能力强的高手可以在此基础上定制）。一般而言，间接多一层，就多了一层的灵活性，所以很多引擎其实就是把Game和Engine揉在了一块没有为了GamePlay框架而分开。
思考：哪些逻辑应该放在GameInstance？
第二个惯例的问题是，这一层应该写些什么逻辑。顾名思义，既然是作为游戏中全局唯一的长者，我们就应该给他全局的控制权。在逻辑层面，GameInstance往下看是：
1. Worlds，Level的切换实际发生地是Engine，而GameInstance可以说是UE之神其下的唯一代言人，所以GameInstance也可以代之管理World的切换等。我们可以在GameInstance里实现各种逻辑最后调用Engine的OpenLevel等接口。
2. Players，虽然一般来说我们直接控制Players的机会不多，都是配置好了就行。但要是到了需要的时候，GameInstance也实现了许多的接口可以让你动态的添加删除Players。
3. UI，UE的UI是另一套World之外的系统，虽然同属于Viewport的显示之下，但是控制结构跟Actor们并不一样。所以我们常常会需要控制UI各种切换的业务逻辑，虽然在Widget的Graph里也可以写些简单的切换，但是要想复用某些切换逻辑的时候，在特定的Wdiget里就不合适了，而GameMode一方面局限于Level，另一方面又只存在于Server；PlayerController也是会切换掉的，同时又只存在于World中，所以最后比较合适的就剩下GameInstance了，以后当然有可能了可能会扩展出个UI的业务逻辑Manger类，不过那是后话了。
4. 全局的配置，也常常需要根据平台改变一些游戏的配置，Execute一些ConsoleCommand，GameInstance也是这些命令的存放地。
5. 游戏的额外第三方逻辑，如果你的游戏需要其他一些控制，比如自己写的网络通信、自定义的配置文件或者自己的一些程序算法，如果简单的话，GameInstance也可以一放，等复杂起来了，也可以把GameInstance当作一个模块容器，你可以在里面再扩展出来其他的子逻辑模块。当然如果是插件的话，还是在自己的插件Module里面自行管理逻辑，然后把协调工作交给GameInstance来做。
而在数据层面上，我们层层上来，已经有了针对一个Player的Contoller的PlayerState，也有了针对World的GameMode的GameState，到了更全局之上，自然的GameInstance就应该存储一些全局的状态数据。所以你可以在GameInstance的成员变量中添加一些全局的状态，或者是那些想要在Level之外持续存在的对象。不过需要注意的一点是，GameInstance成员变量中最好只保存那些“临时”的数据，而对于那些想要持久序列化保存的数据，我们就需要接下来的SaveGame了。把持久的数据直接放在SaveGame，用的时候直接读取出来，之后再直接在其上更新，好处是只用维护一份，省得要保存的时候，还去想到底要选GameInstance的哪些成员变量中来保存，一开始就设计选好，以后就方便了。
SaveGame
UE连玩家存档都帮你做了！得益于UObject的序列化机制，现在你只需要继承于USaveGame，并添加你想要的那些属性字段，然后这个结构就可以序列化保存下来的。玩家存档也是游戏中一个非常常见的功能，差的引擎一般就只提供给你读写文件的接口，好一点的会继续给你一些序列化机制，而更好的则会服务得更加周到。UE为我们在蓝图里提供了SaveGame的统一接口，让你只用关心想序列化的数据。
USaveGame其实就是为了提供给UE一个UObject对象，本身并不需要其他额外的控制，所以它的类是如此的简单以至于我能直接把它的全部声明展示出来：
UCLASS(abstract, Blueprintable, BlueprintType)
class ENGINE_API USaveGame : public UObject
{
	/**
	 *	@see UGameplayStatics::CreateSaveGameObject
	 *	@see UGameplayStatics::SaveGameToSlot
	 *	@see UGameplayStatics::DoesSaveGameExist
	 *	@see UGameplayStatics::LoadGameFromSlot
	 *	@see UGameplayStatics::DeleteGameInSlot
	 */
	GENERATED_UCLASS_BODY()
};
而UGameplayStatics作为暴露给蓝图的接口实现部分，其内部的实现是：
先在内存中写入一些SavegameFileVersion之类的控制文件头，然后再序列化USaveGame对象，接着会找到ISaveGameSystem接口，最后交于真正的子类实现文件的保存。目前的默认实现是FGenericSaveGameSystem，其内部也只是转发到直接的文件读写接口上去。但你也可以实现自己的SaveGameSystem，不管是写文件或者是网络传输，保存到不同的地方去。或者是内部调用OnlineSubsystem的Storage接口，直接把玩家存档保存到Steam云存储中也可以。
因此可见，单单是玩家存档这件边角的小事，UE作为一个深受游戏开发淬炼过的引擎，为了方便自己，也同时造福我们广大开发者，已经实现了这么一套完善的机制。
关于存档数据关联的逻辑，再重复几句，对于那些需要直接在全局处理的数据逻辑，也可以直接在SaveGame中写方法来实现。比如实现AddCoin接口，对外隐藏实现，对内可以自定义附加一些逻辑。USaveGame可以看作是一个全局持久数据的业务逻辑类。跟GameInstance里的数据区分就是，GameInstance里面的是临时的数据，SaveGame里是持久的。清晰这一点区分，到时就不会纠结哪些属性放在哪里，哪些方法实现在哪里了。
注意一下，SaveGameToSlot里的SlotName可以理解为存档的文件名，UserIndex是用来标识是哪个玩家在存档。UserIndex是预留的，在目前的UE实现里并没有用到，只是预留给一些平台提供足够的信息。你也可以利用这个信息来为多个不同玩家生成不同的最后文件名什么的。而ISaveGameSystem是IPlatformFeaturesModule提供的模块接口，关于模块的机制，等引擎流程章节再说吧，目前可以简单理解为一个单件对象里提供了一些平台相关的接口对象。
总结
至此，我们可以说已经介绍完了GamePlay下半部分——逻辑控制。在蓝图层，UE并不向BP直接暴露Engine概念，即使在C++层，在实现GamePlay业务时也是很少需要真正直接操纵Engine的时候。如果GamePlay已经足够好，那么Engine自然就可以隐居幕后了。UE用GameInstance实现了全局的控制，并支持多GameInstance来实现编辑器，最后在存档的时候还可以用到SaveGame的方便的接口。
下篇，就是GamePlay章节的最终章，我们将会对GamePlay架构的（一到九）篇进行回顾归纳总结巩固，以一个承上启下总览的眼光，再来重新审视一下UE的整套GamePlay框架，下个章节见。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（十）总结</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/24170697
引言
通过对前九篇的介绍，至此我们已经了解了UE里的游戏世界组织方式和游戏业务逻辑的控制。行百里者半九十，前述的篇章里我们的目光往往专注在于特定一个类或者对象，一方面固然可以让内容更有针对性，但另一方面也有了身在山中不见山的困惑。本文作为GamePlay章节的最终章，就是要回顾我们之前探讨过的内容，以一个更高层总览的眼光，把之前的所有内容有机组织起来，思考整体的结构和数据及逻辑的流向。
游戏世界
如果我们在最初篇所问的，如果让你来制作一款3D游戏引擎，你会怎么设计其结构？已经知道，在UE的眼里，游戏世界的万物皆Actor，Actor再通过Component组装功能。Actor又通过UChildActorComponent实现Actor之间的父子嵌套。(GamePlay架构（一）Actor和Component)
众多的各种Actor子类又组装成了Level(GamePlay架构（二）Level和World):
如此每一个Level就拥有了一座Actor的森林，你可以根据自己的需要定制化Level，比如有些Level是临时Loading场景，有些只是保存光照，有些只是一块静态场景。UE用Level这种细一些粒度的对象为你的想象力提供了极大的自由度，同时也能方便团队内的平行协作。
一个个的Level，又进一步组装成了World:
就像地球上的大陆板块一样，World允许多个Level静态的通过位置摆放在游戏世界中，也允许运行时动态的加载关卡。
而World之间的切换，UE用了一个WorldContext来保存切换的过程信息。玩家在切换PersistentLevel的时候，实际上就相当于切换了一个World。而再往上，就是整个游戏唯一的GameInstance，由Engine对象管理着。(GamePlay架构（三）WorldContext，GameInstance，Engine)
到了World这一层，整个游戏的渲染对象就齐全了。但是游戏引擎并不只是渲染，因此为了让玩家也各种方式接入World中开始游戏。GameInstance下不光保存着World，同时也存储着Player，有着LocalPlayer用于表示本地的玩家，也有NetConnection当作远端的连接。（GamePlay架构（八）Player）：
玩家利用Player对象接入World之后，就可以开始控制Pawn和PlayerController的生成，有了附身的对象和摄像的眼睛。最后在Engine的Tick心跳脉搏驱动下开始一帧帧的逻辑更新和渲染。
数据和逻辑
说完了游戏世界的表现组成，那么对于一个GamePlay框架而言自然需要与其配套的业务逻辑架构。GamePlay架构的后半部分就自底向上的逐一分析了各个层次的逻辑载体，按照MVC的思想，我们可以把整个游戏的GamePlay分为三大部分：表现（View）、逻辑（Controller）、数据（Model）。一图胜千言：
(请点击看大图)
最左侧的是我们已经讨论过的游戏世界表现部分，从最最根源的UObject和Actor，一直到UGameEngine，不断的组合起来，形成丰富的游戏世界的各种对象。
从UObject派生下来的AActor，拥有了UObject的反射序列化网络同步等功能，同时又通过各种Component来组装不同组件。UE在AActor身上同时利用了继承和组合的各自优点，同时也规避了彼此的一些缺点，我不得不说，UE在这一方面度把握得非常的平衡优雅，既不像cocos2dx那样继承爆炸，也不像Unity那样走极端全部组件组合。
AActor中一些需要逻辑控制的成员分化出了APawn。Pawn就像是棋盘上的棋子，或者是战场中的兵卒。有3个基本的功能：可被Controller控制、PhysicsCollision表示和MovementInput的基本响应接口。代表了基本的逻辑控制物理表示和行走功能。根据这3个功能的定制化不同，可以派生出不同功能的的DefaultPawn、SpectatorPawn和Character。(GamePlay架构（四）Pawn)
AController是用来控制APawn的一个特殊的AActor。同属于AActor的设计，可以让Controller享受到AActor的基本福利，而和APawn分离又可以通过组合来提供更大的灵活性，把表示和逻辑分开，独立变化。(GamePlay架构（五）Controller)。而AController又根据用法和适用对象的不同，分化出了APlayerController来充当本地玩家的控制器，而AAIController就充当了NPC们的AI智能。(GamePlay架构（六）PlayerController和AIController)。而数据配套的就是APlayerState，可以充当AController的可网络复制的状态。
到了Level这一层，UE为我们提供了ALevelScriptActor（关卡蓝图）当作关卡静态性的逻辑载体。而对于一场游戏或世界的规则，UE提供的AGameMode就只是一个虚拟的逻辑载体，可以通过PersistentLevel上的AWorldSettings上的配置创建出我们具体的AGameMode子类。AGameMode同时也是负责在具体的Level中创建出其他的Pawn和PlayerController的负责人，在Level的切换的时候AGameMode也负责协调Actor的迁移。配套的数据对象是AGameState。(GamePlay架构（七）GameMode和GameState)
World构建好了，该派玩家进来了。但游戏的方式多样，玩家的接入方式也多样。UE为了支持各种不同的玩家模式，抽象出了UPlayer实体来实际上控制游戏中的玩家PlayerController的生成数量和方式。(GamePlay架构（八）Player)
所有的表示和逻辑汇集到一起，形成了全局唯一的UGameInstance对象，代表着整个游戏的开始和结束。同时为了方便开发者进行玩家存档，提供了USaveGame进行全局的数据配套。(GamePlay架构（九）GameInstance)
UE为我们提供了这些GamePlay的对象，说多其实也不多，而且其实也是这么优雅有机的结合在一起。但是仍然会把一些朋友给迷惑住了，常常就会问哪些逻辑该写在哪里，哪些数据该放在哪里，这么多个对象，好像哪个都可以。比如Pawn，有些人就会说我就是直接在Pawn里写逻辑和数据，游戏也运行的好好的，也没什么不对。
如果你是一个已经对设计架构了然于心，也预见到了游戏未来发展变化，那么这么直接干也确实比较快速方便。但是这么做其实隐含了两个前提，一是这个Pawn的逻辑足够简单，把MVC的三者混合在一起依然不超过你的心智负担；二是已经断绝了逻辑和数据的分离，如果以后本地想复用一些逻辑创建另一个Pawn就会很麻烦，而且未来联机多玩家的状态复制也不支持。但说回来，人类的一个最常见的问题就是自大，对自己能力的过度自信，对未来变化的虚假掌控感。程序员在自己的编程世界里，呼风唤雨操作内存设备惯了，这种强大的掌控感非常容易地就外延到其他方面去了。你现在写的代码，过几个月后再回头看，是不是经常觉得非常糟糕？那奇怪了，当初写的时候怎么就感觉信心满满呢？所以踩坑多了的人就会自然的保守一些。另一方面，作为团队里的技术高手或老人，我个人觉得也有支持同行和提携后辈的责任，对自己而言只是多花一点点力气，却为别人树立一个清晰的程序结构典范，也传播了设计思想。程序员何苦为难程序员。
但还有一些人喜欢那么硬怼着干的原因要嘛是对未来的可预见性不足（经验不足），要嘛是对程序设计的基本原则不够了解（程序能力不够），比如最简单的“单一职责”。在新手期，面对着UE的程序世界，虽然在已经懂的人眼里就那么几个对象，但是在新手眼里，往往就感觉复杂无比，面对未知，我们本能的反应是逃避，往往就倾向于哪些看起来这么用能工作，就像玩游戏一样，形成了你的“专属套路”。跟穷人忙于工作而没力气提高自己是一个道理。相信我，所有的高手都是从小白过来的，我敢保证，他出生的时候脑袋也肯定是一片空白！区别是有些人后来不怕麻烦的勤能补拙，他努力的去理解这种设计模式的优劣，不局限于自己已经掌握的一片舒适区内，努力去设想未来的各种变化和应对之法，最终形成自己的独立思考。高手只是比新手懂得更多想得更多一些而已。
闲话说完。在分析UE这么一个GamePlay系统的时候，就像UML有各种图一样，我们也应该从各个切面去分析它的构成。这里有两大基本原则：单一职责和变化隔离，但也可以说只有一个。所有的程序设计模式都只是在抽象变化，把变化都抽离开了，剩下的不就是单一职责了嘛。所以UE里对MVC的实践其实也只是在不断抽离出各个对象的变化部分，把Pawn的逻辑抽出来是Controller，把数据抽出来是PlayerState。把World的Level静态逻辑抽出来是关卡蓝图，把动态的游戏玩法抽离出来是GameMode，把游戏数据抽离出来是GameState。具体的每个层次的数据和逻辑的关系前文已经一一详细说过了，此处就不再赘述了。但也再次着重探讨一些分析方法：
从竖直的角度来看，左侧是表示，中间是逻辑，右侧是数据。
当我们谈到表示的时候，脑袋里想的应该是一个单纯的展示对象，就像一个基本的网络物体，它可以带一些基本的动画，再多一些功能，也顶多只能像一个木偶，有着一些非常机械原始的行为。我们让他前进，他可以知道左腿右腿交替着迈，但他是无知觉的。所以左侧的那一串对象，你应该尽量得让他们保持简单。
实现中间的逻辑的时候，你应该专注于逻辑本身，尽量的忘记两旁的表示和数据。去思考哪些逻辑是表示固有的还是比较智能判断的。哪些Controller或Mode我们应该尽量的让它们通用，哪些就让它们特定的负责某一块，有些也不能强求，自己把握好度。
右侧的数据，同样的保持简单。我们把它们分离出来的目的就是为了独立变化和在网络间同步，注意一下别走回头路了就好。我们应该只在此放置纯数据。
从水平的切面上看，依次自底向上，记住一个原则，哪个层次的应该尽量只负责哪个层次的东西，不要对上层或下层的细节知道得太多，也尽量不要逾矩越权去指手画脚别的对象里的内务事。大家通力协作，注重隐私，保持安全距离，不就社会和谐了嘛。
最底层的Component，应该只是实现一些与游戏逻辑无关的功能。理解这个“无关”是关键。换个游戏，你这些Component依然可以用，就是所谓的游戏无关。
Actor层，通过Pawn、Controller和PlayerState的合作，根据需要旗下再派生出特定的Character，或PlayerController，AIController，但它们的合作模式，三大家族的长老们已经定下了，后辈们应该尽量遵守。这一层，关键的地方在于分清楚哪些是操作Actor的，别向下把Actor内部的功能给抽了出来，也别大包大揽把整个游戏的玩法也管了过来。脑袋保持清醒，这一层所做的事，就是为了让Actor们显得更加的智能。换句话说，这些智能的Actor组合，理论上是可以在随便哪个Level里用的。
Level和World层，分清楚静态的关卡蓝图和动态可组合GameMode。静态的意思是这个场景本身的运作机制，动态的指的是可以像切换比赛方式一样切换一场游戏的目的。在这一层上，你得有总览游戏大局的自觉了，咱们都是干大事的人，眼光就不要局限在那些一兵一卒那些小事了。制定好游戏规则，赋予这一场游戏以意义，是GameMode最重要的职责。注意两点，一是脑袋里有跟弦，一旦开始联机环境了，GameMode就升职到Server里去了，Client就没有了，所以千万要小心别在GameMode做些客户端的小事；二是GameState是表示一场游戏的数据的，而PlayerState是表示Controller的数据，对象和范围都不同，不能混了。
GameInstance层，一般来说Player不需要你做太多事情，UE已经帮你处理好了。虽说力量越大，责任就越大，但领导日理万机累坏了也不行是吧。所以GameInstance作为全局的唯一逻辑对象，我们如果能不打扰他就尽量少把事推给他，否则你很快就会看着GameInstance里堆着一山东西。GameInstance身在高层，应该只尽量做一些Level之间的协调工作。而SaveGame也应该尽量只保存游戏持久的数据。
自始至终，回顾一下每个类的本身的职责，该是他的就是他的，别人的不要抢。读者朋友们，如果到此觉得似乎懂了一些，但还是觉得不够深刻理解的话，也没关系，凡事不能一蹴而就，在开发过程中多想多琢磨自然而然就会慢慢领悟了。
整体类图
从类的继承层次上，咱们再加深一下理解。下图只列出了GamePlay架构里一些相关的重要的类：
(请点击看大图)
由此也可以看出来，UE基于UObject的机制出发，构建出了纷繁复杂的游戏世界，几乎所有的重要的类都直接或间接的继承于UObject，都能充分利用到UObject的反射等功能，大大加强了整体框架的灵活度和表达能力。比如GamePlay中最常用到根据某个Class配置在运行时创建出特定的对象的行为就是利用了反射功能；而网络里的属性同步也是利用了UObject的网络同步RPC调用；一个Level想保存成uasset文件，或者USaveGame想存档，也都是利用了UObject的序列化；而利用了UObject的CDO（Class Default Object），在保存时候也大大节省了内存；这么多Actor对象能在编辑器里方便的编辑，也得益于UObject的属性编辑器集成；对象互相引用的从属关系有了UObject的垃圾回收之后我们就不用担心会释放问题了。想象一下如果一开始没有设计出UObject，那么这个GamePlay框架肯定是另一番模样了。
总结
对于GamePlay我们从构建游戏世界开始，再到一层层的逻辑控制，本篇也从各个切面上总结归纳了整体架构。希望读者们好好领会UE的GamePlay架构思想，别贪快，整体上慢慢琢磨以上的架构图，细节上可以回顾过往的单篇来了解。
对于这一套UE提供的GamePlay框架，我们既然选择了用UE引擎，那么自然就应该想着怎么充分利用好它。框架就是你如果在它的规则下办事，那它就是事半功倍的助力器，你会常常发现UE怎么连这个也帮你做完了；而如果你在不了解的情况下想逆着它行事，就常常感受到怎么哪里都受到束缚。我们对于框架的理念应该就像是对待一辆汽车一般，我们关心的是怎么驾驶它到达想要的目的地，而不是折腾着怪它四个轮子不能按照你的心意朝不同方向乱转。对比隔壁的Cocos2dx、或Unity、或CryEngine，UE能够提供这么一个完善的GamePlay框架，对我们开发者而言，是一件幸福的事，不是吗？
结束语
完结撒花！GamePlay大章节也终于结束了，最开始是本着怎么尽早尽大的能帮助到读者朋友们，所以选择了GamePlay作为起始章节。相信GamePlay也是开发者们日常开发过程中接触最多，也是有可能混淆最多，概念不清，很容易用错的一块主题。在介绍GamePlay的时候，更多的重点是在于介绍各对象的职责和关联，所以更多是用类图来描述结构，反而对源码进行剖析的机会不多，但读者们可以自己去阅读验证。希望GamePlay架构的一系列十篇文章能切实地帮助到你们。
而下个专题，根据QQ群友们的投票反馈，决定了是UObject！有相当部分开发人员，可能不知道也不太关心UObject的内部机制。清楚了UObject，确实对于开发游戏并没有多少直接的提升，但《InsideUE4》系列教程的初衷就是为了深入到引擎内部提高开发者人员的内功。对于有志于想掌握好UE的开发者而言，分析一个游戏引擎，如果只是一直停留在高层的交互，而对于最底层的对象系统不了解的话，那就像云端行走一般，自身感觉飘飘然，但是总免不了内心里有些不安，学习和使用的脚步也会显得虚浮。因此在下个专题，我们将插入UObject的最最深处，把UObject扒得一毛不挂，慢慢领会她的美妙！我们终于有机会得偿心愿，细细把玩一句句源码，了解关于UObject的RTTI、反射、GC、序列化等等的内容。如果你也曾经好奇NewObject里发生了些什么、困惑CreateDefaultSubObject为何只能在构造函数里调用、不解GC是如何把对象给释放掉了、uasset文件里是些什么……
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》GamePlay架构（十一）Subsystems</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/158717151
引言
非常惭愧，自从我更新完GamePlay架构十篇之后，我就断更了许久。如今说再多缘由也是借口，借着假期，在家继续重操旧业，继续写写技术文章。
UE在4.22版本的时候，开始引入Subsystems，然后在4.24完善。写本篇文章的一个原因是Subsystems其实可以算是GamePlay框架基础上的一个增强功能，属于GamePlay架构的范围，因此我要补完。另一个原因是我观察到大家对Subsystems好像还很陌生，讨论和用的人都很少。这着实有点可惜，Subsystems其实是一个非常便利的功能，如果大家在编写代码的时候，能够有意识的利用好Subsystems这个特性的话，会使自己的程序架构更加的清晰和便利。
希望本文能帮助到你达成这一点。为了好好阐述好这个问题，本文的篇幅会比较长，大家可以慢慢挑自己感兴趣的部分，不用着急。
为避免接下来混淆，本文先定义一下接下来使用的术语：
Subsystems：指的是这整套“子系统”框架，包含了定义的类以及运作机制。
SubsystemType/SubsystemClass：指向的是Subsystem的类型，比如TSubclassOf<USubsystem>。
Subsystem对象：指的是真正创建生成实例化出来的Subsystem对象。
UMyXXXSubsystem: 用户定义的类，我会以My为前缀来区分。
5类Outer对象：Subsystem对象依存属于的5类Outer对象。
UEngine* GEngine;
UEditorEngine* GEditor;
UGameInstance* GameInstance;
UWorld* World;
ULocalPlayer* LocalPlayer;
生命周期5类：引擎已经预定义的5个让你可以由此派生的父类。
UEngineSubsystem
UEditorSubsystem
UGameInstanceSubsystem
UWorldSubsystem
ULocalPlayerSubsystem
Subsystems是什么？
一句话：Subsystems是一套可以定义自动实例化和释放的类的框架。这个框架允许你从5类里选择一个来定义子类(只能在C++定义)：
之后就可以享受以下这些福利了：
自动实例化
这些的UMyXXXSubsystem类，会在合适的时机被创建出对象，然后在合适的时机释放，这个过程是自动化的。不需要自己手写创建代码。也不需要自己显式的定义变量，Subsystems已经定义好方便友好的访问接口了。
2. 托管生命周期
根据你选择的父类不同，引擎会为创建出来的Subsystem实现出不同的生命周期。因此官方文档里会称这5个父类为5个不同的生命周期。根据你选择的生命周期不同，Initialize()和Deinitialize()会自动的在合适的时机被调用。一个Subystem类型也有可能根据需要被自动的被创建出多个实例。这些里面的繁琐逻辑自己都不用操心。
Subsystems的基本使用
在谈到为什么需要Subsystems，以及如何用好Subsystems之前，我们先了解一些Subsystems的基础使用知识。先懂怎么用，然后再谈为什么，以及怎么用好。 目前Subsystems的使用只能在C++端，用起来倒也还简单。
第一步，定义C++子类：
//声明定义：
UCLASS() 
class HELLO_API UMyEditorSubsystem : public UEditorSubsystem
UCLASS() 
class HELLO_API UMyEngineSubsystem : public UEngineSubsystem
UCLASS() 
class HELLO_API UMyGameInstanceSubsystem : public UGameInstanceSubsystem
UCLASS() 
class HELLO_API UMyWorldSubsystem : public UWorldSubsystem
UCLASS() 
class HELLO_API UMyLocalPlayerSubsystem : public ULocalPlayerSubsystem
//注：使用UEditorSubsystem需要在Build.cs里加上EditorSubsystem模块的引用，因为这是编辑器模块
if (Target.bBuildEditor)
{
    PublicDependencyModuleNames.AddRange(new string[] { "EditorSubsystem" });
}
第二步，像普通的UObject类一样，可以在里面定义属性和函数。
以一个非常简单的分数系统为例：
UCLASS()
class HELLO_API UMyScoreSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public://重载的函数，可以做一些初始化和释放操作
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override { return true; }
    virtual void Initialize(FSubsystemCollectionBase& Collection)override;
    virtual void Deinitialize()override;
public:
    UFUNCTION(BlueprintCallable)
    void AddScore(float delta);
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Score;
};
第三步，就可以在C++和蓝图里访问这些类和调用函数了。
C++里的访问：
//UMyEngineSubsystem获取
UMyEngineSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UMyEngineSubsystem>();
//UMyEditorSubsystem的获取
UMyEditorSubsystem* MySubsystem = GEditor->GetEditorSubsystem<UMyEditorSubsystem>();
//UMyGameInstanceSubsystem的获取
UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(...);
UMyGameInstanceSubsystem* MySubsystem = GameInstance->GetSubsystem<UMyGameInstanceSubsystem>();
//UMyWorldSubsystem的获取
UWorld* World=MyActor->GetWorld();  //world用各种方式也都可以
UMyWorldSubsystem* MySubsystem=World->GetSubsystem<UMyWorldSubsystem>();
//UMyLocalPlayerSubsystem的获取
ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->Player)
UMyLocalPlayerSubsystem * MySubsystem = LocalPlayer->GetSubsystem<UMyLocalPlayerSubsystem>();
当然引擎源码里也已经定义好了一些方便的蓝图库函数，USubsystemBlueprintLibrary里的函数虽然不暴露在蓝图端，但也是可以在C++端方便调用的。
//我省略了一些宏标记和注释，因为函数名字是不言自明的。
UCLASS()
class ENGINE_API USubsystemBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    static UEngineSubsystem* GetEngineSubsystem(TSubclassOf<UEngineSubsystem> Class);
    static UGameInstanceSubsystem* GetGameInstanceSubsystem(UObject* ContextObject, TSubclassOf<UGameInstanceSubsystem> Class);
    static ULocalPlayerSubsystem* GetLocalPlayerSubsystem(UObject* ContextObject, TSubclassOf<ULocalPlayerSubsystem> Class);
    static UWorldSubsystem* GetWorldSubsystem(UObject* ContextObject, TSubclassOf<UWorldSubsystem> Class);
    static ULocalPlayerSubsystem* GetLocalPlayerSubSystemFromPlayerController(APlayerController* PlayerController, TSubclassOf<ULocalPlayerSubsystem> Class);
};
蓝图内的访问：
用起来的感觉有点像“全局变量”，也有点像是静态蓝图函数（如GetGameInstance），可以方便的在蓝图的各个地方调用。但Subsystems真正的威力其实远不止这点手头上的便利，而在于接下来要谈的引擎帮你自动处理的部分。
如何理解Subsystems的生命周期？
可以说Subsystems机制的核心之处就是在于引擎帮你托管了对象的生命周期，而理解这些对象生命周期的不同，也是理解Subsystems的关键之处。
简短的说，Subsystem对象的生命周期取决于其依存的Outer对象的生命周期，随着Outer对象的创建而创建，随着Outer对象的销毁而销毁。而选择依存哪种Outer对象，就是选择哪种Subsystem生命周期，靠的就是选择继承于哪个Subsystem基类。
从数据角度分析，先一图以概之：
从源码里分析，像5类这种对象，比如GEngine，里面都添加了一个FSubsystemCollection<TBaseType> SubsystemCollection的对象，而其基类FSubsystemCollectionBase里面存储了Subsystem对象的引用。
class ENGINE_API UEngine
{
private:
    FSubsystemCollection<UEngineSubsystem> EngineSubsystemCollection;
};
//而FSubsystemCollection又继承于FSubsystemCollectionBase
template<typename TBaseType>
class FSubsystemCollection : public FSubsystemCollectionBase
{
};
//而FSubsystemCollectionBase里面用Map存储了对象引用
class ENGINE_API FSubsystemCollectionBase : public FGCObject
{
private:
    TMap<TSubclassOf<USubsystem>, USubsystem*> SubsystemMap;//用Map来存储对象
    TSubclassOf<USubsystem> BaseType;//Subsystem对象类型
    UObject* Outer;//外部的对象
}
可以看到，这5类Outer对象(UEngine,UEditorEngine,UGameInstance,UWorld,ULocalPlayer)里面都新增了一个FSubsystemCollection<TBaseType> SubsystemCollection的成员变量，用来存储其关联的Subsystem对象。 拿最常用的UGameInstance来举个例子，假如你定义了两个自己UScoreSubsystem(计分系统)和UTaskSubsystem(任务系统)，全都继承于UGameInstanceSubsystem之后，你的对象布局应该是这个样子：
可以看到GameInstance里的FSubsystemCollection对象存储了生成的UScoreSubsystem和UTaskSubsystem对象的引用，而这二者其Outer都是指向GameInstance对象。数据内存结构还是比较简单的，但也有一些要点：
我特意标明了FSubsystemCollectionBase继承于FGCObject，意在说明虽然FSubsystemCollection是个结构，其在UGameInstance里，但其内部的对象引用也是受到GC管理的。FGCObject的内容不是此文重点，因此不再赘述，只要明白它是个让F结构也可以让GC管理内部U对象引用的机制。
FSubsystemCollectionBase里的UObject* Outer，指向外部的UGameInstance对象。这个Outer可以用来在USubsystem::ShouldCreateSubsystem()或FSubsystemCollectionBase::Initialize(FSubsystemCollectionBase& Collection)的时候，从而可以在某个USubsystem对象创建之前获取到外部Outer，从而继续获取到其他的兄弟姐妹Subsystem对象，从而做一些逻辑判断。当然创建完之后，因为USubsystem对象的Outer其实也为UGameInstance，所以直接GetOuter()也就可以了。
从TMap的Key为TSubclassOf可以看出，一种特定类型的USubsystem子类只能创建出一个USubsystem对象。所以UScoreSubsystem和UTaskSubsystem可以同时存在，但一种也只能有一个，类似单件模式。
如果查看UGameInstanceSubsystem的源码（其他同理）：
UCLASS(Abstract, Within = GameInstance)
class ENGINE_API UGameInstanceSubsystem : public USubsystem
{
}
解释一下两个重要的宏标记：
Abstract标记指明UGameInstanceSubsystem是抽象基类，是不能被直接创建出来的。
Within = GameInstance，Within这个标记的意思是其对象的Outer必须是某个类型，另外Within的标记是会被继承到子类的。所以综合的意思就是继承于UGameInstanceSubsystem的之类Subsystem对象的Outer必须是GameInstance，保证了其对象的依存合法性。所以其实你也是不能自己随便NewObject()出来的，避免了自己误操作。
总结一下，在Subsystems之前我们其实也可以自己用C++来实现一个类似的“单例模式”，也可以达成类似的效果，其实大家也往往就这么干。但Subsystems给我们带来的远不止这些，因此接下来我们就来谈谈Subsystems相比我们自己手写的优点有哪些。
为什么要引进Subsystems？
首先，我非常赞同官方引入Subsystems这套机制，虽然其实工作量不多，实际源码行数也很少，但是这有效的弥补了程序实践上的一个易混乱缺陷漏洞。为了让你们能真正学习Subsystems并开始用起来，下面我就来好好安利一番：
一， 不用自己手写，懒人福音，而且更正确
减少Bug最好的方式就是少写代码。诚然Subsystems这套并不是多高深的技术，实现的原理也蛮简单，差不多的程序员都能自己实现一套。但是引擎是否内建提供了该通用机制依然很重要。举例来说，你如果也想实现个类似的单件模式，你可能需要这么写：
UCLASS()
class HELLO_API UMyScoreManager : public UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure,DisplayName="MyScoreManager")
    static UMyScoreManager* Instance()
    {
        static UMyScoreManager* instance=nullptr;
        if (instance==nullptr)
        {
            instance=NewObject<UMyScoreManager>();
            instance->AddToRoot();
        }
        return instance;
        //return GetMutableDefault<UMyScoreManager>();
    }
public:
    UFUNCTION(BlueprintCallable)
        void AddScore(float delta);
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Score;
};
这段代码有什么问题？
学习负担重，新人看不明白。首先第一个问题就是，但凡是想要用单件模式的人，都得先自己学会这么一编写套路，而且得抄对。
AddRoot()往往很多人会忘掉，导致对象被释放，自己却拿它来调用函数是，导致崩溃。
这里用GetMutableDefault可不可以？直接采用CDO对象当做单件对象可不可以，区别是什么？又有多少人能分得清呢。实际上二者确实差别不大，只不过是一个是否保留默认值的问题，常常确实可以通用。但GetMutableDefault其实我发现知道和用的人不多。Subsystem是没有直接用CDO的，因为其可能会被反复的创建销毁，所以需要CDO来恢复默认值。
这个单件的存续期其实在Editor模式下也会存在，所以在Play和Stop后其值依然会存在，表现为脏值。这也是一个常见的单件陷阱问题。
因此是否考虑重复创建和销毁的时机？像上述这种写法，单件创建出来后就一直存在。这个时候想处理这个创建销毁的问题又有几个选择：一是再加上Initialize和Deinitialize()函数来手动调用；二是换种写法，不用函数静态变量，而用类静态变量再加上Destroy方法手动调用；三是把static UMyScoreManager* 放到UGameInstance的子类里当做类静态变量，然后在Init和Shutdown的重载函数里进行创建和释放。不同的写法也都有其优缺点，但最大的缺点是：你要为每个单件类都写一遍，而且不能写错。
维护成本高。手动模式要求你为每个新单件类都要记得加上其创建和释放的代码操作。根据第5点，当新定一个MyNewManager，你就得记得先定义静态变量，然后Init里加上创建代码，在ShutDown里加上销毁代码。而引擎的这套机制可以利用反射机制，方便的创建和销毁对象。可维护性比手写的要强多了。
当然也有人会说用Engine内建提供好的GameInstanceClass，但是缺点是只支持一个类型，而且生命周期是整个引擎，不是一场游戏。
总结一下，你或许可以自己手写出一套足够健壮灵活的机制，但想做好做正确其实并不简单。而且因为你不能侵入引擎源码(受引擎分发升级等限制)，所以你自己实现的方式总会受限。最好的方式是引擎实现好了之后，你理解并用好它。
二、 更模块化
很多人，包括我自己，在实现一些全局的游戏系统的时候，总是从UGameInstance继承下来，然后在里面码一堆代码：
UCLASS()
class HELLO_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()
public://UI系统
    UFUNCTION(BlueprintCallable)
        void PushUI(TSubclassOf<UUserWidget> widgetClass);
public://任务系统
    UFUNCTION(BlueprintCallable)
        void CompleteTask(FString taskName);
public://计分系统
    UFUNCTION(BlueprintCallable)
        void AddScore(float delta);
};
示例代码我就意思一下，但请读者们自己回想一下，自己是否也曾经这么干过呢？有的人请在公屏上打上“确实”。但这么写其实也有三个大问题：
1. 一个类里挤占着太多逻辑。可维护性差，不利于分工协作。一个游戏常常有很多个逻辑模块，如任务系统，计分系统，经济系统、对话系统、爆率系统等等，这些都实现在UMyGameInstance里，会导致类越来越庞大，逐渐超过自己的心智负担上限。
2. 不利于模块复用。假如你下载了个游戏模板，里面有个对话系统，你觉得很好想挪用过来。但人家也是写在UDialogueGameInstance里的，这个时候你只能手动把其代码拷贝到你的UMyGameInstance里。或者说，你的另一款游戏也想复用上款游戏的一些逻辑模块，于是你也只能手动拷贝一遍。想想之前是不是经常这么干？
3. 手动划分Manager类也不够机智。当然一些机智的人已经想到了可以把这些业务逻辑模块，划分为不同的Manager类。但问题依旧，你依然需要自己手动去管理这些Manager类的生命周期。
因此，现在有了Subsystems之后，你只需要把这些都写成:
UCLASS()
class HELLO_API UMyUISubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public://UI系统
    UFUNCTION(BlueprintCallable)
        void PushUI(TSubclassOf<UUserWidget> widgetClass);
};
UCLASS()
class HELLO_API UMyTaskSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public://任务系统
    UFUNCTION(BlueprintCallable)
        void CompleteTask(FString taskName);
};
UCLASS()
class HELLO_API UMyScoreSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()
public://计分系统
    UFUNCTION(BlueprintCallable)
        void AddScore(float delta);
};
这么写有几点好处：
1. 代码看起来优雅多了。 相应的逻辑组织在对应的类里，易于理解，易于维护，也易于分工协作（可以一个人写一个模块）。
2. 自己不用手写Subsystem对象的创建释放逻辑了。解放了双手，也免于出错。
3. 容易迁移复用。 想复用一个之前已经写好的比如任务系统，只需要把那个类直接拷贝过来就行了。不需要进行代码的手动拷贝粘贴工作，避免出错。
4. 更好的封装粒度，避免系统之间的数据访问污染。按之前的方式，在UMyGameInstance里面，你在实现任务系统的时候，比如StartTask，你可能还需要用到计分系统的Score变量，这个时候你往往可能就直接访问成员变量了。因此，多个逻辑模块之间的数据其实是互相污染的，这是一种耦合紧密，封装不够良好的坏味道。如今拆成多个Subsystem类之后，就可以在特定的系统里，如UMyScoreSubsystem::GetScore()里面做更好的封装和验证。
三，理解的一致性
当程序员之间进行沟通程序架构的时候，设计模式是一些约定俗成的招数。同样，在UE4里进行逻辑复用的时候，也需要更加的清晰的统一认识。 让我们设想这么一个场景，你从虚幻商城里下载了一个游戏模板，比如一套战斗系统模板。你在去理解怎么把它复用到你的游戏项目里的时候，你会按照什么思路去理解它？你首先要看的是什么文件？如果作者没有写清楚说明文档的话，我发现往往也都是先从GamePlay那几个类先看看里面有什么，然后去Demo关卡里看看用到了哪些Actor类，接着运行起来看看，然后各个目录翻翻。这里面的问题在于，不同的开发者在编程的时候都有自己的方式，互相之前缺少共识。
在有了Subsystem之后，如果大家都学习和利用好Subsystem，把自己的功能模块用Subsystem来实现。这样大家都看和理解别人的模块的时候，首先想到的就是去看看对方里面有啥Subsystem类，然后专注的看它就行了。要复用的话也是直接拷贝过来就行。
总结一下，UE里如果提到复用的理解一致性：
通用功能的复用：从各个ActorComponent里查看，这一层代表的往往是跟“游戏逻辑”无关的可复用功能。
业务逻辑的复用：从Subsystem来查找，其代表就是游戏逻辑相关的可复用部分。
至于GamePlay里的各个类，那其实是大家对于业务框架流程的一致性理解，往往并不能直接复用拷贝过来使用。
四，避免重载引擎类
特别是在实现插件模块的时候，其实你并不需要继承于GameInstance或之类的，但是往往你又需要一个“全局的管理类”，于是不得不为之。继承于GameInstance的坏处上文已经说过了，有些人有鉴于此，往往就另建了一个“XXXManagerActor”蓝图类，然后要求用户拖放这个Actor到场景内来使它工作。这其实也只是一种“绕开”的办法而已，从结构上来说不够优雅，从用户使用体验上来说也不够直接。
五，生命周期控制粒度更细
如果说想让自己的Manager类依存UGameInstance的生命周期还好实现，因为UGameInstance里已经提供了Init和Shutdown的重载，但如果想实现依存Engine，Editor，World，LocalPlayer的不同生命周期，就难很多了。你得去注册这些对象的创建销毁事件，如果没有提供的话，就只能去改源码了，必须修改引擎来在合适的时机插入初始化删除代码。因此相比，Subsystem的实现由引擎开发人员已经实现好了，我们不用自己处理这点脏活，省心。
六，更友好的访问接口
虽然说UE已经提供了Subsystem的Python的访问，但我在UE里用Python不多，因此不是特别在意。光从蓝图的访问接口来说，Subsystem的样子更像个全局变量，而用静态函数模拟的就还只是个函数。这点差别对强迫症来说 算是一点小福利吧。
但其实还有一点比较隐晦的是，Subsystem有个“上下文”的概念。相比MyScoreManager这种全局函数在哪里都可以访问来获得值，Subsystem的访问接口里会判断当前所属于的对象ContextObject是否能够获得相应的Subsystem对象。比如UWorldSubsystem，就必须在可以根据当前蓝图对象得到World的时候才能访问值，否则是null。比如你如果在一个UserWidget里，或者在一个UObject子类对象里，虽然可以写下MyWorldSubsystem节点，但是返回的会是null。ULocalPlayersystem也是同理。关于“上下文”对象的理解，我们在后面再详述。
能否再具体解释一下Subsystem对象的创建销毁流程？
如果你被我成功安利到了，想要开始使用Subsystems，那下一个问题就是如何用好Subsystems呢？我一直有一个观点，纯熟的应用是要建立在深刻的理解之上的。因此且让我们再花一些时间阐述一下Subsystem对象的具体创建的流程。做到知其然且知其所以然，心中不慌。 从源码上进行分析，虽然真正核心流程并不长，但具体叙述起来也是篇幅太长，因此这里我叙述一些要点：
一，深刻理解5类Outer对象的生命周期。
理解这些引擎重要的内建类的生命周期机制是理解的基础。因此也请读者事先知道引擎编辑器模式、Runtime模式和PIE(Play In Editor)模式这三个的区别。编辑器模式就是你启动编辑器，Runtime模式是指你游戏打包后的运行状态，PIE模式指的是在编辑器里点击Play后的运行状态。
UEngine* GEngine： 代表引擎，数量1。 Editor或Runtime模式都是全局唯一，从进程启动开始创建，进程退出时销毁。
UEditorEngine* GEditor： 代表编辑器，数量1。 顾名思义，只在编辑器下存在且全局唯一，从编辑器启动开始创建，到编辑器退出时销毁。
UGameInstance* GameInstance：代表一场游戏，数量1。 从游戏的启动开始创建，游戏退出时销毁。这里的一场游戏指的是Runtime或PIE模式的运行的都算，一场游戏里可能会创建多个World切换。
UWorld* World：代表一个世界，数量可能>1。 对此不明白的建议读者去看我之前的GamePlay架构文章。简单来说，World和GameMode是关联的，可以包含多个Level，默认情况下OpenLevel常常会切换World。因此其生命周期，其实跟GameMode是一起的。但也请读者建议，编辑器模式下视口里的场景其实也是个World，因此EWorldType其实有多个类型：Game，Editor，PIE，EditorPreview，GamePreview等。读者需知道，编辑器下的视口场景也是个World!
ULocalPlayer* LocalPlayer：代表本地玩家，数量可能>1。 UE支持本地分屏多玩家类型的游戏，但往往最常见的是就只有一个。LocalPlayer虽然往往跟PlayerController一起访问，但是其生命周期其实是跟UGameInstance一起的(默认一开始的时候就创建好一定数量的本地玩家)，或者更准确的说是跟LocalPlayer的具体数量挂钩（当然你也可以运行时动态调用AddLocalPlayer)。
因此你想理解好那5个Subsystem类的生命周期，就得理解这5个Host对象的生命周期。道理很简单，Subsystem对象的创建和销毁都是在Host对象的创建和销毁的时候相应执行的。
二，理解Subsystem对象反射创建销毁流程
这5类Outer对象自己创建的时候，都会调用一下FSubsystemCollectionBase::Initialize(UObject* NewOuter)，把自己this作为Outer传进去。因此其Subsystem对象的创建流程其实就在这个函数里面：
void FSubsystemCollectionBase::Initialize(UObject* NewOuter)
{
    if (BaseType->IsChildOf(UDynamicSubsystem::StaticClass()))//如果是UDynamicSubsystem的子类
    {
        for (const TPair<FName, TArray<TSubclassOf<UDynamicSubsystem>>>& SubsystemClasses : DynamicSystemModuleMap)
        {
            for (const TSubclassOf<UDynamicSubsystem>& SubsystemClass : SubsystemClasses.Value)
            {
                if (SubsystemClass->IsChildOf(BaseType))
                {
                    AddAndInitializeSubsystem(SubsystemClass);
                }
            }
        }
    }
    else
    {   //普通Subsystem对象的创建
        TArray<UClass*> SubsystemClasses;
        GetDerivedClasses(BaseType, SubsystemClasses, true);//反射获得所有子类
        for (UClass* SubsystemClass : SubsystemClasses)
        {
            AddAndInitializeSubsystem(SubsystemClass);//添加初始化Subsystem对象创建
        }
    }
}
UDynamicSubsystem的部分，我们稍后再讲。先来讲那些从USubsystem直接继承下来的子类对象创建，可以看到第一步是由反射获得BaseType（就是生命周期5类）的所有Subsystem子类。然后对其一一AddAndInitializeSubsystem：
bool FSubsystemCollectionBase::AddAndInitializeSubsystem(UClass* SubsystemClass)
{
    //...省略一些判断语句，咱们只看核心代码
    const USubsystem* CDO = SubsystemClass->GetDefaultObject<USubsystem>();
    if (CDO->ShouldCreateSubsystem(Outer))  //从CDO调用ShouldCreateSubsystem来判断是否要创建
    {
        USubsystem*& Subsystem = SubsystemMap.Add(SubsystemClass);//创建且添加到Map里
        Subsystem = NewObject<USubsystem>(Outer, SubsystemClass);//创建对象
        Subsystem->InternalOwningSubsystem = this;//保存父指针
        Subsystem->Initialize(*this);   //调用Initialize
        return true;
    }
}
这一段代码就核心说明了ShouldCreateSubsystem和Initialize的作用！因此自己可不要忘了重载哦~
那销毁呢？其实在玩家退出游戏或者按照生命周期，遇到Outer对象要被销毁的时候，其内部都加了一句：SubsystemCollection.Deinitialize();，依旧来欣赏一下代码：
void FSubsystemCollectionBase::Deinitialize()
{
    //...省略一些清除代码
    for (auto Iter = SubsystemMap.CreateIterator(); Iter; ++Iter)   //遍历Map
    {
        UClass* KeyClass = Iter.Key();
        USubsystem* Subsystem = Iter.Value();
        if (Subsystem->GetClass() == KeyClass)
        {
            Subsystem->Deinitialize();  //反初始化
            Subsystem->InternalOwningSubsystem = nullptr;
        }
    }
    SubsystemMap.Empty();
    Outer = nullptr;
}
逻辑也非常简单，遍历然后Deinitialize就是！
思考：那Subsystem是怎么被GC掉的呢？
我们在上述的代码里并不会看到手动的调用Destroy，因为USubsystem对象是个UObject对象，其依然是受GC管理的。Subsystem对象和Outer对象之前隔了一个FSubsystemCollection结构，为了让F结构依然可以追溯到对象引用，因此FSubsystemCollectionBase继承于FGCObject，所以我们也能找到如下代码：
void FSubsystemCollectionBase::AddReferencedObjects(FReferenceCollector& Collector)
{
    Collector.AddReferencedObjects(SubsystemMap);
}
当FSubsystemCollectionBase::Deinitialize()里进行SubsystemMap.Empty();后，USubsystem对象就没有被持有引用了，在下一帧的GC的时候，就会被判定为PendingKill的对象，从而得到Destroy。 这里的妙处是，直接利用了UObject对象之间引用所带来的生命周期绑定机制，来直接把USubsystem对象的生命周期和其Outer对象关联起来，而不用写重复的代码。秒啊！
三，理解UDynamicSubsystem
从一开始的类继承结构来看，读者们肯定已经发现UEngineSubsystem和UEditorSubsystem是继承于UDynamicSubsystem的，那为什么要如此设计呢？
顾名思义，其为动态Subsystem，动态二字，表明其会被动态的对待。这里的动态特指随着模块的加载释放来创建和销毁。要理解这点，首先要理解UE4的模块机制，简单来说，一个uproject项目或uplugin插件可以包含多个Module模块，每个Module可以有个Build.cs，每个模块可以被编译成一个Dll。模块之间可以互相引用。因此一个模块可能有多个依赖的其他模块，我们假如叫它：DependencyModules。引擎的机制是加载一个模块的时候会自动的加载DependencyModules，
首先假设我有一个插件叫做MyPlugin.uplugin，然后有个项目Hello.uproject，Hello项目想使用MyPlugin插件。MyPlugin里依次都定义了：UMyPluginEngineSubsystem，UMyPluginEditorSubsystem和UMyPluginGameInstanceSubsystem。
显式添加依赖的方式：事先配置好DependencyModules
当你在Hello项目插件设置上上开启MyPlugin，或者在Hello.uproject里写上"Plugins": [{"Name": "MyPlugin","Enabled": true}]，或者在Build.cs里加上PublicDependencyModuleNames.Add("MyOtherModule");，这些方式其实都是在显式的在一开始配置好项目的DependencyModules。这样当Hello模块启动的时候，引擎会自动的加载其依赖模块(MyPlugin)，从而你会发现UMyPluginEngineSubsystem和UMyPluginEditorSubsystem在编辑器一启动的时候就会创建并Initialize。 但是如下的代码分支，其实是只在GEditor初始化的时候才会调用到，因为这个时候其他插件里模块还没有加载。
void FSubsystemCollectionBase::Initialize(UObject* NewOuter)
{
    if (BaseType->IsChildOf(UDynamicSubsystem::StaticClass()))//如果是UDynamicSubsystem的子类
    {
        for (const TPair<FName, TArray<TSubclassOf<UDynamicSubsystem>>>& SubsystemClasses : DynamicSystemModuleMap)
        {
            for (const TSubclassOf<UDynamicSubsystem>& SubsystemClass : SubsystemClasses.Value)
            {
                if (SubsystemClass->IsChildOf(BaseType))
                {
                    AddAndInitializeSubsystem(SubsystemClass);
                }
            }
        }
    }
    else
    {   //普通Subsystem对象的创建
    }
}
这个时候加载的DynamicSystemModuleMap中最重要的就是UnrealEd模块。UnrealEd里面本身其实也已经定义了几个Subsystem: AssetEditorSubsystem，BrushEditingSubsystem，ImportSubsystem，LayersSubsystem和PanelExtensionSubsystem。
那MyPlugin里的Subsystem什么时候创建呢？
还是这块代码，其实在第一次初始化的时候，就用FSubsystemModuleWatcher
void FSubsystemCollectionBase::Initialize(UObject* NewOuter)
{
    if (SubsystemCollections.Num() == 0)//静态变量，用数目来判断是第一次创建
    {
        FSubsystemModuleWatcher::InitializeModuleWatcher();
    }
}
void FSubsystemModuleWatcher::InitializeModuleWatcher()
{
    // 获得所有UDynamicSubsystem的子类
    TArray<UClass*> SubsystemClasses;
    GetDerivedClasses(UDynamicSubsystem::StaticClass(), SubsystemClasses, true);
    for (UClass* SubsystemClass : SubsystemClasses) //遍历
    {
        if (!SubsystemClass->HasAllClassFlags(CLASS_Abstract))  //不为抽象类
        {
            UPackage* const ClassPackage = SubsystemClass->GetOuterUPackage();//获得所属于的包
            if (ClassPackage)
            {
                const FName ModuleName = FPackageName::GetShortFName(ClassPackage->GetFName());
                if (FModuleManager::Get().IsModuleLoaded(ModuleName))
                {
                    TArray<TSubclassOf<UDynamicSubsystem>>& ModuleSubsystemClasses = FSubsystemCollectionBase::DynamicSystemModuleMap.FindOrAdd(ModuleName);
                    ModuleSubsystemClasses.Add(SubsystemClass);//添加到DynamicSystemModuleMap
                }
            }
        }
    }
    //注册模块加载和释放事件
    ModulesChangedHandle = FModuleManager::Get().OnModulesChanged().AddStatic(&FSubsystemModuleWatcher::OnModulesChanged);
}
其中最重要的就是遍历当前进程里的UDynamicSubsystem子类们，并按照模块划分存储进DynamicSystemModuleMap，这样之后就知道当加载或释放某个模块的时候，应该去创建和销毁哪些Subsystem类型对象。
第二步是OnModulesChanged事件的注册，这样在后面加载的模块就能够得到通知：
void FSubsystemModuleWatcher::OnModulesChanged(FName ModuleThatChanged, EModuleChangeReason ReasonForChange)
{
    switch (ReasonForChange)
    {
    case EModuleChangeReason::ModuleLoaded:
        AddClassesForModule(ModuleThatChanged);//创建一个模块的DynamicSubsystem类们
        break;
    case EModuleChangeReason::ModuleUnloaded:
        RemoveClassesForModule(ModuleThatChanged);//销毁一个模块的DynamicSubsystem类们
        break;
    }
}
而这两个方法的实现其实也挺简单，就是查找该代码模块里定义的类看看是否是UDynamicSubsystem子类，然后为其创建对象实例。
void FSubsystemModuleWatcher::AddClassesForModule(const FName& InModuleName)
{
    // 找到这个模块所定义的代码包
    const UPackage* const ClassPackage = FindPackage(nullptr, *(FString("/Script/") + InModuleName.ToString()));
    TArray<TSubclassOf<UDynamicSubsystem>> SubsystemClasses;
    TArray<UObject*> PackageObjects;
    GetObjectsWithOuter(ClassPackage, PackageObjects, false);//得到该模块里定义的所有对象
    for (UObject* Object : PackageObjects)
    {
        UClass* const CurrentClass = Cast<UClass>(Object);//转成UClass试试
        if (CurrentClass && !CurrentClass->HasAllClassFlags(CLASS_Abstract) && CurrentClass->IsChildOf(UDynamicSubsystem::StaticClass()))//满足这些条件
        {
            SubsystemClasses.Add(CurrentClass);
            FSubsystemCollectionBase::AddAllInstances(CurrentClass);//为这个类创建对象实例
        }
    }
    if (SubsystemClasses.Num() > 0)//如果其内部有定义Subsystem类，有些可能没有
    {   //就需要登记一下
        FSubsystemCollectionBase::DynamicSystemModuleMap.Add(InModuleName, MoveTemp(SubsystemClasses));
    }
}
void FSubsystemModuleWatcher::RemoveClassesForModule(const FName& InModuleName)
{
    TArray<TSubclassOf<UDynamicSubsystem>>* SubsystemClasses = FSubsystemCollectionBase::DynamicSystemModuleMap.Find(InModuleName);
    if (SubsystemClasses)//如果能找到，说明其之前有登记过
    {
        for (TSubclassOf<UDynamicSubsystem>& SubsystemClass : *SubsystemClasses)
        {
            FSubsystemCollectionBase::RemoveAllInstances(SubsystemClass);//销毁这个类的所有对象
        }
        FSubsystemCollectionBase::DynamicSystemModuleMap.Remove(InModuleName);//移除登记
    }
}
创建和销毁类的对象实例代码：
void FSubsystemCollectionBase::AddAllInstances(UClass* SubsystemClass)
{
    for (FSubsystemCollectionBase* SubsystemCollection : SubsystemCollections)
    {
        if (SubsystemClass->IsChildOf(SubsystemCollection->BaseType))
        {   //这个函数之前解释过，用来创建对象
            SubsystemCollection->AddAndInitializeSubsystem(SubsystemClass);
        }
    }
}
void FSubsystemCollectionBase::RemoveAllInstances(UClass* SubsystemClass)
{
    ForEachObjectOfClass(SubsystemClass, [](UObject* SubsystemObj)//遍历属于该类型的对象们
    {
        USubsystem* Subsystem = CastChecked<USubsystem>(SubsystemObj);
        if (Subsystem->InternalOwningSubsystem)
        {   //也是大同小异的释放操作
            Subsystem->InternalOwningSubsystem->RemoveAndDeinitializeSubsystem(Subsystem);
        }
    });
}
这里的关键是SubsystemCollections是个静态变量，其引用了整个进程的所有定义的FSubsystemCollection的数量（2个在GEngine和GEditor里，其他多个可能动态新增在GameInstance，World，LocalPlayer里），这么写其实只是保险一点保证一个Subsystem类型的对象能够自动的多个SubsystemCollection里正确的创建多个。因为AddAllInstances也可能是个会被复用的方法。
说了一大堆，其实想说明MyPlugin模块在被加载的时候，会自动的触发OnModulesChanged事件，从而被自动的创建出内部的UMyPluginEngineSubsystem和UMyPluginEditorSubsystem。
后期动态加载模块或插件：
如果你不写上述的那些“静态”引用方式，想要在游戏或编辑器运行一段时间后然后动态的加载某个模块或插件。UE当然也支持，方法是：
对于模块，假如MyOtherModule是Hello项目里定义的另一个模块，你别在Build.cs添加Dependency引用，反而选择在后续的时机调用FModuleManager::Get().LoadModule(TEXT("MyOtherModule"));,你就会发现MyOtherModule的StartupModule开始调用了。如果这个模块里有定义DynamicSubsystem，其会被创建出来。 对于插件，假如Hello项目不开启MyPlugin插件，且在MyPlugin.uplugin里加上一句："ExplicitlyLoaded": true，这一句很重要，表明后面要显式的动态加载。这样你在之后的时机里调用：
FString path= FPaths::Combine(FPaths::ProjectPluginsDir(),TEXT("MyPlugin/MyPlugin.uplugin"));
IPluginManager::Get().AddToPluginsList(path);//添加插件路径让可以找到
IPluginManager::Get().MountExplicitlyLoadedPlugin(TEXT("MyPlugin"));//显式加载
这样这个插件就会被加载起来了。UMyPluginEngineSubsystem和UMyPluginEditorSubsystem也就会在这个时候被创建出来了。
总结一下，MyPlugin里的DynamicSubsystem们，虽然都是靠触发OnModulesChanged事件来创建和销毁自己。但是根据你项目配置模块引用的不同，时机也可以不同。所以DynamicSubsystem可以根据Module的加载释放来创建销毁，就是此动态的含义！
思考：动态加载MyPlugin里的UMyPluginGameInstanceSubsystem可以正常工作吗？
答案是可以。UMyPluginGameInstanceSubsystem虽然不是UDynamicSubsystem，但因为其需要创建的时机是游戏运行时。而这个时候，其实你如果去GetDerivedClasses(TSubclassOf&lt;UGameInstanceSubsystem&gt;)，你可以成功的获得到UMyPluginGameInstanceSubsystem。原因是MyPlugin这个模块dll加载的时候，其身带的反射代码里的全局静态变量会自动的在进程里注册进各种类型。这部分机制请参考我之前写的UObject文章，说来实在太话长了。所以MyPlugin已经被加载进来之后，你再点击Play，这个时候已经可以正确的使用MyPlugin里定义的非DynamicSubystem了。
思考：那为什么只有UEngineSubsystem和UEditorSubsystem才是UDynamicSubsystem呢？
还是得从生命周期来思考。生命周期5类中，只有UEngineSubsystem和UEditorSubsystem的生命周期是跟游戏的进程绑定在一起的。因此游戏进程启动的时候创建Subsystem叫做默认创建，游戏进程启动一段时间后想创建Subsystem叫做动态创建。而对于另外3个：UGameInstanceSubsystem，UWorldSubsystem和ULocalPlayerSubsystem，你观察一下，发现这3者都是跟一场游戏的生命周期绑定的！因此无论这3者定义上如何动态，其在编辑器启动后，都不会创建出来！而反正这3者会随着Play和Stop来反反复复的创建和销毁，其本身已经足够动态！因此就不需要专门处理了。结论还是其根据生命周期的不同而定的机制。
那前面说过了，UWorldSubsystem可能也会被WorldType::Editor的创建出来，其明显生命周期不是跟游戏一起的，编辑器如果已经完全启动完成了，那再动态加载的插件里定义的WorldSubsystem其实并不能扩展到Editor的World里。那这怎么理解呢？你可以把这当做是一种疏漏，但也可以当做是一种小故意。其含义就是：
Engine和Editor在启动前启动后，都可以通过静态或动态加载插件来扩展。
Game的部分，如果想扩展的话，就尽量在Game启动之前。
理论上你当然可以做一些骚操作，在游戏运行一半的时候，动态加载某个插件，然后再下个World里应用上你新增的WorldSubsystem，但实际情况是没这必要这么麻烦，因为已经有ShouldCreateSubsystem可以让你控制了。
四，理解Subsystem对象的个体生命周期
这一部分比较简单，就是你要理解好一个Subsystem对象：ShouldCreateSubsystem，Initialize和Deinitialize的调用时机才知道应该怎么重载。
要明白USubsystem本身是一个UObject，所以必然有CDO。自己用的时候要注意这一点。
五，总结一下其生命周期的不同时机
絮叨了一堆，希望读者们能清晰明白到生命周期其关键点就在于什么时候触发SystemCollection的Initiaze和DeInitialize，根据Outer对象自身运行机制生命周期的不同，由此搭配出不同的使用方式。在理解了这些不同Subsystem对象的不同之后，也许你也可以由此组织实现符合自己需求的加载创建策略。
如何用好Subsystems？
如果说到学习使用Subsystems的难点是什么，那肯定是如何用好它了！Subsystems本身是机制和使用方式并不复杂，但反而容易令人疑惑的是：该把自己项目的哪些业务逻辑封装成Subsystem？
一谈到编程实践，笔者本身并无金科玉律可传授，但可分享一些理解的点和使用的经验：
1. Subsystem是GamePlay级别的Component。要好好理解这句话的关键是，你要明白：
Component组件模式在程序架构中的作用套路，组合胜过继承而带来的灵活性。
清晰区分通用功能和业务逻辑。对于一个游戏来说，通用功能可能是人物按格子行走的能力，而业务逻辑是这个人物自身的战斗结算系统。通常来说，我倾向于把功能理解为可在不同游戏之间复用的功能，尽量与某款特定游戏无关，而与某类游戏相关，比如CharacterMovement。那自然的，剩下的与某款游戏强相关的部分，就是该游戏的业务逻辑部分了。对于功能能力，你应该用ActorComponent来实现。对于业务逻辑，你应该用Subsystem来实现。更清晰的对比是：
ActorComponent：依托Actor存在，封装基础的功能，着眼于某一功能的实现。
Subsystem：依托GamePlay对象存在，封装游戏的业务逻辑，专注于某部分游戏逻辑系统的调度安排。
二者是配合补充的关系。Component在底层专注于功能，Subsystem在上层统筹调度。虽然二者也可以有一些交集，可以替代着实现一些功能，但笔者并不建议如此。
2. USubsystem只是个普通的UObject。 所以，别害怕，USubsystem并没有什么特殊的，你之前可以在UObject里写的东西，可以实现的功能，依然可以在USubsystem里实现。所以你可以在里面写UPROPERTY和UFUNCTION，也可以定义事件，也可以被蓝图继承引用等等。只是心里永远有个意识，Subsystem的生命周期处于你的掌控之中。
3. Subsystem是有状态的。很多人可能还发现其跟蓝图函数库有点相像，但其最大的区别是蓝图函数库本身全都是静态函数，是无状态的。而Subsystem对象里面可以放属性，会真正的被构建出对象来，因此是有状态的。理论上你也是可以对此序列化的。
4. 尽量不要再写Manager类了。在以前你或许会自己定义一些Manager类，比如MapManager之类的，但现在都可以换成UMapWorldSubsystem了。理由是之前我们定义Manager类，无非是想要有一个全局的统一管理类来统筹做一些调度管理，现在这部分工作可以由Subsystem来做了。自己定义的Manager类的理由和空间越来越小了。
5. 引擎源码里已经定义了一些Subsystem，方便你抄袭学习。 UE引进了Subsystem并不是只对外提供给开发者使用的，其内部也自己先吃了Dogfood，把一些功能改造成Subsystem了。简单列一下列表。具体的功能不解释了，有兴趣自己去模板。
UEditorSubsystem
UnrealEd.AssetEditorSubsystem
UnrealEd.BrushEditingSubsystem
UnrealEd.ImportSubsystem
UnrealEd.LayersSubsystem
UnrealEd.PanelExtensionSubsystem
MovieRenderPipelineEditor.MoviePipelineQueueSubsystem
Blutility.EditorUtilitySubsystem
GeometryMode.UBrushEditingSubsystem
GeometryMode.UBrushEditingSubsystemImpl
VirtualProductionUtilities.UVPScoutingSubsystem
DataValidation.UEditorValidatorSubsystem
UWorldSubsystem
Landscape.LandscapeSubsystem
Engine.AutoDestroySubsystem
Engine.ObjectTraceWorldSubsystem
使用Subsystems的各种姿势
继续分享一些能想到的编写Subsystems的套路：
1. 可定义一个Subsystem抽象基类，然后派生多个子类。
用这种方式，依然可以在Subsystem的继承体系里往上抽象一些基本逻辑。官方直播里举的一个例子我觉得特别的形象，假如你要实现版本控制系统，且同时支持多个协议。这时你就可以定一个UCLASS(abstract) USourceControlSubsystem，然后往下派生出UGitSubsystem，USVNSubsystem，UPerforceSubsystem等等。原因是这些版本管理系统是拥有一些共同机制的。但请注意在基类上务必加上abstract的标记，以防止其也被实例化出来，那就很容易引起混淆了。 然后引擎还支持Subsystem的遍历：
const TArray<USourceControlSubsystem*>& systems= GEngine->GetEngineSubsystemArray<USourceControlSubsystem>();
这样就可以获得其多个git，svn等Subsystem实例了。
2. Subsystem也支持蓝图继承！
目前虽然不支持直接在蓝图里定义Subsystem，究其原因是生命周期5类定义的时候UCLASS里都没加上Blueprintable标记。但这一步其实很容易绕过，只要你自己定义的Subsystem上的UCLASS里加上标记：
UCLASS(abstract, Blueprintable, BlueprintType)
class HELLO_API UMyGameInstanceSubsystemBase : public UGameInstanceSubsystem
{
}
这样就可以在蓝图里继承然后使用了。依然加上abstract的用意是防止UMyGameInstanceSubsystemBase被实例化出来，造成混淆。Blueprintable和BlueprintType是支持蓝图继承和定义变量。
注意：抱歉，之前没有写清楚。有些人反馈遇见了蓝图Subsystem无法创建的问题。这个问题的原因是，如果你的蓝图类只是创建出来，但是在还没有被加载的时候，这个蓝图类的类型其实还没有注册到UE的类型系统里。因此就导致了SubsystemCollection在搜集和创建的时候，无法识别到该蓝图类，因此就无法创建出来。特别要提醒注意的是，这个问题很隐晦，很多人可能会发现有时可以创建有时失败，很有可能只是因为有时你在UE编辑器里双击打开了这个Subsystem蓝图类，而有时没有。在编辑器里双击打开蓝图类其实就会触发BP的加载，因此会发现PIE的时候就能正确创建了，而有时你没打开，就会创建失败。
理解了原因之后，解决的方式其实就很简单了，只要我们手动的触发一个Load，就可以了。
void FHelloModule::StartupModule()
{
	UObject* bpAsset = LoadObject<UObject>(NULL, TEXT("/Game/BP_MyGameInstanceSubsystem.BP_MyGameInstanceSubsystem_C"));
}
因此假如我们在模块的StartupModule里自己手动加载一下这个蓝图，其实就可以创建成功了。
3. 同一个BaseType下的多个Subsystem可以定义依赖顺序
虽然不太推荐在Subsystem之间构成强顺序依赖，但万一你真的需要的话，比如任务系统依赖于计分系统的计算结果来决定是否触发某个任务。这个时候，你可以这么写：
void UMyTaskSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    //初始化依赖项
    Collection.InitializeDependency(UMyScoreSubsystem::StaticClass());
    //获取
    UMyScoreSubsystem* ss=((FSubsystemCollection<UGameInstanceSubsystem>&)Collection).GetSubsystem<UMyScoreSubsystem>(UMyScoreSubsystem::StaticClass());
}
InitializeDependency内部会调用一下AddAndInitializeSubsystem来确保UMyScoreSubsystem已经被创建出来。这样你在后续就可以访问了。现在的访问方式依然有点别扭，希望后续可以改善。
4. Subsystem之间也可以通信
只要你获取到目标Subsystem的对象引用，你就可以使用它了。获取的方式有多种，一种是通过GEngine或GetGameInstance()等外部对象开始，然后GetSubsystem()来特定的获取。另一种是通过Subsystem在Initialize的时候，保存下其他Subsystem对象的指针来后续访问。
5. Subsystem也可以支持Tick
参考源码里的UAutoDestroySubsystem，咱们自己写一个支持Tick的Subsystem可以继承自FTickableGameObject：
UCLASS()
class HELLO_API UMyTickSubsystem : public UGameInstanceSubsystem,public FTickableGameObject
{
    GENERATED_BODY()
public:
    virtual void Tick(float DeltaTime) override;
    virtual bool IsTickable() const override { return !IsTemplate(); }//不是CDO才Tick
    virtual TStatId GetStatId() const override{RETURN_QUICK_DECLARE_CYCLE_STAT(UMyScoreSubsystem, STATGROUP_Tickables);}
};
其中IsTickable的实现要注意一下避免CDO，否则会造成Tick两次。
6. SubSystem里定义一些委托回调是一个常用的套路
还是以Score系统为例子，Subsystem往往自身都带有一些业务数据。而当这些数据改变的时候，往往也需要通知一些对象如UI来更新状态。这个时候可以定义一些委托回调：
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreChanged, float, NewScore);
UPROPERTY(BlueprintAssignable)
FScoreChanged OnScoreChanged;
UFUNCTION(BlueprintCallable)
void AddScore(float delta)
{
    Score += delta;
    OnScoreChanged.Broadcast(Score);
}
这样OnScoreChanged就可以在蓝图和其他地方BindEvent了。因为Subsystem本身具有全局访问的特性，因此往往很容易作为数据的集中式更新和事件的统一分发处。
再来一些零散的思考吧
还有一些小的思考，也想分享一下。作为一个程序架构设计的思考领悟交流。
思考：Subsystem支持网络复制吗？
不支持。我们知道UE里的网络复制是基于Actor的ActorChannel的，而USubsystem是普通的UObject对象，因此并不支持。在这一点上，你可能会有冲动去定义一个AManagerActor类来作为通信通道，这也许是一个好主意，但也得仔细的评估。因为常常很多时候，GameState和PlayerState等一些内建的GamePlay通信已经能够满足你的需求，我比较建议尽量把职责划分清楚。实在不行的话，那就用一个Actor来作为通信通道吧，反正再坏也坏不到哪里去，是吧。
思考：Subsystem为什么单挑这5个类？
多问几个为什么，不免会此疑问。我自己在思考这个问题的时候，会从引擎的关键流程有几个来思考。Engine支持了通用的引擎时机，Editor专门支持了编辑器。接下来的游戏启动和关闭，有GameInstance来负责了。然后游戏中的切换关卡有World相关联了。本地多玩家由LocalPlayer来支持。你会发现，这些对象都是关键的数据节点。
有人可能会问那怎么不弄UGameModeSubsystem？怎么不弄UPlayerControllerSubsystem？我尝试回答的答案是要控制拆分的粒度。理论上你甚至可以再定义UPawnSubsystem，把角色身上的业务逻辑也垂直拆分一下，但这未免就有点太多太细了，在很多时候往往都用不上。业务逻辑粒度太小了就更难拆分出来了。因此设计的一个原则是合适的考虑实际需求，不宜妄自追求灵活性。另一个方面，GameMode和PlayerController这些对象的生命周期往往是和World一起的，得到了World就可以顺藤摸瓜得到其他，因此在功能实现上倒也不损失多少。
当然，我同时的观点是引擎是一个持续迭代的产物，未来也许也会根据需要继续添加其他。未来需要构建更大的大世界后，架构必须演化以适应，自然会做更多的自调整。
思考：可否自己也参照着新建个USubsystem基类？
源码在手，为所欲为。在理解了这套机制的基础上，自己读读源码，其实不难参照着自己写一套。只是我自己确实没有想到实际的游戏需求。关键的倒不是如何继续添加一个，而是在吸收了这些架构知识营养后，读者们可以在自己的游戏结构里灵活应用上对象的反射和事件注册等知识。
思考：好奇蓝图里是怎么访问到Subsystem全局变量的？
关于这一点，引擎其实是做了专门的实现的。具体的源码原理可以参照，UK2Node_GetSubsystem定义了专门的蓝图节点，其内部实现会转发到USubsystemBlueprintLibrary的一些静态函数接口去。因此关于怎么理解Subsystem的上下文ContextObject这个问题，读者朋友们可以好好的读下USubsystemBlueprintLibrary的源码。其内容比较简单直接，我就不赘述贴出来了。
总结
不好意思，本文篇幅实在太长。原因是我想毕其功于一文，希望一次就能讲透。Subsystems其实可以算是GamePlay框架上发布的一个美味DLC，懂得使用它的人会让自己的程序架构愈发的清晰，而不懂的的人依然习惯把代码搅和在一团，摊手~
希望本文对大家有帮助，没脸皮求赞了，就酱，后会有期！
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（一）开篇</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/24319968
引言
在上个GamePlay专题，谈到UE创建游戏世界的时候(GamePlay架构（一）Actor和Component)，简单的介绍了一下UObject的功能：
藉着UObject提供的元数据、反射生成、GC垃圾回收、序列化、编辑器可见、Class Default Object等，UE可以构建一个Object运行的世界。（后续会有一个大长篇深挖UObject）
那么从本专题开始，我们将开始慢慢的填这个大坑。正所谓，千里之堤溃于蚁穴，万丈高塔始于垒土。在阅读分析游戏引擎源码的时候，又或者是想要扩展引擎功能，如果对于引擎底层对象创建的机制不太清楚，则常常会有点力不从心，因为功能模块的运行机制、数据流程、资源的加载释放时机，往往也都是依赖于对象的生命周期。而如果想要实现一个自己的游戏引擎，从一开始，也都得设计一个完善的对象管理机制，然后慢慢的在其上叠加功能，这个对象模型设计实现的如何，往往决定了一款引擎的基因。
愿景目标
本专题的内容主要是用于提升UE开发者，或者游戏引擎研究爱好者的内功，所以并不适合所有读者。在此需要明示本专题后续篇章（大概10~20篇）的目标愿景，以后不再赘述。
专注于UE的UObject及其周边的系统，在介绍构建对象系统的时候，虽然会涉及到引擎的启动流程，但是并不详细介绍（留待后续专题探讨）。本专题的重点是介绍UE4中的UObject系统，理论上，读完该篇章，你应该可以心里比较有数的在别的引擎里也实现出一套类似的系统。
本专题的内容对于你使用蓝图实现游戏逻辑几乎“无用”，对正常的表层C++开发也基本上提升不大。本专题只是让你安心一些而已。
我，先声明，本专题为了详细的讨论机制，在91.233%的情况下我会显得比较罗嗦，会引用罗列大量的引擎源码。如同开篇所说，毕竟是在探讨最最底层的的源码，再粗旷的泛泛而谈也没啥意思。
前置知识
本专题的学习探讨门槛比较高，在开始本专题之前，需要你先掌握以下知识：
优秀的C++语言能力。虽然不需要你“精通”C++，但是需要你熟练掌握C++11、模板、宏、对象内存模型和基本的各种规则机制。
本专题也涉及到对象反射，所以也需要你对编译原理、元数据、程序结构有一定的了解。如果对其他编程语言（java,c#）的反射熟悉的话，对理解本专题也是一大助力。
对多线程编程比较熟悉，知道并掌握各种线程同步机制。UE用多线程并行优化了很多任务，其中就包括GC，所以不可避免的需要你掌握相关的知识。
对C++内存分配管理也比较熟悉，知道一些STL基本的内存分配器，也知道各种内存分配管理的意义和技术，如引用技术，GC等。
为了更好的理解本专题内容，有必要的时候，我也会在每一个篇章开头简单介绍一下C++的一些知识要点。不过还是需要你自己去搜索查阅学习其他更系统的C++资料。
对象模型
先问一个问题，为什么需要有一个统一的基类：Object？
甚至，我们在编程语言中也常常见到这种模式，比如Java中的object、C#的object，甚至一些纯对象的脚本语言（Ruby里连数字123都是对象）。刚接触UE的人，看到UE里的Object，可能觉得这没什么，好像就自然而然应该有应该是这样，但是做过游戏引擎的人就知道，这里面蕴含了很多设计思想和权衡。
大部分的游戏引擎底层都是C++，而C++作为一个下接操作系统硬件底层，上接用户逻辑的编程语言，为了适应各种环境，不为你不需要的东西付代价，C++是并没有提供原生GC的。STL库的那些智能指针更多只是在C++的语言层面上再提供一些小辅助。在最开始设计游戏引擎的时候，你不光要考虑该引擎所面对的用户群体和针对的游戏重点，更要开始考虑你所能利用到的都有什么内存管理方式。简单说一下其他游戏引擎在这方便的情况：
Cocos系列，最早是cocos-iphone扎根于objective-c，所以用的引用技术，后来有cocos2dx了，为了照顾老用户的使用习惯，几乎是机械翻译了objective-c的内存管理机制，搞出了一个CCObject，里面只有Retain/Release，因为还是太过粗糙，也常常还是出现各种内存泄漏问题，用的时候也是得处处小心，漏掉一个就敢泄漏给你看，而且追查起来非常困难。没看人家objective-c自己后来都搞了一个ARC来减轻大家的工作了嘛。
Unity底层源码我没看过不得而知，不过上层脚本C#是基于Mono的已经实现完善的语言原生管理机制，对游戏对象的内存管理倒也确实是省心了非常多，缺点也是如果想要更精细的控制的时候就有点力不从心。
其他引擎，用的还是C++提供了的那些，顶多自己再定制一些管理辅助类。比如KlayGE就是利用了boost的智能指针，CryEngine用的也是智能指针，我的Medusa引擎也是比较简单的采用的C++智能指针的方案。对象的分配释放也往往需要用户手动管理控制。
在这就不得不提到Qt里的QObject，Qt虽然是处于跟UE不同的GUI框架领域，但是设计的思想却有些殊途同归，Qt里根据QObject基类构建出来的ObjectModel为UI的复杂构建和通信提供了许多了非常便利急需的功能。比如信号和槽的设计就常常让人们津津乐道，而且在编辑中也可以非常方便的查看对象的属性。Qt的流行，QObject应该功不可没。
UE的Object系统无疑是最强大的。实际上UE能实践出这么一套UObject是非常非常了不起的，更何况还有GC和HotReload的黑科技。在大型游戏引擎的领域尝试引入一整套UObject系统，对于整个业界也都是有非常大的启发。
那么引入一个Object的根基类设计到底有什么深远的影响，我们又付出了什么代价？
得到：
万物可追踪。有了一个统一基类Object，我们就可以根据一个object类型指针追踪到所有的派生对象。如果愿意，我们都可以把当前的所有对象都遍历出来。按照纯面向对象的思想，万物皆是对象，所以有一个基类Object会大大方便管理。如果再加上一些机制，我们甚至可以把系统中的所有对象的引用图给展示出来。
通用的属性和接口。得益于继承机制，我们可以在object里加上我们想应用于所有对象的属性和接口，包括但不限于：Equals、Clone、GetHashCode、ToString、GetName、GetMetaData等等。代码只要写一遍，所有的对象就都可以应用上了。
统一的内存分配释放。实际上Cocos2dx里的CCObject的目的就是如此，可惜就是实现得不够好而已。用引用计数方案的话，你可以在Object上添加Retain+1/Release-1的接口；用GC的方案，你也有了一个统一Object可以引用，所以这也是为何几乎所有支持GC的语言都会设计出来一个Object基类的原因了。
统一的序列化模型。如果想要让系统里的各种类型对象支持序列化，那么你要嘛针对各种类型分别写一套（如protobuf就是用程序生成了序列化代码），要嘛就得利用模板和宏各种标记识别（我自己Medusa引擎里实现的序列化模块Siren就是如此实现的），而如果有了一个Object基类，最差的我们就可以利用上继承机制把统一的序列化代码放到Object里面去。而如果再加上设计良好的反射机制，实现序列化就更加的方便了。
统计功能。比如说我们想统计看看整个程序跑下来，哪种对象分配了最多次，哪种对象分配的时间最长，哪种对象存活的时间最长。等等其他很便利的功能，在有了可追踪和统一接口的基础上，我们也能方便的实现出来。
调试的便利。比如对于一块泄漏了的内存数据，如果是多类型对象，你可能压根没法知道它是哪个对象。但是如果你知道它是Object基类下的一个子类对象，你可以把地址转换为一个Object指针，然后就可以一目了然的查看对象属性了。
为反射提供便利。如果没有一个统一Object，你就很难为各种对象实现GetType接口，否则你就得在每个子类里都定义实现一遍，用宏也只是稍微缓解治标不治本。
UI编辑的便利。和编辑器集成的时候，为了让UI的属性面板控件能编辑各种对象。不光需要反射功能的支持，还需要引用一个统一Object指针。否则想象一下如果用一个void* Object，你还得额外添加一个ObjectType枚举用来转换成正确类型的C++对象，而且只能支持特定类型的C++类型对象。
代价：
臃肿的Object。这算是继承的祖传老毛病了，我们越想为所有对象提供额外功能，我们就越会在Object里堆积大量的函数接口和成员属性。久而久之，这个Object身上就挂满了各种代码，可理解性就大大降低。Java和C#里的Object比较简单，看起来只有个位数的接口，那是因为有C++在JVM和CLR的背后默默的干着那些脏活累活，没显示出来给你看而已。而UE在原生的的C++基础上开始搭建这么一套系统，就是如今这么一个重量级的UObject了，大几十个接口，很少有人能全部掌握。
不必要的内存负担。有时候有些属性并不是所有对象都用的到，但是因为不确定，为了所有对象在需要的时候就可以有，你还是不得不放在Object里面。比如说一个最简单的void* UserData，看起来为所有对象附加一个void*数据也挺合理的，用的时候设置取出就好了。但是其实有些类型对象可能一辈子都用不到，用不到的属性，却还占用着内存，就是浪费。所以在一个统一的Object里加数据，就得非常的克制，不然所有的对象都不得不得多一份占用。
多重继承的限制。比如C多重继承于A和B，以前A和B都不是Object的时候还好，虽然大家对C++里的多重继承不太推荐使用，但是基本上也是不会有大的使用问题的。然后现在A和B都继承于Object了，现在让C想多重继承于A和B，就得面临一个尴尬的局面，变成菱形继承了！而甭管用不用得上全部用虚继承显然也是不靠谱的。所以一般有object基类的编程语言，都是直接限制多重继承，改为多重实现接口，避免了数据被继承多份的问题。
类型系统的割裂。除非是像java和C#那样，对用户隐藏整个背后系统，否则用户在面对原生C++类型和Object类型时，就不得不去思考划分对象类型。两套系统在交叉引用、互相加载释放、消息通信、内存分配时采用的机制和规则也是大不一样的。哪些对象应该继承于Object，哪些不用；哪些可以GC，哪些只能用智能指针管理；C++对象里new了Object对象该怎么管理，Object对象里new了C++对象什么时候释放？这些都是强加给用户思考的问题。
著名的沃斯基·索德曾经说过，设计就是权衡的艺术。那些得到的UE已经想要攥在手里了，而那些代价我们也得想办法去尽量降低和规避：
针对太过复杂的Object基类，虽然我常常夸UE的设计优雅卓越，但是我这里要黑一下UE，感觉UE的Object基类已经有点破罐子破摔了，能非常明显的感觉到了进化留下的痕迹，一个UObject你给我分了三层继承：（UObjectBase->UObjectBaseUtility->UObject），关键是头两层你还都没有子类。而Object相关的Flags常常竟然把32位都给占完了也是牛。念在UE提供了那么多的UObject功能模块实现，类声明里大几十个方法我们也只好忍了吧。这一块太过底层，估计也不敢大刀阔斧的整改，只能期待UE5再说了。
sizeof(UObject)==56。56个字节相对来说应该还是可以接受，关掉Stat的话还能再少一个指针大小。当然这里并没有考虑到外围Class系统的内存占用，但是光光一个对象基础的数据占用56字节起步的话，我觉得已经非常优秀了。10000个对象是546K，1百万个对象是53M。一方面游戏里的对象其实数量没有那么多，对于百万粒子那种也可以用原生的C++对象优化，另一方面现在各个平台内存也越来越宽裕了，所以这个问题已经解决得在可接受范围内了。
规避多重继承，UE在BP里提供的也是多重继承Interface的方案。在C++层面上，我们只能尽量规避不要多重继承多个UObject子类，实在想要实现功能复用，也可以采用组合的组件模式，或者把共同逻辑写在C++的类型上，比如UE中众多的F开头的类就是如此的功能类。总之这个问题，好在我们可以用方式规避掉。
只能多学习了。没办法，现实就是不完美的。越是设计精巧的系统就越是难以理解。不过一方面UE提倡在BP里实现游戏逻辑，C++充当BP的VM，就可以完全对用户隐藏掉复杂性。另一方面，UE在UObject上也提供了大量的辅助设计，如UCLASS等各种宏的便利，NewObject方便接口，UHT的自动分析生成代码，尽量避免用户直接涉及到UObject的内部细节。所以单从一个使用者的角度来说，如今的状态已经挺友好的了，Object工作的挺好，几乎不需要去操心或者帮它补漏。至于想理解的更深层次的话，就只能靠开发者们更用心的学习了。
权衡的结果大家也都知道了，UE下定雄心选择了开始搭建Object，提供了那么多我们日常使用的功能。我的Medusa引擎也是非常艳羡UE那么多便利的功能，但是让我从头开始去再去搭建一套，限于精力有限，我是不敢去做的。光一个GC就得有大量的算法权衡，多线程处理的各种细节和各种优化，更何况再融合了反射、序列化、CDO、统计，想实现得既优雅又性能优越就真的是一件非常不容易的事，代码写完之后还得需要大量的测试和修复才能慢慢稳定下来能用。信任感的建立是很难的，一旦出现对象被释放掉了或者没有释放，你第一时间怀疑的应该是你的使用有问题，而如果UE给你的印象是怀疑UE的Object实现内部有bug，那你就会逐渐的倾向于弃用UE的那一套，开始撸起袖子自己管理C++对象了。
总结
本文作为专题的开篇，唠了些书写背景的闲话，也闲聊了一下其他游戏引擎是怎么看待游戏内对象管理这回事的。每款游戏引擎都有自己的产生背景和侧重点，再加上设计的理念也不一样，所以就会产生各种各样的架构。接着探讨了设计一个Object系统有哪些好处和缺点，我不知道UE最初的UObject设计是从何而来的，但是如果没有UObject，没有了富饶的土壤，想要有繁茂的森林就比较困难了。各引擎的开发团队竞赛的时候，大家其实水平都差不了多少，同样想支持一个最新功能的时候，我利用上了统一的Object机制开发用了一周上线；你因为少了一些代码上的便利，还得自己手动管理内存，写序列化，再撸编辑器支持，代码写了两周，修复Bug用了2周，交付用户使用的时候，代码的接口因为不能反射也不是那么易用，慢慢的竞争优势就弱了。没那么方便调试统计，开发者修复bug起来就费劲，埋的Bug多了，用户觉得你越来越不稳定，引擎的生命力就是这么一步步一点点枯萎掉的。所以不要觉得引擎只要堆积功能就行了，一开始有个好的结构是重中之重。
闲话说完才可以开始之后的一个个功能的详细叙述。那么亲爱的读者们，请跟着我的脚步，重走UE曾经走过的路，让我们试着从头开始搭建一个Object系统，一步步的让她羽翼丰满多才多艺。
下篇：UObject（二）类型系统概述
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（二）类型系统概述</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/24445322
引言
上一篇我们谈到了在游戏引擎，或者在程序和高级编程语言中，设计一个统一对象模型得到的好处，和要付出的代价，以及在UE里是怎么对之尽量降低规避的。那么从本篇开始，我们就开始谈谈如何开始构建这么一个对象模型，并在此之上逐渐扩展以适应引擎的各种功能需求的。
众所周知，一般游戏引擎最底层面对的都是操作系统API，硬件SDK，所能借助到的工具也往往只有C++本身。所以考虑从原生的C++基础上，搭建对象系统，往往得从头开始造轮子，最底层也是最核心的机制当然必须得掌控在自己的手中，以后升级改善增加功能也才能不受限制。
那么，从头开始的话，Object系统有那么多功能：GC，反射，序列化，编辑器支持……应该从哪一个开始？哪一个是必需的？GC不是，因为大不了我可以直接new/delete或者智能指针引用技术，毕竟别的很多引擎也都是这么干的。序列化也不是，大不了每个子类里手写数据排布，麻烦是麻烦，但是功能上也是可以实现的。编辑器支持，默认类对象，统计等都是之后额外附加的功能了。那你说反射为何是必需的？大多数游戏引擎用的C++没有反射，不也都用得好好的？确实也如此，不利用反射的那些功能，不动态根据类型创建对象，不遍历属性成员，不根据名字调用函数，大不了手写绕一下，没有过不去的坎。但是既然上文已经论述了一个统一Object模型的好处，那么如果在Object身上不加上反射，无疑就像是砍掉了Object的一双翅膀，让它只能在地上行走，而不能在更宽阔空间内发挥威力。还有另一个方面的考虑是，反射作为底层的系统，如果实现完善了，也可以大大裨益其他系统的实现，比如有了反射，实现序列化起来就很方便了；有没有反射，也关系到GC实现时的方案选择，完全是两种套路。简单举个例，反射里对每个object有个class对象保存信息，所以理论上class身上就可以保存所有该类型的object指针引用，这个信息GC就可以利用起来实现一些功能；而没有这个class对象的话，GC的实现就得走别的方案路子了。所以说是先实现反射，有了一个更加扎实的对象系统基础后，再在此之上实现GC才更加的明智。
类型系统
虽然之上一直用反射的术语来描述我们熟知的那一套运行时得到类型信息的系统，动态创建类对象等，但是其实“反射”只是在“类型系统”之后实现的附加功能，人们往往都太过注重最后表露的强大功能，而把朴实的本质支撑给忘记了。想想看，如果我实现了class类提供Object的类型信息，但是不提供动态创建，动态调用函数等功能，请问还有没有意义？其实还仍然是非常有意义的，光光是提供了一个类型信息，就提供了一个Object之外的静态信息载体，也能构建起来object之间的派生从属关系，想想UE里如果去掉了根据名字创建类对象的能力，是会损失一些便利功能，但确实也还没有到元气大伤的程度，GC依然能跑得起来。
所以以后更多用“类型系统”这个更精确的术语来表述object之外的类型信息构建，而用“反射”这个术语来描述运行时得到类型的功能，通过类型信息反过来创建对象，读取修改属性，调用方法的功能行为。反射更多是一种行为能力，更偏向动词。类型系统指的是程序运行空间内构建出来的类型信息树组织，
C# Type
因C++本身运行时类型系统的疲弱，所以我们首先拿一个已经实现完善的语言，来看看其最后成果是什么样子。这里选择了C#而不是java，是因为我认为C#比java更强大优雅（不辩），Unity用C#作为脚本语言，UE本身也是用C#作为编译UBT的实现语言。
在C#里，你可以通过以下一行代码方便的得到类型信息：
Type type = obj.GetType();  //or typeof(MyClass)
本篇不是C#反射教程（关心的自己去找相关教程），但这里还是简单提一下我们需要关注的：
Assembly是程序集的意思，通常指的是一个dll。
Module是程序集内部的子模块划分。
Type就是我们最关心的Class对象了，完整描述了一个对象的类型信息。并且Type之间也可以通过BaseType，DeclaringType之类的属性来互相形成Type关系图。
ConstructorInfo描述了Type中的构造函数，可以通过调用它来调用特定的构造函数。
EventInfo描述了Type中定义的event事件（UE中的delegate大概）
FiedInfo描述了Type中的字段，就是C++的成员变量，得到之后可以动态读取修改值
PropertyInfo描述了Type中的属性，类比C++中的get/set方法组合，得到后可以获取设置属性值。
MethodInfo描述了Type中的方法。获得方法后就可以动态调用了。
ParameterInfo描述了方法中的一个个参数。
Attributes指的是Type之上附加的特性，这个C++里并没有，可以简单理解为类上的定义的元数据信息。
可以看到C#里的Type几乎提供了一切信息数据，简直就像是把编译器编译后的数据都给暴露出来了给你。实际上C#的反射还可以提供其他更高级的功能，比如运行时动态创建出新的类，动态Emit编译代码，不过这些都是后话了（在以后讲解蓝图时应该还会提到）。当前来说，我希望读者们能有一个大概的印象就是，用代码声明定义出来的类型，当然可以通过一种数据结构完整描述出来，并在运行时再得到。
C++ RTTI
而谈到C++中的运行时类型系统，我们一般会说RTTI（Run-Time Type Identification），只提供了两个最基本的操作符：
typeid
这个关键字的主要作用就是用于让用户知道是什么类型，并提供一些基本对比和name方法，作用也顶多只是让用户判断从属于不同的类型，所以其实说起来type_info的应用并不广泛，一般来说也只是把它当作编译器提供的一个唯一类型Id。
const std::type_info& info = typeid(MyClass);
class type_info
{
public:
    type_info(type_info const&) = delete;
    type_info& operator=(type_info const&) = delete;
    size_t hash_code() const throw();
    bool operator==(type_info const& _Other) const throw();
    bool operator!=(type_info const& _Other) const throw();
    bool before(type_info const& _Other) const throw();
    char const* name() const throw();
};
dynamic_cast
该转换符用于将一个指向派生类的基类指针或引用转换为派生类的指针或引用，使用条件是只能用于含有虚函数的类。转换引用失败会抛出bad_cast异常，转换指针失败会返回null。
Base* base=new Derived();
Derived* p=dynamic_cast<Derived>(base);
if(p){...}else{...}
dynamic_cast内部机制其实也是利用虚函数表里的类型信息来判断一个基类指针是否指向一个派生类对象。其目的更多是用于在运行时判断对象指针是否为特定一个子类的对象。
其他的比如运用模板，宏标记就都是编译期的手段了。C++在RTTI方面也确实是非常的薄弱，传说中的标准反射提案也遥遥无期，所以大家就都得八仙过海各显神通，采用各种方式模拟实现了。C++都能用于去实现别的语言底层，不就是多一个轮子的事嘛。
C++当前实现反射的方案
既然C++本身没提供足够的类型信息，那我们就采用各种其他各种额外方式来搜集，并保存构建起来之后供程序使用。根据搜集信息的方式不同，C++的反射方案也有以下流派：
宏
基本思想是采用手动标记。在程序中用手动的方式注册各个类，方法，数据。大概就像这样：
struct Test
{
    Declare_Struct(Test);
    Define_Field(1, int, a)
    Define_Field(2, int, b)
    Define_Field(3, int, c)
    Define_Metadata(3)
};
用宏偷梁换柱的把正常的声明换成自己的结构。简单可见这种方式还比较的原始，写起来也非常的繁琐。因此往往用的不多。更重要的是往往需要打破常规的书写方式，因此常常被摒弃掉。
模板
C++中的模板是应该也可以算是最大区别于别的语言的一个大杀器了，引导其强大的编译器类型识别能力构建出相应的数据结构，理论上也是可以实现出一定的类型系统。举一个Github实现比较优雅的C++RTTI反射库做例子：rttr
#include <rttr/registration>
using namespace rttr;
struct MyStruct { MyStruct() {}; void func(double) {}; int data; };
RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
         .constructor<>()
         .property("data", &MyStruct::data)
         .method("func", &MyStruct::func);
}
说实话，这写得已经非常简洁优雅了。算得上是达到了C++模板应用的巅峰。但是可以看到，仍然需要一个个的手动去定义类并获取方法属性注册。优点是轻量程序内就能直接内嵌，缺点是不适合懒人。
编译器数据分析
还有些人就想到既然C++编译器编译完整个代码，那肯定是有完整类型信息数据的。那能否把它们转换保存起来供程序使用呢？事实上这也是可行的，比如@vczh的GacUI里就分析了VC编译生成后pdb文件，然后抽取出类型定义的信息实现反射。VC确实也提供了IDiaDataSource COM组件用来读取pdb文件的内容。用法可以参考：GacUI Demo：PDB Viewer（分析pdb文件并获取C++类声明的详细内容）。
理论上来说，只要你能获取到跟编译器同级别的类型信息，你基本上就像是全知了。但是缺点是分析编译器的生成数据，太过依赖平台（比如只能VC编译，换了Clang就是另一套方案），分析提取的过程往往也比较麻烦艰深，在正常的编译前需要多加一个编译流程。但优点也是得到的数据最是全面。
这种方案也因为太过麻烦，所以业内用的人不多。
工具生成代码
自然的有些人就又想到，既然宏和模板的方法，太过麻烦。那我能不能写一个工具来自动完成呢？只要分析好C++代码文件，或者分析编译器数据也行，然后用预定义好的规则生成相应的C++代码来跟源文件对应上。
一个好例子就是Qt里面的反射：
#include <QObject>
class MyClass : public QObject
{
    Q_OBJECT
　　Q_PROPERTY(int Member1 READ Member1 WRITE setMember1 )
　　Q_PROPERTY(int Member2 READ Member2 WRITE setMember2 )
　　Q_PROPERTY(QString MEMBER3 READ Member3 WRITE setMember3 )
　　public:
　　    explicit MyClass(QObject *parent = 0);
　　signals:
　　public slots:
　　public:
　　　 Q_INVOKABLE int Member1();
　　　 Q_INVOKABLE int Member2();
　　　 Q_INVOKABLE QString Member3();
　　　 Q_INVOKABLE void setMember1( int mem1 );
　　　 Q_INVOKABLE void setMember2( int mem2 );
　　　 Q_INVOKABLE void setMember3( const QString& mem3 );
　　　 Q_INVOKABLE int func( QString flag );
　　private:
　　　 int m_member1;
　　　 int m_member2;
　　　 QString m_member3;
　};
大概过程是Qt利用基于moc(meta object compiler)实现，用一个元对象编译器在程序编译前，分析C++源文件，识别一些特殊的宏Q_OBJECT、Q_PROPERTY、Q_INVOKABLE……然后生成相应的moc文件，之后再一起全部编译链接。
UE里UHT的方案
不用多说，你们也能想到UE当前的方案也是如此，实现在C++源文件中空的宏做标记，然后用UHT分析生成generated.h/.cpp文件，之后再一起编译。
UCLASS()
class HELLO_API UMyClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Test")
	float Score;
	UFUNCTION(BlueprintCallable, Category = "Test")
	void CallableFuncTest();
	UFUNCTION(BlueprintNativeEvent, Category = "Test")
	void NativeFuncTest();
	UFUNCTION(BlueprintImplementableEvent, Category = "Test")
	void ImplementableFuncTest();
};
这种方式的优点是能够比较小的对C++代码做修改，所要做的只是在代码里加一些空标记，并没有破坏原来的类声明结构，而且能够以比较友好的方式把元数据和代码关联在一起，生成的代码再复杂也可以对用户隐藏起来。一方面分析源码得力的话能够得到和编译器差不多的信息，还能通过自己的一些自定义标记来提供更多生成代码的指导。缺点是实现起来其实也是挺累人的，完整的C++的语法分析往往是超级复杂的，所以限制是自己写的分析器只能分析一些简单的C++语法规则和宏标记，如果用户使用比较复杂的语法时候，比如用#if /#endif包裹一些声明，就会让自己的分析器出错了，还好这种情况不多。关于多一次编译的问题，也可以通过自定义编译器的编译脚本UBT来规避。
如果是熟悉C#的朋友，一眼就能看出来这和C#的Attribute的语法简直差不多一模一样，所以UE也是吸收了C#语法反射的一些优雅写法，并利用上了C++的宏魔法，当然生成的代码里模板肯定也是少不了的。采取众长最后确定了这种类型信息搜集方案。
总结
本篇主要是解释了为何要以类型系统作为搭建Object系统的第一步，并描绘了C#语言里完善的类型系统看起来是什么样子，接着讨论了C++当前的RTTI工具，然后环顾一下当前C++业内的各种反射方案。知道别人家好的是什么样子，知道自己现在手里有啥，知道当前业内别人家是怎么尝试解决这个问题的，才能心中有数知道为何UE选择了目前的方案，知道UE的这套方案在业内算是什么水平。
依然说些废话，笔者一向认为想解释清楚一件东西，更多的应该是解释清楚背后的各种概念。否则对着源码，罗列出来各个类，说一下每个接口的作用，数据互相怎么引用，流程是怎么跑的，你能很快的就知道一大堆信息。你只是知道了What，How，但是还挡不住别人问一句Why。而功力的提升就在于问一个个why中，A办法能做，B办法也行，那为什么最后选了C方法？想要回答这个问题，你就得朔古至今，旁征博引，了解各种方法的理念，优劣点，偏重倾向，综合起来才能更好的进行权衡。而设计，就是权衡的艺术。这么写起来也确实有点慢，但是个人权衡一下还是系统性更加的重要。宁愿慢点，质量第一。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（三）类型系统设定和结构</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/24790386
引言
上篇我们谈到了为何设计一个Object系统要从类型系统开始做起，并探讨了C#的实现，以及C++中各种方案的对比，最后得到的结论是UE采用UHT的方式搜集并生成反射所需代码。接下来我们就应该开始着手设计真正的类型系统结构。
在之后的叙述中，我会同时用两个视角来考察UE的这套Object系统：
一是以一个通用的游戏引擎开发者角度来从零开始设计，设想我们正在自己实现一套游戏引擎（或者别的需要Object系统的框架），在体悟UE的Object系统的同时，思考哪些是真正的核心部分，哪些是后续的锦上添花。踏出一条重建Object系统的路来。
二是以当前UE4的现状来考量。UE的Object系统从UE3时代就已经存在了（再远的UE3有知道的前辈还望告知），历经风雨，修修补补，又经过UE4的大改造，所以一些代码读起来很是诘屈聱牙，笔者也并不敢说通晓每一行代码写成那样的原由，只能尽量从UE的角度去思考这么写有什么用意和作用。同时我们也要记得UE是很博大精深没错，但并不代表每一行代码都完美。整体结构上很优雅完善，但也同样有很多小漏洞和缺陷，也并不是所有的实现都是最优的。所以也支持读者们在了解的基础上进行源码改造，符合自己本身的开发需求。
PS：类型系统不可避免的谈到UHT（Unreal Header Tool，一个分析源码标记并生成代码的工具），但本专题不会详细叙述UHT的具体工作流程和原理，只假定它万事如我心意，UHT的具体分析后续会有特定章节讨论。
设定
先假定我们已经接受了UE的设定：
在c++写的class（struct一样，只是默认public而已）的头上加宏标记，在其成员变量和成员函数也同样加上宏标记，大概就是类似C#Attribute的语法。在宏的参数可以按照我们自定的语法写上内容。在UE里我们就可以看到这些宏标记：
#define UPROPERTY(...)
#define UFUNCTION(...)
#define USTRUCT(...)
#define UMETA(...)
#define UPARAM(...)
#define UENUM(...)
#define UDELEGATE(...)
#define UCLASS(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_PROLOG)
#define UINTERFACE(...) UCLASS()
真正编译的时候，大体上都是一些空宏。UCLASS有些特殊，一般情况下最后也都是空宏，另外一些情况下会生成一些特定的事件参数声明等等。不过这暂时跟本文的重点无关。这里重点有两点，一是我们可以通过给类、枚举、属性、函数加上特定的宏来标记更多的元数据；二是在有必要的时候这些标记宏甚至也可以安插进生成的代码来合成编译。
我们也暂时不用管UHT到底应该怎么实现，就也先假定有那么一个工具会在每次编译前扫描我们的代码，获知那些标记宏的位置和内容，并紧接着分析下一行代码的声明含义，最后生成我们所需要的代码。
还有两个小问题是：
为何是生成代码而不是数据文件？
毕竟C++平台和C#平台不一样，同时在引用1里的UnrealPropertySystem(Reflection)里也提到了最重要的区分之处：
One of the major benefits of storing the reflection data as generated C++ code is that it is guaranteed to be in sync with the binary. You can never load stale or out of date reflection data since it’s compiled in with the rest of the engine code, and it computes member offsets/etc… at startup using C++ expressions, rather than trying to reverse engineer the packing behavior of a particular platform/compiler/optimization combo. UHT is also built as a standalone program that doesn’t consume any generated headers, so it avoids the chicken-and-egg issues that were a common complaint with the script compiler in UE3.
简单来说就是避免了不一致性，否则又得有机制去保证数据文件和代码能匹配上。同时跨平台需求也很难保证结构间的偏移在各个平台编译器优化的不同导致得差异。所以还不如简单生成代码文件一起编译进去得了。
如果标记应该分析哪个文件？
既然是C++了，那么生成的代码自然也差不多是.h.cpp的组合。假设我们为类A生成了A.generated.h和A.generated.cpp（按照UE习俗，名字无所谓）。此时A.h一般也都需要Include "A.generated.h"，比如类A的宏标记生成的代码如果想跟A.generated.h里我们生成的代码来个里应外合的话。另一方面，用户对背后的代码生成应该是保持最小惊讶的，用户写下了A.h，他在使用的时候自然也会想include "A.h"，所以这个时候我们的A.generated.h就得找个方式一起安插进来，最方便的方式莫过于直接让A.h include A.generated.h了。那既然每个需要分析的文件最后都会include这么一个*.generated.h，那自然就可以把它本身就当作一种标记了。所以UE目前的方案是每个要分析的文件加上该Include并且规定只能当作最后一个include，因为他也担心会有各种宏定义顺序产生的问题。
#include "FileName.generated.h"
如果你一开始想的是给每个文件也标记个空宏，其实倒也无不可，只不过没有UE这么简洁。但是比如说你想控制你的代码分析工具在分析某个特定文件的时候专门定制化一些逻辑，那这种像是C#里AssemblyAttribute的文件宏标记就显示出作用了。UHT目前不需要所以没做罢了。
结构
在接受了设定之后，是不是觉得本来这个写法有点怪的Hello类看起来也有点可爱呢？
#include "Hello.generated.h"
UClass()
class Hello
{
public:
    UPROPERTY()
    int Count;
    UFUNCTION()
    void Say();
};
先什么都不管，假装UHT已经为我们搜集了完善的信息，然后这些信息在代码里应该怎么储存？这就要谈到一些基本的程序结构了。一个程序，简单来说，可以认为是由众多的类型和函数嵌套组成的，类型有基础类型，枚举，类；类里面能够再定义字段和函数，甚至是子类型；函数有输入和输出，其内部也依然可以定义子类型。这是C++的规则，但你在支持的时候就可以在上面进行缩减，比如你就可以不支持函数内定义的类型。
先来看看UE里形成的结构：
C++有声明和定义之分，图中黄色的的都可以看作是声明，而绿色的UProperty可以看作是字段的定义。在声明里，我们也可以把类型分为可聚合其他成员的类型和“原子”类型。
聚合类型（UStruct）：
UFunction，只可包含属性作为函数的输入输出参数
UScriptStruct，只可包含属性，可以理解为C++中的POD struct，在UE里，你可以看作是一种“轻量”UObject，拥有和UObject一样的反射支持，序列化，复制等。但是和普通UObject不同的是，其不受GC控制，你需要自己控制内存分配和释放。
UClass，可包含属性和函数，是我们平常接触到最多的类型
原子类型：
UEnum，支持普通的枚举和enum class。
int，FString等基础类型没必要特别声明，因为可以简单的枚举出来，可以通过不同的UProperty子类来支持。
把聚合类型们统一起来，就形成了UStruct基类，可以把一些通用的添加属性等方法放在里面，同时可以实现继承。UStruct这个名字确实比较容易引起歧义，因为实际上C++中USTRUCT宏生成了类型数据是用UScriptStruct来表示的。
还有个类型比较特殊，那就是接口，可以继承多个接口。跟C++中的虚类一样，不同的是UE中的接口只可以包含函数。一般来说，我们自己定义的普通类要继承于UObject，特殊一点，如果是想把这个类当作一个接口，则需要继承于UInterface。但是记得，生成的类型数据依然用UClass存储。从“#define UINTERFACE(...) UCLASS()”就可以看出来，Interface其实就是一个特殊点的类。UClass里通过保存一个TArray<FImplementedInterface> Interfaces数组，其子项又包含UClass* Class来支持查询当前类实现了那些接口。
最后是定义，在UE里是UProperty，可以理解为用一个类型定义个字段“type instance;”。UE有Property，其Property有子类，子类之多，一屏列不下。实际深入代码的话，会发现UProperty通过模板实例化出特别多的子类，简单的如UBoolProperty、UStrProperty，复杂的如UMapProperty、UDelegateProperty、UObjectProperty。后续再一一展开。
元数据UMetaData其实就是个TMap<FName, FString>的键值对，用于为编辑器提供分类、友好名字、提示等信息，最终发布的时候不会包含此信息。
为了加深一下概念，我列举一些UE里的用法，把图和代码加解释一起关联起来理解的会更深刻些：
#include "Hello.generated.h"
UENUM()
namespace ESearchCase
{
	enum Type
	{
		CaseSensitive,
		IgnoreCase,
	};
}
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	MY_Dance 	UMETA(DisplayName = "Dance"),
	MY_Rain 	UMETA(DisplayName = "Rain"),
	MY_Song		UMETA(DisplayName = "Song")
};
USTRUCT()
struct HELLO_API FMyStruct
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	float Score;
};
UCLASS()
class HELLO_API UMyClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Hello")
	float Score;
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void CallableFuncTest();
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void OutCallableFuncTest(float& outParam);
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void RefCallableFuncTest(UPARAM(ref) float& refParam);
	UFUNCTION(BlueprintNativeEvent, Category = "Hello")
	void NativeFuncTest();
	UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
	void ImplementableFuncTest();
};
UINTERFACE()
class UMyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};
class IMyInterface
{
	GENERATED_IINTERFACE_BODY()
	UFUNCTION(BlueprintImplementableEvent)
	void BPFunc() const;
	virtual void SelfFunc() const {}
};
先不用去管宏里面参数的含义，目前先形成大局的印象。但是注意，我这里没有提到蓝图里可以创建的枚举、接口、结构、类等。它们也都是相应的从各自UEnum、UScriptStruct、UClass再派生出来。这个留待之后再讲。读者们需要明白的是，一旦我们能够用数据来表达类型了，我们就可以自定义出不同的数据来动态创建出不同的其他类型。
思考：为什么还需要基类UField？
UStruct好理解，表示聚合类型。那为什么不直接UProperty、UStruct、UEnum继承于UObject？在笔者看来，主要有三点：
为了统一所有的类型数据，如果所有的类型数据类都有个基类的话，那么我们就很容易用一个数组把所有的类型数据都引用起来，可以方便的遍历。另外也关乎到一个顺序的问题，比如在类型A里定义了P1、F1、P2、F2，属性和函数交叉着定义，在生成类型A的类型数据UClass内部就也可以是以同样的顺序，以后要是想回溯出来一份定义，也可以跟原始的代码顺序一致，如果是用属性和函数分开保存的话，就会麻烦一些。
如上图可见，所有的不管是声明还是定义（UProperty、UStruct、UEnum），都可以附加一份额外元数据UMetaData，所以应该在它们的基类里保存。
方便添加一些额外的方法，比如加个Print方法打印出各个字段的声明，就可以在UField里加上虚方法，然后在子类里重载实现。
UField名字顾名思义，就是不管是声明还是定义，都可以看作是类型系统里的一个字段，或者叫领域也行，术语不同，但能理解到一个更抽象统一的意思就行。
思考：为什么UField要继承于UObject？
这问题，其实也是在问，为什么类型数据也要同样继承于UObject？反过来问，如果不继承会怎么样？把继承链断开，类型数据自成一派，其实也未尝不可。我们来列举一下UObject身上有哪些功能，看看哪些是类型系统所需要的。
GC，可有可无，类型数据一开始分配了就可以不释放，当前GC也是利用了类型系统来支持对象引用遍历
反射，略
编辑器集成，也可以没有，编辑器就是利用类型数据来进行集成编辑的，当然当我们在蓝图里创建函数变量等操作其实也可以看作就是在编辑类型数据。
CDO，不需要，每个类型的类型数据一般只有一份，CDO是用在对象身上的
序列化，必须有，类型数据当然需要保存下来，比如蓝图创建的类型。
Replicate，用处不大，因为目前网络间的复制也是利用了类型数据来进行的，类型数据本身的字段的改变复制想来好像没有什么应用场景
RPC，也无所谓
自动属性更新，也不需要，类型数据一般不会那么频繁变动
统计，可有可无
总结下来，发现序列化是最重要的功能，GC和其他一些功能算是锦上添花。所以归结起来可有可无再加上一些必要功能，本着统一的思想，就让所有类型数据也都继承于UObject了，这样序列化等操作也不需要写两套。虽然这看起来不是那么的纯粹，但是总体上来说利大于弊。
在对象上，你可以用Instance->GetClass()来获得UClass对象，在UClass本身上调用GetClass()返回的是自己本身，这样可以用来区分对象和类型数据。
总结
UE的这套类型数据组织架构，以我目前的了解和知识，私以为优雅程度有80/100分。大体上可用，没什么问题，从UE3时代修修改改过来，我觉得已经很不容易了。只是很多地方从技术角度上来说，不是那么的纯粹，比如接口的类型数据也依然是UClass，但是却又不允许包含属性，这个从结构上就没有做限制，只能通过UHT检查和代码中类型判断来区分；又比如UStruct里包含的是UField链表，其实隐含的意思就是UStruct里既可以有嵌套类型又可以有属性，灵活的同时也少了限制，嵌套类型目前是没有了，但是UFunction也只能包含属性，UScriptStruct只有属性而不能有函数；还有UStruct里用UStruct* SuperStruct指向继承的基类。但是UFunction的基Function是什么意义？所以之后如有含糊之时，读者朋友们可以用下面这个图结构来清醒一下：
可以简单理解这就是UE想表达的真正含义。UMetaData虽然在UPackage里用TMap<UObject*，TMap<FName, FString>>来映射，但是实际上也只有UField里有GetMetaData的接口，所以一般UMetaData也只是跟UField关联罢了。UStruct包含UProperty，UClass和UScriptStruct又包含UFunction，这才是一般实操时用到的数据关联。
含糊之处当然无伤大雅，只不过如果读者作为一个通用引擎研究开发者而言，也要认识到UE的系统的不足之处，不可一一照抄。读者如果自己想要实现的话，左右有两种方向，一种是向着类型单一，但是更多用逻辑来控制，比如C#的类型系统，一个Type之下可以获得各种FieldInfo、MethodInfo等；另一种是向着类型细分，用结构来限制，比如增加UScriptInterface来表达Interface的元数据，把包含属性和函数的功能封装成PropertyMap和FunctionMap，然后让UScriptStruct、UFunction、UClass拥有PropertyMap，让UClass，UScriptInterface拥有FunctionMap。都有各自的利弊和灵活度不同，这里就不展开一一细说了，读者们可以自己思考权衡。
我们当前更关注是如何理解UE这套类型系统（也叫属性系统，为了和图形里的反射作区分），所以下篇我们将继续深入，了解UE里怎么开始开始构建这个结构。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（四）类型系统代码生成</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/25098685
引言
上文讲到了UE的类型系统结构，以及UHT分析源码的一些宏标记设定。在已经进行了类型系统整体的设计之后，本文将开始讨论接下来的步骤。暂时不讨论UHT的细节，假设UHT已经分析得到了足够的类型元数据信息，下一步就是利用这个信息在程序内存中构建起前文的类型系统结构，这个过程我们称之为注册。同一般程序的构建流程需要经过预处理、编译、汇编、链接一样，UE为了在内存中模拟构建的过程，在概念上也需要以下几个阶段：生成，收集，注册，链接。总体的流程比较繁杂，因此本文首先开始介绍第一阶段，生成。在生成阶段，UHT分析我们的代码，并生成类型系统的相关代码。
Note1：生成的代码和注册的过程会因为HotReload功能的开启与否有些不一样，因此为了最简化流程阐述，我们先关闭HotReload，关闭的方式是在Hello.Build.cs里加上一行：Definitions.Add("WITH_HOT_RELOAD_CTORS=0");
Note2：本文开始及后续会简单的介绍一些用到的C++基础知识，但只是点到为止，不做深入探讨。
C++ Static Lazy初始化模式
一种我们常用，也是UE中常用的单件懒惰初始化模式是：
Hello* StaticGetHello()
{
    static Hello* obj=nullptr;
    if(!obj)
    {
        obj=...
    }
    return obj;
}
或者
Hello& StaticGetHello()
{
    static Hello obj(...);
    return obj;
}
前者非常简单，也没考虑多线程安全，但是在单线程环境下足够用了。用指针的原因是，有一些情况，这些对象的生命周期是由别的地方来管理的，比如UE里的GC，因此这里只static化一个指针。否则的话，还是后者更加简洁和安全。
UHT代码生成
在C++程序中的预处理是用来对源代码进行宏展开，预编译指令处理，注释删除等操作。同样的，一旦我们采用了宏标记的方法，不管是怎么个标记语法，我们都需要进行简单或复杂的词法分析，提取出有用的信息，然后生成所需要的代码。在引擎里创建一个空C++项目命名为Hello，然后创建个不继承的MyClass类。编译，UHT就会为我们生成以下4个文件（位于Hello\Intermediate\Build\Win64\Hello\Inc\Hello）
HelloClasses.h：目前无用
MyClass.generated.h：MyClass的生成头文件
Hello.generated.dep.h：Hello.generated.cpp的依赖头文件，也就是顺序包含上述的MyClass.h而已
Hello.generated.cpp：该项目的实现编译单元。
其生成的文件初看起来很多很复杂，但其实比较简单，不过就是一些宏替换而已。生成的函数大都也以Z_开头，笔者开始也在猜想Z_前缀的缩写含义，感谢NetFly向Epic的人求证之后的回答：
The 'Z_' prefix is not part of any official naming convention, and it
doesn't really mean anything. Some generated functions were named this way
to avoid name collisions and so that these functions will appear together at the
bottom of intelisense lists.
简而言之，没什么特别含义，就是简单为了避免命名冲突，用Z是为了字母排序总是出现在智能感知的最下面，尽量隐藏起来。
接下来，请读者们紧跟着我的步伐，开始进行这趟剖析之旅。
UCLASS的生成代码剖析
先从一个最简单的UMyClass的开始，总览分析生成的代码结构，接着再继而观察其他UEnum、UStruct、UInterface、UProperty、UFunction的代码生成样式。
MyClass.h
首先是我们自己编写或者引擎帮我们生成的文件样式：
// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyClass.generated.h"
UCLASS()
class HELLO_API UMyClass : public UObject
{
	GENERATED_BODY()
};
第5行：#include "UObject/NoExportTypes.h" 通过查看文件内容，发现这个文件在编译的时候就是Include了其他一些更基础的头文件，比如#include "Math/Vector.h"，因此你才能在MyClass里不用include就引用这些类。当然，还有一些内容是专门供UHT使用来生成蓝图类型的，现在暂时不需要管。
第6行：#include "MyClass.generated.h"，就是为了引用生成的头文件。这里请注意的是，该文件include位置在类声明的前面，之后谈到宏处理的时候会用到该信息。
第11行：GENERATED_BODY()，该宏是重中之重，其他的UCLASS宏只是提供信息，不参与编译，而GENERATED_BODY正是把声明和元数据定义关联到一起的枢纽。继续查看宏定义：
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY)
会发现GENERATED_BODY最终其实只是生成另外一个宏的名称，因为：
CURRENT_FILE_ID的定义是在MyClass.generated.h的89行：\#define CURRENT_FILE_ID Hello_Source_Hello_MyClass_h，这是UHT通过分析文件得到的信息。
__LINE__标准宏指向了该宏使用时候的的函数，这里是11。加了一个__LINE__宏的目的是为了支持在同一个文件内声明多个类，比如在MyClass.h里接着再声明UMyClass2，就可以支持生成不同的宏名称。
因此总而生成的宏名称是Hello_Source_Hello_MyClass_h_11_GENERATED_BODY，而这个宏就是定义在MyClass.generated.h的77行。值得一提的是，如果MyClass类需要UMyClass(const FObjectInitializer& ObjectInitializer)的构造函数自定义实现，则需要用GENERATED_UCLASS_BODY宏来让最终生成的宏指向Hello_Source_Hello_MyClass_h_11_GENERATED_BODY_LEGACY（MyClass.generated.h的66行），其最终展开的内容会多一个构造函数的内容实现。
MyClass.generated.h
UHT分析生成的文件内容如下：
PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HELLO_MyClass_generated_h
#error "MyClass.generated.h already included, missing '#pragma once' in MyClass.h"
#endif
#define HELLO_MyClass_generated_h
#define Hello_Source_Hello_MyClass_h_11_RPC_WRAPPERS    //先忽略
#define Hello_Source_Hello_MyClass_h_11_RPC_WRAPPERS_NO_PURE_DECLS  //先忽略
#define Hello_Source_Hello_MyClass_h_11_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesUMyClass(); \
	friend HELLO_API class UClass* Z_Construct_UClass_UMyClass(); \
	public: \
	DECLARE_CLASS(UMyClass, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Hello"), NO_API) \
	DECLARE_SERIALIZER(UMyClass) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};
#define Hello_Source_Hello_MyClass_h_11_INCLASS \
	private: \
	static void StaticRegisterNativesUMyClass(); \
	friend HELLO_API class UClass* Z_Construct_UClass_UMyClass(); \
	public: \
	DECLARE_CLASS(UMyClass, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Hello"), NO_API) \
	DECLARE_SERIALIZER(UMyClass) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};
#define Hello_Source_Hello_MyClass_h_11_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyClass) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyClass); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyClass); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyClass(UMyClass&&); \
	NO_API UMyClass(const UMyClass&); \
public:
#define Hello_Source_Hello_MyClass_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyClass(UMyClass&&); \
	NO_API UMyClass(const UMyClass&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyClass); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyClass); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyClass)
#define Hello_Source_Hello_MyClass_h_11_PRIVATE_PROPERTY_OFFSET     //先忽略
#define Hello_Source_Hello_MyClass_h_8_PROLOG   //先忽略
#define Hello_Source_Hello_MyClass_h_11_GENERATED_BODY_LEGACY \ //两个重要的定义
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hello_Source_Hello_MyClass_h_11_PRIVATE_PROPERTY_OFFSET \
	Hello_Source_Hello_MyClass_h_11_RPC_WRAPPERS \
	Hello_Source_Hello_MyClass_h_11_INCLASS \
	Hello_Source_Hello_MyClass_h_11_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#define Hello_Source_Hello_MyClass_h_11_GENERATED_BODY \    //两个重要的定义
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hello_Source_Hello_MyClass_h_11_PRIVATE_PROPERTY_OFFSET \
	Hello_Source_Hello_MyClass_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	Hello_Source_Hello_MyClass_h_11_INCLASS_NO_PURE_DECLS \
	Hello_Source_Hello_MyClass_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hello_Source_Hello_MyClass_h    //前文说过的定义
PRAGMA_ENABLE_DEPRECATION_WARNINGS
该文件都是宏定义，因为宏定义是有前后顺序的，因此咱们从尾向前看，请读者此时和上文的代码对照着看。
首先最底下是CURRENT_FILE_ID的定义
接着是两个上文说过的GENERATED_BODY定义，先从最简单的结构开始，不管那些PRIVATE_PROPERTY_OFFSET和PROLOG，以后会慢慢介绍到。这两个宏接着包含了4个声明在上面的其他宏。目前来说Hello_Source_Hello_MyClass_h_11_INCLASS和Hello_Source_Hello_MyClass_h_11_INCLASS_NO_PURE_DECLS的定义一模一样，而Hello_Source_Hello_MyClass_h_11_STANDARD_CONSTRUCTORS和Hello_Source_Hello_MyClass_h_11_ENHANCED_CONSTRUCTORS的宏，如果读者仔细查看对照的话，会发现二者只差了“: Super(ObjectInitializer) { }; ”构造函数的默认实现。
我们继续往上，以Hello_Source_Hello_MyClass_h_11_ENHANCED_CONSTRUCTORS为例：
#define Hello_Source_Hello_MyClass_h_11_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \   //默认的构造函数实现
private: \  //禁止掉C++11的移动和拷贝构造
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyClass(UMyClass&&); \
	NO_API UMyClass(const UMyClass&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyClass); \     //因为WITH_HOT_RELOAD_CTORS关闭，展开是空宏
    DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyClass); \   //同理，空宏
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyClass)
继续查看DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL的定义：
#define DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(TClass) \
	static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())TClass(X); }
声明定义了一个构造函数包装器。需要这么做的原因是，在根据名字反射创建对象的时候，需要调用该类的构造函数。可是类的构造函数并不能用函数指针指向，因此这里就用一个static函数包装一下，变成一个"平凡"的函数指针，而且所有类的签名一致，就可以在UClass里用一个函数指针里保存起来。见引擎里Class.h的声明：
class COREUOBJECT_API UClass : public UStruct
...
{
    ...
	typedef void (*ClassConstructorType) (const FObjectInitializer&);
	ClassConstructorType ClassConstructor;
	...
}
当然，如果读者需要自己实现一套反射框架的时候也可以采用更简洁的模式，采用模板实现也是异曲同工。
template<class TClass>
void MyConstructor( const FObjectInitializer& X )
{ 
	new((EInternal*)X.GetObj())TClass(X);
}
再继续往上：
#define Hello_Source_Hello_MyClass_h_11_INCLASS \
	private: \
	static void StaticRegisterNativesUMyClass(); \  //定义在cpp中，目前都是空实现
	friend HELLO_API class UClass* Z_Construct_UClass_UMyClass(); \ //一个构造该类UClass对象的辅助函数
	public: \
	DECLARE_CLASS(UMyClass, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Hello"), NO_API) \   //声明该类的一些通用基本函数
	DECLARE_SERIALIZER(UMyClass) \  //声明序列化函数
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};   //这个标记指定了该类是C++Native类，不能动态再改变，跟蓝图里构造的动态类进行区分。
可以说DECLARE_CLASS是最重要的一个声明，对照着定义：DECLARE_CLASS(UMyClass, UObject, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/Hello"), NO_API)
TClass：类名 TSuperClass：基类名字
TStaticFlags：类的属性标记，这里是0，表示最默认，不带任何其他属性。读者可以查看EClassFlags枚举来查看其他定义。
TStaticCastFlags：指定了该类可以转换为哪些类，这里为0表示不能转为那些默认的类，读者可以自己查看EClassCastFlags声明来查看具体有哪些默认类转换。
TPackage：类所处于的包名，所有的对象都必须处于一个包中，而每个包都具有一个名字，可以通过该名字来查找。这里是"/Script/Hello"，指定是Script下的Hello，Script可以理解为用户自己的实现，不管是C++还是蓝图，都可以看作是引擎外的一种脚本，当然用这个名字也肯定有UE3时代UnrealScript的影子。Hello就是项目名字，该项目下定义的对象处于该包中。Package的概念涉及到后续Object的组织方式，目前可以简单理解为一个大的Object包含了其他子Object。
TRequiredAPI：就是用来Dll导入导出的标记，这里是NO_API，因为是最终exe，不需要导出。
#define DECLARE_CLASS( TClass, TSuperClass, TStaticFlags, TStaticCastFlags, TPackage, TRequiredAPI  ) \
private: \
    TClass& operator=(TClass&&);   \
    TClass& operator=(const TClass&);   \
	TRequiredAPI static UClass* GetPrivateStaticClass(const TCHAR* Package); \
public: \
	/** Bitwise union of #EClassFlags pertaining to this class.*/ \
	enum {StaticClassFlags=TStaticFlags}; \
	/** Typedef for the base class ({{ typedef-type }}) */ \
	typedef TSuperClass Super;\
	/** Typedef for {{ typedef-type }}. */ \
	typedef TClass ThisClass;\
	/** Returns a UClass object representing this class at runtime */ \
	inline static UClass* StaticClass() \
	{ \
		return GetPrivateStaticClass(TPackage); \
	} \
	/** Returns the StaticClassFlags for this class */ \
	inline static EClassCastFlags StaticClassCastFlags() \
	{ \
		return TStaticCastFlags; \
	} \
	DEPRECATED(4.7, "operator new has been deprecated for UObjects - please use NewObject or NewNamedObject instead") \
	inline void* operator new( const size_t InSize, UObject* InOuter=(UObject*)GetTransientPackage(), FName InName=NAME_None, EObjectFlags InSetFlags=RF_NoFlags ) \
	{ \
		return StaticAllocateObject( StaticClass(), InOuter, InName, InSetFlags ); \
	} \
	/** For internal use only; use StaticConstructObject() to create new objects. */ \
	inline void* operator new(const size_t InSize, EInternal InInternalOnly, UObject* InOuter = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags InSetFlags = RF_NoFlags) \
	{ \
		return StaticAllocateObject(StaticClass(), InOuter, InName, InSetFlags); \
} \
	/** For internal use only; use StaticConstructObject() to create new objects. */ \
	inline void* operator new( const size_t InSize, EInternal* InMem ) \
	{ \
		return (void*)InMem; \
	}
大部分都是不言自明的，这里的StaticClass就是我们最经常用到的函数，其内部调用了GetPrivateStaticClass，而其实现正是在Hello.generated.cpp里的。
Hello.generated.cpp
而整个Hello项目会生成一个Hello.generated.cpp
#include "Hello.h"      //包含该项目的头文件，继而包含Engine.h
#include "GeneratedCppIncludes.h"   //包含UObject模块里一些必要头文件
#include "Hello.generated.dep.h"    //引用依赖文件，继而include了MyClass.h
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Hello() {}   //先忽略
	void UMyClass::StaticRegisterNativesUMyClass()  //说是静态注册，但现在都是为空，先忽略
	{
	}
	IMPLEMENT_CLASS(UMyClass, 899540749);   //重要！！！
#if USE_COMPILED_IN_NATIVES //该宏编译的时候会打开
// Cross Module References
	COREUOBJECT_API class UClass* Z_Construct_UClass_UObject(); //引用CoreUObject里的函数，主要是为了得到UObject本身对应的UClass
	HELLO_API class UClass* Z_Construct_UClass_UMyClass_NoRegister();   //构造UMyClass对应的UClass对象，区别是没有后续的注册过程
	HELLO_API class UClass* Z_Construct_UClass_UMyClass();  //构造UMyClass对应的UClass对象
	HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello(); //构造Hello本身的UPackage对象
	UClass* Z_Construct_UClass_UMyClass_NoRegister()
	{
		return UMyClass::StaticClass(); //直接通过访问来获取UClass对象
	}
	UClass* Z_Construct_UClass_UMyClass()   //构造并注册
	{
		static UClass* OuterClass = NULL;   //static lazy模式
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();   //确保UObject本身的UClass已经注册生成
			Z_Construct_UPackage__Script_Hello();   //确保当前Hello项目的UPackage已经创建，因为后续在生成UMyClass的UClass*对象时需要保存在这个UPacage中
			OuterClass = UMyClass::StaticClass();   //访问获得UClass*
			if (!(OuterClass->ClassFlags & CLASS_Constructed))  //防止重复注册
			{
				UObjectForceRegistration(OuterClass);   //提取信息注册自身
				OuterClass->ClassFlags |= 0x20100080;   //增加CLASS_Constructed|CLASS_RequiredAPI标记
				OuterClass->StaticLink();   //“静态”链接，后续解释
#if WITH_METADATA   //编辑器模式下开始
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();    //获取关联到的UPackage其身上的元数据映射，并增加元数据信息
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MyClass.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMyClass(Z_Construct_UClass_UMyClass, &UMyClass::StaticClass, TEXT("UMyClass"), false, nullptr, nullptr, nullptr);    //延迟注册，注入信息，在启动的时候调用
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyClass);    //HotReload相关，先忽略
	UPackage* Z_Construct_UPackage__Script_Hello()  //构造Hello的UPackage
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Hello")), false, false));//注意的是这里只是做一个查找，真正的CreatePackage是在UObjectBase::DeferredRegister里调用的，后续在流程里会讨论到
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);//设定标记和Guid
			FGuid Guid;
			Guid.A = 0x79A097CD;
			Guid.B = 0xB58D8B48;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);
		}
		return ReturnPackage;
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
大部分简单的都注释说明了，本文件的关键点在于IMPLEMENT_CLASS的分析，和上文.h中的DECLARE_CLASS对应，其声明如下：
对照着定义IMPLEMENT_CLASS(UMyClass, 899540749);
#define IMPLEMENT_CLASS(TClass, TClassCrc) \
	static TClassCompiledInDefer<TClass> AutoInitialize##TClass(TEXT(#TClass), sizeof(TClass), TClassCrc); \   //延迟注册
	UClass* TClass::GetPrivateStaticClass(const TCHAR* Package) \   //.h里声明的实现，StaticClas()内部就是调用该函数
	{ \
		static UClass* PrivateStaticClass = NULL; \ //又一次static lazy
		if (!PrivateStaticClass) \
		{ \
			/* this could be handled with templates, but we want it external to avoid code bloat */ \
			GetPrivateStaticClassBody( \    //该函数就是真正创建UClass*,以后
				Package, \  //Package名字
				(TCHAR*)TEXT(#TClass) + 1 + ((StaticClassFlags & CLASS_Deprecated) ? 11 : 0), \//类名，+1去掉U、A、F前缀，+11去掉_Deprecated前缀
				PrivateStaticClass, \   //输出引用
				StaticRegisterNatives##TClass, \
				sizeof(TClass), \
				TClass::StaticClassFlags, \
				TClass::StaticClassCastFlags(), \
				TClass::StaticConfigName(), \
				(UClass::ClassConstructorType)InternalConstructor<TClass>, \
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>, \
				&TClass::AddReferencedObjects, \
				&TClass::Super::StaticClass, \
				&TClass::WithinClass::StaticClass \
			); \
		} \
		return PrivateStaticClass; \
	}
内容也比较简单，就是把该类的信息传进去给GetPrivateStaticClassBody函数。
最后展开结果
通过人肉预处理展开一下生成的文件，应该会看得更加清楚一些：
MyClass.h展开
#pragma once
#include "UObject/NoExportTypes.h"
class HELLO_API UMyClass : public UObject
{
private:
	static void StaticRegisterNativesUMyClass();
	friend HELLO_API class UClass* Z_Construct_UClass_UMyClass();
private:
	UMyClass& operator=(UMyClass&&);
	UMyClass& operator=(const UMyClass&);
	NO_API static UClass* GetPrivateStaticClass(const TCHAR* Package);
public:
	/** Bitwise union of #EClassFlags pertaining to this class.*/
	enum {StaticClassFlags = CLASS_Intrinsic};
	/** Typedef for the base class ({{ typedef-type }}) */
	typedef UObject Super;
	/** Typedef for {{ typedef-type }}. */
	typedef UMyClass ThisClass;
	/** Returns a UClass object representing this class at runtime */
	inline static UClass* StaticClass()
	{
		return GetPrivateStaticClass(TEXT("/Script/Hello"));
	}
	/** Returns the StaticClassFlags for this class */
	inline static EClassCastFlags StaticClassCastFlags()
	{
		return 0;
	}
	DEPRECATED(4.7, "operator new has been deprecated for UObjects - please use NewObject or NewNamedObject instead")
	inline void* operator new(const size_t InSize, UObject* InOuter = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags InSetFlags = RF_NoFlags)
	{
		return StaticAllocateObject(StaticClass(), InOuter, InName, InSetFlags);
	}
	/** For internal use only; use StaticConstructObject() to create new objects. */
	inline void* operator new(const size_t InSize, EInternal InInternalOnly, UObject* InOuter = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags InSetFlags = RF_NoFlags)
	{
		return StaticAllocateObject(StaticClass(), InOuter, InName, InSetFlags);
	}
	/** For internal use only; use StaticConstructObject() to create new objects. */
	inline void* operator new(const size_t InSize, EInternal* InMem)
	{
		return (void*)InMem;
	}
	friend FArchive &operator<<(FArchive& Ar, UMyClass*& Res)
	{
		return Ar << (UObject*&)Res;
	}
	/** Indicates whether the class is compiled into the engine */
	enum { IsIntrinsic = COMPILED_IN_INTRINSIC };
	/** Standard constructor, called after all reflected properties have been initialized */
	NO_API UMyClass(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { };
private:
	/** Private move- and copy-constructors, should never be used */
	NO_API UMyClass(UMyClass&&);
	NO_API UMyClass(const UMyClass&);
public:
	static void __DefaultConstructor(const FObjectInitializer& X) { new((EInternal*)X.GetObj())UMyClass(X); }
};
Hello.generated.cpp展开
//#include "Hello.h"
#include "Engine.h"	
//#include "GeneratedCppIncludes.h"
#include "CoreUObject.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "UObject/Package.h"
#include "UObject/MetaData.h"
#include "UObject/UnrealType.h"
//#include "Hello.generated.dep.h"
#include "MyClass.h"
void EmptyLinkFunctionForGeneratedCode1Hello() {}
void UMyClass::StaticRegisterNativesUMyClass()
{
}
static TClassCompiledInDefer<UMyClass> AutoInitializeUMyClass(TEXT("UMyClass"), sizeof(UMyClass), 899540749);
UClass* UMyClass::GetPrivateStaticClass(const TCHAR* Package)
{
	static UClass* PrivateStaticClass = NULL;
	if (!PrivateStaticClass)
	{
		/* this could be handled with templates, but we want it external to avoid code bloat */
		GetPrivateStaticClassBody(
			Package,
			(TCHAR*)TEXT("UMyClass") + 1 + ((StaticClassFlags & CLASS_Deprecated) ? 11 : 0),
			PrivateStaticClass,
			StaticRegisterNativesUMyClass,
			sizeof(UMyClass),
			UMyClass::StaticClassFlags,
			UMyClass::StaticClassCastFlags(),
			UMyClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<UMyClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<UMyClass>,
			&UMyClass::AddReferencedObjects,
			&UMyClass::Super::StaticClass,
			&UMyClass::WithinClass::StaticClass
		);
	}
	return PrivateStaticClass;
}
// Cross Module References
COREUOBJECT_API class UClass* Z_Construct_UClass_UObject();
HELLO_API class UClass* Z_Construct_UClass_UMyClass_NoRegister();
HELLO_API class UClass* Z_Construct_UClass_UMyClass();
HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
UClass* Z_Construct_UClass_UMyClass_NoRegister()
{
	return UMyClass::StaticClass();
}
UClass* Z_Construct_UClass_UMyClass()
{
	static UClass* OuterClass = NULL;
	if (!OuterClass)
	{
		Z_Construct_UClass_UObject();
		Z_Construct_UPackage__Script_Hello();
		OuterClass = UMyClass::StaticClass();
		if (!(OuterClass->ClassFlags & CLASS_Constructed))
		{
			UObjectForceRegistration(OuterClass);
			OuterClass->ClassFlags |= 0x20100080;
			OuterClass->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
			MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MyClass.h"));
			MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
		}
	}
	check(OuterClass->GetClass());
	return OuterClass;
}
static FCompiledInDefer Z_CompiledInDefer_UClass_UMyClass(Z_Construct_UClass_UMyClass, &UMyClass::StaticClass, TEXT("UMyClass"), false, nullptr, nullptr, nullptr);
UPackage* Z_Construct_UPackage__Script_Hello()
{
	static UPackage* ReturnPackage = NULL;
	if (!ReturnPackage)
	{
		ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Hello")), false, false));
		ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
		FGuid Guid;
		Guid.A = 0x79A097CD;
		Guid.B = 0xB58D8B48;
		Guid.C = 0x00000000;
		Guid.D = 0x00000000;
		ReturnPackage->SetGuid(Guid);
	}
	return ReturnPackage;
}
这样.h的声明和.cpp的定义就全都有了。不管定义了多少函数，要记得注册的入口就是那两个static对象在程序启动的时候登记信息，才有了之后的注册。
UENUM的生成代码剖析
接着是相对简单的Enum，我们测试的Enum如下：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyEnum.generated.h"
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	MY_Dance 	UMETA(DisplayName = "Dance"),
	MY_Rain 	UMETA(DisplayName = "Rain"),
	MY_Song		UMETA(DisplayName = "Song")
};
生成的MyEnum.generated.h为：
PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HELLO_MyEnum_generated_h
#error "MyEnum.generated.h already included, missing '#pragma once' in MyEnum.h"
#endif
#define HELLO_MyEnum_generated_h
#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hello_Source_Hello_MyEnum_h
#define FOREACH_ENUM_EMYENUM(op) \  //定义一个遍历枚举值的宏，只是为了方便使用
	op(EMyEnum::MY_Dance) \
	op(EMyEnum::MY_Rain) \
	op(EMyEnum::MY_Song) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
因此Enum也非常简单，所以发现生成的其实也没有什么重要的信息。同样的，生成的Hello.genrated.cpp中：
#include "Hello.h"
#include "GeneratedCppIncludes.h"
#include "Hello.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Hello() {}
static class UEnum* EMyEnum_StaticEnum()    //定义一个获取UEnum便利函数，会在延迟注册的时候被用到
{
	extern HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
	static class UEnum* Singleton = NULL;
	if (!Singleton)
	{
		extern HELLO_API class UEnum* Z_Construct_UEnum_Hello_EMyEnum();
		Singleton = GetStaticEnum(Z_Construct_UEnum_Hello_EMyEnum, Z_Construct_UPackage__Script_Hello(), TEXT("EMyEnum"));
	}
	return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EMyEnum(EMyEnum_StaticEnum, TEXT("/Script/Hello"), TEXT("EMyEnum"), false, nullptr, nullptr);   //延迟注册
#if USE_COMPILED_IN_NATIVES
	HELLO_API class UEnum* Z_Construct_UEnum_Hello_EMyEnum();
	HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
	UEnum* Z_Construct_UEnum_Hello_EMyEnum()    //构造EMyEnum关联的UEnum*
	{
		UPackage* Outer=Z_Construct_UPackage__Script_Hello();
		extern uint32 Get_Z_Construct_UEnum_Hello_EMyEnum_CRC();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("EMyEnum"), 0, Get_Z_Construct_UEnum_Hello_EMyEnum_CRC(), false);
		if (!ReturnEnum)
		{
			ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EMyEnum"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());//直接创建该UEnum对象
			TArray<TPair<FName, uint8>> EnumNames;//设置枚举里的名字和值
			EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Dance")), 0));
			EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Rain")), 1));
			EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Song")), 2));
			EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_MAX")), 3));   //添加一个默认的MAX字段
			ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
			ReturnEnum->CppType = TEXT("EMyEnum");
#if WITH_METADATA   //设置元数据
			UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("MyEnum.h"));
			MetaData->SetValue(ReturnEnum, TEXT("MY_Dance.DisplayName"), TEXT("Dance"));
			MetaData->SetValue(ReturnEnum, TEXT("MY_Rain.DisplayName"), TEXT("Rain"));
			MetaData->SetValue(ReturnEnum, TEXT("MY_Song.DisplayName"), TEXT("Song"));
#endif
		}
		return ReturnEnum;
	}
	uint32 Get_Z_Construct_UEnum_Hello_EMyEnum_CRC() { return 2000113000U; }
	UPackage* Z_Construct_UPackage__Script_Hello()  //设置Hello项目的Package属性
	{
		...略
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
观察发现EMyEnum_StaticEnum其实并没有比Z_Construct_UEnum_Hello_EMyEnum实现更多的其他的功能。GetStaticEnum目前的实现内部也只是非常简单的调用Z_Construct_UEnum_Hello_EMyEnum返回结果。所以保留着这个EMyEnum_StaticEnum或许只是为了和UClass的结构保持一致。
USTRUCT的生成代码剖析
因为USTRUCT标记的类内部并不能定义函数，因此测试的Struct如下：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyStruct.generated.h"
USTRUCT(BlueprintType)
struct HELLO_API FMyStruct
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite)
	float Score;
};
生成的MyStruct.generated.h如下：
PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HELLO_MyStruct_generated_h
#error "MyStruct.generated.h already included, missing '#pragma once' in MyStruct.h"
#endif
#define HELLO_MyStruct_generated_h
#define Hello_Source_Hello_MyStruct_h_8_GENERATED_BODY \
	friend HELLO_API class UScriptStruct* Z_Construct_UScriptStruct_FMyStruct(); \  //给予全局方法友元权限
	static class UScriptStruct* StaticStruct(); //静态函数返回UScriptStruct*
#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hello_Source_Hello_MyStruct_h
PRAGMA_ENABLE_DEPRECATION_WARNINGS
同理，根据GENERATED_USTRUCT_BODY的定义，最终会替换成Hello_Source_Hello_MyStruct_h_8_GENERATED_BODY宏。我们发现其实作用只是在内部定义了一个StaticStruct函数，因为FMyStruct并不继承于UObject，所以结构也非常的简单。
再接着是Hello.genrated.cpp：
#include "Hello.h"
#include "GeneratedCppIncludes.h"
#include "Hello.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Hello() {}
class UScriptStruct* FMyStruct::StaticStruct()//实现了静态获取UScriptStruct*
{
	extern HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern HELLO_API class UScriptStruct* Z_Construct_UScriptStruct_FMyStruct();
		extern HELLO_API uint32 Get_Z_Construct_UScriptStruct_FMyStruct_CRC();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMyStruct, Z_Construct_UPackage__Script_Hello(), TEXT("MyStruct"), sizeof(FMyStruct), Get_Z_Construct_UScriptStruct_FMyStruct_CRC());
	}
	return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMyStruct(FMyStruct::StaticStruct, TEXT("/Script/Hello"), TEXT("MyStruct"), false, nullptr, nullptr);  //延迟注册
static struct FScriptStruct_Hello_StaticRegisterNativesFMyStruct
{
	FScriptStruct_Hello_StaticRegisterNativesFMyStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("MyStruct")),new UScriptStruct::TCppStructOps<FMyStruct>);
	}
} ScriptStruct_Hello_StaticRegisterNativesFMyStruct;    //static注册
#if USE_COMPILED_IN_NATIVES
	HELLO_API class UScriptStruct* Z_Construct_UScriptStruct_FMyStruct();
	HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
	UScriptStruct* Z_Construct_UScriptStruct_FMyStruct()    //构造关联的UScriptStruct*
	{
		UPackage* Outer = Z_Construct_UPackage__Script_Hello();
		extern uint32 Get_Z_Construct_UScriptStruct_FMyStruct_CRC();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("MyStruct"), sizeof(FMyStruct), Get_Z_Construct_UScriptStruct_FMyStruct_CRC(), false);
		if (!ReturnStruct)
		{
			ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("MyStruct"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FMyStruct>, EStructFlags(0x00000201));//直接创建UScriptStruct对象
			UProperty* NewProp_Score = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Score"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(Score, FMyStruct), 0x0010000000000004);//直接关联相应的Property信息
			ReturnStruct->StaticLink(); //链接
#if WITH_METADATA   //元数据
			UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
			MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("MyStruct.h"));
			MetaData->SetValue(NewProp_Score, TEXT("Category"), TEXT("MyStruct"));
			MetaData->SetValue(NewProp_Score, TEXT("ModuleRelativePath"), TEXT("MyStruct.h"));
#endif
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FMyStruct_CRC() { return 2914362188U; }
	UPackage* Z_Construct_UPackage__Script_Hello()
	{
		...略
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
同理，会发现FMyStruct::StaticStruct内部也不会比Z_Construct_UScriptStruct_FMyStruct更多的事情，GetStaticStruct的实现也只是简单的转发到Z_Construct_UScriptStruct_FMyStruct。值得一提的是定义的ScriptStruct_Hello_StaticRegisterNativesFMyStruct，会在程序一启动就调用UScriptStruct::DeferCppStructOps向程序注册该结构的CPP信息（大小，内存对齐等），和TClassCompiledInDefer<TClass>的作用相当。FMyStruct的展开也是一目了然，就不再赘述了。
UINTERFACE的生成代码剖析
UE对Interface也有支持，如果说FStruct就是一个纯数据的POD容器，那么UInterface则是一个只能带方法的纯接口，比C++里的抽象类要根据的纯粹一些。当然这里谈的都只涉及到用UPROPERTY和UFUNCTION宏标记的那些，如果是纯C++的字段和函数，UE并不能管到那么宽。
测试的MyInterface.h为：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyInterface.generated.h"
UINTERFACE(BlueprintType)
class UMyInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()    
};
class IMyInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void BPFunc() const;
};
GENERATED_UINTERFACE_BODY和GENERATED_IINTERFACE_BODY都可以替换为GENERATED_BODY以提供一个默认的UMyInterface(const FObjectInitializer& ObjectInitializer)构造函数实现。不过GENERATED_IINTERFACE_BODY替换过后的效果也一样，因为并不需要那么一个构造函数，所以用两个都可以。
生成的MyInterface.generated.h如下：
PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef HELLO_MyInterface_generated_h
#error "MyInterface.generated.h already included, missing '#pragma once' in MyInterface.h"
#endif
#define HELLO_MyInterface_generated_h
#define Hello_Source_Hello_MyInterface_h_8_RPC_WRAPPERS
#define Hello_Source_Hello_MyInterface_h_8_RPC_WRAPPERS_NO_PURE_DECLS
#define Hello_Source_Hello_MyInterface_h_8_EVENT_PARMS
extern HELLO_API  FName HELLO_BPFunc;   //函数的名称，在cpp中定义
#define Hello_Source_Hello_MyInterface_h_8_CALLBACK_WRAPPERS
#define Hello_Source_Hello_MyInterface_h_8_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyInterface) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyInterface); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyInterface); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyInterface(UMyInterface&&); \
	NO_API UMyInterface(const UMyInterface&); \
public:
#define Hello_Source_Hello_MyInterface_h_8_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyInterface(UMyInterface&&); \
	NO_API UMyInterface(const UMyInterface&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyInterface); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyInterface); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyInterface)
#undef GENERATED_UINTERFACE_BODY_COMMON
#define GENERATED_UINTERFACE_BODY_COMMON() \
	private: \
	static void StaticRegisterNativesUMyInterface(); \  //注册
	friend HELLO_API class UClass* Z_Construct_UClass_UMyInterface(); \ //构造UClass*的方法
public: \
	DECLARE_CLASS(UMyInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), 0, TEXT("/Script/Hello"), NO_API) \
	DECLARE_SERIALIZER(UMyInterface) \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};
#define Hello_Source_Hello_MyInterface_h_8_GENERATED_BODY_LEGACY \
		PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	GENERATED_UINTERFACE_BODY_COMMON() \
	Hello_Source_Hello_MyInterface_h_8_STANDARD_CONSTRUCTORS \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
#define Hello_Source_Hello_MyInterface_h_8_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	GENERATED_UINTERFACE_BODY_COMMON() \
	Hello_Source_Hello_MyInterface_h_8_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS
#define Hello_Source_Hello_MyInterface_h_8_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~IMyInterface() {} \
public: \
	typedef UMyInterface UClassType; \
	static void Execute_BPFunc(const UObject* O); \
	virtual UObject* _getUObject() const = 0;
#define Hello_Source_Hello_MyInterface_h_8_INCLASS_IINTERFACE \
protected: \
	virtual ~IMyInterface() {} \
public: \
	typedef UMyInterface UClassType; \
	static void Execute_BPFunc(const UObject* O); \
	virtual UObject* _getUObject() const = 0;
#define Hello_Source_Hello_MyInterface_h_5_PROLOG \
	Hello_Source_Hello_MyInterface_h_8_EVENT_PARMS
#define Hello_Source_Hello_MyInterface_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hello_Source_Hello_MyInterface_h_8_RPC_WRAPPERS \
	Hello_Source_Hello_MyInterface_h_8_CALLBACK_WRAPPERS \
	Hello_Source_Hello_MyInterface_h_8_INCLASS_IINTERFACE \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#define Hello_Source_Hello_MyInterface_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hello_Source_Hello_MyInterface_h_8_RPC_WRAPPERS_NO_PURE_DECLS \
	Hello_Source_Hello_MyInterface_h_8_CALLBACK_WRAPPERS \
	Hello_Source_Hello_MyInterface_h_8_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hello_Source_Hello_MyInterface_h
PRAGMA_ENABLE_DEPRECATION_WARNINGS
因为接口的定义需要用到两个类，所以生成的信息稍微繁复了一些。不过使用的时候，我们的类只是继承于IMyInterface，UMyInerface只是作为一个接口类型的载体，用以区分和查找不同的接口。观察的时候，也请注意行号的定义。
从底往上，最后两个是IMyInterface里的宏展开，细看之后，会发现_LEGACY和正常版本并没有差别。展开后是：
class IMyInterface
{
protected: 
	virtual ~IMyInterface() {}  //禁止用接口指针释放对象
public: 
	typedef UMyInterface UClassType;    //设定UMyInterface为关联的类型
	static void Execute_BPFunc(const UObject* O);   //蓝图调用的辅助函数
	virtual UObject* _getUObject() const = 0;   //
public:
	UFUNCTION(BlueprintImplementableEvent)
	void BPFunc() const;
};
再往上是UMyInterface的生成，因为UMyInterface继承于UObject的原因，所以也是从属于Object系统的一份子，所以同样需要遵循构造函数的规则。UInterface本身其实也可以算是UClass的一种，所以生成的代码跟UClass中的生成都差不多，区别是用了COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface)的不同标记。有兴趣的读者可以自己展开看下。
生成的Hello.generated.cpp：
#include "Hello.h"
#include "GeneratedCppIncludes.h"
#include "Hello.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCode1Hello() {}
FName HELLO_BPFunc = FName(TEXT("BPFunc")); //名字的定义
	void IMyInterface::BPFunc() const   //让编译通过，同时加上错误检测
	{
		check(0 && "Do not directly call Event functions in Interfaces. Call Execute_BPFunc instead.");
	}
	void UMyInterface::StaticRegisterNativesUMyInterface()
	{
	}
	IMPLEMENT_CLASS(UMyInterface, 4286549343);  //注册类
	void IMyInterface::Execute_BPFunc(const UObject* O) //蓝图调用方法的实现
	{
		check(O != NULL);
		check(O->GetClass()->ImplementsInterface(UMyInterface::StaticClass()));//检查是否实现了该接口
		UFunction* const Func = O->FindFunction(HELLO_BPFunc);  //通过名字找到方法
		if (Func)
		{
			const_cast<UObject*>(O)->ProcessEvent(Func, NULL);  //在该对象上调用该方法
		}
	}
#if USE_COMPILED_IN_NATIVES
	HELLO_API class UFunction* Z_Construct_UFunction_UMyInterface_BPFunc();
	HELLO_API class UClass* Z_Construct_UClass_UMyInterface_NoRegister();
	HELLO_API class UClass* Z_Construct_UClass_UMyInterface();
	HELLO_API class UPackage* Z_Construct_UPackage__Script_Hello();
	UFunction* Z_Construct_UFunction_UMyInterface_BPFunc()//构造BPFunc的UFunction
	{
		UObject* Outer=Z_Construct_UClass_UMyInterface();   //得到接口UMyInterface*对象
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("BPFunc"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x48020800, 65535); //直接构造函数对象
			ReturnFunction->Bind(); //绑定到函数指针
			ReturnFunction->StaticLink();   //链接
#if WITH_METADATA   //元数据
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("MyInterface.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UMyInterface_NoRegister()
	{
		return UMyInterface::StaticClass();
	}
	UClass* Z_Construct_UClass_UMyInterface()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			UInterface::StaticClass();  //确保基类UInterface已经元数据构造完成
			Z_Construct_UPackage__Script_Hello();
			OuterClass = UMyInterface::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20004081;//CLASS_Constructed|CLASS_Interface|CLASS_Native|CLASS_Abstract
				OuterClass->LinkChild(Z_Construct_UFunction_UMyInterface_BPFunc());//添加子字段
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyInterface_BPFunc(), "BPFunc"); // 1371259725 ,添加函数名字映射
				OuterClass->StaticLink();   //链接
#if WITH_METADATA   //元数据
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintType"), TEXT("true"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MyInterface.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UMyInterface(Z_Construct_UClass_UMyInterface, &UMyInterface::StaticClass, TEXT("UMyInterface"), false, nullptr, nullptr, nullptr);    //延迟注册
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMyInterface);
	UPackage* Z_Construct_UPackage__Script_Hello()
	{
		...略
	}
#endif
PRAGMA_ENABLE_DEPRECATION_WARNINGS
基本和UClass中的结构差不多，只是多了一些函数定义的过程和把函数添加到类中的操作。
UClass中的字段和函数生成代码剖析
在最开始的时候，我们用了一个最简单的UMyClass来阐述整体的结构。行百里者半九十，让我们一鼓作气，看看如果UMyClass里多了Property和Function之后又会起什么变化。
测试的MyClass.h如下：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyClass.generated.h"
UCLASS(BlueprintType)
class HELLO_API UMyClass : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	float Score;
public:
	UFUNCTION(BlueprintCallable, Category = "Hello")
	void CallableFunc();    //C++实现，蓝图调用
	UFUNCTION(BlueprintNativeEvent, Category = "Hello")
	void NativeFunc();  //C++实现默认版本，蓝图可重载实现
	UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
	void ImplementableFunc();   //C++不实现，蓝图实现
};
增加了一个属性和三个不同方法来测试。
其生成的MyClass.generated.h为(只包括改变部分)：
#define Hello_Source_Hello_MyClass_h_8_RPC_WRAPPERS \
	virtual void NativeFunc_Implementation(); \ //默认实现的函数声明，我们可以自己实现
 \
	DECLARE_FUNCTION(execNativeFunc) \  //声明供蓝图调用的函数
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->NativeFunc_Implementation(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCallableFunc) \    //声明供蓝图调用的函数
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->CallableFunc(); \
		P_NATIVE_END; \
	}
#define Hello_Source_Hello_MyClass_h_8_RPC_WRAPPERS_NO_PURE_DECLS \ //和上面重复，略
//声明函数名称
extern HELLO_API  FName HELLO_ImplementableFunc;
extern HELLO_API  FName HELLO_NativeFunc;
因为CallableFunc是C++里实现的，所以这里并不需要再定义函数体。而另外两个函数其实是在蓝图里定义的，就需要专门生成exec前缀的函数供蓝图虚拟机调用。
我们展开execCallableFunc后为：
void execCallableFunc( FFrame& Stack, void*const Z_Param__Result )  //蓝图虚拟机的使用的函数接口
{
    Stack.Code += !!Stack.Code; /* increment the code ptr unless it is null */
    { 
        FBlueprintEventTimer::FScopedNativeTimer ScopedNativeCallTimer;     //蓝图的计时统计
    	this->CallableFunc(); //调用我们自己的实现
    }
}
目前还是非常简单的，当然根据函数签名的不同会加上不同的参数传递，但是大体结构就是如此。以上的函数都是定义在UMyClass类内部的。
再来看Hello.generated.cpp里的变化（只包括改变部分）：
//函数名字定义
FName HELLO_ImplementableFunc = FName(TEXT("ImplementableFunc"));
FName HELLO_NativeFunc = FName(TEXT("NativeFunc"));
	void UMyClass::ImplementableFunc()  //C++端的实现
	{
		ProcessEvent(FindFunctionChecked(HELLO_ImplementableFunc),NULL);
	}
	void UMyClass::NativeFunc() //C++端的实现
	{
		ProcessEvent(FindFunctionChecked(HELLO_NativeFunc),NULL);
	}
	void UMyClass::StaticRegisterNativesUMyClass()  //注册函数名字和函数指针映射
	{
		FNativeFunctionRegistrar::RegisterFunction(UMyClass::StaticClass(), "CallableFunc",(Native)&UMyClass::execCallableFunc);
		FNativeFunctionRegistrar::RegisterFunction(UMyClass::StaticClass(), "NativeFunc",(Native)&UMyClass::execNativeFunc);
	}
//...略去中间相同部分
//构造3个函数的UFunction*对象，结构一样，只是EFunctionFlags不一样
UFunction* Z_Construct_UFunction_UMyClass_CallableFunc()
	{
		UObject* Outer=Z_Construct_UClass_UMyClass();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("CallableFunc"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x04020401, 65535); //FUNC_BlueprintCallable|FUNC_Public|FUNC_Native|FUNC_Final
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Hello"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UMyClass_ImplementableFunc()
	{
		UObject* Outer=Z_Construct_UClass_UMyClass();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("ImplementableFunc"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020800, 65535); //FUNC_BlueprintEvent|FUNC_Public|FUNC_Event
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Hello"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UMyClass_NativeFunc()
	{
		UObject* Outer=Z_Construct_UClass_UMyClass();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("NativeFunc"), RF_Public|RF_Transient|RF_MarkAsNative) UFunction(FObjectInitializer(), NULL, 0x08020C00, 65535);//FUNC_BlueprintEvent|FUNC_Public|FUNC_Event|FUNC_Native
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Hello"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
		}
		return ReturnFunction;
	}
//...略去中间相同部分
UClass* Z_Construct_UClass_UMyClass()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UObject();
			Z_Construct_UPackage__Script_Hello();
			OuterClass = UMyClass::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20100080;
                //添加子字段
				OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_CallableFunc());
				OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_ImplementableFunc());
				OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_NativeFunc());
PRAGMA_DISABLE_DEPRECATION_WARNINGS
				UProperty* NewProp_Score = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Score"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(Score, UMyClass), 0x0010000000000004);//添加属性
PRAGMA_ENABLE_DEPRECATION_WARNINGS
                //添加函数名字映射
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_CallableFunc(), "CallableFunc"); // 774395847
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_ImplementableFunc(), "ImplementableFunc"); // 615168156
				OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_NativeFunc(), "NativeFunc"); // 3085959641
				OuterClass->StaticLink();
#if WITH_METADATA   //元数据
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("BlueprintType"), TEXT("true"));
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MyClass.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
				MetaData->SetValue(NewProp_Score, TEXT("Category"), TEXT("MyClass"));
				MetaData->SetValue(NewProp_Score, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
可以看出，对于CallableFunc这种C++实现，蓝图只是调用的方法，生成的代码只是生成了相应的UFunction*对象。而对于NativeFunc和ImplementableFunc，我们不会在C++里写上它们的实现，因此为了编译通过，也为了可以从C++端直接调用，就需要在生成的代码的时候也同样生成一份默认实现。
在之前的简单类生成代码中，StaticRegisterNativesUMyClass总是空的，在这里UHT为它加上了把函数注册进程序内存的操作。
3个函数的UFunction*生成，虽然它们的调用方式大相径庭，但是生成的代码的方式却是结构一致的，区别的只是不同的EFunctionFlags值。因此可以推断出，更多的差异应该是在蓝图虚拟机的部分实现的，该部分知识以后介绍蓝图的时候再讨论。
最后，把1个属性和3个方法添加进UClass中，齐活收工。
总结
本篇篇幅较长，我们花了大量的叙述阐述UHT生成的代码的样式。首先从一个最简单的UMyClass开始，观察整体生成代码的结构，接着推进到UMyEnum、UMyStruct、UMyInterface的代码样式，最后返归到UMyClass在其中添加进属性和方法，观察属性和方法是怎么生成代码和怎么和UClass*对象关联起来的。其实我们也发现，这个阶段最重要的功能就是尽量的把程序的信息用代码给记录下来，对于Enum记下名字和值；对于Struct记下每个Property的名字和字节偏移；对于Interface记下每个函数或包装函数的的函数指针和名字；对于Class同理都记下Property和Function。
当然，我们现在只能涉及到一些最简单的属性和方法类型，目的是让读者们对生成的代码有个整体的概念，不要一下子陷入到了繁复的细节中去。观察生成的代码可知，其实就分两部分，一是各种Z_辅助方法用来构造出各种UClass*等对象；另一部分是都包含着一两个static对象用来在程序启动的时候驱动登记，继而调用到前者的Z_方法，最终完成注册。
在了解到了生成的代码是什么样之后，下篇，我们就将深入到这些注册的流程中去。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（五）类型系统信息收集</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/26019216
引言
前文中我们阐述了类型系统构建的第一个阶段：生成。UHT分析源码的宏标记并生成了包含程序元信息的代码，继而编译进程序，在程序启动的时候，开始启动类型系统的后续构建阶段。而本文我们将介绍类型信息的收集阶段。
C++ Static 自动注册模式
另一种常用的C++常用的设计模式：Static Auto Register。典型的，当你想要在程序启动后往一个容器里注册一些对象，或者簿记一些信息的时候，一种直接的方式是在程序启动后手动的一个个调用注册函数：
#include "ClassA.h"
#include "ClassB.h"
int main()
{
    ClassFactory::Get().Register<ClassA>();
    ClassFactory::Get().Register<ClassB>();
    [...]
}
这种方式的缺点是你必须手动的一个include之后再手动的一个个注册，当要继续添加注册的项时，只能再手动的依次序在该文件里加上一条条目，可维护性较差。
所以根据C++ static对象会在main函数之前初始化的特性，可以设计出一种static自动注册模式，新增加注册条目的时候，只要Include进相应的类.h.cpp文件，就可以自动在程序启动main函数前自动执行一些操作。简化的代码大概如下：
//StaticAutoRegister.h
template<typename TClass>
struct StaticAutoRegister
{
	StaticAutoRegister()
	{
		Register(TClass::StaticClass());
	}
};
//MyClass.h
class MyClass
{
    //[...]
};
//MyClass.cpp
#include "StaticAutoRegister.h"
const static StaticAutoRegister<MyClass> AutoRegister;
这样，在程序启动的时候就会执行Register(MyClass)，把因为新添加类而产生的改变行为限制在了新文件本身，对于一些顺序无关的注册行为这种模式尤为合适。利用这个static初始化特性，也有很多个变种，比如你可以把StaticAutoRegister声明进MyClass的一个静态成员变量也可以。不过注意的是，这种模式只能在独立的地址空间才能有效，如果该文件被静态链接且没有被引用到的话则很可能会绕过static的初始化。不过UE因为都是dll动态链接，且没有出现静态lib再引用Lib，然后又不引用文件的情况出现，所以避免了该问题。或者你也可以找个地方强制的去include一下来触发static初始化。
UE Static 自动注册模式
而UE里同样是采用这种模式：
template <typename TClass>
struct TClassCompiledInDefer : public FFieldCompiledInInfo
{
	TClassCompiledInDefer(const TCHAR* InName, SIZE_T InClassSize, uint32 InCrc)
	: FFieldCompiledInInfo(InClassSize, InCrc)
	{
		UClassCompiledInDefer(this, InName, InClassSize, InCrc);
	}
	virtual UClass* Register() const override
	{
		return TClass::StaticClass();
	}
};
static TClassCompiledInDefer<TClass> AutoInitialize##TClass(TEXT(#TClass), sizeof(TClass), TClassCrc); 
或者
struct FCompiledInDefer
{
	FCompiledInDefer(class UClass *(*InRegister)(), class UClass *(*InStaticClass)(), const TCHAR* Name, bool bDynamic, const TCHAR* DynamicPackageName = nullptr, const TCHAR* DynamicPathName = nullptr, void (*InInitSearchableValues)(TMap<FName, FName>&) = nullptr)
	{
		if (bDynamic)
		{
			GetConvertedDynamicPackageNameToTypeName().Add(FName(DynamicPackageName), FName(Name));
		}
		UObjectCompiledInDefer(InRegister, InStaticClass, Name, bDynamic, DynamicPathName, InInitSearchableValues);
	}
};
static FCompiledInDefer Z_CompiledInDefer_UClass_UMyClass(Z_Construct_UClass_UMyClass, &UMyClass::StaticClass, TEXT("UMyClass"), false, nullptr, nullptr, nullptr);
都是对该模式的应用，把static变量声明再用宏包装一层，就可以实现一个简单的自动注册流程了。
收集
在上文里，我们详细介绍了Class、Struct、Enum、Interface的代码生成的信息，显然的，生成的就是为了拿过来用的。但是在用之前，我们就还得辛苦一番，把散乱分布在各个.h.cpp文件里的元数据都收集到我们想要的数据结构里保存，以便下一个阶段的使用。
这里回顾一下，为了让新创建的类不修改既有的代码，所以我们选择了去中心化的为每个新的类生成它自己的cpp生成文件——上文里已经分别介绍每个cpp文件的内容。但是这样我们就接着迎来了一个新问题：这些cpp文件里的元数据散乱在各个模块dll里，我们需要用一种方法重新归拢这些数据，这就是我们在一开头就提到的C++ Static自动注册模式了。通过这种模式，每个cpp文件里的static对象在程序一开始的时候就会全部有机会去做一些事情，包括信息的收集工作。
UE4里也是如此，在程序启动的时候，UE利用了Static自动注册模式把所有类的信息都一一登记一遍。而紧接着另一个就是顺序问题了，这么多类，谁先谁后，互相若是有依赖该怎么解决。众所周知，UE是以Module来组织引擎结构的（关于Module的细节会在以后章节叙述），一个个Module可以通过脚本配置来选择性的编译加载。在游戏引擎众多的模块中，玩家自己的Game模块是处于比较高级的层次的，都是依赖于引擎其他更基础底层的模块，而这些模块中，最最底层的就是Core模块（C++的基础库），接着就是CoreUObject，正是实现Object类型系统的模块！因此在类型系统注册的过程中，不止要注册玩家的Game模块，同时也要注册CoreUObject本身的一些支持类。
很多人可能会担心这么多模块的静态初始化的顺序正确性如何保证，在c++标准里，不同编译单元的全局静态变量的初始化顺序并没有明确规定，因此实现上完全由编译器自己决定。该问题最好的解决方法是尽可能的避免这种情况，在设计上就让各个变量不互相引用依赖，同时也采用一些二次检测的方式避免重复注册，或者触发一个强制引用来保证前置对象已经被初始化完成。目前在MSVC平台上是先注册玩家的Game模块，接着是CoreUObject，接着再其他，不过这其实无所谓的，只要保证不依赖顺序而结果正确，顺序就并不重要了。
Static的收集
在讲完了收集的必要性和顺序问题的解决之后，我们再来分别的看各个类别的结构的信息的收集。依然是按照上文生成的顺序，从Class（Interface同理）开始，然后是Enum，接着Struct。接着请读者朋友们对照着上文的生成代码来理解。
Class的收集
对照着上文里的Hello.generated.cpp展开，我们注意到里面有：
static TClassCompiledInDefer<UMyClass> AutoInitializeUMyClass(TEXT("UMyClass"), sizeof(UMyClass), 899540749);
//……
static FCompiledInDefer Z_CompiledInDefer_UClass_UMyClass(Z_Construct_UClass_UMyClass, &UMyClass::StaticClass, TEXT("UMyClass"), false, nullptr, nullptr, nullptr);
再一次找到其定义：
//Specialized version of the deferred class registration structure.
template <typename TClass>
struct TClassCompiledInDefer : public FFieldCompiledInInfo
{
	TClassCompiledInDefer(const TCHAR* InName, SIZE_T InClassSize, uint32 InCrc)
	: FFieldCompiledInInfo(InClassSize, InCrc)
	{
		UClassCompiledInDefer(this, InName, InClassSize, InCrc);    //收集信息
	}
	virtual UClass* Register() const override
	{
		return TClass::StaticClass();
	}
};
//Stashes the singleton function that builds a compiled in class. Later, this is executed.
struct FCompiledInDefer
{
	FCompiledInDefer(class UClass *(*InRegister)(), class UClass *(*InStaticClass)(), const TCHAR* Name, bool bDynamic, const TCHAR* DynamicPackageName = nullptr, const TCHAR* DynamicPathName = nullptr, void (*InInitSearchableValues)(TMap<FName, FName>&) = nullptr)
	{
		if (bDynamic)
		{
			GetConvertedDynamicPackageNameToTypeName().Add(FName(DynamicPackageName), FName(Name));
		}
		UObjectCompiledInDefer(InRegister, InStaticClass, Name, bDynamic, DynamicPathName, InInitSearchableValues);//收集信息
	}
};
可以见到前者调用了UClassCompiledInDefer来收集类名字，类大小，CRC信息，并把自己的指针保存进来以便后续调用Register方法。而UObjectCompiledInDefer（现在暂时不考虑动态类）最重要的收集的信息就是第一个用于构造UClass*对象的函数指针回调。
再往下我们会发现这二者其实都只是在一个静态Array里添加信息记录：
void UClassCompiledInDefer(FFieldCompiledInInfo* ClassInfo, const TCHAR* Name, SIZE_T ClassSize, uint32 Crc)
{
    //...
    // We will either create a new class or update the static class pointer of the existing one
	GetDeferredClassRegistration().Add(ClassInfo);  //static TArray<FFieldCompiledInInfo*> DeferredClassRegistration;
}
void UObjectCompiledInDefer(UClass *(*InRegister)(), UClass *(*InStaticClass)(), const TCHAR* Name, bool bDynamic, const TCHAR* DynamicPathName, void (*InInitSearchableValues)(TMap<FName, FName>&))
{
    //...
	GetDeferredCompiledInRegistration().Add(InRegister);    //static TArray<class UClass *(*)()> DeferredCompiledInRegistration;
}
而在整个引擎里会触发此Class的信息收集的有UCLASS、UINTERFACE、IMPLEMENT_INTRINSIC_CLASS、IMPLEMENT_CORE_INTRINSIC_CLASS，其中UCLASS和UINTERFACE我们上文已经见识过了，而IMPLEMENT_INTRINSIC_CLASS是用于在代码中包装UModel，IMPLEMENT_CORE_INTRINSIC_CLASS是用于包装UField、UClass等引擎内建的类，后两者内部也都调用了IMPLEMENT_CLASS来实现功能。
流程图如下：
思考：为何需要TClassCompiledInDefer和FCompiledInDefer两个静态初始化来登记？
我们也观察到了这二者是一一对应的，问题是为何需要两个静态对象来分别收集，为何不合二为一？关键在于我们首先要明白它们二者的不同之处，前者的目的主要是为后续提供一个TClass::StaticClass的Register方法（其会触发GetPrivateStaticClassBody的调用，进而创建出UClass*对象），而后者的目的是在其UClass*身上继续调用构造函数，初始化属性和函数等一些注册操作。我们可以简单理解为就像是C++中new对象的两个步骤，首先分配内存，继而在该内存上构造对象。我们在后续的注册章节里还会继续讨论到这个问题。
思考：为何需要延迟注册而不是直接在static回调里执行？
很多人可能会问，为什么static回调里都是先把信息注册进array结构里，并没有什么其他操作，为何不直接把后续的操作直接在回调里调用了，这样结构反而简单些。是这样没错，但是同时我们也考虑到一个问题，UE4里大概1500多个类，如果都在static初始化阶段进行1500多个类的收集注册操作，那么main函数必须得等好一会儿才能开始执行。表现上就是用户双击了程序，没反应，过了好一会儿，窗口才打开。因此static初始化回调里尽量少的做事情，就是为了尽快的加快程序启动的速度。等窗口显示出来了，array结构里数据已经有了，我们就可以施展手脚，多线程也好，延迟也好，都可以大大改善程序运行的体验。
Enum的收集
依旧是上文里的对照代码，UENUM会生成：
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_EMyEnum(EMyEnum_StaticEnum, TEXT("/Script/Hello"), TEXT("EMyEnum"), false, nullptr, nullptr);
//其定义：
struct FCompiledInDeferEnum
{
	FCompiledInDeferEnum(class UEnum *(*InRegister)(), const TCHAR* PackageName, const TCHAR* Name, bool bDynamic, const TCHAR* DynamicPackageName, const TCHAR* DynamicPathName)
	{
		if (bDynamic)
		{
			GetConvertedDynamicPackageNameToTypeName().Add(FName(DynamicPackageName), FName(Name));
		}
		UObjectCompiledInDeferEnum(InRegister, PackageName, DynamicPathName, bDynamic);
		//	static TArray<FPendingEnumRegistrant> DeferredCompiledInRegistration;
	}
};
在static阶段会向内存注册一个构造UEnum*的函数指针用于回调：
注意到这里并不需要像UClassCompiledInDefer一样先生成一个UClass*，因为UEnum并不是一个Class，并没有Class那么多功能集合，所以就比较简单一些。
Struct的收集
对于Struct，我们先来看上篇里生成的代码：
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMyStruct(FMyStruct::StaticStruct, TEXT("/Script/Hello"), TEXT("MyStruct"), false, nullptr, nullptr);  //延迟注册
static struct FScriptStruct_Hello_StaticRegisterNativesFMyStruct
{
    FScriptStruct_Hello_StaticRegisterNativesFMyStruct()
    {
        UScriptStruct::DeferCppStructOps(FName(TEXT("MyStruct")),new UScriptStruct::TCppStructOps<FMyStruct>);
    }
} ScriptStruct_Hello_StaticRegisterNativesFMyStruct;    //static注册
同样是两个static对象，前者FCompiledInDeferStruct继续向array结构里登记函数指针，后者有点特殊，在一个结构名和对象的Map映射里登记“Struct相应的C++操作类”（后续解释）。
struct FCompiledInDeferStruct
{
	FCompiledInDeferStruct(class UScriptStruct *(*InRegister)(), const TCHAR* PackageName, const TCHAR* Name, bool bDynamic, const TCHAR* DynamicPackageName, const TCHAR* DynamicPathName)
	{
		if (bDynamic)
		{
			GetConvertedDynamicPackageNameToTypeName().Add(FName(DynamicPackageName), FName(Name));
		}
		UObjectCompiledInDeferStruct(InRegister, PackageName, DynamicPathName, bDynamic);//	static TArray<FPendingStructRegistrant> DeferredCompiledInRegistration;
	}
};
void UScriptStruct::DeferCppStructOps(FName Target, ICppStructOps* InCppStructOps)
{
	TMap<FName,UScriptStruct::ICppStructOps*>& DeferredStructOps = GetDeferredCppStructOps();
	if (UScriptStruct::ICppStructOps* ExistingOps = DeferredStructOps.FindRef(Target))
	{
#if WITH_HOT_RELOAD
		if (!GIsHotReload) // in hot reload, we will just leak these...they may be in use.
#endif
		{
			check(ExistingOps != InCppStructOps); // if it was equal, then we would be re-adding a now stale pointer to the map
			delete ExistingOps;
		}
	}
	DeferredStructOps.Add(Target,InCppStructOps);
}
另外的，搜罗引擎里的代码，我们还会发现对于UE4里内建的结构，比如说Vector，其IMPLEMENT_STRUCT(Vector)也会相应的触发DeferCppStructOps的调用。
这里的Struct也和Enum同理，因为并不是一个Class，所以并不需要比较繁琐的两步构造，凭着FPendingStructRegistrant就可以后续一步构造出UScriptStruct*对象；对于内建的类型（如Vector），因其完全不是“Script”的类型，所以就不需要UScriptStruct的构建，那么其如何像BP暴露，我们后续再详细介绍。
还有一点注意的是UStruct类型会配套一个ICppStructOps接口对象来管理C++struct对象的构造和析构工作，其用意就在于如果对于一块已经擦除了类型的内存数据，我们怎么能在其上正确的构造结构对象数据或者析构。这个时候，如果我们能够得到一个统一的ICppStructOps*指针指向类型安全的TCppStructOps<CPPSTRUCT>对象，就能够通过接口函数动态、多态、类型安全的执行构造和析构工作。
Function的收集
在介绍完了Class、Enum、Struct之后，我们还遗忘了一些引擎内建的函数的信息收集。我们在前文中并没有介绍到这一点是因为UE已经提供了我们一个BlueprintFunctionLibrary的类来注册全局函数。而一些引擎内部定义出来的函数，也是散乱分布在各处，也是需要收集起来的。
主要有这两类：
IMPLEMENT_CAST_FUNCTION，定义一些Object的转换函数
IMPLEMENT_CAST_FUNCTION( UObject, CST_ObjectToBool, execObjectToBool );
IMPLEMENT_CAST_FUNCTION( UObject, CST_InterfaceToBool, execInterfaceToBool );
IMPLEMENT_CAST_FUNCTION( UObject, CST_ObjectToInterface, execObjectToInterface );
IMPLEMENT_VM_FUNCTION，定义一些蓝图虚拟机使用的函数
IMPLEMENT_VM_FUNCTION(EX_CallMath, execCallMathFunction);
IMPLEMENT_VM_FUNCTION( EX_True, execTrue );
//……
而继而查其定义：
#define IMPLEMENT_FUNCTION(cls,func) \
	static FNativeFunctionRegistrar cls##func##Registar(cls::StaticClass(),#func,(Native)&cls::func);
#define IMPLEMENT_CAST_FUNCTION(cls, CastIndex, func) \
	IMPLEMENT_FUNCTION(cls, func); \
	static uint8 cls##func##CastTemp = GRegisterCast( CastIndex, (Native)&cls::func );
#define IMPLEMENT_VM_FUNCTION(BytecodeIndex, func) \
	IMPLEMENT_FUNCTION(UObject, func) \
	static uint8 UObject##func##BytecodeTemp = GRegisterNative( BytecodeIndex, (Native)&UObject::func );
/** A struct that maps a string name to a native function */
struct FNativeFunctionRegistrar
{
	FNativeFunctionRegistrar(class UClass* Class, const ANSICHAR* InName, Native InPointer)
	{
		RegisterFunction(Class, InName, InPointer);
	}
	static COREUOBJECT_API void RegisterFunction(class UClass* Class, const ANSICHAR* InName, Native InPointer);
	// overload for types generated from blueprints, which can have unicode names:
	static COREUOBJECT_API void RegisterFunction(class UClass* Class, const WIDECHAR* InName, Native InPointer);
};
也可以发现有3个static对象收集到这些函数的信息并登记到相应的结构中去，流程图为：
其中FNativeFunctionRegistrar用于向UClass里添加Native函数（区别于蓝图里定义的函数），另一个方面，在UClass的RegisterNativeFunc相关函数里，也会把相应的Class内定义的函数添加到UClass内部的函数表里去。
UObject的收集
如果读者朋友们自己剖析源码，还会有一个疑惑，作为Object系统的根类，它是怎么在最开始的时候触发相应UClass*的生成呢？答案在最开始的IMPLEMENT_VM_FUNCTION(EX_CallMath, execCallMathFunction)调用上，其内部会紧接着触发UObject::StaticClass()的调用，作为最开始的调用，检测到UClass*并未生成，于是接着会转发到GetPrivateStaticClassBody中去生成一个UClass*。
总结
因篇幅有限，本文紧接着上文，讨论了代码生成的信息是如何一步步收集到内存里的数据结构里去的，UE4利用了C++的static对象初始化模式，在程序最初启动的时候，main之前，就收集到了所有的类型元数据、函数指针回调、名字、CRC等信息。到目前，思路还是很清晰的，为每一个类代码生成自己的cpp文件（不需中心化的修改既有代码），进而在其生成的每个cpp文件里用static模式搜罗一遍信息以便后续的使用。这也算是C++自己实现类型系统流行套路之一吧。
在下一个阶段——注册，我们将讨论UE4接下来是如何消费利用这些信息的。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（六）类型系统代码生成重构-UE4CodeGen_Private</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/34059049
引言
在之前的《InsideUE4》UObject（四）类型系统代码生成和《InsideUE4》UObject（五）类型系统收集章节里，我们介绍了UE4是如何根据我们的代码和元标记生成反射代码，并在Main函数调用之前，利用静态变量的初始化来收集类型的元数据信息。经过了我这么长时间的拖更……也经过了Epic这么长时间的版本更替，把UE从4.15.1进化到了4.18.3，自然的，CoreUObject模块也进行了一些改进。本文就先补上一个关于代码生成的改进：在UE4.17（20170722）的时候进行的UObjectGlobals.h.cpp重构，优化了代码生成的内容和组织形式。
旧版本代码生成
首先来看一下之前的版本的代码元数据生成：
UEnum的生成：
//测试代码
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyEnum.generated.h"
UENUM(BlueprintType)
enum class EMyEnum : uint8
{
    MY_Dance    UMETA(DisplayName = "Dance"),
    MY_Rain     UMETA(DisplayName = "Rain"),
    MY_Song     UMETA(DisplayName = "Song")
};
//生成代码节选(Hello.genrated.cpp)：
ReturnEnum = new(EC_InternalUseOnlyConstructor, Outer, TEXT("EMyEnum"), RF_Public|RF_Transient|RF_MarkAsNative) UEnum(FObjectInitializer());//直接创建该UEnum对象
TArray<TPair<FName, uint8>> EnumNames;//设置枚举里的名字和值
EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Dance")), 0));
EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Rain")), 1));
EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_Song")), 2));
EnumNames.Add(TPairInitializer<FName, uint8>(FName(TEXT("EMyEnum::MY_MAX")), 3));   //添加一个默认的MAX字段
ReturnEnum->SetEnums(EnumNames, UEnum::ECppForm::EnumClass);
ReturnEnum->CppType = TEXT("EMyEnum");
#if WITH_METADATA   //设置元数据
UMetaData* MetaData = ReturnEnum->GetOutermost()->GetMetaData();
MetaData->SetValue(ReturnEnum, TEXT("BlueprintType"), TEXT("true"));
MetaData->SetValue(ReturnEnum, TEXT("ModuleRelativePath"), TEXT("MyEnum.h"));
MetaData->SetValue(ReturnEnum, TEXT("MY_Dance.DisplayName"), TEXT("Dance"));
MetaData->SetValue(ReturnEnum, TEXT("MY_Rain.DisplayName"), TEXT("Rain"));
MetaData->SetValue(ReturnEnum, TEXT("MY_Song.DisplayName"), TEXT("Song"));
#endif
UStruct的生成：
//测试代码：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyStruct.generated.h"
USTRUCT(BlueprintType)
struct HELLO_API FMyStruct
{
    GENERATED_USTRUCT_BODY()
    UPROPERTY(BlueprintReadWrite)
    float Score;
};
//生成代码节选(Hello.genrated.cpp)：
ReturnStruct = new(EC_InternalUseOnlyConstructor, Outer, TEXT("MyStruct"), RF_Public|RF_Transient|RF_MarkAsNative) UScriptStruct(FObjectInitializer(), NULL, new UScriptStruct::TCppStructOps<FMyStruct>, EStructFlags(0x00000201));//直接创建UScriptStruct对象
UProperty* NewProp_Score = new(EC_InternalUseOnlyConstructor, ReturnStruct, TEXT("Score"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(Score, FMyStruct), 0x0010000000000004);//直接关联相应的Property信息
ReturnStruct->StaticLink(); //链接
#if WITH_METADATA   //元数据
UMetaData* MetaData = ReturnStruct->GetOutermost()->GetMetaData();
MetaData->SetValue(ReturnStruct, TEXT("BlueprintType"), TEXT("true"));
MetaData->SetValue(ReturnStruct, TEXT("ModuleRelativePath"), TEXT("MyStruct.h"));
MetaData->SetValue(NewProp_Score, TEXT("Category"), TEXT("MyStruct"));
MetaData->SetValue(NewProp_Score, TEXT("ModuleRelativePath"), TEXT("MyStruct.h"));
#endif
UClass的生成：
//测试代码：
#pragma once
#include "UObject/NoExportTypes.h"
#include "MyClass.generated.h"
UCLASS(BlueprintType)
class HELLO_API UMyClass : public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    float Score;
public:
    UFUNCTION(BlueprintCallable, Category = "Hello")
    void CallableFunc();    //C++实现，蓝图调用
    UFUNCTION(BlueprintNativeEvent, Category = "Hello")
    void NativeFunc();  //C++实现默认版本，蓝图可重载实现
    UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
    void ImplementableFunc();   //C++不实现，蓝图实现
};
//生成代码节选(Hello.genrated.cpp)：
//添加子字段
OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_CallableFunc());
OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_ImplementableFunc());
OuterClass->LinkChild(Z_Construct_UFunction_UMyClass_NativeFunc());
PRAGMA_DISABLE_DEPRECATION_WARNINGS
UProperty* NewProp_Score = new(EC_InternalUseOnlyConstructor, OuterClass, TEXT("Score"), RF_Public|RF_Transient|RF_MarkAsNative) UFloatProperty(CPP_PROPERTY_BASE(Score, UMyClass), 0x0010000000000004);//添加属性
PRAGMA_ENABLE_DEPRECATION_WARNINGS
//添加函数名字映射
OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_CallableFunc(), "CallableFunc"); // 774395847
OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_ImplementableFunc(), "ImplementableFunc"); // 615168156
OuterClass->AddFunctionToFunctionMapWithOverriddenName(Z_Construct_UFunction_UMyClass_NativeFunc(), "NativeFunc"); // 3085959641
OuterClass->StaticLink();
#if WITH_METADATA   //元数据
UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
MetaData->SetValue(OuterClass, TEXT("BlueprintType"), TEXT("true"));
MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("MyClass.h"));
MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
MetaData->SetValue(NewProp_Score, TEXT("Category"), TEXT("MyClass"));
MetaData->SetValue(NewProp_Score, TEXT("ModuleRelativePath"), TEXT("MyClass.h"));
#endif
可以见到，以往的方式在生成的代码里有很多的“套路化”的SetValue、Add段落，都是用来添加字段属性、函数和元数据的信息。虽然这些代码也是UHT程序化生成的，不用人手工操作，看起来也只能说是略有瑕疵，但要是从精益求精的角度上来说，缺点有：
本着DRY(Don't Repeat Yourself)原则，这些模式化的代码在每一个反射文件里也都会重复N次，增大了代码的体积。
代码文件的膨胀，自然会增加编译的时间消耗。
即使是程序生成的代码，有时也难免要阅读Debug，大量的模式代码噪音显然降低了关键代码的可读性和课调试性。
UHT的编写维护，更多的代码量生成，自然会带来UHT工具代码的编写量增长，增大了编写维护的成本；代码越多，Bug越多；UHT要输出更多的代码，自然效率会降低，从而导致总编译时间的消耗增长。
UE4CodeGen_Private
改善方式是显然易得的，同一件事不要做两遍。既然到处都是这些胶水代码，那就把这些代码封装成函数；既然到处都散布着这些元数据信息数据，那就把这些数据封装成结构作为函数的参数。
所以，UE在4.17的时候，在UObjectGlobals.h.cpp里增加了一个UE4CodeGen_Private的命名空间，里面添加了一些生成函数：
//UObjectGlobals.h
namespace UE4CodeGen_Private
{
    COREUOBJECT_API void ConstructUFunction(UFunction*& OutFunction, const FFunctionParams& Params);
    COREUOBJECT_API void ConstructUEnum(UEnum*& OutEnum, const FEnumParams& Params);
    COREUOBJECT_API void ConstructUScriptStruct(UScriptStruct*& OutStruct, const FStructParams& Params);
    COREUOBJECT_API void ConstructUPackage(UPackage*& OutPackage, const FPackageParams& Params);
    COREUOBJECT_API void ConstructUClass(UClass*& OutClass, const FClassParams& Params);
}
//UObjectGlobals.cpp
namespace UE4CodeGen_Private
{
    void ConstructUProperty(UObject* Outer, const FPropertyParamsBase* const*& PropertyArray, int32& NumProperties);
    void AddMetaData(UObject* Object, const FMetaDataPairParam* MetaDataArray, int32 NumMetaData);
}
函数的名字含义显而易见，都是用来构造一些元数据结构：UEnum、UFunction、UProperty、UScriptStruct、UClass、UPackage和添加一些元数据（这些结构后续会详解）。第一个参数都是指针的引用，所以是用来向外构造一个对象用指针返回的；关键的是在第二个参数：都是一个个XXXParams参数，用来传进去信息的。
所以我们继续查看这些参数信息：
UEnum的Params和生成：
//UObjectGlobals.h
namespace UE4CodeGen_Private
{
#if WITH_METADATA   //只有在编辑器模式下，才保留元数据信息
    struct FMetaDataPairParam   //元数据对
    {
        //例：MetaData->SetValue(ReturnEnum, TEXT("MY_Song.DisplayName"), TEXT("Song"));
        const char* NameUTF8;   //元数据的键值对信息
        const char* ValueUTF8;
    };
#endif
    struct FEnumeratorParam     //枚举项
    {
        const char*               NameUTF8; //枚举项的名字
        int64                     Value;    //枚举项的值
#if WITH_METADATA
        const FMetaDataPairParam* MetaDataArray;    //一个枚举项依然可以包含多个元数据键值对
        int32                     NumMetaData;
#endif
    };
    struct FEnumParams  //枚举参数
    {
        UObject*                  (*OuterFunc)();   //获取Outer对象的函数指针回调，用于获取所属于的Package
        EDynamicType                DynamicType;    //是否动态，一般是非动态的
        const char*                 NameUTF8;   //枚举的名字
        EObjectFlags                ObjectFlags;    //UEnum对象的标志
        FText                     (*DisplayNameFunc)(int32);    //获取自定义显示名字的回调，一般是nullptr，就是默认规则生成的名字
        uint8                       CppForm; 
        /*CppForm指定这个枚举是怎么定义的，用来在之后做更细的处理。
        enum class ECppForm
        {
            Regular,    //常规的enum MyEnum{}这样定义
            Namespaced, //MyEnum之外套一层namespace的定义
            EnumClass   //enum class定义的
        };
        */
        const char*                 CppTypeUTF8;    //C++里的类型名字，一般是等同于NameUTF8的，但有时定义名字和反射的名字可以不一样
        const FEnumeratorParam*     EnumeratorParams;   //枚举项数组
        int32                       NumEnumerators;
#if WITH_METADATA
        const FMetaDataPairParam*   MetaDataArray;  //元数据数组
        int32                       NumMetaData;
#endif
    };
}
//MyEnum.gen.cpp生成代码：
static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = { //所有的枚举项
            { "MyEnum::MY_Dance", (int64)MyEnum::MY_Dance },
            { "MyEnum::MY_Rain", (int64)MyEnum::MY_Rain },
            { "MyEnum::MY_Song", (int64)MyEnum::MY_Song },
        };
#if WITH_METADATA
static const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {   //枚举的元数据
    { "BlueprintType", "true" },
    { "IsBlueprintBase", "true" },
    { "ModuleRelativePath", "MyEnum.h" },
    { "MY_Dance.DisplayName", "Dance" },
    { "MY_Rain.DisplayName", "Rain" },
    { "MY_Song.DisplayName", "Song" },
};
#endif
static const UE4CodeGen_Private::FEnumParams EnumParams = { //枚举的元数据参数信息
    (UObject*(*)())Z_Construct_UPackage__Script_Hello,
    UE4CodeGen_Private::EDynamicType::NotDynamic,
    "MyEnum",
    RF_Public|RF_Transient|RF_MarkAsNative,
    nullptr,
    (uint8)UEnum::ECppForm::EnumClass,
    "MyEnum",
    Enumerators, //枚举项数组
    ARRAY_COUNT(Enumerators),  
    METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))//枚举元数据数组
};
UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams); //利用枚举参数构造UEnum*对象到ReturnEnum
先挑最软的椰子开始捏，枚举的构造比较简单，就只是包含枚举项（字符串-整形)，所以只要依次添加进去就可以。元数据对指的就是那些UMETA等宏标记里面那些的内容，可以在很多地方上使用来添加额外的信息。
UStruct的Params和生成：
因为UStruct里只能包含属性，所以我们在这里着重关注属性信息是怎么生成的。
//UObjectGlobals.h
//PS:为了阅读方便，与源码有一定的代码位置微调，但不影响功能正确性
namespace UE4CodeGen_Private
{
    enum class EPropertyClass   //属性的类型
    {
        Byte,
        Int8,
        Int16,
        Int,
        Int64,
        UInt16,
        UInt32,
        UInt64,
        UnsizedInt,
        UnsizedUInt,
        Float,
        Double,
        Bool,
        SoftClass,
        WeakObject,
        LazyObject,
        SoftObject,
        Class,
        Object,
        Interface,
        Name,
        Str,
        Array,
        Map,
        Set,
        Struct,
        Delegate,
        MulticastDelegate,
        Text,
        Enum,
    };
    // This is not a base class but is just a common initial sequence of all of the F*PropertyParams types below.
    // We don't want to use actual inheritance because we want to construct aggregated compile-time tables of these things.
    struct FPropertyParamsBase  //属性参数基类
    {
        EPropertyClass Type;    //属性的类型
        const char*    NameUTF8;     //属性的名字
        EObjectFlags   ObjectFlags;  //属性生成的UProperty对象标志，标识这个UProperty对象的特征，RF_XXX那些宏
        uint64         PropertyFlags;    //属性生成的UProperty属性标志，标识这个属性的特征，CPF_XXX那些宏
        int32          ArrayDim;        //属性有可能是个数组，数组的长度，默认是1
        const char*    RepNotifyFuncUTF8;   //属性的网络复制通知函数名字
    };
    struct FPropertyParamsBaseWithOffset // : FPropertyParamsBase
    {
        EPropertyClass Type;
        const char*    NameUTF8;
        EObjectFlags   ObjectFlags;
        uint64         PropertyFlags;
        int32          ArrayDim;
        const char*    RepNotifyFuncUTF8;
        int32          Offset;  //在结构或类中的内存偏移，可以理解为成员变量指针（成员变量指针其实本质上就是从对象内存起始位置的偏移）
    };
    //通用的属性参数
    struct FGenericPropertyParams // : FPropertyParamsBaseWithOffset
    {
        EPropertyClass   Type;
        const char*      NameUTF8;
        EObjectFlags     ObjectFlags;
        uint64           PropertyFlags;
        int32            ArrayDim;
        const char*      RepNotifyFuncUTF8;
        int32            Offset;
#if WITH_METADATA
        const FMetaDataPairParam*           MetaDataArray;
        int32                               NumMetaData;
#endif
    };
    //一些普通常用的数值类型就通过这个类型定义别名了
    // These property types don't add new any construction parameters to their base property
    typedef FGenericPropertyParams FInt8PropertyParams;
    typedef FGenericPropertyParams FInt16PropertyParams;
    //枚举类型属性参数
    struct FBytePropertyParams // : FPropertyParamsBaseWithOffset
    {
        EPropertyClass   Type;
        const char*      NameUTF8;
        EObjectFlags     ObjectFlags;
        uint64           PropertyFlags;
        int32            ArrayDim;
        const char*      RepNotifyFuncUTF8;
        int32            Offset;
        UEnum*         (*EnumFunc)();   //定义的枚举对象回调
#if WITH_METADATA
        const FMetaDataPairParam*           MetaDataArray;
        int32                               NumMetaData;
#endif
    };
    //...省略一些定义，可自行去UObjectGlobals.h查看
    //对象引用类型属性参数
    struct FObjectPropertyParams // : FPropertyParamsBaseWithOffset
    {
        EPropertyClass   Type;
        const char*      NameUTF8;
        EObjectFlags     ObjectFlags;
        uint64           PropertyFlags;
        int32            ArrayDim;
        const char*      RepNotifyFuncUTF8;
        int32            Offset;
        UClass*        (*ClassFunc)();  //用于获取该属性定义类型的函数指针回调
#if WITH_METADATA
        const FMetaDataPairParam*           MetaDataArray;
        int32                               NumMetaData;
#endif
    };
    struct FStructParams    //结构参数
    {
        UObject*                          (*OuterFunc)();   //所属于的Package
        UScriptStruct*                    (*SuperFunc)();   //该结构的基类，没有的话为nullptr
        void*                             (*StructOpsFunc)(); // really returns UScriptStruct::ICppStructOps*，结构的构造分配的辅助操作类
        const char*                         NameUTF8;   //结构名字
        EObjectFlags                        ObjectFlags;    //结构UScriptStruct*的对象特征
        uint32                              StructFlags; // EStructFlags该结构的本来特征
        SIZE_T                              SizeOf;     //结构的大小，就是sizeof(FMyStruct)，用以后续分配内存时候用
        SIZE_T                              AlignOf;//结构的内存对齐，就是alignof(FMyStruct)，用以后续分配内存时候用
        const FPropertyParamsBase* const*   PropertyArray;  //包含的属性数组
        int32                               NumProperties;
    #if WITH_METADATA
        const FMetaDataPairParam*           MetaDataArray;  //元数据数组
        int32                               NumMetaData;
    #endif
    };
}
//MyStruct.gen.cpp生成代码：
#if WITH_METADATA
static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = { //结构的元数据
    { "BlueprintType", "true" },
    { "ModuleRelativePath", "MyStruct.h" },
};
#endif
auto NewStructOpsLambda = []() -> void* { return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMyStruct>(); };   //一个获取操作类的回调
#if WITH_METADATA
//属性的元数据
static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Score_MetaData[] = {
    { "Category", "MyStruct" },
    { "ModuleRelativePath", "MyStruct.h" },
};
#endif
static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Score = { UE4CodeGen_Private::EPropertyClass::Float, "Score", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000004, 1, nullptr, STRUCT_OFFSET(FMyStruct, Score), METADATA_PARAMS(NewProp_Score_MetaData, ARRAY_COUNT(NewProp_Score_MetaData)) };//Score属性的信息
//属性的数组
static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
    (const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Score,
};
//结构的参数信息
static const UE4CodeGen_Private::FStructParams ReturnStructParams = {
    (UObject* (*)())Z_Construct_UPackage__Script_Hello,
    nullptr,
    &UE4CodeGen_Private::TNewCppStructOpsWrapper<decltype(NewStructOpsLambda)>::NewCppStructOps,
    "MyStruct",
    RF_Public|RF_Transient|RF_MarkAsNative,
    EStructFlags(0x00000201),
    sizeof(FMyStruct),
    alignof(FMyStruct),
    PropPointers, ARRAY_COUNT(PropPointers),
    METADATA_PARAMS(Struct_MetaDataParams, ARRAY_COUNT(Struct_MetaDataParams))
};
UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, ReturnStructParams);//构造UScriptStruct*到ReturnStruct里去
代码比较简单，上下对照和看看注释就能大概明白。就是收集一个个属性的信息整合成数组，然后合并到结构参数里去，最后传给ConstructUScriptStruct来构造。
思考：FPropertyParamsBaseWithOffset以及后续为何不继承于FPropertyParamsBase？
我们在FPropertyParamsBase和FPropertyParamsBaseWithOffset等后续的注释后面以及属性成员的相似性上来看，很容易就看到这些F*PropertyParams其实是用了继承语义的，那为何不直接继承而是费劲的再写一遍呢？
虽然官方在FPropertyParamsBase上已经写了注释，但是有些朋友可能还是依然比较懵懂。其实这里涉及到一个C++的Aggregate类型的aggregate initialization规则。具体的C++语法规则请自行去补充学习。简单来说，一个Aggregate是一个数组或者一个没有用户声明构造函数，没有私有或保护类型的非静态数据成员，没有父类和虚函数的类型。 Aggregatel类型就可以用形如 T object = {arg1, arg2, ...} 的初始化列表来初始化。我们在上文中见到的：
static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Score = { UE4CodeGen_Private::EPropertyClass::Float, "Score", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000004, 1, nullptr, STRUCT_OFFSET(FMyStruct, Score), METADATA_PARAMS(NewProp_Score_MetaData, ARRAY_COUNT(NewProp_Score_MetaData)) };
后面的={}就是初始化列表。这么写当然是为了简洁的目的，否则一个个参数的字段设置过去，那也太麻烦了。
那如果用继承会怎么样呢？我们可以来做个测试：
struct Point2
{
    float X;
    float Y;
};
struct Point3 :public Point2    //这不是个Aggregate类型，因为有父类
{
    float Z;
};
struct Point3_Aggregate //这是个Aggregate类型
{
    float X;
    float Y;
    float Z;
};
const static Point3 pos{ 1.f,2.f,3.f }; // error C2440:'initializing': cannot convert from 'initializer list' to 'Point3'
const static Point3_Aggregate pos2{ 1.f,2.f,3.f };
因此UE选择不继承，宁愿每个重复写一遍字段声明，就是为了可以简单用{}初始化列表来构造对象。但是我们也观察到，在PropPointers数组里，也依然把一个个元素都转为FPropertyParamsBase*。因为根据C/C++的对象内存模型，继承的时候，基类成员排在派生类成员之前的内存地址上。又因为F*PropertyParams是如此的POD，所以只要保证内存地址和属性成员顺序一致，就可以保证转为另一个结构指针后依然可以正确的使用。
虽然看起来这么解释的通，但还是感觉很麻烦，本来应该用继承的语义却偏偏为了初始化列表妥协了。对完美主义者来说还是不能忍，那么有没有一种既可以用继承又可以用初始化列表的解决方案呢？
其实加上构造函数就可以了。不用Aggregate类型，放宽限制，改用POD类型（POD类型就是没有非静态类型的non-POD类型 （或者这些类型的数组）和引用类型的数据成员，也没有用户定义的赋值操作符和析构函数的类型。）。如：
struct Point2
{
    float X;
    float Y;
    Point2(float x, float y) :X(x), Y(y) {} //构造函数
};
struct Point3_POD :public Point2
{
    float Z;
    Point3_POD(float x, float y, float z) :Point2(x, y), Z(z) {}//构造函数
};
struct Point3_Aggregate
{
    float X;
    float Y;
    float Z;
};
const static Point3_POD pos{ 1.f,2.f,3.f };     //works happy ^_^
const static Point3_Aggregate pos2{ 1.f,2.f,3.f };  //works happy ^_^
所以只要把F*PropertyParams加上构造函数就可以了。至于为啥UE不这么做？问Epic的人去，摊手~
UFunction和UClass的Params和生成：
为了测试UClass里的函数输入输出参数，所以增加一个AddHP函数。
//测试文件：
UCLASS()
class HELLO_API UMyClass :public UObject
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
    float Score;
public:
    UFUNCTION(BlueprintCallable, Category = "Hello")
    float AddHP(float HP);
    UFUNCTION(BlueprintCallable, Category = "Hello")
    void CallableFunc();    //C++实现，蓝图调用
    UFUNCTION(BlueprintNativeEvent, Category = "Hello")
    void NativeFunc();  //C++实现默认版本，蓝图可重载实现
    UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
    void ImplementableFunc();   //C++不实现，蓝图实现
};
//Class.h
//类里的函数链接信息，一个函数名字对应一个UFunction对象
struct FClassFunctionLinkInfo 
{
    UFunction* (*CreateFuncPtr)();  //获得UFunction对象的函数指针回调
    const char* FuncNameUTF8;       //函数的名字
};
//类在Cpp里的类型信息，用一个结构是为了将来也许还会添加别的字段
struct FCppClassTypeInfoStatic
{
    bool bIsAbstract;   //是否抽象类
};
//UObjectGlobals.h
namespace UE4CodeGen_Private
{
    //函数参数
    struct FFunctionParams
    {
        UObject*                          (*OuterFunc)();   //所属于的外部对象，一般是外部的UClass*对象
        const char*                         NameUTF8;   //函数的名字
        EObjectFlags                        ObjectFlags;    //UFunction对象的特征
        UFunction*                        (*SuperFunc)();   //UFunction的基类，一般为nullptr
        EFunctionFlags                      FunctionFlags;  //函数本身的特征
        SIZE_T                              StructureSize;  //函数的参数返回值包结构的大小
        const FPropertyParamsBase* const*   PropertyArray;  //函数的参数和返回值字段数组
        int32                               NumProperties;  //函数的参数和返回值字段数组大小
        uint16                              RPCId;          //网络间的RPC Id
        uint16                              RPCResponseId;  //网络间的RPC Response Id
    #if WITH_METADATA
        const FMetaDataPairParam*           MetaDataArray;  //元数据数组
        int32                               NumMetaData;
    #endif
    };
    //实现的接口参数，篇幅所限，接口的内容可以自行分析
    struct FImplementedInterfaceParams
    {
        UClass* (*ClassFunc)();     //外部所属于的UInterface对象
        int32     Offset;           //在UMyClass里的实现的IMyInterface的虚函数表地址偏移
        bool      bImplementedByK2; //是否在蓝图中实现
    };
    //类参数
    struct FClassParams
    {
        UClass*                                   (*ClassNoRegisterFunc)(); //获得UClass*对象的函数指针
        UObject*                           (*const *DependencySingletonFuncArray)();    //获取依赖对象的函数指针数组，一般是需要前提构造的基类，模块UPackage对象
        int32                                       NumDependencySingletons;
        uint32                                      ClassFlags; // EClassFlags，类特征
        const FClassFunctionLinkInfo*               FunctionLinkArray;  //链接的函数数组
        int32                                       NumFunctions;
        const FPropertyParamsBase* const*           PropertyArray;  //类里定义的成员变量数组
        int32                                       NumProperties;
        const char*                                 ClassConfigNameUTF8;    //配置文件名字，有些类可以从配置文件从加载数据
        const FCppClassTypeInfoStatic*              CppClassInfo;   //Cpp里定义的信息
        const FImplementedInterfaceParams*          ImplementedInterfaceArray;  //实现的接口信息数组
        int32                                       NumImplementedInterfaces;
    #if WITH_METADATA           //类的元数据
        const FMetaDataPairParam*                   MetaDataArray;
        int32                                       NumMetaData;
    #endif
    };
}
//MyClass.gen.cpp
//构造AddHp函数的UFunction对象
UFunction* Z_Construct_UFunction_UMyClass_AddHP()
{
    struct MyClass_eventAddHP_Parms     //函数的参数和返回值包
    {
        float HP;
        float ReturnValue;
    };
    static UFunction* ReturnFunction = nullptr;
    if (!ReturnFunction)
    {
        //定义两个属性用来传递信息
        static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue = { UE4CodeGen_Private::EPropertyClass::Float, "ReturnValue", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000580, 1, nullptr, STRUCT_OFFSET(MyClass_eventAddHP_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
        static const UE4CodeGen_Private::FFloatPropertyParams NewProp_HP = { UE4CodeGen_Private::EPropertyClass::Float, "HP", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000080, 1, nullptr, STRUCT_OFFSET(MyClass_eventAddHP_Parms, HP), METADATA_PARAMS(nullptr, 0) };
        static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
            (const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_ReturnValue,
            (const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_HP,
        };
#if WITH_METADATA
        static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
            { "Category", "Hello" },
            { "ModuleRelativePath", "MyClass.h" },
        };
#endif
        static const UE4CodeGen_Private::FFunctionParams FuncParams = { (UObject*(*)())Z_Construct_UClass_UMyClass, "AddHP", RF_Public|RF_Transient|RF_MarkAsNative, nullptr, (EFunctionFlags)0x04020401, sizeof(MyClass_eventAddHP_Parms), PropPointers, ARRAY_COUNT(PropPointers), 0, 0, METADATA_PARAMS(Function_MetaDataParams, ARRAY_COUNT(Function_MetaDataParams)) };
        UE4CodeGen_Private::ConstructUFunction(ReturnFunction, FuncParams); //构造函数
    }
    return ReturnFunction;
}
//...构造其他的函数
//该类依赖的对象列表，用函数指针来获取。
static UObject* (*const DependentSingletons[])() = {
                (UObject* (*)())Z_Construct_UClass_UObject,
                (UObject* (*)())Z_Construct_UPackage__Script_Hello,
            };
//函数链接信息
static const FClassFunctionLinkInfo FuncInfo[] = {
    { &Z_Construct_UFunction_UMyClass_CallableFunc, "CallableFunc" }, // 1841300010
    { &Z_Construct_UFunction_UMyClass_ImplementableFunc, "ImplementableFunc" }, // 2010696670
    { &Z_Construct_UFunction_UMyClass_NativeFunc, "NativeFunc" }, // 2593520329
};
#if WITH_METADATA
static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
    { "IncludePath", "MyClass.h" },
    { "ModuleRelativePath", "MyClass.h" },
};
#endif
#if WITH_METADATA
static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Score_MetaData[] = {
    { "Category", "MyClass" },
    { "ModuleRelativePath", "MyClass.h" },
};
#endif
static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Score = { UE4CodeGen_Private::EPropertyClass::Float, "Score", RF_Public|RF_Transient|RF_MarkAsNative, 0x0010000000000004, 1, nullptr, STRUCT_OFFSET(UMyClass, Score), METADATA_PARAMS(NewProp_Score_MetaData, ARRAY_COUNT(NewProp_Score_MetaData)) };
static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = {
    (const UE4CodeGen_Private::FPropertyParamsBase*)&NewProp_Score,
};
static const FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
    TCppClassTypeTraits<UMyClass>::IsAbstract,
};
static const UE4CodeGen_Private::FClassParams ClassParams = {
    &UMyClass::StaticClass,
    DependentSingletons, ARRAY_COUNT(DependentSingletons),
    0x00100080u,
    FuncInfo, ARRAY_COUNT(FuncInfo),
    PropPointers, ARRAY_COUNT(PropPointers),
    nullptr,
    &StaticCppClassTypeInfo,
    nullptr, 0,
    METADATA_PARAMS(Class_MetaDataParams, ARRAY_COUNT(Class_MetaDataParams))
};
UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);   //构造UClass对象
注意，对于一个函数来说，参数和返回值都可以算是函数内部定义的属性，只不过其有不同的特征和用途。类里包含属性和函数，而函数又包含属性。属性的构造和Struct里的规则一样，就不赘述了。不同的是，因为Class里可以包含Function，所以构造UClass之前必须先构造出所有的UFunction。所以整理下，其实上述的那些构造就是结构套结构，加上一些数组整合出来的信息集合而已。
思考：为什么生成的代码里大量用了函数指针来返回对象？
如UClass* (*ClassNoRegisterFunc)()或UFunction* (*CreateFuncPtr)()都用函数指针来获取定义的UClass*对象和前提依赖的UFunction*对象。为什么不直接用个UClass*或UFunction*指针呢？
答案很简单，因为构造顺序的不确定。
在一个类型系统中，类型的依赖管理是项很麻烦但又非常重要的事，你必须保证当前类型的所有前置类型都已经定义完毕，才能开始本类型的构造。针对此问题，当然你可以小心翼翼的理清定义顺序，确保所有的顺序都是由底向上的。可是理想很美好，现实很骨感，这一步骤很难实现，是人都会犯错，更何况面对UE4当前的1572个UClass、1039个UStruct、588个Enum……你真的相信有人能管理好这些？所以在类型系统里想人工整理好类型的依赖定义顺序基本不现实，你几乎很难在构造本类型的时候，恰好的取得前置类型的对象。
那怎么办？也简单，就如同C++里处理static单件对象的依赖顺序一样，既然处理不了，那就不处理！采用懒惰求值的思想，在需要前置类型的时候，先判断有没有构造出来，如果有就立即返回，如果没有就构造后再返回——一个简易版的单件模式。因为这个套路是如此的普遍，所以这一些判断加上构造的逻辑封装一下就成了一个个函数，为了获得那些对象，就变成了先获得那些函数指针了。生成的代码里都是大概这种套路：
UClass* Z_Construct_UClass_UMyClass()   //用以获取UMyClass所对应的UClass的函数
{
    static UClass* OuterClass = nullptr;    //一个函数局部静态指针
    if (!OuterClass)    //反正都是单线程执行，所以不需要线程安全的保护
    {
        //...一些构造代码
        UE4CodeGen_Private::ConstructUClass(OuterClass, ClassParams);
    }
    return OuterClass;
}
利用此法，就在代码中形成了一个可自动上溯的前置对象获取链条。任何时候，想得到某一个类的UClass*对象，我们不需要去操心是否已经构造完成，也不需要担心它的依赖项是否已经全部构造了，因为代码的机制保证了前置项的按需构造。
UPackage的Params和生成：
对于Hello模块而言，按照UE4的Module规则，我们需要定义一个Hello UPackage来存放该模块里定义的类型。
之前的4.15的代码形式为：
UPackage* Z_Construct_UPackage__Script_Hello()
{
    static UPackage* ReturnPackage = NULL;
    if (!ReturnPackage)
    {
        ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Hello")), false, false));
        ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
        FGuid Guid;
        Guid.A = 0x79A097CD;
        Guid.B = 0xB58D8B48;
        Guid.C = 0x00000000;
        Guid.D = 0x00000000;
        ReturnPackage->SetGuid(Guid);
    }
    return ReturnPackage;
}
在4.17之后改为：
//UObjectGlobals.h
namespace UE4CodeGen_Private
{
    //包参数
    struct FPackageParams
    {
        const char*                        NameUTF8;    //名字
        uint32                             PackageFlags; // EPackageFlags包的特征
        uint32                             BodyCRC; //内容的CRC,CRC的部分后续介绍
        uint32                             DeclarationsCRC; //声明部分的CRC
        UObject*                  (*const *SingletonFuncArray)();   //依赖的对象列表
        int32                              NumSingletons;
#if WITH_METADATA
        const FMetaDataPairParam*          MetaDataArray;//元数据数组
        int32                              NumMetaData;
#endif
    };
}
//Hello.init.gen.cpp
UPackage* Z_Construct_UPackage__Script_Hello()
{
    static UPackage* ReturnPackage = nullptr;
    if (!ReturnPackage)
    {
        static const UE4CodeGen_Private::FPackageParams PackageParams = {
            "/Script/Hello",    //包名字
            PKG_CompiledIn | 0x00000000,
            0xA1EAFF6A,
            0x41CF0543,
            nullptr, 0,
            METADATA_PARAMS(nullptr, 0)
        };
        UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
    }
    return ReturnPackage;
}
本块内容比较简单，能坚持看到此处的朋友，对上文的代码应该是一目了然的。有一点需要知道的是，在Hello模块里的定义的类型数据，都是放在"/Script/Hello"Package里的，所以Hello Package是第一个首先构造出来的，因为它被后续的其他类型都依赖着。
总结
对比了前后两版本的代码，我们不难看出重构了之后，生成的代码更加的紧致，语法的噪音减少了很多，代码的信息量密度大大提高了。但要注意，本文关注的类型系统阶段是对之前《InsideUE4》UObject（四）类型系统代码生成的补充，后续依然是接着《InsideUE4》UObject（五）类型系统收集章节的内容进行开始收集，所以前文的那些static静态收集机制并没有改变。
至于UE4CodeGen_Private::ConstructXXX构造的具体实现，我们在后续章节讲到类型系统的结构组织时候再详细讲解，我保证，那天不会太久远。当前阶段你可以简单的理解为都是通过一个个参数构造出一个个类型对象。
思考：生成的代码能否做得更加的清晰高效？
虽然通过此次重构，代码的可读性上升了许多。但平心而论，现在的代码生成依然远远算不上优雅。那么在程序化代码生成的时候一般有哪些手段可以继续提升呢？
追其本质，让代码变得简洁的手段其实都是在提升信息密度。把代码比作文件的话，重构就像压缩软件一样，把代码的信息量压缩到无所压就算是到了极致了。但是当然这中间当然也要权衡平台移植性（否则直接存一个二进制文件好了）、可读性、编译效率等问题。提升信息密度的手段就只有一个：同样的信息不要书写两遍。因此带来的方式就是封装！而封装，在代码生成的时候，我们其实可以用到：
宏，UE4里其实已经用了一些宏来缩减代码，比如ARRAYCOUNT、VTABLEOFFSET、IMPLEMENT_CLASS等。但目前的生成代码里依然有大量的长名字，套路化数组拼接，可以用宏来拼接。过度用宏当然也会降低可读性可调试性，但恰当的地方使用可以如同开挂一般优化掉巨量的代码。宏一直是代码拼接的最强大利器。
函数，把相似的逻辑封装成函数可以优化掉大量的操作，只对外提供最简洁的信息输入接口。本文介绍的UE4优化方式就是用了函数来优化。我个人的倾向是宁愿在核心层多定义一些方便的辅助函数来接收多种输入，而不是在代码生成的时候去一个个拼函数的实体，这样可以大大减小生成代码的体积。函数的实现上巧用不定参数、数组和循环，可以使你的函数吞吐能力惊人。
模板，更深层次的挖掘编译器提供的信息，压榨每个字段提供的信息量，利用它，从而自动推导出你所需要的其他信息。比如属性的类型就可以用模板根据字段的c++类型自动推导出来，而不需要手动分析注入了。UE4的生成代码里模板用的不多，是因为模板也有其很大的缺点：编译慢和难理解。在已经有了UHT分析代码的基础上，再用模板推导一遍，好像意义就不是那么大了，所以编译消耗还是能省一点是一点吧。至于模板的难理解，一款开源面向大众的引擎，在技术的选型实现上不应该过分的炫技，因为从业人员的技术水平，初中级的才是占绝大多数。考虑到受众问题和推广，有时候还是应该用一些朴实无华的实现比较能广为接受，同时也能有更大概率争取到重构维护者。否则，你写的代码，是很厉害，但是只有你自己能改得动改得明白，那叫社区里的人怎么为你贡献维护升级。
扩展性，同时建议尽量把类型系统的构造逻辑放到Runtime里去，而不是在生成代码里（之前UE4就是在生成代码里直接new出一个个UXXX类型对象。放到Runtime，对外提供函数API接口，这样的好处是可测试性大大增长，不需要依赖UHT就可以手动构造出想要的类型进行测试。另外对于一些有在运行时动态Emit创建类型的需求来说，脱离UHT，保持自身功能的完备性也是必需的。
上述的讨论不限于UE4引擎，只是对于有兴趣实现一个类型系统的人来说，在每个阶段其实都有很多技术选择，但设计就是权衡的艺术，清楚了解你的受众，清晰你的设计目的愿景，对可用的各种手段信手拈来，最后才能组合出优雅的设计。
后记
在我们阅读UE4源码的过程中，也要时刻认识到UE4的源码不是完美的。有很多时候，在阅读一段具体代码时，我们可能会去使劲猜测这段代码的用意，琢磨当初是怎么的设计理念却不可得。其实，现实的情况是这些代码往往只是一时的修复，且不是所有代码的编写者技术都是那么高超。他会出错，另一个他会修复，然后再犯错修复，周而复始。如同生物的进化一样，一次次重构优化，最终得到的往往并不是最优解，就像人眼睛的盲点和人的智齿都不是最正确的设计，而是会留下进化的痕迹。但是尽管如此，我们也并不需要感到沮丧，因为接受不完美，接受最后的这个可接受解，适当的懂得妥协和接受缺陷，也许也是一个技术人成熟的标志之一吧。
有一个有趣的现象，对于大工程量的项目（如UE4)来说，越是底层的模块越是缺乏推动力去重构，越底层的代码其改动的阻力也越大。牵一发而动全身，在一些时候，重构底层模块其实也是最能产生巨量效益的时候，因为其影响会层层放大到最上层上去。但是代码毕竟是人在写，在一个公司里，一个团队里，形成的开发氛围往往是只要底层代码能工作，就不会有人去改，也不会有人敢改。拿UE4的CoreUObject模块来说，是UE4的对象系统模块，可以说是最底层核心的模块了，但是根据我这么一大段时间的研读来说，代码里充斥着各种历史痕迹和小修小补，一些代码结构也是让人无可奈何，but it works，所以这块代码从UE3过来，到UE4里，相信有生之年也是会继续追随到UE5的。CoreUObject代码模块目前能工作，虽然有时也会有点BUG，但是到时小修补就好了，那些代码的优雅追求和结构的设计，改的好了效益不太明显；改过之后出了Bug是不是都算你的？所以正是因为这种效益和责任的担负，导致往往最需要重视的模块，最得不到升级改造。但历史的规律也表明了，代码的小缺陷积累多了，开发者的怨气积攒足够了，再适逢一个不动底层不能开工的功能需求的刺激，到时候才能下得了决心大改，或者干脆另起炉灶重新设计了。说这些，是希望同读UE4源码的朋友，在遇到代码里莫名其妙的设计，抓耳挠腮苦思冥想的时候，可以放宽心态，稍安勿躁，休息一下，我们继续前行。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（七）类型系统注册-第一个UClass</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/57005310
引言
很久很久以前，有这么三篇文《InsideUE4》UObject（四）类型系统代码生成、《InsideUE4》UObject（五）类型系统收集和《InsideUE4》UObject（六）类型系统代码生成重构-UE4CodeGen_Private，介绍了UHT利用代码里的宏标记来生成反射代码来记录信息，然后在在Main函数调用之前，利用静态变量的初始化来收集这些类型的元数据信息到一个个数据结构里。因我的拖延原罪，对这个流程已经遗忘的朋友，强烈建议回顾一下前三文来收拾一下思绪继续前进。
在走过了引擎的static初始化阶段后，类型系统的元数据信息仍然零零散散的分布在几个全局变量里面，声明定义出来一些注册构造函数也只是收集了函数指针，却都还没有机会来好好的调用一下它们。因此注册的文章部分着重讲解的是程序启动过程中，是怎么把之前的信息和函数都串起来使用，最终在内存中构造出类型系统的类型树的。
理所当然的注意一下：
注册章节暂时忽略UObject如何分配存储、GC释放、蓝图动态类的相关内容，后续讲解。
忽略性能分析STATS和热重载WITH_HOT_RELOAD的代码，忽略check和ensure的检测代码。
示例源码里中间如果有其他主题无关代码会用//...表示，否则的话代码就是原本那样。
Static初始化
在前面的文章里，讲解了在static阶段的信息收集。在《InsideUE4》UObject（五）类型系统收集最后UObject的收集的时候简单点了一下，IMPLEMENT_VM_FUNCTION(EX_CallMath, execCallMathFunction)会触发UObject::StaticClass()的调用，因此作为最开始的调用，会生成第一个UClass*。
#define IMPLEMENT_FUNCTION(func) \
static FNativeFunctionRegistrar UObject##func##Registar(UObject::StaticClass(),#func,&UObject::func);
//...
IMPLEMENT_VM_FUNCTION(EX_CallMath, execCallMathFunction);//ScriptCore.cpp里的定义
虽然代码里有很多个IMPLEMENT_CAST_FUNCTION和IMPLEMENT_VM_FUNCTION的调用，但第一个触发的是execCallMathFunction的调用，可以看到FNativeFunctionRegistrar对象在构造的时候，第一个参数就会触发UObject::StaticClass()的调用。而以前文的内容，StaticClass()的调用会被展开为GetPrivateStaticClass的调用。而GetPrivateStaticClass是在IMPLEMENT_CLASS里定义的，那么UObject的相关IMPLEMENT_CLASS是在哪里定义的呢？
NoExportTypes.h
答案就在这个文件里。相信有些朋友也会不经意间打开过这个文件，但可能会有点迷糊，为何里面重复定义了一些Enum、Struct和UObject？难道不会和真正的定义冲突吗？这个文件的目的是干嘛的？ 其实这个文件的目的就是为了把CoreUObject模块里的一些基础类型喂给UHT来生成类型的元数据信息。 NoExportTypes.h文件的结构其实理解起来很简单：
#if CPP
//包含一些头文件来让NoExportTypes.gen.cpp可以编译通过
#endif
#if !CPP//这里面的部分是不参与编译的，所以不会产生定义冲突，但是却可以让UHT分析，因为UHT只是个文本分析器而已。
//枚举的声明，只是加上了宏标记。
//结构的声明，只是加上了宏标记。
//UObject的声明，C++的内容其实不重要，重要的是让UHT分析得到些什么信息
UCLASS(abstract, noexport)
class UObject
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintImplementableEvent, meta=(BlueprintInternalUseOnly = "true"))
    void ExecuteUbergraph(int32 EntryPoint);
};
#endif
而NoExportTypes.gen.cpp就和之前讲过的元数据代码生成一样的内容结构了。文件拉到最后你就会看到IMPLEMENT_CLASS(UObject, 1563732853);的定义了。
GetPrivateStaticClass
而IMPLEMENT_CLASS根据前文的介绍的展开，里面定义着GetPrivateStaticClass的实现。 虽然最开始的调用是UObject::StaticClass()。但是以UMyClass为例会更看清楚里面参数的含义（因为跟我们实际应用时候的值更贴近，而UObject太基础了，很多信息是空的），工程名为Hello。
//类的声明值
DECLARE_CLASS(UMyClass, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Hello"), NO_API)
//值的传递
UClass* UMyClass::GetPrivateStaticClass(const TCHAR* Package)
{
    static UClass* PrivateStaticClass = NULL;   //静态变量，下回访问就不用再去查找了
    if (!PrivateStaticClass)
    {
        /* this could be handled with templates, but we want it external to avoid code bloat */
        GetPrivateStaticClassBody(
            Package,    //包名,TEXT("/Script/Hello")，用来把本UClass*构造在该UPackage里
            (TCHAR*)TEXT("UMyClass") + 1 + ((StaticClassFlags & CLASS_Deprecated) ? 11 : 0),//类名，+1去掉U、A、F前缀，+11去掉Deprecated_前缀
            PrivateStaticClass, //输出引用，所以值会被改变
            StaticRegisterNativesUMyClass,  //注册类Native函数的指针
            sizeof(UMyClass),   //类大小
            UMyClass::StaticClassFlags, //类标记，值为CLASS_Intrinsic，表示在C++代码里定义的类
            UMyClass::StaticClassCastFlags(),   //虽然是调用，但只是简单返回值CASTCLASS_None
            UMyClass::StaticConfigName(),   //配置文件名，用于从config里读取值
            (UClass::ClassConstructorType)InternalConstructor<UMyClass>,//构造函数指针，包了一层
            (UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<UMyClass>,//hotreload的时候使用来构造虚函数表，暂时不管
            &UMyClass::AddReferencedObjects,   //GC使用的添加额外引用对象的静态函数指针，若没有定义，则会调用到UObject::AddReferencedObjects，默认函数体为空。
            &UMyClass::Super::StaticClass,  //获取基类UClass*的函数指针，这里Super是UObject
            &UMyClass::WithinClass::StaticClass //获取对象外部类UClass*的函数指针，默认是UObject
        );
    }
    return PrivateStaticClass;
}
虽然值的传递还是很简明的，但有些要点在此还是得提醒一下：
Package名字的传入是为了在构建UClass*之后，把UClass*对象的OuterPrivate设定为正确的UPackage*对象。在UE里，UObject必须属于某个UPackage。所以传入名字是为了后续查找或者创建出前置需要的UPackage对象。“/Script/”开头表示这是个代码模块。
StaticRegisterNativesUMyClass这个函数的名字是用宏拼接的，分别在.generated.h和.gen.cpp里声明和定义。
InternalConstructor<UMyClass>这个模板函数是为了包一下C++的构造函数，因为你没法直接去获得C++构造函数的函数指针。在.generated.h里会根据情况生成这两个宏的调用（GENERATED_UCLASS_BODY接收FObjectInitializer参数，GENERATED_BODY不接收参数），从而在以后的UObject*构造过程中，可以调用到我们自己写的类的构造函数。
Super指的是类的基类，WithinClass指的是对象的Outer对象的类型。这里要区分开的是类型系统和对象系统之间的差异，Super表示的是类型上的必须依赖于基类先构建好UClass*才能构建构建子类的UClass*；WithinClass表示的是这个UObject*在构建好之后应该限制放在哪种Outer下面，这个Outer所属于的UClass*我们必须先提前构建好。
#define DEFINE_DEFAULT_CONSTRUCTOR_CALL(TClass) \
static void __DefaultConstructor(const FObjectInitializer& X) {new((EInternal*)X.GetObj())TClass;}
#define DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(TClass) \
static void __DefaultConstructor(const FObjectInitializer& X) {new((EInternal*)X.GetObj())TClass(X);}
template<class T>
void InternalConstructor( const FObjectInitializer& X )
{ 
    T::__DefaultConstructor(X);
}
GetPrivateStaticClassBody
接着我们来看看内部的函数实现：
void GetPrivateStaticClassBody(
    const TCHAR* PackageName,
    const TCHAR* Name,
    UClass*& ReturnClass,
    void(*RegisterNativeFunc)(),
    uint32 InSize,
    EClassFlags InClassFlags,
    EClassCastFlags InClassCastFlags,
    const TCHAR* InConfigName,
    UClass::ClassConstructorType InClassConstructor,
    UClass::ClassVTableHelperCtorCallerType InClassVTableHelperCtorCaller,
    UClass::ClassAddReferencedObjectsType InClassAddReferencedObjects,
    UClass::StaticClassFunctionType InSuperClassFn,
    UClass::StaticClassFunctionType InWithinClassFn,
    bool bIsDynamic /*= false*/
    )
{
    ReturnClass = (UClass*)GUObjectAllocator.AllocateUObject(sizeof(UClass), alignof(UClass), true);//分配内存
    ReturnClass = ::new (ReturnClass)UClass //用placement new在内存上手动调用构造函数
    (
    EC_StaticConstructor,Name,InSize,InClassFlags,InClassCastFlags,InConfigName,
    EObjectFlags(RF_Public | RF_Standalone | RF_Transient | RF_MarkAsNative | RF_MarkAsRootSet),
    InClassConstructor,InClassVTableHelperCtorCaller,InClassAddReferencedObjects
    );
    InitializePrivateStaticClass(InSuperClassFn(),ReturnClass,InWithinClassFn(),PackageName,Name);//初始化UClass*对象
    RegisterNativeFunc();//注册Native函数到UClass中去
}
这个函数内部只做了4件事：
分配内存。GUObjectAllocator是全局的内存分配器，分配了一块内存来存放UClass对象。关于存储的内容后续再说，这里理解为返回一块内存就可。也要注意的是，ReturnClass是引用，这里一赋值，就代表外面static的PrivateStaticClass就有值了。所以就算这个GetPrivateStaticClassBody函数还没返回，但是如果去访问UMyClass::StaticClass()也是会立即返回这个值的。
调用UClass的构造函数。这里的EC_StaticConstructor只是个标记用来指定调用特定的UClass构造函数重载版本。该构造函数内只是简单的成员变量赋值，并没有什么特别的。这么二步构造的原因是UObject的内存都是统一管理的，所以应该由GUObjectAllocator来分配，不能像标准C++那样直接new出来一个。
InitializePrivateStaticClass调用的时候，InSuperClassFn()和InWithinClassFn()是会先被调用的，所以其会先触发Super::StaticClass()和WithinClass::StaticClass()，再会堆栈式的加载前置的类型。
RegisterNativeFunc()就是上文的StaticRegisterNativesUMyClass，在此刻调用，用来像UClass里添加Native函数。Native函数指的是在C++有函数体实现的函数，而蓝图中的函数和BlueprintImplementableEvent的函数就不是Native函数。
InitializePrivateStaticClass
COREUOBJECT_API void InitializePrivateStaticClass(
    class UClass* TClass_Super_StaticClass,
    class UClass* TClass_PrivateStaticClass,
    class UClass* TClass_WithinClass_StaticClass,
    const TCHAR* PackageName,
    const TCHAR* Name
    )
{
    //...
    if (TClass_Super_StaticClass != TClass_PrivateStaticClass)
    {
        TClass_PrivateStaticClass->SetSuperStruct(TClass_Super_StaticClass);    //设定类之间的SuperStruct
    }
    else
    {
        TClass_PrivateStaticClass->SetSuperStruct(NULL);    //UObject无基类
    }
    TClass_PrivateStaticClass->ClassWithin = TClass_WithinClass_StaticClass;    //设定Outer类类型
    //...
    TClass_PrivateStaticClass->Register(PackageName, Name); //转到UObjectBase::Register()
    //...
}
这个函数的名字叫做初始化，但其实没干啥事。
设定类型的SuperStruct。SuperStruct是定义在UStruct里的UStruct* SuperStruct，用来指向本类型的基类。
设定ClassWithin的值。也就是限制Outer的类型。
调用UObjectBase::Register()。终于对每个UClass*开始了注册，不枉调用链条上的UClassRegisterAllCompiledInClasses的Register之名。
UObjectBase::Register
而该函数比较简单，只是简单的先记录一下信息到一个全局单件Map里和一个全局链表里。
struct FPendingRegistrantInfo
{
    const TCHAR*    Name;   //对象名字
    const TCHAR*    PackageName;    //所属包的名字
    static TMap<UObjectBase*, FPendingRegistrantInfo>& GetMap()
    {   //用对象指针做Key，这样才可以通过对象地址获得其名字信息，这个时候UClass对象本身其实还没有名字，要等之后的注册才能设置进去
        static TMap<UObjectBase*, FPendingRegistrantInfo> PendingRegistrantInfo;    
        return PendingRegistrantInfo;
    }
};
//...
struct FPendingRegistrant
{
    UObjectBase*    Object; //对象指针，用该值去PendingRegistrants里查找名字。
    FPendingRegistrant* NextAutoRegister;   //链表下一个节点
};
static FPendingRegistrant* GFirstPendingRegistrant = NULL;  //全局链表头
static FPendingRegistrant* GLastPendingRegistrant = NULL;   //全局链表尾
//...
void UObjectBase::Register(const TCHAR* PackageName,const TCHAR* InName)
{
    //添加到全局单件Map里，用对象指针做Key，Value是对象的名字和所属包的名字。
    TMap<UObjectBase*, FPendingRegistrantInfo>& PendingRegistrants = FPendingRegistrantInfo::GetMap();
    PendingRegistrants.Add(this, FPendingRegistrantInfo(InName, PackageName));
    //添加到全局链表里，每个链表节点带着一个本对象指针，简单的链表添加操作。
    FPendingRegistrant* PendingRegistration = new FPendingRegistrant(this);
    if(GLastPendingRegistrant)
    {
        GLastPendingRegistrant->NextAutoRegister = PendingRegistration;
    }
    else
    {
        check(!GFirstPendingRegistrant);
        GFirstPendingRegistrant = PendingRegistration;
    }
    GLastPendingRegistrant = PendingRegistration;
}
思考：为何Register只是先记录一下信息？
初看之下肯定会疑惑，为何这里并没有做一些实际的操作。其实是因为UClass的注册分成了多步，在static初始化的时候（连main都没进去呢），甚至到后面CoreUObject模块加载的时候，UObject对象分配索引的机制（GUObjectAllocator和GUObjectArray）还没有初始化完毕，因此这个时候如果走下一步去创建各种UProperty、UFunction或UPackage是不合适，创建出来了也没有合适的地方来保存索引。所以，在最开始的时候，只能先简单的创建出各UClass*对象（简单到对象的名字都还没有设定，更何况填充里面的属性和方法了），先在内存里把这些UClass*对象记录一下，等后续对象的存储结构准备好了，就可以把这些UClass*对象再拉出来继续构造了。先剧透一下，后续的初始化对象存储机制的函数调用是InitUObject()，继续构造的操作是在ProcessNewlyLoadedUObjects()里的。这些信息在后面会被消费用到的，莫急。
思考：记录信息为何需要一个TMap加一个链表？
我们可以看到，为了记录信息，明明是用一个数据结构就能保存的（源码里的两个数据结构里的数据数量也是1:1的），为何要麻烦的设置成这样。原因有三：
是快速查找的需要。在后续的别的代码（获取CDO等）里也会经常调用到UObjectForceRegistration(NewClass)，因此常常有通过一个对象指针来查找注册信息的需要，这个时候为了性能就必须要用字典类的数据结构才能做到O(1)的查找。
顺序注册的需要。而字典类的数据结构一般来说内部为了hash，数据遍历取出的顺序无法保证和添加的顺序一致，而我们又想要遵循添加的顺序来注册（很合理，早添加进来的是早加载的，是更底层的，处在依赖顺序的前提位置。我们前面的SuperClass和WithinClass的访问也表明了这一点），因此就需要另一个顺序数据结构来辅助。
那为什么是链表而不是数组呢？链表比数组优势的地方也只在于可以快速的中间插入。但是UE源码里也没有这个方面的体现，所以其实二者都可以。我在源码里把注册结构改为如下用数组也依然可以正常工作。要嘛是他们的代码写得也挺啰嗦，要嘛是我没懂其他的深意。不过倒也无伤大雅。
struct FPendingRegistrant
{
    UObjectBase*    Object;
    FPendingRegistrant(UObjectBase* InObject)
        : Object(InObject)
    {}
    static TArray<FPendingRegistrant>& GetArray()
    {
        static TArray<FPendingRegistrant> PendingRegistrants;
        return PendingRegistrants;
    }
};
RegisterNativeFunc
讲完了注册，接着说GetPrivateStaticClassBody的最后一步：RegisterNativeFunc的调用，同样以MyClass为例：
//...MyClass.gen.cpp
void UMyClass::StaticRegisterNativesUMyClass()
{
    UClass* Class = UMyClass::StaticClass();   //这里是可以立即返回值的
    static const FNameNativePtrPair Funcs[] = { 
        //exec开头的都是在.generated.h里定义的蓝图用的，暂时不管它，理解为可以调用就行了。
        { "AddHP", &UMyClass::execAddHP },
        { "CallableFunc", &UMyClass::execCallableFunc },
        { "NativeFunc", &UMyClass::execNativeFunc },
    };
    FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
}
//...
void FNativeFunctionRegistrar::RegisterFunctions(class UClass* Class, const FNameNativePtrPair* InArray, int32 NumFunctions)
{
    for (; NumFunctions; ++InArray, --NumFunctions)
    {
        Class->AddNativeFunction(UTF8_TO_TCHAR(InArray->NameUTF8), InArray->Pointer);
    }
}
//...
void UClass::AddNativeFunction(const ANSICHAR* InName, FNativeFuncPtr InPointer)
{
    FName InFName(InName);
    new(NativeFunctionLookupTable) FNativeFunctionLookup(InFName,InPointer);
}
而NativeFunctionLookupTable是在UClass里的一个成员变量
//蓝图调用的函数指针原型
typedef void (*FNativeFuncPtr)(UObject* Context, FFrame& TheStack, RESULT_DECL);
/** A struct that maps a string name to a native function */
struct FNativeFunctionLookup
{
    FName Name; //函数名字
    FNativeFuncPtr Pointer;//函数指针
};
//...
class COREUOBJECT_API UClass : public UStruct
{
public:
    TArray<FNativeFunctionLookup> NativeFunctionLookupTable;
}
可以看到这步操作这是简单的往UClass*里添加Native函数的数据。
思考：为什么这么猴急的需要一开始就往UClass里添加Native函数？
以IMPLEMENT_VM_FUNCTION(EX_CallMath, execCallMathFunction)为例，execCallMathFunction是定义在代码里的一个函数，它的地址必然需要通过一种方式记录下来。当然你也可以像UE4CodeGen_Private做的那样，先用各种Params对象保存起来，然后在后面合适的时候调用提取来添加。只不过这个时候因为UClass对象都已经创建出来了，所以就索性直接存到NativeFunctionLookupTable里面去了，后续要用的时候再用名字去里面查找。稍微提一下，这里不用TMap而用TArray是因为一般来说我们在一个类里写的函数数量并不会太多，对于元素比较少的情况下，TArray的线性查找也很快，而且还省内存。
思考：那些非Native的函数怎么办？
其实就是指的就是BlueprintImplementableEvent的函数，它不需要我们自己定义函数体。而UHT会帮我们生成一个函数体，当我们在C++里调用ImplementableFunc的时候，其实会触发一次函数查找，如果在蓝图中有定义该名字的函数，则会得到调用。
//...MyClass.h
UFUNCTION(BlueprintImplementableEvent)
void ImplementableFunc();   //C++不实现，蓝图实现
//...MyClass.gen.cpp
void UMyClass::ImplementableFunc()
{
    ProcessEvent(FindFunctionChecked(TEXT("ImplementableFunc"),NULL);
}
需要提前注意的是，不管是Native与否，函数后面都会生成一个UFunction对象，只不过Native函数的UFunction在绑定的时候会去它所属于的UClass里的NativeFunctionLookupTable通过函数名字查找真正的函数指针，而非Native的UFunction会把函数指针指向UObject::ProcessInternal，用来处理蓝图虚拟机调用的情况。
总结
到此刻，Static初始化就结束了。总结一下，我们至今的成果是在内存中收集到一些类型元数据信息以备后续使用，还有成功构建出来的第一个UClass对象———也是第一个UObject对象，是UObject::StaticClass()，这个对象想想是不是很奇妙呢。一个对象表示了对象的类型，其本身也是个对象。类型系统的第一个类型是UObject类型。
Static初始化后，第一个UClass的属性值是：
SuperStruct = NULL，因为UObject上面没有基类了
ClassPrivate = NULL，所属的类型，这个时候还没有设置该值。在以后会设置指向UClass::StaticClass()，因为其本身是一个UClass。
OuterPrivate = NULL，属于的Outer，也还没放进任何Package里。在以后会设置指向“/Script/CoreUObject”的UPackage。
NamePrivate = "None"，还没有设定任何名字。在以后会设置为“Object”
ClassWithin = this，这个倒是已经知道了指向自己，表明一个UObject可以放在任何UObject下。
PropertiesSize = sizeof(UObject) = 56，所以一个最简单的UObject的大小是56字节。
而UE里的WithinClass有这4种情况：
（图里表示的皆为UClass*类型的对象，名字就是方块里的名字）
UFunction的WithinClass就定义为UClass，表示UFunction只能放在UClass对象下面。
UProperty的WithinClass定义为UField，表示字段下才能有属性。
UClass和UDynamicClass的WithinClass都是UPackage，表示二者只能属于UPackage。
对于其它类型，这个WithinClass类型默认在UObject类里定义为UObject本身，就表示其它类型的对象可以放在任意其它类型对象下面。
本篇主要讲的是Static初始化阶段的最后一步创建出了第一个UClass，自然的Static初始化之后就是程序入口Main函数的执行，因此下一篇我们将开始讲解Main函数入口后开始的类型系统注册过程。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（八）类型系统注册-CoreUObject模块加载</summary>
<pre><code>
引言
前文介绍了Static初始化阶段的最后一步进行的操作，创建出了第一个UClass对象。接着遵循程序启动的流程，本文就开始介绍Main函数入口进来后的流程。
还请注意以下几点：
UE引擎这么大，其初始化从WinMain开始必然要经过一系列繁复的过程，而本章节只关注跟CoreUObject模块里，或者说是UObject系统相关的内容和流程，其他的初始化（比如窗口创建，线程启动，模块加载等）我们暂时忽略，挖个坑留待后续讲解。
同时也为了最简明的说明流程，忽略编辑器的相关函数调用流程内容，只关心Runtime下的流程（就是游戏打包后运行起来的流程。调试的过程是采用源码版引擎，创建个项目，先在Editor下CookContentForWindows，然后在VS里转为Debug配置，编译运行。这样就可以一起跟踪调试Game和Engine的内容。）
流程图里的箭头连接的代码块，不代表源码里就是这么直接相邻，中间仍然可能有其他的代码，只是与主题无关，所以不表示出来。箭头方向向右表示函数的嵌套调用，越向右嵌套越深；箭头向下表示一个函数内部的顺序执行代码块，向下结束表示这个函数完成执行。
引擎整体流程
先大概看一下当运行项目时候的整个引擎启动流程。其中绿色的部分表示有涉及CoreUObject模块。
Static初始化就是指的前文说的收集过程。
以Windows平台为例，WinMain是LaunchWindows.cpp里定义的程序入口。
int32 WINAPI WinMain( _In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char*, _In_ int32 nCmdShow )
{
    //...
    ErrorLevel = GuardedMain( CmdLine, hInInstance, hPrevInstance, nCmdShow );
    //...
    FEngineLoop::AppExit(); //程序的退出
    //...
    return ErrorLevel;
}
GuardedMain是真正的实现程序循环的地方。其中Engine开头的函数内部其实只是简单的转调一个全局的GEngineLoop的内部函数。
FEngineLoop GEngineLoop;
int32 GuardedMain( const TCHAR* CmdLine, HINSTANCE hInInstance, HINSTANCE hPrevInstance, int32 nCmdShow )
{
   // make sure GEngineLoop::Exit() is always called.
    struct EngineLoopCleanupGuard 
    { 
        ~EngineLoopCleanupGuard()
        {
            EngineExit();   //保证在函数退出后能调用    转向 GEngineLoop.Exit();
        }
    } CleanupGuard;
    //...
    int32 ErrorLevel = EnginePreInit( CmdLine );    //预初始化  转向 GEngineLoop.PreInit( CmdLine );
    //...
#if WITH_EDITOR
    if (GIsEditor)
    {
        ErrorLevel = EditorInit(GEngineLoop);   //编辑器有其初始化版本
    }
    else
#endif
    {
        ErrorLevel = EngineInit();   //Runtime下的初始化    转向 GEngineLoop.Init();
    }
    //...
    while( !GIsRequestingExit )
    {
        EngineTick();   //无限循环的Tick    转向 GEngineLoop.Tick();
    }
    #if WITH_EDITOR
    if( GIsEditor )
    {
        EditorExit();   //编辑器的退出
    }
#endif
    return ErrorLevel;
}
FEngineLoop::PreInit是我们关心的涉及UObject启动的最开始的地方。
FEngineLoop::PreInit
我们知道，UE是建立在UObject对象系统上的，所以引擎里别的模块想要启动加载起来，就得先把CoreUObject模块初始化完成。因此引擎循环的预初始化部分就得开始加载CoreUObject了。
int32 FEngineLoop::PreInit(const TCHAR* CmdLine)
{
    //...
    LoadCoreModules();  //加载CoreUObject模块
    //...
    //LoadPreInitModules();   //加载一些PreInit的模块，比如Engine，Renderer
    //...
    AppInit();  //程序初始化
    //...
    ProcessNewlyLoadedUObjects();   //处理最近加载的对象
    //...
    //LoadStartupModules();   //自己写的LoadingPhase为PreDefault的模块在这个时候加载
    //...
    GUObjectArray.CloseDisregardForGC();    //对象池启用，最开始是关闭的
    //...
    //NotifyRegistrationComplete();   //注册完成事件通知，完成Package加载
}
从这个预初始化的流程可以看出，最先加载的是CoreUObject。 其中的LoadCoreModules()内部调用FModuleManager::Get().LoadModule(TEXT("CoreUObject"))，会接着去触发FCoreUObjectModule::StartupModule():
class FCoreUObjectModule : public FDefaultModuleImpl
{
    virtual void StartupModule() override
    {
        // Register all classes that have been loaded so far. This is required for CVars to work.
        UClassRegisterAllCompiledInClasses();   //注册所有编译进来的类，此刻大概有1728多个
        void InitUObject();
        FCoreDelegates::OnInit.AddStatic(InitUObject);  //先注册个回调，后续会在AppInit里被调用
        //...
    }
}
UClassRegisterAllCompiledInClasses
展开后是：
void UClassRegisterAllCompiledInClasses()
{
    TArray<FFieldCompiledInInfo*>& DeferredClassRegistration = GetDeferredClassRegistration();
    for (const FFieldCompiledInInfo* Class : DeferredClassRegistration)
    {
        //这里的Class其实是TClassCompiledInDefer<TClass>
        UClass* RegisteredClass = Class->Register();    //return TClass::StaticClass();
    }
    DeferredClassRegistration.Empty();  //前面返回的是引用，因此这里可以清空数据。
}
//...
static TArray<FFieldCompiledInInfo*>& GetDeferredClassRegistration()    //返回可变引用
{
    static TArray<FFieldCompiledInInfo*> DeferredClassRegistration; //单件模式
    return DeferredClassRegistration;
}
想看懂这里的逻辑需要回顾提醒的有（忘了的请翻阅前三篇）：
GetDeferredClassRegistration()里的元素是之前收集文章里讲的静态初始化的时候添加进去的，在XXX.gen.cpp里用static TClassCompiledInDefer这种形式添加。
TClassCompiledInDefer<TClass>::Register()内部只是简单的转调TClass::StaticClass()。
TClass::StaticClass()是在XXX.generated.h里的DECLARE_CLASS宏里定义的，内部只是简单的转到GetPrivateStaticClass(TPackage)。
GetPrivateStaticClass(TPackage)的函数是实现是在IMPLEMENT_CLASS宏里。其内部会真正调用到GetPrivateStaticClassBody。这个函数的内部会创建出UClass对象并调用Register()，在上篇已经具体讲解过了。
总结这里的逻辑就是对之前收集到的所有的XXX.gen.cpp里定义的类，都触发一次其UClass的构造，其实也只有UObject比较特殊，会在Static初始化的时候就触发构造。因此这个过程其实是类型系统里每一个类的UClass的创建过程。
这个函数会被调用多次，在后续的ProcessNewlyLoadedUObjects的里仍然会触发该调用。在FCoreUObjectModule::StartupModule()的这次调用是最先的，这个时候加载编译进来的的类都是引擎启动一开始就链接进来的。
思考：猜猜看最先生成的是哪几个类？
通过对关键代码的增加Log打印（比如在GetPrivateStaticClassBody的最后打印）， 朋友们可能会发现在Editor模式和Runtime模式下，各类的UClass可能会不太一样。这一方面原因是因为dll链接加载的方式顺序不一样，另一方面也是因为static变量的初始化顺序是不确定的，所以会造成进来的FFieldCompiledInInfo顺序不一样。但这其实也没太多影响，因为UE的代码里，有大量的防护性代码去加载前置所需要的类。另一方面，因为这个阶段生成的UClass，也只有SuperStruct和WithinClass之间的依赖，所以一定的顺序不定也没有关系。Static初始化的“Object”Class是最先的，Editor模式下会先加载CoreUObject模块和其他引擎模块，最后才是Hello模块（原因其实是编辑器的exe启动了然后去加载Hello.dll）。而打包后的游戏Runtime就反了过来，会先加载Hello模块，然后才是CoreUObject模块（原因其实是Hello.exe启动后内部加载其他dll）。所以static变量初始化的顺序其实大体上是越顶层的dll会越先被初始化。
附一下CoreUObject里面的各UClass来混个眼熟，反正也不多：
//Static初始化:
Object
//CoreUObject:
GCObjectReferencer，TextBuffer，Field，Struct，ScriptStruct，Class，Package，Function，DelegateFunction，DynamicClass，PackageMap，Enum，EnumProperty，Property，Interface，LinkerPlaceholderClass，LinkerPlaceholderExportObject，LinkerPlaceholderFunction，MetaData，ObjectRedirector，ArrayProperty，ObjectPropertyBase，BoolProperty，ByteProperty，NumericProperty，ClassProperty，ObjectProperty，DelegateProperty，DoubleProperty，FloatProperty，IntProperty，Int16Property，Int64Property，Int8Property，InterfaceProperty，LazyObjectProperty，MapProperty，MulticastDelegateProperty，NameProperty，SetProperty，SoftClassProperty，SoftObjectProperty，StrProperty，StructProperty，UInt16Property，UInt32Property，UInt64Property，WeakObjectProperty，TextProperty
思考：Struct和Enum的注册为何在这一个阶段无体现？
在此阶段，我们好像没有看见在模块里定义的结构和枚举有参与此阶段的注册。其实是因为结构在注册后生成的元数据信息保存的对象是UScriptStruct，枚举对应的是UEnum，类对应的是UClass。 虽然我们在上篇说构造出来的第一个UClass也是一个UObject，但其实除了在Native编译进来的UClass，其他的UObject的构造都得需要有其对应的UClass的辅助，因为UClass里保存了类的构造函数指针。所以如果想构造出UScriptStruct和UEnum对象，就必须先有描述这两个类元数据信息的UClass。而这两个名为“ScriptStruct”和“Enum”的UClass在上述的CoreUObject模块加载里已经完成了。所以就不需要再做啥了。因此在这个阶段，其实已经是加载了所有基本的类型，因为类型就是用UClass描述。
描述对象类型的只有UClass，UScriptStruct和UEnum是两个保存结构和枚举元数据信息的对象，而构造对象就需要先有其UClass。
讲到这，希望大家好好领悟这一句话：
UObject对象的类型是UClass，而UClass是个UObject对象。
总结
篇幅所限，本篇其实才刚刚讲了PreInit里面的LoadCoreModules()，这一步骤的目的主要是为了把CoreUObject里面定义的类的UClass都给先构建出来。但是其实这些UClass对象内部的值还没有完成初始化设置，因此下一个步骤的AppInit()和ProcessNewlyLoadedUObjects()还会继续这个注册的步程。下篇再来讲解AppInit()里的道道。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（九）类型系统注册-InitUObject</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/58244447
引言
在上文中，我们讲解了CoreUObject模块的加载用UClassRegisterAllCompiledInClasses来生成各编译进来的类的UClass*对象，这些UClass*对象的数据还只是比较简单的版本，只调用过构造函数、设定了SuperStruct和ClassWithin。在这一步之后呢，我们继续按照流程，介绍跟UObject注册相关的FEngineLoop::AppInit。
AppInit
程序的Init里做的事情比较简单，关键是最后一步用一个多播委托通知了程序初始化事件，让别的代码有机会继续进行一些初始化工作。
bool FEngineLoop::AppInit()
{
    //...做一些其他程序入口的初始化工作
    FCoreDelegates::OnInit.Broadcast(); //在前文注册的委托，在CoreUOject模块加载的时候指向了InitUObject
    return true;
}
InitUObject
继续跟踪代码：
void InitUObject()
{
    //...
    FCoreDelegates::OnExit.AddStatic(StaticExit);   //注册退出的事件
    //注册模块加载的
    FModuleManager::Get().OnProcessLoadedObjectsCallback().AddStatic(ProcessNewlyLoadedUObjects);
    //...
    StaticUObjectInit();//调用另一个函数
}
这里的重点是ProcessNewlyLoadedUObjects的注册，这个函数的构造生成类型系统一个非常重要的函数（下文讲解）。我们知道，UE的组织形式是Module，一个Module编译后可以生成一个dll。dll是可以动态加载的，因此如果在引擎初始化结束后，继续动态加载一个模块（即dll)，根据C++机制，会触发dll里面的static变量初始化。因此元数据信息就又收集到了一些。我们就需要继续利用这些元数据信息来为这个新dll里定义的类构造类型的UClass*对象。总而言之，注册这个事件的目的是让新的模块在加载完毕后，让我们为dll里的native类构造类型对象。一个非常重要要知道的是，这里隐含的另一个意思是ProcessNewlyLoadedUObjects有可能会被调用多次。
StaticUObjectInit
void StaticUObjectInit()
{
    UObjectBaseInit();  //继续转发
    //最后，创建临时包
    GObjTransientPkg = NewObject<UPackage>(nullptr, TEXT("/Engine/Transient"), RF_Transient);
    GObjTransientPkg->AddToRoot();  //这个临时包总不会释放
    //...
}
//...
template< class T >
T* NewObject(UObject* Outer = (UObject*)GetTransientPackage())
{
    //...
}
继续转发调用，但我们发现在UObjectBaseInit初始化结束后，就已经可以开始NewObject了，标志着整个UObject系统的成功创建！GObjTransientPkg是个全局变量，所有没有Outer的对象都会放在这个包里。我们在NewObject的时候，如果不提供Outer，则会返回这个临时包，符合了UObject对象必须在UPackage里的一贯基本原则。
UObjectBaseInit
void UObjectBaseInit()
{
    //...
    GUObjectAllocator.AllocatePermanentObjectPool(SizeOfPermanentObjectPool);//初始化对象分配器
    GUObjectArray.AllocateObjectPool(MaxUObjects, MaxObjectsNotConsideredByGC, bPreAllocateUObjectArray);//初始化对象管理数组
    void InitAsyncThread();
    InitAsyncThread();  //初始化Package(uasset)的异步加载线程
    Internal::GObjInitialized = true;   //指定UObject系统初始化完毕
    UObjectProcessRegistrants();    //处理注册项
    //...
}
这个函数主要做了4件事： 1. 初始化UObject的内存分配存储系统和对象的Hash系统，这部分在下一个大章节讲解。 2. 创建了异步加载线程，用来后续Package(uasset)的加载。 3. GObjInitialized=true，这样在后续就可以用bool UObjectInitialized()来判断对象系统是否可用。 4. 继续转发到UObjectProcessRegistrants来把注册项一一处理。
UObjectProcessRegistrants
static void DequeuePendingAutoRegistrants(TArray<FPendingRegistrant>& OutPendingRegistrants)
{
    FPendingRegistrant* NextPendingRegistrant = GFirstPendingRegistrant;
    GFirstPendingRegistrant = NULL;
    GLastPendingRegistrant = NULL;
    while (NextPendingRegistrant)
    {
        FPendingRegistrant* PendingRegistrant = NextPendingRegistrant;
        OutPendingRegistrants.Add(*PendingRegistrant);
        NextPendingRegistrant = PendingRegistrant->NextAutoRegister;
        delete PendingRegistrant;
    };
}
static void UObjectProcessRegistrants()
{
    TArray<FPendingRegistrant> PendingRegistrants;
    DequeuePendingAutoRegistrants(PendingRegistrants);  //从链表中提取注册项列表
    for(int32 RegistrantIndex = 0;RegistrantIndex < PendingRegistrants.Num();++RegistrantIndex)
    {
        const FPendingRegistrant& PendingRegistrant = PendingRegistrants[RegistrantIndex];
        UObjectForceRegistration(PendingRegistrant.Object); //真正的注册
        DequeuePendingAutoRegistrants(PendingRegistrants);  //继续尝试提取
    }
}
可以看出这个函数的主要目的是从GFirstPendingRegistrant和GLastPendingRegistrant定义的链表抽取出来FPendingRegistrant的列表，然后一一用UObjectForceRegistration来注册。但是要注意在每一项注册之后，都要重复调用DequeuePendingAutoRegistrants一下来继续提取，这么做是因为在真正注册一个UObject的时候（后文谈到创建CDO和加载Package有可能引用到别的模块里的东西)，里面有可能触发另一个Module的加载，从而导致有新的注册项进来。所以就需要不断的提取注册直到把所有处理完。
UObjectForceRegistration
void UObjectForceRegistration(UObjectBase* Object)
{
    TMap<UObjectBase*, FPendingRegistrantInfo>& PendingRegistrants = FPendingRegistrantInfo::GetMap();//得到对象的注册信息
    FPendingRegistrantInfo* Info = PendingRegistrants.Find(Object);
    if (Info)   //有可能为空，因为之前已经被注册过了
    {
        const TCHAR* PackageName = Info->PackageName;//对象所在的Package
        const TCHAR* Name = Info->Name; //对象名字
        PendingRegistrants.Remove(Object);//删除
        Object->DeferredRegister(UClass::StaticClass(),PackageName,Name);//延迟注册
    }
}
需要注意的是，UObjectForceRegistration这个函数有可能在多个地方调用：
在UObjectProcessRegistrants里对一个个对象手动进行注册。
UClass::CreateDefaultObject()内部用UObjectForceRegistration(ParentClass)来确认基类已经注册完成。 3. UE4CodeGen_Private::ConstructUClass()等构造类型对象的函数里用UObjectForceRegistration(NewClass)来保证该对象已经注册。
所以，在重复的调用的时候，需要先判断是否PendingRegistrants里还存在该元素。
UObjectBase::DeferredRegister
void UObjectBase::DeferredRegister(UClass *UClassStaticClass,const TCHAR* PackageName,const TCHAR* InName)
{
    // Set object properties.
    UPackage* Package = CreatePackage(nullptr, PackageName);    //创建属于的Package
    Package->SetPackageFlags(PKG_CompiledIn);
    OuterPrivate = Package; //设定Outer到该Package
    ClassPrivate = UClassStaticClass;   //设定属于的UClass*类型
    // Add to the global object table.
    AddObject(FName(InName), EInternalObjectFlags::None);   //注册该对象的名字
}
void UObjectBase::AddObject(FName InName, EInternalObjectFlags InSetInternalFlags)
{
    NamePrivate = InName;   //设定对象的名字
    //...
    //AllocateUObjectIndexForCurrentThread(this);
    //HashObject(this);
}
DeferredRegister其实才是对象真正注册的地方。很多朋友或许会疑惑，我们一直说注册注册，但具体什么是注册呢。DeferredRegister这个名字的包含的两个意思：
Deferred是延迟的意思，区分于之前的UObjectBase::Register，延迟的意思是在对象系统初始化（GUObjectAllocator和GUObjectArray）之后的注册。Register的时候还不能正常NewObject和加载Package，而初始化之后这个阶段就可以开始正常的使用UObject系统的功能了。所以这里面才可以开始CreatePackage。
Register注册，确定一点的意思是对代码里的class生成相应的UClass*对象并添加（注册）到全局对象数组里。
所以总结起来这里所做的是创建出UClass*的Outer指向的Package，并设置ClassPrivate（这里都是UClass*对象，所以其实都是UClass::StaticClass()）。然后在AddObject里设置NamePrivate。因此这步之后这些一个个UClass*对象才有名字，之间的联系才算完整。 但同时也需要注意的是，这些UClass*对象里仍然没有UProperty和UFunciton，下一篇来讲解这些的构造生成。
总结
本篇主要是讲解了AppInit阶段里跟UObject有关的InitUObject操作，其中按顺序重要的操作有：
ProcessNewlyLoadedUObjects回调的注册，让后续模块加载后可以调用该函数。
对象存储分配系统初始化：GUObjectAllocator和GUObjectArray初始化。
UObjectProcessRegistrants里对每一项进行注册，创建Package，设置OuterPrivate，ClassPrivate，NamePrivate，并添加到全局对象数组里。
创建GObjTransientPkg临时包用来存放以后其他的对象。
到现在，我们就可以继续来总结下内存中的UClass*的互相关系。虽然各UClass*对象里面还有UProperty和UFuntion对象还没有创建，也还没有设置完成。但是对象之间互相的联系（OuterPrivate，ClassPrivate，SuperStruct，NamePrivate）这些值就已经设置完毕了。所以，朋友们，让我们闭上眼，在脑海里回顾一下，迄今为止构造的这些UClass*对象、各种UPackage对象、还有我们以后代码里自己创建的类和对象，它们的从属关系，和类型关系又是怎么样的呢？
SuperStruct
SuperStruct主要是用在UClass*对象之间表示类型的继承关系。UClass*对象和我们在代码里定义class是一一对应的通过SuperStruct组织形成了一棵类型树。 而对象的类型关系就是通过ClassPrivate来表达的了。
ClassPrivate
读者朋友们可以根据此图来验证一下自己的理解是否正确。
特别需要主要的是名为“Class”的UClass*对象，其是通过UClass::StaticClass()生成创建的，它的ClassPrivate指向了自身！就像只衔尾蛇一样，这是个特殊情况，通过此可以判断一个对象是否是UClass本身。
UObject类本身类型关系也是用UClass来表示的。
图上并没有列出各UClass*拥有的ClassDefaultObject，一是因为后续序列化再讲解，二是因为其不过也是个普通对象而已。
各UPackage也不过是个UObject对象。所以虽然说我们创建的对象的Outer一般是UPackage，但是也可以是其他的普通Outer，从而用Outer的不断指向来组成一颗从属树。注意和Owner这个概念区分，Owner是Actor里定义的AActor* Owner变量，用在网络的领域里用来确定Relevant相关性的。
同时也让我们通过源码里的数据变量进一步归纳：
class COREUOBJECT_API UObjectBase
{
private:
    EObjectFlags    ObjectFlags;    //对象标志，定义了对象各种状态和特征
    int32           InternalIndex;  //对象的存储索引
    UClass*         ClassPrivate;
    FName           NamePrivate;
    UObject*        OuterPrivate;
};
class COREUOBJECT_API UStruct : public UField
{
private:
    UStruct* SuperStruct;
};
在内存中对象们通过这4个变量来定义了各种关系：
NamePrivate：定义了对象的名字
OuterPrivate：定义了对象的从属关系
ClassPrivate：定义了对象的类型关系
SuperStruct：定义了类型的继承关系
System.out.println("Hello to see U!");
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（十）类型系统构造-再次触发</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/58868952
引言
上文讲解到了UObject系统的初始化和各UClass*对象的初级构造，但是这还没有完成，UClass*对象里还有很多东西没有塞进去。本文将继续FEngineLoop::PreInit()里AppInit的下一个非常重要的函数ProcessNewlyLoadedUObjects。同时非常需要注意的是ProcessNewlyLoadedUObjects会在模块加载后再次触发调用，所以脑袋里一定要时刻意识到两点，一是它是重复调用多次的，二是它的内部流程是一个完整的流程。
ProcessNewlyLoadedUObjects
void ProcessNewlyLoadedUObjects()
{
    UClassRegisterAllCompiledInClasses();   //为代码里定义的那些类生成UClass*
    //提取收集到的注册项信息
    const TArray<UClass* (*)()>& DeferredCompiledInRegistration=GetDeferredCompiledInRegistration();
    const TArray<FPendingStructRegistrant>& DeferredCompiledInStructRegistration=GetDeferredCompiledInStructRegistration();
    const TArray<FPendingEnumRegistrant>& DeferredCompiledInEnumRegistration=GetDeferredCompiledInEnumRegistration();
    //有待注册项就继续循环注册
    bool bNewUObjects = false;
    while (GFirstPendingRegistrant || 
    DeferredCompiledInRegistration.Num() || 
    DeferredCompiledInStructRegistration.Num() || 
    DeferredCompiledInEnumRegistration.Num())
    {
        bNewUObjects = true;
        UObjectProcessRegistrants();    //注册UClass*
        UObjectLoadAllCompiledInStructs();  //为代码里的枚举和结构构造类型对象
        UObjectLoadAllCompiledInDefaultProperties();    //为代码里的类继续构造UClass对象
    }
    if (bNewUObjects && !GIsInitialLoad)
    {
        UClass::AssembleReferenceTokenStreams();    //构造引用记号流，为后续GC用
    }
}
代码里的结构也比较简单，还有一些我们之前介绍过的函数，忘了的朋友请回顾前文，特别是信息收集，因为此刻就开始真正使用这些数据了。
UClassRegisterAllCompiledInClasses在前文介绍过，里面主要是为每一个编译进来的class调用TClass::StaticClass()来构造出UClass*对象。
GetDeferredCompiledInRegistration()是之前信息收集的时候static FCompiledInDefer变量初始化时收集到的全局数组，和定义的class一对一。
GetDeferredCompiledInStructRegistration()是之前信息收集的时候static FCompiledInDeferStruct变量初始化时收集到的全局数组，和定义的struct一对一。
GetDeferredCompiledInEnumRegistration()是之前信息收集的时候static FCompiledInDeferEnum变量初始化时收集到的全局数组，和定义的enum一对一。
UObjectProcessRegistrants()前文刚讲过，为之前生成的UClass*注册，生成其Package。这里调用的目的是在后续的操作之前确保内存里已经把相关的类型UClass*对象都已经注册完毕。
UObjectLoadAllCompiledInStructs()里为enum和struct分别生成UEnum和UScriptStruct对象。后文详细讲解。
UObjectLoadAllCompiledInDefaultProperties()里为UClass*们继续构造和创建类默认对象(CDO)。后文详细讲解。
最后一步判断如果有新UClass*对象生成了，并且现在不在初始化载入阶段（GIsInitialLoad初始=true，只有在后续开启GC后才=false表示初始化载入过程结束了），用AssembleReferenceTokenStreams为UClass创建引用记号流（一种辅助GC分析对象引用的数据结构，挖坑留待以后讲GC的时候讲解。）。所以第一次的FEngineLoop::PreInit()里的ProcessNewlyLoadedUObjects并不会触发AssembleReferenceTokenStreams的调用但也会在后续的GUObjectArray.CloseDisregardForGC()里面调用AssembleReferenceTokenStreams。只有后续模块动态加载后触发的ProcessNewlyLoadedUObjects才会AssembleReferenceTokenStreams。通过这个判断保证了在两种情况下，AssembleReferenceTokenStreams只会被调用一次。
思考：为何ProcessNewlyLoadedUObjects函数里前面的步骤总有一种既视感？
抛开后面的两个Load函数，前面的UClassRegisterAllCompiledInClasses()和UObjectProcessRegistrants()都是我们前面两篇文章里讲过的：
Static初始化阶段，会调用UClassRegisterAllCompiledInClasses()来生成UClass*。
CoreUObject模块加载阶段，先初始化一下对象分配系统。GUObjectAllocator和GUObjectArray。
CoreUObject模块加载阶段，接着调用UObjectProcessRegistrants()来注册UClass*。
因为此刻当然对象分配系统已经初始化过了，所以这二者的调用顺序和ProcessNewlyLoadedUObjects里的是一样的！原因很简单，每一个模块dll的加载，我们其实都应该为他安排一次一条龙的类型树的构建服务，所以这个构造UClass*的过程都要依照此流程走一遍。当然这个过程也是可以批量合并的，在引擎启动的时候，已经加载了很多模块dll，因此反正也是先执行了前面这两步。
UObjectLoadAllCompiledInStructs
让我们继续深挖，类型UClass*都有了，这一步开始真正的构造UEnum和UScriptStruct。
static void UObjectLoadAllCompiledInStructs()
{
    TArray<FPendingEnumRegistrant> PendingEnumRegistrants = MoveTemp(GetDeferredCompiledInEnumRegistration());
    for (const FPendingEnumRegistrant& EnumRegistrant : PendingEnumRegistrants)
    {
        CreatePackage(nullptr, EnumRegistrant.PackageName); //创建其所属于的Package
    }
    TArray<FPendingStructRegistrant> PendingStructRegistrants = MoveTemp(GetDeferredCompiledInStructRegistration());
    for (const FPendingStructRegistrant& StructRegistrant : PendingStructRegistrants)
    {
        CreatePackage(nullptr, StructRegistrant.PackageName);   //创建其所属于的Package
    }
    for (const FPendingEnumRegistrant& EnumRegistrant : PendingEnumRegistrants)
    {
        EnumRegistrant.RegisterFn();    //调用生成代码里Z_Construct_UEnum_Hello_EMyEnum
    }
    for (const FPendingStructRegistrant& StructRegistrant : PendingStructRegistrants)
    {
        StructRegistrant.RegisterFn(); //调用生成代码里Z_Construct_UScriptStruct_FMyStruct
    }
}
开头的两个数组就不赘述了。这个代码写得也很有意思：
先创建EnumRegistrant.PackageName再创建StructRegistrant.PackageName。这两个名字值都是在生成代码里定义的，同UClass一样，表示了其所在的Package。注意的是，CreatePackage的里面总是会先查找该名字的Package是否已经存在，不会重复创建。
MoveTemp会触发TArray的右移引用赋值，把源数组里的数据迁移到目标数组里去。所以外层的while判断值才会改变。
先enum再struct的调用其注册函数RegisterFn()。RegisterFn是个函数指针，指向生成代码里Z_Construct开头的函数，用来真正构造出UEnum和UScriptStruct对象。
有意思的是，顺序总是先enum再struct。其原因其实是因为更基础的类型总是先构造。代码里enum不能嵌套struct，但struct里却可以包含enum。所以在struct里包含一个enum变量的时候，构造UScriptStruct时就需要用enum名字查找到其相应的UEnum*对象，因此当然希望UEnum在前面都先构造好了。有位朋友问了，那如果struct里包含一个UMyClass*变量怎么办？不怎么办，因为各Class所属于的UClass*对象都已经在前面的UObjectProcessRegistrants()里注册好了，所有的对象引用类型反正只是通过Class名字来查找到UClass*，因此UClass*对象就算还没有真正构造完毕也没有关系，反正只要能用名字查找到就好了！
UObjectLoadAllCompiledInDefaultProperties
针对UClass*对象的构造的重头戏来了：
static void UObjectLoadAllCompiledInDefaultProperties()
{
    static FName LongEnginePackageName(TEXT("/Script/Engine")); //引擎包的名字
    if(GetDeferredCompiledInRegistration().Num() <= 0) return;
    TArray<UClass*> NewClassesInCoreUObject;
    TArray<UClass*> NewClassesInEngine;
    TArray<UClass*> NewClasses;
    TArray<UClass* (*)()> PendingRegistrants = MoveTemp(GetDeferredCompiledInRegistration());
    for (UClass* (*Registrant)() : PendingRegistrants) 
    {
        UClass* Class = Registrant();//调用生成代码里的Z_Construct_UClass_UMyClass创建UClass*
        //按照所属于的Package分到3个数组里
        if (Class->GetOutermost()->GetFName() == GLongCoreUObjectPackageName)
        {
            NewClassesInCoreUObject.Add(Class);
        }
        else if (Class->GetOutermost()->GetFName() == LongEnginePackageName)
        {
            NewClassesInEngine.Add(Class);
        }
        else
        {
            NewClasses.Add(Class);
        }
    }
    //分别构造CDO对象
    for (UClass* Class : NewClassesInCoreUObject)   { Class->GetDefaultObject(); }
    for (UClass* Class : NewClassesInEngine)        { Class->GetDefaultObject(); }
    for (UClass* Class : NewClasses)                { Class->GetDefaultObject(); }
}
步骤共有：
从GetDeferredCompiledInRegistration()的源数组里MoveTemp出来遍历。
依次调用Registrant()来继续构造UClass*，这个函数指向了生成代码里形如Z_Construct_UClass_UMyClass的函数。
对生成的UClass*对象，依照属于的Package划分到3个数组里。
对3个数组分别依次手动构造CDO对象。这三个数组的顺序是：CoreUObject、Engine和其他。按照此顺序构造的原因是根据依赖关系。构造CDO的过程，有可能触发uassset的加载和UObject构造函数的调用，所以就可能在内部触发其他Package里对象的加载构造。CoreUObject最底层（它不会引用其他的Package里的对象）、Engine次之（它有可能引用底层的对象）、其他（就不确定会引用啥了）。所以依照此顺序能避免依赖倒置，从而减少重复调用查找。
我们知道，代码里Class里可以包含结构和枚举，因此UObjectLoadAllCompiledInDefaultProperties被安排到UObjectLoadAllCompiledInStructs之后，可以让此时构造的UClass*对象能够通过enum和struct的类型名字查找到相应的UEnum*和UScriptStruct*对象。顺序还是很讲究的。
CloseDisregardForGC
UClass*构造之后的还有个尾巴操作，此时可以开启GC了。因为之前一直都是在初始化载入阶段，这个阶段构造的类型UClass*对象和CDO对象，及其属于的UPackage对象，都是属于引擎底层的必要对象，它们是只有在游戏推出的时候才会销毁，因此它们就不属GC管了——GC一开始也是关着的：OpenForDisregardForGC=true。在类型系统都构建完了之后，就可以放心的打开GC了，因为后续就有可能NewObject来生成对象了。
void FUObjectArray::CloseDisregardForGC()
{
    if (!GIsRequestingExit)
    {
        ProcessNewlyLoadedUObjects();//之前仍然有可能加载了别的模块dll
    }
    UClass::AssembleReferenceTokenStreams(); //此时才是真正的第一次为所有的UClass\*构建引用记号流
    //...
    OpenForDisregardForGC = false;
    GIsInitialLoad = false;//初始化载入阶段结束
}
代码省略了其他无关操作，关于GC的内容挖坑后续讲解。此时提前先了解一下，以对全局流程有个总览。
总结
现在到此为止，我们能了解到内存中已经构造出来了各类型表达对象，之前描述过的各个信息收集阶段收集到各种信息也都得到了消费应用，让我们来梳理一下：
原谅我捉急的画图能力，和这么多的线绕来绕去，我尽力了。 1. 大部分是不言自明的，从左到右是类型信息的收集和消费过程。从上到下是依据代码的执行顺序。 2. 红色箭头代表数据的产生添加，蓝色箭头代表数据的消费使用。这二者一起表达了类型信息的数据流向。 3. 浅蓝色箭头和矩形，代表内存中UClass*以及类型对象的创建和构造。 4. 信息收集里黄色的3个矩形，代表它们的数据会一直在内存中，用来做查找用，不会被清空。
篇幅有限，关于enum、struct、class的RegisterFn调用，生成代码里的Z_Construct_XXX的调用，还没有讲解，留待下篇讲解。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（十一）类型系统构造-构造绑定链接</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/59553490
引言
在上篇介绍了类型注册的最后阶段，为每一个enum、struct、class都进行了一次RegisterFn调用（忘了调用时机的请翻阅前文)，而这些RegisterFn其实都指向生成代码里的函数。本篇就来讲解这个里面的类型对象生成和构造。 按照生成顺序，也是调用顺序，一一讲解UEnum和UScriptStruct的生成，以及UClass的继续构造。 注意：
代码里去除掉HotReload和MetaData的部分（那只是给编辑器提供额外信息的）。
代码里各Params的定义可到“代码生成重构”篇去查看，或者自己打开源码对照，都比较简单，就不列出来了。
UEnum
先从软的开始捏，这是用来测试的MyEnum：
UENUM(Blueprintable,meta=(EnumDisplayNameFn="GetMyEnumDisplayName"))
enum class MyEnum:uint8
{
    Dance   UMETA(DisplayName = "MyDance"),
    Rain    UMETA(DisplayName = "MyRain"),
    Song    UMETA(DisplayName = "MySong")
};
FText GetMyEnumDisplayName(int32 val)   //可以提供一个自定义函数给枚举来额外显示
{
    MyEnum enumValue = (MyEnum)val;
    switch (enumValue)
    {
    case MyEnum::Dance:
        return FText::FromString(TEXT("Hello_Dance"));
    case MyEnum::Rain:
        return FText::FromString(TEXT("Hello_Rain"));
    case MyEnum::Song:
        return FText::FromString(TEXT("Hello_Song"));
    default:
        return FText::FromString(TEXT("Invalid MyEnum"));
    }
}
生成代码的关键：
static UEnum* MyEnum_StaticEnum()   //RegisterFn指向该函数
{
    static UEnum* Singleton = nullptr;
    if (!Singleton)
    {
        Singleton = GetStaticEnum(Z_Construct_UEnum_Hello_MyEnum, Z_Construct_UPackage__Script_Hello(), TEXT("MyEnum"));
    }
    return Singleton;
}
static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_MyEnum(MyEnum_StaticEnum, TEXT("/Script/Hello"), TEXT("MyEnum"), false, nullptr, nullptr);    //收集点
UEnum* Z_Construct_UEnum_Hello_MyEnum() //实际调用点
{
    static UEnum* ReturnEnum = nullptr;
    if (!ReturnEnum)
    {
        static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
            { "MyEnum::Dance", (int64)MyEnum::Dance }, //注意枚举项的名字是以"枚举::"开头的
            { "MyEnum::Rain", (int64)MyEnum::Rain },
            { "MyEnum::Song", (int64)MyEnum::Song },
        };
        static const UE4CodeGen_Private::FEnumParams EnumParams = {
            (UObject*(*)())Z_Construct_UPackage__Script_Hello,
            UE4CodeGen_Private::EDynamicType::NotDynamic,
            "MyEnum",
            RF_Public|RF_Transient|RF_MarkAsNative,
            GetMyEnumDisplayName,//一般为nullptr，我们自定义了一个，所以这里才有
            (uint8)UEnum::ECppForm::EnumClass,
            "MyEnum",
            Enumerators,
            ARRAY_COUNT(Enumerators),
            METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
        };
        UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);//最终生成点
    }
    return ReturnEnum;
}
生成代码里的收集点，把MyEnum_StaticEnum注册给了RegisterFn。调用的时候，内部的GetStaticEnum会调用参赛里的Z_Construct_UEnum_Hello_MyEnum。而Z_Construct_UEnum_Hello_MyEnum内部其实比较简单，定义了枚举项参数和枚举参数，最终发给UE4CodeGen_Private::ConstructUEnum调用。
void ConstructUEnum(UEnum*& OutEnum, const FEnumParams& Params)
{
    UObject* (*OuterFunc)() = Params.OuterFunc;
    UObject* Outer = OuterFunc ? OuterFunc() : nullptr; //先确保创建Outer
    if (OutEnum) {return;}  //防止重复构造
    UEnum* NewEnum = new (EC_InternalUseOnlyConstructor, Outer, UTF8_TO_TCHAR(Params.NameUTF8), Params.ObjectFlags) UEnum(FObjectInitializer());    //创建一个UEnum
    OutEnum = NewEnum;
    //生成枚举名字值对数组
    TArray<TPair<FName, int64>> EnumNames;
    EnumNames.Reserve(Params.NumEnumerators);
    for (const FEnumeratorParam* Enumerator = Params.EnumeratorParams, *EnumeratorEnd = Enumerator + Params.NumEnumerators; Enumerator != EnumeratorEnd; ++Enumerator)
    {
        EnumNames.Emplace(UTF8_TO_TCHAR(Enumerator->NameUTF8), Enumerator->Value);
    }
    //设置枚举项数组
    NewEnum->SetEnums(EnumNames, (UEnum::ECppForm)Params.CppForm, Params.DynamicType == EDynamicType::NotDynamic);
    NewEnum->CppType = UTF8_TO_TCHAR(Params.CppTypeUTF8);  //cpp名字
    if (Params.DisplayNameFunc)
    {
        NewEnum->SetEnumDisplayNameFn(Params.DisplayNameFunc);  //设置自定义显示名字回调
    }
}
基本上代码都是不言自明的，只有两处需要注意：一是OuterFunc()的调用是用来先确保外界所属于的UPackage存在。二是UEnum的构造，源码里用了重载new的方式，注意不是placement new。这个new的方式定义在DECLARE_CLASS宏中：
/** For internal use only; use StaticConstructObject() to create new objects. */ 
inline void* operator new(const size_t InSize, EInternal InInternalOnly, UObject* InOuter = (UObject*)GetTransientPackage(), FName InName = NAME_None, EObjectFlags InSetFlags = RF_NoFlags) 
{ 
    return StaticAllocateObject(StaticClass(), InOuter, InName, InSetFlags); 
} 
/** For internal use only; use StaticConstructObject() to create new objects. */ 
inline void* operator new( const size_t InSize, EInternal* InMem ) 
{ 
    return (void*)InMem; 
}
所以是会先触发StaticAllocateObject来分配出一块对象内存（简易初始化过的，后续对象分配章节再讲解），接着才会调用UEnum的构造函数，在构造完毕后再往里面填充枚举项。
思考：为什么不用我们常用的NewObject来创建UEnum呢？
实际上，这里如果换成UEnum* NewEnum= NewObject< UEnum>(Outer, UTF8_TO_TCHAR(Params.NameUTF8), Params.ObjectFlags);也是可行的。那么这二者差在哪呢？微乎其微。二者的流程大体都是一样的，只差在FObjectInitializer的值不一样，new构造会调用FObjectInitializer()默认构造函数，而NewObject会调用FObjectInitializer(Result, InTemplate, bCopyTransientsFromClassDefaults, true, InInstanceGraph)。其中差在第4个参数bShouldInitializePropsFromArchetype，前者默认为=false，会略过构造过程中的UClass里属性值初始化的过程。因为enum里也没有属性，所以略过该过程会稍微提高点性能，但也微乎其微啦。
继续往里面看下SetEnums
bool UEnum::SetEnums(TArray<TPair<FName, int64>>& InNames, UEnum::ECppForm InCppForm, bool bAddMaxKeyIfMissing)
{
    if (Names.Num() > 0)
    {
        RemoveNamesFromMasterList();   //去除之前的名字
    }
    Names   = InNames;
    CppForm = InCppForm;
    if (bAddMaxKeyIfMissing)
    {
        if (!ContainsExistingMax())
        {
            FName MaxEnumItem = *GenerateFullEnumName(*(GenerateEnumPrefix() + TEXT("_MAX")));
            if (LookupEnumName(MaxEnumItem) != INDEX_NONE)
            {
                // the MAX identifier is already being used by another enum
                return false;
            }
            Names.Emplace(MaxEnumItem, GetMaxEnumValue() + 1);
        }
    }
    AddNamesToMasterList();
    return true;
}
代码也很简单，enum就是简单呀。有两个操作比较重要：
RemoveNamesFromMasterList和AddNamesToMasterList一起维护UEnum里的static TMap<FName, UEnum*> AllEnumNames;，该数据结构可以允许我们通过一个枚举项名字来搜索到枚举类型。比如通过"MyEnum::Dance"用LookupEnumName来返回枚举的UEnum*。
bAddMaxKeyIfMissing在native的情况下为true，所以在C++里定义的枚举，其实是会自动添加一项形如MyEnum::MyEnum_MAX=最大值+1，方便蓝图中使用。
然后就enum就结束啦！
UScriptStruct
依然来先看下结构的测试代码：
USTRUCT(BlueprintType)
struct HELLO_API FMyStruct
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadWrite)
    float Score;
};
UE里的结构不可继承自c++ struct，但可以继承自USTRUCT标记的struct，里面也不可以添加UFUNCTION。以上的测试代码非常简单，生成代码(为了可读性进行了一些排版调整)：
class UScriptStruct* FMyStruct::StaticStruct()  //RegisterFn指向该函数
{
    static class UScriptStruct* Singleton = NULL;
    if (!Singleton)
    {
        Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMyStruct, Z_Construct_UPackage__Script_Hello(), TEXT("MyStruct"), sizeof(FMyStruct), Get_Z_Construct_UScriptStruct_FMyStruct_CRC());
    }
    return Singleton;
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMyStruct(FMyStruct::StaticStruct, TEXT("/Script/Hello"), TEXT("MyStruct"), false, nullptr, nullptr);     //收集点
static struct FScriptStruct_Hello_StaticRegisterNativesFMyStruct
{
    FScriptStruct_Hello_StaticRegisterNativesFMyStruct()
    {
        UScriptStruct::DeferCppStructOps(FName(TEXT("MyStruct")),new UScriptStruct::TCppStructOps<FMyStruct>);
    }
} ScriptStruct_Hello_StaticRegisterNativesFMyStruct; //收集点
struct Z_Construct_UScriptStruct_FMyStruct_Statics
{
    static void* NewStructOps() //创建结构操作辅助类
    {
        return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMyStruct>();
    }
    //属性参数...
    //结构参数
    static const UE4CodeGen_Private::FStructParams ReturnStructParams= 
    {
        (UObject* (*)())Z_Construct_UPackage__Script_Hello,//Outer
        nullptr,    //构造基类的函数指针
        &NewStructOps,//构造结构操作类的函数指针
        "MyStruct",//结构名字
        RF_Public|RF_Transient|RF_MarkAsNative, //对象标记
        EStructFlags(0x00000201),   //结构标记
        sizeof(FMyStruct),//结构大小
        alignof(FMyStruct), //结构内存对齐
        PropPointers, ARRAY_COUNT(PropPointers) //属性列表
    };
};
UScriptStruct* Z_Construct_UScriptStruct_FMyStruct() //真正的构造实现
{
    static UScriptStruct* ReturnStruct = nullptr;
    if (!ReturnStruct)
    {
        UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FMyStruct_Statics::ReturnStructParams);
    }
    return ReturnStruct;
}
同Enum的套路一样，RegisterFn指向FMyStruct::StaticStruct()函数，其内部会继续调用Z_Construct_UScriptStruct_FMyStruct。最终还是用ConstructUScriptStruct来通过参数生成UScriptStruct。而那些参数我在代码里的注释一看也都明白，结构套结构而已。
void ConstructUScriptStruct(UScriptStruct*& OutStruct, const FStructParams& Params)
{
    UObject* Outer = Params.OuterFunc ? Params.OuterFunc() : nullptr;//构造Outer
    UScriptStruct* Super = Params.SuperFunc ? Params.SuperFunc() : nullptr;//构造SuperStruct
    UScriptStruct::ICppStructOps* StructOps = Params.StructOpsFunc ? Params.StructOpsFunc() : nullptr;//构造结构操作类
    if (OutStruct) {return;}
    //构造UScriptStruct
    UScriptStruct* NewStruct = new(EC_InternalUseOnlyConstructor, Outer, UTF8_TO_TCHAR(Params.NameUTF8), Params.ObjectFlags) UScriptStruct(FObjectInitializer(), Super, StructOps, (EStructFlags)Params.StructFlags, Params.SizeOf, Params.AlignOf);
    OutStruct = NewStruct;
    //构造属性集合
    ConstructUProperties(NewStruct, Params.PropertyArray, Params.NumProperties);
    //链接
    NewStruct->StaticLink();
}
和UEnum一样的模式调用，先依次构造出依赖的Outer、Super和CppStructOps。然后依然是overload new构造出UScriptStruct。但是UScriptStruct的构造函数里多了一步调用PrepareCppStructOps（比较简单提一下，主要是从CppStructOps提出特征然后存在StructFlags里）。 接着的ConstructUProperties是个从属性参数数组里构造出UProperty*数组，在后面构造UClass*的时候也会复用调用到。因此留待后文一起讲解。 所有复合类型（继承于UStruct）都会接着调用StaticLink来链接子属性。关于Link的作用在后文讲解。
ICppStructOps的作用
很多朋友在看源码的时候，可能会对UScriptStruct里定义的ICppStructOps类以及模板子类TCppStructOps<CPPSTRUCT>感到疑惑。其实它们是C++的一种常见的架构模式，用一个虚函数基类定义一些公共操作，再用一个具体模板子类来实现，从而既可以保存类型，又可以有公共操作接口。
针对于UE4这里来说，ICppStructOps就定义了这个结构的一些公共操作。而探测这个C++结构的一些特性就交给了TCppStructOps<CPPSTRUCT>类里的TStructOpsTypeTraits<CPPSTRUCT>。一些C++结构的信息不能通过模板探测出来的，就需要我们手动标记提供了，所以具体的代码是：
template <class CPPSTRUCT>
struct TStructOpsTypeTraitsBase2
{
    enum
    {
        WithZeroConstructor = false, // 0构造，内存清零后就可以了，说明这个结构的默认值就是0
        WithNoInitConstructor = false, // 有个ForceInit的参数的构造，用来专门构造出0值结构来
        WithNoDestructor = false, // 是否没有结构有自定义的析构函数， 如果没有析构的话，DestroyStruct里面就可以省略调用析构函数了。默认是有的。结构如果是pod类型，则肯定没有析构。
        WithCopy = !TIsPODType<CPPSTRUCT>::Value, // 是否结构有自定义的=赋值函数。如果没有的话，在CopyScriptStruct的时候就只需要拷贝内存就可以了
        WithIdenticalViaEquality = false, // 用==来比较结构
        WithIdentical = false, // 有一个自定义的Identical函数来专门用来比较，和WithIdenticalViaEquality互斥
        WithExportTextItem = false, // 有一个ExportTextItem函数来把结构值导出为字符串
        WithImportTextItem = false, // 有一个ImportTextItem函数把字符串导进结构值
        WithAddStructReferencedObjects = false, // 有一个AddStructReferencedObjects函数用来添加结构额外的引用对象
        WithSerializer = false, // 有一个Serialize函数用来序列化
        WithStructuredSerializer = false, // 有一个结构结构Serialize函数用来序列化
        WithPostSerialize = false, // 有一个PostSerialize回调用来在序列化后调用
        WithNetSerializer = false, // 有一个NetSerialize函数用来在网络复制中序列化
        WithNetDeltaSerializer = false, // 有一个NetDeltaSerialize函数用来在之前NetSerialize的基础上只序列化出差异来，一般用在TArray属性上进行优化
        WithSerializeFromMismatchedTag = false, // 有一个SerializeFromMismatchedTag函数用来处理属性tag未匹配到的属性值，一般是在结构进行升级后，但值还是原来的值，这个时候用来把旧值升级到新结构时使用
        WithStructuredSerializeFromMismatchedTag = false, // SerializeFromMismatchedTag的结构版本
        WithPostScriptConstruct = false,// 有一个PostScriptConstruct函数用在蓝图构造脚本后调用
        WithNetSharedSerialization = false, // 指明结构的NetSerialize函数不需要用到UPackageMap
    };
};
template<class CPPSTRUCT>
struct TStructOpsTypeTraits : public TStructOpsTypeTraitsBase2<CPPSTRUCT>
{
};
这些枚举值定义了一个结构的特性，我已经在源码里一一解释了。 说回ICppStructOps里的接口，内部实现大部分都是通过TStructOpsTypeTraits<CPPSTRUCT>的结构来分别调用不同版本的函数。结构的操作可以分为：
构造：HasNoopConstructor、HasZeroConstructor、Construct、HasPostScriptConstruct、PostScriptConstruct、IsAbstract
析构：HasDestructor、Destruct
拷贝：IsPlainOldData、HasCopy、Copy
比较：HasIdentical、Identical
导入导出：HasExportTextItem、ExportTextItem、HasImportTextItem、ImportTextItem
GC：HasAddStructReferencedObjects、AddStructReferencedObjects
序列化：HasSerializer、HasStructuredSerializer、Serialize、HasPostSerialize、PostSerialize、HasNetSerializer、HasNetSharedSerialization、NetSerialize、HasNetDeltaSerializer、NetDeltaSerialize、HasSerializeFromMismatchedTag、HasStructuredSerializeFromMismatchedTag、SerializeFromMismatchedTag、StructuredSerializeFromMismatchedTag
有了ICppStructOps的公共接口，和上面特化的信息，UE4在内部对结构进行构造析构或序列化的时候，就可以选择最优的步骤(比如拷贝的时候只需要直接拷贝内存而不需要调用赋值函数)，在GC的时候，也可以告诉UE4这个结构内部有可能有额外的UObject*对象。从而让UE4实现对该结构实现出更高的性能。
比如对于常见的FVector来说，源码里就定义了这么一个特化来描述其特性：
template<>
struct TStructOpsTypeTraits<FVector> : public TStructOpsTypeTraitsBase2<FVector>
{
    enum 
    {
        WithNoInitConstructor = true,
        WithZeroConstructor = true,
        WithNetSerializer = true,
        WithNetSharedSerialization = true,
        WithSerializer = true,
    };
};
一看我们就知道FVector有个0值构造函数，和有Serializer函数。对于我们自己定义的UStruct，如果有需要，也可以定义这么一个模板特化，来更详细的提供结构信息。
UClass
接着是我们自己最常用的Class和Interface，一起梭哈一把：
UINTERFACE(BlueprintType, Blueprintable)
class HELLO_API UMyInterface:public UInterface
{
    GENERATED_BODY()
};
class IMyInterface
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
        void NativeInterfaceFunc();
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void ImplementableInterfaceFunc();
};
UCLASS(BlueprintType, Blueprintable)
class HELLO_API UMyClass :public UObject, public IMyInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        float Score;
public:
    UFUNCTION(BlueprintCallable, Category = "Hello")
        int32 Func(float param1);    //C++实现，蓝图调用
    UFUNCTION(BlueprintNativeEvent, Category = "Hello")
        void NativeFunc();  //C++实现默认版本，蓝图可重载实现
    UFUNCTION(BlueprintImplementableEvent, Category = "Hello")
        void ImplementableFunc();   //C++不实现，蓝图实现
};
生成的代码的关键部分（做了些排版调整）：
//函数参数...
struct Z_Construct_UClass_UMyClass_Statics
{
    //依赖项列表
    static UObject* (*const DependentSingletons[])()=
    {
        (UObject* (*)())Z_Construct_UClass_UObject,//依赖基类UObject
        (UObject* (*)())Z_Construct_UPackage__Script_Hello,//依赖所属于的Hello模块
    };
    //属性参数...
    //函数参数...
    //接口
    static const UE4CodeGen_Private::FImplementedInterfaceParams InterfaceParams[]= 
    {
        {
            Z_Construct_UClass_UMyInterface_NoRegister,//构造UMyInterface所属的UClass*函数指针
            (int32)VTABLE_OFFSET(UMyClass, IMyInterface),//多重继承的指针偏移
            false   //是否是在蓝图实现
        }
    };
    static const FCppClassTypeInfoStatic StaticCppClassTypeInfo= {
        TCppClassTypeTraits<UMyClass>::IsAbstract,//c++类信息，是否是虚类
    };
    static const UE4CodeGen_Private::FClassParams ClassParams = 
    {
        &UMyClass::StaticClass,//取出UClass*的函数指针
        DependentSingletons, ARRAY_COUNT(DependentSingletons),//依赖项
        0x001000A0u,//类标志
        FuncInfo, ARRAY_COUNT(FuncInfo),//函数列表
        PropPointers, ARRAY_COUNT(PropPointers),//属性列表
        nullptr,//Config文件名
        &StaticCppClassTypeInfo,//c++类信息
        InterfaceParams, ARRAY_COUNT(InterfaceParams)//接口列表
    };
};
UClass* Z_Construct_UClass_UMyClass()
{
    static UClass* OuterClass = nullptr;
    if (!OuterClass)
    {
        UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UMyClass_Statics::ClassParams);
    }
    return OuterClass;
}
IMPLEMENT_CLASS(UMyClass, 4008851639); //收集点
static FCompiledInDefer Z_CompiledInDefer_UClass_UMyClass(Z_Construct_UClass_UMyClass, &UMyClass::StaticClass, TEXT("/Script/Hello"), TEXT("UMyClass"), false, nullptr, nullptr, nullptr); //收集点
Class的信息就比较多了，可以拥有接口、属性和函数。属性和函数在后文讲解，多出来的MyInterface，因为也是个UObject类，所以其实也会对UMyInterface生成一个UClass*对象并添加函数，和UMyClass的模式是一样的，因此不再赘述。但UMyClass因为继承于IMyInterface，因此就要在UMyClass的UClass*里添加额外的接口继承信息。C++里实现interface是用多继承，因此就有对象基类指针偏移的问题（不懂这个的同学请自觉补C++基础的课），于是FImplementedInterfaceParams里每一项就有一个用VTABLE_OFFSET获取的指针偏移，有了Offset就可以根据Obj+Offset来获取IMyInterface*地址，从而调用接口函数，这也是GetInterfaceAddress的逻辑实现。
FCppClassTypeInfoStatic的作用其实和结构的ICppStructOps差不多，都是识别原生C++里的类型信息，但UClass毕竟和UStruct的作用不一样，没有那些纯内存构造析构的操作，也都必然有序列化器，所以FCppClassTypeInfoStatic里目前只有一项bIsAbstract来判断是否该类是虚类。
构造的代码（做了些排版和易读调整）：
void ConstructUClass(UClass*& OutClass, const FClassParams& Params)
{
    if (OutClass && (OutClass->ClassFlags & CLASS_Constructed)) {return;}  //防止重复构造
    for(int i=0;i<Params.NumDependencySingletons;++i)
    {
        Params.DependencySingletonFuncArray[i]();   //构造依赖的对象
    }
    UClass* NewClass = Params.ClassNoRegisterFunc();    //取得先前生成的UClass*，NoRegister是指没有经过DeferRegister
    OutClass = NewClass;
    if (NewClass->ClassFlags & CLASS_Constructed) {return;}//防止重复构造
    UObjectForceRegistration(NewClass); //确保此UClass*已经注册
    NewClass->ClassFlags |= (EClassFlags)(Params.ClassFlags | CLASS_Constructed);//标记已经构造
    if ((NewClass->ClassFlags & CLASS_Intrinsic) != CLASS_Intrinsic)
    {
        check((NewClass->ClassFlags & CLASS_TokenStreamAssembled) != CLASS_TokenStreamAssembled);
        NewClass->ReferenceTokenStream.Empty();//对于蓝图类需要重新生成一下引用记号流
    }
    //构造函数列表
    NewClass->CreateLinkAndAddChildFunctionsToMap(Params.FunctionLinkArray, Params.NumFunctions);
    //构造属性列表
    ConstructUProperties(NewClass, Params.PropertyArray, Params.NumProperties);
    if (Params.ClassConfigNameUTF8)
    {   //配置文件名
        NewClass->ClassConfigName = FName(UTF8_TO_TCHAR(Params.ClassConfigNameUTF8));
    }
    NewClass->SetCppTypeInfoStatic(Params.CppClassInfo);//C++类型信息
    if (Params.NumImplementedInterfaces)
    {
        NewClass->Interfaces.Reserve(Params.NumImplementedInterfaces);
        for(int i=0;i<Params.Params.NumImplementedInterfaces;++i)
        {
            const auto& ImplementedInterface = Params.ImplementedInterfaceArray[i];
            UClass* (*ClassFunc)() = ImplementedInterface.ClassFunc;
            UClass* InterfaceClass = ClassFunc ? ClassFunc() : nullptr;//取得UMyInterface所属于的UClass*对象
            NewClass->Interfaces.Emplace(InterfaceClass, ImplementedInterface.Offset, ImplementedInterface.bImplementedByK2);//添加实现的接口
        }
    }
    NewClass->StaticLink();//链接
}
构造的过程也很简明，无非是先确保一下依赖对象已经存在，然后一一把各种信息：函数、属性、配置文件名、C++类型信息和接口添加到UClass*里去。重要的只有三步：ConstructUProperties和UScriptStruct的时候一样；接口的实现是通过UClass*里的TArray<FImplementedInterface> Interfaces数组表达的；CreateLinkAndAddChildFunctionsToMap创造函数列表。
void UClass::CreateLinkAndAddChildFunctionsToMap(const FClassFunctionLinkInfo* Functions, uint32 NumFunctions)
{
    for (; NumFunctions; --NumFunctions, ++Functions)
    {
        const char* FuncNameUTF8 = Functions->FuncNameUTF8;
        UFunction*  Func         = Functions->CreateFuncPtr();//调用构造UFunction*对象
        Func->Next = Children;
        Children = Func;//新函数挂在UField*链表的开头
        AddFunctionToFunctionMap(Func, FName(UTF8_TO_TCHAR(FuncNameUTF8)));
        //内部实现是：FuncMap.Add(FuncName, Function);添加到FuncMap里
    }
}
一个个创建UFunction*对象然后添加到FuncMap里去就是了。这里有意思的一点是，Children其实一个UField*的单链表，添加属性和函数都是直接挂在链表头的。通过构造顺序（CreateLinkAndAddChildFunctionsToMap先，ConstructUProperties次之）可以得知，最后Children的顺序是先所有UProperty*，之后才是所有的UFunction*。但UProperty*的顺序跟代码里定义的顺序一致，因为UHT生成的代码里PropPointers里恰好是倒序排列的。而UFunction*的顺序是根据函数名字排序后的反序。
UPackage
我们注意到在构造UEnum、UScriptScript和UClass的一开始都有一个构造Outer的过程，这个OuterFunc其实指向了这个Module的Package的构造，这个函数一般在模块的init.gen.cpp里。
//Hello.init.gen.cpp
UPackage* Z_Construct_UPackage__Script_Hello()
{
    static UPackage* ReturnPackage = nullptr;
    if (!ReturnPackage)
    {   //先构造代码里的Dynamic Delegate
        static UObject* (*const SingletonFuncArray[])() = {
            (UObject* (*)())Z_Construct_UDelegateFunction_Hello_MyDynamicSinglecastDelegate_One__DelegateSignature,
            (UObject* (*)())Z_Construct_UDelegateFunction_Hello_MyDynamicMulticastDelegate_One__DelegateSignature,
        };
        static const UE4CodeGen_Private::FPackageParams PackageParams = {
            "/Script/Hello",
            PKG_CompiledIn | 0x00000000,
            0x135222B4,
            0x392E1CFD,
            SingletonFuncArray, ARRAY_COUNT(SingletonFuncArray),
            METADATA_PARAMS(nullptr, 0)
        };
        UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);//构造Pacakge
    }
    return ReturnPackage;
}
//DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDynamicSinglecastDelegate_One, int32, Value);
唯一需要提醒的是对于代码里定义的动态委托（DynamicDelegate），其实是会在相应地生成UFunction*对象。这些散乱的DynamicDelegate是可以定义在类外面的，因此就不属于任一UClass*对象，所以就只好属于模块Package了。 构造代码也比较简单：
void ConstructUPackage(UPackage*& OutPackage, const FPackageParams& Params)
{
    if (OutPackage) {return;}
    UPackage* NewPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), nullptr, FName(UTF8_TO_TCHAR(Params.NameUTF8)), false, false));//找到之前创建的Package
    OutPackage = NewPackage;
    NewPackage->SetPackageFlags(Params.PackageFlags);//设定标记
    NewPackage->SetGuid(FGuid(Params.BodyCRC, Params.DeclarationsCRC, 0u, 0u));
    for (UObject* (*const *SingletonFunc)() = Params.SingletonFuncArray, *(*const *SingletonFuncEnd)() = SingletonFunc + Params.NumSingletons; SingletonFunc != SingletonFuncEnd; ++SingletonFunc)
    {
        (*SingletonFunc)();//调用构造前提对象
    }
}
需要注意的是ConstructUPackage这个时候，其实UPackage在之前UClass*对象Register的时候就已经Create出来了，所以只需要查找一下就行，然后设定一下信息标记，最后创建这个UPackage里的UFunction*对象。
UProperty
终于在前面讲完了大块头的构造，接着来说一下小小的属性。
//一个个属性的参数
static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Score = 
{ 
    UE4CodeGen_Private::EPropertyClass::Float, 
    "Score", 
    RF_Public|RF_Transient|RF_MarkAsNative,//对象标记
    (EPropertyFlags)0x0010000000000004, //属性标记
    1,  //数组维度，固定的数组的大小
    nullptr, //RepNotify函数的名称
    STRUCT_OFFSET(FMyStruct, Score) //属性的结构偏移地址
};
 //结构参数数组，会发送给ConstructUProperties来构造。
static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[] = 
{
    &NewProp_Score
};
ConstructUProperties其实就是会遍历数组调用ConstructUProperty：
void ConstructUProperty(UObject* Outer, const FPropertyParamsBase* const*& PropertyArray, int32& NumProperties)
{
    const FPropertyParamsBase* PropBase = *PropertyArray++;
    uint32 ReadMore = 0;
    UProperty* NewProp = nullptr;
    switch (PropBase->Type)
    {
       case EPropertyClass::Array:
        {
            const FArrayPropertyParams* Prop = (const FArrayPropertyParams*)PropBase;
            NewProp = new (EC_InternalUseOnlyConstructor, Outer, UTF8_TO_TCHAR(Prop->NameUTF8), Prop->ObjectFlags) UArrayProperty(FObjectInitializer(), EC_CppProperty, Prop->Offset, Prop->PropertyFlags);//构造Property对象
            // Next property is the array inner
            ReadMore = 1;//需要一个子属性
        }
        break;
        //case其他的各种类型属性
    }
    NewProp->ArrayDim = PropBase->ArrayDim;//设定属性维度，单属性为1，int32 prop[10]这种的为10
    if (PropBase->RepNotifyFuncUTF8)
    {   //属性的复制通知函数名
        NewProp->RepNotifyFunc = FName(UTF8_TO_TCHAR(PropBase->RepNotifyFuncUTF8));
    }
    --NumProperties;
    for (; ReadMore; --ReadMore)
    {   //构造子属性，注意这里以现在的属性NewProp为Outer
        ConstructUProperty(NewProp, PropertyArray, NumProperties);
    }
}
UHT会分析我们代码里的定义的属性类型，来生成不同的FPropertyParams类型。根据不同的EPropertyClass，构造生成不同类型的UProperty*。同时对于一些复合的属性类型，需要生成1或2个子属性。
这个表提供给大家对照。还有点需要注意的是UProperty的构造函数里会把自己添加到Outer里去：
void UProperty::Init()
{
    GetOuterUField()->AddCppProperty(this);//AddCppProperty是个虚函数
}
//重载
void UArrayProperty::AddCppProperty( UProperty* Property )
{
    Inner = Property;   //元素属性
}
void UMapProperty::AddCppProperty( UProperty* Property )
{
    if (!KeyProp) {KeyProp = Property;}//第一个是键属性
    else {ValueProp = Property;}//第二个是值属性
}
void USetProperty::AddCppProperty( UProperty* Property )
{
    ElementProp = Property;//元素属性
}
void UEnumProperty::AddCppProperty(UProperty* Inner)
{
    UnderlyingProp = CastChecked<UNumericProperty>(Inner);//依靠的整数属性
}
void UStruct::AddCppProperty( UProperty* Property )
{
    Property->Next = Children;
    Children       = Property;//新属性挂在UField*链表的开头
}
UFunction
属性说完，再来宠幸一下函数吧。测试代码请往上滚滚滚去MyClass里查看。
//测试函数：int32 Func(float param1);
void UMyClass::ImplementableFunc()  //UHT为我们生成了函数实体
{
    ProcessEvent(FindFunctionChecked("ImplementableFunc"),NULL);
}
void UMyClass::NativeFunc() //UHT为我们生成了函数实体，但我们可以自定义_Implementation
{
    ProcessEvent(FindFunctionChecked("NativeFunc"),NULL);
}
void UMyClass::StaticRegisterNativesUMyClass()  //之前的Native函数收集点
{
    UClass* Class = UMyClass::StaticClass();
    static const FNameNativePtrPair Funcs[] = {
        { "Func", &UMyClass::execFunc },
        { "NativeFunc", &UMyClass::execNativeFunc },
    };
    FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
}
struct Z_Construct_UFunction_UMyClass_Func_Statics
{
    struct MyClass_eventFunc_Parms  //把所有参数打包成一个结构来存储
    {
        float param1;
        int32 ReturnValue;
    };
    static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue= 
    { 
        UE4CodeGen_Private::EPropertyClass::Int, 
        "ReturnValue", 
        RF_Public|RF_Transient|RF_MarkAsNative,
        (EPropertyFlags)0x0010000000000580,
        1, 
        nullptr, 
        STRUCT_OFFSET(MyClass_eventFunc_Parms, ReturnValue) 
    };
    static const UE4CodeGen_Private::FFloatPropertyParams NewProp_param1 =
    { 
        UE4CodeGen_Private::EPropertyClass::Float,
        "param1", 
        RF_Public|RF_Transient|RF_MarkAsNative, 
        (EPropertyFlags)0x0010000000000080, 
        1,
        nullptr, 
        STRUCT_OFFSET(MyClass_eventFunc_Parms, param1) 
    };
    //函数的子属性
    static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[]= 
    {
        &NewProp_ReturnValue,   //返回值也用属性表示
        &NewProp_param1,        //参数用属性表示
    };
    //函数的参数
    static const UE4CodeGen_Private::FFunctionParams FuncParams=
    { 
        (UObject*(*)())Z_Construct_UClass_UMyClass, //外部对象
        "Func", //名字
        RF_Public|RF_Transient|RF_MarkAsNative, //对象标记
        nullptr, //父函数，在蓝图中重载基类函数时候指向基类函数版本
        (EFunctionFlags)0x04020401, //函数标记
        sizeof(MyClass_eventFunc_Parms),//属性的结构大小
        PropPointers, ARRAY_COUNT(PropPointers),//属性列表
        0,  //RPCId
        0   //RPCResponseId
    };
};
UFunction* Z_Construct_UFunction_UMyClass_Func()
{
    static UFunction* ReturnFunction = nullptr;
    if (!ReturnFunction)
    {   //构造函数
        UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UMyClass_Func_Statics::FuncParams);
    }
    return ReturnFunction;
}
//其他函数...
static const FClassFunctionLinkInfo FuncInfo[]= //发给ClassParams来构造UClass*
{
    { &Z_Construct_UFunction_UMyClass_Func, "Func" }, // 2606493682
    { &Z_Construct_UFunction_UMyClass_ImplementableFunc, "ImplementableFunc" }, // 3752866266
    { &Z_Construct_UFunction_UMyClass_NativeFunc, "NativeFunc" }, // 3036938731
}; 
//接口函数...
void IMyInterface::Execute_ImplementableInterfaceFunc(UObject* O)
{   //通过名字查找函数
    UFunction* const Func = O->FindFunction("ImplementableInterfaceFunc");
    if (Func)
    {
        O->ProcessEvent(Func, NULL);
    }//找不到，其实不会报错，所以是在尝试调用一个接口函数
}
void IMyInterface::Execute_NativeInterfaceFunc(UObject* O)
{   //通过名字查找函数
    UFunction* const Func = O->FindFunction("NativeInterfaceFunc");
    if (Func)
    {
        O->ProcessEvent(Func, NULL);
    }
    else if (auto I = (IMyInterface*)(O->GetNativeInterfaceAddress(UMyInterface::StaticClass())))
    {   //如果找不到蓝图中的版本，则会尝试调用C++里的_Implementation默认实现。
        I->NativeInterfaceFunc_Implementation();
    }
}
代码有点多，但其实结构还是很简单的。函数的参数和返回值都打包成一个结构（MyClass_eventFunc_Parms），这样UProperty才能有一个Offset的宿主。但有意思的是，其实这个结构（MyClass_eventFunc_Parms）我们只需要它的大小，并不需要它的实际类型定义，因为只要用它分配一块内存布局一致的内存就可以了。
我们可以看见，UHT为我们生成了一些函数的默认实现，如ImplementableFunc何NativeFunc，还有接口里的函数，所以我们不应该在C++里再重复实现（写了也会报错）。它们的内部实现也都是通过ProcessEvent来调用蓝图中的版本，或者调用C++里的_Implementation默认版本实现。 开始构造的过程如下：
void ConstructUFunction(UFunction*& OutFunction, const FFunctionParams& Params)
    {
        UObject*   Outer = Params.OuterFunc ? Params.OuterFunc() : nullptr;
        UFunction* Super = Params.SuperFunc ? Params.SuperFunc() : nullptr;
        if (OutFunction) {return;}
        if (Params.FunctionFlags & FUNC_Delegate)   //生成委托函数
        {
            OutFunction = new (EC_InternalUseOnlyConstructor, Outer, UTF8_TO_TCHAR(Params.NameUTF8), Params.ObjectFlags) UDelegateFunction(
                FObjectInitializer(),
                Super,
                Params.FunctionFlags,
                Params.StructureSize
            );
        }
        else
        {
            OutFunction = new (EC_InternalUseOnlyConstructor, Outer, UTF8_TO_TCHAR(Params.NameUTF8), Params.ObjectFlags) UFunction(
                FObjectInitializer(),
                Super,
                Params.FunctionFlags,
                Params.StructureSize
            );
        }
        ConstructUProperties(OutFunction, Params.PropertyArray, Params.NumProperties);//生成属性列表
        OutFunction->Bind();//函数绑定
        OutFunction->StaticLink();//函数链接
    }
构造的老套路是生成依赖，然后再new出对象，UFunction生成UProperty列表当做参数和返回值，最后再依次Bind和Link。其中一个function的SuperFunc表达的其实是函数的从基类继承重载下来，它其实指向的是基类里的函数版本。但在C++里其实一直是nullptr，因为C++里继承一个UFUNCION，不允许子类重复加UFUNCION标记，避免出现UFUNCION里标记不一致的情况，但是因为是virtual，所以其实也是可以正常多态的。那什么时候UFunction* GetSuperFunction()的才有值呢？答案是在蓝图里使用的时候，蓝图里所有函数其实都是UFunction，所以在继承重载的时候，子类函数的SuperFunction就会指向基类的版本。如我们新创建一个BPMyActor继承自AActor，就会默认出现4个重载函数：ReceiveBeginPlay、ReceiveTick、ReceiveActorBeginOverlap、UserConstructionScript，它们的Outer其实是基类版本的同名UFunction*（其他的是属于外部的UStruct或UPacakge）。也正是因为如此，UE知道这个函数是重载下来的，所以在该蓝图节点上点右键，才有“AddParentCall”啊。
绑定链接
事实上在构造完各类型对象后，还需要再梳理一遍，完成一些后初始化工作。跟C++的编译机制有点像，最后一步都是链接，通过符号定位到函数地址来替换。UE里也一样，需要这么一个绑定链接操作。之前的时候有谈到Bind和StaticLink都略过了，这时再来讲解一下内部的操作。
Bind
绑定的作用是把函数指针绑定到正确的地址！
Bind其实是定义在UField里的方法：virtual void Bind(){}，代表所有的字段都可能需要重载这么一个绑定操作，只不过事实上只有UFunction和UClass才有这两个操作。
UFunction::Bind()的目的是把FNativeFuncPtr Func绑定到正确的函数指针里去。
void UFunction::Bind()
{
    UClass* OwnerClass = GetOwnerClass();
    if (!HasAnyFunctionFlags(FUNC_Native))
    {
        Func = &UObject::ProcessInternal;   //非native函数指向蓝图调用
    }
    else
    {
        FName Name = GetFName();    //在之前注册的naive函数表里去查找函数指针
        FNativeFunctionLookup* Found = OwnerClass->NativeFunctionLookupTable.FindByPredicate([=](const FNativeFunctionLookup& NativeFunctionLookup){ return Name == NativeFunctionLookup.Name; });
        if (Found)
        {
            Func = Found->Pointer;  //定位到c++代码里的函数指针。
        }
    }
}
UClass的Bind在编译蓝图和载入Package里的类才需要调用，因为native的类在之前的GetPrivateStaticClassBody的时候已经传进去了函数指针。只有没有C++代码实体的类才需要绑定到基类里的构造函数等才能正确正确继承下来这些函数来调用。
void UClass::Bind()
{
    UStruct::Bind();
    UClass* SuperClass = GetSuperClass();
    if (SuperClass && 
            (ClassConstructor == nullptr || 
            ClassAddReferencedObjects == nullptr || 
            ClassVTableHelperCtorCaller == nullptr)
        )
    {
        SuperClass->Bind();//确保基类已经绑定
        if (!ClassConstructor)
        {
            ClassConstructor = SuperClass->ClassConstructor;//绑定构造函数指针
        }
        if (!ClassVTableHelperCtorCaller)
        {
            ClassVTableHelperCtorCaller = SuperClass->ClassVTableHelperCtorCaller;//绑定热载函数指针
        }
        if (!ClassAddReferencedObjects)
        {
            ClassAddReferencedObjects = SuperClass->ClassAddReferencedObjects;//绑定ARO函数指针
        }
        ClassCastFlags |= SuperClass->ClassCastFlags;
    }
}
绑定的这三个函数和GetPrivateStaticClassBody里传进来的一样。
Link
在构造UScriptStuct和UClass的最后一步都调用了StaicLink，它其实是UStruct的一个方法，包装了一个空的序列化归档类对象后转发到UStruct::Link函数上去。
void UStruct::StaticLink(bool bRelinkExistingProperties /*= false*/)
{
    FArchive ArDummy;   //一个空的序列化归档类
    Link(ArDummy, bRelinkExistingProperties);
}
而UStruct::Link又是一个虚函数，在很多的子类中都有重载。StaicLink也在很多地方有调用。 Link这个词其实有三层意思：
跟编译器的Link一样，编译完成后的最后一个操作链接，替换符号地址等。典型的是在结构改变或者编译后重新Link。
把子字段们按照属性特征分成一个个链条，如RefLink。
序列化的时候也有概念Link，用来充当磁盘和内存里对象的链接桥梁。同样，在一个保存在磁盘里的类型被序列化出来之后，就需要再Link一下来重新设置属性的偏移，结构内存对齐等。这也是Link需要一个FArchive参数的原因。
UProperty里其实也有一个Link，分为LinkInternal和SetupOffset，LinkInternal主要是用来根据属性特征再设置一下PropertyFlags，而SetupOffset是用来在序列化后设置属性内存偏移。这部分比较散乱，就请读者朋友们自己查看了。 而重点的是UStruct::Link：
void UStruct::Link(FArchive& Ar, bool bRelinkExistingProperties)
{
    for (UField* Field=Children; (Field != NULL) && (Field->GetOuter() == this); Field = Field->Next)
    {
        if (UProperty* Property = dynamic_cast<UProperty*>(Field))
        {
            Property->LinkWithoutChangingOffset(Ar);//对所有属性先Link一下。
        }
    }
    UProperty** PropertyLinkPtr = &PropertyLink;
    UProperty** DestructorLinkPtr = &DestructorLink;
    UProperty** RefLinkPtr = (UProperty**)&RefLink;
    UProperty** PostConstructLinkPtr = &PostConstructLink;
    TArray<const UStructProperty*> EncounteredStructProps;
    for (TFieldIterator<UProperty> It(this); It; ++It)  //遍历出所有属性
    {
        UProperty* Property = *It;
        if (Property->ContainsObjectReference(EncounteredStructProps) || Property->ContainsWeakObjectReference())
        {
            *RefLinkPtr = Property;//包含对象引用的属性
            RefLinkPtr = &(*RefLinkPtr)->NextRef;
        }
        const UClass* OwnerClass = Property->GetOwnerClass();
        bool bOwnedByNativeClass = OwnerClass && OwnerClass->HasAnyClassFlags(CLASS_Native | CLASS_Intrinsic);
        if (!Property->HasAnyPropertyFlags(CPF_IsPlainOldData | CPF_NoDestructor) &&
            !bOwnedByNativeClass) // these would be covered by the native destructor
        {   
            *DestructorLinkPtr = Property;//需要额外析构的属性
            DestructorLinkPtr = &(*DestructorLinkPtr)->DestructorLinkNext;
        }
        if (OwnerClass && (!bOwnedByNativeClass || (Property->HasAnyPropertyFlags(CPF_Config) && !OwnerClass->HasAnyClassFlags(CLASS_PerObjectConfig))))
        {
            *PostConstructLinkPtr = Property;//需要从CDO中获取初始值的属性
            PostConstructLinkPtr = &(*PostConstructLinkPtr)->PostConstructLinkNext;
        }
        *PropertyLinkPtr = Property;//所有属性
        PropertyLinkPtr = &(*PropertyLinkPtr)->PropertyLinkNext;
    }
    *PropertyLinkPtr = nullptr;
    *DestructorLinkPtr = nullptr;
    *RefLinkPtr = nullptr;
    *PostConstructLinkPtr = nullptr;
}
看起来有点乱，各种标记的判断，但其实只是把之前AddCppProperty添加到UField* Children里的字段们，抽出UProperty们，然后再串成4个链条：
PropertyLink：所有的属性
RefLink：包含对象引用（UObject*）的属性，这些属性对GC有影响，所以单独分类出来加速分析。
PostConstructLink：所有需要从CDO中获取初始值的属性，属性可以从Config文件中或者CDO中获取初始值，因此在序列化后需要初始化一下属性们的值。
DestructorLink：需要额外析构的属性，在析构的时候，需要去调用一下属性的析构函数。否则的话，如一个int属性，就不用管它，释放内存就可以了。
单独分类出来这4个链条也是为了在不同的应用场景下加速性能，不需要每次去遍历所有的属性。UFunction本身也是个UStruct，它的Link的之后会调用InitializeDerivedMembers来算一下参数和返回值的信息偏移而已。
总结
篇幅太长了都……但没办法，不一鼓作气的把它们都串起来也不好拆分。我知道，阅读文章时，最不喜欢看到贴大段的代码。但读者朋友们如果想对类型系统的组织形式有个更深的了解，还请对照着UE的源码，一点点加深理解。我们最后来梳理一下：
类型系统结构：
整个的类型系统结构还是挺明了的，UMetaData之前一直略去，其实是把宏标记里的那些信息采集起来关联到对象身上，在编辑器里使用。UUserDefinedEnum、UUUserDefinedStruct和UBlueprintGeneratedClass都是蓝图里定义编译出来的枚举结构和类。UDynamicClass是蓝图Native化后生成的类，FClass是UHT分析过程产生的类。
属性就有各种类型了，简直是各开花：
我也是敬业，把所有属性都列了出来。UE为了在这么多属性之间尽量复用接口，用了多继承的方式。每个属性的实现还是挺简单的，有兴趣的读者朋友们可以到源码里一观。有些属性我们在后面的GC章节也还会涉及到。
类型系统到这也就算是构造完了，我们在下篇来汇总总结一下。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（十二）类型系统-总结</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/60291730
引言
又是总结了，前面我们用了挺长的段落来一一讲解UE4里类型系统的结构、信息收集、构造注册和绑定链接。但还剩一些小主题和一些梳理没讲完，最后一波带走。
UClass对象成长的几个阶段
相信很多读者朋友们，在研究了一段时间，或者看了这一系列文章下来后，虽然感觉懂得了挺多东西，但可能依然会像我刚开始自己研究一样，脑袋里去回想整个流程，却依然会有点模糊，感觉掌握的不够牢靠。初始懵懂，大家都是管中窥豹盲人摸象，但如果想要做到肆意亵玩，就要走进科学，多角度观察。按我的经验来说，此时有两种视角就很有效用：过程和数据。过程关注一个个步骤是怎么承上启下的，数据关注高楼林立的对象是怎么平地起的。
针对类型系统来说，前面都讲了各个函数调用的序列，其中穿插着也讲了UClass*对象的构造的几个阶段。但是零碎的讲述和专门的整理是两回事！
一个UClass*要经历这么几个阶段：
内存构造。刚创建出来一块白纸一般的内存，简单的调用了UClass的构造函数。UE里一个对象的构造，构造函数的调用只是个起点而已。
注册。给自己一个名字，把自己登记在对象系统中。这步是通过DeferredRegister而不是Register完成的。
对象构造。往对象里填充属性、函数、接口和元数据的信息。这步我们应该记得是在gen.cpp里的那些函数完成的。
绑定链接。属性函数都有了，把它们整理整理，尽量优化一下存储结构，为以后的使用提供更高性能和便利。
CDO创建。既然类型已经有了，那就万事俱备只差国家包分配一个类默认对象了。每个UClass都有一个CDO（Class Default Object），有了CDO，相当于有了一个存档备份和参照，其他对象就心不慌。
引用记号流构建。一个Class是怎么样有可能引用其他别的对象的，这棵引用树怎么样构建的高效，也是GC中一个非常重要的话题。有了引用记号流，就可以对一个对象高效的分析它引用了其他多少对象。
UMetaData
前面对于这个元数据，几乎都略过了，因为它是只在Editor模式下使用的。在所有的类型对象Construct的一步就是AddMetaData：
#if WITH_METADATA
void AddMetaData(UObject* Object, const FMetaDataPairParam* MetaDataArray, int32 NumMetaData)
{
    if (NumMetaData)
    {
        UMetaData* MetaData = Object->GetOutermost()->GetMetaData();//得到Package属于的MetaData
        for (const FMetaDataPairParam* MetaDataParam = MetaDataArray, *MetaDataParamEnd = MetaDataParam + NumMetaData; MetaDataParam != MetaDataParamEnd; ++MetaDataParam)
        {
            MetaData->SetValue(Object, UTF8_TO_TCHAR(MetaDataParam->NameUTF8), UTF8_TO_TCHAR(MetaDataParam->ValueUTF8)); //添加数据
        }
    }
}
#endif
UMetaData* UPackage::GetMetaData()
{
#if WITH_EDITORONLY_DATA
    if (MetaData == NULL)
    {
        MetaData = FindObjectFast<UMetaData>(this, FName(NAME_PackageMetaData));
        if(MetaData == NULL)
        {
            MetaData = NewObject<UMetaData>(this, NAME_PackageMetaData, RF_Standalone | RF_LoadCompleted);
        }
    }
    if (MetaData->HasAnyFlags(RF_NeedLoad))
    {
        MetaData->GetLinker()->Preload(MetaData);
    }
    return MetaData;
#else
    return nullptr;
#endif
}
从这里能知道的有三件事，一是UMetaData是属于UPackage关联的，而不是跟某个UField直接绑定。第二是UMetaData在Runtime下是被略过去的。三是UMetaData也是个对象。继续查看UMetaData的定义：
class COREUOBJECT_API UMetaData : public UObject
{
public:
    TMap< FWeakObjectPtr, TMap<FName, FString> > ObjectMetaDataMap;//对象关联的键值对
    TMap< FName, FString > RootMetaDataMap;//包本身的键值对
};
const FString& UField::GetMetaData(const FName& Key) const
{
    UPackage* Package = GetOutermost();
    UMetaData* MetaData = Package->GetMetaData();
    const FString& MetaDataString = MetaData->GetValue(this, Key);
    return MetaDataString;
}
这个ObjectMetaDataMap的定义就很有意思，FWeakObjectPtr用弱指针引用UObject对象，这样就不会阻碍对象的GC；键用FName，因为键只有固定的一些（Category，Tooltip这些）；值用FString就可以爱写啥写啥了。
思考：为何不把Map<FName,FString> MetaDataMap直接放进UObject里？ 一个直接的思维可能是直接在UObject里添加个字段，这样所有的UObject就都可以有额外的元数据了。但有时候过于直接是有害的，直男们应该都懂……UE这么设计，就是为了脱钩！ 嵌入的方式有可见的坏处：
加大了UObject本身的Size，不轮用到元数据没有，都得承受多一个字段的负担。就算只放进UField里，也只是减轻，因为还有很多UField并没有多余的元数据需要记录。
请神容易送神难，嵌入进去后，就比较难再拆出来了，这些元数据信息只是在编辑器模式下提供给编辑器界面行为用的，在Cook的时候是要略去的，这个时候如果MetaDataMap在真正的对象里面，在一个二进制流里单独想拆出来一部分，这种手术的难度可是比较高的。而如果UMetaData是个独立的对象，这样它就算保存也是保存在文件里一整块地方，单独拆这个楼就容易多了。
拆出来当然会多一层间接访问，多了效率的负担和CacheMiss的机会。但审时度势来说，UMetaData的使用只在编辑器下用，编辑器稍微慢一点点无所谓，没有游戏那种帧率要求。且访问UMetaData的频率并不高，只在初始化界面的时候获取一下来改变UI。UMetaData再设计成UPackage是关联的（Outer是UPackage），而UPackage是序列化保存的单位，这样UMetaData就可以当做一个独立的部分来进行加载或释放了。
GRegisterCast和GRegisterNative的作用
前面有讲过一个static初始化阶段还有两个收集点：IMPLEMENT_CAST_FUNCTION收集到GRegisterCast，IMPLEMENT_VM_FUNCTION收集到GRegisterNative，但并没有机会来讲那些是用来干嘛的。这些其实就是一些函数用来做对象的转换和蓝图虚拟机的一些基础函数。把虚拟机里运行的指令码和真正的函数指针绑定起来。这些是蓝图的部分，以后讲到蓝图的时候再介绍。
Flags
还有一个东西是有点略过的，就是各种Flags的枚举。UE利用这些枚举标志来判断对象的状态和特征。 重要的有：
EObjectFlags：对象本身的标志。
EInternalObjectFlags：对象存储的标志，GC的时候用来检查可达性。
EObjectMark：用来额外标记对象特征的标志，用在序列化过程中标识状态。
EClassFlags：类的标志，定义了一个类的特征。
EClassCastFlags：类之间的转换，可以快速的测试一个类是否可以转换成某种类型。
EStructFlags：结构的特征标志。
EFunctionFlags：函数的特征标志。
EPropertyFlags：属性的特征标志。
具体的请读者们自己去查看定义了，太多了就不一一解释了。这也是一种常用的C++惯用法，枚举标志来表示叠加的特征。
总结
在絮絮叨叨了这么一大套流程之后，我不知道读者朋友们对UE的这部分流程是个什么感觉。这套流程这么设计是否流畅合理？整体回想起来是否脉络清晰呢？答案是否定的。作为一个能把这部分啰嗦写成十篇文章的人来说，我都觉得里面的弯弯绕绕太多，何况普通的开发者去阅读呢。这里面固然有着实践的权衡，但其实也是疏于整理，历史包袱太重。
从一个方面来说，CoreUObject这部分固然是不用暴露给普通用户使用的，所以即使内部再怎么复杂都没有关系。我们经常讲一个模块应该高内聚低耦合，但这句话的语境其实是针对模块的边界时候讲的，但边界的判断只是个视角问题。换种眼光，一个函数的外部也算是边界。所以，对于一个模块内部来说，如果内部纠缠不清，那它其实也只是外强中干。但凡事也都有个程度问题，小病只要不影响生活质量那就算伴随一辈子其实也没事，引擎的内部这一点点流程复杂，从完美主义者上来说不够优雅，但其实只要负责的那个人能够Hold得住，其实也就能心平气和的接受了。
那是不是就可以这么过去了呢？诚然对于UE的这么核心的模块，我们都没有什么话语权去修改，但作为一个技术人员，秉着精益求精的态度，对于自己负责的项目模块，在自己的一亩三分地里，就要尽量的做到优雅设计了。提供给别人用的模块更是如此。
对于游戏引擎，在这里我想谈的一个非常重要的话题是信心！引擎开发者的信心和引擎使用者的信心。经济学里，信心是非常重要的，人们对未来的预期会很大的影响社会经济，甚至可以说货币的本质就是信心。而在游戏引擎领域，信心也非常重要。游戏开发人员相信引擎能帮他实现想要的效果，引擎开发人员相信自己能把引擎不断升级迭代越来越好，这样才能不断正向循环。
信心跟架构有什么关系？关系其实很大，当一个引擎的代码，模块的代码，看起来读起来理解起来改造起来，都显得很艰深晦涩的话，人们就会逐渐开始丧失信心。就拿CoreUObject打比方，普通的开发者自己去研读它的代码，发现太复杂了很难搞懂，请问他会有很强的信心用好这个引擎吗？他只会想这个引擎里还藏着好多秘密，我就当个普通人用吧，自己小心一点，别踩到坑了。人的心理对于模糊不清的东西就是会失去掌控感，而没有安全感就会畏首畏尾不前，开始保守主义，慢慢的潜意识里就算引擎新出了厉害功能，也不敢去使用，因为怕踩坑。会害怕是因为新技术自己不懂，印象里就觉得很难懂，因为过往的都很难懂。慢慢的在游戏引擎市场里就开始传出了这个引擎很难用的风气。而对于引擎开发人员自己来说，如果理解维护一个模块的成本太大，也会逐渐的丧失信心。开发软件项目的时候，有时会出现一种失控的状况，出bug了修复靠运气和防御，开发人员也尽量不想去碰它。这种模块某种意义上来说已经走完了生命期，行将就木了。引擎是产品，代码其实也是产品，对外对内都是，代码就是要给人读的，提供给别人的就一定要漂亮一点，否则大家就直接只敲01得了。
其实我有时候也在犹豫，知道了解类型系统内部的构建过程这些知识有什么用？费这么多口舌，越是艰深的内容看的人也越是少，从功利主义上来说，我直接画张结构图，然后示例几种用法不就好了嘛。但这后来想了，其实还是有两点好处的。首先是信心，把东西剖开了就没有秘密，大家用起来改造起来心就稳。其次是扩宽了思维的广度，为实际编程提供更多思路。
举个小例子，假如你看到编辑器里某个属性，想在C++里去修改它的值，结果发现它不是public的，甚至有可能连头文件都是private的，这个时候如果对类型系统结构理解不深的人可能就放弃了，但懂的人就知道可以通过这个对象遍历UProperty来查找到这个属性从而修改它。
还有一个例子是如果你做了一个插件，调用了引擎编辑器本身的Details面板属性，但又想隐藏其中的一些字段，这个时候如果不修改引擎往往是难以办到的，但是如果知道了属性面板里的属性其实也都是一个个UProperty来的，这样你就可以通过对象路径获得这个属性，然后开启关闭它的某些Flags来达成效果。这也算是一种常规的Hack方式。
所以，你懂得越多，就越是能在你想象不到的地方回报给你。
下一篇，讲讲类型系统反射在实战中大概有哪些应用。
</code></pre>
</details>
<br />
<details>
<summary>《InsideUE4》UObject（十三）类型系统-反射实战</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/61042237
引言
上篇章节总结了类型系统的最后一些小知识点，为了免于说都是纯理论知识，本篇我们来讲一些利用反射的例子。
获取类型对象
如果想获取到程序里定义的所有的class，方便的方法是：
TArray<UObject*> result;
GetObjectsOfClass(UClass::StaticClass(), result);   //获取所有的class和interface
GetObjectsOfClass(UEnum::StaticClass(), result);   //获取所有的enum
GetObjectsOfClass(UScriptStruct::StaticClass(), result);   //获取所有的struct
GetObjectsOfClass是UE4已经写好的一个很方便的方法，可以获取到属于某个UClass*下面的所有对象。因此如果用UClass::StaticClass()本身，就可以获得程序里定义的所有class。值得注意的是，UE4里的接口是有一个配套的UInterface对象来存储元数据信息，它的类型也是用UClass*表示的，所以也会获得interface。根据前文，enum会生成UEnum，struct会生成UScriptStruct，所以把参数换成UEnum::StaticClass()就可以获得所有的UEnum*对象了，UScriptStruct::StaticClass()就是所有的UScriptStruct*了，最后就可以根据这些类型对象来反射获取类型信息了。
而如果要精确的根据一个名字来查找某个类型对象，就可以用UE4里另一个方法：
template< class T > 
inline T* FindObject( UObject* Outer, const TCHAR* Name, bool ExactClass=false )
{
    return (T*)StaticFindObject( T::StaticClass(), Outer, Name, ExactClass );
}
UClass* classObj=FindObject<UClass>(ANY_PACKAGE,"MyClass");   //获得表示MyClass的UClass*
这样就可以轻易的获得不同类型的对象。FindObject内部的原理在下大章节内存管理再讲述。
遍历字段
在获取到了一个类型对象后，就可以用各种方式去遍历查找内部的字段了。为此，UE4提供了一个方便的迭代器TFieldIterator<T>，可以通过它筛选遍历字段。
const UStruct* structClass; //任何复合类型都可以
//遍历属性
for (TFieldIterator<UProperty> i(structClass); i; ++i)
{
    UProperty* prop=*i; 
}
//遍历函数
for (TFieldIterator<UFunction> i(structClass); i; ++i)
{
    UFunction* func=*i; 
    //遍历函数的参数
    for (TFieldIterator<UProperty> i(func); i; ++i)
    {
        UProperty* param=*i; 
        if( param->PropertyFlags & CPF_ReturnParm ) //这是返回值
        {
        }
    }
}
//遍历接口
const UClass* classObj; //只有UClass才有接口
for (const FImplementedInterface& ii : classObj->Interfaces)
{
    UClass* interfaceClass = ii.Class;
}
给模板参数T传UFunction就可以获得类型下的所有函数，通过这也可以遍历获得UFunction下的参数列表。当然TFieldIterator也可以再传其他参数的控制是否包含基类的字段、是否包含废弃的字段、是否包含接口里的字段。TFieldIterator的内部实现其实也挺简单的，一是通过SuperStruct来获得Super，二是通过Interfaces来获得实现的接口，三是用Field->Next来遍历字段。信息数据都是全的，迭代遍历就简单了。
遍历枚举的字段也很简单:
const UEnum* enumClass;
for (int i = 0; i < enumClass->NumEnums(); ++i)
{
    FName name = enumClass->GetNameByIndex(i);
    int value = enumClass->GetValueByIndex(i);
}
还有遍历元数据的：
#if WITH_METADATA
const UObject* obj;//可以是任何对象，但一般是UField才有值
UMetaData* metaData = obj->GetOutermost()->GetMetaData();
TMap<FName, FString>* keyValues = metaData->GetMapForObject(obj);
if (keyValues != nullptr&&keyValues->Num() > 0)
{
    for (const auto& i : *keyValues)
    {
        FName key=i.Key;
        FString value=i.Value;
    }
}
#endif
当然，如果想精确查找的话，也有相应的方法。
//查找属性
UProperty* UStruct::FindPropertyByName(FName InName) const
{
    for (UProperty* Property = PropertyLink; Property != NULL; Property = Property->PropertyLinkNext)
    {
        if (Property->GetFName() == InName)
        {
            return Property;
        }
    }
    return NULL;
}
//查找函数
UFunction* UClass::FindFunctionByName(FName InName, EIncludeSuperFlag::Type IncludeSuper) const;
查看继承
得到类型对象后，也可以遍历查看它的继承关系。 遍历继承链条：
const UStruct* structClass; //结构和类
TArray<FString> classNames;
classNames.Add(structClass->GetName());
UStruct* superClass = structClass->GetSuperStruct();
while (superClass)
{
    classNames.Add(superClass->GetName());
    superClass = superClass->GetSuperStruct();
}
FString str= FString::Join(classNames, TEXT("->")); //会输出MyClass->UObject
那反过来，如果想获得一个类下面的所有子类，可以这样：
const UClass* classObj; //结构和类
TArray<UClass*> result;
GetDerivedClasses(classObj, result, false);
//函数原型是
void GetDerivedClasses(UClass* ClassToLookFor, TArray<UClass *>& Results, bool bRecursive);
GetDerivedClasses也是UE4里写好的一个方法，内部用到了HashMa方式（TMap<UClass*, TSet<UClass*>> ClassToChildListMap）保存了类到子类列表的映射。
那么怎么获取实现了某个接口的所有子类呢？呃，没啥好办法，因为可能用的不多，所以没有保存这层映射关系。我们只能暴力的遍历出来：
TArray<UObject*> result;
GetObjectsOfClass(UClass::StaticClass(), result);
TArray<UClass*> classes;
for (UObject* obj : result)
{
    UClass* classObj = Cast<UClass>(obj);
    if (classObj->ImplementsInterface(interfaceClass))//判断实现了某个接口
    {
        classes.Add(classObj);
    }
}
获取设置属性值
有了UProperty之后，就可以方便的反射获得其值：
template<typename ValueType>
ValueType* UProperty::ContainerPtrToValuePtr(void* ContainerPtr, int32 ArrayIndex = 0) const
{
    return (ValueType*)ContainerVoidPtrToValuePtrInternal(ContainerPtr, ArrayIndex);
}
template<typename ValueType>
ValueType* UProperty::ContainerPtrToValuePtr(UObject* ContainerPtr, int32 ArrayIndex = 0) const
{
    return (ValueType*)ContainerVoidPtrToValuePtrInternal(ContainerPtr, ArrayIndex);
}
void* UProperty::ContainerVoidPtrToValuePtrInternal(void* ContainerPtr, int32 ArrayIndex) const
{
    //check...
    return (uint8*)ContainerPtr + Offset_Internal + ElementSize * ArrayIndex;
}
void* UProperty::ContainerUObjectPtrToValuePtrInternal(UObject* ContainerPtr, int32 ArrayIndex) const
{
    //check...
    return (uint8*)ContainerPtr + Offset_Internal + ElementSize * ArrayIndex;
}
//获取对象或结构里的属性值地址，需要自己转换成具体类型
void* propertyValuePtr = property->ContainerPtrToValuePtr<void*>(object);
//包含对象引用的属性可以获得对象
UObject* subObject = objectProperty->GetObjectPropertyValue_InContainer(object);
UE4特意加了void*和UObject*的重载来分别获得结构和对象里的属性值，内部其实有更多的check代码被我忽略掉了。UE4里面把外部的结构或对象值叫做Container（容器），非常合理，包裹着属性的外部的东西不就是容器嘛。另一个可以见到的是属性值的获取其实也非常简明，Offset_Internal就是一开始的时候STRUCT_OFFSET()的时候传进来的属性在结构里内存偏移值。ElementSize是元素内存大小，可以通过ArrayIndex数组索引（比如int values[10]这种固定数组的属性）获取数组里第几号元素值。
也因为获取到的是存放属性值的指针地址，所以其实也就可以*propertyValuePtr=xxx;方便的设置值了。当然如果是从字符串导入设置进去，UE4也提供了两个方法来导出导入：
//导出值
virtual void ExportTextItem( FString& ValueStr, const void* PropertyValue, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = NULL ) const; 
//使用
FString outPropertyValueString;
property->ExportTextItem(outPropertyValueString, property->ContainerPtrToValuePtr<void*>(object), nullptr, (UObject*)object, PPF_None);
//导入值
const TCHAR* UProperty::ImportText( const TCHAR* Buffer, void* Data, int32 PortFlags, UObject* OwnerObject, FOutputDevice* ErrorText = (FOutputDevice*)GWarn ) const;
//使用
FString valueStr;
prop->ImportText(*valueStr, prop->ContainerPtrToValuePtr<void*>(obj), PPF_None, obj);
ExportTextItem和ImportText实际上也是我们在编辑器里在Details面板里选择一个属性进行Ctrl+C Copy和Ctrl+V Paste的时候调用的方法。UE4实际上都是把他们序列化成字符串传递的。
反射调用函数
既然能够得到UFunction了，我们当然也就可以调用他们了。虽然这部分机制是关于蓝图的，但是提前罗列出来也未尝不可。在一个UObject上通过名字调用UFunction方法最简单的方式大概是：
//方法原型
int32 UMyClass::Func(float param1); 
UFUNCTION(BlueprintCallable)
int32 InvokeFunction(UObject* obj, FName functionName,float param1)
{
    struct MyClass_Func_Parms   //定义一个结构用来包装参数和返回值，就像在gen.cpp里那样
    {
        float param1;
        int32 ReturnValue;
    };
    UFunction* func = obj->FindFunctionChecked(functionName);
    MyClass_Func_Parms params;
    params.param1=param1;
    obj->ProcessEvent(func, &params);
    return params.ReturnValue;
}
//使用
int r=InvokeFunction(obj,"Func",123.f);
特别注意的是，我们需要定义一块内存用来包装存储参数和返回值，就像注册函数的时候那样。在gen.cpp里也是这么一块内存，表示参数的UProperty里的Offset其实就是针对这块内存而说的。所以为了能够正确的根据Offset再反取出来值来，这块内存的字段内存布局必须和函数注册时候的保持严格一致！所以字段声明的顺序是必须和gen.cpp里一致。也就是按照先参数顺序后返回值的顺序。
ProcessEvent也是UE4里事先定义好的非常方便的函数，内部会自动的处理蓝图VM的问题。当然，更底层的方法也可以是：
//调用1
obj->ProcessEvent(func, &params);
//调用2
FFrame frame(nullptr, func, &params, nullptr, func->Children);
obj->CallFunction(frame, &params + func->ReturnValueOffset, func);
//调用3
FFrame frame(nullptr, func, &params, nullptr, func->Children);
func->Invoke(obj, frame, &params + func->ReturnValueOffset);
调用123其实是差不多等价的，在没有obj的情况下调用static函数，可以用调用3的方式。我们知道写在蓝图里的函数和事件最终也都是会编译生成的UFunction对象的，所以用此方法可以直接调用蓝图里的成员函数和自定义事件。
当然我们也见到上述的方法也有不便之处，必须手动定一个参数结构和固定的函数原型。这是我自己写的一个通过反射调用函数的方法：
template<typename... TReturns, typename... TArgs>
void InvokeFunction(UClass* objClass, UObject* obj, UFunction* func, TTuple<TReturns...>& outParams, TArgs&&... args)
{
    objClass = obj != nullptr ? obj->GetClass() : objClass;
    UObject* context = obj != nullptr ? obj : objClass;
    uint8* outPramsBuffer = (uint8*)&outParams;
    if (func->HasAnyFunctionFlags(FUNC_Native)) //quick path for c++ functions
    {
        TTuple<TArgs..., TReturns...> params(Forward<TArgs>(args)..., TReturns()...);
        context->ProcessEvent(func, &params);
        //copy back out params
        for (TFieldIterator<UProperty> i(func); i; ++i)
        {
            UProperty* prop = *i;
            if (prop->PropertyFlags & CPF_OutParm)
            {
                void* propBuffer = prop->ContainerPtrToValuePtr<void*>(&params);
                prop->CopyCompleteValue(outPramsBuffer, propBuffer);
                outPramsBuffer += prop->GetSize();
            }
        }
        return;
    }
    TTuple<TArgs...> inParams(Forward<TArgs>(args)...);
    void* funcPramsBuffer = (uint8*)FMemory_Alloca(func->ParmsSize);
    uint8* inPramsBuffer = (uint8*)&inParams;
    for (TFieldIterator<UProperty> i(func); i; ++i)
    {
        UProperty* prop = *i;
        if (prop->GetFName().ToString().StartsWith("__"))
        {
            //ignore private param like __WolrdContext of function in blueprint funcion library
            continue;
        }
        void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
        if (prop->PropertyFlags & CPF_OutParm)
        {
            prop->CopyCompleteValue(propBuffer, outPramsBuffer);
            outPramsBuffer += prop->GetSize();
        }
        else if (prop->PropertyFlags & CPF_Parm)
        {
            prop->CopyCompleteValue(propBuffer, inPramsBuffer);
            inPramsBuffer += prop->GetSize();
        }
    }
    context->ProcessEvent(func, funcPramsBuffer);   //call function
    outPramsBuffer = (uint8*)&outParams;    //reset to begin
    //copy back out params
    for (TFieldIterator<UProperty> i(func); i; ++i)
    {
        UProperty* prop = *i;
        if (prop->PropertyFlags & CPF_OutParm)
        {
            void* propBuffer = prop->ContainerPtrToValuePtr<void*>(funcPramsBuffer);
            prop->CopyCompleteValue(outPramsBuffer, propBuffer);
            outPramsBuffer += prop->GetSize();
        }
    }
}
哇，这么复杂！不是我坏，而是这个函数处理了各种情况。
利用了UE4本身内部的模板类TTuple来自动的包装多个参数，这样就不用手动的去定义参数结构体了。多返回值也是用TTuple来返回的。
可以调用C++里定义的成员函数和静态函数，同时也支持调用定义在蓝图里的成员函数，事件，蓝图库里的函数。因为蓝图里的函数支持多输入多输出值，蓝图函数在编译之后，参数常常就会比C++里看起来的多一些，函数中的临时变量也常常被当做一个UProperty了。所以如何压参到蓝图VM就会比C++里多一些额外的步骤。我在上面的函数里面在栈上面生成了一块FMemory_Alloca(func->ParmsSize);内存来当做函数运行时候的参数内存。当然，这块内存在反射调用前必须从函数参数集合里初始化，反射调用后又必须把值拷贝回返回参数上。
在调用静态函数的时候，因为其实不需要UObject*，所以可以传nullptr，于是就可以把相应的UClass*来当做context调用对象了。
这个函数处理的最复杂的情况，对于无参数和无返回值的情况，读者朋友们可以自己用不定参数模板偏特化和重载来定义出不同的版本来。也是比较容易的。
我们也看到函数参数里需要你提供UClass*、UObject*和UFunction*，这些参数利用上面的FindFunctionByName类似方式来查找。我们也可以在这上面继续加上一些便利方法来暴露给蓝图。
假如你还想就像在蓝图中调用蓝图函数库一样，只提供函数名字和参数就可以调用，你可以这样：
template<typename... TReturns, typename... TArgs>
static void InvokeFunctionByName(FName functionName,TTuple<TReturns...>& outParams,TArgs&&... args)
{
    /*
    错误！在PIE模式下，有可能会获得SKEL_XXX_C:Func这个对象，里面的Script为空
    UFunction* func = FindObject<UFunction>(ANY_PACKAGE, *functionName.ToString()); 
    */
    UFunction* func = (UFunction*)StaticFindObjectFast(UFunction::StaticClass(), nullptr, functionName, false, true, RF_Transient); //exclude SKEL_XXX_C:Func
    InvokeFunction<TReturns...>(func->GetOuterUClass(), nullptr, func, outParams,Forward<TArgs>(args)...);
}
值得注意的是UFunction*的查找方式。我们不能简单的用FindObject来查找，因为蓝图在编译编译后Cook前，会生成两个类：BPMyClass_C和SKEL_BPMyClass_C，后者里面也有个同名的UFunction*对象，但里面的Script是空的，导致不能进蓝图VM调用。同时也观察到这个UFunction*对象的ObjectFlags包含RF_Transient标志（意思是不保存），因此就可以用这个来把此对象过滤掉从而查找到正确的UFunction*对象。
这些函数自己再包装一下然后BlueprintCallable一下，就可以在C++和BP端都可以尽情的通过函数名字调用函数了，祝你好运！
运行时修改类型
让我们继续扩宽一下思路，之前已经详细讲解过了各大类型对象的构造过程，最后常常都是到UE4CodeGen_Private里的调用。既然我们已经知道了它运行的逻辑，那我们也可以仿照着来啊！我们也可以在常规的类型系统注册流程执行完之后，在游戏运行的半途过程中，动态的去修改类型甚至注册类型，因为说到底UE4编辑器也就是一个特殊点的游戏而已啊！这种方式有点类似C#的emit的方式，用代码去生成代码然后再编译。这些方式理论上都是可以通的，我来提供一些思路用法，有兴趣的朋友可以自己去实现下，代码贴出来就太长了。
修改UField的MetaData信息，其实可以改变字段在编辑器中的显示信息。MetaData里有哪些字段，可以在ObjectMacros.h中自己查看。
动态修改UField的相应的各种Flags数据，比如PropertyFlags，StructFlags，ClassFlags等，可以达成在编辑器里动态改变其显示行为的效果。
动态添加删除UEnum对象里面的Names字段，就可以动态给enum添加删除枚举项了。
动态地给结构或类添加反射属性字段，就可以在蓝图内创建具有不定字段的结构了。当然前提是在结构里预留好属性存放的内存，这样UProperty的Offset才有值可指向。这么做现在想来好像也不知道能用来干嘛。
同属性一样，其实参照对了流程，也可以动态的给蓝图里暴露函数。有时候这可以达成某种加密保护的奇效。
可以动态的注册新结构，动态的构造出来相应的UScriptStruct其实就可以了。
动态注册新类其实也是可以的，只不过UClass的构造稍微要麻烦点，不过也没麻烦到哪去，有需求了就自然能照着源码里的流程自己实现一个流程出来。
再甚至，其实某种程度上的用代码动态创建蓝图节点，填充蓝图VM指令其实也是可行的。只不过想了想好像一般用不着上这种大手术。
总结
本篇我们讲解了类型系统反射的应用，这些的应用知识其实都得基于对类型系统的结构含义有比较深刻的基础上。看到编辑器里的一个字段想修改它，应该就能想到在C++里肯定有对应的，就算被隐藏了，也会想到用反射去获取看看。
下篇开始讲解UObject内存管理，学习完内存管理之后，就会更有一种，心中想要哪个对象，就能立即随心所欲的去获取它的掌控感，同时也对对象应该怎么保持，什么时候被释放了，为什么被释放了，有更深刻的认识。
</code></pre>
</details>

