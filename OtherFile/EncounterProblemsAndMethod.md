problem:
GPU发生崩溃 或D3D设备移除
用-d3ddebug来启用D3D调试设备.
检查日志中的GPU状态信息
vr设备中不断屏闪 电脑十分卡顿
method:
-> 项目设置 -> 目标硬件 为此项优化项目设置 -> Scalable (设备性能问题)
-> 引擎 Rendering -> Global IIIumination(动态全局光照方法) -> None
-> 反射 反射方法 -> None
-> NVDIA 控制面板 -> 管理 3D 设置 -> 全局设置 -> 恢复

problem:
检测到依赖型循环
蓝图中有无限循环
method:
-> 断点寻找死循环的位置

problem:
内存无止境持续暴涨
内存泄漏
method:
-> 寻找出现构造创建的物体,持续生成未销毁则容易出此问题(例如Spline组件中创建点而未销毁时)

problem:
pc预览700帧率,VR预览帧率暴跌,只有30帧不到
十分卡顿,效果不好
method:
设置方向:
-> 项目设置 -> 渲染 -> 移动着色 -> 向前着色
-> 项目设置 -> 一般设置 -> 帧率 -> 平滑帧率 / 固定帧率 等等
-> VR设置 -> 垂直同步关闭 / 平滑帧率 / 双眼分辨率
项目方向:
-> 光照 模型 复杂度优化

problem:
VR预览模式后进行导出,无VR无法正常运行,出现"fatal error"
游戏出现提示框即闪退
method:
-> 右键 以管理员身份运行
-> 关闭防火墙
-> 检查VR设备串流以及激活问题

problem:
对创建的Widget以ViewportSize定义SetPositioninViewpot
调试时UI的位置正常,但打包软件后调试会发现位置异常
UI的位置并不会受屏幕像素所影响
method:
在UI蓝图中,添加Canvas Panel,在屏幕Panel中明确定义好UI的具体位置
锚点可以与屏幕像素所关联
注:注意UI的层级关系

problem:
编辑器中运行发生的错误:如果需要移动,则.....的移动性必须为可移动性
无移动效果,需要在StaticMeshComponent设置移动性(可移动)
method:
Node:Set Mobility(设置为可移动)

problem:
""无访问 正在尝试读取属性
editor报错,出现未知效果
method:
加入IsValid节点判断是否有效(或者使用cast to [Type])

problem:
打开某些Widget时会与主窗口之间输入产生冲突
case:
透过Widget对主窗口操作
method:
加入Set Input Mode(UI Only/Game Only)

problem:
打开.uproject工程后弹出提示框"The following modules are missing or built with a different engine version:
[plugin name]
Would you like to rebuild them now?
在工程路径下新加了几个不同ue版本的插件导致工程项目无法打开,抑或是使用了ue的vs加入了新的代码
method:
->删除新添加到Plugins路径下的插件文件(当作什么都没发生...)
->按yes 让他重新编译(大概率没效果)
->vs打开工程重新生成解决方案(不能有失败)
->vs代码写完后生成解决方案失败了->需要重新调试并将代码以正确的方式进行生成解决方案(我想warning中会有足够的提示告诉你写的代码有问题)
->可能是你当前已经打开了ue工程,又使用vs生成解决方案的时候,ue工程并没有关闭使得解决方案生成失败,在你ue和vs都没有关闭的情况下,又打开了ue工程也会有这个问题->那么就需要将ue关闭后,vs(可以不关闭)重新生成解决方案成功后,重新打开ue

problem:
重新生成解决方案报错->
1>C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\MediaAssets\Public\MediaSource.h(35): error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
1>C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\MediaAssets\Public\MediaSource.h(63): error C2143: 语法错误: 缺少“;”(在“<class-head>”的前面)
1>C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\MediaAssets\Public\MediaSource.h(64): error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
1>C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\MediaAssets\Public\MediaSource.h(67): error C4430: 缺少类型说明符 - 假定为 int。注意: C++ 不支持默认 int
1. （此情况经常出现在大型工程项目中）如果存在两个类的头文件a.h和b.h,在a.h中有这样的语句：#include "b.h",在b.h文件中有这样的语句：#include "a.h"   且在一个类中有另一个类的对象时   那么就会出现这样的错误。
2. 没有包含要定义的类的头文件。
3.项目中少加了宏定义，导致头文件重复定义或相应宏无法识别。
4.当有多个头文件时，顺序写反也可能导致相关的错误，其根本是头文件中的预编译语句被隐去了。
e.g
#include <stdio.h>
#include <Windows.h>
#include <WinCrypt.h>
#include <string.h>
如果把第二个和第三个写反，一个宏定义就被#if给注了，就会出现类似错误
5.还有可能的原因是没有用到相关的空间。比如，用string，记得用using namespace std;若没有这一句，也会出现这样的问题。
6.没有加;
method:
1.尝试取消头文件代码引用
2.加入头文件
3.寻找宏定义问题
4.尝试寻找头文件依赖关系的顺序
5.加std::
6.加;

problem:
生成B widget时,可以对B widget操作事件,但更早生成的A widget却无法操作
被覆盖的widget无法触发事件,可能是被不可见的窗口而遮盖导致
method:
1.Canvas Panel中设置Visibility - Not Hit-Testable(Self Only)

problem:
正在执行输入映射时,按下widget的button,则会突然中断输入映射事件
case:
例如按W进行前进时,鼠标按下widget的button,则前进事件中断,导致无法前进
method:
1.将button控件改成image控件,按下事件绑定到image中即可

problem:
用Datasmith导入骨骼动画模型(SKeletalMeshActor)时候，模型一直在闪烁
case：
选择该对象 -> 细节 -> 骨骼网格 -> 高级 -> Per Bone Motion Blur (取消打勾)