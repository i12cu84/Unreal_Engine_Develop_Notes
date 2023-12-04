 tmux（Terminal Multiplexer）是一个终端多路复用器，类似于 GNU Screen，它允许用户在单个终端窗口内创建多个终端会话。tmux 可以为每个会话分配不同的键盘快捷键，使您可以轻松地在不同的会话之间切换。此外，tmux 还支持上下分屏、左右分屏以及会话的保存和恢复等功能。
在 Linux 系统中，可以使用以下命令安装 tmux：
- Ubuntu：`sudo apt-get install tmux`
- RHEL 或 CentOS：`yum install tmux`
使用 tmux 的基本命令如下：
- 创建新的会话：`tmux new -s session_name`
- 进入已存在的会话：`tmux attach` 或 `tmux attach-session`
- 列出所有会话：`tmux ls`
- 退出会话：`tmux exit` 或 `tmux detach`
- 分屏：使用 `Ctrl + Shift +上下左右` 进行上下分屏或左右分屏
通过这些命令，您可以轻松地在 Linux 系统中管理和使用多个终端会话。