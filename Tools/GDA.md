GDA是一款由本人对反编译理论的长期研究和实践而形成的全交互式反编译器，世界上唯一一款用c++写的android-java反编译器，中国第一款也是唯一一款全交互式反编译器。其简洁、轻便、快速，无需安装，也无需java和android sdk环境支持。支持apk、dex、odex、oat、jar、aar、class文件的反编译分析，GDA中包含多个由本人独立研究的高速分析引擎: 反编译引擎、漏洞检测引擎、恶意行为检测引擎、污点传播分析引擎、反混淆引擎、apk壳检测引擎等。

在Android可执行文件反编译分析上，GDA摆脱了使用java速度慢的问题，完全采用C++完成核心反编译引擎的编写，并且使用了字节码直接转java伪代码的解析方式，无需转换成smali汇编后在做反编译，大大提升了解析速度。

此外，在反编译引擎的基础上，我做了一些更加实用的功能，如路径求解、 漏洞检测、隐私泄露检测、查壳、odex转dex、oat转dex、加解密算法工具、android设备内存dump等等功能，在交互式分析上，提供了( multi-dex的跨dex的 )字符串、方法、类和域交叉引用查询、调用者查询、搜索功能、注释功能、分析结果保存等等功能。

目标文件基本信息；
BaseInfo            Dex文件所使用的API                      了解该样本的一些基本情况，如检查看看该病毒开启了扫描敏感权限，从主界面中我们可以看到该病毒开启了很多敏感权限
AllAPI              查看所有字符串；
AllStrings          查看所有被引用过的字符串；               会获取该APK所有的字符串
AppStrings          提取出Dex中的所有URL(pro Version)；     获取APK有效类会用到的字符串
Urls                查看AndroidManifest文件；
AndroidManifest     十六进制查看器，可编辑数据；              来分析该病毒所使用的Activity, Service，receive等信息
HewView             恶意行为扫描分析；
MalScan             漏洞扫描(Pro Version)；                 了解该病毒大致的恶意行为
VulScan             隐私泄露扫描（Pro Version);
PrivacyLeak         展开权限并查看权限所属模块/方法；
AccessPermission    点击进入入口函数(method)；


参考链接
https://github.com/charles2gan/GDA-android-reversing-Tool
https://zhuanlan.zhihu.com/p/28354064
https://bbs.kanxue.com/thread-203916.htm
