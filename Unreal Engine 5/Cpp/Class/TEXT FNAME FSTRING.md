FName：着重于表示名称，不区分大小写，不可更改，引擎中的资源名称都是FName类型，通过一个轻型系统重复使用字符串，FName创建时会根据内容创建一个Hash值，且同样的内容只会存储一次。
通过Hash值在进行FName的查找和访问时速度较快，而在比较的时，也不需要比较字符串内容，直接比较Hash值来区分不同FName字符串。

另外两种字符串到FName的转换（特别注意的是，FText不能直接转换到FName，可先转换为FString，再转换为FName）：

FString str = TEXT("Hello world~");
FText txt = LOCTEXT("keyName", "theValue");
FText txtNS = NSLOCTEXT("TextNameSpace", "keyName", "theValue");
 
// FString 转 FName：不可靠，丢失大小写信息
FName name1 = FName(*str);

FString strFromTxt = txt.ToString();
// FText 先转 FString，再转 FName：不可靠，丢失大小写信息，丢失本地化信息可能导致语言转换的潜在风险
FName name2 = FName(*strFromTxt);





FString：最接近std::string，着重在于字符串的操作，提供了大量对字符串的操作接口，是三者中唯一可修改的字符串类型，也正因如此，FString对比其它两种字符串来说消耗更高，性能更低。

另外两种字符串到FString的转换：

FName name = TEXT("I am Frank~");
FText txt = LOCTEXT("keyName", "theValue");
FText txtNS = NSLOCTEXT("TextNameSpace", "keyName", "theValue");

// FName 转 FString：可靠
FString str1 = name.ToString();
// FText 转 FString：不可靠，丢失本地化信息可能导致语言转换的潜在风险
FString str2 = txt.ToString();




FText：着重在于显示与本地化，显示可理解玩家能直接看到的信息，本地化即多语言的处理，不可更改。相较于另外两种类型，FText会更加的臃肿，但提供了优秀的本地化功能。

另外两种字符串到FText的转换：

FString str = TEXT("Hello world~");
FName name = TEXT("I am Frank~");

// FString 转 FText：可靠
FText txt1 = FText::FromString(str);
// FName 转 FText：可靠
FText txt2 = FText::FromName(name);
需要注意的是，创建FText需要命名控件需要定义命名空间，并在编辑器开启本地化控制面板功能（Localization Dashboard）：

I. 在当前源文件声明文本空间宏，在宏的声明范围内创建FText可以不需要命名空间参数，需要特别注意必须在源文件末尾取消声明：

// Source.cpp 
// 声明文本空间宏
#define LOCTEXT_NAMESPACE "MyTextNameSpace"

// 宏声明范围创建FText
FText txt = LOCTEXT("keyName", "theValue");

// 必须要在合适的位置取消声明
#undef LOCTEXT_NAMESPACE 
II. 在编辑器定义好命名空间，可在代码中直接使用：

// 利用已经定义好的命名空间
FText txtNS = NSLOCTEXT("TextNameSpace", "keyName", "theValue");

参考文献
https://zhuanlan.zhihu.com/p/408359058