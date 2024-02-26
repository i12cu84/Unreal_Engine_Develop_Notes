
Event Anim Motion Effect ->
Get Surface Type
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\GameplayStatics.cpp
// 此函数用于获取碰撞检测中的表面类型
EPhysicalSurface UGameplayStatics::GetSurfaceType(const struct FHitResult& Hit)
{
	// 从碰撞结果中获取物理材质
	UPhysicalMaterial* const HitPhysMat = Hit.PhysMaterial.Get();
	// 使用物理材质确定表面类型
	return UPhysicalMaterial::DetermineSurfaceType( HitPhysMat );
}
```

Get Socket Transform
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\Components\SceneComponent.cpp
// 获取场景组件的套接字变换
FTransform USceneComponent::GetSocketTransform(FName SocketName, ERelativeTransformSpace TransformSpace) const
{
	// 根据指定的变换空间来确定如何获取套接字的变换
	switch(TransformSpace)
	{
		// 当变换空间为演员空间时
		case RTS_Actor:
		{
			// 获取组件的变换，并相对于演员的变换计算相对变换
			return GetComponentTransform().GetRelativeTransform( GetOwner()->GetTransform() );
			break;
		}
		// 当变换空间为组件空间或父骨骼空间时
		case RTS_Component:
		case RTS_ParentBoneSpace:
		{
			// 返回单位变换矩阵，即不进行任何变换
			return FTransform::Identity;
		}
		// 如果变换空间不是上述情况，则默认为组件空间
		default:
		{
			// 直接返回组件的变换
			return GetComponentTransform();
		}
	}
}
```

TransformDirection
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Classes\Kismet\KismetMathLibrary.inl
// KISMET_MATH_INLINE 宏用于指示这段代码应该被内联，以减少函数调用的开销
// UKismetMathLibrary 是一个提供数学运算功能的类
// TransformDirection 函数接受一个变换矩阵和一个方向向量，返回该方向向量在变换后的结果
FVector UKismetMathLibrary::TransformDirection(const FTransform& T, FVector Direction)
{
	// 使用变换矩阵 T 对方向向量 Direction 进行变换，但不考虑缩放因子
	// T.TransformVectorNoScale 方法应用了变换矩阵的旋转和平移部分，但没有应用缩放
	// 这意味着方向向量会被旋转和平移，但其长度（即缩放）保持不变
	return T.TransformVectorNoScale(Direction);
}
```

Make Rotation From Axes
```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\KismetMathLibrary.cpp
// UKismetMathLibrary 是一个提供数学运算功能的类
// MakeRotationFromAxes 函数接受三个向量：前进方向（Forward）、右方向（Right）和上方向（Up）
// 这些向量定义了一个三维空间中的坐标系
// 函数的目的是从这些向量创建一个旋转矩阵，并返回对应的旋转器（Rotator）
FRotator UKismetMathLibrary::MakeRotationFromAxes(FVector Forward, FVector Right, FVector Up)
{
	// 对输入的向量进行归一化，以确保它们是单位向量
	// 这意味着向量的长度为1，方向不变
	Forward.Normalize();
	Right.Normalize();
	Up.Normalize();

	// 创建一个旋转矩阵，其列向量由归一化的 Forward、Right 和 Up 向量组成
	// 第四个列向量是 FVector::ZeroVector，它表示原点
	// 这个旋转矩阵定义了一个坐标系，其中 Forward、Right 和 Up 分别是 x、y 和 z 轴
	FMatrix RotMatrix(Forward, Right, Up, FVector::ZeroVector);

	// 从旋转矩阵中提取旋转器（Rotator）
	// 旋转器是一个表示旋转轴和旋转角度的三维向量
	// 它可以用于旋转其他向量或对象
	return RotMatrix.Rotator();
}
```