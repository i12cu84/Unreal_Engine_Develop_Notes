
<details>
<summary>UE并发-线程和同步机制</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/393406118
Unreal Engine提供了多种并发机制，从简单的原子操作，到复杂的TaskGraph系统。线程及其同步机制是最基础的，其本身许多内容和C++标准线程库、Pthread等线程库并无二致。本文简单整理下，UE并发中最基础的内容：

线程/线程管理器的结构
线程的常见操作
三种同步机制：原子操作、临界区/读写锁、事件机制。
1.线程



1.1.结构
接口层：

FRunnable - 可在任何一个线程中运行的对象，调用模式：Init() -> Run() -> Exit()。
FRunnableThread - 平台对立的线程对象，创建时根据平台创建相应的子类。
FThreadManager - 线程管理器，所有使用FRunableThread::Create创建的线程，都会添加都该全局管理器。
FSingleThreadRunnable - 提供Tick接口，对于不支持多线程的系统，可以创建FFakeThread，然后通过主线程中调用FThreadManager::Tick来驱动FakeThread运行的Tick操作。
实现层：

FRunnableThreadWin - Windows系统下的线程的实现
FRunnableThreadPThread - pthread的封装，一般Unix/Linux/Mac多线程都是用pthread库实现。
FFakeThread - 不支持多线程的系统，模拟一个“假”线程。
1.2.常用操作
创建线程：使用FRunnableThread::Create创建线程并运行
class FSimpleThread : public FRunnable
{
public:
    FSimpleThread(const FString& TheName) : Name(TheName)
    {
        // 创建平台无关的线程并运行
        RunnableThread = FRunnableThread::Create(this, *Name);
    }
    //....
    FString Name;
    FRunnableThread* RunnableThread = nullptr;
};
线程回调：在创建的线程中运行Init、Run、Exit。
virtual bool Init() override
{
    // 初始化（在该线程中调用）
    return true;
}

virtual uint32 Run() override
{
    // 线程主逻辑
    while (!bStop)
    {
        FPlatformProcess::Sleep(1);
    }
    return 0;
}

virtual void Exit() override
{
    // 线程退出时执行（在该线程中调用）
}
结束线程：跳出Run操作，等待线程结束（RunnableThread->WaitForCompletion）。
// 等待线程结束（WaitForCompletion），线程的Join操作。
virtual void Stop() override
{
    bStop = true;
    if (RunnableThread) 
        RunnableThread->WaitForCompletion();
}
获取当前线程ID和名字
uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
遍历当前所有线程对象
inline void DumpAllThreads(const char* Log)
{
    FThreadManager::Get().ForEachThread(
        [=](uint32 ThreadID, FRunnableThread* Thread)
        {
            UE_LOG(LogTemp, Display, TEXT("%s: %s,%u"), ANSI_TO_TCHAR(Log), *Thread->GetThreadName(), ThreadID);
        });
}
1.3.完整示例
https://github.com/david-pp/UESnippets/blob/main/SnippetAsync/Private/SimpleThread.h
class FSimpleThread : public FRunnable
{
public:
    FSimpleThread(const FString& TheName) : Name(TheName)
    {
        RunnableThread = FRunnableThread::Create(this, *Name);
        Log(__FUNCTION__);
    }

    virtual ~FSimpleThread() override
    {
        if (RunnableThread)
        {
            RunnableThread->WaitForCompletion();
            delete RunnableThread;
            RunnableThread = nullptr;
            Log(__FUNCTION__);
        }
    }

    virtual bool Init() override
    {
        Log(__FUNCTION__);
        return true;
    }

    virtual uint32 Run() override
    {
        while (!bStop)
        {
            FPlatformProcess::Sleep(1);
            Log(__FUNCTION__);
        }
        return 0;
    }

    virtual void Exit() override
    {
        Log(__FUNCTION__);
    }


    virtual void Stop() override
    {
        bStop = true;
        if (RunnableThread)
            RunnableThread->WaitForCompletion();
    }

    void Log(const char* Action)
    {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);

