激活组件

```
// C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\Engine\Private\Components\ActorComponent.cpp
void UActorComponent::Activate(bool bReset)
{
	if (bReset || ShouldActivate()==true)
	{
		SetComponentTickEnabled(true);
		SetActiveFlag(true);

		OnComponentActivated.Broadcast(this, bReset);
	}
}
```