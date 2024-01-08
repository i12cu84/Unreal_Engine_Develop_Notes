# Unreal_Engine_Develop_Notes

<details>
<summary>-> assets -> 有关所有notes的markdown图片</summary>
<pre><code>
    [持续补充,将会适配到有需要的markdown中]
</code></pre>
</details>
<br>
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
    <br>
    <details>
    <summary>-> common -> c++ 各版本同一特性改进汇总</summary>
    <pre><code>
        lambda - 匿名函数
        ptr - 指针
    </code></pre>
    </details>
    <br>
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
    <br>
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
    <br>
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
    <br>
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
    <br>
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
    <br>
    <details>
    <summary>-> other -> 其他特性(不知道版本)</summary>
    <pre><code>
        __DATE__ - 获取当前日期
        __FILE__ - 获取当前文件名
        __FUNCTION__ - 获取当前函数名
        __LINE__ - 获取当前行号
        __STDC__ - 获取编译器是否符合标准
        __TIME__ - 获取当前时间
        __VA_ARGS__ - 获取可变参数
        # - 宏定义覆盖运算符
        ## - 连接运算符
        #define typedef - 宏定义与类型重命名
        #define - 宏定义
        #if defined - 检查蒂宏定义
        #ifdef #pragram once - 头文件编译一次方法
        #undef - 宏定义取消
        args sum - 可变形参
        args template - 可变形参模板类
        callback - 回调函数
        fold - 可变形参折叠表达式
        fun ptr typedef - 可变形参函数重定义(或许仍可以拓展)
        point add - 指针累加运算符分析
        sizeof strlen - 字符串占用区分
        struct using - 结构体中using类型别名
        two meaning - 二义性(nullptr定义区分的起因)
        typeof decltype - 获取变量类型
        va_start va_arg va_end - 可变参数关键字(初始化/获取/结束)
        vprintf - printf调用源代码
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> source -> 其他代码</summary>
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
<br>
<details>
<summary>-> image -> 图片素材</summary>
<pre><code>
    [持续补充]
</code></pre>
</details>
<br>
<details>
<summary>-> OtherFile -> 汇总笔记(环境构建以及其他总结)</summary>
<pre><code>
    <details>
    <summary>-> build -> ue自身工程代码架构及记录</summary>
    <pre><code>
        CoreRuntime - 工程核心
        DesignProject - 工程设计
        ImportModel - 工程模型导入
        RootDirectory - 工程目录
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Construct -> 环境配置</summary>
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
    <br>
    <details>
    <summary>-> Log -> 日志</summary>
    <pre><code>
        Creash problem - 目前遇到ue闪退的主要解决方案
        Debug_Log - 调试编译日志
        EncounterProblemsAndMethod - 目前遇到ue崩溃问题及其解决方案
    </code></pre>
    </details>
    agreement - 开源协议汇总
    game task - 各类游戏操作记录
    node notes - 节点汇总笔记
    OpenMoreLib - Open前缀三方扩展库
</code></pre>
</details>
<br>
<details>
<summary>-> ProjectNote -> 搜集到有关的项目,对其的解析笔记(Loading...)</summary>
<pre><code>
    Lyra Starter Game - 官方天琴座游戏项目
    VRExpPluginExample - OpenXR示例项目
</code></pre>
</details>
<br>
<details>
<summary>-> Temp -> 临时文件夹</summary>
<pre><code>
    c/c++类代码在该项目下编译后执行文件将存于此处为缓存,可删除
