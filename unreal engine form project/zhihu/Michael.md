
<details>
<summary>UnLua原理详解</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/330790611
前言
用Lua写逻辑，是越来越多开发者的选择，它生来可热更，写完不用等编译，在线编程(一边运行一边编写)，它很香。

一、UnLua的"HelloWorld!"程序
开门见山，我们先把UnLua用起来。即，用UnLua创建一个UMG，UMG的Text里写个“Unlua的HelloWorld”显示出来，步骤如下：

1. 创建一个HelloWorldUMG↓

2、打开HelloWorldUMG，Add"UnLuaInterface"接口↓

3、创建一个HelloWorldUMG.lua文件↓

4、将HelloWorldUMG.lua的相对路径填入到HelloWorldUMG的UnLuaInterface接口实现中↓

5、在HelloWorldUMG中创建一个TextBlock↓

6、在程序入口输入以下代码↓

7、显示输出↓

二、HelloWorld程序代码讲解
我们来逐行看看，实现这个功能的Lua代码干了啥


逐行分析↑：

28 程序入口函数名 29 require了一个资源加载的管理类 30 同步加载UMG资源，并缓存加载结果 31 缓存中获取加载结果
33 实例化一个UMG 34 对UMG的centerText赋值 35 将UMG添加到视窗中显示出来
比较常见的实例化UI代码。我们先拿下面这行代码进行深入，它的功能是实例化一个UMG↓


这行Lua代码让我们很容易联想到UE4的这个函数↓


是的，Lua最终就是调到了C++的这个函数实例化出的UMG，那么问题来了：

1、为什么在Lua中调用UE4.UWidgetBlueprintLibrary.Create，可以最终调用到C++的Create函数？

2、C++的Create函数返回的是一个UserWidget对象，而Lua这边用"local UMG"接住的是一个Lua对象，是怎么做到C++这边Return一个UObject，Lua这边接住的是一个Lua Table的呢，这个C++对象和Lua对象之间又有什么关系？

3、为什么执行“UMG.centerText”，就直接可以对它进行SetText操作了？

下面，我来逐个解答。

三、源码解析：UnLua与UE4的绑定
1、问题1：为什么在Lua中调用UE4.UWidgetBlueprintLibrary.Create，可以最终调用到C++的Create函数？
（如果手上有UnLua工程，可以和我一起来啃代码。）


上图UE4.UWidgetBlueprintLibrary.Create中的"UE4"，其实就是代表_G表，是在UnLua初始化的时候赋值的↓。之所以取名UE4，是为了可切换另一种命名空间考虑，本文我们把UE4当_G表就行


那么UE4.UWidgetBlueprintLibrary，可看成_G.UWidgetBlueprintLibrary。由于UWidgetBlueprintLibrary之前没有被定义过，因此会触发G表的__Index元方法。而在Unlua初始化的时候，在这里设了G表的__Index元方法↓


因此，UE4.UWidgetBlueprintLibrary执行后，会调到上图的125行：RegisterClass(UWidgetBlueprintLibrary)，这是一个全局方法，它起源自UnLua初始化的时候给【RegisterClass】赋值为对应的C方法【Global_RegisterClass】


上图210行 lua_register的功能：将一个C function【Global_RegisterClass】放入Lua状态机的全局表中，key设为"RegisterClass"，根据Lua调用C++函数机制，lua脚本中调用RegisterClass，就会调用到C++中的Global_RegisterClass函数，并且会将lua脚本调用时的参数依次压入Lua栈中，栈底是第一个参数，次底是第二个参数，依次类推。这是Lua和C++交互的常用方法。详见lua和C++交互详细总结：https://www.cnblogs.com/sevenyuan/p/4511808.html


所以，在上图的Lua脚本中调用UE4.UWidgetBlueprintLibrary，则会将“UWidgetBlueprintLibrary”这个字符串压入Lua栈中，接着调用C方法Global_RegisterClass方法↓。


上图1627行 lua_gettop的功能：获取Lua栈顶的Index，这里插入讲一下Lua栈的index表示方法：可选择用正数index和负数index的一种表示Lua栈↓


如果想从栈顶开始数起，就用负数index：栈顶为-1，次顶为-2... ；如果想从栈底开始数起，就用正数index：栈底为1，次底为2...；两种表示方式选其一，Lua皆可识别。


回到Global_RegisterClass这个例子中，逐行分析↑：

1627 lua_gettop方法，返回的是当前栈的栈顶、并且该值以正数index的方式表示，也就是说，它返回了几，就代表了当前栈有几个元素。因为Lua调用C++将参数一次压入栈中，即，lua_gettop(L)返回了几，就代表了lua那边传进来了几个参数。根据上述传入了“UWidgetBlueprintLibrary”，所以NumParams为1。
1628-1633 容错判断，注册必须要传入参数
1634 执行结果：RegisterClass(L,"UWidgetBlueprintLibrary")
进入1634函数得到↓

1）RegisterClass

本例中传入的SuperClassName为null，因此RegisterClass分为两大块，（1）1847行，GReflectionRegistry.RegisterClass 和 （2）1849行，RegisterClassInternal

（1）GReflectionRegistry.RegisterClass
便于理解，先预告下GReflectionRegistry.RegisterClass的功能：通过字符串反射出UE4类型，记录到UnLua的反射库中，目的是为了后续Lua、C++交互调用的方便。下面我们详细介绍下是如何记录反射信息的，本例没有传入SuperClassName，撇开一些容错判断和声明，程序到上图1847行变成了：GReflectionRegistry.RegisterClass("UWidgetBlueprintLibrary",&Chain)


上图代码功能：通过对象名，用UE4的反射获取了WidgetBluprintLibrary这个对象类型，然后执行注册，即记录反射信息到UnLua的反射库中，程序到上图83行变成了：RegisterClass(WidgetBlueprintLibrary, OutChain)


上图代码功能：UnLua反射库做了一些判断是否已存在的逻辑，本例中不存在，继续往下，接着将ClassName通过字符串还原到"UWidgetBlueprintLibrary"，程序到上图112行变成了：RegisterClassInternal("UWidgetBluprintLibrary", WidgetBlueprintLibrary, Class)


