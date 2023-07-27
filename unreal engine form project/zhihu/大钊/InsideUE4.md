
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

<details>
<summary>《InsideUE4》GamePlay架构（三）WorldContext，GameInstance，Engine</summary>
<pre><code>
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
</code></pre>
</details>

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>

<details>
<summary>展开查看</summary>
<pre><code>
System.out.println("Hello to see U!");
</code></pre>
</details>

注:本节来自于"zhihu"作者"大钊",仅作笔记内容浏览,侵权请联系删除