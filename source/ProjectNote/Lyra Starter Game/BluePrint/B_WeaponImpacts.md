与武器有关的蓝图(应该是类似枪火特效的蓝图)

Fire ->
Sort Impact Arrays // 数组排序
-> 本地宏
Set Array Elem // 
```cpp
// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\KismetArrayLibrary.cpp
void UKismetArrayLibrary::Array_Set(const TArray<int32>& TargetArray, int32 Index, const int32& NewItem, bool bSizeToFit)
{
    //我们永远不应该碰到这些!它们是存根，以避免类上的NoExport。取而代之的是调用等价的通用*函数
	check(0);
}
```

Niagara Set Vector Array //
```cpp
// C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\FX\Niagara\Source\Niagara\Private\NiagaraDataInterfaceArrayFunctionLibrary.cpp
// 设置Niagara组件的数组向量数据
// @param NiagaraComponent 引用要设置的Niagara组件
// @param OverrideName 要覆盖的数组名称，若为空则使用默认名称
// @param ArrayData 要设置的数组数据，类型为FVector
void UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(UNiagaraComponent* NiagaraComponent, FName OverrideName, const TArray<FVector>& ArrayData)
{
	// 调用基类的SetNiagaraArray函数，传入FVector类型和对应的UNiagaraDataInterfaceArrayFloat3接口
	// 这样可以确保数据被正确地设置到Niagara组件的数组中
	SetNiagaraArray<FVector, UNiagaraDataInterfaceArrayFloat3>(NiagaraComponent, OverrideName, ArrayData);
}
```

Niagara Set Position Array //
```cpp
// C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\FX\Niagara\Source\Niagara\Private\NiagaraDataInterfaceArrayFunctionLibrary.cpp
// 设置Niagara组件的数组位置
// @param NiagaraComponent 引用要设置的Niagara组件
// @param OverrideName 要覆盖的数组名称，若为空则使用默认名称
// @param ArrayData 要设置的数组数据，类型为FVector
void UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayPosition(UNiagaraComponent* NiagaraComponent, FName OverrideName, const TArray<FVector>& ArrayData)
{
	// 获取LWC转换器实例
	// LWC转换器用于在world坐标和simulation坐标之间转换
	FNiagaraLWCConverter LwcConverter = GetLWCConverter(NiagaraComponent);
	// 创建一个用于存储转换后数据的数组
	// 数组的大小与输入数据相同，初始时未初始化
	TArray<FNiagaraPosition> ConvertedData;
	ConvertedData.SetNumUninitialized(ArrayData.Num());
	// 遍历输入的数组数据
	for (int i = 0; i < ArrayData.Num(); i++)
	{
		// 将world坐标转换为simulation坐标
		// 并存储在转换后的数据数组中
		ConvertedData[i] = LwcConverter.ConvertWorldToSimulationPosition(ArrayData[i]);
	}
	// 使用转换后的数据设置Niagara组件的数组位置
	// 此函数会根据传入的数组类型和组件接口来设置数据
	SetNiagaraArray<FNiagaraPosition, UNiagaraDataInterfaceArrayPosition>(NiagaraComponent, OverrideName, ConvertedData);
}
```

Set Niagara Varibale [Type]
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\FX\Niagara\Source\Niagara\Private\NiagaraComponent.cpp
// 设置Niagara组件的整型变量
// @param InVariableName 要设置的变量名称
// @param InValue 要设置的整型值
void UNiagaraComponent::SetVariableInt(FName InVariableName, int32 InValue)
{
	// 创建一个FNiagaraVariable对象，用于描述变量，其中包含变量的类型定义和名称
	const FNiagaraVariable VariableDesc(FNiagaraTypeDefinition::GetIntDef(), InVariableName);
	// 检查SystemInstanceController是否有效
	if (SystemInstanceController.IsValid())
	{
		// 如果有效，使用SystemInstanceController来延迟设置变量值
		SystemInstanceController->SetVariable_Deferred(InVariableName, InValue);
	}
	else
	{
		// 如果SystemInstanceController无效，使用OverrideParameters来立即设置变量值
		OverrideParameters.SetParameterValue(InValue, VariableDesc, true);
	}
	// #if WITH_EDITOR
	// 在编辑器模式下，设置参数的覆盖值
	// SetParameterOverride用于在编辑器中设置参数的值，以便在编辑器中查看和修改
#if WITH_EDITOR
	SetParameterOverride(VariableDesc, FNiagaraVariant(&InValue, sizeof(int32)));
#endif
}
```

Set Tick Behavior
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Plugins\FX\Niagara\Source\Niagara\Private\NiagaraComponent.cpp
// 设置Niagara组件的滴答行为
// @param NewTickBehavior 要设置的新的滴答行为枚举值
void UNiagaraComponent::SetTickBehavior(ENiagaraTickBehavior NewTickBehavior)
{
	// 将传入的新的滴答行为设置为当前组件的滴答行为
	TickBehavior = NewTickBehavior;
	// 检查SystemInstanceController是否有效
	if (SystemInstanceController.IsValid())
	{
		// 如果SystemInstanceController有效，调用其SetTickBehavior方法来应用新的滴答行为
		SystemInstanceController->SetTickBehavior(TickBehavior);
	}
	// 如果SystemInstanceController无效，则不执行任何操作，因为无法应用滴答行为
}
```