// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Core\Public\Misc\AutomationTest.h

/**
 * 请求获取调用栈信息，并确保返回的结果非空。
 * 如果调用栈为空，将返回一个占位符 "Unknown"，并指定行号为 1。
 *
 * @param VariableName 用于存储返回的调用栈信息的数组。
 * @param IgnoreCount 跳过栈顶的帧数。
 * @param MaxDepth 遍历调用栈的最大深度。
 */
#define SAFE_GETSTACK(VariableName, IgnoreCount, MaxDepth)                                                \
    TArray<FProgramCounterSymbolInfo> VariableName = FPlatformStackWalk::GetStack(IgnoreCount, MaxDepth); \
    if (VariableName.Num() == 0)                                                                          \
    {                                                                                                     \
        /* 极少发生的情况，可能在某些情况下出现 */                                                           \
        FProgramCounterSymbolInfo &Info = VariableName.Emplace_GetRef();                                  \
        TCString<ANSICHAR>::Strcpy(Info.Filename, FProgramCounterSymbolInfo::MAX_NAME_LENGTH, "Unknown"); \
        Info.LineNumber = 1;                                                                              \
    }

/**
 *用于指定自动化测试需求/行为的标志
 *更新这个枚举时更新GetTestFlagsMap。
 */
struct EAutomationTestFlags
{
};

//用于指定预期消息的匹配类型的标志
namespace EAutomationExpectedMessageFlags
{
};

//用于指定预期错误消息的匹配类型的标志。别名用于向后兼容。
namespace EAutomationExpectedErrorFlags = EAutomationExpectedMessageFlags;

//
struct FAutomationTelemetryData{};

//存储自动化测试执行结果的简单类
class CORE_API FAutomationTestExecutionInfo
{
};

//存储自动化测试信息的简单类
class CORE_API FAutomationTestInfo
{
};

// 简单的抽象基类，用于创建需要顺序运行的单个测试的时间延迟(Loadmap & Wait，打开编辑器& Wait，然后执行…)
class IAutomationLatentCommand : public TSharedFromThis<IAutomationLatentCommand>
{
};

// 一个简单的潜在命令，在另一个线程上运行所提供的函数
class FThreadedAutomationLatentCommand : public IAutomationLatentCommand
{
};

// 用于网络化、多参与者测试的简单抽象基类
class IAutomationNetworkCommand : public TSharedFromThis<IAutomationNetworkCommand>
{
};

//
struct FAutomationExpectedMessage
{
};

//
struct FAutomationScreenshotData
{
};

//
struct CORE_API FAutomationScreenshotCompareResults
{
};

//
struct FAutomationComparisonToleranceAmount
{
};

//表示运行自动化测试的主要框架的类
class CORE_API FAutomationTestFramework
{
};

//用于所有自动化测试的简单抽象基类
class CORE_API FAutomationTestBase
{
};

//
class CORE_API FBDDAutomationTestBase : public FAutomationTestBase
{
};

//
class CORE_API FAutomationSpecBase
    : public FAutomationTestBase,
      public TSharedFromThis<FAutomationSpecBase>
{
};

//////////////////////////////////////////////////
// 潜在的命令定义宏

#define DEFINE_LATENT_AUTOMATION_COMMAND(CommandName)   \
    class CommandName : public IAutomationLatentCommand \
    {                                                   \
    public:                                             \
        virtual ~CommandName()                          \
        {                                               \
        }                                               \
        virtual bool Update() override;                 \
    }

#define DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(CommandName, ParamType, ParamName) \
    class CommandName : public IAutomationLatentCommand                                   \
    {                                                                                     \
    public:                                                                               \
        CommandName(ParamType InputParam)                                                 \
            : ParamName(InputParam)                                                       \
        {                                                                                 \
        }                                                                                 \
        virtual ~CommandName()                                                            \
        {                                                                                 \
        }                                                                                 \
        virtual bool Update() override;                                                   \
                                                                                          \
    private:                                                                              \
        ParamType ParamName;                                                              \
    }

