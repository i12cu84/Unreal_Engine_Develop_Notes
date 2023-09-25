
<details>
<summary>UE5 Lumen原理介绍</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/380720641
来源

本文从Epic Games官方的视频整理而来，原视频来自于：https://www.youtube.com/watch?v=QdV_e-U7_pQ

并且加入了一点个人的思考（都在括号中）

背景

https://docs.unrealengine.com/5.0/en-US/RenderingFeatures/Lumen/

UE5是Unreal Engine新版本的引擎，目前还在early access状态，其中最引人注目的升级是推出了支持海量数据的几何体渲染模块Nanite，以及全动态的实时全局照明（Global Illumination，简称GI）模块Lumen

Lumen的主要特点是无需硬件光线追踪支持，也可以支持实时的全动态GI，无需预先烘焙，对室内外场景均可以达到较好的细节质量与性能的平衡，且与Nanite可以无缝配合。本文主要针对Lumen进行介绍。

目标

完全实时的GI
针对下一代游戏主机
进一步支持高端PC
高性能的反射
与动态GI集成在一起
巨大的开放世界
所有东西都支持流式加载（stream)
能够处理百万个实例（Nanite级别的内容）

室内（光照）质量
目前为止是实时GI中最困难的问题
无缝的支持室内外场景过渡（例如从室内走到室外）
Lumen的一些效果图（细节很高）



UE5中开启Lumen的方法


动态GI方法设置为Lumen
反射方法设置为Lumen
由于Lumen的算法依赖于Signed Distance Field（简称SDF），所以需要打开SDF的生成
以上设置在UE5新项目中默认打开
软件光线追踪 - 默认

先与depth buffer进行光线追踪（屏幕空间光线追踪）
（如果得不到交点，或者光线走出屏幕外）利用compute shader与SDF进行光线追踪
对于光线交点，通过Surface Cache（Lumen特有的一种cache）计算光照
（Lumen的底层可以理解为就是一个软件光线追踪的架构，为了加速，先尝试与屏幕空间光线追踪，再尝试与场景的voxel形式的近似表达求交，Lumen还大量使用了compute shader来实现GPGPU软件算法）

混合追踪管线

每种追踪方法解决它能够解决的问题

红色为屏幕光线追踪
绿色为Mesh Distance Field追踪（逐个物体一个SDF，主要针对追踪距离较近的光线）
蓝色为Global Distance Field追踪（把整个场景合并为一个SDF，主要针对追踪距离较远的光线）
（这里其实用到一个常识，光线追踪的越远的时候，ray differentials越大，于是geometry LOD level可以越粗糙）

（根据UE5文档：Lumen对于开始的2米使用Mesh Distance Fields进行追踪，剩余的距离使用Global Distance Field进行追踪）

Mesh Distance Fields

（UE4本来就支持Mesh SDF，UE5的主要改进是支持了）稀疏的表达（用于节省空间）

（左：UE5，右：UE4，支持了稀疏的表达方式以后，同样空间存储的精度就提高了，可以参考OpenVDB/NanoVDB）

（同时Mesh SDF还支持了）Mipmaps

（Lumen通过Mesh SDF + Mipmap的方式来支持场景几何的LOD表达，也是为了优化光线追踪）

基于距离从磁盘以流式（stream）加载
稀疏表达允许了默认voxel密度翻倍，并且每个mesh最大的voxel分辨率是原来的4倍
净内存消耗：约UE4的一半
Mesh Distance Field的构造速度是原来的10倍（这也是该技术能够实用化的一个重要原因）
简单光照模式下更好的可视化Mesh SDF（主要用于调试）

Surface Cache

离线放置的'Cards' = mesh捕捉
r.Lumen.Visualize.CardPlacement 1

（这里涉及到一个重要概念就是mesh card，这是Lumen特有的一个结构，原理为从不同的方向获取mesh表面属性的投影，这些投影后的属性被储存在纹理atlas中）

在低分辨率捕获mesh到atlas