上图代码功能：为“UWidgetBluprintLibrary”创建一个UnLua反射库的FClassDesc，用于记录UE4 UStruct类型信息，用作后续反射，然后记录类型名字、Struct、FClassDesc之间的映射关系，方便后续取用，同时递归它的父类，做相同的注册。这样做的原因，就是记录传入类型名对应的UE4反射信息到UnLua自己的反射库中，目的是为了后续Lua、C++交互调用的方便。


记录完这些信息后，跳出该函数，执行GetClassChain()，上图115行就是将UWidgetBluprintLibrary的父类FClassDesc依次Add进OutChain里，无需展开。至此，GReflectionRegistry.RegisterClass全部跑完了

（2）RegisterClassInternal

便于理解，先提前讲下这个函数的大体功能：它要为UWidgetBluprintLibrary，以及它的父类们分别创建一个Lua元表，元表名为UClass.ClassName，拿UWidgetBluprintLibrary来说，元表名为“UWidgetBluprintLibrary”，同时设置这个元表的一些元方法，目的是将来设这个元表给Lua，使得Lua可以和C++交互。

逐行分析↑RegisterClassInternal：

1790-1792 容错与声明，忽略
1794 获取要注册的类名“UWidgetBluprintLibrary”，这个名字在（1）GReflectionRegistry.RegisterClass时，FClassDesc已记录了下来
1796-1804 判断Lua Registry表里是否已经存在以“UWidgetBluprintLibrary”为key的元表，如果有就返回，不再创建
1805-1820 对UWidgetBluprintLibrary类型、以及它的父类一次进行RegisterClassCore操作，顺序依次是自己父类，最后是自己，拿UWidgetBluprintLibrary举例，依次是UObject、UBlueprintFunctionLibrary、UWidgetBlueprintLibrary。因为RegisterClassCore第二参数和第三个参数要求分别传入自己和自己的父类，所以分成了1805-1811和1813-1820两段，因为1811的RegisterCore的父类为nil。
可以看到，RegisterClassInternal主要是遍历自己和父类进行RegisterClassCore，重点在RegisterClassCore，RegiterCore函数的代码比较多，我们分段看。还是以传入的类型是UWidgetBlueprintLibrary情况举例

（3）RegisterClassCore

逐行分析↑：

1647 传入检查，忽略
1648-1650 前面提到，从FClassDesc的获取类型名，这里是“UWidgetBlueprintLibrary”，做了下编码转换
1651-1658 这件事前面做过，判断Lua Registry表里是否已经存在以“UWidgetBluprintLibrary”为key的元表，如果有就退出，不再创建，注意到luaL_getmetatable执行的实际是lua_getfield，所以不管有没有都会将结果压入栈中
1659 对该类型对应的UnLlua反射信息FClassDesc进行引用计数，因为将要创建的元表会使用这个FClassDesc
1661 因为1651获取的检查结果会入栈，即使结果是nil，所以栈顶pop，去掉这个结果
1662 在Lua的注册表（LUA_REGISTRYINDEX）里创建了一个新表，它在lua注册表里的key为“UWidgetBlueprintLibrary”，后面将作为元表，且新表.__name = "UWidgetBlueprintLibrary"，展开luaL_newmetatable这个函数可以看到，这里只说结果
1664-1676 如果传入参数InSuperClass不为nil，则设置新表.ParentClass=UWidgetBlueprintLibrary父类对应的元表，这也是为什么之前RegisterInternal函数里，要先从最基类开始RegisterCore的原因。注： lua_rawset(L,-3)功能：设置t[k] = v，t为Lua栈中index为-3的内容，v为栈顶，k为次栈顶，赋值完成后，从Lua栈中pop出k和v。
1677-1680 设置新表.__index = Class_Index函数
1677-1680 设置新表.__newindex = Class_NewIndex函数，用于
1684-1687 设置新表.TypeHash = UWidgetBlueprintLibrary类型的指针值，用于唯一性判断
可以看到，这部分代码就是在lua中创建了一个名为“UWidgetBlueprintLibrary”新表，然后分别为__index、__newindex定义了一个C方法，可以联想到，如果这个表作为一个lua对象的元表，那么lua找不到对象，就会调用C++的ClassIndex方法，这样就构成了Lua和C++之间的联系，创建这个元表的目的也正是如此。往下接着看。1689-1724行的代码是注册类型为UScriptStruct的情况，UWidgetBlueprintLibrary是UClass情况，不会走到这个分支，直接看1725-1757行。


可以看到，类似上部分代码，也是分别为这个新表的ClassDesc、StaticClass、Cast、__eq、__gc设置了一些C Fcuntion，注意到我总是叫它为新表，没有称为元表，因为代码至此，它确实只是一张表而已，并没有作为谁的元表。

其中值得注意的是，key为StaticClass，赋值的是一个闭包，功能就是当调用StaticClass时，C Function Class_StaticClass会被调用，同时FClassDesc的指针会同时被压入Lua栈中，因为FClassDesc的指针和C Function Class_StaticClass作为了一个闭包，赋值给了StaticClass。完成了新表的一些赋值，看下最后的操作


逐行分析↑：

1759-1761 将这个新表作为元表赋给了自己，这样这个表去索引不存在的key时，就会调用到那些元方法了
1762-1768 如果注册类型还声明了些额外的绑定方法，也会注册到这个表中
1769-1771 和 1773-1776 业务加的判断内容，忽略
1772 将这个新表放入到了lua的全局表中，这样在lua的G表中，通过名字就可以获取这个表
1777-1781 如果传入类型不是Native类型，还会将它的名字记到LibraryNames数组中，后续用于从Lua注册表和全局表中清理掉这些元表
至此，RegisterInternal的执行全部完成了。

同时，lua中调用UE4.UWidgetBlueprintLibrary，接着调到了C++的Global_RegisterClass，接着调到了RegisterClass的所有代码内容也全部执行完了，可以看到这一次简单调用，背后做了很多事情，当然，这些事情是在UE4.UWidgetBlueprintLibrary之前从未被调用过的情况下才出现的，因为经过这一次调用之后，G表中已经有UWidgetBlueprintLibrary这个key了，它对应的是RegisterClassCore函数中创建出的新表，下一次调用不会触发index元方法，直接返回这个表了。