#define DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(CommandName, ParamType0, ParamName0, ParamType1, ParamName1) \
    class CommandName : public IAutomationLatentCommand                                                             \
    {                                                                                                               \
    public:                                                                                                         \
        CommandName(ParamType0 InputParam0, ParamType1 InputParam1)                                                 \
            : ParamName0(InputParam0), ParamName1(InputParam1)                                                      \
        {                                                                                                           \
        }                                                                                                           \
        virtual ~CommandName()                                                                                      \
        {                                                                                                           \
        }                                                                                                           \
        virtual bool Update() override;                                                                             \
                                                                                                                    \
    private:                                                                                                        \
        ParamType0 ParamName0;                                                                                      \
        ParamType1 ParamName1;                                                                                      \
    }

#define DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(CommandName, ParamType0, ParamName0, ParamType1, ParamName1, ParamType2, ParamName2) \
    class CommandName : public IAutomationLatentCommand                                                                                       \
    {                                                                                                                                         \
    public:                                                                                                                                   \
        CommandName(ParamType0 InputParam0, ParamType1 InputParam1, ParamType2 InputParam2)                                                   \
            : ParamName0(InputParam0), ParamName1(InputParam1), ParamName2(InputParam2)                                                       \
        {                                                                                                                                     \
        }                                                                                                                                     \
        virtual ~CommandName()                                                                                                                \
        {                                                                                                                                     \
        }                                                                                                                                     \
        virtual bool Update() override;                                                                                                       \
                                                                                                                                              \
    private:                                                                                                                                  \
        ParamType0 ParamName0;                                                                                                                \
        ParamType1 ParamName1;                                                                                                                \
        ParamType2 ParamName2;                                                                                                                \
    }

#define DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(CommandName, ParamType0, ParamName0, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3) \
    class CommandName : public IAutomationLatentCommand                                                                                                              \
    {                                                                                                                                                                \
    public:                                                                                                                                                          \
        CommandName(ParamType0 InputParam0, ParamType1 InputParam1, ParamType2 InputParam2, ParamType3 InputParam3)                                                  \
            : ParamName0(InputParam0), ParamName1(InputParam1), ParamName2(InputParam2), ParamName3(InputParam3)                                                     \
        {                                                                                                                                                            \
        }                                                                                                                                                            \
        virtual ~CommandName()                                                                                                                                       \
        {                                                                                                                                                            \
        }                                                                                                                                                            \
        virtual bool Update() override;                                                                                                                              \
                                                                                                                                                                     \
    private:                                                                                                                                                         \
        ParamType0 ParamName0;                                                                                                                                       \
        ParamType1 ParamName1;                                                                                                                                       \
        ParamType2 ParamName2;                                                                                                                                       \
        ParamType3 ParamName3;                                                                                                                                       \
    }

#define DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(CommandName, ParamType0, ParamName0, ParamType1, ParamName1, ParamType2, ParamName2, ParamType3, ParamName3, ParamType4, ParamName4) \
    class CommandName : public IAutomationLatentCommand                                                                                                                                      \
    {                                                                                                                                                                                        \
    public:                                                                                                                                                                                  \
        CommandName(ParamType0 InputParam0, ParamType1 InputParam1, ParamType2 InputParam2, ParamType3 InputParam3, ParamType4 InputParam4)                                                  \
            : ParamName0(InputParam0), ParamName1(InputParam1), ParamName2(InputParam2), ParamName3(InputParam3), ParamName4(InputParam4)                                                    \
        {                                                                                                                                                                                    \
        }                                                                                                                                                                                    \
        virtual ~CommandName()                                                                                                                                                               \
        {                                                                                                                                                                                    \
        }                                                                                                                                                                                    \
        virtual bool Update() override;                                                                                                                                                      \
                                                                                                                                                                                             \
    private:                                                                                                                                                                                 \
        ParamType0 ParamName0;                                                                                                                                                               \
        ParamType1 ParamName1;                                                                                                                                                               \
        ParamType2 ParamName2;                                                                                                                                                               \
        ParamType3 ParamName3;                                                                                                                                                               \
        ParamType4 ParamName4;                                                                                                                                                               \
    }

#define DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND(EXPORT_API, CommandName) \
    class EXPORT_API CommandName : public IAutomationLatentCommand         \
    {                                                                      \
    public:                                                                \
        virtual ~CommandName()                                             \
        {                                                                  \
        }                                                                  \
        virtual bool Update() override;                                    \
    }

