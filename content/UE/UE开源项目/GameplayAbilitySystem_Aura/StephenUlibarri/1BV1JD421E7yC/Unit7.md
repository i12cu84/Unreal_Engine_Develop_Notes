P1 Initalize Attribute from a Data Table 初始化属性方法
//Primary Attributes 主属性
UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Strength,Category="Primary Attributes")
FGameplayAttributeData Strength;
ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);

UFUNCTION()
//初始化属性
void OnRep_Strength(const FGameplayAttributeData& OldStrength)const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}
4:12