        if (RunnableThread)
        {
            UE_LOG(LogTemp, Display, TEXT("%s@%s[%d] - %s,%d, %s"), *Name, *CurrentThreadName, CurrentThreadId,
                   *RunnableThread->GetThreadName(),
                   RunnableThread->GetThreadID(), ANSI_TO_TCHAR(Action));
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT("%s@%s[%d] - %s,%d, %s"), *Name, *CurrentThreadName, CurrentThreadId,
                   TEXT("NULL"), 0, ANSI_TO_TCHAR(Action));
        }
    }

public:
    FString Name;
    FRunnableThread* RunnableThread = nullptr;
    FThreadSafeBool bStop;
};

#define SAFE_DELETE(Ptr)  if (Ptr) { delete Ptr; Ptr = nullptr; }

inline void DumpAllThreads(const char* Log)
{
    FThreadManager::Get().ForEachThread(
        [=](uint32 ThreadID, FRunnableThread* Thread)
        {
            UE_LOG(LogTemp, Display, TEXT("%s: %s,%u"), ANSI_TO_TCHAR(Log), *Thread->GetThreadName(), ThreadID);
        });
}

inline void Test_SimpleThread()
{
    // Create Threads
    FSimpleThread* SimpleThread1 = new FSimpleThread(TEXT("SimpleThread1"));
    FSimpleThread* SimpleThread2 = new FSimpleThread(TEXT("SimpleThread2"));

    DumpAllThreads(__FUNCTION__);

    // Ticks
    int TickCount = 100;
    for (int i = 0; i < TickCount; ++i)
    {
        // Consume
        UE_LOG(LogTemp, Display, TEXT("Tick[%d] ........ "), i);
        FPlatformProcess::Sleep(0.1);
    }

    // Stop Thread
    SimpleThread1->Stop();
    SimpleThread2->Stop();

    // Destroy Threads
    SAFE_DELETE(SimpleThread1);
    SAFE_DELETE(SimpleThread2);
}
2.同步机制
支持三种类型的同步操作，用于线程之间的同步操作： - 原子操作 - 临界区/读写锁 - 事件

2.1.Atomic
FPlatformAtomics
平台独立的原子操作，编译器和系统级的原子操作封装。

原子操作：TAtomic -> std::atomic
TAtomic，是Unreal使用模板实现的原子操作封装，功能类似std::atomic，随着C++标准对于并发支持的完善，官方建议使用std::atomic。

TAtomic<int> Counter;
Counter ++; // Atomic increment -> FPlatformAtomics::InterlockedIncrement
if (Counter.Load()) // Atomic read -> FPlatformAtomics::AtomicRead
{
}
支持原子操作的计数器：FThreadSafeCounter/FThreadSafeCounter64/FThreadSafeBool
FThreadSafeCounter Counter2;
Counter2.Increment(); // FPlatformAtomics::InterlockedIncrement
Counter2.Decrement(); // FPlatformAtomics::InterlockedDecrement
if (Counter2.GetValue() == 0) // FPlatformAtomics::AtomicRead
{
}
2.2.Locking
互斥锁/临界区：FCriticalSection/FScopeLock
FCriticalSection，Windows下使用临界区实现，Pthread用mutex实现。

class ThreadSafeArray
{
public:
    int32 GetValue(int32 Index)
    {
        FScopeLock Lock(&CS);
        return Values[Index];
    }

    void AppendValue(int32 Value)
    {
        CS.Lock();
        Values.Add(Value);
        CS.Unlock();
    }

private:
    FCriticalSection CS;
    TArray<int32> Values;
};
读写锁：FRWLock/FRWScopeLock
若读操作远高于写操作，建议使用读写锁。

class ThreadSafeArray2
{
public:
    int32 GetValue(int32 Index)
    {
        FRWScopeLock ScopeLock(ValuesLock, SLT_ReadOnly);
        return Values[Index];
    }

    void AppendValue(int32 Value)
    {
        ValuesLock.WriteLock();
        Values.Add(Value);
        ValuesLock.WriteUnlock();
    }

private:
    FRWLock ValuesLock;
    TArray<int32> Values;
};
2.3.Event

FEvent，是可等待事件的接口，用来线程之间事件的等待和触发。

功能类似std::condition_variable
Windows系统下使用CreateEvent创建，pthread使用pthread_cond_create来创建。
作为系统级的资源，为了降低创建和释放的消耗，创建时优先从EventPool中拿出来一个Event对象。
相关类及其用法：

