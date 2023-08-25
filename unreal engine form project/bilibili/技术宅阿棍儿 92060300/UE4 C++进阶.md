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
</code></pre>
</details>

<details>
<summary>UE4 C++进阶04 异步操作-Tick/异步节点/多输入输出节点</summary>
<pre><code>
https://www.bilibili.com/video/BV19Z4y137Bw
</code></pre>
</details>

<details>
<summary>UE4 C++进阶05 异步操作-基于FRunnable类的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1ov411h7ng
</code></pre>
</details>

<details>
<summary>UE4 C++进阶06 异步操作-基于AsyncTask的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1oX4y137Ed
</code></pre>
</details>

<details>
<summary>UE4 C++进阶07 异步操作-基于TaskGraph的多线程</summary>
<pre><code>
https://www.bilibili.com/video/BV1fh411S7dL
</code></pre>
</details>


