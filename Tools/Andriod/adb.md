 ADB，即Android Debug Bridge，是Android平台上一个非常重要的调试工具。通过ADB，开发者可以实现与Android设备或模拟器的双向通信，从而进行应用程序的测试、调试和数据传输等多种操作。以下是ADB的一些具体用途：
1. **设备管理**：
   - `adb devices`：列出当前连接的设备。
   - `adb connect`：手动连接到一个指定的Android设备或模拟器。
   - `adb disconnect`：断开与设备的连接。
2. **文件传输**：
   - `adb push`：将文件从电脑发送到设备。
   - `adb pull`：从设备上获取文件到电脑。
   - `adb sync`：同步设备的文件系统与电脑。
3. **应用安装与管理**：
   - `adb install`：安装APK文件到设备上。
   - `adb uninstall`：卸载APK，如果不加 `-k` 参数，将删除应用及其数据。
   - `adb shell`：进入设备的Shell环境，可以执行各种命令。
4. **系统监控与调试**：
   - `adb logcat`：查看设备的日志输出。
   - `adb bugreport`：获取设备的错误报告。
   - `adb shell dumpsys`：获取系统的各种状态信息。
5. **界面自动化与测试**：
   - `adb uiautomator`：运行UiAutomator测试脚本。
   - `adb appium`：运行Appium测试脚本，适用于UI自动化测试。
6. **网络通信**：
   - `adb tcpip`：设置设备的网络通信模式。
   - `adb forward`：设置端口转发，允许从电脑访问设备上的服务。
7. **开发者选项**：
   - `adb shell pm enable-feature`：启用或禁用开发者选项中的功能。
ADB不仅限于开发者使用，普通用户也可以利用ADB来进行一些高级操作，如刷机、解锁Bootloader等。但需要注意的是，使用ADB操作可能会违反设备的保修条款，或者需要特定的权限。因此，在使用ADB进行任何操作之前，用户应确保自己了解所做行为的后果，并遵循相关法律法规以及设备制造商的使用指南。


-----------------------------------------------------------------------------------------------------------------------------------------------------------


Android 调试桥 (adb)
Android 调试桥 (adb) 是一种功能多样的命令行工具，可让您与设备进行通信。adb 命令可用于执行各种设备操作，例如安装和调试应用。adb 提供对 Unix shell（可用来在设备上运行各种命令）的访问权限。它是一种客户端-服务器程序，包括以下三个组件：

客户端：用于发送命令。客户端在开发机器上运行。您可以通过发出 adb 命令从命令行终端调用客户端。
守护程序 (adbd)：用于在设备上运行命令。守护程序在每个设备上作为后台进程运行。
服务器：用于管理客户端与守护程序之间的通信。服务器在开发机器上作为后台进程运行。
adb 包含在 Android SDK 平台工具软件包中。您可以使用 SDK 管理器下载此软件包，该管理器会将其安装在 android_sdk/platform-tools/ 下。如果您需要独立的 Android SDK 平台工具软件包，请点击此处进行下载。

如需了解如何通过 adb 连接设备以供使用，包括如何使用 Connection Assistant 来排查常见问题，请参阅在硬件设备上运行应用。

adb 的工作原理
当您启动某个 adb 客户端时，该客户端会先检查是否有 adb 服务器进程已在运行。如果没有，它会启动服务器进程。服务器在启动后会与本地 TCP 端口 5037 绑定，并监听 adb 客户端发出的命令。

注意：所有 adb 客户端均使用端口 5037 与 adb 服务器通信。

然后，服务器会与所有正在运行的设备建立连接。它通过扫描 5555 到 5585 之间（该范围供前 16 个模拟器使用）的奇数号端口查找模拟器。服务器一旦发现 adb 守护程序 (adbd)，便会与相应的端口建立连接。

每个模拟器都使用一对按顺序排列的端口：一个用于控制台连接的偶数号端口，另一个用于 adb 连接的奇数号端口。例如：

模拟器 1，控制台：5554
模拟器 1，adb：5555
模拟器 2，控制台：5556
模拟器 2，adb：5557
依此类推。

如上所示，在端口 5555 处与 adb 连接的模拟器与控制台监听端口为 5554 的模拟器是同一个。

服务器与所有设备均建立连接后，您便可以使用 adb 命令访问这些设备。由于服务器管理与设备的连接，并处理来自多个 adb 客户端的命令，因此您可以从任意客户端或从某个脚本控制任意设备。

在设备上启用 adb 调试
如要在通过 USB 连接的设备上使用 adb，您必须在设备的系统设置中启用 USB 调试（位于开发者选项下）。在 Android 4.2（API 级别 17）及更高版本中，开发者选项屏幕默认处于隐藏状态。如需将其显示出来，请启用开发者选项。

现在，您已经可以通过 USB 连接设备了。您可以通过从 android_sdk/platform-tools/ 目录执行 adb devices 来验证设备是否已连接。如果已连接，您将看到设备名称以“设备”形式列出。

