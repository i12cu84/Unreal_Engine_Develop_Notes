url down to:https://github.com/niXman/mingw-builds-binaries/releases

选择 -> x86_64-13.1.0-release-win32-seh-ucrt-rt_v11-rev1.7z

将文件解压到[fliePath]中

win+r 呼出sysdm.cpl -> 高级 -> 环境变量 -> 系统变量 -> Path 添加  导入[fliePath]/bin 存入

win+r 呼出cmd -> 输入gcc --version (显示版本则完成)

另外:

c++的mingw有很多下载版本，这些有什么区别呢？如下：
i686-13.2.0-release-posix-dwarf-msvcrt-rt_v11-rev0.7z
i686-13.2.0-release-posix-dwarf-ucrt-rt_v11-rev0.7z
i686-13.2.0-release-win32-dwarf-msvcrt-rt_v11-rev0.7z
i686-13.2.0-release-win32-dwarf-ucrt-rt_v11-rev0.7z
x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0.7z
x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev0.7z
x86_64-13.2.0-release-win32-seh-msvcrt-rt_v11-rev0.7z
x86_64-13.2.0-release-win32-seh-ucrt-rt_v11-rev0.7z

ChatGPT
这些版本的Mingw都是C/C++编译工具链的不同配置选项，其中包括架构（32位或64位）、C库（msvcrt或ucrt）、以及异常处理模型（dwarf或seh）。让我为你解释一下它们的区别：

i686 vs. x86_64:

i686: 这是32位架构的Mingw版本，适用于32位应用程序。
x86_64: 这是64位架构的Mingw版本，适用于64位应用程序。
release vs. debug:

release: 这是发布版本，用于生成优化的可执行文件。
debug: 这是调试版本，用于生成包含调试信息的可执行文件。
posix vs. win32:

posix: 这表示使用POSIX线程模型。
win32: 这表示使用Win32线程模型。
dwarf vs. seh:

dwarf: 这是一种异常处理模型，通常用于GNU工具链。
seh: 这是结构化异常处理模型，用于Windows上的异常处理。
msvcrt vs. ucrt:

msvcrt: 使用Microsoft C Runtime库，通常适用于旧版Windows应用程序。
ucrt: 使用Universal C Runtime库，适用于较新的Windows应用程序。