虚幻编译工具 UnrealBuildTool（UBT，C#）：是一个自定义工具，负责管理通过各种编译配置来编译虚幻引擎4（UE4）源代码的过程。

该工具处理所有复杂的项目编译工作，编译UE4的逐个模块并处理依赖等。我们编写的Target.cs，Build.cs都是为这个工具服务的。 

并将项目与引擎关联起来。该过程以透明方式进行，这样，您只需通过标准的Visual Studio 构建工作流程构建项目即可。

详解:
https://zhuanlan.zhihu.com/p/400473355

为什么模块代码文件要区分Public和Private目录?
答:是为了满足模块导出(从模块导出类或者函数供其它模块使用)机制.因为模块里的代码默认是不暴露(导出)给其它模块的,所以UE4约定:把需要导出(全导出或部分导出)给其它模块使用的代码文件的头文件放在模块的Public目录下.

模块默认不暴露任何类或函数(如何暴露(导出)请看PPT)
不想暴露的头文件可以放进Private文件夹
不会被其它模块引用的模块,可以不区分Public/Private文件夹.(比如游戏(主)模块)
Public目录下只放头文件,因为.cpp文件放这里,其它模块也无法' #include "xxx.cpp" '.
IncludePathModuleNames,DependencyModuleNames的区别?
答:

*注意,问题里没有Public/Private前缀
二者都能使本模块可以包含其它模块Public目录下的头文件,从而调用函数.

但IncludePathModuleNames只能调用定义全部在头文件里的函数.

// Class.h
void A()
{
    B(); // 假设B的定义在.cpp文件中,那么这时A的函数实现由B组成,但B不在头文件中.
}

则此时使用IncludePathModuleNames时,无法调用函数A.(报错:无法解析的外部符号B)
因为在编译时会将包含的头文件的内容都拷贝一份到.cpp里,所以定义全部在头文件里的函数能正常工作.
而这带来的问题是:同一个函数,被编译多次(根据它被包含的次数),在大型项目里将拖慢编译速度.
所以我们为了让函数只编译一次,才会把函数定义放在cpp文件里.
使用DependencyModuleNames时,会进行对两个模块进行链接.故不存在此问题.

只有与其它模块链接之后,才能使用其它模块的定义在.cpp里函数(若使用了定义在.cpp内函数,但又没将引用到的模块添加到DependencyModuleNames,就会获得"无法解析的外部符号(unresolved external symbol)"错误)
*IncludePathModuleNames是过时的用法,现在一般只用DependencyModuleNames
PublicIncludePathModuleNames, PublicDependencyModuleNames的区别?
PrivateIncludePathModuleNames, PrivateDependencyModuleNames的区别?
PublicDependencyModuleNames, PrivateDependencyModuleNames的区别?
答答答:要回答这个问题,除了要理解"Include与Dependency",就剩明白Public和Private的含义.

其实我也是到现在才完全明白,它俩其实和C++里的访问控制符是类似的,只是多了点小细节

C++中则是控制成员和函数,在模块这,控制的是模块之间"包含/依赖"关系的公/私有
并且它跟目录的Public/Private没太大关系.模块的Public/Private目录只用来控制代码的暴露与否

(我自己之前总把这些ModuleNames联系到目录的公私有,两模块之间的关系,就..无法理解...
现在才明白,"Public与Private"描述的是三个模块以上的关系,与目录无关)

*由于IncludePathModuleNames已过时,下面只讨论DependencyModuleNames.

结论:Private隐藏所有信息,Public只传递头文件信息.链接永不传递,需显式在Build.cs里添加.

对于三个模块,无法获得Private中模块的任何信息,可以获得Public中模块的头文件信息.
对于两个模块Public/Private无意义.(可以随意用)
最终结论:建议只使用PrivateDependencyModuleNames.杜绝迷惑.(但应该考虑过多模块静态链接的问题？)


几种我想到的情形图解,对了,大佬的PPT里还有更形象的图片
图片源文件下载



MinimalAPI说明符的作用?
答:暴露(导出)该类的类型信息让其它模块可以

Cast到该类型
继承该类型 (该类型的所有定义在.cpp文件的虚函数都需要导出)
使用内联函数
[YourModuleName]_API宏的作用?
答:

放函数声明前用于暴露(导出)该函数
放类声明前用于暴露(导出)该类的所有内容
如何正确的包括头文件(使用来自其它模块的类)?
答:首先找到该头文件的完整路径


获取完整路径的方式之一
在.h或cpp中包括头文件#include "Path" : Path是完整路径中Classes或Public的斜杠之后的部分
Classes目录是过时的东西,现在都放在Public目录下
在build.cs中添加模块关系 : 模块名是完整路径中Classes或Public之前的部分
模块的类型有多少种可以选择?
答:请查看Projects模块中的EHostType::Type.(UBT里也能找到一样的定义)

