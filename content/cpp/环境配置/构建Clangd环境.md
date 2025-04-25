构建c++的Clangd环境
参考资料https://zhuanlan.zhihu.com/p/613922486

环境准备

先下载好 vscode、llvm 以及 MinGW-W64。

下载并安装 VS Code
下载 VS Code，链接Visual Studio Code，并安装。百度网盘链接：VSCodeUserSetup-x64-1.76.2.exe，提取码：p2i9。

安装 vscode 的时候，建议将下图框框中的两个都选上，如下图示。


安装 vscode
这样我们要打开一个代码工程（文件夹）的时候，直接右键，就可以打开了，如下图示。


右键打开代码工程
下载并安装 LLVM
下载 LLVM，链接 llvm，并安装。百度网盘链接：llvm-16.0.0-win64.exe，提取码：699c。


llvm 下载

llvm 安装

安装位置选择
说明：安装目录可根据自己的爱好，不过建议放在 D 盘下。

下载 MinGW-W64
下载 MinGW-W64 GCC-8.1.0，链接 MinGW-W64。百度网盘链接：x86_64-8.1.0-release-posix-seh-rt_v6-rev0，提取码：66s9。


MinGW-W64 下载
下载后进行解压，如下图示：


解压 MinGW-W64
环境变量相关
MinGW-W64 存放位置
MinGW-W64 解压后，将 mingw64 文件夹中的所有文件拷贝到 LLVM 的安装目录下（D:\Program Files\LLVM）。


拷贝 mingw64 文件夹中的所有文件

拷贝 mingw64 文件夹中的所有文件放到该目录下
由于没有冲突，mingw64 文件夹中的所有文件拷贝到 LLVM后，显示如下图示。


合并文件夹之后显示
添加环境变量
说明：若在安装 LLVM 时，选择了 Add LLVM to the system PATH for all users，则添加环境变量这一步可以省略，因为它会自动添加环境变量。

右键我的电脑，选择属性，进到下图界面。


高级系统设置
点击上图的高级系统设置，进入下图界面。


环境变量设置
点击上图的环境变量，进入下图界面。


系统变量设置
点击上图的 path，进入下图界面。


编辑环境变量
点击上图的新建，如下图示。


增加环境变量
将 LLVM 安装文件下的 bin 文件路径（D:\Program Files\LLVM\bin）拷贝，放到上图的红色框框中，如下图示，然后点击几个确定。


编辑环境变量
环境变量是否生效
按住 win+R 在框框中输入 cmd，进到 dos 界面，再输入 clang++ -v，查看显示是否如下图示。


查看 clang 是否生效
当然也可以输入 g++ -v。


查看 g++ 是否生效
如果输入上述指令，没有上图相对应的显示，重启一下 pc，再试一下，就会有了。

至次，前期准备工作基本完成。

测试相关
如果 pc 上尚未安装 MSVC，例如 Visual Studio 20XX 之类的，用记事本或者其它的文本编辑器，随便写一段简单无误的代码 hello.cpp，如下：
```
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
```
然后直接通过 dos 界面去编译，会报错，如下图示。


直接通过 clang++ 编译代码
主要原因：clang 的 target 是 msvc，从上面图中的 clang++ -v 输出可以看出，使用其标准库和各种头文件。也可以看下图。


clang 编译时查找头文件和库文件
从上图可知，clang++ 在编译时，一直在 **/VC 文件夹中寻找头文件。

如果安装了全套的 Visual Studio，使用 clang++ 编译 cpp 文件，clang 会去查找相应的 C++ 库，其实只需要安装 Visual Studio Build Tools 即可。

要想在 MinGW 模式下运行，且不安装 MSVC 相关组件，可以通过添加 target 选项来编译，例如：--target=x86_64-w64-windows-gnu 或 --target=x86_64-w64-mingw 将 target 改为 mingw，运行结果如下图示。


增加 target 编译选项运行
代码相关
插件安装
打开 vscode，界面显示如下图示，点击右下角的安装并重启，即可将语言设置为中文了。


