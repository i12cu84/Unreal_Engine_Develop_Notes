//ue项目打包Android后产生的脚本文件内容解析(简述,安装)

setlocal
if NOT "%UE_SDKS_ROOT%"=="" (call %UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat)
set ANDROIDHOME=%ANDROID_HOME%
if "%ANDROIDHOME%"=="" set ANDROIDHOME=C:/Users/chru/AppData/Local/Android/Sdk
set ADB=%ANDROIDHOME%\platform-tools\adb.exe
set AFS=.\win-x64\UnrealAndroidFileTool.exe
set DEVICE=
if not "%1"=="" set DEVICE=-s %1
for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A
@echo.
@echo Uninstalling existing application. Failures here can almost always be ignored.
%ADB% %DEVICE% uninstall com.YourCompany.[Android_Project_Name]
@echo.
@echo Installing existing application. Failures here indicate a problem with the device (connection or storage permissions) and are fatal.
%ADB% %DEVICE% install [Android_Project_Name]-arm64.apk
@if "%ERRORLEVEL%" NEQ "0" goto Error
%ADB% %DEVICE% shell pm list packages com.YourCompany.[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/UnrealGame/[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/UnrealGame/UECommandLine.txt
%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.YourCompany.[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.YourCompany.[Android_Project_Name]
%ADB% %DEVICE% shell rm -r %STORAGE%/Download/obb/com.YourCompany.[Android_Project_Name]

@echo.
@echo Grant READ_EXTERNAL_STORAGE and WRITE_EXTERNAL_STORAGE to the apk for reading OBB file or game file in external storage.
%ADB% %DEVICE% shell pm grant com.YourCompany.[Android_Project_Name] android.permission.READ_EXTERNAL_STORAGE
%ADB% %DEVICE% shell pm grant com.YourCompany.[Android_Project_Name] android.permission.WRITE_EXTERNAL_STORAGE

@echo.
@echo Installation successful
goto:eof
:Error
@echo.
@echo There was an error installing the game or the obb file. Look above for more info.
@echo.
@echo Things to try:
@echo Check that the device (and only the device) is listed with "%ADB$ devices" from a command prompt.
@echo Make sure all Developer options look normal on the device
@echo Check that the device has an SD card.
@pause

这个批处理脚本似乎是Android游戏部署过程的一部分。我来为你解释一下代码：
1. `setlocal`：该命令启动环境变量的本地化，防止对环境变量的更改影响系统的其他部分。
2. 脚本检查 `%UE_SDKS_ROOT%` 环境变量是否设置。如果设置了，它会调用指定位置的一个批处理文件（`SetupEnvironmentVars.bat`）。
3. 将 `%ANDROIDHOME%` 环境变量设置为 `%ANDROID_HOME%` 的值。如果 `%ANDROIDHOME%` 尚未设置，它默认为 `C:/Users/chru/AppData/Local/Android/Sdk`。
4. 将 `%ADB%` 变量设置为 Android SDK 中 `adb.exe` 工具的路径。
5. 将 `%AFS%` 变量设置为当前目录 (`.\win-x64`) 中 `UnrealAndroidFileTool.exe` 的路径。
6. 根据命令行参数（如果提供）初始化 `%DEVICE%` 变量。
7. 使用 `adb shell` 命令从连接的Android设备中检索 `$EXTERNAL_STORAGE` 的值，并将其存储在 `%STORAGE%` 变量中。
8. 尝试使用 `adb uninstall` 卸载具有包名 `com.YourCompany.[Android_Project_Name]` 的现有应用程序。
9. 尝试使用 `adb install` 安装包名为 `com.YourCompany.[Android_Project_Name]` 的应用程序。
10. 如果安装失败（由非零的 `%ERRORLEVEL%` 表示），它跳转到 `:Error` 标签并显示错误消息。
11. 如果安装成功，脚本将继续在Android设备上执行各种清理任务，例如删除与游戏相关的目录和文件。
12. 使用 `adb shell pm grant` 命令为已安装的应用程序授予 `READ_EXTERNAL_STORAGE` 和 `WRITE_EXTERNAL_STORAGE` 权限。
13. 脚本输出成功消息并结束。
14. 如果在安装过程中发生错误，脚本输出错误消息并提供故障排除建议，然后暂停等待用户输入。
注意：请将 `[Android_Project_Name]` 替换为实际的Android项目名称。此外，确保必要的工具和文件，如 `adb.exe`、`UnrealAndroidFileTool.exe` 和APK文件，位于指定的位置。

总的来说，
这是一段Windows批处理脚本，用于在Android设备上安装应用程序。
该脚本首先检查是否设置了环境变量，然后设置ADB路径和设备ID。
接下来，它卸载现有的应用程序，然后安装新的应用程序。
如果安装失败，则会输出错误消息。
如果安装成功，则会授予应用程序读取和写入外部存储的权限。
最后，它会输出安装成功的消息。
如果安装失败，则会输出错误消息，并提供一些可能的解决方案。
请注意，这是一段Windows批处理脚本，不适用于其他操作系统。