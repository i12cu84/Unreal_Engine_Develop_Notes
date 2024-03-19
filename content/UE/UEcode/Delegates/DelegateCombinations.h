// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Core\Public\Delegates\DelegateCombinations.h

// 委托(节选)

/**
 *  DELEGATE PARAMETER COMBINATIONS
 *  -----------------------------------------------------------------------------------------------
 *
 * 这个文件定义了用于声明不同委托类型的宏的不同组合。
 * 每种委托类型可以绑定到最多接受9个参数的函数。
 * 委托系统的完整文档可以在main delegate .h头文件中找到，
 * 哪些应该包含在需要访问这些宏的CPP文件中。
 */

#if 0 // 导入委托头文件的示例
#include "Delegates/Delegate.h"
#endif

/**声明一个委托，一次只能绑定到一个原生函数*/
#define DECLARE_DELEGATE(DelegateName) FUNC_DECLARE_DELEGATE(DelegateName, void)

/**声明一个广播委托，可以同时绑定到多个本机函数*/
#define DECLARE_MULTICAST_DELEGATE(DelegateName) FUNC_DECLARE_MULTICAST_DELEGATE(DelegateName, void)

/**声明一个广播线程安全的委托，它可以同时绑定到多个本机函数*/
#define DECLARE_TS_MULTICAST_DELEGATE(DelegateName) FUNC_DECLARE_TS_MULTICAST_DELEGATE(DelegateName, void)

/ ***声明一个只能从OwningType激活的多播委托 *注意 : 此行为不是强制的，对于新的委托，此类型应考虑弃用，请使用普通多播 * /
#define DECLARE_EVENT(OwningType, EventName) FUNC_DECLARE_EVENT(OwningType, EventName, void)

/**声明一个blueprint可访问的委托，一次只能绑定到一个UFUNCTION */
#define DECLARE_DYNAMIC_DELEGATE(DelegateName) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_DELEGATE(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, , FUNC_CONCAT(*this), void)

/**声明一个blueprint可访问的广播委托，它可以同时绑定到多个原生的ufunction */
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE(DelegateName) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, , FUNC_CONCAT(*this), void)

/**声明一个具有返回值的委托，一次只能绑定到一个原生函数*/
#define DECLARE_DELEGATE_RetVal(ReturnValueType, DelegateName) FUNC_DECLARE_DELEGATE(DelegateName, ReturnValueType)

/**声明一个blueprint可访问的委托，其返回值一次只能绑定到一个非函数*/
#define DECLARE_DYNAMIC_DELEGATE_RetVal(ReturnValueType, DelegateName) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_DELEGATE_RETVAL(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, ReturnValueType, , FUNC_CONCAT(*this), ReturnValueType)

// 以上委托类型的多参数版本:(仅以一个参数为例,后八个参数代码就省略了)
// 这段代码是C++的宏定义，用于简化委托（Delegate）和事件（Event）的声明。这些宏定义通常用于游戏引擎或大型软件项目中，以便于快速创建和使用委托和事件。以下是对每个宏定义的注释：

// 用于声明一个单参数的委托。`DelegateName`是委托的名称，`Param1Type`是委托参数的类型。
#define DECLARE_DELEGATE_OneParam(DelegateName, Param1Type) FUNC_DECLARE_DELEGATE(DelegateName, void, Param1Type)

// 用于声明一个单参数的多播委托。与`DECLARE_DELEGATE_OneParam`类似，但多播委托可以持有多个回调。
#define DECLARE_MULTICAST_DELEGATE_OneParam(DelegateName, Param1Type) FUNC_DECLARE_MULTICAST_DELEGATE(DelegateName, void, Param1Type)

// 用于声明一个单参数的TypeScript多播委托。这通常用于与TypeScript交互的项目中。
#define DECLARE_TS_MULTICAST_DELEGATE_OneParam(DelegateName, Param1Type) FUNC_DECLARE_TS_MULTICAST_DELEGATE(DelegateName, void, Param1Type)

// 用于声明一个拥有者类型为`OwningType`的单参数事件。`EventName`是事件的名称，`Param1Type`是事件参数的类型。
#define DECLARE_EVENT_OneParam(OwningType, EventName, Param1Type) FUNC_DECLARE_EVENT(OwningType, EventName, void, Param1Type)

// 用于声明一个单参数的动态委托。这种委托在运行时可以添加或移除回调。`Param1Name`是参数的名称。
#define DECLARE_DYNAMIC_DELEGATE_OneParam(DelegateName, Param1Type, Param1Name) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_DELEGATE(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, FUNC_CONCAT(Param1Type InParam1), FUNC_CONCAT(*this, InParam1), void, Param1Type)

// 用于声明一个单参数的动态多播委托。与`DECLARE_DYNAMIC_DELEGATE_OneParam`类似，但它是多播的。
#define DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(DelegateName, Param1Type, Param1Name) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, FUNC_CONCAT(Param1Type InParam1), FUNC_CONCAT(*this, InParam1), void, Param1Type)

// 用于声明一个有返回值和单参数的委托。`ReturnValueType`是委托返回值的类型。
#define DECLARE_DELEGATE_RetVal_OneParam(ReturnValueType, DelegateName, Param1Type) FUNC_DECLARE_DELEGATE(DelegateName, ReturnValueType, Param1Type)

// 用于声明一个有返回值和单参数的动态委托。与`DECLARE_DELEGATE_RetVal_OneParam`类似，但它是动态的。
#define DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(ReturnValueType, DelegateName, Param1Type, Param1Name) BODY_MACRO_COMBINE(CURRENT_FILE_ID, _, __LINE__, _DELEGATE) FUNC_DECLARE_DYNAMIC_DELEGATE_RETVAL(FWeakObjectPtr, DelegateName, DelegateName##_DelegateWrapper, ReturnValueType, FUNC_CONCAT(Param1Type InParam1), FUNC_CONCAT(*this, InParam1), ReturnValueType, Param1Type)
