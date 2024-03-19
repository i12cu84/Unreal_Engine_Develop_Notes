Set-ExecutionPolicy：用于设置执行策略，允许或禁止执行特定类型的代码。
Get-ChildItem：类似于CMD中的dir命令，用于遍历目录并显示子目录和文件。
Set-Item：用于修改文件或目录的属性，如权限、只读等。
Get-Item：用于获取文件或目录的属性，如权限、大小等。
Remove-Item：用于删除文件或目录。
Copy-Item：用于复制文件或目录。
Move-Item：用于移动文件或目录。
Rename-Item：用于重命名文件或目录。
Get-Process：用于获取系统中的进程信息。
Stop-Process：用于停止指定进程。
Start-Process：用于启动新进程。
Get-Service：用于获取系统中的服务信息。
Stop-Service：用于停止指定服务。
Start-Service：用于启动指定服务。
Set-Service：用于设置服务属性，如启动类型等。
Get-EventLog：用于获取系统事件日志。
Clear-EventLog：用于清除系统事件日志。
Set-EventLog：用于设置系统事件日志。
Import-Module：用于导入模块，以便使用模块中的命令和功能。
Export-Module：用于导出模块，以便在其他会话中使用。

 PowerShell 是 Windows 操作系统中一个强大的自动化工具和配置管理框架。它提供了一个命令行壳体和脚本语言，以帮助管理员管理 Windows 环境。下面是 PowerShell 的使用方法介绍：
### 打开 PowerShell
1. **启动 PowerShell：** 点击开始菜单，然后搜索“PowerShell”并选择打开。
2. **通过运行对话框打开：** 在运行对话框中输入 `powershell` 并回车。
### PowerShell 的基本概念
- **命令行和脚本：** PowerShell 允许用户在命令行中输入命令执行。
- **PS 命令：** 所有命令都以 `PS` 开头，表示当前是在 PowerShell 中执行命令。
- **命令别名：** 和 CMD 一样，PowerShell 允许定义别名以便于快速访问命令。
### 基本命令操作
- **文件和目录操作：** 使用 `Get-ChildItem` 命令来查看当前目录下的文件和子目录。
- **路径操作：** 使用 `cd` 命令切换目录，或使用 `Set-Location` 命令。
- **文件操作：** 使用 `New-Item` 创建新文件或目录，`Remove-Item` 删除文件或目录。
### 条件语句和循环
- **if 语句：** 用于根据条件执行不同的命令。
- **for 循环：** 用于执行一系列命令，直到条件不再满足。
- **while 循环：** 用于在条件为真的情况下持续执行命令。
### 功能增强
- **函数：** PowerShell 允许用户定义函数以重用代码。
- **模块：** 用于组织代码并可导入到 PowerShell 会话中。
- **脚本：** 编写复杂脚本来执行自动化任务。
### 获取帮助
- **帮助命令：** 使用 `Get-Help`，`Man` 或 `Help` 来获取命令帮助。
### 退出 PowerShell
- **退出命令：** 使用 `Exit` 命令退出 PowerShell 会话。
### 安全性和权限
- PowerShell 允许精细的权限控制，以执行特定操作。
- 使用 `RunAs` 或 `Start-Process` 来以不同用户身份执行命令。
### 结合其他工具
- PowerShell 支持各种 Windows 管理工具和命令行工具的集成。
### 学习资源
- 由于 PowerShell 具有强大的功能，建议查阅专业书籍或在线资源来深入学习。
通过这些基础知识和操作，用户可以开始利用 PowerShell 执行各种自动化任务，并提高工作效率。需要注意的是，PowerShell 的功能非常强大，适当的学习和练习是非常必要的。

 PowerShell 是一种命令行界面和脚本环境，用于管理和自动化 Windows 操作系统。它提供了许多命令，可用于执行各种操作，如管理文件和文件夹、管理网络连接、查看系统信息等。以下是一些常用的 PowerShell 命令：
1. Get-Command：列出所有可用的 PowerShell 命令。
2. Get-Help：获取有关特定命令的帮助信息。
3. Get-Process：查看当前运行的进程。
4. Get-Service：查看当前运行的服务。
5. Get-EventLog：查看系统事件日志。
6. Start-Service：启动一个服务。
7. Stop-Service：停止一个服务。
8. Restart-Service：重新启动一个服务。
9. New-Item：创建一个新文件或文件夹。
10. Copy-Item：复制文件或文件夹。
11. Move-Item：移动文件或文件夹。
12. Remove-Item：删除文件或文件夹。
13. Get-ChildItem：查看当前目录下的文件和子目录。
14. Set-Alias：给指定命令重命名。
15. Clear-Host：清屏。
16. help：获取帮助信息。
17. exit：退出 PowerShell。
这只是 PowerShell 命令的一小部分，您可以使用 "Get-Command" 命令来查看所有可用的命令。