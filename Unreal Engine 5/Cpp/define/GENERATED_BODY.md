GENERATED_BODY 宏在 Unreal Engine 中用于生成代码模板。当您创建一个派生类并使用此宏时，引擎将自动生成一个包含类构造函数、类析构函数、默认构造函数和蓝牙（Blueprint）构造函数的代码模板。这个宏有助于确保派生类具有正确的基础类实现，并简化创建新类的过程。
以下是如何使用 GENERATED_BODY 宏的示例：
cpp
复制
// 声明一个名为 "UMyBaseClass" 的基础类
UCLASS()
class MYGAME_API UMyBaseClass : public UObject
{
    GENERATED_BODY()
public:
    // 定义一个名为 "MyFunction" 的 UFUNCTION
    UFUNCTION(BlueprintCallable, Category = "MyFunctions")
    void MyFunction();
};
// 声明一个名为 "UMyDerivedClass" 的派生类
UCLASS()
class MYGAME_API UMyDerivedClass : public UMyBaseClass
{
    GENERATED_BODY()
public:
    // 重写基类的 MyFunction 函数
    UFUNCTION(BlueprintCallable, Category = "MyFunctions")
    void MyFunction() override;
    // 添加一个新的 UFUNCTION
    UFUNCTION(BlueprintCallable, Category = "MyDerivedFunctions")
    void MyDerivedFunction();
};
在这个例子中，我们声明了一个名为 UMyDerivedClass 的派生类，它继承了 UMyBaseClass 基础类。通过使用 GENERATED_BODY 宏，引擎将自动生成以下代码：
基类的构造函数和析构函数
派生类的构造函数（包括蓝牙构造函数）
派生类的默认构造函数
这使得创建新类变得更加简单，因为您不需要手动实现这些代码。同时，这有助于确保派生类正确地继承了基础类的功能。
请注意，尽管 GENERATED_BODY 宏对简化类创建过程很有帮助，但在某些情况下，您可能需要手动编写代码以实现特定的功能。在这种情况下，不使用 GENERATED_BODY 宏，而是手动编写相关代码。

-----------------------------------------------------------------------------------------------------------------------------------------------------------
解析内部

宏GENERATED_BODY
GENERATED_BODY宏定义在引擎源文件Engine/Source/Runtime/CoreUObject/Public/UObjectMacros.h中，下面是源码的部分摘录：

// This pair of macros is used to help implement GENERATED_BODY() and GENERATED_USTRUCT_BODY()
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

// Include a redundant semicolon at the end of the generated code block, so that intellisense parsers can start parsing
// a new declaration if the line number/generated code is out of date.
#define GENERATED_BODY_LEGACY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY_LEGACY);
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);

#define GENERATED_USTRUCT_BODY(...) GENERATED_BODY()
#define GENERATED_UCLASS_BODY(...) GENERATED_BODY_LEGACY()
#define GENERATED_UINTERFACE_BODY(...) GENERATED_BODY_LEGACY()
#define GENERATED_IINTERFACE_BODY(...) GENERATED_BODY_LEGACY()
初步宏展开会得到:

CURRENT_FILE_ID_15_GENERATED_BODY

头文件MyProject.h包含了MyProject.generated.h这个头文件，在MyProject.generated.h中，有如下定义：

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID MyProject_Source_MyProject_Public_MyObject_h
进一步宏展开得到：

MyProject_Source_MyProject_Public_MyObject_h_15_GENERATED_BODY
查看MyProject.generated.h文件，这个这玩意其实也是一个宏定义：

#define MyProject_Source_MyProject_Public_MyObject_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	MyProject_Source_MyProject_Public_MyObject_h_15_PRIVATE_PROPERTY_OFFSET \
	MyProject_Source_MyProject_Public_MyObject_h_15_SPARSE_DATA \
	MyProject_Source_MyProject_Public_MyObject_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Public_MyObject_h_15_INCLASS_NO_PURE_DECLS \
	MyProject_Source_MyProject_Public_MyObject_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS
以当前MyObject.h和MyObject.generated.h中的宏定义展开后，会得到下面的UMyObject定义：

class UMyObject : public UObject
{
public:
	// MyProject_Source_MyProject_Public_MyObject_h_15_PRIVATE_PROPERTY_OFFSET // 空宏
	// MyProject_Source_MyProject_Public_MyObject_h_15_SPARSE_DATA // 空宏
	// MyProject_Source_MyProject_Public_MyObject_h_15_RPC_WRAPPERS_NO_PURE_DECLS // 空宏
	
    // ****************** INCLASS_NO_PURE_DECLS 开始 *****************
private:
	static void StaticRegisterNativesUMyObject();
	friend struct Z_Construct_UClass_UMyObject_Statics;
public:
	DECLARE_CLASS(UMyObject, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/MyProject"), NO_API)
	DECLARE_SERIALIZER(UMyObject)
    // ****************** INCLASS_NO_PURE_DECLS 结束 *****************

    // ****************** ENHANCED_CONSTRUCTORS 开始 ******************
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMyObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UMyObject(UMyObject&&); \
	NO_API UMyObject(const UMyObject&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMyObject); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMyObject); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMyObject)
   // ****************** ENHANCED_CONSTRUCTORS 结束 ******************
private:

};
到目前为止可以确定的，GENERATED_BODY宏做了下面这些事：

添加了一个静态函数static void StaticRegisterNativeUMyObject();
声明结构体struct Z_Construct_UClass_UMyObject_Statics;为friend
添加了一个public构造函数UMyObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
通过声明private: UMyObject(UMyObject&&); UMyObject(const UMyObject&&);禁用move和copy

来源:https://www.cnblogs.com/ayou007/p/15640145.html