</code></pre>
</details>
<br>
<details>
<summary>-> shared -> 知识分享</summary>
<pre><code>
    <details>
    <summary>-> algorithm -> 常规算法</summary>
    <pre><code>
        AVL-Tree-Cpp - AVL树
        Bezier-Curve-Cpp - 贝塞尔曲线
        B-Plus-Tree-Cpp - B+树
        BRDF-Cpp - 双向反射分布函数
        BSP-Tree-Cpp - 二叉空间划分
        BSSRDF-Cpp - 双向散射表面反射分布函数
        BVH-Cpp - 层次包围盒
        Convex-hull-Algorithm-Cpp - 凸包
        Huffman-Compression-Algorithm-Cpp - 哈夫曼编码
        KD-Tree-Cpp - KD树
        MCPT-Cpp - 蒙特卡洛路径追踪
        NURBS-Cpp - 非均匀有理B样条曲线
        Octree-Cpp - 八叉树
        Ray-Tracing-Cpp - 光线追踪
        Red-Black-Tree-Cpp - 红黑树
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> app -> Python执行文件</summary>
    <pre><code>
        [详细功能在文件中有注释,不赘述]
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> bin -> Windows执行文件</summary>
    <pre><code>
        WindowsFileMoveTo - 移动到路径文件夹的脚本
        WindowsFileMoveToAndroid - 移动到Android文件夹的脚本
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> data -> 数值处理</summary>
    <pre><code>
        <details>
        <summary>-> Data-Mining-Algorithm-Matlab -> 数据挖掘</summary>
        <pre><code>
            Apriori - 关联规则挖掘算法
            K-means - K-均值算法
            Hierarchical clustering - 分层聚类
            ID3 - 决策树
            Naive bayes classifier - 朴素贝叶斯分类器
            Support vector machine - 支持向量机
            Fuzzy C-means clustering algorithm - 模糊c均值聚类算法
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> Intelligent-Computing-Matlab -> 智能计算</summary>
        <pre><code>
            BP neural network - BP神经网络
            Hopfield neural network - Hopfield神经网络
            Radial basis function - 径向基函数
            Genetic algorithm - 遗传算法
            Particle swarm optimization - 粒子群优化算法
            Ant colony algorithm - 蚁群算法
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> Numerical-Algebra-Matlab -> 数值代数</summary>
        <pre><code>
            Gaussian elimination method - 高斯消去法
            Column pivot elimination - 列轴消元法
            Chasing method - 追逐法
            Root-squaring method - Root-squaring方法
            Jacobi iteration method - 雅可比迭代法
            Gaussian iteration method - 高斯迭代法
            JOR method - 约旦迭代法
            SOR method - 超松弛迭代法
            Steepest descent method - 最速下降法
            Conjugate gradient methods - 共轭梯度法
            The steepest descent method and the rate of convergence - 最速下降法和收敛速度
            Newton iteration method - 牛顿迭代法
            Secant method - 割线法
            Iteration method - 迭代法
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> Numerical-Approximation-Matlab -> 数值逼近</summary>
        <pre><code>
            Lagrange's interpolation - 拉格朗日插值
            Newton interpolation - 牛顿插值
            Analogue function - 模拟
            Hermite interpolation function - 埃尔米特插值
            Spline interpolation - 样条插值
            Polynomial canonical orthogonal fit - 多项式正则正交拟合
            Newton-cotes formula - 牛顿-柯特斯公式
            Euler's method - 欧拉方法
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> Numerical-Methods-for-PDE-Matlab -> 偏微分方程数值解法</summary>
        <pre><code>
            PDE fun - 数值解法函数
            Finite difference method - 有限差分法
            Finite element difference method - 有限元差分法
            Calculus of differences - 差分演算
            Two dimensional heat conduction equation - 二维热传导方程
            ADI - 求解偏微分方程的数值方法
            Wave equation - 波动方程
            Diffusion-convection equation - 对流扩散方程
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> Optimization-Theory-and-Algorithms-Matlab -> 最优化理论</summary>
        <pre><code>
            Linear programming - 线性规划
            Golden cut algorithm - 黄金分割算法
            Ternary quadratic interpolation method - 三元二次插值法
            Steepest descent method - 最速下降法
            Newton method - 牛顿法
            Conjugate gradient methods - 共轭梯度法
            Uadratic programming - 二次规划
            Rosen's gradient projection method - 梯度投影法
        </code></pre>
        </details>
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> doc -> 文档</summary>
    <pre><code>
        agreement - 协议
        BIOS UEFI - 系统引导
        NTFS EFI FAT - 存储格式
        port - 端口
        pwa公共标准 - 渐进式web应用
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> local -> 局部内容更新</summary>
    <pre><code>
        HotUpdateHotFix -> 热更新
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> log -> unity开发日志</summary>
    <pre><code>
        [详情看本作者上传的同名库,库中有demo,不赘述]
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> modules -> 机器学习算法模块</summary>
    <pre><code>
        <details>
        <summary>-> DeepLearningAlgorithm -> 深度学习算法</summary>
        <pre><code>
            Convolutional Neural Networks -> 卷积神经网络
            Recurrent Neural Networks -> 循环神经网络
            Long Short-Term Memory Networks -> 长短期记忆网络
            Gated Recurrent Unit -> 门控循环单元
            Autoencoders -> 自编码器
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> EvolutionaryAlgorithm -> 进化算法</summary>
        <pre><code>
            GeneticAlgorithm -> 遗传算法
            ParticleSwarmOptimization -> 粒子群优化
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> MachineLearningAlgorithm -> 机器学习算法</summary>
        <pre><code>
            LinearRegression -> 线性回归
            LogisticRegression -> 逻辑回归
            DecisionTrees -> 决策树
            RandomForests -> 随机森林
            SupportVectorMachines -> 支持向量机
            NeuralNetworks -> 神经网络
            Adaboost -> 集成算法
            GradientBoosting -> 梯度提升
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> NaturalLanguageProcessingAlgorithm -> 自然语言处理算法(NLP算法)</summary>
        <pre><code>
            NaiveBayes -> 朴素贝叶斯
            LogisticRegression -> 逻辑回归
            SupportVectorMachine(SVN) -> 支持向量机
            ConvolutionalNeuralNetwork(CNN) -> 卷积神经网络
            RecurrentNeuralNetwork(RNN) -> 循环神经网络
            LongShortTermMemory(LSTM) -> 长短时记忆网络
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> OtherArtificialIntelligenceAlgorithm -> 其他人工智能算法</summary>
        <pre><code>
            KNN(K-NearestNeighbors) -> K最近邻
            MarkovChains -> 马尔可夫链
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> ReinforcementLearningAlgorithm -> 强化学习算法</summary>
        <pre><code>
            Q-Learning -> Q学习
            Deep Q-Network -> 深度Q网络
            Policy Gradient -> 策略梯度
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> UnsupervisedLearningArithmeticAlgorithm -> 算法模块</summary>
        <pre><code>
            Unsupervised-Learning-Arithmetic-Algorithm -> 无监督学习算法
            K-Means Clustering -> K均值聚类
            Hierarchical Clustering -> 层次聚类
            Principal Component Analysis -> 主成分分析
            Autoencoders -> 自编码器
        </code></pre>
        </details>
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> paper -> 毕业设计</summary>
    <pre><code>
        [已整理,不赘述]
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> plugins -> UE插件</summary>
    <pre><code>
        lib - 蓝图库插件
        TP - 添加Tag/导出Tag插件
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> private -> 笔者公开分享私有知识(转载请注明出处)</summary>
    <pre><code>
        AutoHotkey-quick-click-Follow - 自动跟随脚本
        AutoAgree.js -> 自动点赞脚本
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> public -> 已知可公开分享知识</summary>
    <pre><code>
        c++编程规范-101条规则准则与最佳实践
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> source -> C++执行文件</summary>
    <pre><code>
        [详细功能在文件中有注释,不赘述]
    </code></pre>
    </details>