Engine/Source/Runtime/Projects/Public/ModuleDescriptor.h
Engine/Source/Programs/UnrealBuildTool/System/ModuleDescriptor.cs
模块的加载时期的有多少种可以选择?
答:请查看Projects模块中的ELoadingPhase::Type.(UBT里也能找到一样的定义)

Engine/Source/Runtime/Projects/Public/ModuleDescriptor.h
Engine/Source/Programs/UnrealBuildTool/System/ModuleDescriptor.cs
Precompiled Headers(PCH)文件有什么用?
答:由于编译代码时一般不会单独编译头文件,头文件被包含到每个.cpp里,随着.cpp文件一起编译.因此当多个.cpp包含同一份.h时,就带来了重复编译的问题.

于是PCH出现了,这个文件里的头文件只会被编译一次.

PCH包含了所有最常使用的头文件
优先编译
仅在这些最常使用的头文件发生变化时,重新编译一次
包含了PCH的.cpp也会重新编译
最好用在引擎代码或者那种很少变动的代码
Private PCH 和 Shared PCH又是什么?有啥用?
答:它俩是特殊一点的PCH,只需记住几（×）1（√）点，

Private PCH是给本模块用的PCH，Shared PCH是给依赖本模块的模块用的PCH
一个模块可以使用其他模块定义的Shared PCH
一个模块不能使用自己定义的Shared PCH
模块对PCH的选择只有三个：
-使用本模块定义的Private PCH
-使用引擎自动从本模块依赖的模块定义的Shared PCH中,选出一个最佳PCH
-不使用PCH
两者需要在模块的build.cs文件中手动指定

PrivatePCHHeaderFile = "FooBarPrivatePCH.h";
SharedPCHHeaderFile  = "FooBarSharedPCH.h"
//变量定义在
//Engine/Source/Programs/UnrealBuildTool/Configuration/ModuleRules.cs
不要手动在模块的.h/.cpp中包含该文件
UBT会自动把它注入到每个被编译的.cpp中
PCH应该是一种优化层面的东西
不要把它当作一种快捷的"include all"的方式,还是要坚持"IWYU,只包含用到的东西"
你的代码在没有PCH的时候,也能编译通过
对于Shared PCH

UE4将自动选择最优的Shared PCH，最终的目的是让选择的Shared PCH尽可能多的涵盖本模块用到的头文件。
Shared PCH的选择范围是本模块依赖的模块中定义的Shared PCH

假如模块A依赖Slate，Core以及CoreUOject模块，且没定义Private PCH，
且只有Slate及Core模块中定义了Shared PCH，
那么，A的Shared PCH就只能从Slate, Core两个模块中选
选哪一个呢？

基于得分来选择——以它俩依赖的<定义了Shared PCH的>模块数量来作为它们的分数

假设Core模块依赖了TraceLog, Json,假如只有TraceLog模块中定义了Shared PCH,
那么它得1分

假设Slate模块依赖了Core, SourceControl, Json模块，假如Json模块中定义了Shared PCH，
那么它得2分(Core 1 + Json 1)

而且很容易看出，由于Slate的依赖项里包含了Core,那么它Shared PCH很可能包含了大部分Core模块里的头文件，以及其它额外的头文件，这样，我们就会理所当然的选择使用Slate的Shared PCH，因为我们的模块使用到的头文件，也在Slate的Shared PCH里的概率更大。

因此我们将会选择Slate模块的Shared PCH作为本模块的PCH。
它是一个用于给依赖于本模块的模块使用的PCH
在UE4的一些重要且常用的模块里可以看到它
具体来说:UnrealEd, Engine, Slate, CoreUObject, Core 等.
多个模块使用同一个Shared PCH时,它也只会编译一次


IWYU是什么?有什么作用?
答:IWYU就是Include-What-You-Use,类似于一种代码规范,正确的说法或许是依赖模型(dependency model, 描述文件之间的依赖关系).

在工程中应用IWYU将会带来减少编译时间与重编次数以及利于重构等多种好处.

详解:
https://zhuanlan.zhihu.com/p/107270501  

对于模块自身，他依赖的父模块放在这两个文件夹中无所谓 没有区别
但是对于依赖于该模块的子模块 ，只能访问到publicDependency中模块暴露出来的类

例如 C依赖B B依赖A
那么 假如C想访问A中的类 那么有两种方式
一种是在C的依赖中添加上A模块
另一种就是确保B在public依赖中添加的A模块，这样c就可以间接的访问到A

原文链接：https://blog.csdn.net/maxiaosheng521/article/details/79174337