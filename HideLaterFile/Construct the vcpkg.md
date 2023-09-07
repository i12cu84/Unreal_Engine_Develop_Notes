vcpkg ulr:https://github.com/microsoft/vcpkg/tree/master

这是一个用于管理C++软件包的软件包管理器。

需要准备的东西有:
自身windows 环境
[git](https://git-scm.com/download/win)
vs 2015及以上

在所需安装的vcpkg目录下 右键"Open git Bash here"
依次输入命令行

```
    git clone https://github.com/microsoft/vcpkg
    .\vcpkg\bootstrap-vcpkg.bat

    第一句是拉取外部库vcpkg 到本地(类似于下载安装包)
    第二句是运行本地bat文件一键部署vcpkg(类似于安装软件)
```

随后

win+R 输入sysdm.cpl 找到 高级 环境变量

在Path中填写vcpkg的根目录即可完成功能部署

测试: win+R 输入cmd 输入vcpkg --help 若有提示信息则成功