注意：当您连接搭载 Android 4.2.2（API 级别 17）或更高版本的设备时，系统会显示一个对话框，询问您是否接受允许通过此计算机进行调试的 RSA 密钥。这种安全机制可以保护用户设备，因为它可以确保用户只有在能够解锁设备并确认对话框的情况下才能执行 USB 调试和其他 adb 命令。

如需详细了解如何通过 USB 连接到设备，请参阅在硬件设备上运行应用。

通过 Wi-Fi 连接到设备
注意：以下说明不适用于搭载 Android 11（API 级别 30）的 Wear 设备。如需了解详情，请参阅调试 Wear OS 应用指南。

Android 11（API 级别 30）及更高版本支持使用 Android 调试桥 (adb) 从工作站以无线方式部署和调试应用。例如，您可以将可调试应用部署到多台远程设备，而无需通过 USB 实际连接设备。这样就可以避免常见的 USB 连接问题，例如驱动程序安装方面的问题。

在开始使用无线调试功能之前，请执行以下操作：

确保您的工作站和设备已连接到同一无线网络。

确保您的设备搭载的是 Android 11（API 级别 30）或更高版本（针对手机），或者 Android 13（API 级别 33）或更高版本（针对 TV 和 WearOS）。如需了解详情，请参阅查看并更新 Android 版本。

确保您已安装最新版本的 Android Studio。您可以在此处下载。

在您的工作站上，将 SDK 平台工具更新到最新版本。

如需使用无线调试功能，您必须使用二维码或配对码将设备与工作站配对。您的工作站和设备必须连接到同一无线网络。如需连接到您的设备，请按以下步骤操作：

在您的设备上启用开发者选项。

打开 Android Studio，然后从运行配置菜单中选择 Pair Devices Using Wi-Fi。

运行配置下拉菜单
图 1. 运行配置菜单。
系统会弹出 Pair devices over Wi-Fi 窗口，如图 2 所示。

“Pair devices over Wi-Fi”弹出式窗口的屏幕截图
图 2. 使用二维码或配对码配对设备的弹出式窗口。
在您的设备上，点按无线调试，然后配对您的设备：

显示“无线调试”系统设置的 Pixel 手机的屏幕截图。
图 3. Google Pixel 手机上的无线调试设置屏幕截图。
如需使用二维码配对设备，请选择使用二维码配对设备，然后扫描 Pair devices over Wi-Fi 弹出式窗口中提供的二维码（如图 2 所示）。

如需使用配对码配对设备，请从 Pair devices over Wi-Fi 弹出式窗口中选择 Pair device with pairing code。在您的设备上，选择使用配对码配对设备，并记下提供的 6 位数配对码。设备显示在 Pair devices over Wi-Fi 窗口中后，您可以选择 Pair，并输入设备上显示的 6 位数配对码。

PIN 码输入示例的屏幕截图
图 4. 6 位数配对码输入示例。
配对设备后，您可以尝试将应用部署到该设备。

如需与其他设备配对，或在工作站上取消保存当前设备，请在设备上进入无线调试部分，在已配对的设备下点按工作站名称，然后选择取消保存。

如果您想快速开启和关闭无线调试功能，可以利用快捷设置开发者图块进行无线调试（可在开发者选项 > 快捷设置开发者图块中找到）。

Google Pixel 手机上的快捷设置开发者图块屏幕截图。
图 5. 快捷设置开发者图块设置可让您快速开启和关闭无线调试功能。
使用命令行连接 Wi-Fi
另外，如果您想在不使用 Android Studio 的情况下，通过命令行连接到您的设备，请按以下步骤操作：

如前所述，在设备上启用开发者选项。

如前所述，在设备上启用无线调试。

在工作站上，打开终端窗口并前往 android_sdk/platform-tools。

选择 Pair device with pairing code，找到您的 IP 地址、端口号和配对码。记下设备上显示的 IP 地址、端口号和配对码。

在工作站的终端上，运行 adb pair ipaddr:port。请使用上述 IP 地址和端口号。

收到提示时，输入配对码，如下所示。

通过命令行进行配对的屏幕截图。
图 6. 表明设备已成功配对的消息。
解决无线连接问题
如果您通过无线方式连接到设备时遇到问题，不妨尝试通过以下问题排查步骤来解决问题。

检查您的工作站和设备是否满足前提条件
检查工作站和设备是否满足本部分开头列出的前提条件。

检查是否存在其他已知问题
下面列出了 Android Studio 中目前已知的无线调试问题及其解决办法：

无法连接到 Wi-Fi：某些 Wi-Fi 网络（如企业 Wi-Fi 网络）可能会阻止点对点连接，并且不让您通过 Wi-Fi 进行连接。请尝试通过网线连接，或连接其他 Wi-Fi 网络。

“通过 Wi-Fi 使用 adb”的功能有时会自动关闭：如果设备切换 Wi-Fi 网络或断开网络连接，就可能会发生这种情况。如需解决此问题，请重新连接到网络。

通过 Wi-Fi 连接到设备（Android 10 及更低版本）
注意：以下说明不适用于搭载 Android 10（API 级别 29）或更低版本的 Wear 设备。如需了解详情，请参阅调试 Wear OS 应用指南。