RegisterClass总结

（1）根据传入的类型名，通过UE反射得到它的类型信息，然后记录这个类型信息，以FClassDesc（UnLua自己的数据结构）的形式存入UnLua的反射库GReflectionRegistry中，方便后续Lua、C++交互调用

（2）为传入的类型，以及它所有的父类，依次创建一个元表，然后设置一些元方法，最后记录在Lua的G表中，这样下次在Lua里调这个类型名，获得的就是创建出的G表。调这个类型里的方法，就会索引到当初注册时赋予的元方法，这也是接下来，我们要继续讲的内容。

为什么在Lua中调用UE4.UWidgetBlueprintLibrary.Create，可以最终调用到C++的Create函数？这个问题的回答，我们已经完成了一半，即UE4.UWidgetBlueprintLibrary调用时，对UWidgetBlueprintLibrary先进行了记录反射信息、创建元表等工作。下面回到下面的Lua代码。


之前是运行到125行时，触发的Global_RegisterClass，Global_RegisterClass执行完后，我们知道了在G表中，有一个以"UWidgetBlueprintLibrary"为Key的新表了，它的元表是它自己，它的一些元方法是C Function，如Class_Index、Class_NewIndex。

然后lua代码接着执行，从↑130行我们知道，返回的正是这个新表。接着代码就回到了下面的33行↓


那么Lua代码：UE4.UWidgetBlueprintLibrary.Create = 新表.Create，很明显新表里没有Create这个key，根据lua机制，这就触发了__index元方法，前面在RegisterClassCore函数的1677行设置过它的__index = Class_Index，所以此时代码会执行到这里↓

2）Class_Index

首先执行了GetField函数，函数代码比较长，分段看它做了什么事情↓

（1）GetField

逐行分析↑：

1146 lua_getmetatable的功能是获取栈上对应index内容的元表，若有则压入栈中，返回1，若无则不压入栈，返回0。又根据Lua语言特性，触发index元方法时，传入index元方法的参数有两个：被索引表和被索引的key，本例中这两个参数分别是UWidgetBlueprintLibrary表和"Create"。
又根据Lua调用C++机制，会将lua的参数压入lua栈中，因此这一行代码是获取栈底（index为1）的元表，即UWidgetBlueprintLibrary表的元表，前面我们分析RegisterClassCore函数知道，它的元表即为自己。所以元表是有的，返回1，把UWidgetBlueprintLibrary的元表（UWidgetBlueprintLibrary自己）又压入了栈中，此时的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表
1147 检查，保证被索引表必须有元表，也就是必须要之间注册过
1148 lua_pushvalue(L, 2) 功能：将栈index为2的元素复制一份，压到栈顶，此时的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、“Create”
1149 lua_rawget(L, -2)功能：获取t[k]的值压入栈顶，t为index所指内容，k为栈顶内容，获取完后将k出栈，结果入栈。即获取UWidgetBlueprintLibrary表["Create"]，我们知道，它为nil，因为没设过，所以执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、nil
1150 返回为nil，判断成立
1152 pop栈顶的nil，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表
1154 执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、"__name"
1155 获取UWidgetBlueprintLibrary["__name"]放入栈顶代替"__name"，在RegiterClassCore 函数的1662行中，我们知道，__name为“UWidgetBlueprintLibrary”，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、"UWidgetBlueprintLibrary"
1156 检查__name必须为string
1158 获取栈顶的"UWidgetBlueprintLibrary"赋值给ClassName，栈不变
1159 获取index为2的值"Create"赋值给FieldName，栈不变
1160 pop栈顶，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表
1163-1168 去unlua的反射库中，根据名字找到反射信息ClassDesc，如果找不到，则退出，调用失败
可以看到，这部分代码就是找到被索引lua表的元表，然后找到对应的反射信息FClassDesc，之前RegisterClass准备反射信息和元表的作用逐渐体现了出来。接着往下看


逐行分析↑：

1169-1170 声明和保护，忽略
1171 RegisterField，根据FieldName获取对应Field的反射信息，这里比较关键，我们先展开一下
同样代码比较长，分段看

（2）RegisterField

逐行分析↑：

111-114 容错，忽略
116-121 先去Unlua反射信息FClassDesc的缓存里去找是不是已有，有就直接返回了，没有就进到else里创建
124 通过UE4的反射接口，根据名字尝试去获取FProperty，注意到，这里的Struct是保存在FClassDesc里的，是最开始GReflectionRegistry.RegisterClass的时候存进去的
125 如果根据名字获取不到FProperty，则尝试去获取UFunction
127-153 如果要找的Field既不是FProperty，又不是UFunction，而且是结构体类型，且不是Native的，则进一步继续遍历这个结构体，找到匹配的名字赋值给Property
154 如果这三种情况尝试过了，还没找到，就退出，如果匹配到了，则继续以下内容

逐行分析↑：

159-160 获取Field的来源，如果有则继续
162 如果属性或方法来源不是自己，说明这个Field来自于基类，则把它的基类再注册一遍，返回它的基类的FieldDesc
170-173 如果Field的来源是自己，则创建一个FFieldDesc，和FClassDesc建立映射
174-186 将反射结果存入Properties或Functions中，并在FieldDesc中记住FieldIndex，正数FieldIndex表示是Property，负数FieldIndex表示是Function（从lua栈index来的灵感？），之所以要++一下，应该是为了避免FieldIndex为0区分不出正负了。
RegisterField总结

从上面看到，RegisterField借助UE4的反射机制，根据Field的字符串名字找到了对应了FProperty或UFunction，并缓存在Unlua自己的数据结构中，供后续取用。

接着我们回到GetField这里。


逐行分析↑：