设置 vscode 语言为中文
在 vscode 界面上，按住 Ctrl+Shift+X 或者直接点击下图位置，如下图示。


打开扩展商店
在扩展商店里面输入 C/C++ 和 clangd，并点击安装进行安装，如下图示。


安装C/C++插件

安装 clangd 插件
由于同时安装了 C/C++ 和 clangd 插件，并且这两个插件都有代码自动补全或者提示功能，因此会出现冲突的情况，暂时忽略不管，下文中有注意点解释。

代码编辑
在 pc 上新建一个文件夹（例如：huawei），然后右键选择通过 code 打开，再点击下图圆形框框，新建一个 test.cpp 文件，并输入一段代码并保存。


vscode 打开文件夹
```
#include <iostream>
using namespace std;

int main() {
    cout << "Come on HuaWei, Come on China" << endl;
    return 0;
}
```
此时 test.cpp 的界面显示如下，可能在头文件、cout 和 endl 下会出现红色的波浪线。


当前界面显示
然后点击终端，选择新建终端，如下图示。


新建终端
此时底下的问题栏，也会提示当前代码的一些问题，如下图示。


问题栏提示当前存在的问题
运行 test.cpp，点击下图中方框位置，然后选择 C/C++:g++.exe，如下图示。


运行 test.cpp
此时终端会输出运行结果，如下图示。


运行结果
vscode 的左侧会多出一个 .vscode 文件夹，文件夹里面有 tasks.json 文件，还会生成一个 test.exe 文件，如下图示。


生成 tasks.json
自动生成的 tasks.json 如下：
```
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe 生成活动文件",
            "command": "D:\\Program Files\\LLVM\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```
tasks.json 中的 type 是任务的类型。对自定义任务来说，type 可以是 shell 或 process。如果是 shell，命令被解释为 shell 命令（例如，bash、cmd 或 PowerShell）；否则，命令被解释为一个将要执行的进程。

label 是用在用户界面的任务的标签。

其它参数，可以参考官方文档。

再在当前 test.cpp 界面，点击下图中的正方形框，然后再选择 C/C++:g++.exe，会自动创建 launch.json 文件，如下图示。


创建 launch.json
自动生成的 launch.json 文件如下。
```
{
    "configurations": [
        {
            "name": "C/C++: g++.exe 生成和调试活动文件",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\Program Files\\LLVM\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++.exe 生成活动文件"
        }
    ],
    "version": "2.0.0"
}
```
launch.json 中的 name 是对阅读者友好的名称，出现在调试启动配置下拉列表，如下图示。


launch.json 中 name 对应 vscode 界面位置
type 是用于此次启动配置的调试器的类型。

request 是用于此次启动配置的请求类型。

其它参数可以参考官方文档。

