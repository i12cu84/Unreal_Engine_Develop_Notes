
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
0.Overview
生产者消费者模型，在并发编程中经常会用到，Unreal Engine中也封装了相应的无锁数据结构：

TQueue - 一个无锁的不限制大小的队列，支持SPSC（单生产者单消费者）/MPSC（多生产者单消费者）两种模式。
TCircularQueue - 一个无锁环形队列，SPSC（单生产者单消费者）模式下线程安全。
TTripleBuffer - 一个无锁的三缓存实现，SPSC（单生产者单消费者）模式下线程安全（UE源码中没有用到，所以本文不涉及其用法，不过其思路在物理模块中有用到）。
另外，针对MPMC/SPMC（多消费者）模式，需要自行实现，示例代码中做了简单实现，供参考。本文主要包含：

生产者消费者模型及其模式
UE中TQueue和TCircularQueue的实现和用法
一个双缓冲的简单实现，双缓冲主要用来优化队列读写锁定的开销，在服务器中一般用于IO线程和逻辑线程之间做数据交换。
一个MPMC模式的简实现，用到锁和事件。
1.生产者消费者模式
生产者消费者问题（Producer-consumer problem），也称有限缓冲问题（Bounded-buffer problem），是一个多进程同步问题的经典案例。该问题描述了共享固定大小缓冲区的两个进程——即所谓的“生产者”和“消费者”——在实际运行时会发生的问题。生产者的主要作用是生成一定量的数据放到缓冲区中，然后重复此过程。与此同时，消费者也在缓冲区消耗这些数据。该问题的关键就是要保证生产者不会在缓冲区满时加入数据，消费者也不会在缓冲区中空时消耗数据。

一般根据生产者和消费者的数量，进行组合，可以分为下面几种，针对不同的情况，会有对应的优化策略：

SPSC（Single Producer & Single Consumer），对于单生产者单消费者，只有同步没用互斥，只用保证缓冲区满的时候，生产者不会继续向缓冲区放数据，缓冲区空的时候，消费者不会继续从缓冲区取数据，而不存在同时有两个生产者使用缓冲区资源，造成数据不一致的状态。
MPSC（Multiple Producer & Simple Consumer），对于多生产者单消费者来说，多生产者之间具有互斥关系，需要加锁。
SPMC（Single Producer & Multiple Consumer），类似MPMC模式。
MPMC（Multiple Producer & Multiple Consumer），对于多生产者多消费者问题，是一个同步+互斥问题，不仅需要生产者和消费者之间的同步协作，还需要实现对缓冲区资源的互斥访问。
2.UE中的并发数据结构
2.1.TQueue
TQueue实现了一个不限制大小的LockFree链表，节点数据以值形式存储。该数据结构可以用于两种模式：

EQueueMode::Spsc，单生产者单消费者模式。
EQueueMode::Mpsc，多生产者单消费者模式。
两种模式下都是线程安全的：

在消费者线程中调用的Dequeue方法只操作Tail，不存在竞争
在生产者线程中调用的Enqueue方法，在SPSC模式下，操作Head，不存在竞争（保证内存访问顺序一致即可，使用了Memory Barrier）；在MPSC模式，多个生产者对Head的访问，通过原子操作CAS实现。

实现代码片段：

bool Enqueue(const ItemType& Item)
{
        TNode* NewNode = new TNode(Item);
        if (NewNode == nullptr)
        {
            return false;
        }
        TNode* OldHead;
        if (Mode == EQueueMode::Mpsc)
        {
            // CAS原子操作，设置节点指针和NextNode指针
            OldHead = (TNode*)FPlatformAtomics::InterlockedExchangePtr((void**)&Head, NewNode);
            TSAN_BEFORE(&OldHead->NextNode);
            FPlatformAtomics::InterlockedExchangePtr((void**)&OldHead->NextNode, NewNode);
        }
        else
        {
            OldHead = Head;
            Head = NewNode;
            TSAN_BEFORE(&OldHead->NextNode);
            FPlatformMisc::MemoryBarrier(); // 保证内存访问顺序一致
            OldHead->NextNode = NewNode;
        }
        return true;
 }
用法代码片段：

// 自定义数据
struct FMyItem
{
    FMyItem(uint32 TheId = 0, const FString& TheName = TEXT("Item"))
        : Id(TheId), Name(TheName)
    {
    }
    uint32 Id;
    FString Name;
};

// SPSC队列
TQueue<FMyItem, EQueueMode::Spsc> ItemsQueue;

void Test_Queue()
{
    // Single Producer
    Async(EAsyncExecution::Thread, []()
    {
        for (uint32 Id = 1; ; Id++)
        {
            // 生产一个对象
            ItemsQueue.Enqueue(FMyItem(Id, "Item"));
            UE_LOG(LogTemp, Display, TEXT("Produce: %d,%s"), Id, TEXT("Item"));
        }
    });
    // Single Consumer
    Async(EAsyncExecution::Thread, []()
    {
        while (true)
        {
            if (!ItemsQueue.IsEmpty())
            {
                // 消费一个对象
                FMyItem Item;
                ItemsQueue.Dequeue(Item);
                UE_LOG(LogTemp, Display, TEXT("Consume: %d,%s"), Item.Id, *Item.Name);
            }
        }
    });
}
2.2.TCircularQueue/TCircularBuffer
TCircularQueue，一个基于环形数组实现的LockFree的FIFO的队列，只能用于SPSC模式下：

Enqueue，在队尾（Tail）添加一个对象，成功返回true；若队列已满（Capacity-1个元素）返回false，添加失败。
Dequeue，从队列的前面（Head）移除一个元素，成功返回true；若队列已经没有元素了，返回false。

用法代码片段：

template<uint32 Num>
void TestTCircularQueue()
{
    // 环形队列
    TCircularQueue<uint32> Queue{ 100 };
    std::atomic<bool> bStop{ false };
    // 一个生产者（TaskGraph线程）
    FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady(
        [&bStop, &Queue]
        {
            while (!bStop)
            {
                Queue.Enqueue(0);
            }
        }
        );
    // 消费者（当前线程）
    uint32 It = 0;
    while (It != Num)
    {
        uint32 El;
        if (Queue.Dequeue(El))
        {
            ++It;
        }
    }
    bStop = true;
    // 等待任务结束
    Task->Wait(ENamedThreads::GameThread);
}

// 运行示例
TestTCircularQueue<10'000'000>();
3.MPMC的简单实现
对于多生产者多消费者问题，是一个同步+互斥问题，不仅需要生产者和消费者之间的同步协作，还需要实现对缓冲区资源的互斥访问。

简单实现如下：

template <typename ItemType, int QueueSize>
class TQueueMPMC
{
public:
    TQueueMPMC()
    {
        ItemsCount = 0;
        Items.Reserve(QueueSize);
    }
    void Enqueue(const ItemType& Item)
    {
        // 队列以满，则阻塞于此
        if (ItemsCount == QueueSize)
        {
            UE_LOG(LogTemp, Display, TEXT("Enque-Waiting...."));
            FullEvent->Wait();
        }

        // 插入数据
        ItemsMutex.Lock();
        Items.Push(Item);
        ItemsCount = Items.Num();
        ItemsMutex.Unlock();

        // 通知Consumer有数据了
        if (ItemsCount >= 1)
        {
            EmptyEvent->Trigger();
        }
    }
    ItemType Dequeue()
    {
        // 若队列为空，阻塞于此，直到有数据
        if (ItemsCount == 0)
        {
            UE_LOG(LogTemp, Display, TEXT("Dequeue-Waiting...."));
            EmptyEvent->Wait();
        }

        // 弹出数据
        ItemType Item;
        ItemsMutex.Lock();
        if (Items.Num() > 0) Item = Items.Pop();
        ItemsCount = Items.Num();
        ItemsMutex.Unlock();

        // 通知生产者有空间了
        if (ItemsCount == (QueueSize - 1))
            FullEvent->Trigger();
        return Item;
    }
private:
    FEventRef FullEvent;      // 满队列事件/条件变量
    FEventRef EmptyEvent;     // 空队列事件/条件变量