1169-1170 声明和保护，忽略
1171 RegisterField，根据FieldName获取对应Field的反射信息，把对应的UE4 FProperty或UE4 UFunction存到了FClassDesc的Property表或Functions表中，并创建了FFieldDesc，用FieldIndex记住了对应表的index，其中正index表示Property，负Index表示Function
1172 判断Field是否获取成功
1173-1175 获取Field是否来自基类
1176-1188 如果获取成功，且Field来自于基类，则去基类的元表里找Create看有没有，但是本例中，Create不来自基类，所以不会走该分支
1190 在基类元表中没有找到目标Field，bCached为False，执行下面分支
1192 功能是将查询到的、或新注册的Field结果压入Lua栈中，展开看一下

逐行分析↑：

1120 容错判断，Field必须存在且有效
1121-1126 如果Field是一个属性，则获取它的FPropertyDesc，UnLua自己的反射类型，然后把它作为指针Push到Lua栈顶，此例中，Create是个Function，所以不会走到这个分支
1128-1139 如果Field是一个方法，则推入一个闭包，即C Function ClassCallUFunction + FFunctionDesc的指针。执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、ClassCallUFunction + FFunctionDesc的指针（闭包）
我们可以看到，这一步主要是把相应的FPropertyDesc指针，或FFunctionDesc指针 + CFunction函数的闭包压入Lua栈中，我们再回到GetField函数


1169-1170 声明和保护，忽略
1171 RegisterField，根据FieldName获取对应Field的反射信息，把对应的UE4 FProperty或UE4 UFunction存到了FClassDesc的Property表或Functions表中，并创建了FFieldDesc，用FieldIndex记住了对应表的index，其中正index表示Property，负Index表示Function
1172 判断Field是否获取成功
1173-1175 获取Field是否来自基类
1176-1188 如果获取成功，且Field来自于基类，则去基类的元表里找Create看有没有，但是本例中，Create不来自基类，所以不会走该分支
1190 在基类元表中没有找到目标Field，bCached为False，执行下面分支
1192 由上面展开我们知道，功能是将查询到的、或新注册的Field结果压入Lua栈中，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、ClassCallUFunction + FFunctionDesc的指针（闭包）
1193 复制index为2的内容到栈顶，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、ClassCallUFunction + FFunctionDesc的指针（闭包）、“Create”
1194 复制index为-2的内容到栈顶，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、ClassCallUFunction + FFunctionDesc的指针（闭包）、“Create”、ClassCallUFunction + FFunctionDesc的指针（闭包）
1195 lua_rawset(L,-4)功能：设置t[k] = v，t为Lua栈中index为-4的内容，v为栈顶，k为次栈顶，赋值完成后，从Lua栈中pop出k和v。也就是UWidgetBlueprintLibrary表.Create =ClassCallUFunction + FFunctionDesc的指针（闭包），可以看到，这一步完成后，再在Lua中调用UWidgetBlueprintLibrary.Create，就会直接调用ClassCallUFunction + FFunctionDesc的指针（闭包）了，不会再触发Index元方法。 执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、UWidgetBlueprintLibrary表、ClassCallUFunction + FFunctionDesc的指针（闭包）
1197-1204 如果这个Field来自基类，则设置结果到基类元表中，本例中不走这个分支
1205-1224 当RegisterField没有获取到Field的时候，也就是通过名字去UE4反射中找不到对应Field时，则尝试直接去UObjectd的元表里找
1226 lua_remove(L, -2)功能，remove掉Lua栈中，index为-2的内容，然后-2以上的内容随之下移，执行完的lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、ClassCallUFunction + FFunctionDesc的指针（闭包）
至此，执行完了GetField的所有内容。

GetField总结

GetField函数主要做了两件事：

（1）获取FPropertyDesc或者FFunctionDesc。根据传入名字找对应元表，进而找到类型名和Field名，然后去UnLua反射系统中获取对应的FPropertyDesc或者FFunctionDesc，如果FClassDesc缓存里有则直接获取，如果没有，就通过UE4反射获取并缓存到FClassDesc里

（2）将FPropertyDesc或者FFunctionDesc设置到元表中，同时将FPropertyDesc或者FFunctionDesc压入lua栈中

接着我们回到Class_Index方法，


逐行分析↑：

2229 由GetField总结可知它做了哪些事情，此时的Lua栈从底到顶情况：UWidgetBlueprintLibrary表、“Create”、ClassCallUFunction + FFunctionDesc的指针（闭包）
2230-2244 此例中，此时的栈顶是一个闭包，不是lightuserdata，不执行分支，先忽略
2245 return 1表示有一个返回参数。根据Lua和C++交互机制，调用开始时，Lua会把从左到右的Lua参数依次压入栈；调用结束时，C++会把返回值依次压入栈中，同时return返回值个数，lua会根据return的返回值个数，依次去栈顶取出返回值。此例中，返回给了Lua ClassCallUFunction + FFunctionDesc的指针（闭包）
至此，Lua中执行到代码UE4.UWidgetBlueprintLibrary.Create的内容已经全部完成，结果是返回给了Lua一个【ClassCallUFunction + 包含Create函数的FFunctionDesc指针】（闭包）

还没有执行到C++的Create方法，我们接着看。后面继续执行UE4.UWidgetBlueprintLibrary.Create(_G.GetCurrentWorld(), prefab, nil)


UE4.UWidgetBlueprintLibrary.Create此时已经是一个【ClassCallUFunction + 包含Create函数的FFunctionDesc指针】闭包，所以执行UE4.UWidgetBlueprintLibrary.Create(_G.GetCurrentWorld(), prefab, nil)时，会执行到这里↓

3）Class_CallUFunction

逐行分析↑：

2289 获取【ClassCallUFunction + 包含Create函数的FFunctionDesc指针】闭包的UpValue，即包含Create函数的FFunctionDesc指针
2290-2296 一些容错代码，忽略
2297 获取栈的长度，即参数个数，此处为3，分别是lua中的_G.GetCurrentWorld()、 prefab、 nil
2298 关键函数CallUE，我们展开看看
（1）CallUE
到这里，离回答第一个问题越来越近了。代码较长，分段看


逐行分析↑：