FEvent - 可等待事件接口，支持ManualReset/AutoReset两种模式。
inline void Test_Event()
{
    FEvent* SyncEvent = nullptr;

    Async(EAsyncExecution::Thread, [&SyncEvent]()
    {
        FPlatformProcess::Sleep(3);
        if (SyncEvent)
        {
            // 另外一个线程中触发事件
            SyncEvent->Trigger();
            UE_LOG(LogTemp, Display, TEXT("Trigger ....."));
        }
    });

    // 创建事件对象
    SyncEvent = FPlatformProcess::GetSynchEventFromPool(true);
    // 等待事件触发（infinite wait）
    SyncEvent->Wait((uint32)-1);
    // 释放事件对象
    FPlatformProcess::ReturnSynchEventToPool(SyncEvent);

    UE_LOG(LogTemp, Display, TEXT("Over ....."));
}
FEventRef - 构造时创建一个Event，析构时释放该事件。
inline void Test_Event2()
{
    // 创建事件
    FEventRef SyncEvent(EEventMode::AutoReset);

    FEvent* Event = SyncEvent.operator->();
    Async(EAsyncExecution::Thread, [Event]()
    {
        FPlatformProcess::Sleep(3);
        // 触发事件
        Event->Trigger();
        UE_LOG(LogTemp, Display, TEXT("Trigger ....."));
    });

    // 等待事件
    SyncEvent->Wait((uint32)-1);
    UE_LOG(LogTemp, Display, TEXT("Over ....."));
}
FScopeEvent - 构造时创建一个Event，析构时等待该事件，收到该事件，结束并释放事件资源。
inline void Test_Event()
{
    // waiting..
    {
        // 创建事件并等待
        FScopedEvent SyncEvent;

        Async(EAsyncExecution::Thread, [&SyncEvent]()
        {
            FPlatformProcess::Sleep(3);
            // 触发事件
            SyncEvent.Trigger();
            UE_LOG(LogTemp, Display, TEXT("Trigger ....."));
        });

        // SyncEvent析构时等待，并释放资源
    }

    UE_LOG(LogTemp, Display, TEXT("Over ....."));
}
3.参考源码
HAL（Hardware Abstract Layer），平台抽象层相关实现，跨平台线程、文件系统等操作。比如，线程相关操作位于FPlatformProcess::XXXX、本地线程缓存位于FPlatoformTLS::XXXX等待。

Engine/Source/Runtime/Core/Public/HAL/Runnable.h
Engine/Source/Runtime/Core/Public/HAL/RunnableThread.h
Engine/Source/Runtime/Core/Public/HAL/ThreadManager.h
Engine/Source/Runtime/Core/Public/HAL/Event.h
</code></pre>
</details>

<details>
<summary>UE并发-无锁编程及其在TaskGraph中的应用</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/394791310
在多线程程序中为了保证数据一致性，一般会使用同步机制，比如，使用临界区或Mutex来加锁获取资源，解锁释放资源。用锁不当，会产生死锁（Deadlock）、活锁（Livelock）、饥饿（Starving）等问题，另外在某些对性能要求苛刻的地方，也不是最佳选择。

若把同步机制叫软件锁（Software Lock），那么原子操作可以认为是硬件锁（Hardware Lock）。而基于原子操作实现的无锁数据结构和算法，在这些需要考虑加锁/解锁效率的情况下，值得一用。当然无锁数据结构要精心设计，任何一行代码都要慎重考虑，不光是字面代码，还得考虑编译器优化，内存模型，甚至CPU架构。看一看C++11标准引入的atomic就知道有多复杂了，为了性能也是拼了。

UE中支持了无锁队列（TLockFreePointerListFIFO）和无锁堆栈（TLockFreePointerListFIFO），在TaskGraph中的任务队列就是基于此实现的，作为任务多线程调度的核心模块，性能肯定是至关重要的。更加复杂的LockFree数据结构实现起来非常麻烦，正确性也很难保证。下面主要介绍下：

UE中的无锁队列的用法，超级简单。
无锁编程的关键技术点，若要自己设计一个无锁队列，要考虑哪些技术点？CAS原子操作、ABA问题、内存屏障等。
UE中无锁队列的实现，用起来简单的背后，就没那么简单了。
TaskGraph中无锁队列的使用。
1.UE中的无锁队列用法
无锁堆栈和无锁队列类似，仅以无锁队列为例。和最普通的队列操作类似，用起来非常简单，只不过它是线程安全的，并且对其Push/Pop都是没有加锁的。常用操作：

