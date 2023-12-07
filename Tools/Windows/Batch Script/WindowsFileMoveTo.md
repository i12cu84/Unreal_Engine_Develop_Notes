//将 文件路径A 移动到 文件路径B
@echo off
setlocal

REM 设置源目录和目标目录
set SOURCE=[文件路径A]
set DESTINATION=[文件路径A]

REM 检查目标目录是否存在，如果不存在则创建
if not exist "%DESTINATION%" mkdir "%DESTINATION%"

REM 使用 xcopy 复制所有文件
xcopy /E /I "%SOURCE%\*" "%DESTINATION%"

echo Files move finished.
@pause

endlocal
