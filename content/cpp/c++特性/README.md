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
    bate more - 标准库版本扩展细分
    bate - 标准库版本总结
    task - 测试Demo
</code></pre>
</details>