#define DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(EXPORT_API, CommandName, ParamType, ParamName) \
    class EXPORT_API CommandName : public IAutomationLatentCommand                                             \
    {                                                                                                          \
    public:                                                                                                    \
        CommandName(ParamType InputParam)                                                                      \
            : ParamName(InputParam)                                                                            \
        {                                                                                                      \
        }                                                                                                      \
        virtual ~CommandName()                                                                                 \
        {                                                                                                      \
        }                                                                                                      \
        virtual bool Update() override;                                                                        \
                                                                                                               \
    private:                                                                                                   \
        ParamType ParamName;                                                                                   \
    }
//多参数代码省略

#define DEFINE_ENGINE_LATENT_AUTOMATION_COMMAND(CommandName) \
    DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND(ENGINE_API, CommandName)

#define DEFINE_ENGINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(CommandName, ParamType, ParamName) \
    DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(ENGINE_API, CommandName, ParamType, ParamName)

#define DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND_WITH_RETRIES(EXPORT_API, CommandName, RetryCount, WaitTimeBetweenRuns) \
    class EXPORT_API CommandName : public IAutomationLatentCommandWithRetriesAndDelays                                   \
    {                                                                                                                    \
    public:                                                                                                              \
        CommandName(int32 InRetryCount, double InWaitTimeBetweenRuns)                                                    \
            : IAutomationLatentCommandWithRetriesAndDelays(#CommandName, InRetryCount, InWaitTimeBetweenRuns)            \
        {                                                                                                                \
        }                                                                                                                \
        virtual ~CommandName()                                                                                           \
        {                                                                                                                \
        }                                                                                                                \
        virtual bool Execute() override;                                                                                 \
                                                                                                                         \
    private:                                                                                                             \
    }

#define DEFINE_EXPORTED_LATENT_AUTOMATION_COMMAND_WITH_RETRIES_ONE_PARAMETER(EXPORT_API, CommandName, RetryCount, WaitTimeBetweenRuns, ParamType, ParamName) \
    class EXPORT_API CommandName : public IAutomationLatentCommandWithRetriesAndDelays                                                                       \
    {                                                                                                                                                        \
    public:                                                                                                                                                  \
        CommandName(int32 InRetryCount, double InWaitTimeBetweenRuns, ParamType ParamName)                                                                   \
            : IAutomationLatentCommandWithRetriesAndDelays(#CommandName, InRetryCount, InWaitTimeBetweenRuns), ParamName(ParamName)                          \
        {                                                                                                                                                    \
        }                                                                                                                                                    \
        virtual ~CommandName()                                                                                                                               \
        {                                                                                                                                                    \
        }                                                                                                                                                    \
        virtual bool Execute() override;                                                                                                                     \
                                                                                                                                                             \
    private:                                                                                                                                                 \
        ParamType ParamName;                                                                                                                                 \
    }
//多参数代码省略

// 宏来简化排队潜在命令的语法
#define ADD_LATENT_AUTOMATION_COMMAND(ClassDeclaration) FAutomationTestFramework::Get().EnqueueLatentCommand(MakeShareable(new ClassDeclaration));

// 声明这个类
#define START_NETWORK_AUTOMATION_COMMAND(ClassDeclaration)                 \
    class F##ClassDeclaration : public IAutomationNetworkCommand           \
    {                                                                      \
    private:                                                               \
        int32 RoleIndex;                                                   \
                                                                           \
    public:                                                                \
        F##ClassDeclaration(int32 InRoleIndex) : RoleIndex(InRoleIndex) {} \
        virtual ~F##ClassDeclaration() {}                                  \
        virtual uint32 GetRoleIndex() const override { return RoleIndex; } \
        virtual void Run() override

// close the class and add to the framework
#define END_NETWORK_AUTOMATION_COMMAND(ClassDeclaration, InRoleIndex) \
    }                                                                 \
    ;                                                                 \
    FAutomationTestFramework::Get().EnqueueNetworkCommand(MakeShareable(new F##ClassDeclaration(InRoleIndex)));

/**
 *用于简化创建新的自动化测试的宏。要创建一个新的测试，只需将
 *实现_simple_automation_test (NewAutomationClassName, AutomationClassFlags)
 * IMPLEMENT_COMPLEX_AUTOMATION_TEST(NewAutomationClassName, AutomationClassFlags)
 *在他们的CPP文件中，然后继续编写以下实现:
 * bool NewAutomationTestClassName::RunTest() {}
 *虽然宏也可以允许指定代码，但将其放在宏之外是允许的
 *更容易调试的代码。
 *
 *支持自动化测试的构建将自动创建和注册一个自动化测试实例
 *自动化测试框架的结果宏。
 */

#define IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, FileName, LineNumber)                                                           \
    class TClass : public TBaseClass                                                                                                                                     \
    {                                                                                                                                                                    \
    public:                                                                                                                                                              \
        TClass(const FString &InName)                                                                                                                                    \
            : TBaseClass(InName, false)                                                                                                                                  \
        {                                                                                                                                                                \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                        \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                     \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                   \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                      \
        }                                                                                                                                                                \
        virtual uint32 GetTestFlags() const override { return TFlags; }                                                                                                  \
        virtual bool IsStressTest() const { return false; }                                                                                                              \
        virtual uint32 GetRequiredDeviceNum() const override { return 1; }                                                                                               \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                      \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                      \
                                                                                                                                                                         \
    protected:                                                                                                                                                           \
        virtual void GetTests(TArray<FString> &OutBeautifiedNames, TArray<FString> &OutTestCommands) const override                                                      \
        {                                                                                                                                                                \
            OutBeautifiedNames.Add(PrettyName);                                                                                                                          \
            OutTestCommands.Add(FString());                                                                                                                              \
        }                                                                                                                                                                \
        virtual bool RunTest(const FString &Parameters) override;                                                                                                        \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                    \
    };

#define IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, FileName, LineNumber)                                                          \
    class TClass : public TBaseClass                                                                                                                                     \
    {                                                                                                                                                                    \
    public:                                                                                                                                                              \
        TClass(const FString &InName)                                                                                                                                    \
            : TBaseClass(InName, true)                                                                                                                                   \
        {                                                                                                                                                                \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                        \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                     \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                   \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                      \
        }                                                                                                                                                                \
        virtual uint32 GetTestFlags() const override { return ((TFlags) & ~(EAutomationTestFlags::SmokeFilter)); }                                                       \
        virtual bool IsStressTest() const { return true; }                                                                                                               \
        virtual uint32 GetRequiredDeviceNum() const override { return 1; }                                                                                               \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                      \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                      \
                                                                                                                                                                         \
    protected:                                                                                                                                                           \
        virtual void GetTests(TArray<FString> &OutBeautifiedNames, TArray<FString> &OutTestCommands) const override;                                                     \
        virtual bool RunTest(const FString &Parameters) override;                                                                                                        \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                    \
    };

#define IMPLEMENT_NETWORKED_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, NumParticipants, FileName, LineNumber)                                                                 \
    class TClass : public TBaseClass                                                                                                                                                               \
    {                                                                                                                                                                                              \
    public:                                                                                                                                                                                        \
        TClass(const FString &InName)                                                                                                                                                              \
            : TBaseClass(InName, false)                                                                                                                                                            \
        {                                                                                                                                                                                          \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h.");                           \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                                             \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                                            \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                                               \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                                             \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                                             \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                                                \
        }                                                                                                                                                                                          \
        virtual uint32 GetTestFlags() const override { return ((TFlags) & ~(EAutomationTestFlags::EditorContext | EAutomationTestFlags::CommandletContext | EAutomationTestFlags::SmokeFilter)); } \
        virtual uint32 GetRequiredDeviceNum() const override { return NumParticipants; }                                                                                                           \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                                                \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                                                \
                                                                                                                                                                                                   \
    protected:                                                                                                                                                                                     \
        virtual void GetTests(TArray<FString> &OutBeautifiedNames, TArray<FString> &OutTestCommands) const override                                                                                \
        {                                                                                                                                                                                          \
            OutBeautifiedNames.Add(PrettyName);                                                                                                                                                    \
            OutTestCommands.Add(FString());                                                                                                                                                        \
        }                                                                                                                                                                                          \
        virtual bool RunTest(const FString &Parameters) override;                                                                                                                                  \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                                              \
    };

#define IMPLEMENT_BDD_AUTOMATION_TEST_PRIVATE(TClass, PrettyName, TFlags, FileName, LineNumber)                                                                          \
    class TClass : public FBDDAutomationTestBase                                                                                                                         \
    {                                                                                                                                                                    \
    public:                                                                                                                                                              \
        TClass(const FString &InName)                                                                                                                                    \
            : FBDDAutomationTestBase(InName, false)                                                                                                                      \
        {                                                                                                                                                                \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                        \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                     \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                   \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                      \
        }                                                                                                                                                                \
        virtual uint32 GetTestFlags() const override { return TFlags; }                                                                                                  \
        virtual bool IsStressTest() const { return false; }                                                                                                              \
        virtual uint32 GetRequiredDeviceNum() const override { return 1; }                                                                                               \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                      \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                      \
                                                                                                                                                                         \
    protected:                                                                                                                                                           \
        virtual bool RunTest(const FString &Parameters) override;                                                                                                        \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                    \
                                                                                                                                                                         \
    private:                                                                                                                                                             \
        void Define();                                                                                                                                                   \
    };

#define DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, FileName, LineNumber)                                                                                            \
    class TClass : public FAutomationSpecBase                                                                                                                            \
    {                                                                                                                                                                    \
    public:                                                                                                                                                              \
        TClass(const FString &InName)                                                                                                                                    \
            : FAutomationSpecBase(InName, false)                                                                                                                         \
        {                                                                                                                                                                \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                        \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                     \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                   \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                      \
        }                                                                                                                                                                \
        virtual uint32 GetTestFlags() const override { return TFlags; }                                                                                                  \
        using FAutomationSpecBase::GetTestSourceFileName;                                                                                                                \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                      \
        using FAutomationSpecBase::GetTestSourceFileLine;                                                                                                                \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                      \
        virtual FString GetTestSourceFileName(const FString &) const override { return GetTestSourceFileName(); }                                                        \
        virtual int32 GetTestSourceFileLine(const FString &) const override { return GetTestSourceFileLine(); }                                                          \
                                                                                                                                                                         \
    protected:                                                                                                                                                           \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                    \
        virtual void Define() override;                                                                                                                                  \
    };

#define BEGIN_DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, FileName, LineNumber)                                                                                      \
    class TClass : public FAutomationSpecBase                                                                                                                            \
    {                                                                                                                                                                    \
    public:                                                                                                                                                              \
        TClass(const FString &InName)                                                                                                                                    \
            : FAutomationSpecBase(InName, false)                                                                                                                         \
        {                                                                                                                                                                \
            static_assert((TFlags) & EAutomationTestFlags::ApplicationContextMask, "AutomationTest has no application flag.  It shouldn't run.  See AutomationTest.h."); \
            static_assert((((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::SmokeFilter) ||                                                        \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::EngineFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::ProductFilter) ||                                                  \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::PerfFilter) ||                                                     \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::StressFilter) ||                                                   \
                              (((TFlags) & EAutomationTestFlags::FilterMask) == EAutomationTestFlags::NegativeFilter),                                                   \
                          "All AutomationTests must have exactly 1 filter type specified.  See AutomationTest.h.");                                                      \
        }                                                                                                                                                                \
        virtual uint32 GetTestFlags() const override { return TFlags; }                                                                                                  \
        using FAutomationSpecBase::GetTestSourceFileName;                                                                                                                \
        virtual FString GetTestSourceFileName() const override { return FileName; }                                                                                      \
        using FAutomationSpecBase::GetTestSourceFileLine;                                                                                                                \
        virtual int32 GetTestSourceFileLine() const override { return LineNumber; }                                                                                      \
                                                                                                                                                                         \
    protected:                                                                                                                                                           \
        virtual FString GetBeautifiedTestName() const override { return PrettyName; }                                                                                    \
        virtual void Define() override;

#if WITH_AUTOMATION_WORKER
#define IMPLEMENT_SIMPLE_AUTOMATION_TEST(TClass, PrettyName, TFlags)                                              \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                                                                     \
    {                                                                                                             \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                                                     \
    }
    
#define IMPLEMENT_COMPLEX_AUTOMATION_TEST(TClass, PrettyName, TFlags)                                              \
    IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                                                                      \
    {                                                                                                              \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                                                      \
    }
#define IMPLEMENT_COMPLEX_AUTOMATION_CLASS(TClass, PrettyName, TFlags) \
    IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, __FILE__, __LINE__)

#define IMPLEMENT_NETWORKED_AUTOMATION_TEST(TClass, PrettyName, TFlags, NumParticipants)                                              \
    IMPLEMENT_NETWORKED_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, NumParticipants, __FILE__, __LINE__) \
    namespace                                                                                                                         \
    {                                                                                                                                 \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                                                                         \
    }

#define IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TClass, TBaseClass, PrettyName, TFlags)                  \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                                                            \
    {                                                                                                    \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                                            \
    }

#define IMPLEMENT_CUSTOM_COMPLEX_AUTOMATION_TEST(TClass, TBaseClass, PrettyName, TFlags)                  \
    IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                                                             \
    {                                                                                                     \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                                             \
    }

#define IMPLEMENT_BDD_AUTOMATION_TEST(TClass, PrettyName, TFlags)                         \
    IMPLEMENT_BDD_AUTOMATION_TEST_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                                             \
    {                                                                                     \
        TClass TClass##AutomationTestInstance(TEXT(#TClass));                             \
    }

#define DEFINE_SPEC(TClass, PrettyName, TFlags)                         \
    DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__) \
    namespace                                                           \
    {                                                                   \
        TClass TClass##AutomationSpecInstance(TEXT(#TClass));           \
    }

#define BEGIN_DEFINE_SPEC(TClass, PrettyName, TFlags) \
    BEGIN_DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)

#define END_DEFINE_SPEC(TClass)                               \
    }                                                         \
    ;                                                         \
    namespace                                                 \
    {                                                         \
        TClass TClass##AutomationSpecInstance(TEXT(#TClass)); \
    }

//#define BEGIN_CUSTOM_COMPLEX_AUTOMATION_TEST( TClass, TBaseClass, PrettyName, TFlags ) \
	//	BEGIN_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)
//
// #define END_CUSTOM_COMPLEX_AUTOMATION_TEST( TClass ) \
	//	BEGIN_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)
//	namespace\
	//	{\
	//		TClass TClass##AutomationTestInstance( TEXT(#TClass) );\
	//	}

#else
#define IMPLEMENT_SIMPLE_AUTOMATION_TEST(TClass, PrettyName, TFlags) \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, __FILE__, __LINE__)
#define IMPLEMENT_COMPLEX_AUTOMATION_TEST(TClass, PrettyName, TFlags) \
    IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, __FILE__, __LINE__)
