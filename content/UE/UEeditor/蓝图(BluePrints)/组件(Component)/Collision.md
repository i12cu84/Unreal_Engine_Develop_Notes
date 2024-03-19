碰撞 Collision

Simulation Generates Hit Events -> 发生碰撞时是否发射"命中"事件

Phys Material Override ->

Generate Overlap Events ->

Can Character Step Up On ->


碰撞预设 ->

    Default：默认值

    Custom：自定义

    No Collision：无碰撞
    【自身视为WorldStatic】

    BlockAll：对所有类型的物体进行 区块碰撞
    【自身视为WorldStatic】

    OverlapAll：对所有类型的物体进行 重叠
    【自身视为WorldStatic】

    BlockAllDynamic：对所有类型的物体进行 区块碰撞
    【自身视为WorldDynamic】

    OverAllDynamic：对所有类型的物体进行 重叠
    【自身视为WorldDynamic】

    IgnoreOnlyPawn：对碰撞类型为（除了Pawn，Vehicle（载具）） 的物体进行 区块碰撞
    （Pawn，Vehicle（载具）进行忽视处理 ）
    【自身视为WorldDynamic】

    OverlapOnlyPawn：对碰撞类型为（除了Pawn，Vehicle） 的物体进行 区块碰撞
    （忽略Pawn，Vehicle（载具））
    （Camera进行忽视处理）
    【自身视为WorldDynamic】

    Pawn：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为Pawn】

    Spectator：对所有碰撞类型为 “WorldStatic” 的物体进行 区块碰撞
    （忽略其余的碰撞类型）
    【自身视为Pawn】

    CharacterMesh：对碰撞类型为（除了Pawn，Vehicle（载具）） 的物体进行 区块碰撞
    （忽略Pawn，Vehicle（载具））
    【自身视为Pawn】

    PhysicalBody：对所有碰撞类型的物体进行 区块碰撞
    【自身视为PhysicalBody】

    Destructible（可破坏物）：对所有碰撞类型的物体进行 区块碰撞
    【自身视为Destructible】

    InvisibleWall：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldStatic】

    InvisibleWallDynamic：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldDynamic】

    Trigger（触发器）：对所有碰撞类型的物体进行 区块碰撞
    （忽略物体的可见性）
    【自身视为WorldDynamic】

    Ragdoll（模拟骨架网格体组件）：对碰撞类型为（除了Pawn） 的物体进行 区块碰撞
    （忽略物体的可见性）
    （忽略Pawn）
    【自身视为PhysicalBody】

    Vehicle：对所有碰撞类型的物体进行 区块碰撞
    【自身视为Vehicle】