修改 launch.json，如下所示。
```
{
    "configurations": [
        {
            "name": "(gdb) Launch",// 配置名称，将会在启动配置的下拉菜单中显示
            "type": "cppdbg",// 配置类型，对于C/C++可认为此处只能是cppdbg，由cpptools提供；不同编程语言不同
            "request": "launch",// 请求配置类型，可以为launch（启动）或attach（附加）
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",// 将要进行调试的程序的路径
            "args": [],// 程序调试时传递给程序的命令行参数，一般设为空
            "stopAtEntry": false,// 设为true时程序将暂停在程序入口处，相当于在main上打断点
            "cwd": "${workspaceFolder}",// 调试程序时的工作目录，此为工作区文件夹；改成${fileDirname}可变为文件所在目录
            "environment": [],// 环境变量
            "externalConsole": true,//true 显示外置的控制台窗口，false 显示内置终端
            "MIMode": "gdb",// 指定连接的调试器
            "miDebuggerPath": "D:\\Program Files\\LLVM\\bin\\gdb.exe", // 调试器路径，Windows下后缀不能省略
            "setupCommands": [
                {// 模板自带
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {// 模板自带
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: clang++.exe 生成活动文件"// 调试前执行的任务，一般为编译程序。与tasks.json的label相对应
        }
    ],
    "version": "2.0.0"
}
```
再将 tasks.json 修改如下。
```
{
    "tasks": [
        {
            "type": "process",
            "label": "C/C++: clang++.exe 生成活动文件",// 任务名称，与launch.json的preLaunchTask相对应
            "command": "D:\\Program Files\\LLVM\\bin\\clang++.exe", // 要使用的编译器，C++用clang++
            "args": [
                "-fcolor-diagnostics",
                "-fansi-escape-codes",   
                "-g",   // 生成和调试有关的信息
                "${file}",
                "-o",  // 指定输出文件名，不加该参数则默认输出a.exe 
                "${fileDirname}\\${fileBasenameNoExtension}.exe",
                "--target=x86_64-w64-mingw",// 默认target为msvc，不加这一条就会找不到头文件
                "-Wall", // 开启额外警告
                "-static-libgcc", // 静态链接libgcc，一般都会加上
                "-std=c++1z" // c++1z即c++17，C语言最新标准为c11，或根据自己的需要进行修改 
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "group": {
                "kind": "build",
                "isDefault": true// 设为false可做到一个tasks.json配置多个编译指令，需要自己修改本文件
            },
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": [
                    "relative",
                    "/"
                ],
                "pattern": {
                    "regexp": "^(.*):(\\d+):(\\d+):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            },
            "detail": "编译器: \"D:\\Program Files\\LLVM\\bin\\clang++.exe\""
        }
    ],
    "version": "2.0.0"
}
```
注意点

tasks.json 中的 label 必须与 launch.json 中的 preLaunchTask 保持一致。
在 tasks.json 中的编译参数 args 中必须添加--target=x86_64-w64-mingw，否则因为找不到头文件而导致编译出错，如下图示。

编译报错
此时，再修改 test.cpp 成如下代码。
```
#include <iostream>
using namespace std;

int main() {
    cout << __cplusplus << endl;
    cout << "Come on HuaWei, Come on China" << endl;
    system("pause");
    return 0;
}
```
再点击运行，选择以非调试模式运行，如下图示。


运行代码
运行结果如下图示。


运行结果
配置 c_cpp_properties.json
在 vscode 界面上，按住 Ctrl+Shift+P，在跳出的输入框中输入 C/C++，点击 C/C++:编辑配置(UI)，就可生成 c_cpp_properties.json。


生成 c_cpp_properties.json
此时再在 UI 界面的编译器路径下，选择 D:\Program Files\LLVM\bin\clang++.exe，如下图示。


选择编译器路径
然后再在 IntelliSense 模式中选择 clang-x64(legacy)，如下图示。


选择 IntelliSense 模式
C 和 C++ 标准，选择 C17 和 C++17，如下图示。