    TAtomic<int> ItemsCount;   
    FCriticalSection ItemsMutex; // Buffer Mutex
    TArray<ItemType> Items;     // Single Buffer
};
测试代码如下：

struct MPMCTest
{
    // 支持多生产者多消费者模式的队列
    static TQueueMPMC<int, 10> QueueMPMC;

    // 生产者
    static void Producer(int ItemID = 0)
    {
        int Item = ItemID;
        while (true)
        {
            // 生产一个对象
            Item++;
            // 放入队列，若队列已满，等待被消费
            QueueMPMC.Enqueue(Item);
        }
    }

    // 消费者
    static void Consumer()
    {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
        while (true)
        {
            // 拿出一个对象，若队列为空，等待生产者
            int Item = QueueMPMC.Dequeue();
            // 消费对象
            UE_LOG(LogTemp, Display, TEXT("Consumer@%s, Item=%d"), *CurrentThreadName, Item);
        }
    }
};

TQueueMPMC<int, 10> MPMCTest::QueueMPMC;

void Test_MPMC()
{
    const int NumProducer = 5;
    const int NumConsumer = 3;

    // Multiple Producer
    for (int i = 0; i < NumProducer; ++i)
    {
        Async(EAsyncExecution::Thread, [i]()
        {
            MPMCTest::Producer(i * 1000000);
        });
    }

    // Multiple Consumer
    for (int i = 0; i < NumConsumer; ++i)
    {
        Async(EAsyncExecution::Thread, &MPMCTest::Consumer);
    }
}
4.双缓冲技术
在服务器开发中 通常的做法是把逻辑处理线程和IO处理线程分离。 I/0处理线程负责网络数据的发送和接收，连接的建立和维护。 逻辑处理线程处理从IO线程接收到的包。

通常逻辑处理线程和IO处理线程是通过数据队列来交换数据，就是生产者--消费者模型。这个数据队列是多个线程在共享，每次访问都需要加锁，因此如何减少互斥/同步的开销就显得尤为重要。可以通过双缓冲队列来优化这种场景。
所谓双缓冲数据就是两个队列：

一个负责从里写入数据
一个负责读取数据。
当逻辑线程读完数据后负责将自己的队列和IO线程的队列进行交换。这种操作需要在两个地方加锁：

IO线程向队列写入数据。
两个队列进行交换时。
简单实现如下：

template <typename ItemType>
class TDoubleBuffer
{
public:
    TDoubleBuffer(uint32 Capacity = (uint32)-1)
        : MaxCapacity(Capacity)
    {
        WriteBuffer = new TArray<ItemType>();
        ReadBuffer = new TArray<ItemType>();
    }
    ~TDoubleBuffer()
    {
        delete WriteBuffer;
        delete ReadBuffer;
    }
    // 生产者调用
    bool Enqueue(const ItemType& Item)
    { 
        // 写入时加锁
        FScopeLock Lock(&SwapMutex);
        if ((uint32)WriteBuffer->Num() > MaxCapacity)
            return false;
        WriteBuffer->Push(Item);
        return true;
    }

    // 消费者调用
    bool Dequeue(ItemType& Item)
    {
        if (ReadBuffer->Num() == 0)
        {
            // 交换时加锁
            FScopeLock Lock(&SwapMutex);
            Swap(WriteBuffer, ReadBuffer);
            if (ReadBuffer->Num() == 0)
                return false;
        }
        if (ReadBuffer->Num() > 0)
        {
            Item = ReadBuffer->Pop();
            return true;
        }
        return false;
    }
private:
    uint32 MaxCapacity;
    FCriticalSection SwapMutex;    // 交换操作锁
    TArray<ItemType>* WriteBuffer; // 写Buffer
    TArray<ItemType>* ReadBuffer;  // 读Buffer
};
测试代码如下：

void Test_DoubleBuffer()
{
    TDoubleBuffer<uint32> DoubleBuffer;
    std::atomic<bool> bStop{false};

    // 生产者线程
    auto IOThread = Async(EAsyncExecution::Thread, [&bStop, &DoubleBuffer]()
    {
        FRandomStream Rand;
        Rand.GenerateNewSeed();
        while (!bStop)
        {
            // 生产一个对象
            DoubleBuffer.Enqueue(Rand.GetUnsignedInt());
        }
    });

    // 消费者线程
    const uint32 MaxConsuming = 100000;
    for (uint32 i = 0; i < MaxConsuming;)
    {
        uint32 Item;
        if (DoubleBuffer.Dequeue(Item))
        {
            ++i;
            UE_LOG(LogTemp, Display, TEXT("Consumer %u, Item=%u"), i, Item);
        }
    }
    bStop = true;
    IOThread.Wait();
    
    UE_LOG(LogTemp, Display, TEXT("OVer...."));
}
5.参考资料
https://en.wikipedia.org/wiki/Producer%E2%80%93consumer_problem
Engine/Source/Runtime/Core/Public/Containers/Queue.h
Engine/Source/Runtime/Core/Public/Containers/CircularQueue.h
Engine/Source/Runtime/Core/Public/Containers/TripleBuffer.h
Engine/Source/Runtime/Experimental/Chaos/Public/Framework/TripleBufferedData.h
</code></pre>
</details>

<details>
<summary>UE并发-线程池和AsyncTask</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/396824188
为了更高效地利用线程，而不是每个任务都创建一个线程，UE中提供了线程池的方案，可以将多个任务分配在N个线程中执行。任务过多时，排队执行，也可以撤销排队。本文简单介绍下：

线程池FQueuedThreadPool的实现。
使用IQueuedWork自定义一个简单任务类，并放入线程池中执行。
引擎全局的几个线程池：GThreadPool、GIOThreadPool、GBackgroundPriortyThreadPool、GLargeThreadPool。
AyncTask的用法。
1.线程池的实现
结构：


接口层：

IQueuedWork - 任务接口，继承使用。
FQueuedThreadPool - 线程池的接口类，常用操作：
AddQueuedWork - 把任务放入线程池中执行，若有空闲线程，直接分配给空闲线程，若没有空闲线程，放入线程池维护的队列，后台线程会从队列中自己拿任务执行。
RetractQueuedWork - 撤回指定任务，只能撤回正在排队的，已经在执行的没法撤回。
实现层：

FQueuedThreadPoolBase - 线程池的实现类
QueueWork - 排队的任务
QueuedThreads - 空闲的线程
AllThreads - 所有线程（FQueueThread）
FQueuedThread - 线程池的后台线程实现
线程运行时，若没有任务则挂起，有任务时执行任务，执行完一个任务后，从线程池队列中再拿一个执行（FQueuedThreadPoolBase::ReturnToPoolOrGetNextJob），直到没有任务，再次挂起自己
若目前线程为空闲，放入一个任务后，执行该线程的DoWork，结束挂起开始执行任务
运行示意图：