Push - 添加一个Item进队列
Pop - 弹出一个Item，队列为空则返回空值
PopAll - 弹出所有Item到指定数组
IsEmpty - 队列是否为空
代码示例：

// 自定义对象类
class FMyData
{
public:
    FMyData(const int& V) : Value(V){}
    int Value;
};

// 无锁队列
TLockFreePointerListFIFO<FMyData, PLATFORM_CACHE_LINE_SIZE> ThreadSafeList;

TArray<TFuture<void>> Futures;
const int ThreadNum = 10;

// 创建多个线程
for (int i = 0; i < ThreadNum; ++i)
{
    TFuture<void> Future = Async(EAsyncExecution::Thread, [&ThreadSafeList, i]()
    {
        // 在该线程中进行PUSH操作
        ThreadSafeList.Push(new FMyData(i));
    });

    Futures.Add(MoveTemp(Future));
}

// 等待所有线程结束
while (true)
{
    bool IsAllThreadDone = true;
    for (auto& Future : Futures)
    {
        if (!Future.IsReady())
            IsAllThreadDone = false;
    }

    if (IsAllThreadDone) break;
}

// 在主线程中进行POP操作
while (FMyData* Data = ThreadSafeList.Pop())
{
    int32 ThreadId = FPlatformTLS::GetCurrentThreadId();
    FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
    UE_LOG(LogTemp, Display, TEXT("%s[%d], Dump - %d"), *ThreadName, ThreadId, Data->Value);
    delete Data;
}
2.无锁编程的原理
什么是无锁编程？

准备使用多线程编程
多线程需要访问共享内存
线程之间不用阻塞彼此（使用同步机制）

无锁编程的技术点？

同时存在多个写操作：
需要系统支持原子操作（RMW, Read-Modify-Write），原子操作一般都是CPU指令集级实现。
若你的代码里面有CAS（Compare-And-Swap）循环操作，就得考虑ABA问题。
若是多核心的CPU，需要考虑内存模型，顺序一致的？还是乱序的？这个可以通过内存屏障来解决（Memory Barrier）。



接下来重点了解下，LockFree的几大关键技术点：

CAS原子操作
ABA问题
内存屏障
2.1.CAS原子操作
CAS（Compare-And-Swap）：是原子操作的一种，可用于在多线程编程中实现不被打断的数据交换操作，从而避免多线程同时改写某一数据时由于执行顺序不确定性以及中断的不可预知性产生的数据不一致问题。 该操作通过将内存中的值与指定数据进行比较，当数值一样时将内存中的数据替换为新的值。
伪代码如下：

int compare_and_swap(int* reg, int oldval, int newval){
    ATOMIC();
    int old_reg_val = *reg;      // 取出内存中的值
    if (old_reg_val == oldval)   // 和指定的值进行比较
        *reg = newval;           // 相等则设置为新值
    END_ATOMIC();
    return old_reg_val;          // 返回之前内存中的值 
}
假设要实现一个与指定内存位置的值进行AND操作，对比下非线程安全和线程安全版：

// 非线程安全
void NonAtomicAND(tS32* Value, tS32 Op)
{
    *Value &= Op;
}

// 线程安全（代码中的while循环，是常见的自旋锁模式）
void AtomicAND(volatile tS32* Value, tS32 Op)
{
    while(1)
    {
        // 读取内存中的值
        const tS32 OldValue = *Value;
        // 计算新值
        const tS32 NewValue = OldValue & Op;
 
        // 若内存中的值还是上面拿到的值（说明没被其他线程重入），设置新值并返回，
        // 否则继续循环，重新读内存然后进行操作（说明内存中的值，被其他线程修改了）。
        if(CAS(Value, OldValue, NewValue) == OldValue)
        {
            return;
        }
    }
}
UE中的CAS跨平台接口：

// Dest      - 内存位置
// Exchange  - 要设置的新值
// Comparand  - 进行对比的值
// Return - 设置前内存中的值
int64 FPlatformAtomics::InterlockedCompareExchange(volatile int64* Dest, int64 Exchange, int64 Comparand)
2.2.ABA问题
看到上面那个CAP的while循环，就要条件反射想到ABA问题。所谓ABA问题：

