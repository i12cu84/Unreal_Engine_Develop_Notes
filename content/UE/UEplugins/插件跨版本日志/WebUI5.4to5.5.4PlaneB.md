# UnrealEditor.modules文件
BuildId改为37670630
不改会弹窗

# 存入插件
将插件文件夹放入(二选一)
``` 
C:\Program Files\Epic Games\UE_5.5\Engine\Plugins\Marketplace
[项目目录]\Plugins
```


注,如果放入引擎根目录会与Web browser插件产生冲突

# 启动项目启用插件

打开项目 启用 WebUI插件,

注意,记得删除.uproject
```
{
    "Name": "WebUI",
    "Enabled": true
}
```