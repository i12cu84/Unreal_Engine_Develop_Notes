
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

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>
