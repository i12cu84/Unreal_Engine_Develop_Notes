# Unreal_Engine_Develop_Notes

-> assets -> 有关所有notes的markdown图片

<details>
<summary>-> CppPeculiarity -> C++特性笔记</summary>
<pre><code>
    <details>
    <summary>-> boost -> Boost标准规范</summary>
    <pre><code>
        a_more_wil_done_task - 目前正在研究的库（未完成）
        accumulators - 用于统计和数据收集
        atomic - 原子操作
        bimap - 双向映射的容器
        circular_buffer - 循环缓冲区
        cpp_int - 高精度整数
        date_time - 日期和时间操作
        endian - 处理不同字节顺序
        format - 格式化输出
        fusion - 管理容器
        geometry_index - 管理空间索引
        geometry - 处理几何图形
        graph - 图形和图论算法
        hana - 编写元编程代码
        histogram - 直方图
        interprocess - 在进程间共享数据
        intrusive - 设计高性能容器
        iostreams - 扩展I/O流操作
        lexical_cast - 转换字符串
        localte - 本地化和国际化
        managed_shared_memory - 共享内存通信
        math - 数学和数值计算
        mp11 - 编译时操作包含类型的数据结构
        multi_array - 多维数组
        multiprecision - 高精度数学计算
        numeric_conversion - 数值转换
        optional - 安全地表示可能为空的值
        program_options - 解析命令行参数和配置文件
        property_grid - 创建属性网格
        property_map - 数据关联到图形结构
        property_tree - 操作XML、INI、JSON等配置文件格式
        random - 生成伪随机数
        rational - 有理数操作
        regex - 正则表达式支持
        safe_numerics - 安全数值操作
        signals2 - 于实现信号和槽机制
        spirit - 解析和生成文本
        stacktrace - 获取程序堆栈跟踪信息
        string_algo - 字符串处理
        test - 单元测试
        typeindex - 类型信息
        variant - 变体类型
        vmd - 预处理宏操作
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cpp11 -> C++11标准规范</summary>
    <pre><code>
        algorithm - 算法汇总
        alignment specifiers - 校准说明符
        atomic - 原子操作
        auto - 自适应类型
        bind - lambda绑定函数
        call_once once_flag - 进程单例模式
        chrono - 时间操作库
        cite move forwared - 左值引用、右值引用、移动语义、完美转发
        condition_variable - 条件变量
        constexpr - 常量表达式
        decltype - 获取目标类型
        default - class的默认函数
        delegate constructor - 委托构造函数
        delete - class的禁用函数
        enum class - 枚举类
        explicit - 显式类型转换
        final override - 虚函数的结束与重写
        for loop - for循环新方式
        forward_list - 顺序容器
        future async - 期望、异步
        inherited constructors - 继承构造函数
        lock - 锁管理
        mutex - 互斥锁
        nullptr - 空指针
        random - 随机数新方式
        regex - 正则表达式
        sizeof - 新方法(可计算class)
        static_assert - 静态断言
        Tail return type - 函数尾部定义返回类型
        thread_local - 线程局部变量
        thread - 线程池
        tie - 包装成元组的函数
        tuple - 元组
        union - 联合体
        unique_ptr shared_ptr weak_ptr - 智能指针
        volatile - 易变的
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cpp14 -> C++14标准规范</summary>
    <pre><code>
        [[deprecated]] - function的弃用
        auto lambda - lambda支持auto形参
        auto return - 自动返回类型
        constexpr more - 常量更多的特性
        constexpr template - 模板常量
        exchange - 交换
        integer_sequence - 整数序列
        make_unique - 智能指针-唯一指针
        quoted - 字符串添加引号
        shared_timed_mutex shared_lock - 读写锁(共享锁)
        template fun - 模板函数
        other name template - 模板重载
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cpp17 -> C++17标准规范</summary>
    <pre><code>
        __attribute__ - 状态修饰定义
        __has_include - 是否包含库判定
        [[fallthrough]] - switch跳过break判定警告屏蔽
        [[nodiscard]] - 返回必被处理修饰
        any - 通用容器
        apply - 参数包
        as_const - 创建只读引用
        constexpr lambda - lambda常量表达式
        filesystem - 文件读写库
        folding expressions - 折叠表达式
        from_chars to_chars - 变量与char[]互相转换
        if init - if初始化
        infer_type - 类型自推导
        inline type - 内联变量
        invoke - 调用任何类型的可调用对象
        lambda *this - lambda函数的this引用捕获
        make_from_tuple - 元组转类构造对象
        maybe_unused - 可能未使用修饰
        more structured binding - 更多的结构化绑定
        nested namespace - 命名空间嵌套
        optional - 可能含无值模板
        remove_reference - 移除引用修饰
        shared_mutex - 读写锁
        string_view - 字符串复制类型
        structured binding - 结构化绑定
        variant monostate - 变体容器
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cpp20 -> C++20标准规范</summary>
    <pre><code>
        [[likely]] [[unlikely]] - 分支预测条件编译
        [[no_unique_address]] - 优化类成员空间
        assume_aligned - 内存对齐断言
        atomic shared_ptr float - 新增类型
        auto constainer - 简化容器内部类型推断
        barrier - 原子操作屏障
        basic_osyncstream - 输出流的多线程同步
        bind_front - 函数参数绑定
        chrono calendar time_zone - 时间库日历和时区
        compare - '<=>'逻辑计算
        concepts constraints - 概念和约束
        conroutine - 协程
        consteval - 编译期间执行
        constint - 零初始化和常量初始化
        counting_semaphore - 信号量
        endian - 字节序
        for loop init - 循环初始化
        format - 字符串格式化方法
        function template abbreviation - 函数模板缩写
        init catch - 支持初始化捕捉
        is_bounded_array - 检查T是否是已知边界的数组类型
        jthread - 新线程
        lambda_template - lambda的template
        lambda_this - lambda的this
        latch - 锁存器(同步线程向下计数器)
        lerp - 线性插值
        make_shared support constructed array - make_shared支持构造数组
        midpoint - 计算中点
        modules - 模块化特性(**will donw**)
        numbers - 常量库
        omit tempname - 省略tempname
        perfect forwarding - 完美转发
        Ranges - 范围库(迭代器库的扩展和泛化)
        remove_cvref - 移除类型的顶层const、volatile修饰符
        semaphore - 信号量同步机制
        source_lacation - 源码信息(文件名、行号以及函数名)
        span - 连续内存范围
        ssize - 获取容器或数组的大小
        starts_with ends_with - 判断特定字符是否前缀开始/后缀结束
        struct init - 结构体初始化
        synchronization - 同步库
        to_address - 获取指针的地址
        using enum - 支持using enum
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cpp98 -> C++98标准规范</summary>
    <pre><code>
        bool - 支持布尔
        cast - 支持强制转换 `static_cast`、`dynamic_cast`、`const_cast`和`reinterpret_cast`
        comma operator - 支持逗号操作符
        friend - 支持友元
        inline - 支持内联
        mutable - 支持可变
        namespace - 支持命名空间
        operator - 支持运算符重载
        RTTI - 支持运行时类型识别(资源获取即初始化)
        STL - 支持标准模板库
        template - 支持模板
        try catch throw - 支持异常处理
        typedef - 支持类型重命名
        typeid - 支持运行时类型识别
        virtual - 支持虚函数
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> cppcollect -> c++ 各版本同一特性改进汇总</summary>
    <pre><code>
        lambda - 匿名函数
        ptr - 指针
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> more -> 其他代码</summary>
    <pre><code>
        CheckGccVersion - 获取gcc版本
        connect_file - 连接文件
        inherit - 继承
        max_heap - 最大堆
        OpenMP - 并行编程
        os_file - 文件操作(同名不同类型文件 克隆指定位置)
        power_calculate - 幂次计算 大数乘法
        quine - quine(自我复制程序)
        vtable - 虚表
    </code></pre>
    </details>
    bate more - 标准库版本扩展细分
    bate - 标准库版本总结
    task - 测试Demo
