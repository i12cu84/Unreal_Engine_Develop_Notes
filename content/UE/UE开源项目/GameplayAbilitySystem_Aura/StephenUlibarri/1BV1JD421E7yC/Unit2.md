P1 The Gameplay Ability System
GAS概述

P2 The Main Parts of GAS GAS主要部分
Ability System Component 能力系统组件
Attribute Set 属性集
Gameplay Ability 能力
Ability Task 任务
Gameplay Effect 效果
Gameplay Cue 提示
GamePlay Tag 标签

P3 The Player State (状态类分配,这是在GameMode中的Player State Class中)
NetUpdateFrequency=100.f; //服务器尝试更新客户端的频率
//5.5更新为SetNetUpdateFrequency(100.f)

P4 Ability System Component And Attribute Set 能力系统组件和属性集
添加插件 Gameplay Abilities
Abilitysystemcomponent蓝图类

需要在Target.cs中添加"GameplayAbilities" "GameplayTags" "GameplayTasks"三个模块

P5 GAS in Multiplayer GAS 在多人游戏中的使用
Dedicated Server 专用服务器
-> No human player 没有人类玩家
-> No rendering to a screen 没有渲染到屏幕上
Listen Server 监听服务器
-> Is a human player 是一个人类玩家
-> Host has the advantage - no lag 主机有优势 - 没有延迟

server is the authority 服务器是权威
-> "correct" version of the game 游戏"正确"的版本
-> We do "important" things on the server 我们在服务器上做"重要"的事情

游戏模式仅存在于服务器上,因而相关逻辑会在服务器中处理
客户端只在机器上有对玩家0控制器的访问
只有服务器拥有游戏中的所有玩家控制器,并可以访问

HUD/Widgets/Client等都只存在于该客户端(并且客户端之间有内容上的差别),每个客户端只有自己的HUD等任何相关小部件显示在自己的屏幕上,并且无法访问其他客户端的HUD等小部件信息(这相当于复制)

服务器上存在Variable(变量),它会将数据分发到每一个客户端上(这个过程成为复制)(注意,该数据的复制是单向的,标记为复制时,不应该在客户端上对其进行更改)->服务器是权威

P6 Constructing the ASC(AbilitySystemComponent) and AS(AttributeSet) 构建能力系统组件和属性集
TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent; //能力系统组件
TObjectPtr<UAttributeSet> AttributeSet; //属性集

AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent"); //创建能力系统组件
AbilitySystemComponent->SetIsReplicated(true); //设置能力系统组件为复制

AttributeSet =CreateDefaultSubobject<UAttributeSet>("AttributeSet"); //创建属性集

P7 Replication Mode
AbilitySystemComponent->SetReplicationMode(EGameplayAbilityReplicationMode::Mixed)//为了玩家控制角色,(经验法则)
PlayerState使用Mixed,Enemy使用Minimal

复制的行为模式选择:
|Replication Mode|Use Case|Description|
|-|-|-|
|FuLL|Single Player|Gameplay Effects are replicated to all clients|
|Mixed|Multiplayer Player-Controlled|Gameplay Effects are replicated to the owning client only. Gameplay cues and Gameplay Tags replicated to all clients.|
|Minimal|Multiplayer, Al-Controlled|Gameplay Effects are not replicated. Gameplay Cues and Gameplay Tags replicated to all clients.|
译:
|复制模式|用例|描述|
|-|-|-|
|Full|单人|游戏效果复制到所有客户端|
|Mixed|多人玩家控制|游戏效果只复制到拥有的客户端。玩法提示和玩法标签复制到所有客户端|
|Minimal|多人,al控制|游戏效果不复制。玩法提示和玩法标签复制到所有客户端|

P8 Init Ability Actor Info 初始化能力演员信息
AbilitySystemComponent->InitAbilityActorInfo(this, this); //初始化能力演员信息

AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this); //初始化能力演员信息
AbilitySystemComponent=AuraPlayerState->GetAbilitySystemComponent(); //获取能力系统组件
AttributeSet=AuraPlayerState->GetAttributeSet(); //获取属性集

For Mixed Replication Mode: The ownerActor's owner must be the controller.
对于混合复制模式:拥有者的所有者必须是控制器。
For Pawns, this is set automatically in PossessedBy().
对于Pawn,这将在PossessedBy()中自动设置。
The Playerstate's Owner is automatically set to the controller.
Playerstate的所有者将自动设置为控制器。
Therefore, if your ownerActor is not the Playerstate, and you use Mixed Replication Mode.
因此,如果您的ownerActor不是Playerstate,并且您使用混合复制模式。
you must call Setowner()on the OwnerActor to set its owner to the controller.
您必须在OwnerActor上调用Setowner()将其所有者设置为控制器。