2.线程池的用法
定义可以放入线程池执行的Worker类，需要重载：
DoThreadedWork - 在线程池中的某个线程中执行
Abandon - 线程池释放自己时（Destroy），放弃排队的任务时会调用该函数。
class FSimpleQueuedWorker : public IQueuedWork
{
public:
    FSimpleQueuedWorker(const FString& Name) : WorkerName(Name) {
        Log(__FUNCTION__);
    }

    virtual ~FSimpleQueuedWorker() override {
        Log(__FUNCTION__);
    }

    // 在线程池中的某个线程中执行
    virtual void DoThreadedWork() override {
        FPlatformProcess::Sleep(0.2);
        Log(__FUNCTION__);
        // 任务结束，释放创建的Worker对象，也可以交给调用者析构
        delete this;
    }

    // 放弃该任务的执行
    virtual void Abandon() override {
        Log(__FUNCTION__);
        // 任务被放弃，释放创建的Worker对象，也可以交给调用者析构
        delete this;
    }

    void Log(const char* Action) {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
        UE_LOG(LogTemp, Display, TEXT("%s@%s[%d] - %s"),
               *WorkerName, *CurrentThreadName, CurrentThreadId, ANSI_TO_TCHAR(Action));
    }

public:
    FString WorkerName;
};
创建一个线程池，并执行一批任务：
FQueuedThreadPool::Allocate - 在堆中分配一个线程池对象
FQueuedThreadPool::Create - 创建线程池，可以指定线程的数量、堆栈大小、线程的优先级。
inline void Test_SimpleQueuedWorker()
{
    // 创建线程池，有5个线程
    FQueuedThreadPool* CreatePool = FQueuedThreadPool::Allocate();
    Pool->Create(5, 0, TPri_Normal, TEXT("SimpleThreadPool"));

    int WokerNum = 100;
    for (int i = 0; i < WokerNum; ++i)
    {
        FString Name = TEXT("Worker") + FString::FromInt(i);

        // 创建Worker对象并交给线程池执行
        Pool->AddQueuedWork(new FSimpleQueuedWorker(Name));
    }

    // 等待部分任务完成
    int TickCount = 20;
    for (int i = 0; i < TickCount; ++i)
    {
        // Consume
        UE_LOG(LogTemp, Display, TEXT("Tick[%d] ........ "), i);
        FPlatformProcess::Sleep(0.1);
    }

    // 线程池释放，没有完成的任务会被放弃（Abandon）
    Pool->Destroy();
    delete Pool;
}
3.引擎中的全局线程池
获取线程数量的几个操作：

FPlatformMisc::NumberOfWorkerThreadsToSpawn() -> CPU核心数-2
FPlatformMisc::NumberOfIOWorkerThreadsToSpawn() -> 4
全局定义了四个线程池，分别如下（调试时，线程名为：PoolThread X）：

GThreadPool : 最常用的全局线程池，FAsyncTask默认使用。
Client: NumberOfWorkerThreadsToSpawn
Server: 1
GBackgroundPriorityThreadPool : 低优先级线程池
Client: 2
Server: 1
GLargeThreadPool：Editor模式下用的线程池
Client：Max(NumberOfCoresIncludingHyperthreads() - 2, 2)
GIOThreadPool：IO操作的线程池
Client：NumberOfIOWorkerThreadsToSpawn
Server：2
GThreadPool初始化代码如下，其他类似：

// FEngineLoop::PreInitPreStartupScreen
GThreadPool = FQueuedThreadPool::Allocate();
int32 NumThreadsInThreadPool = FPlatformMisc::NumberOfWorkerThreadsToSpawn();
// we are only going to give dedicated servers one pool thread
if (FPlatformProperties::IsServerOnly()){
     NumThreadsInThreadPool = 1;
}
verify(GThreadPool->Create(NumThreadsInThreadPool, StackSize * 1024, TPri_SlightlyBelowNormal, TEXT("ThreadPool")));
4.AsyncTask的使用
上面继承自IQueuedWork的任务类，对应的任务对象只能在线程池后台线程中运行。现在需要一种能力，同一个类型的任务，可以指定它在线程中异步执行，也可以指定它在当前调用线程中执行。

FAsyncTask/FAutoDeleteAsyncTask模板类提供了这样的作用，它们继承自IQueduedTask，对于调试和任务调度提供了一定的灵活性，代码也更简洁。

4.1.定义一个可以异步/同步执行的任务
该任务类，必须实现下面两个接口：

DoWork - 执行任务
GetStatId - 性能统计
示例代码：

class SimpleExampleTask : public FNonAbandonableTask
{
    friend class FAsyncTask<SimpleExampleTask>;

    int32 ExampleData;
    float WorkingTime;

public:
    SimpleExampleTask(int32 InExampleData, float TheWorkingTime = 1)
        : ExampleData(InExampleData), WorkingTime(TheWorkingTime) { }

    ~SimpleExampleTask() {
        Log(__FUNCTION__);
    }

    // 执行任务（必须实现）
    void DoWork() {
        // do the work...
        FPlatformProcess::Sleep(WorkingTime);
        Log(__FUNCTION__);
    }

    // 用时统计对应的ID（必须实现）
    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(ExampleAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
    }

    void Log(const char* Action)
    {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
        UE_LOG(LogTemp, Display, TEXT("%s[%d] - %s, ExampleData=%d"), *CurrentThreadName, CurrentThreadId,
               ANSI_TO_TCHAR(Action), ExampleData);
    }
};
4.2.FAutoDeleteAsyncTask的用法
自动删除的任务，调用者不用管，任务结束或被放弃时，都会自动析构。示例：

inline void Test_SimpleTask_1()
{
    // 在指定线程池中执行，默认在：GThreadPool
    (new FAutoDeleteAsyncTask<SimpleExampleTask>(1000))->StartBackgroundTask();

    // 在当前线程中执行
    (new FAutoDeleteAsyncTask<SimpleExampleTask>(2000))->StartSynchronousTask();
}
4.3.FAsyncTask的用法
任务的生命周期由调用者负责，可以在调用线程中：

IsDone - 判定任务是否完成。
WaitCompletionWithTimeout - 在指定的范围内等待任务完成，
EnsureCompletion - 确保任务完成，若还在排队，直接撤销，在当前线程中执行。一般该操作用于任务收尾。
Cancel - 取消任务，只能取消正在排队的。
示例1:

inline void Test_SimpleTask_2(bool bForceOnThisThread)
{
    // 创建一个任务
    FAsyncTask<SimpleExampleTask>* MyTask = new FAsyncTask<SimpleExampleTask>(1000);

    // 同步/异步执行该任务
    if (bForceOnThisThread)
        MyTask->StartSynchronousTask();
    else
        MyTask->StartBackgroundTask();

    // 检查是否结束？（可以用于一些帧内判定，不适合自旋式检查）
    bool IsDone = MyTask->IsDone();
    UE_LOG(LogTemp, Display, TEXT("Is Done : %d"), IsDone);

    // 保证任务被执行
    //  - 若该任务在线程池中排队，则拿出来在该线程中执行
    //  - 若该任务在线程池执行，则等待直到它完成
    MyTask->EnsureCompletion();
    delete MyTask;
}
示例2：

