url down to:https://github.com/niXman/mingw-builds-binaries/releases

选择 -> x86_64-13.1.0-release-win32-seh-ucrt-rt_v11-rev1.7z

将文件解压到[fliePath]中

win+r 呼出sysdm.cpl -> 高级 -> 环境变量 -> 系统变量 -> Path 添加  导入[fliePath]/bin 存入

win+r 呼出cmd -> 输入gcc --version (显示版本则完成)