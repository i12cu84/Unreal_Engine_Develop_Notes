//该文件是windows脚本(Batch Script)
//将 C:\Users\chru\Desktop\test路径下的所有文件迁移到安卓手机的/sdcard/Android/data/com.YourCompany.Repair/files/UnrealGame/Repair/路径下
//chru 是我系统电脑的用户名
//Repair是ue的项目名字(安卓版)
//该项目是用于为原有安装的ue项目安装后的基础上额外添加一些配置文件
@echo off
setlocal enabledelayedexpansion

REM 如果UE_SDKS_ROOT已定义，则设置环境变量
if NOT "%UE_SDKS_ROOT%"=="" (
    call "%UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat"
)

REM 将ANDROIDHOME设置为ANDROID_HOME的值或默认路径
set ANDROIDHOME=%ANDROID_HOME%
if "%ANDROIDHOME%"=="" set ANDROIDHOME=C:\Users\chru\AppData\Local\Android\Sdk

REM 使用引号定义ADB变量，围绕可执行文件路径
set ADB="%ANDROIDHOME%\platform-tools\adb.exe"

REM 检查ADB可执行文件是否存在
if not exist %ADB% (
    echo 未在 %ADB% 找到ADB可执行文件
    exit /b 1
)

REM 设置文件夹路径为所需的目录
set "folder_path=C:\Users\chru\Desktop\test"

REM 遍历指定文件夹中的文件
for %%i in ("%folder_path%\*") do (
    set "LOCAL_FILE_PATH=%%i"
    set "ANDROID_DEST_PATH=/sdcard/Android/data/com.YourCompany.Repair/files/UnrealGame/Repair/"

    REM 使用ADB将本地文件推送到Android设备
    %ADB% push "!LOCAL_FILE_PATH!" "!ANDROID_DEST_PATH!"

    REM 检查错误级别并打印成功或错误消息
    if not errorlevel 1 (
        echo !LOCAL_FILE_PATH!
        echo 成功
    ) else (
        echo !LOCAL_FILE_PATH!
        echo 错误
    )
)

@pause

endlocal
