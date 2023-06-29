problem:
GPU发生崩溃 或D3D设备移除
用-d3ddebug来启用D3D调试设备.
检查日志中的GPU状态信息
case:
vr设备中不断屏闪 电脑十分卡顿
method:
-> 项目设置 -> 目标硬件 为此项优化项目设置 -> Scalable (设备性能问题)
-> 引擎 Rendering -> Global IIIumination(动态全局光照方法) -> None
-> 反射 反射方法 -> None
-> NVDIA 控制面板 -> 管理 3D 设置 -> 全局设置 -> 恢复

problem:
检测到依赖型循环
case:
蓝图中有无限循环
method:
-> 断点寻找死循环的位置

problem:
内存无止境持续暴涨
case:
内存泄漏
method:
-> 寻找出现构造创建的物体,持续生成未销毁则容易出此问题(例如Spline组件中创建点而未销毁时)

problem:
pc预览700帧率,VR预览帧率暴跌,只有30帧不到
case:
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
case:
游戏出现提示框即闪退
method:
-> 右键 以管理员身份运行
-> 关闭防火墙
-> 检查VR设备串流以及激活问题

problem:
对创建的Widget以ViewportSize定义SetPositioninViewpot
调试时UI的位置正常,但打包软件后调试会发现位置异常
case:
UI的位置并不会受屏幕像素所影响
method:
在UI蓝图中,添加Canvas Panel,在屏幕Panel中明确定义好UI的具体位置
锚点可以与屏幕像素所关联
注:注意UI的层级关系

problem:
编辑器中运行发生的错误:如果需要移动,则.....的移动性必须为可移动性
case:
无移动效果,需要在StaticMeshComponent设置移动性(可移动)
method:
Node:Set Mobility(设置为可移动)

problem:
""无访问 正在尝试读取属性
case:
editor报错,出现未知效果
method:
加入IsValid节点判断是否有效(或者使用cast to [Type])

problem:
打开某些Widget时会与主窗口之间输入产生冲突
case:
透过Widget对主窗口操作
method:
加入Set Input Mode(UI Only/Game Only)

