
.uprojecct 右键内容:
Launch Game -> 创建一个游戏程序(在上一次构建之后的游戏,类似于项目exe执行后的效果)
Generate Visual Studio Project Files -> 构建vs工程代码
Switch Unreal Engine Version -> 选择虚幻打开的版本([不可逆]只能向上选择版本,若启用注意备份)

压缩工程文件的方式:
-> .vs/Saved/Intermediate 三大缓存文件删除
-> 迁移到新的目录后
->  .uprojecct 右键 
-> Generate Visual Studio Project Files (会加载缓存内容)