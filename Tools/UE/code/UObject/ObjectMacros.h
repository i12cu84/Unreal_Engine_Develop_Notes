//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\CoreUObject\Public\UObject\ObjectMacros.h

/* ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

//Line 666

///////////////////////////////
/// UObject definition macros
///////////////////////////////

//这些宏包装由Unreal头(UHT)信息工具解析的元数据
//当包含它们的代码被c++编译器编译时，它们会被忽略

//定义引擎可以识别和使用的属性 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UPROPERTY.md
#define UPROPERTY(...)

//定义引擎可以识别和调用的函数 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UFUNCTION.md
#define UFUNCTION(...)

//定义引擎可以识别和调用的结构体 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/USTRUCT.md
#define USTRUCT(...)

//定义元数据信息 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UMETA.md
#define UMETA(...)

//定义函数的参数 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UPARAM.md
#define UPARAM(...)

//定义引擎可以识别和调用的枚举 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UENUM.md
#define UENUM(...)

//定义代理类 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/UDELEGATE.md
#define UDELEGATE(...)

//在Rig虚拟机（RVM）中注册自定义的运行时函数 详解https://github.com/i12cu84/Unreal_Engine_Develop_Notes/blob/main/Unreal%20Engine%205/Cpp/define/RIGVM_METHOD.md
#define RIGVM_METHOD(...)

//用于内联UObject头文件生成的cpp文件
#define UE_INLINE_STRINGIFY(name) #name
#if UE_DISABLE_INLINE_GEN_CPP
	#define UE_INLINE_GENERATED_CPP_BY_NAME(name) UE_INLINE_STRINGIFY(CoreTypes.h)
#else
	#define UE_INLINE_GENERATED_CPP_BY_NAME(name) UE_INLINE_STRINGIFY(name.gen.cpp)
#endif

//这对宏用于帮助实现GENERATED_BODY()和GENERATED_USTRUCT_BODY()
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D //##链接，#把字符变为字符串
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

//在生成的代码块的末尾包含一个冗余分号，以便智能感知解析器可以开始解析
//如果行号/生成的代码过期了，则重新声明。
#define GENERATED_BODY_LEGACY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY_LEGACY);
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);//定义蓝图节点

#define GENERATED_USTRUCT_BODY(...) GENERATED_BODY()
#define GENERATED_UCLASS_BODY(...) GENERATED_BODY_LEGACY()
#define GENERATED_UINTERFACE_BODY(...) GENERATED_BODY_LEGACY()
#define GENERATED_IINTERFACE_BODY(...) GENERATED_BODY_LEGACY()

#if UE_BUILD_DOCS || defined(__INTELLISENSE__ )
#define UCLASS(...)
#else
#define UCLASS(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_PROLOG)
#endif

#define UINTERFACE(...) UCLASS()