</code></pre>
</details>
    <br />
<details>
<summary>-> OtherFile -> 汇总笔记(环境构建以及其他总结)</summary>
<pre><code>
    <details>
    <summary>-> construct -> 环境配置</summary>
    <pre><code>
        Construct the Android Packing And Debug - 构建Android环境的笔记
        Construct the Android - 构建Android环境的笔记
        Construct the cpp boost - 构建c++ Boost环境的笔记
        Construct the cpp - 构建c++环境的笔记
        Construct the cpp - 构建c++标准库20环境的笔记
        Construct the python from ue5 - 构建python环境的笔记
        Construct the vcpkg - 构建vcpkg的笔记
    </code></pre>
    </details>
    agreement - 开源协议汇总
    Creash problem - 目前遇到ue闪退的主要解决方案
    Debug_Log - 调试编译日志
    EncounterProblemsAndMethod - 目前遇到ue崩溃问题及其解决方案
    game task - 各类游戏操作记录
    node notes - 节点汇总笔记
    OpenMoreLib - Open前缀三方扩展库
</code></pre>
</details>
    <br />
<details>
<summary>-> ProjectNote -> 搜集到有关的项目,对其的解析笔记(Loading...)</summary>
<pre><code>
    Lyra Starter Game - 官方天琴座游戏项目
    VRExpPluginExample - OpenXR示例项目