选择 c/c++ 标准
此时 c_cpp_properties.json 文件中的内容如下：
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:/Program Files/LLVM/bin/clang++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
}
```
test.cpp 界面的问题栏会提示如下错误。


#include 错误
此时只需要把鼠标放到 #include 那里，然后点击小黄色灯泡，选择编辑 “includePath”设置，如下如示。


修复找不到头文件的错误
此时界面会跳转到 IntelliSense 配置界面，如下图示。


跳转到 IntelliSense 配置界面
打开 dos 界面，输入脚本：gcc -v -E -x c++ -，如下图示。


输入脚本后显示
将上图中红色框框中的路径拷贝到 IntelliSense 配置界面中的包含路径中，如下图示。


修改 IntelliSense 配置 中的包含路径
此时，c_cpp_properties.json 中的 includePath 多了这些刚添加的路径，如下所示示。
```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/x86_64-w64-mingw32",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include/c++/backward",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/include-fixed",
                "D:/Program Files/LLVM/bin/../lib/gcc/x86_64-w64-mingw32/8.1.0/../../../../x86_64-w64-mingw32/include"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:/Program Files/LLVM/bin/clang++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64"
        }
    ],
    "version": 4
}
```
同时，之前 test.cpp 界面的问题栏会提示检测到#include错误随之消失，如下图示。


#include 头文件错误消失
注意点

说明：暂时可以忽略这个冲突，不管它，等配置完成之后再修改。

1、同时安装了 C/C++ 和 clangd 插件后，由于这两个插件都有代码自动补全或者提示功能，所以需要 disable 其中一个，如下图示，可以直接点击 Disable IntelliSense。


解决冲突
2、虽然上面的操作，可以解决冲突，但这会带来另外一个问题，如果需要修改 UI 中一些配置或者 json 文件，通过 Ctrl+Shift+P 的方式，再在输入栏中输入，操作后会出现失败的情况，具体如下图示。


修改配置
3、随便点击上图中框框中下面的任何一个，会出现失败的情况，如下图示。


失败提示
4、此时，需要进行如下操作，点击下图中的椭圆形框，然后点击扩展设置，然后再输入 intell，将 C_Cpp:Intelli Sense Engine 框框中的 diabled 下拉选择 default 即可。


修改 C/C++ 扩展设置

具体修改位置
此时会出现注意点 1 中的问题，按照 1 中的方法去处理即可。

代码格式配置
在这里主要介绍采用 Clang-Format 对代码进行格式化。由于 C/C++ 插件包含了 clang-format，因此不需要单独安装 clang-format 插件了。


C/C++ 插件中包含 clang-format
也可以参考官方Edit C++ in Visual Studio Code。

clang-format 默认安装路径为：C:\Users\Administrator\.vscode\extensions\ms-vscode.cpptools-1.14.5-win32-x64\LLVM\bin，也就是用户的 .vscode 文件夹下面，如下图示。


clang-format.exe 存放位置
首选项设置
1、点击文件，选择首选项，再点击设置，如下图示。


打开首选项设置
2、在文本框中输入 format on save，勾选前面的正方形，如下图示。


保存文件时设置文件格式
3、在文本框中再输入 Clang_format_style，查看 C_Cpp:Clang_format_style 下面的文本框中是否显示 file，若是，则调用在 workspace 中的 .clang-format。如下图示。


修改 Clang_format_style
4、在文本框中再输入 Clang_format_fallback Style，如果上面的第 3 个中设置的是 file，但无 .clang-format 文件，则会按照 C_Cpp:Clang_format_fallback Style 下面的文本框中显示的规则。如下图示。


Clang_format_fallback Style 设置
.clang-format
1、进入到路径：C:\Users\Administrator\.vscode\extensions\ms-vscode.cpptools-1.14.5-win32-x64\LLVM\bin，然后再选中并输入 cmd，进到命令行模式，如下图示。


在 clang-format 默认安装路径中输入 cmd
2、在命令行中输入：clang-format -style="llvm" --dump-config > .clang-format，如下图示。


命令行中输入脚本
3、此时该路径下，会出现一个新的文件 .clang-format，如下图示。


生成 .clang-format
4、用文本编辑器打开 .clang-format，如下所示，可以修改里面的参数，进而变成自己想要的格式。

```
---
Language:        Cpp
# BasedOnStyle:  LLVM
AccessModifierOffset: -2
AlignAfterOpenBracket: Align
AlignArrayOfStructures: None
AlignConsecutiveAssignments:
  Enabled:         false
  AcrossEmptyLines: false
  AcrossComments:  false
  AlignCompound:   false
  PadOperators:    true
AlignConsecutiveBitFields:
  Enabled:         false
  AcrossEmptyLines: false
  AcrossComments:  false
  AlignCompound:   false
  PadOperators:    false
AlignConsecutiveDeclarations:
  Enabled:         false
  AcrossEmptyLines: false
  AcrossComments:  false
  AlignCompound:   false
  PadOperators:    false
AlignConsecutiveMacros:
  Enabled:         false
  AcrossEmptyLines: false
  AcrossComments:  false
  AlignCompound:   false
  PadOperators:    false
