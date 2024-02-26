//C:\Users\chru\Desktop\Lyra\Source\LyraGame\Character\LyraHeroComponent.cpp

//Lyra中的输入系统 https://zhuanlan.zhihu.com/p/608528503

//224 Line
//初始化玩家输入
void ULyraHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}
	//get控制器
	const APlayerController* PC = GetController<APlayerController>();
	check(PC);
	//get玩家
	const ULyraLocalPlayer* LP = Cast<ULyraLocalPlayer>(PC->GetLocalPlayer());
	check(LP);
	//获取增强输入本地玩家子系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	//清空所有映射
	Subsystem->ClearAllMappings();
	//LyraPawnExtensionComponent:Pawn拓展组件：为所有Pawn添加功能的组件，以便它可以用于角色/车辆/等。协调其他组件的初始化。
	/*
	获取在ULyraPawnExtensionComponent上的ULyraPawnData，ULyraPawnData中有配置的ULyraInputConfig，
	我们即将绑定代码逻辑的IA都配置在ULyraInputConfig中。
	*/
	if (const ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{	
			//取得输入配置
			//这个InputConfig即DT中存放所有键值对的DataAsset
			if (const ULyraInputConfig* InputConfig = PawnData->InputConfig)
			{
				const FLyraGameplayTags& GameplayTags = FLyraGameplayTags::Get();
	
				// Register any default input configs with the settings so that they will be applied to the player during AddInputMappings。
				// 使用settings注册任意默认的输入配置，以便使得其能在AddInputMapping过程中被应用到玩家。
				for (const FMappableConfigPair& Pair : DefaultInputConfigs)
				{
					if (Pair.bShouldActivateAutomatically && Pair.CanBeActivated())
					{
						FModifyContextOptions Options = {};
						Options.bIgnoreAllPressedKeysUntilRelease = false;
						// Actually add the config to the local player	
						//实际添加配置给本地Player
						Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);	
					}
				}
				
				//加载已经激活的InputConfig,InputConfig就是按键和InputAction的映射表
				ULyraInputComponent* LyraIC = CastChecked<ULyraInputComponent>(PlayerInputComponent);
				LyraIC->AddInputMappings(InputConfig, Subsystem);

				//增强输入的绑定函数
				TArray<uint32> BindHandles;
				LyraIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, /*bLogIfNotFound=*/ false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, /*bLogIfNotFound=*/ false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, /*bLogIfNotFound=*/ false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, /*bLogIfNotFound=*/ false);
				LyraIC->BindNativeAction(InputConfig, GameplayTags.InputTag_AutoRun, ETriggerEvent::Triggered, this, &ThisClass::Input_AutoRun, /*bLogIfNotFound=*/ false);
			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}
 
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}