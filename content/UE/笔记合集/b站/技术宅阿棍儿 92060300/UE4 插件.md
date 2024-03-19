https://www.bilibili.com/video/BV1tv41117qg
<details>
<summary>UE4插件00 创建</summary>
<pre><code>
https://www.bilibili.com/video/BV1ht4y1y7ad
引擎插件与项目的插件的目录是不同的(是用来说没什么区别)
位置->根目录/Plugin/...[file]
    空白->没有任何逻辑
    纯内容->只有资源(贴图)
    蓝图库->静态蓝图节点(蓝图节点中可以找到的函数)
    编辑器工具栏按钮->上一列按钮
    编辑器独立窗口->上一列按钮呼出一个独立窗口
    编辑器模式->模式窗口用于模式性的工作
    第三方库->引用第三方库
</code></pre>
</details>

<details>
<summary>UE4插件01 从代码引用插件</summary>
<pre><code>
https://www.bilibili.com/video/BV19i4y1s7xk
相当于从c+底层调用的API(其实可以从蓝图库中用静态的方式以蓝图节点调用的)
"CoreUObject"模块记得添加到[file].Build.cs
添加项目->增加解决方案
</code></pre>
</details>

<details>
<summary>UE4插件02 模块大串联</summary>
<pre><code>
https://www.bilibili.com/video/BV1tK411p7Wo
[模块工程].Build.cs中添加目标模块的名字即可
不同类型的插件的父类是不一样的
[file].Target.cs  添加模块
    "PluginName"
[file].uproject   添加模块
    "Modules":[
        {
            "Name": "PluginName",
            "Type": "Runtime",
            "LoadingPhase": "Default"
        }
    ]
</code></pre>
</details>

<details>
<summary>UE4插件03 万能三招在任意编辑窗口加按钮</summary>
<pre><code>
https://www.bilibili.com/video/BV1Ei4y1x77z/
添加按钮的基本方法
</code></pre>
</details>

<details>
<summary>UE4插件04 使用UToolMenu加按钮/改蓝图编辑器工具条</summary>
<pre><code>
https://www.bilibili.com/video/BV1uA411B7PY
</code></pre>
</details>

<details>
<summary>UE4插件05 初识Slate</summary>
<pre><code>
https://www.bilibili.com/video/BV19t4y1X7vh
按下后显示单独窗口(停靠标签页)
控件反射器(用于探究光标滑动到的目标窗口的信息,例:窗口的代码来源,地址,以及窗口的具体信息)
TEXT(__FUNCTION__) -> 获取本函数名字
添加滑动条并影响滑动后的文本值
</code></pre>
</details>

<details>
<summary>UE4插件06 对照UMG设计自定义Slate控件</summary>
<pre><code>
https://www.bilibili.com/video/BV1rD4y1Q73S
使用UMG架构的蓝图uesset
右键蓝图"运行编辑器工具控件"即可实现(但是ue4)
</code></pre>
</details>

<details>
<summary>UE4插件07 右键新建自定义资源（包括4.25.1版的特别处理）</summary>
<pre><code>
https://www.bilibili.com/video/BV1454y1z7dn
</code></pre>
</details>

<details>
<summary>UE4插件08 拖拽导入自定义资源</summary>
<pre><code>
https://www.bilibili.com/video/BV1EK4y1s7Mn
资源管理 -> 右键添加资源类型
</code></pre>
</details>

<details>
<summary>UE4插件09 自定义资源的自定义编辑器</summary>
<pre><code>
https://www.bilibili.com/video/BV15K4y1s7Vp
可用自定义资源内容
</code></pre>
</details>

<details>
<summary>UE4插件10 自定义资源的重新导入</summary>
<pre><code>
https://www.bilibili.com/video/BV13Z4y1p7WN
写个文件覆盖资源
</code></pre>
</details>

<details>
<summary>UE4插件11 自定义资源的自定义操作和导出</summary>
<pre><code>
https://www.bilibili.com/video/BV1u54y1z7kr
右键菜单对目标资源内容进行更改
</code></pre>
</details>

<details>
<summary>UE4插件番外00 折腾内容浏览器玩，向官方提交了俩修改</summary>
<pre><code>
https://www.bilibili.com/video/BV12a4y1a7Nd
拖拽资源以及子菜单按钮调用函数
</code></pre>
</details>

<details>
<summary>UE4插件12 自定义细节面板</summary>
<pre><code>
https://www.bilibili.com/video/BV1Nh411Z72u
双击蓝图后的右侧细节面板编辑
</code></pre>
</details>

<details>
<summary>UE4插件13 自定义编辑模式</summary>
<pre><code>
https://www.bilibili.com/video/BV1254y1S72r
编辑框修改自定义模式
</code></pre>
</details>