AlignEscapedNewlines: Right
AlignOperands:   Align
AlignTrailingComments:
  Kind:            Always
  OverEmptyLines:  0
AllowAllArgumentsOnNextLine: true
AllowAllParametersOfDeclarationOnNextLine: true
AllowShortBlocksOnASingleLine: Never
AllowShortCaseLabelsOnASingleLine: false
AllowShortEnumsOnASingleLine: true
AllowShortFunctionsOnASingleLine: All
AllowShortIfStatementsOnASingleLine: Never
AllowShortLambdasOnASingleLine: All
AllowShortLoopsOnASingleLine: false
AlwaysBreakAfterDefinitionReturnType: None
AlwaysBreakAfterReturnType: None
AlwaysBreakBeforeMultilineStrings: false
AlwaysBreakTemplateDeclarations: MultiLine
AttributeMacros:
  - __capability
BinPackArguments: true
BinPackParameters: true
BitFieldColonSpacing: Both
BraceWrapping:
  AfterCaseLabel:  false
  AfterClass:      false
  AfterControlStatement: Never
  AfterEnum:       false
  AfterExternBlock: false
  AfterFunction:   false
  AfterNamespace:  false
  AfterObjCDeclaration: false
  AfterStruct:     false
  AfterUnion:      false
  BeforeCatch:     false
  BeforeElse:      false
  BeforeLambdaBody: false
  BeforeWhile:     false
  IndentBraces:    false
  SplitEmptyFunction: true
  SplitEmptyRecord: true
  SplitEmptyNamespace: true
BreakAfterAttributes: Never
BreakAfterJavaFieldAnnotations: false
BreakArrays:     true
BreakBeforeBinaryOperators: None
BreakBeforeConceptDeclarations: Always
BreakBeforeBraces: Attach
BreakBeforeInlineASMColon: OnlyMultiline
BreakBeforeTernaryOperators: true
BreakConstructorInitializers: BeforeColon
BreakInheritanceList: BeforeColon
BreakStringLiterals: true
ColumnLimit:     80
CommentPragmas:  '^ IWYU pragma:'
CompactNamespaces: false
ConstructorInitializerIndentWidth: 4
ContinuationIndentWidth: 4
Cpp11BracedListStyle: true
DerivePointerAlignment: false
DisableFormat:   false
EmptyLineAfterAccessModifier: Never
EmptyLineBeforeAccessModifier: LogicalBlock
ExperimentalAutoDetectBinPacking: false
FixNamespaceComments: true
ForEachMacros:
  - foreach
  - Q_FOREACH
  - BOOST_FOREACH
IfMacros:
  - KJ_IF_MAYBE
IncludeBlocks:   Preserve
IncludeCategories:
  - Regex:           '^"(llvm|llvm-c|clang|clang-c)/'
    Priority:        2
    SortPriority:    0
    CaseSensitive:   false
  - Regex:           '^(<|"(gtest|gmock|isl|json)/)'
    Priority:        3
    SortPriority:    0
    CaseSensitive:   false
  - Regex:           '.*'
    Priority:        1
    SortPriority:    0
    CaseSensitive:   false
IncludeIsMainRegex: '(Test)?$'
IncludeIsMainSourceRegex: ''
IndentAccessModifiers: false
IndentCaseBlocks: false
IndentCaseLabels: false
IndentExternBlock: AfterExternBlock
IndentGotoLabels: true
IndentPPDirectives: None
IndentRequiresClause: true
IndentWidth:     2
IndentWrappedFunctionNames: false
InsertBraces:    false
InsertNewlineAtEOF: false
InsertTrailingCommas: None
IntegerLiteralSeparator:
  Binary:          0
  Decimal:         0
  Hex:             0
