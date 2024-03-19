yum是一个在Fedora和RedHat以及SUSE中的Shell前端软件包管理器。它基于RPM包管理，能够从指定的服务器自动下载RPM包并且安装，可以自动处理依赖性关系，并且一次安装所有依赖的软件包，无须繁琐地一次次下载、安装。yum提供了查找、安装、删除某一个、一组甚至全部软件包的命令，而且命令简洁而又好记。以下是一些常用的yum命令：

1. 列出所有可更新的软件清单命令：`yum check-update`
2. 更新所有软件命令：`yum update`
3. 仅安装指定的软件命令：`yum install <package_name>`
4. 仅更新指定的软件命令：`yum update <package_name>`
5. 列出所有可安裝的软件清单命令：`yum list`
6. 删除软件包命令：`yum remove <package_name>`
7. 查找软件包命令：`yum search <keyword>`
8. 清除缓存命令: `yum clean packages`: 清除缓存目录下的软件包; `yum clean headers`: 清除缓存目录下的headers; `yum clean oldheaders`: 清除缓存目录下旧的headers; `yum clean`, `yum clean all (= yum clean packages; yum clean oldheaders)`: 清除缓存目录下的软件包及旧的headers。
