老程序员解 bug 有哪些通用套路？

linux上的一些经验

先看dmsg(诊断系统故障)，程序是崩溃还是oom，同时看看当时有没有硬件和内核告警，比如磁盘满。

找找core文件放哪里了，立即备份core文件，日志和程序binary和动态库。

有[zabbix](https://www.zabbix.com/documentation/3.4/zh/manual)或[falcon](http://book.open-falcon.com/zh_0_2/dev/support_grafana.html)(监控告警系统)之类的，把出问题当时的cpu io net 内存的监控数据备份下来。

如果挂了debugfs(内核开发人员向用户空间提供信息的一种简单方法)的信号监控，记录下当时进程间信号通信情况，搞不好是谁手贱帮你把进程kill了，或者shell退出时帮你杀了。

gdb(GNU symbolic debugger 程序调试器)，要会用脚本，用脚本在core中帮助排查复杂数据结构。

make(构建自动化工具)时记得把git hash和编译时间写到程序中，集中测试时频繁更新程序，搞不清出代码版本是很头痛的。

nm(文件分析工具)链接失败的问题一般用nm看一下就能知道原因。

为代码封装一个方便打印backtrace(嵌入式C代码调试利器)的宏或函数，只打印地址即可，打函数名代价大又麻烦，打出来的地址用空格分隔，这样多个地址可以直接拷贝给addr2line(将函数地址解析为函数名)来看函数名。

怀疑编译优化有问题，就用objdump(反汇编命令)看看，我遇到过编译优化出死循环的情况。

如果出问题时进程还活着，那得仔细看看/proc(虚拟文件系统)下的东西，fd(file descriptor 文件描述符,用于表示打开的文件在内核中的索引)、vma(Virtual Memory Area,用户进程拥有用户空间的地址)、环境变量。另外如果你不小心删了日志或其他文件，进程未关闭文件的话，可以用文件描述符找回来。

netstat(网络状态 显示各种网络相关信息的神器工具)看网络链接的状态，监听端口，进出队列长度，留意下time wait,close wait,sendq,recvq，也许会有惊喜。

TIME_WAIT 状态表示套接字连接已关闭，但客户端仍在等待确认。这种情况通常发生在客户端主动关闭连接时。为确保连接安全关闭，客户端需要等待一段时间，以确保服务器接收到关闭请求并完成相关清理工作。在 TIME_WAIT 状态下，客户端不能再次发送数据。以下是一个特殊情况：
当服务器在处理大量并发连接时，可能导致 TIME_WAIT 队列空间不足。为解决这一问题，可以调整内核参数 /proc/sys/net/ipv4/tcp_tw_reuse 和 /proc/sys/net/ipv4/tcp_tw_max，以增加 TIME_WAIT 队列的大小。

CLOSE_WAIT 状态表示服务器端已收到客户端的关闭请求，但服务器仍在等待关闭相关的资源（如缓冲区、文件描述符等）。在 CLOSE_WAIT 状态下，服务器不能接收新的数据，但可以发送数据。以下是一个特殊情况：
当服务器在处理大量并发连接时，可能导致 CLOSE_WAIT 队列空间不足。为解决这一问题，可以调整内核参数 /proc/sys/net/ipv4/tcp_max_tw_buckets，以增加 CLOSE_WAIT 队列的大小。

sendq 和 recvq 分别表示发送和接收数据缓冲区的大小。当发送或接收缓冲区满时，套接字会进入阻塞状态，直到缓冲区有空间可用。以下是一些特殊情况：
发送队列满：当发送队列满时，新的数据包无法发送，可能导致连接中断。解决方法是增加发送缓冲区大小，或调整内核参数 /proc/sys/net/ipv4/tcp_sndbuf 和 /proc/sys/net/ipv4/tcp_rcvbuf，以增加发送和接收缓冲区的大小。
接收队列满：当接收队列满时，服务器无法接收新的数据包。这可能导致数据包被丢弃，从而影响服务质量。解决方法是增加接收缓冲区大小，或调整内核参数 /proc/sys/net/ipv4/tcp_sndbuf 和 /proc/sys/net/ipv4/tcp_rcvbuf，以增加发送和接收缓冲区的大小。

lsof(list open files 查看当前系统上打开的文件和进程的命令行工具)看看进程加载了什么位置的动态库，也许有新发现。

/sys(内核动态生成的虚拟数据,系统设备信息,系统内核参数,系统服务,系统事件日志,其他系统信息)下的系统配置，检查下io调度器，ssd一般都用noop，其他调度器可能影响性能。

lspci(List PCI Devices用于查询计算机上所有 PCI 设备信息的命令)检查raid卡型号，lsi芯片的话，用megacli64来查看和修改配置，检查下你的raid缓存配置。

sysctl(用于管理系统内核参数和系统监控的命令)看看系统配置，重点关注tcp缓冲区和sock链接复用的配置，默认的缓冲区大小可能不能发挥万兆的能力。

perf(用于性能分析的工具,可以用于检测和诊断各种性能问题，如 CPU 缓存缺失、内存访问延迟、磁盘 I/O 瓶颈等)是看性能问题的神器，特别矬的问题用pstack抓几下也能看出来。

irqbalance(模块,用于自动平衡处理器中断请求（IRQ）的分配)是坑，一般都关掉，自己把中断只分配到3-4个core上可以发挥更好的万兆网卡性能。所以要留意/proc下的中断统计。

大内存机器注意，glibc(全局内存分配器)默认配置，mmap超过一定数量后可能都走sbrk了，已经free的内存可能碎片化无法还给系统也不能重用，自己管理内存的话一般都把mmap的大小和个数都调大，避免走sbrk。所以看/proc下的虚存使用情况很必要。

怀疑网络或磁盘问题，用iperf(测量互联网端到端带宽和延迟的命令行工具)和fio(灵活、可定制的文件 I/O 性能测试工具)亲自测试看看。

高并发或内存池管理下的内存越界，valgrind(内存调试工具,检测和分析程序的内存泄漏、缓冲区溢出等问题)基本没用，mprotect(内存保护工具,助程序员保护程序的内存区域，防止未经授权的访问)可以帮忙，但是要改代码做对齐。

另外就是管教结构的头尾可以用宏控制加magic number，运气好的话看一眼被破坏的内存就知道是谁占用的了。

日志中把微秒时间，文件名，函数名，行号都打出来，关键时候有大用处。

其他想起来再补充。

最后，老司机的经验是做好防御性编程，把日志做好，即方便查问题也方便甩锅。。