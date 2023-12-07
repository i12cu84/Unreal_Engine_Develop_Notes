//该文件是windows脚本(Batch Script)
//将 C:\Repair5.7\MoveFile 路径下文件夹内的文件复制到 DESTINATION=C:\Users\chru\Desktop\pack\Windows 路径下

@echo off
setlocal

REM 设置源目录和目标目录
set SOURCE=C:\Repair5.7\MoveFile
set DESTINATION=C:\Users\chru\Desktop\pack\Windows

REM 检查目标目录是否存在，如果不存在则创建
if not exist "%DESTINATION%" mkdir "%DESTINATION%"

REM 使用 xcopy 复制所有文件
xcopy /E /I "%SOURCE%\*" "%DESTINATION%"

echo Files move finished.
@pause

endlocal
