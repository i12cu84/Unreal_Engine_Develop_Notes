# Add-Tag-plugins-for-Unreal-Engine

虚幻引擎5.2版

将文件放在项目目录Plugins中

这个插件将在“Build project”列中生成14个按钮

按钮功能按顺序排列

0：

向选定的目标添加一个Tags:
Action_Pullout
Action_Insert

1：

向选定的目标添加一个Tags:
Action_Screwout
Action_Screwin

2：

向选定的目标添加一个Tags:
Action_Fade
Action_Display

3：

记录您选择模型的UAID并将其应用于接下来的两个按钮
(如果选择“A”和“B”模型并按下按钮)

4：

将上一个按下按钮的模型的UAID添加到所选模型的Tag中:
Constraint束+[A模型的UAID;B模型的UAID]

5：

在“3”按钮所选模型的UAID附加到当前所选模型Tag上:
选择模型原有将添加在输入框中输入的:
Constraint+[C模型UAID]
这个将添加在输入框中输入的将是:
Constraint+[A型UAID;B型UAID;C型UAID]

6：

按下后，会弹出一个窗口。
分别输入“1”、“2”、“3”、“4”的内容，按“Enter”。
所选模型将被标记为:
UnloadStep ^ [1] + [2] + [3] + [4]

7：

同上，但格式将变成
LoadedStep ^ [1] + [2] + [3] + [4]

8：

同上，但格式将变成
ChangeStep ^ [1] + [2] + [3] + [4]

9：

向选定的目标添加一个Tags:
Name_xxx
Tip_xxx
Durab_xxx

10：

按下后，会弹出一个输入框。
输入内容后，按“Enter”，
将输入框中输入的内容添加到选择的模型将添加在输入框中输入的中

11:

将所选模型的Tag导出到项目的根目录
导出文件的格式为:
世界大纲中的名称-模型的UAID -模型的将添加在输入框中输入的
导出的文件将部分按时间命名，因此您不必担心覆盖文件

12：

将场景中所有模型的Tag导出到项目根目录
导出格式同上
导出的文件将部分按时间命名，因此您不必担心覆盖文件

13：

读取项目根目录的“input.csv”文件，为项目中所有模型导入Tag
只会替换csv中存在的模型的Tag;如果它不存在，什么都不会改变