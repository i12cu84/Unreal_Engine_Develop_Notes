
<details>
<summary>chkdsk 参数说明：</summary>
<pre><code>
CHKDSK [volume[path]filename]] [/F] [/V] [/X] [/C] [/L[:size］
volume 指定驱动器(后面跟一个冒号)、装入点或卷名。
filename 仅用于 FAT/FAT32: 指定要检查是否有碎片的文件
/F 修复磁盘上的错误。
/V　 在 FAT/FAT32 上: 显示磁盘上每个文件的完整路径和名称。在 NTFS 上: 如果有清除消息，将其显示。
/R 查找不正确的扇区并恢复可读信息(隐含 /F)。
/L:size 仅用于 NTFS:? 将日志文件大小改成指定的 KB 数。如果没有指定大小，则显示当前的大小。
/X 如果必要，强制卷先卸下。卷的所有打开的句柄就会无效(隐含 /F)
</code></pre>
</details>

<details>
<summary>shutdown</summary>
<pre><code>
关机：shutdown /s
重启：shutdown /r
注销：shutdown /l
休眠：shutdown /h /f
取消关机：shutdown /a
定时关机：shutdown /s /t 3600（3600 秒后关机）
</code></pre>
</details>

切换磁盘：d:（进入 d 盘）
切换磁盘和目录：cd /d d:/test（进入 d 盘 test 文件夹）
进入文件夹：cd \test1\test2（进入 test2 文件夹）
返回根目录：cd \
回到上级目录：cd ..
新建文件夹：md test

显示目录中文件列表：dir
显示目录结构：tree d:\test（d 盘 test 目录）
显示当前目录位置：cd
显示指定磁盘的当前目录位置：cd d:

延迟和丢包率：ping ip/域名
Ping 测试 5 次：ping ip/域名 -n 5
清除本地 DNS 缓存：ipconfig /flushdns
路由追踪：tracert ip/域名

显示当前正在运行的进程：tasklist
运行程序或命令：start 程序名
结束进程，按名称：taskkill /im notepad.exe（关闭记事本）
结束进程，按 PID：taskkill /pid 1234（关闭 PID 为 1234 的进程）

显示当前正在运行的服务：net start
启动指定服务：net start 服务名
停止指定服务：net stop 服务名

<details>
<summary>保存为 .bat 可执行文件</summary>
<pre><code>
我们可以将常用的命令输入记事本中，并保存为后缀为 .bat 的可执行文件。
以后只要双击该文件即可执行指定命令；将文件放入系统【启动】目录中，可以实现开机自动运行。
注：启动目录位置：[C:\Users\用户名\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup]
</code></pre>
</details>

<details>
<summary>cmd命令大全</summary>
<pre><code>
　　winver---------检查Windows版本
　　wmimgmt.msc----打开windows管理体系结构(WMI)
　　wupdmgr--------windows更新程序
　　wscript--------windows脚本宿主设置
　　write----------写字板
　　winmsd---------系统信息
　　wiaacmgr-------扫描仪和照相机向导
　　winchat--------XP自带局域网聊天
　　mem.exe--------显示内存使用情况
　　Msconfig.exe---系统配置实用程序
　　mplayer2-------简易widnows media player
　　mspaint--------画图板
　　mstsc----------远程桌面连接
　　mplayer2-------媒体播放机
　　magnify--------放大镜实用程序
　　mmc------------打开控制台
　　mobsync--------同步命令
　　dxdiag---------检查DirectX信息
　　drwtsn32------ 系统医生
　　devmgmt.msc--- 设备管理器
　　dfrg.msc-------磁盘碎片整理程序
　　diskmgmt.msc---磁盘管理实用程序
　　dcomcnfg-------打开系统组件服务
　　ddeshare-------打开DDE共享设置
　　dvdplay--------DVD播放器
　　net stop messenger-----停止信使服务
　　net start messenger----开始信使服务
　　notepad--------打开记事本
　　nslookup-------网络管理的工具向导
　　ntbackup-------系统备份和还原
　　narrator-------屏幕“讲述人”
　　ntmsmgr.msc----移动存储管理器
　　ntmsoprq.msc---移动存储管理员操作请求
　　netstat -an----(TC)命令检查接口
　　syncapp--------创建一个公文包
　　sysedit--------系统配置编辑器
　　sigverif-------文件签名验证程序
　　sndrec32-------录音机
　　shrpubw--------创建共享文件夹
　　secpol.m转载自电脑十万个为什么http://www.qq880.com，请保留此标记sc-----本地安全策略
　　syskey---------系统加密，一旦加密就不能解开，保护windows xp系统的双重密码
　　services.msc---本地服务设置
　　Sndvol32-------音量控制程序
　　sfc.exe--------系统文件检查器
　　sfc /scannow---windows文件保护
　　tsshutdn-------60秒倒计时关机命令
　　tourstart------xp简介（安装完成后出现的漫游xp程序）
　　taskmgr--------任务管理器
　　eventvwr-------事件查看器
　　eudcedit-------造字程序
　　explorer-------打开资源管理器
　　packager-------对象包装程序
　　perfmon.msc----计算机性能监测程序
　　progman--------程序管理器
　　regedit.exe----注册表
　　rsop.msc-------组策略结果集
　　regedt32-------注册表编辑器
　　rononce -p ----15秒关机
　　regsvr32 /u *.dll----停止dll文件运行
　　regsvr32 /u zipfldr.dll------取消ZIP支持
　　cmd.exe--------CMD命令提示符
　　chkdsk.exe-----Chkdsk磁盘检查
　　certmgr.msc----证书管理实用程序
　　calc-----------启动计算器
　　charmap--------启动字符映射表
　　cliconfg-------SQL SERVER 客户端网络实用程序
　　Clipbrd--------剪贴板查看器
　　conf-----------启动netmeeting
　　compmgmt.msc---计算机管理
　　cleanmgr-------垃圾整理
　　ciadv.msc------索引服务程序
　　osk------------打开屏幕键盘
　　odbcad32-------ODBC数据源管理器
　　oobe/msoobe /a----检查XP是否激活
　　lusrmgr.msc----本机用户和组
　　logoff---------注销命令
　　iexpress-------木马捆绑工具，系统自带
　　Nslookup-------IP地址侦测器
　　fsmgmt.msc-----共享文件夹管理器
　　utilman--------辅助工具管理器
　　gpedit.msc-----组策略
</code></pre>
</details>