inline void Test_SimpleTask_3()
{
    using FSimpleExampleAsyncTask = FAsyncTask<SimpleExampleTask>;

    int TaskCount = 20;
    TArray<FSimpleExampleAsyncTask*> Tasks;

    // 创建一批任务，并异步在GPoolThread中执行
    for (int i = 0; i < TaskCount; ++i)
    {
        FSimpleExampleAsyncTask* MyTask = new FSimpleExampleAsyncTask(i + 1, 3);
        if (MyTask)
        {
            MyTask->StartBackgroundTask();
            Tasks.Add(MyTask);
        }
    }

    // 等待线程池中的任务执行
    FPlatformProcess::Sleep(5);

    // 运行一段时间，检查任务的状态
    TArray<FSimpleExampleAsyncTask*> RemainTasks;
    for (auto Task : Tasks)
    {
        if (Task->IsDone())  // 完成，则删除任务
        {
            UE_LOG(LogTemp, Display, TEXT("Done ......"));
            delete Task;
        }
        else
        {
            if (Task->Cancel())  // 没完成，尝试取消任务，并删除
            {
                UE_LOG(LogTemp, Display, TEXT("Cancel ........"));
                delete Task;
            }
            else // 正在运行的任务是没法取消的
            {
                UE_LOG(LogTemp, Display, TEXT("Still Working ....."));
                RemainTasks.Add(Task);
            }
        }
    }
    Tasks.Reset();

    // 等待任务完成
    for (auto Task : RemainTasks)
    {
        UE_LOG(LogTemp, Display, TEXT("EnsureCompletion ..."));
        Task->EnsureCompletion();
        delete Task;
    }

    UE_LOG(LogTemp, Display, TEXT("Over .............."));
}
5.参考资料
代码示例：

线程池： https://github.com/david-pp/UESnippets/blob/main/SnippetAsync/Private/SimpleQueuedWorker.h
AysncTask： https://github.com/david-pp/UESnippets/blob/main/SnippetAsync/Private/SimpleQueuedWorker.h
UE源码：

Engine/Source/Runtime/Core/Public/Misc/QueuedThreadPool.h
Engine/Source/Runtime/Core/Public/Misc/IQueuedWork.h
Engine/Source/Runtime/Core/Public/Async/AsyncWork.h
</code></pre>
</details>

<details>
<summary>UE并发-TaskGraph的实现和用法</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/398843895
TaskGraph是UE中基于任务的并发机制。可以创建任务在指定类型的线程中执行，同时提供了等待机制，其强大之处在于可以调度一系列有依赖关系的任务，这些任务组成了一个有向无环的任务网络（DAG），并且任务的执行可以分布在不同的线程中。


TaskGraph支持两种类型的线程：

一种是由TaskGraph系统后台创建的线程，称之为AnyThread。
另一种是外部线程，包括系统线程（比如：主线程）或者其他基于FRunnableThread创建的线程，初始化的时候需要Attach到TaskGraph系统，此类线程成为NamedThread。
1.TaskGraph简介
1.1.AnyThread
AnyThread是由TaskGraph系统创建的后台线程，会持续地从相应优先级队列中拿任务执行，线程的个数由当前运行的系统及CPU核心数决定的。对于AnyThread，有优先级和线程集合的概念。

线程优先级（Thread Priority）：

对于AnyThread，TaskGraph系统在初始化时，会根据需要创建多个优先级的线程（线程名 - 描述，线程类型标记，系统线程优先级）：

TaskGraphThreadNP X - 正常优先级，NormalThreadPriority，TPri_BelowNormal
TaskGraphThreadHP X - 高优先级，HighThreadPriority，TPri_SlightlyBelowNormal
TaskGraphThreadBP X - 低优先级，BackgroundThreadPriority， TPri_Lowest
线程集（Thread Set）：

一组多个优先级的线程，称为为ThreadSet
至少1个，最多3个（由CREATE_HIPRI_TASK_THREADS和CREATE_BACKGROUND_TASK_THREADS决定是否创建高/低优先级线程）
1.2.NamedThread
NamedThread是外部创建的线程，该类型初始化时，可以通过Attach操作，设置TLS指向相应的Worker对象：

// 绑定主线程（GameThread）
FTaskGraphInterface::Get().AttachToThread(ENamedThreads::GameThread);
目前支持的NamedThread有：

StatsThread - 统计性能线程，FStatsThread
RHIThread - 渲染硬件接口层线程，FRHIThread
AudioThread - 音频线程，FAudioThread
GameThread - 游戏逻辑线程，主线程
RenderThread - 渲染线程，FRenderingThread
NameThread的支持两个任务队列（由QueueIndex指定）：

FThreadTaskQueue Queues[ENamedThreads::NumQueues];
MainQueue - 对应Queues[0]（默认）
LocalQueue - 对应Queues[1]
1.3.Task Priority
AnyThread和NamedThread都支持两种优先级的任务：