#define IMPLEMENT_NETWORKED_AUTOMATION_TEST(TClass, PrettyName, TFlags, NumParticipants) \
    IMPLEMENT_NETWORKED_AUTOMATION_TEST_PRIVATE(TClass, FAutomationTestBase, PrettyName, TFlags, NumParticipants, __FILE__, __LINE__)

#define IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(TClass, TBaseClass, PrettyName, TFlags) \
    IMPLEMENT_SIMPLE_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)
#define IMPLEMENT_CUSTOM_COMPLEX_AUTOMATION_TEST(TClass, TBaseClass, PrettyName, TFlags) \
    IMPLEMENT_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)
#define IMPLEMENT_BDD_AUTOMATION_TEST(TClass, PrettyName, TFlags) \
    IMPLEMENT_BDD_AUTOMATION_TEST_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)
#define DEFINE_SPEC(TClass, PrettyName, TFlags) \
    DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)
#define BEGIN_DEFINE_SPEC(TClass, PrettyName, TFlags) \
    BEGIN_DEFINE_SPEC_PRIVATE(TClass, PrettyName, TFlags, __FILE__, __LINE__)
#define END_DEFINE_SPEC(TClass) \
    }                           \
    ;

//#define BEGIN_CUSTOM_COMPLEX_AUTOMATION_TEST( TClass, TBaseClass, PrettyName, TFlags ) \
	//	BEGIN_CUSTOM_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)

