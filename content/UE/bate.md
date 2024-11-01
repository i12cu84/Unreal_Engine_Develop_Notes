版本更新日志记录及理解

4.13 (启用虚幻VR初代版本)

4.22 (优化及稳定版,大部分企业项目主用的版本)
- 使用虚幻渲染管线4 (UE4 Renderer 4) 的全新高清晰度渲染技术
- 改进的真实时间光线追踪技术
- 运动模糊、景深和色调映射等效果改进
- 人体IK系统更新
- 强化虚幻编辑器快捷键配置

4.23
- 引入虚幻物理引擎Chaos的预览版：Chaos提供了更快速、高质量和可扩展的物理模拟，包括刚体动力学、碰撞检测和破坏效果。
- 多重场景编辑器：允许在一个虚幻项目中同时打开多个场景编辑器窗口，增强了多任务处理和工作流程的灵活性。
- 动态分屏抗锯齿 (Temporal Upsampling)：通过使用历史帧数据和运动向量来提高渲染品质，实现更平滑的图像边缘。
- 虚幻高级材质集（Unreal Advanced Materials）：新增了多个复杂材质示例，包括玻璃、液体、布料等，以展示更逼真的材质效果制作方法。
- 可视化数据制作工具增强：改进了Sequencer序列器和Blueprint蓝图编辑器，为用户提供更方便和强大的可视化工具，简化了动画和交互逻辑的创建与编辑过程。

4.24 (优化及稳定版,大部分企业项目主用的版本)
- 集成了Niagara粒子系统
- 增强了虚幻编辑器用户界面和工作流程
- 改进的光照质量和开发工具
- 引入了实时的AI导航系统
- 具有更好性能和稳定性的虚幻数据驱

4.25
- 多用户合作编辑模式
- 新的Volumetric Cloud System插件
- 虚幻渲染管线4 (UE4 Renderer 4)
- 超级分辨率图像增强技术（Super Resolution）
- 光线追踪软件解算器（Path Tracer）

4.26
- 更快的编译速度和更小的包大小
- Lumen全局光照和虚拟Shadow Map系统
- 骨骼IK优化和改进
- 光线追踪软件解算器更新
- Niagra粒子系统改进

4.27 (通用最终版,之前版本慎升5)
- Virtual Texturing支持
- Chaos物理引擎更新
- 可视化数据制作工具和功能增强
- 平滑跨网格距离场 (Signed Distance Fields) 渲染
- 安卓11支持

warning:4版本突发到5版本会有很大的变化(得不偿失,不建议跳)
迁移指南:https://docs.unrealengine.com/5.0/zh-CN/unreal-engine-5-migration-guide/

5.0 (真实化版)
- 颠覆性UI更迭(! 目前十分不适应)
- 全动态的实时全局照明（Global Illumination，简称GI）模块Lumen(提高真实度画面特性)
- 新的时间流系统（TimeFlow）和全新的LUMS（Landscapes Unified Material System）材质系统
- 3D音频重做，以提供更具沉浸感的声音效果
- 大量工具和工作流程改进，例如Visual Dataprep、Geometry Cache Plugin等
- Nanite虚幻几何技术，可实时渲染数百万甚至数十亿个多边形级别的细节模型
- 全新的World Partition系统，改进了大型场景管理和加载效率
- 更快的数据迭代和编辑体验，包括Live Link面板、Variant Manager和Multi-User Editing等功能增强

5.1 
- VR增强输入,原有输入映射被废弃(仍可用)
- 优化N/L技术以及阴影贴图
- 世界分区(! 暂未涉及 不了解)
- 简化ICVFX

5.2 
- 渲染:
- Substrate(全新材质,替换固定着色模型,multi-lobe框架) waning:推进测试,慎用
- SMPTE 2110集成(?)
- ML变形器(角色全身网格体)
- N/L技术改良
- PSO预缓存(改进DX12卡顿问题)
- 时序超分辨率相关的改进/优化
- 曝光改进(即将废弃眼适应纹理)
- 硬件光追工具强化
- 多视图优化
- 次表面散射改进(BP Node:Subsurface Medium(Path Tracer Only))
- 渲染资源查看器工具
- 着色器编译改进(效率优化以及诊断崩溃)
- 二级可变速率着色(自适应着色,试用中)
- 音频:音频参数调制改进
- MetaSound节点(Low Frequency Noise/Evaluate WaveTable/SuperOscillator(Stereo)/Perlin Noise(audio) -> Perlin噪点/低频率噪点/超级振荡器/评估波表)
- 神经网络引擎(NNE)(!):Neural Network Engine(插件,试用中)
- 更多相关内容传送阵:https://docs.unrealengine.com/5.2/zh-CN/unreal-engine-5.2-release-notes/

5.3
- Nanite 几何体系统: 进一步改进了 Nanite 几何体系统，通过新的“细化”功能，可以更精细地控制细节层次。这使得开发者能够更灵活地管理细节级别，以适应不同性能要求。
- Lumen 光线追踪: Lumen 光线追踪系统也得到了改进，提供了更好的光线追踪效果，并且优化了性能，使得更多场景能够使用实时光线追踪。
- 基于节点的材料编辑器: 引入了一个全新的基于节点的材料编辑器，使得材料创建更加直观和高效。
- 动画系统改进: 动画系统也得到了改进，包括对动画混合算法的优化，以及对 Avatar Mesh Morph Targets 的支持，使得角色动画更加平滑和自然。
- 虚拟生产工具: 增强了虚拟生产工具，包括 improvements to the Sequencer, the addition of a new Digital Doubles feature, and enhancements to the Lockdown mode.
- 性能优化: 引擎的整体性能得到了提升，包括对渲染、动画和物理模拟等领域的优化。
- 跨平台支持: 进一步加强了跨平台支持，使得游戏和应用程序可以在更多平台上运行。
- Python API 更新: 更新了 Python API，为开发者提供了更多功能和更好的兼容性。
- 新的示例项目和教程: 提供了新的示例项目和教程，帮助开发者更快地上手和使用新功能。
- 用户界面和功能改进: 用户界面得到了优化和更新，许多现有功能也得到了改进和增强。
- 支持新的硬件和平台: 增加了对新的硬件和平台的支持，包括对苹果 M1 芯片的支持。
- 多线程和并行处理: 增强了多线程和并行处理能力，提高了引擎的性能和效率。
- 更多相关内容传送阵:https://docs.unrealengine.com/5.3/zh-CN/unreal-engine-5.3-release-notes/

5.4

- 动画工具集的更新：5.4版本对虚幻引擎内置的动画工具集进行了重大更新，允许用户直接在引擎中快速、轻松地绑定角色和制作动画，无需频繁切换到外部应用程序。这包括一个新的实验性模块化控制绑定功能，使用户能够通过模块化部件构建动画绑定，而不是复杂的详细图表。此外，自动重定向功能简化了双足角色动画的复用过程，提高了效率。
- 性能和视觉保真度的提升：此版本还包括对性能和视觉保真度的改进，这些改进将使游戏开发者和各行各业的创作者受益。
- 内部工具集的交付：Unreal Engine 5.4交付了一些内部使用的工具集，这些工具集曾用于制作和发布《Fortnite》第五章、《Rocket Racing》、《Fortnite Festival》和《LEGO Fortnite》。
- 更多相关内容传送阵:https://dev.epicgames.com/documentation/zh-cn/unreal-engine/unreal-engine-5.4-release-notes?application_version=5.4

5.5

- Loading

‽
