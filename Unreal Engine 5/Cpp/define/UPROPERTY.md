
属性声明
属性使用标准的C++变量语法声明，前面用UPROPERTY宏来定义属性元数据和变量说明符。
```
UPROPERTY([specifier, specifier, ...], [meta(key=value, key=value, ...)])
Type VariableName;
```

下面是一个 UPROPERTY 宏的例子：
// 声明一个名为 "my_property" 的 UPROPERTY
```
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyProperties")
float my_property;
```
在这个例子中，我们声明了一个名为 "my_property" 的 UPROPERTY，它具有以下特性：
VisibleAnywhere：表示该属性在任何地方都是可见的。
BlueprintReadOnly：表示该属性在蓝图中只能被读取，不能被修改。
Category = "MyProperties"：表示该属性属于 "MyProperties" 类别。
通过在蓝图中引用这个属性，可以将其值与其他变量或操作相结合，以实现各种功能。例如：
```
float MyPropertyValue = GetFloatProperty("my_property");
```
这个例子中，我们通过 GetFloatProperty 函数获取 "my_property" 的值，并将其存储在变量 MyPropertyValue 中。然后，您可以根据需要使用这个值进行其他操作。


属性标签

效果

AdvancedDisplay

属性将被放置在其出现的任意面板的高级（下拉）部分中。

AssetRegistrySearchable

AssetRegistrySearchable 说明符说明此属性与其值将被自动添加到将此包含为成员变量的所有资源类实例的资源注册表。不可在结构体属性或参数上使用。

BlueprintAssignable

只能与组播委托共用。公开属性在蓝图中指定。

BlueprintAuthorityOnly

此属性必须为一个组播委托。在蓝图中，其只接受带 BlueprintAuthorityOnly 标签的事件。

BlueprintCallable

仅用于组播委托。应公开属性在蓝图代码中调用。

BlueprintGetter=GetterFunctionName

此属性指定一个自定义存取器函数。如此属性不带 BlueprintSetter 或 BlueprintReadWrite 标签，则其为隐式 BlueprintReadOnly。

BlueprintReadOnly

此属性可由蓝图读取，但不能被修改。此说明符与 BlueprintReadWrite 说明符不兼容。

BlueprintReadWrite

可从蓝图读取或写入此属性。此说明符与 BlueprintReadOnly 说明符不兼容。

BlueprintSetter=SetterFunctionName

此属性拥有一个自定义编译函数，被隐式标记为 BlueprintReadWrite。注意：必须对变异函数进行命名，并为相同类的一部分。

Category="TopCategory|SubCategory|..."

指定在蓝图编辑工具中显示时的属性类别。使用 | 运算符定义嵌套类目。

Config

此属性将被设为可配置。当前值可被存入与类相关的 .ini 文件中，创建后将被加载。无法在默认属性中给定一个值。暗示为 BlueprintReadOnly。

DuplicateTransient

说明在任意类型的复制中（复制/粘贴、二进制复制等），属性的值应被重设为类默认值。

EditAnywhere

说明此属性可通过属性窗口在原型和实例上进行编辑。此说明符与所有"可见"说明符均不兼容。

EditDefaultsOnly

说明此属性可通过属性窗口进行编辑，但只能在原型上进行。此说明符与所有"可见"说明符均不兼容。

EditFixedSize

只适用于动态数组。这能防止用户通过虚幻编辑器属性窗口修改数组长度。

EditInline

允许用户在虚幻编辑器的属性查看器中编辑此属性所引用的Object的属性（只适用于Object引用，包括Object引用的数组）。

EditInstanceOnly

说明此属性可通过属性窗口进行编辑，但只能在实例上进行，不能在原型上进行。此说明符与所有"可见"说明符均不兼容。

Export

只适用于Object属性（或Object数组）。说明Object被复制时（例如复制/粘贴操作）指定到此属性的Object应整体导出为一个子Object块，而非只是输出Object引用本身。

GlobalConfig

工作原理与 Config 相似，不同点是无法在子类中进行覆盖。无法在默认属性中对其给定一个值。暗示为 BlueprintReadOnly。

Instanced

仅限Object（UCLASS）属性。此类的一个实例创建时，其将被给定一个Object的特殊副本，指定到默认项中的此属性。用于实例化类默认属性中定义的子Object。暗示为 EditInline 和 Export。

Interp

说明值可随时间由Sequencer中的一个轨道驱动。

Localized

此属性的值将拥有一个定义的本地化值。多用于字符串。暗示为 ReadOnly。

Native

属性为本地：C++代码负责对其进行序列化并公开到垃圾回收。

NoClear

阻止从编辑器将此Object引用设为空。隐藏编辑器中的清除（和浏览）按钮。

NoExport

只适用于本地类。此属性不应包含在自动生成的类声明中。

NonPIEDuplicateTransient

属性将在复制中被重设为默认值，除非其被复制用于PIE会话。

NonTransactional

说明对此属性值的修改不会包含在编辑器的撤销/重新执行历史中。

NotReplicated

跳过复制。这只会应用到服务请求函数中的结构体成员和参数。

Replicated

属性应随网络进行复制。

ReplicatedUsing=FunctionName

ReplicatedUsing 说明符指定一个回调函数，其在属性通过网络更新时执行。

RepRetry

只适用于结构体属性。如果此属性未能完全发送（举例而言：Object引用尚无法通过网络进行序列化），则重新尝试对其的复制。对简单引用而言，这是默认选择；但对结构体而言，这会产生带宽开销，并非优选项。因此在指定此标签之前其均为禁用状态。

SaveGame

此说明符可简便地将域显式包含，用于属性关卡中的检查点/保存系统。应在作为游戏存档一部分的所有域上设置此标签，并使用代理归档器对其进行读写。

SerializeText

本地属性应被序列化为文本（ImportText、ExportText）。

SkipSerialization

此属性不会被序列化，但仍能导出为一个文本格式（例如用于复制/粘贴操作）。

SimpleDisplay

出现在 细节 面板中的可见或可编辑属性，无需打开"高级"部分即可见。

TextExportTransient

此属性将不会导出为一个文本格式（因此其无法用于复制/粘贴操作）。

Transient

属性为临时，意味着其无法被保存或加载。以此方法标记的属性将在加载时被零填充。

VisibleAnywhere

说明此属性在所有属性窗口中可见，但无法被编辑。此说明符与"Edit"说明符不兼容。

VisibleDefaultsOnly

说明此属性只在原型的属性窗口中可见，无法被编辑。此说明符与所有"Edit"说明符均不兼容。

VisibleInstanceOnly

说明此属性只在实例的属性窗口中可见（在原型属性窗口中不可见），无法被编辑。此说明符与所有"Edit"说明符均不兼容。

参考资料
https://docs.unrealengine.com/5.0/zh-CN/unreal-engine-uproperties/