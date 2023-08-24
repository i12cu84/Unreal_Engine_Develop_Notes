
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
<summary> </summary>
<pre><code>

</code></pre>
</details>

<details>
<summary> </summary>
<pre><code>

</code></pre>
</details>