// #define END_CUSTOM_COMPLEX_AUTOMATION_TEST( TClass )
//	END_COMPLEX_AUTOMATION_TEST_PRIVATE(TClass, TBaseClass, PrettyName, TFlags, __FILE__, __LINE__)
#endif // #if WITH_AUTOMATION_WORKER

/**
 *宏，以便使用单行代码轻松测试状态:它们将运行适当的状态
 *测试方法，如果测试失败，则执行`return false;`，该方法(如果放置在
 *主测试用例方法)将立即停止测试。
 *
 *错误日志已经被调用的测试方法处理了。
 *
 *因此，你可以轻松地测试一些东西，如果出错，可能会导致测试崩溃:
 *
 *		bool FMyEasyTest::RunTest(const FString& Parameters)
 *		{
 *			TArray<float> Data = GetSomeData();
 *			int32 Index = GetSomeIndex();
 *			UTEST_TRUE("Check valid index", Index < Data.Num());
 *			float DataItem = Data[Index];   // Won't crash, the test exited on the previous
 *										    // line if index was invalid.
 *			UTEST_TRUE("Check valid item", DataItem > 0.f);
 *		}
 *
 */

#define UTEST_EQUAL(What, Actual, Expected) \
    if (!TestEqual(What, Actual, Expected)) \
    {                                       \
        return false;                       \
    }