221-227 性能数据统计埋点、容错、声明，忽略
228-232 获取这个函数包含的实例UObject。因为Create是静态方法，所以获取它的COD对象 default__WidgetBlueprintLibrary
233-239 本例不会走到这个分支，但如果不是静态函数的情况，Lua那边的调用会用冒号":"，会把自己传进来，也会获得方法所属的UObject
241-245 容错，必须要找到Function所属的UObject
247-252 RPC Call的特殊功能，忽略
254-255 创建一个以Function 参数个数(包含返回类型)为长度的bool数组，用作后续清除标记。根据 UUserWidget Create(UObject WorldContextObject, TSubclassOf\<class UUserWidget> WidgetType, APlayerController* OwningPlayer)，数组长度为4
256 PreCall(L, 3, 1，长度为4的数组，null)，继续展开看下PreCall
（2）PreCall

逐行分析↑：

360-368 为Functon的参数提前开辟一块内存，用作后续缓存每个参数的值
370 记录递归调用次数
373 遍历UnLua反射库里，该Function的Property对象
375 获取Function的一个Property
376 初始化此Property在缓存区的位置
377-384 对于Latent类型的处理，本例没有，忽略
385-389 如果当前property是返回值类型，则先置为true，后续执行Call的时候会填入返回值到缓存区中
390-393 如果参数还没遍历完，从lua栈中，根据lua对象，在UnLua反射库和元表中，获取的C++对象，放入缓存区中，因为这里主要想回答是怎么调用到C++的Create方法的，先不展开说是如何通过Lua对象找到C++对象的，只用记住这里通过调用Property->SetValue，通过传入栈index，可以从Lua对象转换成C++对象的值，将C++对象放入缓存区中
394-407 property为Out类型的情况，本例没有，忽略
可以看到，PreCall做的事情主要是把传入的Lua参数转换成C++对象，放入Params缓存区中，然后返回这个缓存区。执行完PreCall后，我们接着看CallUE剩余部分


逐行分析↑：

258 记录调用的Function到FinalFunction中
259-301 如果Function是接口或有重写的情况，会去找相应更准确的函数赋值给FinalFunction，本例不会走到这个分支，忽略
310 本例会执行到这里，这是一个UE4接口，功能是通过虚拟机，直接传入函数的反射类型和参数缓存，实现调用这个函数，即，调用UWidgetBlueprintLibrary::Create这个C++函数，对，就是这里回答了第一个问题。这个函数也解释了为什么上面的代码要获取这个函数的UObject实例，以及为什么要把传入参数装入一个缓存区中，就是为了调用这个接口做准备。调用完后，会把返回值放入Params缓存区中
314 从Params中读出返回值，返回值是一个C++类型，然后转换成Lua对象（后面会展开将怎么讲C++类型转换成Lua对象），push Lua对象到Lua栈中，返回返回值个数。Lua那边就收到了最终的返回值
至此，我们就回答了第一个问题：为什么在Lua中调用UE4.UWidgetBlueprintLibrary.Create，可以最终调用到C++的Create函数？，这里我们总结一下回答：

4）问题1回答总结：
Lua代码执行到UE4.UWdigetBlueprintLibrary的时候，执行了RegisterClass("UWdigetBlueprintLibrary")函数，做了这样几件事：
（1） UnLua框架代码在G表里创建了一个名为【“UWdigetBlueprintLibrary”的表】
（2）为这个表定义了【C++类型的__Index元方法】
（3）将这个类型的【FClassDesc】记录到了UnLua的反射信息库中
Lua代码执行到UE4.UWdigetBlueprintLibrary.Create的时候，执行了【C++类型的__Index元方法】，做了这样几件事：
（1）通过【FClassDesc】和函数名“Create”注册Field，组装了【UFunctionDesc】，记录到了UnLua的反射信息库中
（2）在【“UWdigetBlueprintLibrary”的表】创建了key为“Create”，value为【C++函数ClassCallUFunction + 函数反射信息UFunctionDesc指针的闭包】
（3）将【C++函数ClassCallUFunction + 函数反射信息UFunctionDesc指针的闭包】返回给Lua层
Lua代码执行到UE4.UWidgetBlueprintLibrary.Create(_G.GetCurrentWorld(), prefab, nil)的时候，执行了【C++函数ClassCallUFunction + 函数反射信息UFunctionDesc指针的闭包】，也就是执行了C++函数ClassCallUFunction，做了这样几件事：
（1）执行PreCall，根据【UFunctionDesc】和Lua参数，将Lua参数转换成C++参数，再根据【UFunctionDesc】反射信息，将C++参数写入到一个缓存区中
（2）执行 UObject::ProcessEvent(FinalFunction, Params)，参数FinalFunction是UFunction，参数Params是前面保存有C++参数的缓存区。ProcessEvent执行时，即调用了真正我们想调用的C++ Create函数，然后把C++返回值放入了Params缓存区中
（3）执行PostCall，从Params缓存区中读出C++返回值，转换成Lua返回值，Push进Lua栈，返回给Lua。
以上为整个过程，可以看到，上述1、2步都是在做准备工作，主要是收集反射信息，创建元表。第3步就是根据之前的准备工作，执行调用，这也是为什么在Lua中调用UE4.UWidgetBlueprintLibrary.Create，可以最终调用到C++的Create函数的原因，问题回答完毕。

另外，上述的第3步还做了Lua和C++对象之间的转换工作，并且上面一直没有展开讲Lua和C++对象之间是怎么转换的，现在我们开始展开，其实也是开始回答第二个问题。

四、源码解析：Lua与C++对象转换
2、问题2：C++的Create函数返回的是一个UserWidget对象，而Lua这边用"local UMG"接住的是一个Lua对象，是怎么做到C++这边Return一个UObject，Lua这边接住的是一个Lua Table的呢，这个C++对象和Lua对象之间又有什么关系？
我们先看下C++的Create函数，由上面的总结答案我们知道，它是在进行到3. （2）步的时候被调用到的

（2）执行 UObject::ProcessEvent(FinalFunction, Params)，参数FinalFunction是【UFunctionDesc】，参数Params是前面保存有C++参数的缓存区。ProcessEvent执行时，即调用了真正我们想调用的C++ Create函数，然后把C++返回值放入了Params缓存区中
接着我们看下Create函数做了啥↓


