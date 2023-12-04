//ue项目打包Android后产生的脚本文件内容解析(简述,卸载)

setlocal
if NOT "%UE_SDKS_ROOT%"=="" (call %UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat)
set ANDROIDHOME=%ANDROID_HOME%
if "%ANDROIDHOME%"=="" set ANDROIDHOME=C:/Users/chru/AppData/Local/Android/Sdk
set ADB=%ANDROIDHOME%\platform-tools\adb.exe
set DEVICE=
if not "%1"=="" set DEVICE=-s %1
for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A
@echo.
@echo Uninstalling existing application. Failures here can almost always be ignored.
%ADB% %DEVICE% uninstall com.YourCompany.[Android_Project_Name]
@echo.
echo Removing old data. Failures here are usually fine - indicating the files were not on the device.
%ADB% %DEVICE% shell rm -r %STORAGE%/UnrealGame/[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/UnrealGame/UECommandLine.txt
%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.YourCompany.[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.YourCompany.[Android_Project_Name]
@echo.
@echo Uninstall completed

这段脚本主要用于卸载现有的Android应用程序。以下是代码的解析：
1. `setlocal`：启用局部环境变量，确保对环境变量的更改仅在当前批处理脚本中有效，而不会影响系统环境变量。
2. `if NOT "%UE_SDKS_ROOT%"=="" (call %UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat)`：检查 `%UE_SDKS_ROOT%` 环境变量是否已设置。如果设置了，调用 `%UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat` 脚本以设置环境变量。
3. `set ANDROIDHOME=%ANDROID_HOME%`：将 `%ANDROID_HOME%` 的值赋给 `%ANDROIDHOME%` 环境变量。
4. `if "%ANDROIDHOME%"=="" set ANDROIDHOME=C:/Users/chru/AppData/Local/Android/Sdk`：如果 `%ANDROIDHOME%` 仍然为空，将其设置为默认的Android SDK路径。
5. `set ADB=%ANDROIDHOME%\platform-tools\adb.exe`：构建 `adb.exe` 的完整路径，并将其赋给 `%ADB%` 变量。
6. `set DEVICE=`：初始化 `%DEVICE%` 变量。
7. `if not "%1"=="" set DEVICE=-s %1`：如果命令行参数（`%1`）存在，则将 `-s %1` 赋给 `%DEVICE%`，其中 `%1` 是传递给脚本的第一个参数，通常是设备的标识符。
8. `for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A`：使用 `adb shell` 命令获取设备的 `$EXTERNAL_STORAGE` 值，并将其存储在 `%STORAGE%` 变量中。
9. `%ADB% %DEVICE% uninstall com.YourCompany.[Android_Project_Name]`：卸载具有包名 `com.YourCompany.[Android_Project_Name]` 的现有应用程序。
10. `echo Removing old data. Failures here are usually fine - indicating the files were not on the device.`：输出消息，指示正在移除旧数据，这里的错误通常可以被忽略，因为它可能表示在设备上找不到相应的文件。
11. `%ADB% %DEVICE% shell rm -r %STORAGE%/UnrealGame/[Android_Project_Name]` 等命令：使用 `adb shell` 命令删除设备上特定路径下的文件或目录。
12. `@echo. @echo Uninstall completed`：输出消息表明卸载完成。
这个脚本主要用于清理和卸载Android应用程序及其相关数据。

总的来说，
这段代码是一段Windows批处理脚本，用于在Android设备上安装应用程序。
该脚本首先检查是否设置了环境变量，然后设置ADB路径和设备ID。
接下来，它卸载现有的应用程序，然后删除旧数据。
如果删除失败，则可以忽略错误。
最后，它会输出卸载完成的消息。
