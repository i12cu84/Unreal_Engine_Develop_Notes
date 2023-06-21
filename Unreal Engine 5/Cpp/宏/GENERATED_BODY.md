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