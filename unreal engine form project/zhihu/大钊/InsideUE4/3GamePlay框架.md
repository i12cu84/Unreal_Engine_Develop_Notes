
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