对于Nanite mesh能够加速10-100倍
Nanite LOD本身就能够伸缩到低分辨率
Nanite基于compute shader的GPGPU软件实现，可以一次性并行绘制mesh LOD到所有的Card上（称为Multi-View支持，所以相比于其它mesh类型能加速那么多）
只支持简单的室内结构
墙壁、地板、天花板必须是单独的mesh（否则无法正确捕获）

缓存了直接光照
支持低质量的多次反弹GI

（上图是Nanite + Lumen的最终渲染效果，下图是Lumen的Surface Cache捕获的低分辨率光照）

（根据UE5文档：Lumen的Surface Cache只能覆盖从摄像机开始200米内的场景，超过这个范围，GI只计算屏幕空间反射。Lumen支持一种实验性的Distant Scene表达，可以允许追踪远于Surface Cache的场景范围。Distant Scene覆盖了200米到1千米的场景范围，原理是基于Nanite从太阳渲染一张Reflective Shadowmap，然后在Final Gather的时候与这张heightfield图求交。）

（Lumen场景调试方法，打开）Show -> Visualize -> LumenScene

这是Lumen的光线在屏幕空间追踪失败的时候，实际看到的场景样子

（所以如果右侧的效果和左侧的差异过大，会造成GI与直接看到的场景效果不一致，此时的一种解决方法是针对有问题的mesh加大SDF分辨率）

优化

合并所有的Mesh Distance Fields为Global Distance Field
UE5中2倍精度，且是稀疏表达

把Surface Cache合并为Voxel Lighting（体素光照）
默认对光线最开始的两米，与Mesh Distance Fields求交（通过Detail Tracing模式打开，大于2米则与Global Distance Field求交）
当打开Global Tracing模式的时候，则直接跳过上述与Mesh Distance Field求交过程

软件光线追踪的局限性

只支持静态mesh和实例化的静态mesh
5.0正式发布会支持Landscape
World Position Offset会引起瑕疵
更多信息看'Lumen Technical Details'文档：Lumen Technical Details
硬件光线追踪

提供最高质量，但是最高的成本 + 仅限部分显卡支持
PC: 需要D3D12版本支持
NVIDIA RTX-2000系列或更高显卡
AMD RX-6000系列或更高显卡
在early access版本中仅部分支持
反射
Final Gather的一部分
（Lumen部分支持通过硬件光线追踪进行计算，主要是为了高质量，不是为了性能，但是实现还比较早期）

硬件光线追踪与Nanite

只能与Nanite的'Proxy'（代理）几何体求交
屏幕光线追踪掩盖了不一致性
如果发现瑕疵可能需要提高'Proxy Triangle Percent'参数
硬件光线追踪性能

