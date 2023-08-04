
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