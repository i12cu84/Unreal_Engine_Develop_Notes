以作项目中语言切换映射使用

[详情介绍](https://blog.csdn.net/chai_tian/article/details/133752582)

1.
本地化控制板 -> 编译文本 -> LogLiveCoding: Display: Waiting for server 无后续反应问题

编辑器偏好设置 -> 启用实时代码编写(去掉勾)

---

2.
本地化控制板产生(状态)冲突,出现了哈希列表错误,例如
```
 - 03E4BC1F466CC72021629EA59F265A81 
	/Game/Hyper/UI/Widgets/Specific/Attribute/Active_State_effects/UI_Active_Effect_Slot.UI_Active_Effect_Slot_C:Set_Values [Script Bytecode] - "Healthy" 
	/Game/Hyper/UI/Widgets/Specific/Attribute/AttributeList/UI_Attribute_Row.UI_Attribute_Row_C:ExecuteUbergraph_UI_Attribute_Row [Script Bytecode] - "Character Level" 
	/Game/Hyper/UI/Widgets/Specific/Inventory/SubWidgets/Tooltip/UI_ToolTip_Row.UI_ToolTip_Row_C:ExecuteUbergraph_UI_ToolTip_Row [Script Bytecode] - "Armor" 
```
起因是复制了赋值节点之后,连带着把节点信息中的哈希内容也复制过来了,由于在不同蓝图中,运行测试的时候并没有发现异常,但在启用文本转化的时候会发现出现问题了!

重新将重叠的蓝图节点删除,(注意,不要再复制节点了!)然后重新输入新建蓝图节点即可解决

3.
文本无法被收集的时候,可以对对应蓝图创建类似switch的sttring枚举(然后使用"文本"类型来赋值,有一定概率会失败,可以多尝试收集文本,倘若仍旧失败,可以尝试使用"Make Literal Text"节点)

