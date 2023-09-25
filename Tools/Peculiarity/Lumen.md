ue5特性:Lumen(Light-weight Multiple-scattering Unified Rendering)(软件光线追踪技术)全**动态全局照明**和反射系统
Lumen的主要特点是无需硬件光线追踪支持，也可以支持实时的全动态GI，无需预先烘焙，对室内外场景均可以达到较好的细节质量与性能的平衡，且与Nanite可以无缝配合
支持无限漫反射反弹
解决全局照明的同时，也解决了天空阴影问题
通过发光材料传播照明，而无需任何额外费用
解决了半透明和体积雾的全局照明
可以动态地解决任何表面、任何粗糙度的反射
漫反射全局照明:基于辐射缓存的高级最终聚集算法

启用方法
-> 项目设置 -> Software Ray Tracing -> 生成网格体距离场
-> 项目设置 -> 反射 -> 反射方法 -> Lumen
-> 项目设置 -> Lumen -> 高质量半透明反射
-> 项目设置 -> Global Illumination -> 动态全局光照方法 -> Lumen
-> 模型 -> 放置Actor -> Post Process Volume -> 细节面板 -> Global Illumination -> Method -> Lumen