一般情况下，adb 通过 USB 与设备进行通信，但您也可以通过 Wi-Fi 使用 adb。若要连接到搭载 Android 10（API 级别 29）或更低版本的设备，请通过 USB 执行以下初始步骤：

将 Android 设备和 adb 主机连接到同一 Wi-Fi 网络。
注意：并非所有接入点都适用。您可能需要使用防火墙已正确配置为支持 adb 的接入点。

使用 USB 线将设备连接到主机。
设置目标设备以监听端口 5555 上的 TCP/IP 连接：

adb tcpip 5555
拔掉连接目标设备的 USB 线。
找到 Android 设备的 IP 地址。例如，对于 Nexus 设备，您可以在设置 > 关于平板电脑（或关于手机）> 状态 > IP 地址下找到 IP 地址。
通过 IP 地址连接到设备：

adb connect device_ip_address:5555
确认主机已连接到目标设备：

$ adb devices
List of devices attached
device_ip_address:5555 device
您的设备现已连接到 adb。

如果与设备的 adb 连接断开：

确保主机仍与 Android 设备连接到同一 Wi-Fi 网络。
通过再次执行 adb connect 步骤重新连接。
如果这样无法解决问题，请重置您的 adb 主机：

adb kill-server
然后，从头开始操作。

查询设备
在发出 adb 命令之前，了解哪些设备实例已连接到 adb 服务器会很有帮助。您可以使用以下 devices 命令生成已连接设备的列表：


  adb devices -l
  
作为响应，adb 会针对每个设备输出以下状态信息：

序列号：adb 会创建一个字符串，用于通过端口号唯一标识设备。下面是一个序列号示例：emulator-5554
状态：设备的连接状态可以是以下几项之一：
offline：设备未连接到 adb 或没有响应。
device：设备已连接到 adb 服务器。请注意，此状态并不表示 Android 系统已完全启动并可正常运行，因为在设备连接到 adb 时系统仍在启动。系统完成启动后，设备通常处于此运行状态。
no device：未连接任何设备。
说明：如果您加入 -l 选项，devices 命令会告知您设备是什么。当您连接了多个设备时，此信息会很有用，方便您区分这些设备。
以下示例展示了 devices 命令及其输出。有三个设备正在运行。列表中的前两行表示模拟器，第三行表示连接到计算机的硬件设备。


$ adb devices
List of devices attached
emulator-5556 device product:sdk_google_phone_x86_64 model:Android_SDK_built_for_x86_64 device:generic_x86_64
emulator-5554 device product:sdk_google_phone_x86 model:Android_SDK_built_for_x86 device:generic_x86
0a388e93      device usb:1-1 product:razor model:Nexus_7 device:flo
模拟器未列出
adb devices 命令的极端命令序列会导致正在运行的模拟器不显示在 adb devices 输出中（即使在您的桌面上可以看到该模拟器）。当满足以下所有条件时，就会发生这种情况：

adb 服务器未在运行。
您在使用 emulator 命令时，将 -port 或 -ports 选项的端口值设为 5554 到 5584 之间的奇数。
您选择的奇数号端口处于空闲状态，因此可以与指定端口号的端口建立连接，或者该端口处于忙碌状态，模拟器切换到了符合第 2 条中要求的另一个端口。
启动模拟器后才启动 adb 服务器。
避免出现这种情况的一种方法是让模拟器自行选择端口，并且每次运行的模拟器数量不要超过 16 个。另一种方法是始终先启动 adb 服务器，然后再使用 emulator 命令，如下例所示。

示例 1：在下面的命令序列中，adb devices 命令启动了 adb 服务器，但是设备列表未显示。

停止 adb 服务器，然后按照所示顺序输入以下命令。对于 AVD 名称，请提供系统中有效的 AVD 名称。如需获取 AVD 名称列表，请输入 emulator -list-avds。emulator 命令位于 android_sdk/tools 目录下。


$ adb kill-server
$ emulator -avd Nexus_6_API_25 -port 5555
$ adb devices

List of devices attached
* daemon not running. starting it now on port 5037 *
* daemon started successfully *
示例 2：在下面的命令序列中，adb devices 显示了设备列表，因为先启动了 adb 服务器。

如果想在 adb devices 输出中看到模拟器，请停止 adb 服务器，然后在使用 emulator 命令之后、使用 adb devices 命令之前，重新启动该服务器，如下所示：


$ adb kill-server
$ emulator -avd Nexus_6_API_25 -port 5557
$ adb start-server
$ adb devices

List of devices attached
emulator-5557 device
如需详细了解模拟器命令行选项，请参阅命令行启动选项。

将命令发送至特定设备
如果有多个设备在运行，您在发出 adb 命令时必须指定目标设备。如需指定目标设备，请按以下步骤操作：

使用 devices 命令获取目标设备的序列号。
获得序列号后，结合使用 -s 选项与 adb 命令来指定序列号。
如果您要发出很多 adb 命令，可以将 $ANDROID_SERIAL 环境变量设为包含序列号。
如果您同时使用 -s 和 $ANDROID_SERIAL，-s 会替换 $ANDROID_SERIAL。
在以下示例中，先获得了已连接设备的列表，然后使用其中一个设备的序列号在该设备上安装了 helloWorld.apk：


