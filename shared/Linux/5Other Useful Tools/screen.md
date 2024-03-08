 `screen` 是一个终端会话管理器，允许用户在单个终端窗口内创建多个终端会话。与 `tmux` 类似，`screen` 也支持多窗口、多会话管理，以及会话的保存和恢复等功能。
在 Linux 系统中，可以使用以下命令安装 `screen`：
- Ubuntu：`sudo apt-get install screen`
- RHEL 或 CentOS：`yum install screen`
使用 `screen` 的基本命令如下：
- 创建新的会话：`screen -S session_name`
- 进入已存在的会话：`screen -x session_name`
- 列出所有会话：`screen -ls`
- 退出会话：`exit` 或 `Ctrl + A + D`
- 新建窗口：`Ctrl + A + c`
- 在窗口间切换：`Ctrl + A + n`（前进）或 `Ctrl + A + p`（后退）
通过这些命令，您可以轻松地在 Linux 系统中管理和使用多个终端会话。