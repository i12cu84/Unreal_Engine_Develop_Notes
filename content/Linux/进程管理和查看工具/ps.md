 `ps` 是一个常用的 Linux 和 Unix 系统命令，用于显示当前运行的进程。通过 `ps` 命令，用户可以了解系统当前运行的进程及其状态，例如运行的进程数量、进程ID、运行的命令等。这对于系统监控和故障排查非常有用。
基本的 `ps` 命令使用方法如下：
1. 显示所有当前运行的进程：
   ```
   ps
   ```
2. 显示所有当前运行的进程，并显示进程的详细信息，如进程ID、运行命令等：
   ```
   ps -e
   ```
3. 按照用户数显示进程：
   ```
   ps -u
   ```
4. 按照运行时间显示进程：
   ```
   ps -rt
   ```
5. 显示特定进程的详细信息：
   ```
   ps -fp 进程ID
   ```
6. 隐藏指定进程：
   ```
   ps -f -p 进程ID
   ```
其中，`-a` 表示显示所有进程，`-e` 表示显示详细信息，`-u` 表示按用户数排序，`-r` 表示按运行时间排序，`-f` 表示显示进程的进程ID和命令行。
此外，`ps` 命令还支持许多其他选项，如 `-o`（输出特定字段）、`-t`（显示线程信息）等。通过结合这些选项，用户可以根据需要定制 `ps` 命令的输出内容。