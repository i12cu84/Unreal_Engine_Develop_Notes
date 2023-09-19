命令行执行自定义事件(类似于ue Editor 的cmd控制台命令)


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