#define UTEST_EQUAL_TOLERANCE(What, Actual, Expected, Tolerance) \
    if (!TestEqual(What, Actual, Expected, Tolerance))           \
    {                                                            \
        return false;                                            \
    }

#define UTEST_EQUAL_INSENSITIVE(What, Actual, Expected) \
    if (!TestEqualInsensitive(What, Actual, Expected))  \
    {                                                   \
        return false;                                   \
    }

#define UTEST_NOT_EQUAL(What, Actual, Expected) \
    if (!TestNotEqual(What, Actual, Expected))  \
    {                                           \
        return false;                           \
    }

#define UTEST_SAME(What, Actual, Expected) \
    if (!TestSame(What, Actual, Expected)) \
    {                                      \
        return false;                      \
    }

#define UTEST_NOT_SAME(What, Actual, Expected) \
    if (!TestNotSame(What, Actual, Expected))  \
    {                                          \
        return false;                          \
    }

#define UTEST_TRUE(What, Value) \
    if (!TestTrue(What, Value)) \
    {                           \
        return false;           \
    }

#define UTEST_FALSE(What, Value) \
    if (!TestFalse(What, Value)) \
    {                            \
        return false;            \
    }

#define UTEST_VALID(What, SharedPointer) \
    if (!TestValid(What, SharedPointer)) \
    {                                    \
        return false;                    \
    }