</code></pre>
</details>
<br>
<details>
<summary>-> Tools -> 与UE配套的相关工具(Loading...)</summary>
<pre><code>
    <details>
    <summary>-> Andriod -> 安卓</summary>
    <pre><code>
        adb_unstall_HarmonyOS_App - 安卓卸载鸿蒙应用
        adb - 安卓调试工具
        fastboot - 安卓快速启动
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> browser -> 浏览器</summary>
    <pre><code>
        console - js命令行
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Compiler -> 编译器</summary>
    <pre><code>
        c_cpp - c和cpp的编译器汇总及介绍
        python - python的库汇总及介绍
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Git -> Git上传基本指令</summary>
    <pre><code>
        OutputToGit - 输出到git仓库
        ReverseCommit - 撤销git提交
        UpdateToGit - 更新git仓库
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Linux -> Linux系统中工具常用指令</summary>
    <pre><code>
        <details>
        <summary>-> 1System monitoring tool -> 系统监控工具</summary>
        <pre><code>
            vmstat -> 提供系统运行状态信息，如CPU使用率、内存使用情况、磁盘I/O等
            iostat -> 用于监控系统硬盘的使用情况
            sar（System Activity Reporter） -> 收集和报告系统活动的工具，提供全面的系统性能分析
            htop -> 进程监控工具，提供了丰富的界面来查看系统的实时进程和资源使用情况
            iotop -> 磁盘I/O监测工具，用于监控系统中的磁盘I/O活动
            free -> 显示内存的使用情况
            netstat -> 提供网络连接、路由表、接口统计等信息
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 2Network analysis tools -> 网络分析工具</summary>
        <pre><code>
            tcpdump -> 网络数据包捕获和分析工具
            iftop -> 监控网络带宽使用情况
            iptraf -> 提供实时的IP网络监控
            nethogs -> 监视每个进程的网络带宽使用
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 3Process management and viewing tools -> 进程管理和查看工具</summary>
        <pre><code>
            ps -> 查看当前运行的进程
            pstack -> 显示进程的调用栈
            fuser -> 通过文件或文件结构来识别使用该文件的进程
            lsof -> 列出所有打开的文件和它们的进程
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 4Development and debugging tools -> 开发和调试工具</summary>
        <pre><code>
            gdb -> 程序调试器
            make -> 自动化构建工具
            pt-query-digest -> 查询MySQL数据库的性能
            pt-pmp -> 查看进程的调用栈
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 5Other Useful Tools -> 其他实用工具</summary>
        <pre><code>
            byobu、tmux、screen -> 终端复用和会话管理工具，允许在多个会话之间切换
            dstat -> 综合监控系统运行状态
            arpwatch -> 监控以太网活动
            suricata -> 网络安全监控工具
            nagios -> 网络和服务器监控工具
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 6software testing tool -> 软件测试工具</summary>
        <pre><code>
            pytest -> 流行的Python测试框架
            Allure -> 用于自动化测试的报告工具
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> 7Package management tools -> 软件包管理工具</summary>
        <pre><code>
            yum -> 基于RPM的Linux软件包管理工具
            apt-get -> 基于Debian的Linux软件包管理工具
            pacman -> 基于Arch Linux的软件包管理工具
            emerge -> 基于Gentoo的软件包管理工具
            pkg -> 基于NetBSD的软件包管理工具
            pkg_add -> 基于OpenBSD的软件包管理工具
        </code></pre>
        </details>
    </code></pre>
    </details>
    <br>
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
    <br>
    <details>
    <summary>-> Plugins -> UE相关插件介绍</summary>
    <pre><code>
        plugins -> UE相关插件介绍描述汇总
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> UE -> UE相关工具介绍</summary>
    <pre><code>
        <details>
        <summary>-> code -> ue工程模块解析(version 5.2.1)</summary>
        <pre><code>
            AugmentedReality - 增强现实
            Chaos - 动态破碎布料解算
            Delegate - 委托
            Engine - 引擎
            Input - 输入
            Misc - 杂项
            UObject - 对象
            Windows - Windows配置
        </code></pre>
        </details>
        <br>
        UBT - 虚幻编译工具 UnrealBuildTool
        UHT - 虚幻头工具 UnrealHeaderTool
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> vs code -> visual studio code 配置</summary>
    <pre><code>
        <details>
        <summary>-> .vscode -> 配置文件</summary>
        <pre><code>
            c_cpp_properties - c++语言配置
            extensions - 插件配置(含介绍)
            keybindings - 快捷键配置
            launch - 调试配置
            settings - 设置
            tasks - 任务配置
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> User -> 配置文件(用户目录)</summary>
        <pre><code>
            keybindings - 快捷键配置
            settings - 设置
        </code></pre>
        </details>
        regex find and replace - 搜索替换正则表达式
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Windows -> Windows相关工具</summary>
    <pre><code>
        <details>
        <summary>-> Batch Script -> 批处理脚本</summary>
        <pre><code>
            BatchScript - Batch Script指令整合
            Install_[Android_Project_Name]-arm64 - 安装安卓脚本
            Uninstall_[Android_Project_Name]-arm64 - 卸载安卓脚本
            WindowsFileMoveTo - 同设备文件迁移脚本
            WindowsFileMoveToAndroid - 跨设备文件迁移脚本
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> cmd -> cmd工具</summary>
        <pre><code>
            cmd - cmd指令汇总及介绍
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> powershell -> powershell工具</summary>
        <pre><code>
            powershell - powershell指令汇总及介绍
        </code></pre>
        </details>
        compare batch_script cmd - 两者差异
        compare powershell cmd - 两者差异
    </code></pre>
    </details>
        cloc - 代码统计工具
        GDA - Android apk 解析工具
        linux_debug_method - linux代码调试方法
        windows_debug_method - windows代码调试方法