ABA问题是无锁结构实现中常见的一种问题，可基本表述为： > - 线程P1读取了一个数值AP1被挂起(时间片耗尽、中断等) > - 线程P2开始执行P2修改数值A为数值B > - 然后又修改回AP1被唤醒，比较后发现数值A没有变化，程序继续执行。 > - 对于P1来说，数值A未发生过改变，但实际上A已经被变化过了，继续使用可能会出现问题。
在CAS操作中，由于比较的多是指针，这个问题将会变得更加严重。
假设要实现一个简单的无锁堆栈，不考虑ABA，如下（借CMU并行架构和编程课件一用，后面有链接）：

push操作：更新栈顶指针为新结点，通过CAP循环实现原子操作
pop操作：弹出一个元素，更新栈顶指针，通过CAP循环实现原子操作



ABA问题的产生：

Thread0：执行pop操作，设置完局部变量，old_top=A, new_top=B, Thread1重入
Thread1：
执行pop操作
然后push一个D进去
然后又去修改A指向的对象，或者新建了一个对象，它刚好也指向A指针，然后push进去
Thread0：Thread0这个时候重入，CAP操作发现内存中的值（A，其实是Thread1重新push进去的那个A）和old_top相同，然后更新栈顶为new_top（B）。
那么问题来了？D去哪里了？肯定不对了，这就ABA问题！


ABA问题的解决方法：

Pop操作加上一个计数器
更新栈顶和Pop操作计数器，为一个原子操作
这样每次Pop操作时就不再是ABA，而是A1BA2了，这样只要上个Pop没完成，这个Pop就得等待了。



2.3.内存屏障
内存屏障（Memory Barrier）是用来解决内存访问乱序的问题。看一段很简单的代码（但是需要考虑多核和多线程）：

// 假设x、y初始化为0
// Litmus Test: Message Passing
// Can this program see r1 = 1, r2 = 0?
// Thread 1   // Thread 2
x = 1         r1 = y
y = 1         r2 = x
思考下：能否出现： r1 = 1, r2 = 0的情况？

答案是：看情况！这就有点可怕了，写的多线程代码行为不确定！

2.3.1.内存模型的差异
什么情况不出现？

顺序一致性模型下，是不会出现 r1 = 1, r2 = 0的情况，只可能的结果如下（按顺序交替执行）：



顺序一致性的一个很好的思维模型是想象所有处理器直接连接到同一个共享内存，它可以一次处理一个线程的读或写请求。 不涉及缓存，因此每次处理器需要读取或写入内存时，该请求都会转到共享内存。 一次使用一次的共享内存对所有内存访问的执行施加了顺序顺序：顺序一致性。


x86-Total Store Order（x86-TSO）也不会出现（Intel/AMD）

什么情况下可能会出现？

ARM/POWER Relaxed Memory Model时，可能会出现：



在ARM/POWER模型中，我们可以想象线程1和线程2都有各自独立的内存副本，写操作以任何顺序在内存之间传播。如果线程1的内存在发送x的更新(update)之前向线程2发送y的更新，并且如果线程2在这两次更新之间执行，它将确实看到结果r1 = 1，r2 = 0。

更进一步了解，可以参考C++11之后提出的内存模型概念，同时研究下计算机体系结构。

2.3.2.内存乱序
这种不确定主要是因为，开发者编写的代码和最终运行的程序往往会存在较大的差异，而运行结果与开发者预想一致，只是一种“假象”罢了。之所以会产生差异，原因主要来自下面三个方面：

编译器优化
CPU乱序执行（out-of-order）执行
CPU缓存（Cache）不一致性

2.3.3.编译器优化导致的乱序
以gcc为例，该编译器提供了-o参数来控制非常多的优化选项。

以下面这段代码为例：

int A, B;
void foo()
{
    A = B + 1;
    B = 0;
}
在编译优化后，可能会变成下面这样：

int A, B;
void foo()
{
    int temp = B;
    B = 0;
    A = temp + 1;
}
请注意，编译器只要保证：在单线程环境下，执行的结果和原先一样就可以了。所以，这样做是可以的。

