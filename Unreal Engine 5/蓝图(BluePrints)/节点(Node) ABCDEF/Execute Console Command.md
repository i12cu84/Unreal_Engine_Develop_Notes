命令行执行自定义事件(类似于ue Editor 的cmd控制台命令)


<details>
<summary>ce [事件名]</summary>
<pre><code>
关卡蓝图通信(事件为在关卡蓝图中CustomEvent蓝图的名字)
</code></pre>
</details>

严重性	代码	说明	项目	文件	行	禁止显示状态
错误	LNK1181	无法打开输入文件“..\Intermediate\Build\Win64\x64\UnrealEditor\Development\UnrealEditor.lib”	UPlayer	C:\Users\chru\Desktop\UPlayer\Intermediate\ProjectFiles\LINK	1	



<details>
<summary>Shot</summary>
<pre><code>
游戏内截图,存储到[项目名字]\Saved\Screenshots\WindowsEditor\ScreenShot[图片编号].png
</code></pre>
</details>

<details>
<summary>HighResShot</summary>
<pre><code>
HighResShot 1 - 游戏内截图,存储到[项目名字]\Saved\Screenshots\WindowsEditor\HighresScreenshot[图片编号].png
HighResShot 2048x2048 - 游戏内截图,以分辨率方式
HighResShot filename=PATH (XxY OR Multiplier) CaptureX CaptureY CaptureW CaptureH bMaskUsingCustomDepth bDumpBufferVisualizationTargets bCaptureHDR bDateTimeAsFilename
|参数|描述|
|-|-|
|XxY|指定截图的尺寸(宽度x高度)|
|乘数(Multiplier)|指定截图的值放大截图尺寸|
|CaptureX CaptureY CaptureW CaptureH|用整数定义视口要用于截图的区域|
|bMaskUsingCustomDepth|用一个布尔值(0或1)来控制是否要用自定义深度(Custom Depth)缓冲作为捕获的遮罩|
bDumpBufferVisualizationTargets|用一个布尔值(0或1)来控制是否要将GBuffer中的每一个通道都捕获为一张图片并将其导出|
|bCaptureHDR|用一个布尔值(0或1)来控制是否要使用.EXR文件格式来捕获HDR图片|
</code></pre>
</details>

更多指令内容:https://docs.unrealengine.com/4.27/en-US/TestingAndOptimization/PerformanceAndProfiling/StatCommands/

~“键 调用控制台命令 

0，技巧

键盘 ↑键 可以看到之前输入过的指令
控制台指令并不需要打全名，空格+指令 可以模糊搜索
Ctrl + Shift + 逗号 ，打开 GPUProfile 面
1，调试类

stat fps —— 显示帧率
stat unit —— 显示包括Draw Call ，游戏逻辑等各种项的消耗
stat UnitGraph —— 显示各个参数的实时曲线图
stat rhi —— 显示各种GPU上的消耗细则
stat game —— 显示当前帧的时间信息
stat Engine —— 显示帧数时间，三角面数等
stat scenerendering —— 显示Drawcall
ShowFlag.Bounds —— 显示包围盒（0关闭，1打开）
ShowFlag.Collision—— 显示碰撞盒（0关闭，1打开）
r.visualizeOccludedPrimitives —— 查看遮挡剔除（0关闭，1打开）
DisableAllScreenMessages/EnableAllScreenMessages —— 关闭/打开屏幕打印信息
ke * rendertextures 高分辨率截图
HighResShot  —— 以当前viewport分辨率的倍数进行截图（倍数）
HighResShot 3840x2160 —— 指定分辨率截图（分辨率）【图片存储位置：\Saved\Screenshots\】
stat Hitches —— 或者stat DumpHitches 记录log文件
stat startfile / stat stopfile —— 开始/结束统计性能分析  ，用于记录某段时间内的性能分析数据。【此时会在路径 Saved/Profiling/UnrealStats 下生成数据文件。】
2，图像类

r.vsync 0—— 垂直同步（0关闭，1打开）
r.Tonemapper.Sharpen 3 —— 锐化（锐化强度）
r.Streaming.PoolSize 4096 —— 显存多少分配给了纹理流送池（显存大小，0表示无上限）
r.ScreenPercentage 50 —— 设置渲染分辨率为默认大小的50%
r.TonemapperFilm —— 开关后处理效果
ShowFlag.PostProcessing —— 开关后期盒子效果
r.AOSpecularOcclusionMode —— 可以让 skylight 产生的 DFAO 产生更准确的高光（0关闭，1打开）
3，游戏类

slomo —— 游戏运行速度（运行速度）