从上面看到，它其实就是创建了一个新的UUserWidget，即一个新的UObjet，作为返回值返回。而在UnLua框架中，UnLua会监听每一个新的UObject的创建，并做一些准备工作，为今后的C++和Lua对象转换做准备，这也就是我们将要讲的内容。

1）NotifyUObjectCreated

UnLua监听了新UObject被创建出来的事件，回调函数是上图的NotifyUObjectCreated，因此，当C++ Create函数创建出一个新的UserWidget的时候，会调到NotifyUObjectCreated，并把新UObject传入，我们以创建出了HelloWorldUMG为例，这个UserWidget触发了回调，下面我们看看它做了什么事情。

逐行分析↑：

914-918 把所有新创建的UObject添加到一个列表中，用于后续判断Object的有效性
920-923 容错，忽略
924 类型转换
925 TryToBindLua 关键函数，展开讲解
928-943 对InputComponent的特殊处理，这里忽略
（1）TryToBindLua

逐行分析↑：

396-405 容错判断，bind要在UnLua初始化之后进行
408-409 过滤掉CDO对下和Archetype对象，不对他们进行绑定
410-426 一些容错判断，忽略

逐行分析↑：

427 这里检查UMG有没有实现UnLuaInterface接口，这句代码也是为什么第一章的HelloWorld程序中，要让UMG实现这个接口的原因，如果实现了，则走到静态绑定流程，否则走到456-459进行动态绑定，本例中只讲静态绑定的情况
428-436 获取UnLuaInterface接口里实现的方法，本例中获取的是“UAGame.Utils.HelloWorldUMG”
437-442 如果通过UnLuaInterface获取的结果为空，则直接通过ModuleName获取
443 执行Manager->Bind方法
444-461 其余一些异步加载和动态绑定的情况，本例中忽略
可以看到，TryToBindLua主要是对UObject做一些检查，把满足条件的UObject交给UnLuaManager去执行Bind，展开看一下Bind方法做了啥

（2）Manager->Bind

逐行分析↑：

56-68 容错判断，忽略
69-72 又执行到了上面讲到的RegisterClass方法，根据上面的讲解，我们知道它会做两件事，（1）记录HelloWorldUMG的类型反射信息 （2）创建一个以“HelloWorldUMG_C”为名字的元表，“HelloWorldUMG_C”是其类型GetName的结果，然后设置相应的元方法，并放入G表中。如果RegisterClass失败则退出bind，成功则继续下面代码
74-75 去缓存中检查以前是否绑定过这个lua脚本，没有则进行绑定
77 调用lua里的Require方法，获取Lua的模块代码，即路径“UAGame.Utils.HelloWorldUMG”的Lua代码，Require之后，UnLua会将该Lua模块缓存到package.loaded中，通过名字就可以获取该lua模块
81 如果Require成功，则进一步进行绑定，此时调用情况：BindInternal(UHelloWorldUMG，UHelloWorldUMG类型，"UAGame.Utils.HelloWorldUMG"， true)
（3）Manager->BindInternal

逐行分析↑：

642-645 容错判断，忽略
647-648 声明、字符编码转换
650-662 本例为bNewCrated为true，不执行，忽略
664-665 Lua Module路径名和C++类型建立映射关系，记录在ModuleNames和Classes表中
667-672 容错判断，忽略
674-675 获取“UAGame.Utils.HelloWorldUMG”Lua模块的所有方法名，记录在ModuleFunctions数据结构中
676-677 获取HelloWorldUMG类型所有可重写的函数反射信息，记录在OverridableFunctions数据结构中
679 判断Lua Module中的方法名，有没有和HelloWorldUMG函数名重名的，如果有，则将原Function的调用重定向为Lua方法的调用，将原Function的执行代码保存在一个新的函数中，新的函数名为函数原名+“Copy”，可自行展开函数查看细节
681 对动画Notify函数进行重写
我们看到，BindInternal方法主要是绑定了Lua模块和它对应的C++对象的反射类型，做了两件事情：

（1）将Lua模块名和C++对象的反射类型记录在ModuleNames、Classes表中

（2）如果Lua模块的方法中，有和C++函数同名的方法，则直接拿这个C++函数的反射信息进行改写，改写为执行Lua方法

至此，BindInternal的内容就执行完了，现在我们回到Bind函数↓


逐行分析↑：

85-92 Object是Class的继承类型的情况，本例不是，先忽略
94 把Lua模块路径，即“UAGame.Utils.HelloWorldUMG”缓存到一个列表里，便于后续统一清理这些已Require的Lua模块
95 根据新生成的UObject和对应的Lua模块路径，新创建一个Lua对象，这里比较关键，展开看
（4）NewLuaObject

逐行分析↑：

835 获取Lua栈顶的Index
836 获取ObjectMap表放入栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表
837 把UObject的指针Push到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）
838 栈顶创建一个LuaInstance，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance
839 push了一个包含UObject的userdata到，具体展开看下
（5）PushObjectCore

逐行分析↑：

539-544 容错判断，忽略
546 创建一个userdata，是一个二级指针，注意lightuserdata和userdata的区别，lightuserdata就是用来保存一个指针，是不会被Lua GC的，而userdata是lua分配了一块特定大小的内存，不用是会被GC掉的。执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata
547 将这个二级指针指向了UObject的指针
548 标记这个userdata为二级指针
550 获取这个对象类型
551-557 如果是结构体对象，则将“UObject”表设为userdata的metatable，“UObject”表是在RegisterClass的时候注册的
558-579 如果是UClass对象，将“UClass”表设为userdata的metatable，如果是UObject实例，则将类型名对应的元表设为userdata的metatable
一句话总结，PushObjectCore函数就是在lua栈中创建了一个userdata，然后将它的值设为一个指向UObject指针的指针，它的元表设为RegisterClass时创建的、类型对应的元表。回过头来看NewLuaObject


逐行分析↑：

