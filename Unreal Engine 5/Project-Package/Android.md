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


UATHelper: 打包 (Android (DXT)): Copying C:\Users\chru\Desktop\11\Intermediate\Android\arm64\AndroidManifest.xml to C:\Users\chru\Desktop\11\Intermediate\Android\arm64\gradle\app\src\main\AndroidManifest.xml
UATHelper: 打包 (Android (DXT)): Directory Engine/Plugins/Runtime/AndroidFileServer/Source/AndroidFileServer/../AFSStub copied to C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/AFSProject (True)
UATHelper: 打包 (Android (DXT)): Directory Engine/Plugins/Runtime/AndroidFileServer/Source/AndroidFileServer/Android copied to C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/AFSProject/app/src/main (True)
UATHelper: 打包 (Android (DXT)): Directory C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/app/src/main/res copied to C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/AFSProject/app/src/main/res (True)
UATHelper: 打包 (Android (DXT)): Directory C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/gradle copied to C:/Users/chru/Desktop/11/Intermediate/Android/arm64/gradle/AFSProject/gradle (True)
UATHelper: 打包 (Android (DXT)): Creating rungradle.bat to work around commandline length limit (using unused drive letter Z:)
UATHelper: 打包 (Android (DXT)): Making .apk with Gradle...
UATHelper: 打包 (Android (DXT)): To honour the JVM settings for this build a new JVM will be forked. Please consider using the daemon: https://docs.gradle.org/6.1.1/userguide/gradle_daemon.html.
UATHelper: 打包 (Android (DXT)): Daemon will be stopped at the end of the build stopping after processing
UATHelper: 打包 (Android (DXT)): java.lang.NoClassDefFoundError: Could not initialize class org.codehaus.groovy.vmplugin.v7.Java7
UATHelper: 打包 (Android (DXT)):     at java.base/java.lang.Thread.run(Thread.java:833)
UATHelper: 打包 (Android (DXT)): Caused by: java.lang.ExceptionInInitializerError: Exception org.codehaus.groovy.GroovyBugError [in thread "Daemon worker"]
UATHelper: 打包 (Android (DXT)):     at org.codehaus.groovy.vmplugin.v7.Java7.<clinit>(Java7.java:45)
UATHelper: 打包 (Android (DXT)):     at java.base/jdk.internal.reflect.NativeConstructorAccessorImpl.newInstance0(Native Method)
UATHelper: 打包 (Android (DXT)):     at java.base/jdk.internal.reflect.NativeConstructorAccessorImpl.newInstance(NativeConstructorAccessorImpl.java:77)
UATHelper: 打包 (Android (DXT)):     at java.base/jdk.internal.reflect.DelegatingConstructorAccessorImpl.newInstance(DelegatingConstructorAccessorImpl.java:45)
UATHelper: 打包 (Android (DXT)):     at java.base/java.lang.reflect.Constructor.newInstanceWithCaller(Constructor.java:499)
UATHelper: 打包 (Android (DXT)):     at java.base/java.lang.reflect.Constructor.newInstance(Constructor.java:480)
UATHelper: 打包 (Android (DXT)):     at org.codehaus.groovy.vmplugin.VMPluginFactory.createPlugin(VMPluginFactory.java:57)
UATHelper: 打包 (Android (DXT)):     at org.codehaus.groovy.vmplugin.VMPluginFactory.<clinit>(VMPluginFactory.java:39)
UATHelper: 打包 (Android (DXT)):     ... 128 more
UATHelper: 打包 (Android (DXT)): FAILURE: Build failed with an exception.
UATHelper: 打包 (Android (DXT)): * What went wrong:
UATHelper: 打包 (Android (DXT)): Could not initialize class org.codehaus.groovy.reflection.ReflectionCache
UATHelper: 打包 (Android (DXT)): > Exception java.lang.NoClassDefFoundError: Could not initialize class org.codehaus.groovy.vmplugin.v7.Java7 [in thread "Daemon worker"]
UATHelper: 打包 (Android (DXT)): * Try:
UATHelper: 打包 (Android (DXT)): Run with --stacktrace option to get the stack trace. Run with --info or --debug option to get more log output. Run with --scan to get full insights.
UATHelper: 打包 (Android (DXT)): * Get more help at https://help.gradle.org
UATHelper: 打包 (Android (DXT)): BUILD FAILED in 1s
UATHelper: 打包 (Android (DXT)): ERROR: cmd.exe failed with args /c "C:\Users\chru\Desktop\11\Intermediate\Android\arm64\gradle\rungradle.bat" :app:assembleDebug
UATHelper: 打包 (Android (DXT)):        (see C:\Users\chru\AppData\Roaming\Unreal Engine\AutomationTool\Logs\C+Program+Files+Epic+Games+UE_5.2\Log.txt for full exception trace)
UATHelper: 打包 (Android (DXT)): AutomationTool executed for 0h 18m 21s
UATHelper: 打包 (Android (DXT)): AutomationTool exiting with ExitCode=1 (Error_Unknown)
UATHelper: 打包 (Android (DXT)): BUILD FAILED
PackagingResults: Error: Unknown Error