对于编译器的乱序优化来说，开发者并非完全不能控制。编译器会提供称之为内存栅栏（Memory Barrier）的工具给开发者，让开发者告诉编译器：这部分代码编译的时候不能乱序。

gcc的内存栅栏写法如下：

int A, B;
void foo()
{
    A = B + 1;
    asm volatile("" ::: "memory");
    B = 0;
}
其他编译器内存屏障的写法：

// C11 / C++11
atomic_signal_fence(memory_order_acq_rel);

// Microsoft Visual C++
_ReadWriteBarrier();

// GCC
__sync_synchronize();
2.3.4.CPU乱序执行
运行时产生的原因上面已经说过了，主要是因为内存模型的差异，导致的Momeory Reorder问题，常见平台的差异：



类似的，处理器也会提供指令给开发者进行避免乱序的控制。例如，x86，x86-64上的fence指令：

// x86, x86-64
lfence (asm), void _mm_lfence(void) // 读操作屏障
sfence (asm), void _mm_sfence(void) // 写操作屏障
mfence (asm), void _mm_mfence(void) // 读写操作屏障
2.3.5.CPU缓存不一致

每个CPU核在运行的时候，都会优先考虑离自己最近的Cache，一旦命中就直接使用Cache中的数据。这是因为Cache相较于主存（RAM）来说要快很多。但是每个核之间的Cache，每一层之间的Cache，数据常常是不一致的。而同步这些数据是需要消耗时间的。

这就会造成一个问题，那就是：某个CPU核修改了一个数据，没有同步的让其他核知道，于是就存在了数据不一致的情况。

2.3.6.UE中的内存屏障
为了跨硬件平台，跨操作系统，可谓煞费苦心。看起来简简单单的代码，背后要考虑的事情太多太多。

// 代码中直接调用
FPlatformMisc::MemoryBarrier();

// Windows下的实现（运行时）
static void FWindowsPlatformMisc::MemoryBarrier() 
{ 
    _mm_sfence(); 
}
// Apple/Linux下的实现（编译期）
static void FApplePlatformMisc::MemoryBarrier()
{
    __sync_synchronize();
}
3.UE中无锁队列的实现
3.1.结构

常用结构：

TLockFreePointerListLIFO - 不考虑内存Prefetch的无锁堆栈
TLockFreePointerListUnordered - 防止内存Prefetch导致的竞争的无锁堆栈。
TLockFreePointerListFIFO - 无锁队列（带防止内存Prefetch导致竞争的机制）
内部实现：

FIndexedPointer - 支持原子操作的节点指针（64位，低26位表示指针索引，其他高位表示计数器或状态），最多支持2^26个节点。
FIndexedLockFreeLink - 节点结构。
FLockFreeLinkPolicy - 封装节点内存管理、隔离节点相关类
FLockFreePointerListLIFORoot - 无锁堆（LIFO）核心实现
FLockFreePointerFIFOBase - 无锁队列（FIFO）核心实现
3.2.Push/Pop的原子性
再次见到CAS Loop，及ABA问题的计数器解决方案，熟悉了原理，一看就明白了：

void FLockFreePointerListLIFORoot::Push(TLinkPtr Item)
{
    while (true)
    {
         // 从内存中拿出Head指针
        TDoublePtr LocalHead;
        LocalHead.AtomicRead(Head);    

        TDoublePtr NewHead;        
        // 更新用于防止ABA问题的计数器
        NewHead.AdvanceCounterAndState(LocalHead, TABAInc);
        // 更新NewHead指向LocalHead
        NewHead.SetPtr(Item); 
        FLockFreeLinkPolicy::DerefLink(Item)->SingleNext = LocalHead.GetPtr();

        // CAS原子判定（指针和计数器，合在一起是uint64，直接用CAS比较）
        // 这样其他线程中的Push/Pop操作没法重入，Pop中的实现类似
        if (Head.InterlockedCompareExchange(NewHead, LocalHead))
        {
            break;
        }
    }
}
同样的CAS循环结构，在LockFreeList.h多次出现，没有一行代码是多余的。

3.3.节点内存分配/释放的原子性
还有一个问题要解决：

创建或析构一个节点FIndexedLockFreeLink（TLink），怎么做？Malloc/Free不是线程安全的。

创建/析构链表节点的原子操作：

