CLOC 对许多编程语言中源代码的空白行、注释行和物理行进行计数。

作为单个自包含文件存在，只需最少的安装工作---只需下载并运行该文件即可。
可以从文件中读取语言注释定义，因此可能使用尚不存在的计算机语言。
允许按语言和项目将多个运行的结果相加。
可以生成多种格式的结果：纯文本，SQL，JSON，XML，YAML，逗号分隔值。
可以计算压缩存档（焦油球，Zip文件，Java .ear文件）中的代码。
具有许多故障排除选项。
处理带有空格和其他异常字符的文件和目录名称。
在标准 Perl 发行版之外没有依赖关系。
在具有 Perl 5.6 或更高版本的 Linux、FreeBSD、NetBSD、OpenBSD、macOS、AIX、HP-UX、Solaris、IRIX 和 z/OS 系统上运行。源版本在Windows上运行，带有ActiveState Perl，Strawberry Perl，Cygwin或MobaXTerm + Perl插件。或者，在Windows上可以运行没有依赖关系的Windows二进制文件。

more and download url:https://github.com/AlDanial/cloc

win+r 呼出sysdm.cpl -> 高级 -> 环境变量 -> 系统变量 -> Path 添加  导入[fliePath] 存入

win+r 呼出cmd -> 

code:

cloc . -> 显示根目录文件 不同代码类型的码数行数

cloc [name] -> 显示指定文件夹文件 不同代码类型的码数行数

https://blog.csdn.net/qq_49181524/article/details/111298517