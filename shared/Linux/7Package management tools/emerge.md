emerge是Gentoo Linux中的一个命令行软件包管理器，它是Portage系统的命令行接口。您可以使用emerge来安装、更新和维护软件包。以下是一些常用的emerge命令：

1. 列出所有可更新的软件清单命令：`emerge --sync && emerge -avuDN world`
2. 仅安装指定的软件命令：`emerge <package_name>`
3. 仅更新指定的软件命令：`emerge -u <package_name>`
4. 列出所有可安装的软件清单命令：`emerge -s <keyword>`
5. 删除软件包命令：`emerge --unmerge <package_name>`
6. 查找软件包命令：`emerge -s <keyword>`
7. 清除缓存命令: `emerge --depclean`: 清除不再需要的软件包; `emerge --prune`: 清除不再需要的依赖项。