JavaScriptQuotes: Leave
JavaScriptWrapImports: true
KeepEmptyLinesAtTheStartOfBlocks: true
LambdaBodyIndentation: Signature
LineEnding:      DeriveLF
MacroBlockBegin: ''
MacroBlockEnd:   ''
MaxEmptyLinesToKeep: 1
NamespaceIndentation: None
ObjCBinPackProtocolList: Auto
ObjCBlockIndentWidth: 2
ObjCBreakBeforeNestedBlockParam: true
ObjCSpaceAfterProperty: false
ObjCSpaceBeforeProtocolList: true
PackConstructorInitializers: BinPack
PenaltyBreakAssignment: 2
PenaltyBreakBeforeFirstCallParameter: 19
PenaltyBreakComment: 300
PenaltyBreakFirstLessLess: 120
PenaltyBreakOpenParenthesis: 0
PenaltyBreakString: 1000
PenaltyBreakTemplateDeclaration: 10
PenaltyExcessCharacter: 1000000
PenaltyIndentedWhitespace: 0
PenaltyReturnTypeOnItsOwnLine: 60
PointerAlignment: Right
PPIndentWidth:   -1
QualifierAlignment: Leave
ReferenceAlignment: Pointer
ReflowComments:  true
RemoveBracesLLVM: false
RemoveSemicolon: false
RequiresClausePosition: OwnLine
RequiresExpressionIndentation: OuterScope
SeparateDefinitionBlocks: Leave
ShortNamespaceLines: 1
SortIncludes:    CaseSensitive
SortJavaStaticImport: Before
SortUsingDeclarations: LexicographicNumeric
SpaceAfterCStyleCast: false
SpaceAfterLogicalNot: false
SpaceAfterTemplateKeyword: true
SpaceAroundPointerQualifiers: Default
SpaceBeforeAssignmentOperators: true
SpaceBeforeCaseColon: false
SpaceBeforeCpp11BracedList: false
SpaceBeforeCtorInitializerColon: true
SpaceBeforeInheritanceColon: true
SpaceBeforeParens: ControlStatements
SpaceBeforeParensOptions:
  AfterControlStatements: true
  AfterForeachMacros: true
  AfterFunctionDefinitionName: false
  AfterFunctionDeclarationName: false
  AfterIfMacros:   true
  AfterOverloadedOperator: false
  AfterRequiresInClause: false
  AfterRequiresInExpression: false
  BeforeNonEmptyParentheses: false
SpaceBeforeRangeBasedForLoopColon: true
SpaceBeforeSquareBrackets: false
SpaceInEmptyBlock: false
SpaceInEmptyParentheses: false
SpacesBeforeTrailingComments: 1
SpacesInAngles:  Never
SpacesInConditionalStatement: false
SpacesInContainerLiterals: true
SpacesInCStyleCastParentheses: false
SpacesInLineCommentPrefix:
  Minimum:         1
  Maximum:         -1
SpacesInParentheses: false
SpacesInSquareBrackets: false
Standard:        Latest
StatementAttributeLikeMacros:
  - Q_EMIT
StatementMacros:
  - Q_UNUSED
  - QT_REQUIRE_VERSION
TabWidth:        8
UseTab:          Never
WhitespaceSensitiveMacros:
  - BOOST_PP_STRINGIZE
  - CF_SWIFT_NAME
  - NS_SWIFT_NAME
  - PP_STRINGIZE
  - STRINGIZE
