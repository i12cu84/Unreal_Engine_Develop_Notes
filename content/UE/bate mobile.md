# 移动端适配特性

## 一、未完全适配到移动端的特性

1.延迟着色（Deferred Shading）的全面支持

- 问题：在官方版本的UE中，移动端的延迟着色（Deferred Shading）长期受限于 Multiview（多视图） 和 MSAA（多重采样抗锯齿） 的兼容性问题，导致在移动VR平台上难以实际应用13。

- 现状：PICO在UE 5.3的分支版本中通过支持 FXAA（快速近似抗锯齿） 替代MSAA，并结合 Application SpaceWarp 等特性解决了部分问题17。

2.贴花（Decals）的移动端兼容性

- 问题：官方版本的Decals需要开启 MobileHDR 才能运行，且不支持Multiview，限制了移动VR平台的使用13。

- 现状：PICO的UE 5.3分支允许在关闭MobileHDR并开启Multiview时使用Decals17。

3.高级抗锯齿技术（如MSAA）

- 问题：MSAA在移动端延迟渲染中难以实现，需依赖FXAA等替代方案15。

4.动态光源与复杂光照的实时计算

- 问题：移动端硬件对动态光源和复杂几何场景的实时渲染仍存在性能瓶颈，需依赖优化技术（如HLOD）降低负载24。

## 二、各版本中适配到移动端的关键特性
1.UE 5.3（PICO分支版本）
- Mobile Deferred Shading的优化：支持与 Late Latching、Tone Mapping 协同工作，并在动态光源场景中减少渲染延迟17。

- Decals的兼容性改进：无需开启MobileHDR即可在Multiview下运行3。

- FXAA抗锯齿支持：替代MSAA以减少锯齿问题1。

2.UE 5.0-5.2
- 次表面散射（Subsurface Scattering）：预集成次表面轮廓模型，支持皮肤、蜡等材质的真实表现（试验性）10。

- 距离场阴影（Distance Field Shadows）：结合级联阴影贴图（Cascaded Shadow Maps），为动态光照提供远距离阴影支持（试验性）10。

- Vulkan和DXC编译器支持：提升移动端着色器编译效率，并优化二进制文件大小10。

3.UE 4.x系列
- 移动端前向渲染器（Forward Renderer）：支持OpenGL ES 3.1、Vulkan和Metal，优化低端设备兼容性9。

- 动态光照与阴影：通过级联阴影贴图（CSM）和静态光源混合实现基础光照效果9。

4.第三方优化案例（非官方版本）
- 叠纸游戏的《无限暖暖》：通过 HLOD技术、OIT（顺序无关透明） 和 PCG（过程化内容生成） 实现了UE5移动端的高画质表现2。

- PICO的XR开发支持：集成 Unreal OpenXR SDK 1.3，增强混合现实（MR）功能的兼容性