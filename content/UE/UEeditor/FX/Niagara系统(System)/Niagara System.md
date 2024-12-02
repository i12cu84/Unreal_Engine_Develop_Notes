这相当于是Niagara模块,展现一个特效的发射器,并没有SpaceLine


属性

用户参数

系统生成

系统更新

---
```
属性(Properties GPU/CPU)
    Local Space 粒子发射位移是否关联全局空间
    Determinism   是否使用 determinism 模式
    Interpolated Spawning  粒子发射时是否插值
    Sim Target    选择CPU/GPU
        ->CPU Sim  CPU
        ->GPU Compute Sim   GPU
    Calculate Bounds Mode  边界计算模式
        ->Dynamic         每秒计算边界
        ->Fixed           自设定特效边界范围
        ->Programmable    使用发射器属性数据接口从脚本设置边界
    Requires Persistent IDs  是否使用 determinism 模式
    Combine Event Spawn   是否允许在发射器生成时发射粒子

发射器摘要(Emitter Summary) ->在其他模块面板中右键点击"在发射器摘要中显示" 即可在此地显示选择的模块面板

发射器生成(Emitter Spawn) ->定义可编辑常量在其他模块参量中使用
    加号 ->直接设置新参数或现有参数
    其他模块参量 ->General ->Link Inputs ->发射器(Emitter) ->自定义编辑常量命名

发射器更新(Emiter Update)
->Emitter State  粒子状态
    Life Cycle   生命周期
        Life Cycle Mode   生命周期模式
            ->System   依照系统参量
            ->Self     自行设置参量
        Inactive Response  不活跃响应
            ->Complete  完成
            ->Kill      终止
            ->Continue  继续
        Loop Behavior       循环行为
            ->Infinite 无限循环
                Loop Duration 持续时间
                Recalculate Duration Each Loop 重新计算
            ->Once     仅执行一次
                Loop Duration Mode 持续时间模式
                    ->Fixed 固定
                        Loop Duration 持续时间
                    ->Infinite 无限循环
            ->Multiple 设置循环次数
                Loop Count 循环次数
                Loop Duration  持续时间
        Loop Delay  循环延迟
        Delay First Loop Only 第一次循环延迟
    Scalability  粒子缩放
        Scalability Mode  缩放模式
            ->System      根据系统参量
            ->Self        自行设置参量
                Enable Distance Culling  距离裁剪
                    Min/Max Distance  距离范围
                    Min/Max Distance Response   距裁剪响应
                        ->Awaken                           唤醒
                        ->Sleep and Let Particles Finish   唤醒后等待粒子完成
                        ->Sleep and Clear Particles        唤醒后清除粒子
                        ->Kill Immediately                 立即终止
                        ->Kill After Particles Finish      粒子完成之后终止
                Enable Visibility Culling 显示裁剪
                    Visibility Cull Response    裁剪响应可视
                        ->Awaken                           唤醒
                        ->Sleep and Let Particles Finish   唤醒后等待粒子完成
                        ->Sleep and Clear Particles        唤醒后清除粒子
                        ->Kill Immediately                 立即终止
                        ->Kill After Particles Finish      粒子完成之后终止
                    Visibility Cull Delay 显示延迟
                Reset Age On Awaken  唤醒重置时间
->Spawn Burst Instantaneous 瞬时发射
    Spawn Count 发射数量
    Spawn Time 发射时间
    Spawn Probability 发射概率
        ->Spawn Group    发射组
        ->Age 粒子存活时间
->Spawn Rate 粒子生成速率
    Spawn Rate 响应粒子数量
    Spawn Probability 发射概率
    Spawn Group 粒子发射组
->Spawn Particles from Other Emitter 从其他发射器发射粒子
    Attribute Reader  粒子读取
        Errors And Warnigns(粒子读取)
            Emitter Name  发射器名称
            ->点击Fix issue 修复(启用)
        Spawn Rate       发射速率
        Calculate Spawn Rate Per Particle   计算发射速率
        Spawn Rate Per Particle Cap   发射速率上限
        Spawning Enable   发射启用
        Min/Maximum Age Spawn Threshold   发射阈值
        Spawn Group       发射组
->Spawn Per Frame 每帧发射
    Spawn Count   发射数量
->Spawn Per Unit 每单位发射(移动特效单位时喷射特效)
    Spawn Spacing   发射间隔
    Max Movement Thershold  移动阈值
    Movement Tolerance   移动容差
    Spawn Probability   发射概率

粒子生成(Particle Spawn)
->Initalize Particle   初始化粒子
    Point Attributes   初始化粒子属性
        Lifetime Mode   生命周期模式
            ->Direct Set   直接设置
            ->Random       随机范围
        Color Mode  颜色模式
            ->Unset                        不设置
            ->Direct Set                   直接设置
            ->Random Range                 随机范围
            ->Random Hue/Saturation/Value  随机色相/饱和度/值
        Position Mode  位置模式
            ->Unset                        不设置
            ->Direct Set                   直接设置
                Position                   位置
            ->Simulation Position          模拟位置
                Position Offset            位置偏移
        Mass Mode  质量模式 (可使用 Calculate Size and Rotational Inertia by Mass 重新计算粒子大小和旋转惯性)
            ->Unset/(Mass of 1)  不设置
            ->Direct Set  直接设置
            ->Ramdom    随机
    Sprite Attribute   粒子属性
        Sprite Size Mode  粒子大小模式
            ->Unset  不设置
            ->Uniform  均分
            ->Random Uniform  均分随机
            ->Non-Uniform  均分非均分
            ->Ramdowm Non-Uniform  均分随机非均分
        Sprite Rotation Mode  粒子旋转模式
            ->Unset  不设置
            ->Random  随机
            ->Direct Angle (Degrees)  直接角度(度)
            ->Direct Normailzed Angle (0-1)  直接角度(0-1)
        Sprite UV Mode 粒子UV模式
            ->Unset  不设置
            ->Ramdom X  随机X
            ->Ramdom Y  随机Y
            ->Ramdom X/Y  随机X/Y
            ->Custom  自定义
->Shape Location 形状位置
    Shape   形状
        Shape Primitive  形状原点
            ->Sphere  球体
                Sphere Radius  球体半径
            ->Cylinder 圆柱体
                Chlinder Height 高度
                Cylinder Radius 半径
                Cylinder Height Midpoint 中点
            ->Box/Plane  盒子/平面
                Box/Plane Mode 模式
                    ->Box 盒子
                        Box Size 大小
                        Box Midpoint 中点
                    ->Plane 平面
                        Plane Size 大小
                        Plane Midpoint 中点
            ->Torus 圆环面
                Large Radius 大半径
                Handle Radius 小半径
            ->Ring/Disc 圆环/圆盘
                Ring/Disc Radius 半径
            ->Cone 圆锥
                Cone Mode 模式
                    ->Spherical Cone  球面圆锥
                        Cone Length 长度
                        Cone Angle 角度
                        Cone Inner Angle 内角度
                        Cone Radial Angle 角度
                        Cone Angle Type   角度类型
                            ->Degrees  角度(度)
                        FlattenEndcaps 平面
                    ->Spherical Wedge 球面楔形
                        Cone Length 长度
                        Wedge Horizontal Angle 水平角度
                        Wedge Vertical Angle 垂直角度
        Apply To Particle Position  应用于粒子位置
            ->Apply    应用
            ->Output  输出
    ...(更多内容待补充)
->Add Velocity 添加速度
    Velocity Mode  速度模式
        ->Linear  线性
            Velocity  速度
            Velocity Speed Scale 速度倍率
        ->From Point 从点
            Velocity Speed 速度
            Constrain To Radius 约束到半径
        ->In Cone 在圆锥内
            Velocity Speed 速度
            Distribution Along Cone Axis 沿圆锥轴分布
            Speed Falloff From Cone Axis 速度落差
->Spawn Particles from Other Emitter 从其他发射器发射粒子
    Filtering  过滤器
    Reject Particle By Sampled Age   过滤粒子
    Min/Maximum Sampled Particle Age   最小/最大粒子存活时间
    ...(更多内容待补充)
->Inherit Velocity  继承速度
    Inherit Velocity  继承速度
        Inherited Velocity Amount 继承速度
        Inherited Velocity Speed Limit 继承速度速度限制
        Source Speed Threshold 源速度阈值
->Vortex Velocity 漩涡速度
    Velocity Amount 漩涡速度
    Vortex Axis 漩涡轴
    Vortex Origin 漩涡原点
    Vortex Axis Coordinate Space 漩涡轴坐标空间
->Add Rotational Velocity 添加旋转速度
    Rotation Rate 旋转速率
    Coordinate Space 坐标空间

粒子更新(Particle Update)
->Particle State  粒子状态
->Gravity Force 重力
->Drag  阻力
->Scale Color 颜色
->Solve Forces and Velocity 解决力和速度

渲染(Render)
->Sprite Renderer Sprite渲染
->Light Renderer Light渲染
    渲染光照 但无法在GPU Compute Sim中使用
```
  
参考文献 【UE5& Niaraga特效基础教程.】 https://www.bilibili.com/video/BV1C84y1D7hd
其中 包含 Acceleration Force / Aerodrynamic Drag Force / Curl Noise Force / Drag Force / Gravity Force

微信 支付宝 米哈游 百度 拼多多 知乎 抖音 爱给网 b站 网易云音乐 qq 华为 高德 个人所得税 网易(永劫) 
银行 酷我音乐 麦 肯
