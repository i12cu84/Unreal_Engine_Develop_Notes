虚幻专用多线程(基于线程的并行编程)

解决多线程中任务需要先后执行顺序的问题

```
UCLASS()
class MAKINGUSEOFTASKGRAPH_API AFirstAsyncTask : public AActor
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
        void AsyncLoadTextFile(const FString& FilePath);

    UFUNCTION(BlueprintImplementableEvent)
        void OnFileLoaded(const FString& FileContent);

};
```
建立了一个 Actor 的派生类
提供一个接口，用来发起异步加载的操作：void AsyncLoadTextFile(const FString& FilePath)
提供一个蓝图事件，供上层来接收加载的文件内容：void OnFileLoaded(const FString& FileContent)

```
void AFirstAsyncTask::AsyncLoadTextFile(const FString& FilePath)
{
    FTaskDelegate_FileLoaded TaskDelegate;
    TaskDelegate.BindUFunction(this, "OnFileLoaded");

    TGraphTask<FTask_LoadFileToString>::CreateTask()
                  .ConstructAndDispatchWhenReady(FilePath, TaskDelegate);
}
```
在 AsyncLoadTextFile() 函数中发起一个异步操作；
OnFileLoaded() 将在蓝图中实现，C++这里没有代码；
任务代码是通过自定义的一个class实现的：FTask_LoadFileToString，这个Task的实现代码后面详说；

定义任务
```
class FTask_LoadFileToString
{
    FTaskDelegate_FileLoaded TaskDelegate;
    FString FilePath;

    FString FileContent;
public:
    FTask_LoadFileToString(FString InFilePath, FTaskDelegate_FileLoaded InTaskDelegate) :
        TaskDelegate(InTaskDelegate), FilePath(MoveTemp(InFilePath))
    {}

    FORCEINLINE TStatId GetStatId() const   {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FTask_LoadFileToString, STATGROUP_TaskGraphTasks);
    }

    static ENamedThreads::Type GetDesiredThread() { return CPrio_LoadFileToString.Get(); }
    static ESubsequentsMode::Type GetSubsequentsMode() 
    { return ESubsequentsMode::TrackSubsequents; }

    void DoTask(ENamedThreads::Type CurrentThread, 
         const FGraphEventRef& MyCompletionGraphEvent)    {
        // load file from Content folder
        FString FullPath = FPaths::Combine(FPaths::ProjectContentDir(), FilePath);
        if (FPaths::FileExists(FullPath))
        {
            FFileHelper::LoadFileToString(FileContent, *FullPath);
        }

        // create completion task
        FGraphEventRef ChildTask =
           TGraphTask<FTaskCompletion_LoadFileToString>::CreateTask(nullptr, CurrentThread).
            ConstructAndDispatchWhenReady(TaskDelegate, FileContent);
        MyCompletionGraphEvent->SetGatherThreadForDontCompleteUntil(
              ENamedThreads::GameThread);
        MyCompletionGraphEvent->DontCompleteUntil(ChildTask);
    }
};
```
构造函数是完全自定义的，有多少参数都可以；底层会通过“可变参数模板(Variadic Templates)”把所有参数全都转发过来；
引擎中有一句注释说不支持引用类型的参数：CAUTION!: Must not use references in the constructor args; use pointers instead if you need by reference
不过，我在引擎的代码中发现了有使用引用类型参数的任务，目前还不确定；使用引用类型的话，确实是有很大的“悬空引用(dangling references)”的风险，建议还是不用；
GetStatId()：返回一个 StatId，一般就按照这种固定写法就好了；
GetDesiredThread()：返回这个任务希望运行的线程；常用的写法有：
通过一个 class FAutoConsoleTaskPriority 对象来获得一个当前合适的线程；
指定某个线程，例如：ENamedThreads::GameThread；
GetSubsequentsMode()：有两个可选值，TrackSubsequents 和 FireAndForget ；
DoTask()：这个就是写我们这个任务实际的工作的代码了；

```
class FTaskCompletion_LoadFileToString
{
    FTaskDelegate_FileLoaded TaskDelegate;
    FString FileContent;
public:
    FTaskCompletion_LoadFileToString(FTaskDelegate_FileLoaded InTaskDelegate, 
         FString InFileContent) :
        TaskDelegate(InTaskDelegate), FileContent(MoveTemp(InFileContent))
    {}

    FORCEINLINE TStatId GetStatId() const   {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskCompletion_LoadFileToString, 
        STATGROUP_TaskGraphTasks);
    }

    static ENamedThreads::Type GetDesiredThread() { return ENamedThreads::GameThread; }
    static ESubsequentsMode::Type GetSubsequentsMode() 
    { return ESubsequentsMode::TrackSubsequents; }

    void DoTask(ENamedThreads::Type CurrentThread, 
              const FGraphEventRef& MyCompletionGraphEvent){
        check(IsInGameThread());
        TaskDelegate.ExecuteIfBound(MoveTemp(FileContent));
    }
};
```
通过这个完成通知任务class FTaskCompletion_LoadFileToString来调用AFirstAsyncTask::OnFileLoaded那个蓝图事件的；
FTaskCompletion_LoadFileToString::GetDesiredThread() 返回值为：ENamedThreads::GameThread，也就是要求它在 GameThread 执行！

```
TGraphTask<FTask_LoadFileToString>::CreateTask().
        ConstructAndDispatchWhenReady(FilePath, TaskDelegate);
解释一下上面这一行代码：
```
TGraphTask 是一个模板类，它接收一个类型参数，就是我们前面定义的 “Task 类”
首先是调用 TGraphTask::CreateTask() 函数，这个函数有两个参数：
FGraphEventArray* Prerequisites：前置任务列表，默认值为NULL；这个非常有用，后面我单独；讲
ENamedThreads::Type CurrentThreadIfKnown：当前线程，默认值为ENamedThreads::AnyThread；
这里我直接使用了函数参数的默认值；
TGraphTask::CreateTask() 返回一个对象，它的类型是：class TGraphTask::FConstructor
FConstructor 有两个主要的方法：ConstructAndDispatchWhenReady()、ConstructAndHold()，名字就说明它的作用了
这两个方法主要就是构造我们定义的 “Task 类”的实例，并且使用"可变参数模板(Variadic Templates)"把构造函数的参数转发到 “Task 类的构造函数”