</code></pre>
</details>
    <br />
<details>
<summary>-> Tools -> 与UE配套的相关工具(Loading...)</summary>
<pre><code>
    <details>
    <summary>-> Compiler -> 编译器</summary>
    <pre><code>
        c_cpp - c和cpp的编译器汇总及介绍
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Git -> Git上传基本指令</summary>
    <pre><code>
        OutputToGit - 输出到git仓库
        ReverseCommit - 撤销git提交
        UpdateToGit - 更新git仓库
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Peculiarity -> UE相关特性介绍</summary>
    <pre><code>
        Chaos - 动态破碎布料解算
        Feflect - 反射技术
        Lumen - 软件光线追踪技术
        Nanite - 动态无限面数
        Niagara - 粒子系统
    </code></pre>
    </details>      
        <br />
    <details>
    <summary>-> Plugins -> UE相关插件介绍</summary>
    <pre><code>
        plugins -> UE相关插件介绍汇总
    </code></pre>
    </details> 
        <br />
    <details>
    <summary>-> vs code -> visual studio code 配置</summary>
    <pre><code>
        add_plugins - 目前存在的插件
        c_cpp_properties - c++语言配置
        keybindings - 快捷键配置
        launch - 调试配置
        settings - 设置
        tasks - 任务配置
    </code></pre>
    </details>
        cloc - 代码统计工具
        cmd - cmd指令  
</code></pre>
</details>
    <br />
<details>
<summary>-> Unreal Engine4 -> ue4相关的笔记(Done)</summary>
<pre><code>
    -> 0【虚幻4】UE4初学者系列教程合集-全中文新手入门教程 BV164411Y732
    -> 1 siki Cpp基础 BV1Wt4y1Q7ED
    -> 2 siki 动作游戏入门 BV1Ki4y1V78e
    -> 3 官网 开始入门
    -> 4 siki Unreal蓝图案例 BV1F7411L7pg
    -> 5 siki 换装系统 BV1p64y1F7fh
    -> 6 背包系统 BV1r4411d76g
    -> book notes -> 书籍相关笔记
</code></pre>
</details>
    <br />
