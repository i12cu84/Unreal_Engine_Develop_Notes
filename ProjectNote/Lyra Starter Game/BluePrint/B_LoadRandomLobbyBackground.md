
ShowLoadingScreen ->
Create Loading Screen Process Task
```cpp
//C:\Users\chru\Desktop\Lyra\Plugins\CommonLoadingScreen\Source\CommonLoadingScreen\Public\LoadingProcessTask.cpp
/*static*/ ULoadingProcessTask* ULoadingProcessTask::CreateLoadingScreenProcessTask(UObject* WorldContextObject, const FString& ShowLoadingScreenReason)
{
	// 从 WorldContextObject 获取当前世界
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	// 如果世界存在，获取游戏实例
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	// 如果游戏实例存在，获取加载屏幕管理器
	ULoadingScreenManager* LoadingScreenManager = GameInstance ? GameInstance->GetSubsystem<ULoadingScreenManager>() : nullptr;

	// 如果加载屏幕管理器存在
	if (LoadingScreenManager)
	{
		// 在加载屏幕管理器中创建一个新的加载任务对象
		ULoadingProcessTask* NewLoadingTask = NewObject<ULoadingProcessTask>(LoadingScreenManager);
		// 设置显示加载屏幕的原因
		NewLoadingTask->SetShowLoadingScreenReason(ShowLoadingScreenReason);
		// 将新的加载任务注册到加载屏幕管理器中
		LoadingScreenManager->RegisterLoadingProcessor(NewLoadingTask);
		// 返回新的加载任务对象
		return NewLoadingTask;
	}

	// 如果加载屏幕管理器不存在，返回空指针
	return nullptr;
}
```

HideLoadingScreen ->
Unregister
```cpp
//C:\Users\chru\Desktop\Lyra\Plugins\CommonLoadingScreen\Source\CommonLoadingScreen\Public\LoadingProcessTask.cpp
// ULoadingProcessTask 是一个用于管理加载屏幕过程的任务类
// Unregister 方法用于从加载屏幕管理器中注销当前的任务
void ULoadingProcessTask::Unregister()
{
	// 将当前任务的 outer 指针向下转型为 ULoadingScreenManager 类型
	// 在 Unreal Engine 中，每个任务都是嵌入在某个管理器中的，这里的 outer 指针指向的就是管理器
	ULoadingScreenManager* LoadingScreenManager = Cast<ULoadingScreenManager>(GetOuter());
	// 如果管理器不为空，调用其 UnregisterLoadingProcessor 方法来注销当前任务
	// 这样做可以确保当前任务不再被加载屏幕管理器所管理，也不会被执行
	if (LoadingScreenManager)
	{
		LoadingScreenManager->UnregisterLoadingProcessor(this);
	}
}
```