正常优先级 - NormalTaskPriority，对应的FStallingTaskQueue中的PriorityQueues[0]
高优先级 - HighTaskPriority，对应的FStallingTaskQueue中的PriorityQueues[]`
AnyThread和NamedThread都类似的任务队列，使用的无锁优先级队列，该队列优先Pop出高优先级任务，具体分析参见之前文章：《原子操作及其在TaskGraph中的应用》：

FStallingTaskQueue<FBaseGraphTask, PLATFORM_CACHE_LINE_SIZE, 2> StallQueue;
1.4.ThreadAndIndex
TaskGraph中许多接口需要指定线程类型，比如：

// 要在该类型线程中执行
ENamedThreads::Type ThreadToExecuteOn,    

// 任务要执行的线程
static ENamedThreads::Type GetDesiredThread()
{
    return ENamedThreads::AnyThread;
}
为了降低参数的个数，UE把一些标记也融合进了线程类型变量，比如：

// NamedThread中的LocalQueue
GameThread_Local = GameThread | LocalQueue, 
// AnyThread，高优先级线程，任务低优先级
AnyHiPriThreadHiPriTask = AnyThread | HighThreadPriority | HighTaskPriority,
同时也提供了帮助函数：

// 计算线程类型：NameThread类型或者AnyThread
FORCEINLINE Type GetThreadIndex(Type ThreadAndIndex);
// 计算NamedTread的任务队列索引
FORCEINLINE int32 GetQueueIndex(Type ThreadAndIndex);
// 计算任务的优先级： 0, 1
FORCEINLINE int32 GetTaskPriority(Type ThreadAndIndex);
// 计算线程的优先级：0, 1, 2
FORCEINLINE int32 GetThreadPriorityIndex(Type ThreadAndIndex);
1.5.Simple Examples
一个简单示例感受下：

inline void Test_GraphTask_Simple1()
{
    // 创建一个任务并在后台AnyThread中执行
    FGraphEventRef Event = FFunctionGraphTask::CreateAndDispatchWhenReady([]()
        {
            UE_LOG(LogTemp, Display, TEXT("Main task"));
            FPlatformProcess::Sleep(5.f); // pause for a bit to let waiting start
        }
    );
    check(!Event->IsComplete());

    // 在主线程中等待该任务完成
    Event->Wait(ENamedThreads::GameThread);
    UE_LOG(LogTemp, Display, TEXT("Over1 ..."));


    // 同时创建多个任务
    FGraphEventArray Tasks;
    for (int i = 0; i < 10; ++i)
    {
        Tasks.Add(FFunctionGraphTask::CreateAndDispatchWhenReady([i]()
        {
            UE_LOG(LogTemp, Display, TEXT("Task %d"), i);
        }));
    }

    // 在主线程中等待所有任务完成
    FTaskGraphInterface::Get().WaitUntilTasksComplete(MoveTemp(Tasks), ENamedThreads::GameThread);
    UE_LOG(LogTemp, Display, TEXT("Over2 ..."));
}
2.TaskGraph的实现
2.1.TaskGraph的类结构

接口层核心类：

FTaskGraphInterface - TaskGraph的接口类，可以通过FTaskGraphInterface::Get()来访问。
FBaseGraphTask - 任务基类，在线程中执行时会调用ExecuteTask。
FGraphEvent - 后续任务的集合（SubseuentList），依赖的任务完成后，这些后续任务才会被放入TaskGraph的任务队列进行执行，Graph Event的生命周期由引用计数控制。一般用FGraphEventRef代表一个任务事件，FGraphEventArray代表一组任务事件。
TGraphTask - 基于模板的实现，内置一个用户自定义任务，该任务类必须满足下面的约束：
class FGenericTask
{
    TSomeType   SomeArgument;
public:
    FGenericTask(TSomeType InSomeArgument) : SomeArgument(InSomeArgument)
    {
        // 构造函数一般只做成员变量的初始化
    }

    // 用于统计
    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FGenericTask, STATGROUP_TaskGraphTasks);
    }

    // 任务要被分配的线程类型
    ENamedThreads::Type GetDesiredThread()
    {
        return ENamedThreads::[named thread or AnyThread];
    }

    // 任务的执行逻辑，其中参数：
    //  CurrentThread - 任务执行的线程类型信息
    //  MyCompletionGraphEvent - 该任务的后续任务，可以通过DontCompleteUntil让其挂起直到后续后续任务完成再继续
    void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
    {
        // The arguments are useful for setting up other tasks. 
        // Do work here, probably using SomeArgument.
        MyCompletionGraphEvent->DontCompleteUntil(TGraphTask<FSomeChildTask>::CreateTask(NULL,CurrentThread).ConstructAndDispatchWhenReady());
    }
};
实现层：

FTaskGraphImplementation - TaskGraph系统的实现类，下面会详细介绍。
FWorkerThread - TaskGraph包含多个FWorkerThread对象，该结构有下面几个变量：
RunnableThread - 线程对象。
AnyThread时创建一个线程
NamedThread时为Null
TaskGraphWorker - Woker对象，负责调度和执行任务。
AnyThread时指向FTaskThreadAnyThread对象
NamedThread时指向FNamedTaskThread对象
2.2.TaskGraph的实现细节

其中：

WokerQueue：Woker线程队列。分两部分：
NamedThread，其数量为NumNamedThread
AnyThread，其数量为：ThreadSet的大小 x ThreadSet的数量
AnyThread：
放入任务：根据线程优先级和任务优先级，把任务放进相应的队列
执行任务：每个AnyThread对应的线程，会一直从IncommingAnyThreadTasks[Priority]中拿任务执行，空闲则挂起（无锁、可挂起、优先级队列）。
NamedThread：
放入任务：根据QueueIndex和任务优先级，把任务放进相应的队列。
执行任务：通过在相应线程中手动执行WaitUntilTaskCompletes来执行队列里面的任务。
FTaskGraphImplement的成员变量及其说明：

// 后台线程及数据（Windows平台下，最多有83个线程）
FWorkerThread       WorkerThreads[MAX_THREADS];
// 在用的线程数量
int32               NumThreads;
// NamedThread线程数量
int32               NumNamedThreads;
// 线程优先级数量（一个ThreadSet对应的线程数量，范围：1-3）
int32               NumTaskThreadSets;
// 线程集合（ThreadSet）的数量（不同平台下，根据CPU核心数量计算得出）
int32               NumTaskThreadsPerSet;

// 控制ThreadSet集合大小，是否创建高/低优先级线程
bool                bCreatedHiPriorityThreads;
bool                bCreatedBackgroundPriorityThreads;
其中：

enum
{
    // 最大线程数量
    //  - ThreadSet最多26组
    MAX_THREADS = 26 * (CREATE_HIPRI_TASK_THREADS + CREATE_BACKGROUND_TASK_THREADS + 1) + ENamedThreads::ActualRenderingThread + 1,
    // 线程优先级最多3个
    MAX_THREAD_PRIORITIES = 3
};
TaskGraph系统的初始化入口：

// FEngineLoop::PreInitPreStartupScreen
// initialize task graph sub-system with potential multiple threads
SCOPED_BOOT_TIMING("FTaskGraphInterface::Startup");

// 初始化整个TaskGraph系统
FTaskGraphInterface::Startup(FPlatformMisc::NumberOfCores());

// 当前线程Attach为GameThread
FTaskGraphInterface::Get().AttachToThread(ENamedThreads::GameThread);
2.3.TaskGraph的实现示例
一个DAG的例子：


代码片段：

FGraphEventRef TaskA, TaskB, TaskC, TaskD, TaskE;

// TaskA
TaskA = TGraphTask<FTask>::CreateTask().ConstructAndDispatchWhenReady(TEXT("TaksA"), 1, 1);

// TaskB 依赖 TaskA
{
    FGraphEventArray Prerequisites;
    Prerequisites.Add(TaskA);
    TaskB = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksB"), 1, 1);
}

// TaskC 依赖 TaskB
{
    FGraphEventArray Prerequisites;
    Prerequisites.Add(TaskB);
    TaskC = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksC"), 1, 1);
}

// TaskD 依赖 TaskA
{
    FGraphEventArray Prerequisites;
    Prerequisites.Add(TaskA);
    TaskD = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksD"), 1, 3);
}

// TaskE 依赖 TaskC、TaskD
{
    FGraphEventArray Prerequisites {TaskC, TaskD};
    TaskE = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksE"), 1, 1);
}

UE_LOG(LogTemp, Display, TEXT("Construct is Done ......"));

// 在当前线程等待，直到TaskE完成
TaskE->Wait();
UE_LOG(LogTemp, Display, TEXT("Over ......"));
对象结构：

一个任务主要由两部分构成： - Task对象，表示任务本身 - GraphEvent对象，表示任务之间的依赖关系（后续任务集合）

整个任务DAG由上面两部组成，如下所示：




Wait操作的实现：

无论哪种Wait操作： Event->Wait() FTaskGraphInterface::Get().WaitUntilTaskCompletes()

最终调用的都是FTaskGraphImplementation::WaitUntilTasksComplete

a. 对于AnyThread来说，Wait操作相当于给DAG最后再加一个Trigger任务节点，挂起到该Trigger任务执行完成：

会创建一个FTriggerEventGraphTask对象
然后使用FEvent挂起到该Trigger任务完成（调用FEvent::Trigger）

b. 对于NamedThread来说，Wait操作也是给DAG最后加了一个任务节点（FReturnGraphTask），执行NamedThread里面的任务，直到这个ReturnTask完成。

3.TaskGraph的简单用法
3.1.自定义任务
定义一个两个示例任务：

FGraphTaskSimple - 一次性任务（ESubsequentsMode::FireAndForget）
FTask - 有依赖关系的任务（ESubsequentsMode::TrackSubsequents）
代码示例：

// 定义一个一次性任务
class FGraphTaskSimple
{
public:
    FGraphTaskSimple(const TCHAR* TheName, int InSomeArgument, float InWorkingTime = 1.0f)
        : TaskName(TheName), SomeArgument(InSomeArgument), WorkingTime(InWorkingTime)
    {
        Log(__FUNCTION__);
    }

    ~FGraphTaskSimple()
    {
        Log(__FUNCTION__);
    }

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FGraphTaskSimple, STATGROUP_TaskGraphTasks);
    }

    // AnyThread中运行
    static ENamedThreads::Type GetDesiredThread()
    {
        return ENamedThreads::AnyThread;
    }

    // FireAndForget：一次性任务，没有依赖关系
    static ESubsequentsMode::Type GetSubsequentsMode()
    {
        return ESubsequentsMode::FireAndForget;
    }

    // 执行任务
    void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
    {
        // The arguments are useful for setting up other tasks. 
        // Do work here, probably using SomeArgument.
        FPlatformProcess::Sleep(WorkingTime);
        Log(__FUNCTION__);
    }

public:
    // 自定义参数
    FString TaskName;
    int SomeArgument;
    float WorkingTime;

    // 日志接口
    void Log(const char* Action)
    {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
        UE_LOG(LogTemp, Display, TEXT("%s@%s[%d] - %s, SomeArgument=%d"), *TaskName, *CurrentThreadName,
               CurrentThreadId,
               ANSI_TO_TCHAR(Action), SomeArgument);
    }
};

// 定义一个支持依赖关系的任务
class FTask : public FGraphTaskSimple
{
public:
    using FGraphTaskSimple::FGraphTaskSimple;

    FORCEINLINE TStatId GetStatId() const
    {
        RETURN_QUICK_DECLARE_CYCLE_STAT(FGraphTask, STATGROUP_TaskGraphTasks);
    }

    static ENamedThreads::Type GetDesiredThread()
    {
        return ENamedThreads::AnyThread;
    }

    // TrackSubsequents - 支持依赖检查
    static ESubsequentsMode::Type GetSubsequentsMode()
    {
        return ESubsequentsMode::TrackSubsequents;
    }
};
3.2.一次性任务
代码示例：

inline void Test_GraphTask_Simple()
{
    // 创建一个一次性任务并执行，任务结束自动删除
    TGraphTask<FGraphTaskSimple>::CreateTask().
        ConstructAndDispatchWhenReady(TEXT("SimpleTask1"), 10000, 3);

    // 创建一个任务但不放入TaskGraph执行
    TGraphTask<FGraphTaskSimple>* Task = TGraphTask<FGraphTaskSimple>::CreateTask().ConstructAndHold(
        TEXT("SimpleTask2"), 20000);
    if (Task)
    {
        // Unlock操作，放入TaskGraph执行
        UE_LOG(LogTemp, Display, TEXT("Task is Unlock to Run..."));
        Task->Unlock();
        Task = nullptr;
    }
}
3.3.顺序依赖任务
有三个任务，需要按照顺序执行，任务本身在不同的AnyThread中执行：


代码示例：

// TaskA -> TaskB -> TaskC
inline void Test_GraphTask_Simple2()
{
    UE_LOG(LogTemp, Display, TEXT("Start ......"));

    FGraphEventRef TaskA, TaskB, TaskC;

    // TaskA
    {
        TaskA = TGraphTask<FTask>::CreateTask().ConstructAndDispatchWhenReady(TEXT("TaksA"), 1, 3);
    }

    // TaskA -> TaskB
    {
        FGraphEventArray Prerequisites;
        Prerequisites.Add(TaskA);
        TaskB = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksB"), 2, 2);
    }

    // TaskB -> TaskC
    {
        FGraphEventArray Prerequisites{TaskB};
        TaskC = TGraphTask<FTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(TEXT("TaksC"), 3, 1);
    }


    UE_LOG(LogTemp, Display, TEXT("Construct is Done ......"));

    // Waiting until TaskC is Done
    // FTaskGraphInterface::Get().WaitUntilTaskCompletes(TaskC);
    // Or.
    TaskC->Wait();

    UE_LOG(LogTemp, Display, TEXT("TaskA is Done : %d"), TaskA->IsComplete());
    UE_LOG(LogTemp, Display, TEXT("TaskB is Done : %d"), TaskA->IsComplete());
    UE_LOG(LogTemp, Display, TEXT("TaskC is Done : %d"), TaskC->IsComplete());
    UE_LOG(LogTemp, Display, TEXT("Over ......"));
}
3.4.Gather/Fence任务
FNullGraphTask，一个执行体为空的任务，用于等待多个任务结束后的点，类似Fork-Join模型中的Join操作。


代码示例：

//
//  TaskA ->
//          | -> NullTask(Gather/Fence)
//  TaskB ->
//
inline void Test_GraphTask_NullTask()
{
    // 创建并运行TaskA，TaskB
    auto TaskA = TGraphTask<FTask>::CreateTask().ConstructAndDispatchWhenReady(TEXT("TaskA"), 1, 2);
    auto TaskB = TGraphTask<FTask>::CreateTask().ConstructAndDispatchWhenReady(TEXT("TaskB"), 2, 1);

    // 创建一个空任务，依赖于TaskA和TaskB
    FGraphEventRef CompleteEvent;
    {
        DECLARE_CYCLE_STAT(TEXT("FNullGraphTask.Gather"),
                           STAT_FNullGraphTask_Gather,
                           STATGROUP_TaskGraphTasks);
        FGraphEventArray Prerequisites;
        Prerequisites.Add(TaskA);
        Prerequisites.Add(TaskB);
        CompleteEvent = TGraphTask<FNullGraphTask>::CreateTask(&Prerequisites).ConstructAndDispatchWhenReady(
            GET_STATID(STAT_FNullGraphTask_Gather), ENamedThreads::GameThread);
    }


    UE_LOG(LogTemp, Display, TEXT("Construct is Done ......"));

    // 等待TaskA和TaskB任务完成
    CompleteEvent->Wait();

    UE_LOG(LogTemp, Display, TEXT("Over ......"));
}
3.5.Delegate任务
支持两种代理任务：

FSimpleDelegateGraphTask - Delegate对象没有参数
FDelegateGraphTask - Delegate对象有两个参数，形如：TaskDelegate(NamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)，和上面定义的任务的DoTask参数相同。
代码示例：

inline void Test_GraphTask_Delegate()
{
    // Simple Delegate
    FSimpleDelegateGraphTask::CreateAndDispatchWhenReady(
        FSimpleDelegateGraphTask::FDelegate::CreateLambda([]()
        {
            uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
            FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
            UE_LOG(LogTemp, Display, TEXT("%s[%d] - Simple Delegate"), *CurrentThreadName, CurrentThreadId);
        }),
        TStatId()
    );


    // Delegate
    FTaskGraphInterface::Get().WaitUntilTaskCompletes(
        FDelegateGraphTask::CreateAndDispatchWhenReady(
            FDelegateGraphTask::FDelegate::CreateLambda(
                [](ENamedThreads::Type InCurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
                {
                    FPlatformProcess::Sleep(3);
                    uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
                    FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
                    UE_LOG(LogTemp, Display, TEXT("%s[%d] - Delegate, %d"), *CurrentThreadName, CurrentThreadId,
                           InCurrentThread);
                }),
            TStatId()
        ),
        ENamedThreads::GameThread
    );

    UE_LOG(LogTemp, Display, TEXT("Over ......"));
}
3.6.Function任务
封装了TUniqueFunction，可以直接用于执行某一个函数对象，或者Lambda函数。

代码示例：

inline void Test_GraphTask_Function()
{
    // 无参数的形式
    FFunctionGraphTask::CreateAndDispatchWhenReady([]()
    {
        uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
        FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
        UE_LOG(LogTemp, Display, TEXT("%s[%d] - Fuction with Void"), *CurrentThreadName, CurrentThreadId);
    }, TStatId());


    // 有参数形式
    FFunctionGraphTask::CreateAndDispatchWhenReady(
        [](ENamedThreads::Type InCurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
        {
            FPlatformProcess::Sleep(3);
            uint32 CurrentThreadId = FPlatformTLS::GetCurrentThreadId();
            FString CurrentThreadName = FThreadManager::Get().GetThreadName(CurrentThreadId);
            UE_LOG(LogTemp, Display, TEXT("%s[%d] - Function with parameters, %d"), *CurrentThreadName, CurrentThreadId,
                   InCurrentThread);
        }, TStatId())->Wait(ENamedThreads::GameThread);

    UE_LOG(LogTemp, Display, TEXT("Over ......"));
}
4.并行计算Fibonacci数列的示例
使用TaskGraph实现一个同步和异步模式的，并行计算斐波拉切数列的例子。通过下面示例，感受下其强大之处，使用TaskGraph可以以简洁的代码轻松实现Map/Reduce或Fork/Join模式。

形式1：同步模式
通过递归实现，每次调用创建两个任务，并等待其结束。直到所有子任务完成，返回结果。

int64 Fibonacci(int64 N)
{
    check(N > 0);
    if (N <= 2)
    {
        // 递归结束条件
        return 1;
    }
    else
    {
        std::atomic<int64> F1{ -1 };
        std::atomic<int64> F2{ -1 };
        FGraphEventArray GraphEvents;
        // Fork：创建两个任务，子任务递归调用Fibonacci
        GraphEvents.Add(FFunctionGraphTask::CreateAndDispatchWhenReady([&F1, N] { F1 = Fibonacci(N - 1); }));
        GraphEvents.Add(FFunctionGraphTask::CreateAndDispatchWhenReady([&F2, N] { F2 = Fibonacci(N - 2); }));

        // Join：等待上面两个任务结束
        FTaskGraphInterface::Get().WaitUntilTasksComplete(MoveTemp(GraphEvents));
        check(F1 > 0 && F2 > 0);

        return F1 + F2;
    }
}
形式2：异步模式
也是通过递归调用构建一个树状的任务网络，然后返回它的GraphEvent对象（根结点）。然后任务的执行分配在不同的AnyThread中执行，遇到结束条件时，执行ResEvent->DispatchSubsequents，然后父任务才算完成，完成事件依次往上抛，到最终的根结点。

FGraphEventRef Fib(int64 N, int64* Res)
{
    if (N <= 2)
    {
        // 递归结束条件，返回一个空事件，并执行分发
        *Res = 1;
        FGraphEventRef ResEvent = FGraphEvent::CreateGraphEvent();
        ResEvent->DispatchSubsequents();
        return ResEvent;
    }
    else
    {
        TUniquePtr<int64> F1 = MakeUnique<int64>();
        TUniquePtr<int64> F2 = MakeUnique<int64>();

        FGraphEventArray SubTasks;

        auto FibTask = [](int64 N, int64* Res)
        {
            return FFunctionGraphTask::CreateAndDispatchWhenReady
            (
                [N, Res]
                (ENamedThreads::Type, const FGraphEventRef& CompletionEvent)
                {
                    // 递归调用
                    FGraphEventRef ResEvent = Fib(N, Res);
                    // 若返回的事件没完成，当前任务不算结束
                    CompletionEvent->DontCompleteUntil(ResEvent);
                }
            );
        };

        // 创建两个子任务
        SubTasks.Add(FibTask(N - 1, F1.Get()));
        SubTasks.Add(FibTask(N - 2, F2.Get()));

        // 创建计算任务，依赖上面两个任务
        FGraphEventRef ResEvent = FFunctionGraphTask::CreateAndDispatchWhenReady
        (
            [F1 = MoveTemp(F1), F2 = MoveTemp(F2), Res]
            {
                *Res = *F1 + *F2;
            }, 
            TStatId{}, &SubTasks
        );

        return ResEvent;
    }
}

template<int64 N>
void Fib()
{
    TUniquePtr<int64> Res = MakeUnique<int64>();
    // 异步计算Fib
    FGraphEventRef ResEvent = Fib(N, Res.Get());
    // 干点其它事情...

    // 等待异步计算结束，输出结果
    ResEvent->Wait();
    UE_LOG(LogTemp, Display, TEXT("Fibonacci(%d) = %d"), N, *Res);
}
5.小结
通过以上示例和实现分析，可以看到UE的TaskGraph提供了一套非常方便的，基于任务的并发机制。加上低层无锁任务队列的实现，让其任务调度的性能有了保证。

另外有一点要一直强调：任务执行体中的代码，一定要明确知道它在什么类型的线程中执行，是否存在数据竞争。比如：Gameplay相关的对象操作，如Actor的创建和删除的任务，只能在GameThread类型的线程中执行，若放入其它线程执行就会有问题。

PS.之前在一游戏项目中实现过类似的异步任务机制，后台多个线程执行任务，最终Wait操作只能在游戏逻辑主线程中，比起UE的TaskGraph简直就是小巫见大巫了。代码片段如下：

https://github.com/david-pp/tinyworld/blob/master/common/async.h
6.参考资料
示例完整代码：

https://github.com/david-pp/UESnippets/blob/main/SnippetAsync/Private/SimpleGraphTask.h
UE源码：

Engine/Source/Runtime/Core/Public/Async/TaskGraphInterfaces.h Engine/Source/Runtime/Core/Private/Tests/Async/TaskGraphTest.cpp
</code></pre>
</details>

<details>
<summary>UE并发-Async & Future & Promise</summary>
<pre><code>
https://zhuanlan.zhihu.com/p/399838210
Simplicity is the ultimate form of sophistication ! - Leonardo Da Vinci
UnrealEngine有了跨平台的线程、线程池和TaskGraph，再来看看Async/ParalleFor和Future/Promise的实现，由衷的感受下上面的话：简约是复杂的最终形式。这些操作实现都不复杂，却有着强大的能力，让异步并发代码写起来简洁易懂。下面简单介绍下：

Future & Promise的实现和简单用法
Async系列接口的用法
Paralle接口的用法
另外这里相关接口可以类比C++标准库中的概念。UE中这些接口是基于之前提到的几种并发机制实现的，废话不多说，上代码，看注释。

1.Future & Promise
1.1.实现
Future和Promise的概念，和C++标准中的std::future/std::promise类似：

Future - 一个会在未来某个点返回的值
Promise - 一个异步函数，在某个并发执行体中设置，然后Future变得有效
实现比较简单，类图如下：




TPromise<ResultType> - Promise
TFuture<ResultType> - Future
TFutureState<ResultType> - Future和Promise共享的状态。
Promise创建时创建一个State
GetFuture()时返回一个共享该状态的Future对象
基于FEvent实现，等待和触发
1.2.基本用法
Future和Promise这两个概念非常形象，可以理解为：

Promise - 给别人一承诺
Promise.GetFuture() - 承诺一个未来
Promise.SetValue(X) - 兑现承诺
Future.IsReady() - 承诺是否兑现？
代码示例：

inline void Test_FuturePromise()
{
    // 承诺给一个bool结果
    TPromise<bool> Promise;
    // 返回一个尚未兑现的未来
    TFuture<bool> Future = Promise.GetFuture();

    // AnyThread中执行
    FFunctionGraphTask::CreateAndDispatchWhenReady([&Promise]()
    {
        FPlatformProcess::Sleep(3);
        AsyncLog("do the promise");
        // 实现承诺（Promise）
        Promise.SetValue(true);
    });

    // 等待实现承诺
    //  - Wait - 等到天荒地老
    //  - WaitFor - 等一个时间段
    //  - WaitUntil - 等到某年某月某一天
    UE_LOG(LogTemp, Display, TEXT("waiting for the promise..."));
    // Future.Wait();
    Future.WaitFor(FTimespan::FromSeconds(5));
    // Future.WaitUntil(FDateTime(2022, 1, 1));

    // 承诺已兑现 
    if (Future.IsReady()) 
    {
        // Future.Get() - 看下结果
        UE_LOG(LogTemp, Display, TEXT("keep the promise, future is %d"), Future.Get());
    }
    // 承诺尚未兑现
    else
    {   
        Promise.SetValue(false);
        UE_LOG(LogTemp, Display, TEXT("break the promise"));
    }
}
输出：

LogTemp: Display: waiting for the promise...
LogTemp: Display: TaskGraphThreadNP 0[16164], do the promise
LogTemp: Display: keep the promise, future is 1
1.3.带回调的Promise
Promise在设置完，在进行设置操作的线程中，执行一个回调。

代码示例：

inline void Test_FuturePromise2()
{
    // 带回调的Promise，Promise实现时，调用该回调
    TPromise<bool> Promise([]()
    {
        AsyncLog("the promise is set !");
    });

    TFuture<bool> Future = Promise.GetFuture();

    // TaskGraph中运行并等其完成
    FFunctionGraphTask::CreateAndDispatchWhenReady([&Promise]()
    {
        FPlatformProcess::Sleep(3);

        AsyncLog("do the promise");
        Promise.SetValue(true);
    })->Wait(ENamedThreads::GameThread);
}
输出：

LogTemp: Display: TaskGraphThreadNP 0[15864], do the promise
LogTemp: Display: TaskGraphThreadNP 0[15864], the promise is set !
1.4.创建一个异步函数
定义一个返回Future的异步函数，然后拿着Future返回值，可以进行Wait/Then等操作。

定义一个异步执行的函数，并返回Future对象：

TFuture<int> DoSthAsync(int Value)
{
    TPromise<int> Promise;
    TFuture<int> Future = Promise.GetFuture();

    class FGraphTaskSimple
    {
    public:
        FGraphTaskSimple(TPromise<int>&& ThePromise, int TheValue)
            : Promise(MoveTemp(ThePromise)), FutureValue(TheValue)
        {
        }

        FORCEINLINE TStatId GetStatId() const
        {
            RETURN_QUICK_DECLARE_CYCLE_STAT(FGraphTaskSimple, STATGROUP_TaskGraphTasks);
        }

        static ENamedThreads::Type GetDesiredThread()
        {
            return ENamedThreads::AnyThread;
        }

        static ESubsequentsMode::Type GetSubsequentsMode()
        {
            return ESubsequentsMode::FireAndForget;
        }

        void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
        {
            AsyncLog("DoSthAsync.... Begin");
            FPlatformProcess::Sleep(3);
            AsyncLog("DoSthAsync.... Done");

            Promise.SetValue(FutureValue);
        }

    private:
        TPromise<int> Promise;
        int FutureValue;
    };

    TGraphTask<FGraphTaskSimple>::CreateTask().ConstructAndDispatchWhenReady(MoveTemp(Promise), MoveTemp(Value));

    return MoveTemp(Future);
}
代码示例：

inline void Test_FuturePromise3()
{
    // usage1: 返回Future，通过Get操作等待Promise的兑现
    {
        auto Future = DoSthAsync(100);

        // todo other ...
        FPlatformProcess::Sleep(1);
        UE_LOG(LogTemp, Display, TEXT("Do something else .."));

        // waiting for the value
        int Value = Future.Get();
        UE_LOG(LogTemp, Display, TEXT("Value = %d"), Value);
    }

    // usage2 : Promise兑现的时候，执行一系列Then操作（在相应的线程中）
    DoSthAsync(1)
            .Then([](TFuture<int> Future) -> int
            {
                AsyncLog("then1 .. ");
                UE_LOG(LogTemp, Display, TEXT("Value = %d"), Future.Get());
                return 2;
            })
            .Then([](TFuture<int> Future)
            {
                AsyncLog("then2 .. ");
                UE_LOG(LogTemp, Display, TEXT("Value = %d"), Future.Get());
            })
            .Wait();

    AsyncLog("Over....");
}
输出：

// usage1：
LogTemp: Display: TaskGraphThreadNP 0[4611], DoSthAsync.... Begin
LogTemp: Display: Do something else ..
LogTemp: Display: TaskGraphThreadNP 0[4611], DoSthAsync.... Done
LogTemp: Display: Value = 100

// usage2：
LogTemp: Display: TaskGraphThreadNP 0[4611], DoSthAsync.... Begin
LogTemp: Display: TaskGraphThreadNP 0[4611], DoSthAsync.... Done
LogTemp: Display: TaskGraphThreadNP 0[4611], then1 .. 
LogTemp: Display: Value = 1
LogTemp: Display: TaskGraphThreadNP 0[4611], then2 .. 
LogTemp: Display: Value = 2
LogTemp: Display: GameThread[259], Over....
2.Async接口
Async系列接口支持异步执行一个函数，并返回Future对象（包含函数返回值），可以通过参数控制使用何种UE中的并发机制。

Async执行方式：

TaskGraph - 在TaskGraph中执行，适合运行时间较短的任务
TaskGraphMainThread - 在TaskGraph中并且指定主线程中执行，适合运行时间较短的任务
Thread - 创建一个线程对象执行，适合运行时较长的任务
ThreadPool - 在全局线程池中运行（GThreadPool）
LargeThreadPool - Editor模式下在全局GLargeThreadPool中运行
Async接口：

Async - 异步执行的统一接口，需要指定执行方式（EAsyncExecution），并返回一个Future对象
AsyncThread - 创建一个线程来执行
AsyncPool - 在指定的线程池中执行
AsyncTask - TaskGraph中指定线程类型（ENamedThreads）中执行
代码示例1：

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
代码示例2：

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
3.ParallelFor接口
把某一个大型任务划分成可以并行执行的N个子任务，划分方法比如采用：大的数据结构拆成块，每一块并行处理。

ParallelFor就是用来干这个事情的（基于TaskGraph实现）： 指定划分的数量 和执行函数，其中执行函数的参数为划分的索引 * 运行所有子任务直到结束，ParallelFor返回

代码示例：

inline void Test_Parallel()
{
    // parallel
    ParallelFor(100, [](int32 Index)
    {
        int32 ThreadId = FPlatformTLS::GetCurrentThreadId();
        FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
        UE_LOG(LogTemp, Display, TEXT("%s[%d],Parallel Task, Index:%d"), *ThreadName, ThreadId, Index); 
    });

    // done
    UE_LOG(LogTemp, Display, TEXT("Over....")); 
}
输出：

...
LogTemp: Display: TaskGraphThreadNP 4[3075],Parallel Task, Index:98
LogTemp: Display: TaskGraphThreadNP 3[4355],Parallel Task, Index:96
...
LogTemp: Display: Over....
4.参考资料
完整代码示例：

https://github.com/david-pp/UESnippets/blob/main/SnippetAsync/Private/SimpleAsync.h
UE源码：

Engine/Source/Runtime/Core/Public/Async/Future.h
Engine/Source/Runtime/Core/Public/Async/Async.h
Engine/Source/Runtime/Core/Public/Async/ParallelFor.h
</code></pre>
</details>