配置方法:https://zhuanlan.zhihu.com/p/639130726
思路汇总:https://www.bilibili.com/read/cv16053718

环境配置需求:
Android 4.2版本以上(注意下载对应版本组件)
Epic Unreal Engine 5.2版本
Visual Studio 2022版本 (附加游戏开发/c++开发/Unreal引擎Andriod/Window SDK 等组件)
DirectX 2010 SDK
JDK 8.0版本以上

Unable to locate sdkmanager.bat.
详解:https://blog.csdn.net/m0_51386934/article/details/127191077
路径:C:\Program Files\Epic Games\UE_5.2\Engine\Extras\Android
文件->SetupAndroid.bat(windows环境下打包激活bat)
修改内容-> set SDKMANAGER=%STUDIO_SDK_PATH%\cmdline-tools\latest\bin\sdkmanager.bat (安卓的sdk位置)

Error: A JNI error has occurred, please check your installation and try again
详解:https://blog.csdn.net/Yimu_Wang/article/details/113666518
详解2:https://blog.csdn.net/simonchi/article/details/126625381
详解3:https://blog.csdn.net/qq_44664231/article/details/131544077
java版本不一致问题
JAVA_HOME + : C:\Program Files\Java\jdk-17
Path + : C:\Program Files\Java\jdk-17\bin

打包时显示:Do you want to attempt again?
具体内容:
UATHelper: 打包 (Android (ASTC)): ERROR: Command C:\Program Files\Epic Games\UE_5.2\Engine\Extras\Android\SetupAndroid.bat android-32 30.0.3 3.10.2.4988404 25.1.8937393 -noninteractive failed [Exit code 4, working dir = C:\Program Files\Epic Games\UE_5.2\Engine\Extras\Android]
PackagingResults: Error: Command C:\Program Files\Epic Games\UE_5.2\Engine\Extras\Android\SetupAndroid.bat android-32 30.0.3 3.10.2.4988404 25.1.8937393 -noninteractive failed [Exit code 4, working dir = C:\Program Files\Epic Games\UE_5.2\Engine\Extras\Android]
LogSlate: Window 'Turnkey' being destroyed
Message dialog closed, result: No, title: Turnkey, text: Do you want to attempt again?
UATHelper: 打包 (Android (ASTC)): Scanning for envvar changes...
UATHelper: 打包 (Android (ASTC)): ... done! 
UATHelper: 打包 (Android (ASTC)): ----------------------------------------------
UATHelper: 打包 (Android (ASTC)): Finished with 4
UATHelper: 打包 (Android (ASTC)): ----------------------------------------------
UATHelper: 打包 (Android (ASTC)): Failed to install Android SDK r25b
UATHelper: 打包 (Android (ASTC)): Scanning for envvar changes...
UATHelper: 打包 (Android (ASTC)): ... done! 
UATHelper: 打包 (Android (ASTC)): Cleaning Temp Paths...
UATHelper: 打包 (Android (ASTC)): AutomationTool executed for 0h 0m 14s
UATHelper: 打包 (Android (ASTC)): AutomationTool exiting with ExitCode=200 (Error_SDKInstallFailed)
UATHelper: 打包 (Android (ASTC)): BUILD FAILED
PackagingResults: Error: Unknown Error
解决方案:
工程左上角 -> 编辑 -> 项目设置 -> 平台 -> Android -> 以.apk打包(打勾)
工程左上角 -> 编辑 -> 项目设置 -> 平台 -> Android SDK -> 三大路径需要核对正确 
示例:C:/Users/chru/AppData/Local/Android/Sdk
C:/Users/chru/AppData/Local/Android/Sdk/ndk/25.1.8937393
C:/Program Files/Java/jdk-17

打包时日志:Platform Android is not a valid platform to build. Check that the SDK is installed properly.
sdk和ndk的路径有问题(修正即可,可能是版本问题)
参考:https://forums.unrealengine.com/t/platform-android-is-not-a-valid-platform-to-build-check-that-the-sdk-is-installed-properly/511950

仍旧报错:
"Intermediate\Android\arm64\gradle\rungradle.bat" :app:assembleDebug
解决方法:
https://blog.csdn.net/u011407338/article/details/90446187
end:
仍未解决...且搁置

放个具体流程吧:
https://docs.unrealengine.com/5.2/zh-CN/setting-up-unreal-engine-projects-for-android-development/