$ adb devices
List of devices attached
emulator-5554 device
emulator-5555 device

$ adb -s emulator-5555 install helloWorld.apk
注意：如果您在多个设备可用时发出命令但未指定目标设备，adb 会显示错误。

如果有多个可用设备，但只有一个是模拟器，请使用 -e 选项将命令发送至该模拟器。如果有多个设备，但只连接了一个硬件设备，请使用 -d 选项将命令发送至该硬件设备。

安装应用
您可以使用 adb 的 install 命令在模拟器或连接的设备上安装 APK：


adb install path_to_apk
安装测试 APK 时，必须在 install 命令中使用 -t 选项。如需了解详情，请参阅 -t。

若要详细了解如何创建可安装在模拟器/设备实例上的 APK 文件，请参阅构建和运行您的应用。

注意：如果您使用的是 Android Studio，则无需直接使用 adb 即可在模拟器或设备上安装您的应用。Android Studio 会为您执行应用的打包和安装操作。

设置端口转发
您可以使用 forward 命令设置任意端口转发，将特定主机端口上的请求转发到设备上的其他端口。以下示例设置了主机端口 6100 到设备端口 7100 的转发：


adb forward tcp:6100 tcp:7100
以下示例设置了主机端口 6100 到 local:logd 的转发：


adb forward tcp:6100 local:logd
如果您尝试确定发送到设备上指定端口的内容，上述做法可能会非常有用。系统会将收到的所有数据写入系统日志记录守护程序，并显示在设备日志中。

将文件复制到设备以及从设备复制文件
您可以使用 pull 和 push 命令将文件复制到设备或从设备复制文件。与 install 命令（仅将 APK 文件复制到特定位置）不同，使用 pull 和 push 命令可将任意目录和文件复制到设备中的任何位置。

如需从设备中复制某个文件或目录（及其子目录），请使用以下命令：


adb pull remote local
如需将某个文件或目录（及其子目录）复制到设备，请使用以下命令：


adb push local remote
将 local 和 remote 替换为开发机器（本地）和设备（远程）上的目标文件/目录的路径。例如：


adb push myfile.txt /sdcard/myfile.txt
停止 adb 服务器
在某些情况下，您可能需要终止 adb 服务器进程，然后重启才能解决问题。例如，如果 adb 不响应命令，就可能会发生这种情况。

如需停止 adb 服务器，请使用 adb kill-server 命令。然后，您可以通过发出其他任何 adb 命令来重启服务器。

发出 adb 命令
您可以使用开发机器上的命令行或使用以下命令通过脚本发出 adb 命令：


adb [-d | -e | -s serial_number] command
如果只有一个模拟器在运行或者只连接了一个设备，系统会默认将 adb 命令发送至该设备。如果有多个模拟器正在运行并且/或者连接了多个设备，您需要使用 -d、-e 或 -s 选项指定应向其发送命令的目标设备。

您可以使用以下命令来查看所有受支持 adb 命令的详细列表：


adb --help
发出 shell 命令
您可以使用 shell 命令通过 adb 发出设备命令，也可以使用该命令启动交互式 shell。如需发出单个命令，请使用如下所示的 shell 命令：


adb [-d |-e | -s serial_number] shell shell_command
要在设备上启动交互式 shell，请使用如下所示的 shell 命令：


adb [-d | -e | -s serial_number] shell
如需退出交互式 shell，请按 Control+D 或输入 exit。

Android 提供了大多数常见的 Unix 命令行工具。如需查看可用工具的列表，请使用以下命令：


adb shell ls /system/bin
对于大多数命令，都可通过 --help 参数获得命令帮助。许多 shell 命令都由 toybox 提供。对于所有 toybox 命令，都可通过 toybox --help 获得适用的一般性帮助。

在 Android 平台工具 23 及更高版本中，adb 处理参数的方式与 ssh(1) 命令相同。这项变更解决了很多命令注入方面的问题，同时让安全执行包含 shell 元字符的命令（如 adb install Let\'sGo.apk）成为可能。此外，这项变更还意味着，对包含 shell 元字符的所有命令的解释也发生了变化。

