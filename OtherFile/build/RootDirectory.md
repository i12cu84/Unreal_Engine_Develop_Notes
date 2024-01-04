Config：（不可删除）配置文件。
Content：（不可删除）平常最常用到，所有的资源和蓝图等都放在该目录里。
Source：（不可删除）代码文件。
Plugins：（不可删除）项目使用的插件文件加，项目中没有用到其它插件，这个文件夹就没有。
.uproject：（不可删除）ureal工程

Binaries：（可删除）存放编译生成的结果二进制文件。该目录可以gitignore,反正每次都会生成。
DerivedDataCache：（可删除）“DDC”，存储着引擎针对平台特化后的资源版本。比如同一个图片，针对不同的平台有不同的适合格式，这个时候就可以在不动原始的uasset的基础上，比较轻易的再生成不同格式资源版本。gitignore。
Intermediate：（可删除）中间文件（gitignore），存放着一些临时生成的文件。有：Build的中间文件，.obj和预编译头等 UHT预处理生成的.generated.h/.cpp文件 VS.vcxproj项目文件，可通过.uproject文件生成编译生成的Shader文件。AssetRegistryCache：Asset Registry系统的缓存文件，Asset Registry可以简单理解为一个索引了所有uasset资源头信息的注册表。CachedAssetRegistry.bin文件也是如此。
Saved：（可删除，但不建议删除，如果确定项目没有问题，则可以删除）存储自动保存文件，其他配置文件，日志文件，引擎崩溃日志，硬件信息，烘培信息数据等。gitignore
.vs：（可删除）C++智能提示等功能
.sln：（可删除）C++工程
标记可删

将项目纳入版本控制需要上传的目录：
Config
Content
Source：
Plugins：
[xxx].uproject：

ue的缓存文件路径C:\Users\[i12cu84]\AppData\Local\UnrealEngine\Common\DerivedDataCache(可删除)

ue的缓存文件路径设置修改,配置文件在C:\Program Files\Epic Games\UE_5.2\Engine\Config\BaseEngine.ini
用记事本打开它，然后搜索InstalledDerivedDataBackendGraph并找到%ENGINEVERSIONAGNOSTICUSERDIR%DerivedDataCache把它改为%GAMEDIR%DerivedDataCache
修改完后，项目的编译缓存文件会生成在项目目录中


详情资料
https://docs.unrealengine.com/5.2/zh-CN/unreal-engine-directory-structure/