</code></pre>
</details>
<br>
<details>
<summary>-> Unreal Engine4 -> ue4相关的笔记(Done)</summary>
<pre><code>
    <details>
    <summary>-> 0【虚幻4】UE4初学者系列教程合集-全中文新手入门教程 BV164411Y732</summary>
    <pre><code>
        基础笔记
        蓝图笔记
        AI行为树
        动画入门
        节点笔记
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 1 siki Cpp基础 BV1Wt4y1Q7ED</summary>
    <pre><code>
        code - 代码
        cpp基础
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 2 siki 动作游戏入门 BV1Ki4y1V78e</summary>
    <pre><code>
        人物移动动画
        动画重定向
        视角攻击
        人物碰撞
        血条受伤及动画
        动画及行为树
        敌人的攻击
        行为树
        动画融合
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 3 官网 开始入门e</summary>
    <pre><code>
        相关网址
        走向喜欢引擎
        AEC蓝图案例课程
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 4 siki Unreal蓝图案例 BV1F7411L7pg</summary>
    <pre><code>
        note - 笔记
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 5 siki 换装系统 BV1p64y1F7fh</summary>
    <pre><code>
        note - 笔记
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> 6 背包系统 BV1r4411d76g</summary>
    <pre><code>
        note - 笔记
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> book notes -> 书籍相关笔记</summary>
    <pre><code>
        UnrealEngine4蓝图完全学习教程
    </code></pre>
    </details>
