AI的行为树中Tasks->ResetPlayer节点可展开ReceiveExecute事件用于新建行为任务
Finish Execute即完成(退出该行为蓝图)

success (是否返回执行成功) -> 很重要的一点,若是没有设定,若是在Sequence(序列)执行的其中一步,则会直接跳过接下来的步骤,后续的序列行为都会跳过