835 获取Lua栈顶的Index
836 获取ObjectMap表放入栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表
837 把UObject的指针Push到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）
838 栈顶创建一个LuaInstance，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance
839 PushObjectCore函数在lua栈中创建了一个userdata，然后将它的值设为一个指向UObject指针的指针，它的元表设为RegisterClass时创建的、类型对应的元表。执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)
840 Push "Object"到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、“Object”
841 复制index为-2的内容到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、“Object”、userdata(指向UObject指针的指针，元表为“类型元表”)
842 LuaInstance.Object = userdata，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)
845 获取Lua模块到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块
846 获取userdate的元表，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块、Object元表
847-853 容错判断，忽略
855 Push "Overridden"到栈顶，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块、Object元表、“Overridden”
856 执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块、Object元表、“Overridden”、Object元表
857 Lua模块.Overridden = Object元表。执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块、Object元表
859 Lua模块.metatable = Object元表。执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)、Lua模块
860 LuaInstance.metatable = Lua模块。执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、userdata(指向UObject指针的指针，元表为“类型元表”)
861 执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance
862 执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance、LuaInstance
863 luaL_ref(L, LUA_REGISTRYINDEX)功能：在Registry表中，创建一个对象，对象是当前栈顶的元素，即LuaInstance，然后返回创建对象在Registry表中的索引值，同时pop栈顶对象。因为Registry表是全局表，因此LuaInstance之后就不会被GC，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表、Object指针（lightuserdata）、LuaInstance
865 广播绑定事件
867 ObjectMap.lightuserdata = LuaInstance，执行完的Lua栈从底到顶情况：旧栈顶、ObjectMap表
868 执行完的Lua栈从底到顶情况：旧栈顶
870 返回LuaInstance在lua registry表中index
总结一下，NewLuaObject一共进行了一下操作：

Lua中创建了一个新表：LuaInstance
设置LuaInstance.Object = userdata(UObject二级指针，其元表为“类型元表”)
设置LuaInstance.metatable = Lua模块
将LuaInstance存入Lua Registry表，并返回Index
设置Lua模块.metatable = 类型元表
设置Lua模块.Overridden =类型元表
设置ObjectMap.lightuserdata(Object指针) = LuaInstance
回到Bind函数继续看↓


95 上面总结过，主要是创建了一个Lua对象，做了一些设置
96-100 容错操作，忽略
101 将该UObject放入UE4全局引用中，这样该UObject之后不会被GC掉，并将UObject和Lua对象在Registry表里的索引作为key、value放入AttachedObjects中，这个Lua对象和UObject进行了绑定
103-125 对Lua对象，push一个Initialize方法进去并执行
至此，Manager->Bind函数全部执行完毕，而新UObject创建后触发NotifyUObjectCreated调用的内容，其实就是从新UObject中，尝试获取UObject绑定的Lua脚本路径，然后进行Manager->Bind。总结一下Manager->Bind做了哪些事情：

（1）Manager->Bind绑定的是：新创建的UObject + Lua 对象（根据新创建的UObject找到lua路径后创建的） （2）为新UObject 注册（RegisterClass）元表 （3）根据Lua模块，重写新UObject中可被重写的的UFunction的反射信息，注意这里是直接在UFunction上改写 （4）创建Lua对象，并做设元表、设Object等变量、放入全局引用等初始化，并把Lua对象和lightuserdata（UObject指针）的映射放入ObjectMap中，ObjectMap是Lua中的对象 （5）使新UObject被全局持有，并把Lua对象索引和UObject映射放入AttachedObjects中，AttachedObjects是C++中的对象，和Lua中的ObjectMap对象相似

可以知道，当新的UObject实例被创建时，UnLua做了这些准备工作，然后把Lua对象和C++对象的映射保存了起来，C++存在AttachedObjects中，Lua存在ObjectMap中，容易猜到这是在后面的转换做准备。

继续回到问题2本身，上面NotifyUObjectCreated被触发的时机，是在C++执行Create函数后，也就是在执行CallUE函数的310行时，执行的Create函数↓


由上面我们知道:

310 接口功能是通过UE4的虚拟机，直接传入函数的反射类型和Params缓存，实现调用Create函数调用完后，会把返回值放入Params缓存区中
也就是执行这个行代码后，触发了NotifyUObjectCreated，创建了UObject元表、新的Lua对象、将C++对象和Lua对象进行了绑定，为后续的转换做准备。接着我们再次看下PostCall做了哪些事情。

2）PostCall

上面代码是找到作为函数返回值的Property，本例中代码会执行到433↑，展开会执行到这里

（1） Property->GetValue

GetValueInternal是一个虚函数，对于返回值是UObject的情况，会执行到这里↓


因为不是一个数组，会执行到203，然后通过ObjectBaseProperty->GetObjectPropertyValue(ValuePtr)，从Params缓存中取出了Create函数的返回值，UserWidget。所以最终会执行到这里↓

（2） PushUObject

这里是回答问题2的关键地方了，逐行分析↑：

381-387 容错，忽略
388 从LuaRegistry表中获取ObjectMap，执行完lua栈从底到顶情况：ObjectMap表
389 将Object指针作为lightuserdata Push到栈顶，执行完lua栈从底到顶情况：ObjectMap表、lightuserdata
390 获取ObjectMap.lightuserdata，在NewLuaObject函数分析时，我们知道，Lua对象和C++对象绑定在了ObjectMap中，所以此时会获取到之前绑定的LuaInstance，即代码路径在“UAGame.Utils.HelloWorldUMG”的lua对象实例。执行完lua栈从底到顶情况：ObjectMap表、LuaInstance
391-404 这个分支为没有获取到Lua对象的情况，本例没有。这里展开讲一下，没有获取到的情况是存在的，比如后面我们即将要讲的UMG.centerText的centerText就是没有lua绑定的，此时取出来就为nil，然后会为centerText创建一个userdata返回给lua，并在ObjectMap中和属性对象进行绑定。也就是说，有lua绑定的UObject传LuaInstance给Lua，没lua绑定的UObject传UserData给Lua
我们看到，问题2：C++的Create函数返回的是一个UserWidget对象，而Lua这边用"local UMG"接住的是一个Lua对象，是怎么做到C++这边Return一个UObject，Lua这边接住的是一个Lua Table的呢，这个C++对象和Lua对象之间又有什么关系？的解答就发生在PushUObject中，具体做法是：根据返回值UObject的指针，去Lua栈中的ObjectMap中取出Lua对象放入栈顶，这样代码执行完后，Lua那边收到的就是一个Lua对象了，这Lua对象就是“UAGame.Utils.HelloWorldUMG”的lua对象实例。

