//C:\Users\chru\Desktop\Lyra\Source\LyraGame\Settings\LyraSettingsLocal.h

//Lyra中的输入系统 https://zhuanlan.zhihu.com/p/608528503

//line 341
//////////////////////////////////////////////////////////////////
	// Keybindings
public:


	// Sets the controller representation to use, a single platform might support multiple kinds of controllers.  For
	// example, Win64 games could be played with both an XBox or Playstation controller.
	/*设置要使用的控制器表示，单个平台可能支持多种类型的控制器。例如，Win64游戏可以同时使用XBox或Playstation控制器。*/
	UFUNCTION()
	void SetControllerPlatform(const FName InControllerPlatform);
	UFUNCTION()
	FName GetControllerPlatform() const;

	DECLARE_EVENT_OneParam(ULyraSettingsLocal, FInputConfigDelegate, const FLoadedMappableConfigPair& /*Config*/);

	/** Delegate called when a new input config has been registered */
	FInputConfigDelegate OnInputConfigRegistered;

	/** Delegate called when a registered input config has been activated */
	FInputConfigDelegate OnInputConfigActivated;
	
	/** Delegate called when a registered input config has been deactivate */
	FInputConfigDelegate OnInputConfigDeactivated;
	
	//用给定的输入配置注册给定的输入配置，使其对玩家可用。
	/** Register the given input config with the settings to make it available to the player. */
	void RegisterInputConfig(ECommonInputType Type, const UPlayerMappableInputConfig* NewConfig, const bool bIsActive);
	
	/** Unregister the given input config. Returns the number of configs removed. */
	int32 UnregisterInputConfig(const UPlayerMappableInputConfig* ConfigToRemove);

	/** Get an input config with a certain name. If the config doesn't exist then nullptr will be returned. */
	UFUNCTION(BlueprintCallable)
	const UPlayerMappableInputConfig* GetInputConfigByName(FName ConfigName) const;

	//获取所有当前注册并激活的IMC
	/** Get all currently registered input configs */
	const TArray<FLoadedMappableConfigPair>& GetAllRegisteredInputConfigs() const { return RegisteredInputConfigs; }

	/**
	 * Get all registered input configs that match the input type.
	 * 
	 * @param Type		The type of config to get, ECommonInputType::Count will include all configs.
	 * @param OutArray	Array to be populated with the current registered input configs that match the type
	 */
	void GetRegisteredInputConfigsOfType(ECommonInputType Type, OUT TArray<FLoadedMappableConfigPair>& OutArray) const;

	/**
	 * Returns the display name of any actions with that key bound to it
	 * 
	 * @param InKey The key to check for current mappings of
	 * @param OutActionNames Array to store display names of actions of bound keys
	 */
	void GetAllMappingNamesFromKey(const FKey InKey, TArray<FName>& OutActionNames);

	/**
	 * 将给定的键盘设置映射到新键
	 *
	 * @param mappingname 映射的名字，比如MoveForward，Jump
	 * @param newkey NewKey就是新的按键，如键盘字母键，鼠标左右键
	 * @param LocalPlayer 重置按键绑定的本地玩家
	 */
	void AddOrUpdateCustomKeyboardBindings(const FName MappingName, const FKey NewKey, ULyraLocalPlayer* LocalPlayer);

	/**
	 * Resets keybinding to its default value in its input mapping context 
	 * 
	 * @param MappingName	The name of the FPlayerMappableKeyOptions that you would like to change
	 * @param LocalPlayer   local player to reset the keybinding on
	 */
	void ResetKeybindingToDefault(const FName MappingName, ULyraLocalPlayer* LocalPlayer);

	/** Resets all keybindings to their default value in their input mapping context
	 * @param LocalPlayer   local player to reset the keybinding on
	 */
	void ResetKeybindingsToDefault(ULyraLocalPlayer* LocalPlayer);

	//获得玩家的自定义映射按键
	const TMap<FName, FKey>& GetCustomPlayerInputConfig() const { return CustomKeyboardConfig; }

private:
	void LoadUserControlBusMix();

	UPROPERTY(Config)
	float OverallVolume = 1.0f;
	UPROPERTY(Config)
	float MusicVolume = 1.0f;
	UPROPERTY(Config)
	float SoundFXVolume = 1.0f;
	UPROPERTY(Config)
	float DialogueVolume = 1.0f;
	UPROPERTY(Config)
	float VoiceChatVolume = 1.0f;

	UPROPERTY(Transient)
	TMap<FName/*SoundClassName*/, TObjectPtr<USoundControlBus>> ControlBusMap;

	UPROPERTY(Transient)
	TObjectPtr<USoundControlBusMix> ControlBusMix = nullptr;

	UPROPERTY(Transient)
	bool bSoundControlBusMixLoaded;

	UPROPERTY(Config)
	float SafeZoneScale = -1;

	/**
	 * The name of the controller the player is using.  This is maps to the name of a UCommonInputBaseControllerData
	 * that is available on this current platform.  The gamepad data are registered per platform, you'll find them
	 * in <Platform>Game.ini files listed under +ControllerData=...
	 */
	UPROPERTY(Config)
	FName ControllerPlatform;

	UPROPERTY(Config)
	FName ControllerPreset = TEXT("Default");

	/** The name of the current input config that the user has selected. */
	//默认情况InputConfigName为"Default"，当你更新了键位，会更换为"Custom"，并按照名字和键位的映射关系放入CustomKeyboardConfig中，这里就对应上了。
	UPROPERTY(Config)
	FName InputConfigName = TEXT("Default");
	
	/**
	 * Array of currently registered input configs. This is populated by game feature plugins
	 * 当前注册的输入配置的数组。这是由游戏功能插件填充。
	 * @see UGameFeatureAction_AddInputConfig
	 */
	UPROPERTY(VisibleAnywhere)
	TArray<FLoadedMappableConfigPair> RegisteredInputConfigs;
	
	/** Array of custom key mappings that have been set by the player. Empty by default. */
	//由玩家设置的自定义键映射数组。默认为空。
	UPROPERTY(Config)
	TMap<FName, FKey> CustomKeyboardConfig;