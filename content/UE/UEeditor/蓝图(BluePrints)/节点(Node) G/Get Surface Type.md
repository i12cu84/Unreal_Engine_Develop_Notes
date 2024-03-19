获取表面类型 返回给定命中的 EPhysicalSurface 类型

```cpp
//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\GameplayStatics.cpp
// 获取碰撞命中结果的物理表面类型
EPhysicalSurface UGameplayStatics::GetSurfaceType(const struct FHitResult& Hit)
{
	// 从命中结果中获取物理材质
	UPhysicalMaterial* const HitPhysMat = Hit.PhysMaterial.Get();
	// 使用物理材质来确定表面类型
	return UPhysicalMaterial::DetermineSurfaceType( HitPhysMat );
}
```
