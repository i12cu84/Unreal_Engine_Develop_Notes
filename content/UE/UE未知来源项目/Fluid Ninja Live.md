[官方网址](https://www.fab.com/zh-cn/listings/80fcf53e-49f7-4635-a71c-ba81280c6618)

# 描述

欢迎来到FluidNinja LIVE 1.9.54.4：快速，响应流体模拟角色和环境VFX。

驱动动态系统与流体：水，云，烟，火，沙，雪和树叶。

可玩的互动演示展示Live 1.7功能：NinjaDEMO EXE + videoccapture

有关流体烘焙，请参阅ninjtools

# 特性

强大：能够追踪数百个物体和骨骼，包括超人类骨骼

大规模：局部流体求解器扩展了全局模式生成器-渲染大片的沙，水，雾

Volumetrics：支持所有本机UE卷类型：雾卷、云卷和异构卷

简单模式：在不运行流体的情况下跟踪对象并绘制轨迹。

可扩展：可以针对低端硬件进行优化或运行4k sim卡容器

模块化：可以作为ActorComponent添加/可以驱动其他组件（niagara, volumes）

Cinematics：准备通过电影渲染队列渲染，支持Sequencer

尼亚加拉：双向数据流-使用fluidsim驱动粒子/使用粒子驱动fluidsim

Sim缓冲区暴露给RenderTargets（密度，速度，压力）

例子包括：20个用例关卡和30个教程关卡

大距离：支持虚幻大世界坐标（LWC）

重要提示：不能复制，不支持多人游戏

# 模拟输入

静态网格，物理体（位置，大小和速度）

骨骼网格，超人类（骨骼位置和速度）

纹理和材质（密度，速度）

尼亚加拉粒子（位置，速度）

scenecaptureca摄像头和流媒体视频

用户手势通过鼠标和触摸屏

# 启用

项目设置 -> 引擎 -> Phtsics -> 优化 -> 支持撞击结果的UV

关卡Usecase_008B_LavaWorldSpace -> 需要添加ChasoVehiclesPlugin 插件才能运行