在early access版本中不能超过10000个实例
需要保持场景较小
在UE5/Main分支中已经支持了100000个实例，开发中
对于带蒙皮（skinned）的mesh代价很大（主要来源于逐帧rebuild BVH）
未来：光线追踪LOD bias
(Lumen中硬件光线追踪比软件光线追踪大约慢50%，软件得益于各种算法优化反而来的比较快，硬件比较暴力所以较慢）

光线追踪很慢

只能承担每个像素有1/2条光线，但是室内通常需要200+条光线才能收敛
通常的做法：
Irradiance Fields
看起来太平（不符合室内的细节要求）
光照更新慢
volumes需要手工放置（流程负担）
屏幕空间降噪器（Denoiser）
代价很大
降噪能做的很有限（太noisy的情况效果很有限）
（这里就引入了Final Gather的概念，就是从某个点发射很多光线收集周围环境贡献的过程，而之后提到的Radiance Caching是实现Final Gather思路的一种具体算法）

Lumen使用了屏幕空间的Radiance Caching算法


（Radiance Caching算法的核心是在空间中稀疏的采样一些表面的Hemispherical Harmonics，在没有采样的点，通过插值周围的Hemispherical Harmonics来获得光照分布，该插值出的光照分布可以与BRDF进行积分）

（Radiance Caching的优点是）非常低分辨率的tracing，全分辨率的细节


（Radiance Caching的本身性质，因为插值出的Hemispherical Harmonics是完整的光照分布，支持与任意经过Normal/Bump Mapping修改的法线朝向的BRDF积分）

使用世界坐标系的Radiance Caching实现稳定的远处光照


（在屏幕空间Radiance Caching的基础上，Lumen也使用了世界空间的Radiance Caching来支持场景较远部分的GI贡献）

World Radiance Cache（世界坐标系）

r.Lumen.RadianceCache.Visualize 1

（很稀疏，而且基本上还是个规则的grid，但是因为大多数像素都可以从屏幕空间Radiance Cache获得贡献，所以世界空间Radiance Cache的精度变得不是很重要）

过滤前的图像对比


（左图：屏幕空间降噪器的输入图像，右图：Lumen的过滤前图像，整个场景只有室外光照明，纯光线追踪/Path Tracing由于输入图像过于noisy，对于降噪器的要求太高，而Lumen由于已经使用了各种biased算法来降低噪声，过滤出有效图片变得比较容易，在同样光线预算的情况下可以更高效的生成图像）

Lumen Reflections

对于Roughness < 0.4的情况追踪额外的光线
意味着这些材质是代价最大的
对于Roughness > 0.4的情况重用Final Gather追踪的结果
粗糙的specular lobe收敛于diffuse（意思是分布很接近diffuse）
空间和时间域的降噪器
基于硬件光线追踪的反射

当Reflection Quality参数设为4的时候（是个magic number），对反射中看到的物体使用真实的光照（会进行shading + lighting，否则只是采样Surface Cache中粗糙的光照近似）

Surface Cache依然提供了多次反弹的GI和天空照明

Lumen反射与光线追踪反射

Lumen反射支持
屏幕空间反射
软件（实现的）光线追踪
反射中的动态GI（通过Surface Cache）
反射中可以移动的带阴影的天光（通过Surface Cache）
Clear Coat的两层反射功能
光线追踪的反射支持
反射中看到的Lightmap GI（和Lightmap的兼容性比较好，允许开历史的倒车）
多次反弹的反射
未来：Lumen反射
从光线追踪反射中掏空剩下的功能（替代光线追踪反射）
平台

只支持下一代游戏主机 + 高端PC
还不支持移动设备 - 性能不足（国内手游引擎的机会来了）
不支持VR - VR对于分辨率和帧率的要求太高，不可行
硬件光线追踪有额外要求 - 具体看文档
性能

非常依赖于Temporal Super Resolution（时间域的超分辨率技术）来在内部的低分辨率渲染，然后放大到实际输出分辨率

内部1080p -> 4K输出
但是PC的默认屏幕分辨率比例是100
你可以降低编辑器的视窗大小来提升性能
（关于开发成本：UE5本来就是一个非常复杂的软件系统，而Lumen这一个模块，由3名非常资深的研发人员开发了2年，刚刚进入early access阶段，依然在不断完善中，开发成本还是非常高的）
</code></pre>
</details>

<details>
<summary>UE5 Nanite原理介绍</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/393930818
视频源

本文基于Epic Games的以下视频翻译并整理：

https://www.youtube.com/watch?v=TMorJX3Nj6U



概念

Nanite是UE5引擎中新的虚拟几何系统（virtual geometry system），类似于虚拟纹理系统（virtual texturing system），目标主要是支持直接渲染高精度的mesh资产（当mesh精度足够高的时候，事实上可以避免使用高分辨率的normal map，反而节省了存储）。

演示

Nanite的演示场景，可以在PC上流畅运行，不依赖于PS4的硬件


流程上，Nanite允许用户先使用最高分辨率的资产来构造数字内容，然后再针对download size（云端）或者disk size（本地）来优化package的大小，而不是一开始就限制资产制作精度。



梦想

类似于virtual texture一样支持virtual geometry（支持LOD，且可以快速stream in/out，支持超出显存/内存的数据规模）
不需要考虑budget问题，包括：
多边形数量
draw call数量
内存用量
允许直接使用电影级别质量的艺术资产
直接可用
不需要大量的手工优化渲染工作
质量上没有损失


现实

比virtual texturing困难多了
不只是需要很好的内存管理
几何细节直接会影响渲染开销
几何并不是很简单的就可以过滤的（相比于纹理可以很容易构造mip-map）


使用哪种几何表达？

研究了几种潜在的几何表达方式：

体素（voxel）
细分曲面（subdivision surface）
置换贴图（displacement map）
几何图像（geometry image）
基于点的图形（point based）
...


需求

对于完全改变所有CG流程并不感兴趣
支持从任何地方创作的mesh数据的导入
依然支持UV和分块细节贴图
只替换mesh部分的实现，不影响纹理、材质、以及工具（不影响现有的生态系统）


三角形

基于某些合理的原因，三角形是计算机图形学的基础



GPU驱动的管线

渲染器现在是保留（retained）模式
完全的GPU场景
只对有变化的物体进行局部更新
所有顶点/索引数据都在单个巨大的资源里
逐视图：
GPU实例裁剪
三角形光栅化
如果只是绘制深度，整个场景只需要单个indirect draw命令绘制


三角形cluster剔除

把三角形组织为cluster
对每个cluster构造包围数据
基于包围数据剔除cluster
frustum剔除
遮挡剔除



可见性与材质的解耦

消除
在光栅化时候切换shader
材质求值的多余调用
用于减少overdraw的深度prepass
由于密集的mesh，像素采样低效的问题
延迟材质


次线性的伸缩效率



理想情况下，希望每个像素一个三角形（类似于ray tracing的时间复杂度，避免绘制代价与三角形数量成正比）



cluster层级

对每个cluster决定LOD级别
构造LOD的层级
最简单的就是cluster的二叉树
父节点是子节点的简化版本



LOD运行时

在LOD树中根据需要的精度，寻找cut
基于感知差异的视角依赖方法



流处理

整颗树不需要一次性载入内存
可以把树中的任意cut标记为叶子节点，然后扔掉剩下的数据
在渲染的时候按照需要请求数据
和virtual texturing类似



像素级别的细节

大于一个像素的三角形能否达到像素级别精度
依赖于三角形有多光滑
一般不行
我们需要绘制像素大小的三角形



细微的三角形

对于典型的光栅化来说非常难处理
通常是基于像素并行，而不是基于三角形
软件光栅化在这种情况能不能打败硬件光栅化？



软件光栅化

比硬件光栅化快3倍


硬件光栅化

对于大的三角形呢？
还是用硬件光栅化
基于每个cluster选择是使用软件光栅化还是硬件光栅化

（红色的区域是硬件光栅化，蓝色的区域是软件光栅化）



Nanite的性能

基于TAA把2496x1404上采样到4K
约2.5ms花在剔除和光栅化
基本为零的CPU时间
约2ms的base pass（即延迟材质pass）
很小的CPU代价
每个材质一次draw调用


Nanite的数据

大的三角形数量意味着必须要好的压缩，否则数据太大
（演示中的）Nanite数据在磁盘上约6.14GB
平均每个输入三角形占用14.4B
1M三角形约等于13.8MB磁盘占用
比4k x 4k的normal map还是要小的（所以没必要用normal map了，直接用dense mesh）


Virtual shadow maps（虚拟阴影贴图）

Nanite允许了新的一些技术
每盏灯都可以用16k x16k的shadow map
基于1 texel = 1 pixel选择mip level
只渲染shadow map上需要被看到的像素
Nanite裁剪并且处理LOD来保证足够的细节水平
缓存了（shadow map）所以只有移动的部分需要重新绘制

（不同距离的阴影都很精细）



SMRT filtering（阴影贴图光线追踪过滤）




Nanite支持什么

首先专注在刚体几何
大于90%的几何体都是刚体
物体的移动是支持的
还不支持：
半透明或者带遮罩的材质
非刚体形变，骨骼动画等
细分和置换
对于aggregate类型的几何体不友好
很多很小的物体组成了一个带孔的体积
草地、树叶、毛发（因为这种情况，LOD很难建立的很有效）
</code></pre>
</details>