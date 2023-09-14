虚幻专用多线程

基于线程池的异步任务处理系统,可以利用ue4底层的线程池机制来调度任务

Async - 异步执行的统一接口，需要指定执行方式（EAsyncExecution），并返回一个Future对象
AsyncThread - 创建一个线程来执行
AsyncPool - 在指定的线程池中执行
AsyncTask - TaskGraph中指定线程类型（ENamedThreads）中执行

```
int SimpleAsyncFunc()
{
    AsyncLog("SimpleAsyncFunc .... Begin");
    FPlatformProcess::Sleep(1);
    AsyncLog("SimpleAsyncFunc .... Over");
    return 123;
}

inline void Test_Async1()
{
    // 在TaskGraph中执行一个函数，函数的返回结果放到Future对象
    auto Future = Async(EAsyncExecution::TaskGraph, SimpleAsyncFunc);

    // 干点其他事情
    FPlatformProcess::Sleep(1);
    UE_LOG(LogTemp, Display, TEXT("Do something else .."));

    // 等待SimpleAsyncFunc在TaskGraph中执行完成
    int Value = Future.Get();
    UE_LOG(LogTemp, Display, TEXT("Value = %d"), Value);
}
```

```
inline void Test_Async2()
{
    // 使用全局函数
    Async(EAsyncExecution::Thread, SimpleAsyncFunc);

    // 使用TUniqueFunction
    // TUniqueFunction<int()> Task = SimpleTestFunc;
    TUniqueFunction<int()> Task = []()
    {
        AsyncLog("Lambda1 .... Begin");
        FPlatformProcess::Sleep(1);
        AsyncLog("Lambda1 .... Over");
        return 123;
    };

    Async(EAsyncExecution::Thread, MoveTemp(Task));

    // 使用Labmda函数
    Async(EAsyncExecution::Thread, []()
    {
        AsyncLog("Inline Lambda .... Begin");
        FPlatformProcess::Sleep(1);
        AsyncLog("Inline Lambda .... Over");
    });

    // 带完成回调
    Async(EAsyncExecution::ThreadPool,
          []()
          {
              AsyncLog("Inline Lambda2 .... Begin");
              FPlatformProcess::Sleep(1);
              AsyncLog("Inline Lambda2 .... Over");
          },
          []()
          {
              AsyncLog("Inline Lambda2 .... Completion Callback");
          });

    // 创建一个线程来执行
    AsyncThread([]()
    {
        AsyncLog("AsyncThread Function .... Begin");
        FPlatformProcess::Sleep(1);
        AsyncLog("AsyncThread Function .... Over");
    });

    // 在指定的线程池中执行
    AsyncPool(*GThreadPool, []()
    {
        AsyncLog("AsyncPool Function .... Begin");
        FPlatformProcess::Sleep(1);
        AsyncLog("AsyncPool Function .... Over");
    });

    // TaskGraph中指定线程类型，来执行
    AsyncTask(ENamedThreads::AnyThread, []()
    {
        AsyncLog("AsyncTask Function .... Begin");
        FPlatformProcess::Sleep(1);
        AsyncLog("AsyncTask Function .... Over");
    });
}
```
```
 //AsyncWork.h
        class ExampleAsyncTask : public FNonAbandonableTask
	{
		friend class FAsyncTask<ExampleAsyncTask>;

		int32 ExampleData;

		ExampleAsyncTask(int32 InExampleData)
		 : ExampleData(InExampleData)
		{
		}

		void DoWork()
		{
			... do the work here
		}

		FORCEINLINE TStatId GetStatId() const
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(ExampleAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
		}
	};

	void Example()
	{

		//start an example job

		FAsyncTask<ExampleAsyncTask>* MyTask = new FAsyncTask<ExampleAsyncTask>( 5 );
		MyTask->StartBackgroundTask();

		//--or --

		MyTask->StartSynchronousTask();

		//to just do it now on this thread
		//Check if the task is done :

		if (MyTask->IsDone())
		{
		}

		//Spinning on IsDone is not acceptable( see EnsureCompletion ), but it is ok to check once a frame.
		//Ensure the task is done, doing the task on the current thread if it has not been started, waiting until completion in all cases.

		MyTask->EnsureCompletion();
		delete Task;
	}
```
参考资料:
https://zhuanlan.zhihu.com/p/399838210
https://www.cnblogs.com/shiroe/p/14724496.html
https://zhuanlan.zhihu.com/p/38881269