...
```

设置 .clang-format 生效
1、将生成的 .clang-format 文件拷贝一份放到当前的 workspace，如下图示。


拷贝 clang-format 放到当前工程目录下
2、此时再在 test.cpp 界面，右键，点击格式化文档，如下图示。


格式化 test.cpp
3、此时会弹出一个界面，如下图示，需要配置默认格式化程序，此时点击配置。


配置默认格式化程序
4、然后点击 clangd，如下图示。


选择默认的格式化程序
5、格式化之后 test.cpp 文件显示如下，此时文件中的函数中的每行首行代码变为两空格，由于此时文件还尚未保存，如果想要保存的话，需要 Ctrl + S 保存一下。如下图示。


格式化后显示
此时每行首行代码变为两空格，原因是：由于 .clang-format 中的参数 IndentWidth 的值是 2，如下图示，因此格式化后显示每行首行代码变为两空格，可以通过修改 IndentWidth 的值改变每行首行代码的空格数。


修改 IndentWidth 改变行首空格数
6、将 .clang-format 文件 中的参数 IndentWidth 的值改为 4，然后保存一下后，每行首行代码变为四空格，如下图示。


修改 .clang-format 中参数值后，重新格式化显示
消除代码中红色的波浪线
从上图中，可以看出，test.cpp 文件中的代码，有不少关键字出现了红色的波浪线，例如：iostream、std、cout等，虽然代码能编译过，答案也完全正确，但很不美观，而且会让人在视觉上觉得代码有问题，这主要是因为这些关键字没有关联上相应的头文件，可以按照以下步骤去消除它们。

1、点击 vscode 界面左上方的文件，选择首选项，再点击设置，在文本框中输入 clangd path，如下图示。


设置 clangd path
2、在 Clangd:Path 下面的文本框中填写 C:\Users\Administrator\.vscode\extensions\ms-vscode.cpptools-1.14.5-win32-x64\LLVM\bin，如下图示。


修改 clangd path
3、按住 Ctrl+Shift+P 并在输入框中输入 reload，选择开发人员：重新加载窗口，如下图示。


重新加载 vscode
4、重新加载完成之后，神奇的一幕出现了，之前的红色的波浪线全部消失了，如下图示。


消除代码下的红色波浪线
配置 settings.json
按下键盘 F1 或者按下 Ctrl+Shift+P 并在输入框中输入 open settings，选择首选项：打开用户设置(JSON)，此时进入 settings.json 文件，如下图示。


打开 settings.json 文件
由于前面设置了保存时格式化文件、默认格式化以及 clangd path，因此当前的 settings.json 主要包含了这些项，如下图示。

settings.json
```
{
    "workbench.colorTheme": "Default Dark+",
    "editor.formatOnSave": true,
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    },
    "clangd.path": "C:\\Users\\Administrator\\.vscode\\extensions\\ms-vscode.cpptools-1.14.5-win32-x64\\LLVM\\bin"
}
```
下文会继续修改 settings.json 。

好用的插件推荐
Code Runner

Code Runner 插件
code runner 可以快捷地运行各类代码或代码片段，其安装方法跟上文安装 C/C++ 和 clangd 插件一样，安装完，重新加载界面后，点击界面右侧的三角形图标后面的下拉框，会出现三个选项，其中一个是 Run Code，如下图示。


安装 Code Runner 后显示
code runner 运行代码的几种方法

1、直接点击上图中的 Run Code，如下图示。


通过 code runner 运行 test.cpp
2、在 test.cpp 界面中的代码编辑区，单击鼠标右键，选择 Run Code 来运行代码，如下图示。


单击右键，通过 code runner 运行代码
3、在左侧的文件管理器中，右键点击 test.cpp 选择 Run Code，如下图示。


文件管理器中通过 code runner 运行代码
4、按下键盘 F1 或者按下 Ctrl+Shift+P 并在输入框中输入 Run Code，或者直接按快捷键 Ctrl+Alt+N 来运行代码，如下图示。


快捷键通过 code runner 运行代码
停止代码运行的方法

1、点击界面右侧的小正方形，如下图示。


点击小正方形停止运行代码
2、在下方的输出框，鼠标右键单击，选择 Stop Code Run，如下图示。


输出框右键结束代码运行
3、按下键盘 F1 或者按下 Ctrl+Shift+P 并在输入框中输入 Stop Code Run，或者直接按快捷键 Ctrl+Alt+M 来结束正在运行代码，如下图示。


快捷键结束代码运行
修改代码后自动保存

可以通过修改 Code Runner 插件中的某些扩展设置，让代码在修改之后运行之前自动保存。

1、如下图示，点击下图中的次轮状，然后选择扩展设置，如下图示。


打开 code runner 的扩展设置
2、在输入框中输入 save，此时界面显示 Code-runner:Save All Files Before Run 和 Code-runner:Save File Before Run，根据需要将下图中的小正方形打勾，可以都勾上。


代码修改，运行前自动保存
此时的 settings.json 变为如下：
```
{
    "workbench.colorTheme": "Default Dark+",
    "editor.formatOnSave": true,
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    },
    "clangd.path": "C:\\Users\\Administrator\\.vscode\\extensions\\ms-vscode.cpptools-1.14.5-win32-x64\\LLVM\\bin",
    "code-runner.saveAllFilesBeforeRun": true,
    "code-runner.saveFileBeforeRun": true
}
```
代码在终端运行

由于 vscode 内置了终端，因此可以通过修改 Code Runner 插件中的某些扩展设置，让代码在终端中运行。

修改方法如下图示，在输入框中输入 terminal，然后将 Code-runner:Run In Terminal 下方的小正方形打勾。


让代码在终端运行
点击界面右侧的小三角形，运行 test.cpp 结果如下图示，并且中文不出现乱码。


代码在终端中运行
此时的 settings.json 变为如下：
```
{
    "workbench.colorTheme": "Default Dark+",
    "editor.formatOnSave": true,
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    },
    "clangd.path": "C:\\Users\\Administrator\\.vscode\\extensions\\ms-vscode.cpptools-1.14.5-win32-x64\\LLVM\\bin",
    "code-runner.saveAllFilesBeforeRun": true,
    "code-runner.saveFileBeforeRun": true,
    "code-runner.runInTerminal": true
}
```
修改对编译的设置

Code Runner 插件可以修改编译选项，如下图示，在输入框中输入 executorMap，然后点击 Code-runner:Executor Map 下方的在 settings.json 中编辑。


修改编译选项
此时 settings.json 中会增加如下图示的脚本。


settings.json 内容变化
由于我们主要是针对 C++ 代码，因此需要修改如下脚本：

"cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
修改之后变成如下，因为采用的 clang++ 而不是 g++，所以改为 clang++，并增加了编译选项。

"cpp": "cd $dir && clang++ $fileName -o $fileNameWithoutExt.exe -Wall -g -Og -static-libgcc -fcolor-diagnostics --target=x86_64-w64-mingw -std=c++1z && $dir$fileNameWithoutExt"
此时再点击 test.cpp 界面右侧有个三角形图标，编译结果如下：


更改编译选项之后的编译结果
由于当前只使用 C/C++ 编译代码，因此可以将 code-runner.executorMap 中其它部分删除，此时的 settings.json 变成如下所示：
```
{
    "workbench.colorTheme": "Default Dark+",
    "editor.formatOnSave": true,
    "[cpp]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    },
    "clangd.path": "C:\\Users\\Administrator\\.vscode\\extensions\\ms-vscode.cpptools-1.14.5-win32-x64\\LLVM\\bin",
    "code-runner.saveAllFilesBeforeRun": true,
    "code-runner.saveFileBeforeRun": true,
    "code-runner.runInTerminal": true,
    "code-runner.executorMap": {
        "c": "cd $dir && clang $fileName -o $fileNameWithoutExt.exe -Wall -g -Og -static-libgcc -fcolor-diagnostics --target=x86_64-w64-mingw -std=c11 && $dir$fileNameWithoutExt",
        "cpp": "cd $dir && clang++ $fileName -o $fileNameWithoutExt.exe -Wall -g -Og -static-libgcc -fcolor-diagnostics --target=x86_64-w64-mingw -std=c++1z && $dir$fileNameWithoutExt"
    }
}
```
tabnine

tabnine 插件
自动补全的编码插件，不同于一般的自动补全插件，它使用了深度学习来帮助我们补全代码。

其安装方法跟上文安装 C/C++ 、clangd 和 Code Runner 插件一样。


tabnine 插件自动提示和补全