例如，adb shell setprop key 'value' 现在会返回错误，因为单引号 (') 会被本地 shell 消去，设备看到的是 adb shell setprop key value。如需使该命令正常运行，请引用两次，一次用于本地 shell，另一次用于远程 shell，与处理 ssh(1) 的方法相同。例如 adb shell setprop key 'value' 。

另请参阅 Logcat 命令行工具，该工具对监控系统日志很有用。

调用 activity 管理器
在 adb shell 中，您可以使用 activity 管理器 (am) 工具发出命令以执行各种系统操作，如启动 activity、强行停止进程、广播 intent、修改设备屏幕属性，等等。

在 shell 中，相应的 am 语法为：


am command
您也可以直接从 adb 发出 activity 管理器命令，无需进入远程 shell。例如：


adb shell am start -a android.intent.action.VIEW
表 1. 可用的 activity 管理器命令

命令	说明
start [options] intent	启动由 intent 指定的 Activity。
请参阅 intent 参数的规范。

具体选项包括：

-D：启用调试功能。
-W：等待启动完成。
--start-profiler file：启动性能分析器并将结果发送至 file。
-P file：类似于 --start-profiler，但当应用进入空闲状态时剖析停止。
-R count：重复启动 activity count 次。在每次重复前，将完成顶层 activity。
-S：在启动 activity 前，强行停止目标应用。
--opengl-trace：启用 OpenGL 函数的跟踪。
--user user_id | current：指定要作为哪个用户运行；如果未指定，则作为当前用户运行。
startservice [options] intent	启动由 intent 指定的 Service。
请参阅 intent 参数的规范。

具体选项包括：

--user user_id | current：指定要作为哪个用户运行；如果未指定，则作为当前用户运行。
force-stop package	强行停止与 package 关联的所有进程。
kill [options] package	终止与 package 关联的所有进程。此命令仅终止可安全终止且不会影响用户体验的进程。
具体选项包括：

--user user_id | all | current：指定要终止哪个用户的进程。如果未指定，则终止所有用户的进程。
kill-all	终止所有后台进程。
broadcast [options] intent	发出广播 intent。
请参阅 intent 参数的规范。

具体选项包括：

[--user user_id | all | current]：指定要发送给哪个用户；如果未指定，则发送给所有用户。
instrument [options] component	使用 Instrumentation 实例启动监控。通常情况下，目标 component 采用 test_package/runner_class 格式。
具体选项包括：

-r：输出原始结果（否则，对 report_key_streamresult 进行解码）。与 [-e perf true] 结合使用可生成性能测量的原始输出。
-e name value：将参数 name 设为 value。 对于测试运行程序，通用格式为 -e testrunner_flag value[,value...]。
-p file：将剖析数据写入 file。
-w：等待插桩完成后再返回。测试运行程序需要使用此选项。
--no-window-animation：运行时关闭窗口动画。
--user user_id | current：指定以哪个用户身份运行插桩。如果未指定，则以当前用户身份运行。
profile start process file	启动 process 的性能分析器，将结果写入 file。
profile stop process	停止 process 的性能分析器。
dumpheap [options] process file	转储 process 的堆，写入 file。
具体选项包括：

--user [user_id | current]：提供进程名称时，指定要转储的进程的用户。如果未指定，则使用当前用户。
-n：转储原生堆，而非托管堆。
set-debug-app [options] package	设置要调试的应用 package。
具体选项包括：

-w：应用启动时等待调试程序。
--persistent：保留此值。
clear-debug-app	清除之前使用 set-debug-app 设置的用于调试的软件包。
monitor [options]	开始监控崩溃或 ANR。
具体选项包括：

--gdb：在崩溃/ANR 时，在给定的端口上启动 gdbserv。
screen-compat {on | off} package	控制 package 的屏幕兼容性模式。
display-size [reset | widthxheight]	替换设备显示尺寸。此命令支持使用大屏设备模仿小屏幕分辨率（反之亦然），对于在不同尺寸的屏幕上测试应用非常有用。
示例：
am display-size 1280x800

display-density dpi	替换设备显示密度。此命令支持使用低密度屏幕模仿高密度屏幕环境（反之亦然），对于在不同密度的屏幕上测试应用非常有用。
示例：
am display-density 480

to-uri intent	以 URI 的形式输出给定的 intent 规范。
请参阅 intent 参数的规范。

to-intent-uri intent	以 intent: URI 的形式输出给定的 intent 规范。
请参阅 intent 参数的规范。

intent 参数的规范
对于采用 intent 参数的 activity 管理器命令，您可以使用以下选项指定 intent：

全部显示

调用软件包管理器 (pm)
在 adb shell 中，您可以使用软件包管理器 (pm) 工具发出命令，以对设备上安装的应用软件包执行操作和查询。

在 shell 中，相应的 pm 语法为：


pm command
您也可以直接从 adb 发出软件包管理器命令，无需进入远程 shell。例如：


adb shell pm uninstall com.example.MyApp
表 2. 可用的软件包管理器命令

命令	说明
list packages [options] filter	输出所有软件包，或者视需要仅输出软件包名称包含 filter 中文字的软件包。
具体选项：

-f：查看关联文件。
-d：进行过滤以仅显示已停用的软件包。
-e：进行过滤以仅显示已启用的软件包。
-s：进行过滤以仅显示系统软件包。
-3：进行过滤以仅显示第三方软件包。
-i：查看软件包的安装程序。
-u：包括已卸载的软件包。
--user user_id：要查询的用户空间。
list permission-groups	输出所有已知的权限组。
list permissions [options] group	输出所有已知的权限，或者视需要仅输出 group 中的权限。
具体选项：

-g：按组进行整理。
-f：输出所有信息。
-s：简短摘要。
-d：仅列出危险权限。
-u：仅列出用户将看到的权限。
list instrumentation [options]	列出所有测试软件包。
具体选项：

-f：列出测试软件包的 APK 文件。
target_package：仅列出此应用的测试软件包。
list features	输出系统的所有功能。
list libraries	输出当前设备支持的所有库。
list users	输出系统中的所有用户。
path package	输出给定 package 的 APK 的路径。
install [options] path	将软件包（通过 path 指定）安装到系统。
具体选项：

-r：重新安装现有应用，并保留其数据。
-t：允许安装测试 APK。仅当您运行或调试了应用或者使用了 Android Studio 的 Build > Build APK 命令时，Gradle 才会生成测试 APK。如果是使用开发者预览版 SDK 构建的 APK，那么安装测试 APK 时必须在 install 命令中包含 -t 选项。
-i installer_package_name：指定安装程序软件包名称。
--install-location location：使用以下某个值设置安装位置：
0：使用默认安装位置。
1：在设备内部存储空间中安装。
2：在外部介质上安装。
-f：在内部系统内存上安装软件包。
-d：允许版本代码降级。
-g：授予应用清单中列出的所有权限。
--fastdeploy：通过仅更新已更改的 APK 部分来快速更新安装的软件包。
--incremental：仅安装 APK 中启动应用所需的部分，同时在后台流式传输剩余数据。如要使用此功能，您必须为 APK 签名，创建一个 APK 签名方案 v4 文件，并将此文件放在 APK 所在的目录中。只有部分设备支持此功能。此选项会强制 adb 使用该功能，如果该功能不受支持，则会失败，并提供有关失败原因的详细信息。附加 --wait 选项，可等到 APK 完全安装完毕后再授予对 APK 的访问权限。
--no-incremental 可阻止 adb 使用此功能。

uninstall [options] package	从系统中移除软件包。
具体选项：

-k：移除软件包后保留数据和缓存目录。
--user user_id：指定要为哪位用户移除软件包。
--versionCode version_code：仅在应用具有给定的版本代码时卸载。
clear package	删除与软件包关联的所有数据。
enable package_or_component	启用给定的软件包或组件（写为“package/class”）。
disable package_or_component	停用给定的软件包或组件（写为“package/class”）。
disable-user [options] package_or_component	
具体选项：

--user user_id：要停用的用户。
grant package_name permission	向应用授予权限。在搭载 Android 6.0（API 级别 23）及更高版本的设备上，该权限可以是应用清单中声明的任何权限。在搭载 Android 5.1（API 级别 22）及更低版本的设备上，该权限必须是应用定义的可选权限。
revoke package_name permission	从应用撤消权限。在搭载 Android 6.0（API 级别 23）及更高版本的设备上，该权限可以是应用清单中声明的任何权限。在搭载 Android 5.1（API 级别 22）及更低版本的设备上，该权限必须是应用定义的可选权限。
set-install-location location	更改默认安装位置。位置值如下：
0：自动 - 让系统决定最合适的位置。
1：内部 - 在设备内部存储空间中安装。
2：外部 - 在外部介质上安装。
注意：此命令仅用于调试目的。使用此命令可能会导致应用中断和其他意外行为。

get-install-location	返回当前安装位置。返回值如下：
0 [auto]：让系统决定最合适的位置
1 [internal]：在设备内部存储空间中安装
2 [external]：在外部介质上安装
set-permission-enforced permission [true | false]	指定是否应强制执行指定权限。
trim-caches desired_free_space	减少缓存文件以达到给定的可用空间。
create-user user_name	创建具有给定 user_name 的新用户，从而输出该用户的新用户标识符。
remove-user user_id	移除具有给定 user_id 的用户，从而删除与该用户关联的所有数据。
get-max-users	输出设备支持的最大用户数。
get-app-links [options] [package]	
输出给定 package 的域名验证状态，如果未指定软件包，则输出所有软件包的域名验证状态。状态代码的定义如下：

none：没有为此域名记录任何内容
verified：域名已成功通过验证
approved：强行批准了域名，通常是通过执行 shell 命令来实现的
denied：强行拒绝了域名，通常是通过执行 shell 命令来实现的
migrated：从旧响应流程中保留的验证状态
restored：从用户数据恢复流程中保留的验证状态
legacy_failure：旧版验证程序拒绝了域名，原因未知
system_configured：设备配置自动批准了域名
>= 1024：设备验证程序专属的自定义错误代码
具体选项包括：

--user user_id：包括用户选择的域名。涵盖所有域名，而不仅仅是执行 autoVerify 的域名。
reset-app-links [options] [package]	
重置给定软件包的域名验证状态，如果未指定任何软件包，则重置所有软件包的域名验证状态。

package：要重置的软件包，如果使用“all”，则重置所有软件包
具体选项包括：

--user user_id：包括用户选择的域名。涵盖所有域名，而不仅仅是执行 autoVerify 的域名。
verify-app-links [--re-verify] [package]	
广播给定 package 的域名验证请求，如果未指定软件包，则发送所有软件包的域名验证请求。仅当软件包之前未记录响应时发送该请求。

--re-verify：即使软件包已记录响应也发送
set-app-links [--package package] state domains	
手动设置软件包的域名状态。仅当软件包将域名声明为 autoVerify 时，此命令才能正常运行。此命令不会针对无法应用的域名报告失败。

--package package：要设置的软件包，如果使用“all”，则设置所有软件包
state：要为域名设置的代码。有效值为：
STATE_NO_RESPONSE (0)：按未记录过任何响应的情况进行重置。
STATE_SUCCESS (1)：将域名视为已成功通过域名验证代理的验证。请注意，域名验证代理可以覆盖此设置。
STATE_APPROVED (2)：将域名视为一律批准，防止域名验证代理更改状态。
STATE_DENIED (3)：将域名视为一律拒绝，防止域名验证代理更改状态。
domains：要更改的域名的列表（以空格分隔），如果使用“all”，则更改所有域名。
set-app-links-user-selection --user user_id [--package package] enabled domains	
手动设置主机用户针对软件包选择的域名的状态。仅当软件包声明相应域名时，此命令才能正常运行。此命令不会针对无法应用的域名报告失败。

--user user_id：要更改哪位用户所做的选择
--package package：要设置的软件包
enabled：是否批准域名
domains：要更改的域名的列表（以空格分隔），如果使用“all”，则更改所有域名
set-app-links-user-selection --user user_id [--package package] enabled domains	
手动设置主机用户针对软件包选择的域名的状态。仅当软件包声明相应域名时，此命令才能正常运行。此命令不会针对无法应用的域名报告失败。

--user user_id：要更改哪位用户所做的选择
--package package：要设置的软件包
enabled：是否批准域名
domains：要更改的域名的列表（以空格分隔），如果使用“all”，则更改所有域名
set-app-links-allowed --user user_id [--package package] allowed	
切换软件包的自动验证链接处理设置。

--user user_id：要更改哪位用户所做的选择
--package package：要设置的软件包，如果使用“all”，则设置所有软件包；如果未指定任何软件包，则重置软件包
allowed：值为 true 时，表示允许软件包打开自动验证链接；值为 false 时，表示不允许这么做
get-app-link-owners --user user_id [--package package] domains	
为给定用户输出特定域名的所有者（按优先级从低到高的顺序排列）。

--user user_id：要查询的用户
--package package：（可选）同时针对软件包声明的所有域名输出结果；如果使用“all”，则针对所有软件包声明的所有域名输出结果
domains：要查询的域名的列表（以空格分隔）
调用设备政策管理器 (dpm)
为便于您开发和测试设备管理应用，请向设备政策管理器 (dpm) 工具发出命令。您可以使用该工具控制使用中的管理员应用，或更改设备上的政策状态数据。

在 shell 中，相应的 dpm 语法为：


dpm command
您也可以直接从 adb 发出设备政策管理器命令，无需进入远程 shell：


adb shell dpm command
表 3. 可用的设备政策管理器命令

命令	说明
set-active-admin [options] component	将 component 设为活动管理。
具体选项包括：

--user user_id：指定目标用户。您也可以传递 --user current 以选择当前用户。
set-profile-owner [options] component	将 component 设为活跃管理员，并将其软件包设为现有用户的个人资料所有者。
具体选项包括：

--user user_id：指定目标用户。您也可以传递 --user current 以选择当前用户。
--name name：指定简单易懂的组织名称。
set-device-owner [options] component	将 component 设为活跃管理员，并将其软件包设为设备所有者。
具体选项包括：

--user user_id：指定目标用户。您也可以传递 --user current 以选择当前用户。
--name name：指定简单易懂的组织名称。
remove-active-admin [options] component	停用活跃管理员。应用必须在清单中声明 android:testOnly。此命令还会移除设备所有者和个人资料所有者。
具体选项包括：

--user user_id：指定目标用户。您也可以传递 --user current 以选择当前用户。
clear-freeze-period-record	清除设备之前设置的系统 OTA 更新冻结期记录。在开发管理冻结期的应用时，这有助于避免设备存在调度方面的限制。请参阅管理系统更新。
在搭载 Android 9.0（API 级别 28）及更高版本的设备上受支持。

force-network-logs	强制系统让任何现有网络日志随时可供 DPC 检索。如果有可用的连接或 DNS 日志，DPC 会收到 onNetworkLogsAvailable() 回调。请参阅网络活动日志。
此命令有调用频率限制。在搭载 Android 9.0（API 级别 28）及更高版本的设备上受支持。

force-security-logs	强制系统向 DPC 提供任何现有安全日志。如果有可用的日志，DPC 会收到 onSecurityLogsAvailable() 回调。请参阅记录企业设备活动。
此命令有调用频率限制。在搭载 Android 9.0（API 级别 28）及更高版本的设备上受支持。

截取屏幕截图
screencap 命令是一个用于对设备显示屏截取屏幕截图的 shell 实用程序。

在 shell 中，相应的 screencap 语法为：


screencap filename
如需从命令行使用 screencap，请输入以下命令：


adb shell screencap /sdcard/screen.png
以下屏幕截图会话示例展示了如何使用 adb shell 截取屏幕截图，以及如何使用 pull 命令从设备下载屏幕截图文件：


$ adb shell
shell@ $ screencap /sdcard/screen.png
shell@ $ exit
$ adb pull /sdcard/screen.png
录制视频
screenrecord 命令是一个用于录制设备（搭载 Android 4.4 [API 级别 19] 及更高版本）显示屏的 shell 实用程序。该实用程序将屏幕 activity 录制为 MPEG-4 文件。您可以使用此文件创建宣传视频或培训视频，或将其用于调试或测试。

在 shell 中，使用以下语法：


screenrecord [options] filename
如需从命令行使用 screenrecord，请输入以下命令：


adb shell screenrecord /sdcard/demo.mp4
按 Ctrl+C 键（在 Mac 上，按 Command+C 键）可停止屏幕录制；如果不手动停止，到三分钟或 --time-limit 设置的时间限制时，录制将会自动停止。

如需开始录制设备屏幕，请运行 screenrecord 命令以录制视频。然后，运行 pull 命令以将视频从设备下载到主机。下面是一个录制会话示例：


$ adb shell
shell@ $ screenrecord --verbose /sdcard/demo.mp4
(press Control + C to stop)
shell@ $ exit
$ adb pull /sdcard/demo.mp4
screenrecord 实用程序能以您要求的任何支持的分辨率和比特率进行录制，同时保持设备显示屏的宽高比。默认情况下，该实用程序以本机显示分辨率和屏幕方向进行录制，时长不超过三分钟。

screenrecord 实用程序的局限性：

音频不与视频文件一起录制。
无法在搭载 Wear OS 的设备上录制视频。
某些设备可能无法以它们的本机显示分辨率进行录制。如果在录制屏幕时出现问题，请尝试使用较低的屏幕分辨率。
不支持在录制时旋转屏幕。如果在录制期间屏幕发生了旋转，则部分屏幕内容在录制时将被切断。
表 4. screenrecord 选项

选项	说明
--help	显示命令语法和选项
--size widthxheight	设置视频大小：1280x720。默认值为设备的本机显示屏分辨率（如果支持）；如果不支持，则为 1280x720。为获得最佳效果，请使用设备的 Advanced Video Coding (AVC) 编码器支持的大小。
--bit-rate rate	设置视频的视频比特率（以 MB/秒为单位）。默认值为 4Mbps。您可以增加比特率以提升视频质量，但这样做会导致视频文件变大。下面的示例将录制比特率设为 6Mbps：


screenrecord --bit-rate 6000000 /sdcard/demo.mp4
--time-limit time	设置最长录制时间（以秒为单位）。默认情况下，最大值为 180（3 分钟）。
--rotate	将输出旋转 90 度。此功能处于实验阶段。
--verbose	在命令行屏幕显示日志信息。如果您不设置此选项，则该实用程序在运行时不会显示任何信息。
读取应用的 ART 配置文件
从 Android 7.0（API 级别 24）开始，Android 运行时 (ART) 会收集已安装应用的执行配置文件，这些配置文件用于优化应用性能。您可以检查收集的配置文件，了解在应用启动期间，系统频繁执行了哪些方法和使用了哪些类。

注意：您必须拥有对文件系统的 root 权限（例如在模拟器上），才能检索执行配置文件的文件名。

要生成文本格式的配置文件信息，请使用以下命令：


adb shell cmd package dump-profiles package
要检索生成的文件，请使用：


adb pull /data/misc/profman/package.prof.txt
重置测试设备
如果您在多个测试设备上测试应用，则在两次测试之间重置设备可能很有用，例如，可以移除用户数据并重置测试环境。您可以使用 testharness adb shell 命令对搭载 Android 10（API 级别 29）或更高版本的测试设备恢复出厂设置，如下所示。


adb shell cmd testharness enable
使用 testharness 恢复设备时，设备会自动将允许通过当前工作站调试设备的 RSA 密钥备份在一个持久性位置。也就是说，在重置设备后，工作站可以继续调试设备并向设备发出 adb 命令，而无需手动注册新密钥。

此外，为了帮助您更轻松且更安全地继续测试您的应用，使用 testharness 恢复设备还会更改以下设备设置：

设备会设置某些系统设置，以便不会出现初始设备设置向导。也就是说，设备会进入一种状态，供您快速安装、调试和测试您的应用。
设置：
停用锁定屏幕。
停用紧急警报。
停用帐号自动同步。
停用自动系统更新。
其他：
停用预安装的安全应用。
如果您的应用需要检测并适应 testharness 命令的默认设置，请使用 ActivityManager.isRunningInUserTestHarness()。

sqlite
sqlite3 可启动用于检查 SQLite 数据库的 sqlite 命令行程序。它包含用于输出表格内容的 .dump 以及用于输出现有表格的 SQL CREATE 语句的 .schema 等命令。您也可以从命令行执行 SQLite 命令，如下所示：


$ adb -s emulator-5554 shell
$ sqlite3 /data/data/com.example.app/databases/rssitems.db
SQLite version 3.3.12
Enter ".help" for instructions

参考资料
https://developer.android.google.cn/studio/command-line/adb?hl=zh-cn#issuingcommands