struct FLockFreeLinkPolicy
{
    //  分配一个节点对象
    CORE_API static uint32 AllocLockFreeLink();
    // 释放一个节点对象
    CORE_API static void FreeLockFreeLink(uint32 Item);
    // 全局节点分配器
    CORE_API static TAllocator LinkAllocator;
};
为了支持原子的内存分配和释放，LockFree的节点内存分配器包含两部分： - GLockFreeLinkAllocator，每个线程通过TLS关联一堆空闲的节点Bundle。 - FLockFreeLinkPolicy::LinkAllocator：LockFree节点页式分配器。 - 默认在静态空间中初始化了MaxBlocks个Page指针，其中：MaxBlocks = (2^26 + 16384 -1)/16384。 - Alloc操作在堆上按页分配内存，若页中还有空闲节点，直接返回，否则，分配一个完整页，然后返回。 - 通过Page/Subindex来索引节点

内存布局如下：


AllocLockFreeLink调用时：

优先从GlobalFreeListBundle中Pop一个节点对象出来， 若GlobalFreeListBundle为空，继续下一步
若当前线程TLS的PartialBundle指向的位置还有空节点，则返回，并移动PartialBundle指针到下一个空节点
若当前线程TLS的PartialBundle指向的位置没有空节点，则通过FLockFreeLinkPolicy::LinkAllocator分配NUM_PER_BUNDLE（64）个空闲节点，返回一个空节点（该情况如下图所示，图中Bundle节点之间的箭头是 FIndexedLockFreeLink的PayLoad变量，没有对象时指向下一个空闲位置，有对象时代表对象指针）

FreeLockFreeLink调用时：

若当前线程TLS的中的Bundle都是空的，把要释放的对象Push进GlobalFreeListBundle
否则释放当前对象，并把当前线程中空位置（TLS.PartailBundle）指向当前节点位置
3.4.防止Cache Prefetch导致的竞争
在访问指定内存地址时，一般硬件/操作系统会进行Prefetch操作，预先取多个字节：


对于多线程程序来说，若我们关注的数据（比如：Head指针）被其他操作预先读入缓存，当在代码中对Head进行原子操作时，缓存数据应该需要和内存中的数据做一次同步，为了节省掉这个同步操作，应当尽量避免Head变量被Prefetch（再次体会到对性能的极致追求，和计算机体系架构的紧密性了，对性能要求没那么苛刻情况下，不限制也不影响正确性）。

UE中LockFree避免的方法是通过变量前后加上一个Prefetch大小（PLATFORM_CACHE_LINE_SIZE）的变量，以空间换取极致的性能：

FPaddingForCacheContention<TPaddingForCacheContention> PadToAvoidContention1;
TDoublePtr Head;
FPaddingForCacheContention<TPaddingForCacheContention> PadToAvoidContention2;
4.无锁队列在TaskGraph中的应用
4.1.FStallingTaskQueue
FStallingTaskQueue：支持优先级的无锁任务队列。

Push时需要指定任务的优先级
Pop时优先从0-N优先级队列弹出任务，可以指定队列为空时挂起（bAllowStall=true时），直到再次有任务。
来看下TaskGraph中FNamedTaskThread中的相关实现：

// 支持2个优先级的无锁队列，0-优先级，1-低优先级
FStallingTaskQueue<FBaseGraphTask, PLATFORM_CACHE_LINE_SIZE, 2> StallQueue;

// 任务对象，从当前NameTaskThread中入队列
virtual void EnqueueFromThisThread(int32 QueueIndex, FBaseGraphTask* Task) override
{
    // 计算当前Task的优先级：
    // - 高优先级 - 任务包含ENamedThreads::HighTaskPriority标记，此时返回0
    // - 低优先级 - 其他标记（对应的有：ENamedThreads::NormalTaskPriority）
    uint32 PriIndex = ENamedThreads::GetTaskPriority(Task->ThreadToExecuteOn) ? 0 : 1;
    int32 ThreadToStart = Queue(QueueIndex).StallQueue.Push(Task, PriIndex);
    check(ThreadToStart < 0); // if I am stalled, then how can I be queueing a task?
}