3）问题2回答总结：
在lua CallUE函数执行到 UObject::ProcessEvent(FinalFunction, Params)时，调用了C++Create函数，这时创建了一个新的UObject，触发了NotifyUObjectCreated回调，在这个回调中，根据UObject创建了Lua对象，并将Lua对象和UObject的映射关系保存在了Lua中的ObjectMap中
在Lua CallUE函数执行到PostCall的时候，根据Params缓存区的返回值，在ObjectMap中索引到了对应的Lua对象，将这个Lua对象返回给了Lua
以此实现了Lua对象和C++对象之间的转换，Lua对象和C++对象之间的关系：

Lua对象的元表是“UAGame.Utils.HelloWorldUMG”Lua模块，该Lua模块的元表是通过RegisterClass创建出的UObject元表，它里面包含了UObject的反射信息、Class_Index元方法等内容可供与C++交互，同时Lua对象的Object对象存有UObject的二级指针，可通过该Lua对象取到UObject。

因为元表的缘故，该Lua对象可以根据名字去匹配取用到对应UObject的属性、函数，进而实现Lua代码中调用到C++的接口。如下图所示。


下面就到了回答第三个问题的部分，根据上述描述，相信读者对第三个问题的答案应该有个大概的解答了，我们继续展开看一看

3、问题3：为什么执行“UMG.centerText”，就直接可以对它进行SetText操作了？
从问题2我们已经知道，上图的UMG是一个Lua对象，在NewLuaObject函数中创建出来的，它的元表是“UAGame.Utils.HelloWorldUMG”Lua模块（见NewLuaObject函数860行），后续简称Lua模块，Lua模块即我们最开始创建的lua脚本↓


它是一个LuaUnrealClass，UnLua在这里设置过它的__index元方法↓


1）LuaUnrealClass.__index

当执行UMG.centerText时，会触发__index元方法调用，即调用上图_.Index(Lua模块, "centerText")，逐行分析↑：

4 获取Lua模块的元表，根据NewLuaObject函数的859行我们知道，Lua模块的元表是"UHellowWorldUMG_C"表（RegisterClass创建的元表）
6-13 遍历元表的k、v，看是否已存在“centerText”这个key，本例第一次取的时候不存在，跳过本分支
14 直接索引元表的centerText，因为不存在，所以会触发"UHellowWorldUMG_C"表的元方法Class_Index，上面展开过Class_Index，功能是根据属性名找出反射信息，组装成FPropertyDesc这个结构，保存在UnLua反射库中，然后作为Lightuserdata返回给Lua
15-16 返回的是一个userdata，走到这个分支，调用GetUProperty(LuaInstance, centerTextFPropertyDesc)，GetUProperty全局注册过


最终会到C++的Global_GetUProperty方法

2）Global_GetUProperty

逐行分析↑：

1887 传入时Lua栈从底到顶情况：LuaInstance，centerTextFPropertyDesc(lightuserdata)
1889 将lightuserdata转成userdata，准备传回给Lua
1894 通过LuaInstance，获取UObject，在上面的NewLuaObject函数的842行我们知道，LuaInstance的Object变量保存有UObject的二级指针，因此通过LuaInstance就可以直接获取到
1898 这里的Property->Read最终调到的也是GetValueInternal


接着会执行PushUObject



上面PushUObject函数的391行分析时讲过，因为centerText没有绑定的LuaInstance，所以取出的为nil，因此会创建一个userdata，然后将它的值设为一个指向UObject指针的指针，它的元表设为RegisterClass时创建的、类型对应的元表，然后返回给Lua

因此，Lua执行到"UMG.centerText"时，返回给了Lua一个userdata，userdata的元表是对应类型RegisterClass出的元表。后面再调用SetText函数，就是和之前一样的套路了，触发元方法，根据FieldName找到UFunction，根据userdata去ObjectMap中找到UObject，然后返回一个包含函数和反射信息的闭包，然后PreCall、UObject::ProcessEvent、PostCall，最后将结果返回给Lua，不再赘述。至此，问题3也回答完毕。

再次回到问题3：为什么执行“UMG.centerText”，就直接可以对它进行SetText操作了？

3）问题3回答总结：
因为上面Create返回的UMG是一个LuaInstance，之前设置了它的元表，并且在Lua的ObjectMap中将它和相应UObject进行了绑定，调用到centerText时，通过反射和映射关系，找到了对应UObject和属性信息，然后又创建了一次新的Userdata以及对应关系放回给了Lua，最后再用这个Userdata调用SetText，和之前调用Create函数一样，触发元方法，根据FieldName找到UFunction，根据userdata去ObjectMap中找到UObject，然后返回一个包含函数和反射信息的闭包，然后PreCall、UObject::ProcessEvent、PostCall，最后将结果返回给Lua，完成一整套调用。

以上，通过一个例子回答了三个问题铺开了对UnLua原理的讲解，希望能帮助到你 =)

REFERENCE
[1] Lua函数解析

[2] UnLua解析（一）Object绑定lua

[3] UnLua解析（二）使用Lua函数覆盖C++函数

[4] [UnLua解析（三）Lua访问Object的property和function

[5] UnLua解析（四）数据在C++和lua间的相互传递

[6] Lua和C++交互详细总结

[7] Lua调用原理展示

[8] 《InsideUE4》UObject（二）类型系统概述

[9] 《InsideUE4》UObject（四）类型系统代码生成

[10] UE4 垃圾回收

[11] UE4 垃圾回收（二）GC Cluster

[12] Lua5.3版GC机制理解

[13] 关于 Lua 内存泄漏的检测

[14] Lua的hook机制及内存泄漏检测
</code></pre>
</details>