</code></pre>
</details>
<br>
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
    <br>
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
    <br>
    <details>
    <summary>-> 人工智能(Artificial Intelligence) - AI行为要素</summary>
    <pre><code>
        黑板(Blackboard) - AI行为必要数据存储库
        行为树(Behavior Tree) - AI行为逻辑设定
    </code></pre>
    </details>
    <br>
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
    <br>
    <details>
    <summary>-> Cpp -> UE中c++开发相关笔记</summary>
        <pre><code>
        <details>
        <summary>-> Class -> UE类</summary>
        <pre><code>
            <details>
            <summary>-> 多线程 -> UE多线程汇总</summary>
            <pre><code>
                AsyncTask - 并发线程池
                FRunnable - 线程执行体
                TaskGraph - 任务图
                thread - c++基础多线程
            </code></pre>
            </details>
            <br>
            <details>
            <summary>-> 异步 -> UE异步汇总</summary>
            <pre><code>
                UBlueprintAsyncActionBase - 异步蓝图
            </code></pre>
            </details>
            TEXT FNAME FSTRING - 三大文本类型转换
        </code></pre>
        </details>
        <br>
        <details>
        <summary>-> define -> UE宏预设</summary>
        <pre><code>
            GENERATED_BODY - 生成代码模板
            RIGVM_METHOD - 蓝图中的虚拟机方法
            UCLASS - 类
            UCLASSES - 组类声明
            UDELEGATE - 事件委托
            UENUM - 枚举
            UFUNCTION - 蓝图中调用的函数
            UFUNCTIONPOINTER - 函数指针
            UINTERFACE - 接口
            UMETA - 类、属性或函数添加元数据
            UPARAM - 声明函数的参数
            UPROPERTY - 定义属性元数据和变量说明符
            USTRUCT - 结构体
        </code></pre>
        </details>
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> Project-Build -> 以vs构建工程笔记</summary>
    <pre><code>
        Note - 笔记
    </code></pre>
    </details>
    <br>
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
<br>
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
    <br>
    <details>
    <summary>-> Website -> 个人网站</summary>
    <pre><code>
        砥才人_代码质疑人生
        风恋残雪_凡事看本质
    </code></pre>
    </details>
    <br>
    <details>
    <summary>-> zhihu -> 知乎</summary>
    <pre><code>
        菜小弟
        大侠刘茗
        大钊_InsideUE4
        戴巍
        房燕良
        放牛的星星
        飞翔的子明
        孤傲雕
        锅约科
        技术宅阿棍儿
        篮子悠悠
        灵知子
        南京周润发
        南山烟雨珠江潮
        牛岱
        清风亦枫
        日天
        旺仔好喝
        小熊猫吃牙膏
        星辰大海
        喧嚣
        杨睿涵
        一块大饼
        一头神秘鸟
        易米八一
        这像画码
        佐味_图解ue4源码
        a飞雷神
        bluecoder
        DrakFlameMaster
        davidpp
        Elvic Liang
        FlyingTree
        IceBear
        Jerish
        Jiff
        Jone
        LRyir
        Mantra
        Michael
        Mick235711
        MoonChildnSky
        rayhunter
        ShaVenZz
    </code></pre>
    </details>
    0MarkdownGrammar - markdown语法
    1htmlGrammar - markdown-html语法
    2CopyCode - 特定复制markdown语法
    Readme - 本根目录内容说明
</code></pre>
</details>
<br>

READNE - 展示当前路径文件夹内容(即当前文件)[其余同名文件不做赘述]

ResearchBlueprintNodeNow - 目前侧重研究的ue节点

work task - 笔者目前的工作重心