// 任务对象，从其他线程中入队
virtual bool EnqueueFromOtherThread(int32 QueueIndex, FBaseGraphTask* Task) override
{
    // 计算优先级
    uint32 PriIndex = ENamedThreads::GetTaskPriority(Task->ThreadToExecuteOn) ? 0 : 1;
    int32 ThreadToStart = Queue(QueueIndex).StallQueue.Push(Task, PriIndex);
    if (ThreadToStart >= 0)
    {
        //  插入任务后，唤醒该NamedThread线程继续执行
        Queue(QueueIndex).StallRestartEvent->Trigger();
        return true;
    }
    return false;
}

// 该NamedThread的Run
uint64 ProcessTasksNamedThread(int32 QueueIndex, bool bAllowStall)
{
    // .....
    while (!Queue(QueueIndex).QuitForReturn) {
       // 从优先级队列中弹出一个任务
       FBaseGraphTask* Task = Queue(QueueIndex).StallQueue.Pop(0, bStallQueueAllowStall);
       if (!Task) {
             // ...
       } else {
             Task->Execute();
       }
    }
}
4.2.TClosableLockFreePointerListUnorderedSingleConsumer
TClosableLockFreePointerListUnorderedSingleConsumer，好长的类名，不过通过名字大概能猜到作用：

可关闭的（Close标记）
无锁队列，带防止内存Prefetch竞争
支持单消费者线程 - 继承自FLockFreePointerListLIFOBase
在FGraphEvent中用来表示任务的后续任务列表：

// 后续任务列表
TClosableLockFreePointerListUnorderedSingleConsumer<FBaseGraphTask, 0>     SubsequentList;

// 添加一个后续任务：无锁队列没有关闭的话，Push进去，否则返回false
bool AddSubsequent(class FBaseGraphTask* Task)
{
    return SubsequentList.PushIfNotClosed(Task);
}

// 无锁队列已关闭，则表示后续任务已完成 
bool IsComplete() const
{
    return SubsequentList.IsClosed();
}

// 开始执行后续任务
void FGraphEvent::DispatchSubsequents(TArray<FBaseGraphTask*>& NewTasks)
{
    // ...
    // 把所有任务Pop出来，并设置该队列为Closed状态
    SubsequentList.PopAllAndClose(NewTasks);

    // reverse the order since PopAll is implicitly backwards
    for (int32 Index = NewTasks.Num() - 1; Index >= 0 ; Index--) 
    {
        FBaseGraphTask* NewTask = NewTasks[Index];
        checkThreadGraph(NewTask);
        NewTask->ConditionalQueueTask(CurrentThreadIfKnown);
    }
    NewTasks.Reset();
}
5.小结
要想写好多线程代码，难吗？挺难的，有篇300多页的文章回答这个问题（Is Parallel Programming Hard, And, If So, What Can You Do About It?）。从计算机体系结构说起，到内存模型，同步机制，再到并发数据结构的设计，实在是没法再展开了（相关资源，见参考资料中的链接）。

用UE多线程/Async/TaskGraph做并发编程，难吗？代码很简洁，简洁的背后是复杂的设计和考量，好在UnrealEngine已帮你封装好了。

切记：写多线程代码时，一定要明确知道你的每一行代码在那个线程中执行的！

6.参考资料
An Introduction to Lock-Free Programming ：
https://preshing.com/20120612/an-introduction-to-lock-free-programming/
Parallel Computer Architecture and Programming
http://15418.courses.cs.cmu.edu/spring2017/lectures
Is Parallel Programming Hard, And, If So, What Can You Do About It?：
https://mirrors.edge.kernel.org/pub/linux/kernel/people/paulmck/perfbook/perfbook.2011.01.02a.pdf
Hardware Memory Models：
https://research.swtch.com/hwmm.pdf
https://research.swtch.com/plmm.pdf
C++内存模型：
https://paul.pub/cpp-memory-model/
UE Source Code：
Engine/Source/Runtime/Core/Public/Containers/LockFreeList.h
</code></pre>
</details>

<details>
<summary>UE并发-生产者消费者模式</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/396037238
</code></pre>
</details>

<details>
<summary>UE并发-线程池和AsyncTask</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/396824188
</code></pre>
</details>

<details>
<summary>UE并发-TaskGraph的实现和用法</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/398843895
</code></pre>
</details>

<details>
<summary>UE并发-Async & Future & Promise</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/399838210
</code></pre>
</details>