<details>
<summary>-> Unreal Engine5 -> ue5相关的笔记(Loading...)</summary>
<pre><code>
    <details>
    <summary>-> 蓝图(BluePrints) -> 对应名字的蓝图</summary>
    <pre><code>
        -> 函数(Functions) -> 特定API解析
        -> 节点(Node) -> 蓝图节点
        -> 蓝图类(BP Class) -> 创建的蓝图类模板
        -> 事件(Event) -> 触发事件节点
        -> 组件(Component) -> Actor模板类添加的组件
        结构(Struct) - 结构体
        蓝图函数库(BlueprintFunctionlibraryLib) - 蓝图函数库
        枚举(Enum) - 枚举
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> 模型(Model) - 基本模型创建</summary>
    <pre><code>
        -> 0基础
        -> 1光源
        -> 2过场动画
        -> 3形状
        -> 4媒体模板
        -> 5视觉效果
        -> 6体积
        -> 7所有类
        -> 8放置Actor面板
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> 人工智能(Artificial Intelligence) - AI行为要素</summary>
    <pre><code>
        黑板(Blackboard) - AI行为必要数据存储库
        行为树(Behavior Tree) - AI行为逻辑设定
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> 输入(Input) -> ue5增强输入特性</summary>
    <pre><code>
        输入操作 - 条件
        输入映射情境 - 管理
        玩家可映射输入配置 - 设置
        ProjectSetting_ActionMappings - 离散渐进按键预设
        ProjectSetting_AxisMappings - 连续渐进按键预设
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Cpp -> UE中c++开发相关笔记</summary>
    <pre><code>
        <details>
        <summary>-> 宏 -> UE宏预设</summary>
        <pre><code>
            GENERATED_BODY
            UFunctions
        </code></pre>
        </details>
            <br />
        <details>
        <summary>-> Class -> UE类</summary>
        <pre><code>
                <br />
            <details>
            <summary>-> 多线程 -> UE多线程汇总</summary>
            <pre><code>
                AsyncTask - 并发线程池
                FRunnable - 线程执行体
                TaskGraph - 任务图
                thread - c++基础多线程
            </code></pre>
            </details>
                <br />
            <details>
            <summary>-> 异步 -> UE异步汇总</summary>
            <pre><code>
                UBlueprintAsyncActionBase - 异步蓝图
            </code></pre>
            </details>
                <br />
        </code></pre>
        </details>
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Project-Build -> 以vs构建工程笔记</summary>
    <pre><code>
        Note - 笔记
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Project-Package -> 不同环境打包工程笔记</summary>
    <pre><code>
        Android - 打包安卓
        Windows - 打包Windows
    </code></pre>
    </details> 
    bate -> ue版本控制
</code></pre>
</details>
    <br />
<details>
<summary>-> Unreal Engine from Project -> 实现为主,泛化为辅(Loading...)</summary>
<pre><code>
    <details>
    <summary>-> bilibili -> b站</summary>
    <pre><code>
        -> 谌嘉诚 31898841
        -> 非真实元小仙 352113380
        -> 技术宅阿棍儿 92060300
        -> 就是如此多娇的Brilaxy 91486031
        -> 瞬夜之港 519286600
        -> 遥不可及的柒 600306449
        -> 游方学者 691857592
        -> 游戏人YR 5935185
        -> 张亮002 22867601
        -> GALAXIX动漫大陆 44903914
        -> tt脑思 398514747
        -> Unreal_Explorer 392671534
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> Website -> 个人网站</summary>
    <pre><code>
        砥才人_代码质疑人生
        风恋残雪_凡事看本质
    </code></pre>
    </details>
        <br />
    <details>
    <summary>-> zhihu -> 知乎</summary>
    <pre><code>
        大侠刘茗
        大钊_InsideUE4
        戴巍
        房燕良
        放牛的星星
        孤傲雕
        技术宅阿棍儿
        篮子悠悠
        南京周润发
        日天
        小熊猫吃牙膏
        星辰大海
        喧嚣
        一头神秘鸟
        这像画码
        佐味_图解ue4源码
        DrakFlameMaster
        davidpp
        Elvic Liang
        FlyingTree
        Jerish
        Jiff
        LRyir
        Mantra
        Michael
    </code></pre>
    </details>
    0MarkdownGrammar - markdown语法
    1htmlGrammar - markdown-html语法
    2CopyCode - 特定复制markdown语法
    Readme - 本根目录内容说明
</code></pre>
</details>
    <br />
<details>
<summary>-> Unreal Engine Self Project -> ue自身工程代码架构及记录</summary>
<pre><code>
    Core_Runtime - 工程核心
    DesignProject - 工程设计
</code></pre>
</details>
    <br />

import - 导入到ue相关内容现象记录

plugins - 笔者已知的ue相关插件描述

ResearchBlueprintNodeNow - 目前侧重研究的ue节点

work task - 笔者目前的**工作重心**

