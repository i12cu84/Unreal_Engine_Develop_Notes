虚幻UE引擎VR虚拟现实游戏套件VRGK – Virtual_爱给网_aigei_com

VRGK是一个以游戏为中心的蓝图包，可让快速启动下一个VR游戏项目，从完全基于物理的玩家 Pawn，到手部交互和碰撞声音，它还包括许多已经可以玩的示例内容。

商城文档中显示:
UE 4.27 -> VRGK v3.0
UE 4.25, 4.26 -> VRGK v2.1
本文默认是VRGK v2.1

相对V1来说更新内容
更新了整体关卡场景,将大部分功能内容蓝图旁边添加了英文看板

---

1.4.27版本项目,在5.2版本中默认启动会导致"Get Finger Curls and Splays"节点丢失的问题

添加以下插件(一共四个,不分先后)并重启即可
```
1.Oculus VR(deprecated) (这个应该可以不用添加)
2.OpenXR
3.OpenXRHandTracking
4.StreamVR(deprecated)  (这个应该可以不用添加)
```
---

2.将字符转为中文后,显示乱码

[解决方法](../../UEeditor/用户界面(User%20Interface)/字体(Font)/中文显示问题.md)

---

3.UE4构建光照时，启动Swarm连接卡住

1.启动reg格式文件修复注册表
```
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Lsa\FipsAlgorithmPolicy]
"Enabled"=dword:00000000
```
2.运行文件C:\Program Files\Epic Games\UE_5.2\Engine\Binaries\DotNET\SwarmAgent.exe
3.如果有红字，卸载所有net framework，并且打开360》系统修复》补丁管理，卸载net framework无关紧要的补丁
接着，去下载个net framework 4.6.2

---

[VRGK V2 文档](https://itchio-mirror.cb031a832f44726753d6267436f3b414.r2.cloudflarestorage.com/upload2/game/2174829/8330585?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=3edfcce40115d057d0b5606758e7e9ee%2F20250408%2Fauto%2Fs3%2Faws4_request&X-Amz-Date=20250408T060949Z&X-Amz-Expires=60&X-Amz-SignedHeaders=host&X-Amz-Signature=afeea3796a2b41ee5d0888646ffc89fdf89753da02de8caa70f82c28cd4f71f1)

---

<details>
<summary>项目中的文本内容(机翻)</summary>

这是一个虚拟现实游戏套件的演示。

VRGK是一个基于蓝图的虚幻引擎市场的资产包，它可以帮助你快速开始你的下一个VR游戏的想法。

请花时间来探索这个演示！

您可以在下面找到有关控件的信息。
---
你想了解一下VRGK吗？

从这里开始，熟悉VRGK如何工作以及如何使用它的一些基本概念。

>>重要信息<<
使用VRGK需要您具备以下知识：

---虚幻引擎
——蓝图
--- VR开发

（不需要c++）
---
这是一个虚拟现实游戏套件的演示。

VRGK是一个基于蓝图的虚幻引擎市场的资产包，它可以帮助你快速开始你的下一个VR游戏的想法。

请花时间来探索这个演示！

您可以在下面找到有关控件的信息。
---
除了您可以在这里找到的信息之外，还有一个完整的独立文档网站，可以提供更多详细信息！
虚拟现实游戏工具包（简称：VRGK）是一个专注于游戏的蓝图包，让你的下一个VR游戏项目快速启动。

从完全基于物理的玩家棋子，到手的交互和碰撞声音。
它还包括许多您已经可以玩的示例内容！
在开始开发或考虑购买VRGK之前，您应该通读文档。它是公开可用的！


至:
https://assets.divivor.eu/vrgk

（该链接也可以在官方虚幻引擎市场的VRGK产品页面上找到。）
---
除了您可以在这里找到的信息之外，还有一个完整的独立文档网站，可以提供更多详细信息！

在开始开发或考虑购买VRGK之前，您应该通读文档。它是公开可用的！


至:
https://assets.divivor.eu/vrgk

（该链接也可以在官方虚幻引擎市场的VRGK产品页面上找到。）

---

大家好!

我是divvor，我是VRGK的独立开发者。

虚拟现实游戏套件已经成为我自己未来VR游戏项目的基础模板。这些VR游戏问世还需要一段时间，但这并不能阻止其他开发者使用这个包并使用它制作出令人惊叹的游戏！

我低估了有多少人对VRGK 1.0感兴趣，所以我希望VRGK 2.0的发布会比1.0的发布更大。感谢我在过去几个月里收到的所有反馈，我能够改进这个系统的几乎每个部分。一些主要的改进和许多小的改进。

既然你正在阅读这篇文章，这可能意味着你正在玩演示或已经从官方虚幻引擎市场购买了VRGK。不管是什么原因，谢谢你的到来！
（除非你没有从我卖这个包的唯一官方来源得到它，在这种情况下，没有感谢你。）

---

VRGK被设计成模块化和可重用的。
这包括使用角色类作为所有VR小兵的基础。

重要的是要知道，这并不意味着它利用了UE4的默认角色移动功能。
以Physics Pawn为例，它就完全禁用了这一功能。
然而，如果你想在你的游戏中使用默认的UE4角色移动，
你可以在使用大多数VRGK功能的同时做到这一点。

---

物理就是一切！

重要的是要理解VRGK提供的所有内容都是基于物理的。这也意味着你必须知道一点关于物理如何在虚幻引擎工作之前
开始在你的项目中使用VRGK。


如果你想创建一个不需要或不想要物理交互的项目，那么VRGK可能不是你想要的。

---

VRGK包括一个复杂的VR手Actor，它可以做很多事情！

完全完成了物理交互，它允许你抓取，拉和触摸任何物体。你也可以决定使用自定义动画的手交互或让手指姿势计算一个新的姿势，基于碰撞。

---

VRGK支持虚幻引擎本身支持的每一个VR头显。唯一的限制可能与输入配置有关，但您可以自己轻松添加这些限制。

---

我得到了很多问题，如果VRGK可以做X或支持Y。

下面是简短的回答：
可能!但你必须自己知道如何使用它！

VRGK不能工作/支持所有开箱即用的东西，这是不可能的。我们希望您能够自己集成或开发功能。这些可以是：
-第三方插件或资产
- VRGK不使用的UE4功能
-虚幻的未来版本
等。

---

我不提供与这些平台相关的直接支持。

但这并不意味着VRGK不起作用！
它确实工作得很好！

然而，目前的VR市场使得一些地区难以使用和访问流行的移动VR头显。
目前我不可能为这些提供直接的支持或优化。

---
VRGK目前不支持多人游戏！

为什么?
这个项目是由单个开发者开发的，现实情况是，它很难提供多人游戏功能。

目前的开发重点是首先让VRGK尽可能适合单人模式。之后将开始开发多人游戏功能。

请注意，这还没有日期！

---
在这个区域你可以选择和自定义你的玩家棋子。

VRGK提供了不同而独特的游戏风格，所以请随意尝试。
现在去造一个兵卒吧！


>>重要信息<<
并不是这个演示的所有区域都针对每个棋子和每个设置组合进行了优化！

当使用VRGK时，你应该尽量在每个游戏项目中只使用1个棋子组合。


</details>
