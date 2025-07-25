兼容Hyper的AI人物出现崩溃
```
LoginId:09a97c9641738214a0680484b0622337
EpicAccountId:d76460e405eb4634b9e1d235aae2e93b

Assertion failed: OutDurationPerBone.Num() == NumSkeletonBones [File:D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\BlendProfile.cpp] [Line: 268]

UnrealEditor_Engine!UBlendProfile::FillSkeletonBoneDurationsArray() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\BlendProfile.cpp:268]
UnrealEditor_Engine!FAnimNode_Inertialization::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNode_Inertialization.cpp:271]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_AnimGraphRuntime!FAnimNode_RotateRootBone::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\AnimNodes\AnimNode_RotateRootBone.cpp:50]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FAnimNode_SaveCachedPose::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNode_SaveCachedPose.cpp:76]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FAnimNode_LinkedInputPose::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNode_LinkedInputPose.cpp:49]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FAnimNode_ConvertLocalToComponentSpace::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeSpaceConversions.cpp:91]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentPose_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:112]
UnrealEditor_AnimGraphRuntime!FAnimNode_SkeletalControlBase::EvaluateComponentSpace_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\BoneControllers\AnimNode_SkeletalControlBase.cpp:130]
UnrealEditor_Engine!FComponentSpacePoseLink::EvaluateComponentSpace() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:468]
UnrealEditor_Engine!FAnimNode_ConvertComponentToLocalSpace::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeSpaceConversions.cpp:40]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FAnimInstanceProxy::EvaluateAnimationNode_WithRoot() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimInstanceProxy.cpp:1420]
UnrealEditor_Engine!FAnimInstanceProxy::EvaluateAnimation_WithRoot() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimInstanceProxy.cpp:1341]
UnrealEditor_Engine!FAnimNode_LinkedAnimGraph::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNode_LinkedAnimGraph.cpp:162]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_ControlRig!FAnimNode_ControlRigBase::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Plugins\Animation\ControlRig\Source\ControlRig\Private\AnimNode_ControlRigBase.cpp:460]
UnrealEditor_ControlRig!FAnimNode_ControlRig::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Plugins\Animation\ControlRig\Source\ControlRig\Private\AnimNode_ControlRig.cpp:194]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_AnimGraphRuntime!FAnimNode_BlendListBase::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\AnimNodes\AnimNode_BlendListBase.cpp:287]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_AnimGraphRuntime!FAnimNode_BlendListBase::Evaluate_AnyThread() [D:\build\++UE5\Sync\Engine\Source\Runtime\AnimGraphRuntime\Private\AnimNodes\AnimNode_BlendListBase.cpp:287]
UnrealEditor_Engine!FPoseLink::Evaluate() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimNodeBase.cpp:396]
UnrealEditor_Engine!FAnimInstanceProxy::EvaluateAnimationNode_WithRoot() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimInstanceProxy.cpp:1420]
UnrealEditor_Engine!FAnimInstanceProxy::EvaluateAnimation_WithRoot() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimInstanceProxy.cpp:1341]
UnrealEditor_Engine!UAnimInstance::ParallelEvaluateAnimation() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Animation\AnimInstance.cpp:826]
UnrealEditor_Engine!USkeletalMeshComponent::EvaluateAnimation() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Components\SkeletalMeshComponent.cpp:1982]
UnrealEditor_Engine!USkeletalMeshComponent::PerformAnimationProcessing() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Components\SkeletalMeshComponent.cpp:2074]
UnrealEditor_Engine!USkeletalMeshComponent::ParallelAnimationEvaluation() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Components\SkeletalMeshComponent.cpp:4017]
UnrealEditor_Engine!FParallelAnimationEvaluationTask::DoTask() [D:\build\++UE5\Sync\Engine\Source\Runtime\Engine\Private\Components\SkeletalMeshComponent.cpp:149]
UnrealEditor_Engine!TGraphTask<FParallelAnimationEvaluationTask>::ExecuteTask() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Public\Async\TaskGraphInterfaces.h:1310]
UnrealEditor_Core!<lambda_17c904c32264d0348d15245fba0e1bff>::operator()() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Public\Async\Fundamental\Task.h:499]
UnrealEditor_Core!LowLevelTasks::TTaskDelegate<LowLevelTasks::FTask * __cdecl(bool),48>::TTaskDelegateImpl<<lambda_17c904c32264d0348d15245fba0e1bff>,0>::CallAndMove() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Public\Async\Fundamental\TaskDelegate.h:171]
UnrealEditor_Core!LowLevelTasks::FTask::ExecuteTask() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Public\Async\Fundamental\Task.h:627]
UnrealEditor_Core!LowLevelTasks::FScheduler::ExecuteTask() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Private\Async\Fundamental\Scheduler.cpp:150]
UnrealEditor_Core!LowLevelTasks::FScheduler::TryExecuteTaskFrom<LowLevelTasks::TLocalQueueRegistry<1024>::TLocalQueue,&LowLevelTasks::TLocalQueueRegistry<1024>::TLocalQueue::DequeueGlobal,0>() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Private\Async\Fundamental\Scheduler.cpp:350]
UnrealEditor_Core!LowLevelTasks::FScheduler::WorkerMain() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Private\Async\Fundamental\Scheduler.cpp:378]
UnrealEditor_Core!UE::Core::Private::Function::TFunctionRefCaller<<lambda_be2218a0adc66e92e8734764b1b5dd37>,void __cdecl(void)>::Call() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Public\Templates\Function.h:475]
UnrealEditor_Core!FThreadImpl::Run() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Private\HAL\Thread.cpp:67]
UnrealEditor_Core!FRunnableThreadWin::Run() [D:\build\++UE5\Sync\Engine\Source\Runtime\Core\Private\Windows\WindowsRunnableThread.cpp:149]
```
删除骨骼,重新以UE5骨骼绑定

后续发现这样还是会报错以下问题

---

```
视口调试,弹出报错日志:

骨骼 SK_Mannerquin is missing bones that SkeletalMesh [BP_xxxx(相关骨骼网格体)] needs.They will be added now. Please save the Skeleton!
```

只能回归原有骨骼网格体,随后在打包的时候不再出现上述的崩溃问题(调试的时候还是会出现崩溃闪退,因为这是cpp程序的断言报错)