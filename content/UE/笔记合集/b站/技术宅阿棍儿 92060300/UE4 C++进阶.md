https://www.bilibili.com/video/BV14p4y1a7nj
<details>
<summary>UE4 C++进阶00 单播委托（代理）</summary>
<pre><code>
https://www.bilibili.com/video/BV1KC4y1Y7QN
委托(delegate)是一种泛型但类型安全的方式,可在cpp对象上调用成员函数
可使用委托动态绑定到任意对象的成员函数,之后在该对象上调用函数,即使调用程序不知对象类型也可进行操作
区别
    不用委托
        Invoker
            Object *obj=new Object;
            obj->fun();
        Object
            fun();
    用委托(要求没有返回值)
        Invoker
            Delegate del;
            del.bind(obj,Object::fun);
            del.Execute();
        Delegate
            Object &obj;
            void Object::fun();(要求没有返回值)
        Object
            fun();
本节<单投射>
官方:https://docs.unrealengine.com/4.27/zh-CN/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/
声明的委托类型宏
DECLARE_DELEGATE(FTestDelegate)
DECLARE_DELEGATE_RetVal(int,FTestDelegateRetVal)
DECLARE_DELEGATE_OneParam(FTestDelegateOneParam,int)
-> 使用方法
mothod 1 直接绑定 -> Delegate.BindUObject(UEObject,&UDelefateObject::fun);
method 2 启用lambda -> Delegate.BindLambda([](void){lambda fun});
method 3 原始(脱离ue原有模板类对象)绑定 -> Delegate.BindRaw(RawObjectPtr.Get(),&RawObjectPtr::fun);
method 4 绑定智能指针 -> Delegate.BindSP(RawObjectPtr.ToSharedRef(),&RawObject::fun);
method 5 无对象静态函数 -> Delegate.BindStatic(&RawObject::DelegateStatic);
method 6 以函数名来找到目标方法 -> Delegate.BindUFunction(UEObject"fun"); 注:需要UFUNCTION()前置定义fun
method 7 弱绑定lambda(多一层对象检查) -> Delegate.BindWeakLambda(UEObject,[](void){lambda fun})
</code></pre>
</details>

<details>
<summary>UE4 C++进阶01 【动态】单播委托（代理）</summary>
<pre><code>
https://www.bilibili.com/video/BV1854y1B7Fv
动态委托可序列化(特色),其函数可按命名查找(单播也有),但其执行速度比常规委托慢
声明的委托类型宏
DECLARE_DYNAMIC_DELEGATE_RetVal(bool,FTestDynamicDelegate,bool,Value);
-> 前返回值 后参数 (Value最好与形参定义的参数变量名一致)
TestDynamicDelegate.BindUObject(UEObject,&UDelegateObject::fun);//宏定义,自动生成字符串,按函数名查找
自动支持负载变量
</code></pre>
</details>

<details>
<summary>UE4 C++进阶02 多播委托（代理）和事件</summary>
<pre><code>
https://www.bilibili.com/video/BV1wp4y1Q76h
一对多的调用(限制不能使用返回值)
声明的委托类型宏
DECLARE_MULTICAST_DELEGATE_OneParam(FTestMultiDelegate,bool);//非动态
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestDynamicMultiDelegate,bool,Value);//动态
多播绑定示例:
TestMultiDelegate.AddRaw(RawObjectPtr.Get(),&RawObject::DelegateTest);
TestMultiDelegate.AddSP(RawObjectPtr.ToSharedRef(),&RawObject::DelegateTest);
TestMultiDelegate.AddStatic(&RawObject::DelegateStatic);
TestMultiDelegate.AddUFunction(UEObject,"TestMultiDelegate_Ret_PBool_Payload",200);
TestMultiDelegate.AddWeakLambda(UEObject,
    [FuncName](bool Value){
        UE_LOG(LogTemp,Warning,TEST("%s in Lambda,bool=%u"),*FuncName,Value);
    }
);
调用:
Delegate.Broadcast(true);//多播执行,注意在类内使用
注:绑定的事件与绑定的顺序不一致
</code></pre>
</details>

<details>
<summary>UE4 C++进阶03 虚幻智能指针</summary>
<pre><code>
https://www.bilibili.com/video/BV1Bk4y1z7ZF/
->url:https://docs.unrealengine.com/4.26/zh-CN/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/SmartPointerLibrary/
智能指针的基本用法
防止内存泄漏
弱引用(中断引用循环并阻止悬挂指针)
可选择的线程(线程安全代码,可跨线程管理引用计数)
运行安全(从不为空,可以固定随时取消引用)
授予意图(可以轻松区分对象所有者和观察者)
内存(在64位下仅为c++指针大小两倍,唯一指针除外其与c++指针大小相同)
入侵性访问器:继承 TSharedFromThis
AsShared()和SharedThis(this)会返回相同的类型
</code></pre>
</details>

<details>
<summary>UE4 C++进阶04 异步操作-Tick/异步节点/多输入输出节点</summary>
<pre><code>
https://www.bilibili.com/video/BV19Z4y137Bw
__LINE__打印内容的行号
定义时间轴蓝图节点函数->多端输出节点
</code></pre>
</details>

<details>
<summary>UE4 C++进阶05 异步操作-基于FRunnable类的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1ov411h7ng

<details>
<summary>FRunnable类的基本用法</summary>
<pre><code>
多线程

|compare|Thread|FRunnable|
|-|-|-|
|应用场景|各线程相互独立|各线程协作完成任务、共享资源|
|分析|复杂/局限高|简易,不需要继承类,避免了单继承的局限|

使用方法
(1) 实现Runnable接口
(2) 重写run()方法
(3) 创建runnable实例
(4) 创建Thread实例
(5) 将Runnable实例放入Thread实例中
(6) 通过线程实例控制线程的行为(运行，停止)，在运行时会调用Runnable接口中的run方法。

注意:Java中真正能创建新线程的只有Thread类对象
通过实现Runnable的方式，最终还是通过Thread类对象来创建线程
Runnable方式也分为标准方式和匿名方式

(1)标准方式
```
public class MainActivity extends AppCompatActivity {
    Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btn = findViewById(R.id.btn);
        //2.创建MyRunnable实例
        MyRunnable runnable=new MyRunnable();
        //3.创建Thread对象
        //4.将MyRunnable放入Thread实例中
        Thread thread=new Thread(runnable);
        //5.通过线程对象操作线程(运行、停止)
        thread.start();
    }
    //1.实现runnable接口并重写run方法
    class MyRunnable implements Runnable{
        @Override
        public void run() {
        }
    }
}
```
(2)匿名方式
```
public class MainActivity extends AppCompatActivity {
    Button btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //1.匿名实现Runnable接口并重写run方法
        Runnable runnable = new Runnable() {
            @Override
            public void run() {

            }
        };
        //2.创建线程对象
        //3.将runnable实例放入线程对象中
        Thread thread=new Thread(runnable);
        //4.由线程实例控制线程的行为(运行，停止)
        thread.start();
    }
}
```

参考资料:
https://www.jianshu.com/p/0c9a74ef87ef
https://blog.csdn.net/zhaojianting/article/details/97664370
</code></pre>
</details>

</code></pre>
</details>

<details>
<summary>UE4 C++进阶06 异步操作-基于AsyncTask的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1oX4y137Ed
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
</code></pre>
</details>

<details>
<summary>UE4 C++进阶07 异步操作-基于TaskGraph的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1fh411S7dL
</code></pre>
</details>