#define UTEST_INVALID(What, SharedPointer) \
    if (!TestInvalid(What, SharedPointer)) \
    {                                      \
        return false;                      \
    }

#define UTEST_NULL(What, Pointer) \
    if (!TestNull(What, Pointer)) \
    {                             \
        return false;             \
    }

#define UTEST_NOT_NULL(What, Pointer) \
    if (!TestNotNull(What, Pointer))  \
    {                                 \
        return false;                 \
    }

//////////////////////////////////////////////////
// 基本的潜命令

/**
 *使用lambda表达式来运行一些代码。如果谓词返回false，潜伏操作将被调用
 *再次下一帧。如果返回true，命令将停止运行。
 */
class FFunctionLatentCommand : public IAutomationLatentCommand
{
};

//
class FDelayedFunctionLatentCommand : public IAutomationLatentCommand
{
};

//
class FUntilCommand : public IAutomationLatentCommand
{
};

// IAutomationLatentCommand的扩展，在尝试之间有延迟
// 如果初始命令不成功。有一个最大的重试次数可以是
// 覆盖。默认是重试10次，间隔1秒。
// 为了防止滥用无限次重试，设置了最大执行次数
// 5分钟的时间这可以被覆盖，但不推荐。只有
// 如果你绝对确定这样做不会导致无限循环，就这么做
class IAutomationLatentCommandWithRetriesAndDelays : public IAutomationLatentCommand
{
};