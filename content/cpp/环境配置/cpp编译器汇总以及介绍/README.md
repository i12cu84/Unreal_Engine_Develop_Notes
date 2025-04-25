历史上出现过的主流C和C++编译器有很多，下面介绍一些较为知名和广泛使用的编译器：
| 名字                           | 介绍                                                                                                                                                                     |
| ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| GCC(GNU Compiler Collection)   | GCC是一个开源的编译器套件，包含了C、C++、Java、Fortran等多种编程语言的编译器。GCC的衍生版本众多，如g++、gcc、clang等。GCC在Linux平台下最为常见，同时也支持其他操作系统。 |
| Visual Studio                  | Visual Studio是微软推出的一款集成开发环境(IDE)，其中包含了一整套C/C++编译器、调试器和集成测试工具。Visual Studio支持Windows平台，是许多开发者首选的IDE。                 |
| MSVC(Microsoft Visual C/C)     | 这是微软开发的C/C编译器套件，包含编译器(cl.exe)和链接器(link.exe)，主要用于编译和运行Windows平台上的C和C++程序。                                                         |
| Borland C++                    | Borland C是一款历史悠久的C编译器，由Borland公司开发。它曾在很长一段时间内被视为C++开发的黄金标准，如今仍有许多开发者使用。                                               |
| Watcom C++                     | Watcom C是一款由加拿大公司Watcom开发的C编译器，支持DOS、Windows和Unix平台。Watcom C++以其高性能和广泛的支持而受到好评。                                                  |
| Clang++                        | Clang是LLVM项目的一个分支，是一个C编译器，支持多种操作系统。Clang++的特点是编译速度快、内存占用少，逐渐成为许多开发者的首选。                                            |
| ICC(Intel Compiler Collection) | ICC是英特尔推出的一套编译器套件，包含C、C++、Fortran等编程语言的编译器。ICC主要用于支持英特尔处理器架构，提供高性能的编译器。                                            |
| EDG(Embedded Developer Studio) | EDG是一款由mentor graphics公司开发的C/C编译器，主要用于嵌入式开发领域。EDG支持多种处理器架构和操作系统，具有高性能和紧凑的特点。                                         |

主流集成工具:

| [MinGW(Minimalist GNU for Windows)](https://github.com/niXman/mingw-builds-binaries/releases) |                                                    |
| --------------------------------------------------------------------------------------------- | -------------------------------------------------- |
| gcc                                                                                           | C/C编译器，用于编译C和C++程序。                    |
| g++                                                                                           | C编译器，用于编译C程序。                           |
| gfortran                                                                                      | Fortran编译器，用于编译Fortran程序。               |
| gnat                                                                                          | ADA编译器，用于编译ADA程序。                       |
| mingw32-make                                                                                  | 一个基于Make的构建工具，用于自动化编译和构建项目。 |
    
| [MSYS(Minimal SYStem)](https://www.msys2.org/) |                                                      |
| ---------------------------------------------- | ---------------------------------------------------- |
| gcc                                            | C/C编译器，用于编译C和C++程序。                      |
| g++                                            | C编译器，用于编译C程序。                             |
| bash                                           | 一个命令行解释器，支持Bourne Again Shell(bash)脚本。 |
| make                                           | 一个构建工具，用于自动化编译和构建项目。             |
| python                                         | 一个高级编程语言，提供了一系列内置库和编译器。       |
| Clang                                          | C/C 编译器，用于编译 C 和 C++ 程序。                 |
| Clang++                                        | C++ 编译器，用于编译 C++ 程序。                      |
| LLDB                                           | 一个调试器，用于调试 C/C 程序。                      |
| libclang                                       | LLVM 库，提供了 LLVM 核心功能的实现。                |

| [LLVM(Low Level Virtual Machine)](https://github.com/llvm/llvm-project/releases) |                                                    |
| -------------------------------------------------------------------------------- | -------------------------------------------------- |
| Clang                                                                            | C/C编译器，用于编译C和C++程序。                    |
| LLDB                                                                             | 一个调试器，用于调试C/C程序。                      |
| libclang                                                                         | LLVM库，提供了LLVM核心功能的实现。                 |
| Swift                                                                            | 一个现代编程语言，提供了编译器和运行时环境。       |
| Objective-C                                                                      | 一个面向对象的编程语言，提供了编译器和运行时环境。 |

| [MSVC(Minimalist GNU for Windows)](https://learn.microsoft.com/zh-cn/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022) 或者 [VS(visual studio)](https://visualstudio.microsoft.com/zh-hans/downloads/) |                                                          |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | -------------------------------------------------------- |
| cl.exe                                                                                                                                                                                                                                           | C/C编译器，用于编译C和C++程序。                          |
| link.exe                                                                                                                                                                                                                                         | 链接器，用于将编译后的目标文件链接成可执行文件或动态库。 |
| visualstudio.com                                                                                                                                                                                                                                 | 在线集成开发环境，支持C、C++、Java、Python等编程语言。   |
| MSBuild                                                                                                                                                                                                                                          | 一个构建系统，用于自动化编译、构建和部署过程。           |

# 1. 核心工具链分类

这些工具可以分为 编译器基础设施、编译器前端/后端、工具链移植 和 开发环境 四类：

| 类别           | 工具/项目          | 说明                                                                |
| -------------- | ------------------ | ------------------------------------------------------------------- |
| 编译器基础设施 | LLVM、GCC          | 提供编译器底层架构（如中间表示、优化器、代码生成）。                |
| 编译器前端     | Clang（LLVM）、GCC | 负责解析源代码，生成中间表示（IR）。                                |
| 工具链移植     | MinGW64            | 将 GCC 工具链移植到 Windows 平台，生成原生 Windows 程序。           |
| 开发环境       | MSYS2              | 提供类 Unix 环境和包管理，支持安装多种工具链（如 MinGW64、Clang）。 |
| 独立编译器     | MSVC               | 微软的 C/C++ 编译器，集成于 Visual Studio，专为 Windows 优化。      |
| 辅助工具       | Clangd             | 基于 Clang 的 Language Server，提供代码补全、跳转等 IDE 功能。      |

# 2. 包含关系与交互

## (1) 编译器基础设施与前端
## LLVM

包含 Clang（C/C++ 前端）、LLVM 核心库（优化器、后端代码生成）。

Clangd 是 Clang 的衍生工具，依赖 Clang 解析代码，但不参与编译过程。

示例流程：Clang 解析代码 → LLVM IR → 生成机器码。

## GCC

包含 GCC 前端（解析 C/C++ 等语言）和 GCC 后端（生成目标代码）。

与 LLVM 是独立的项目，但部分工具（如 gcc 和 clang）可互换使用。

## (2) 工具链移植：MinGW64

MinGW64 是 GCC 的 Windows 移植版本，提供：

gcc.exe（Windows 版 GCC 编译器）。

g++.exe（C++ 编译器）。

libstdc++（GNU 标准库）。

依赖关系：MinGW64 基于 GCC，通过 MSYS2 或独立安装包分发。

## (3) 开发环境：MSYS2

MSYS2 是一个 Windows 上的开发环境，核心功能包括：

类 Unix 的 Shell（基于 Cygwin 精简）。

包管理器 pacman，支持安装 MinGW64（GCC）、Clang/LLVM 等工具链。

示例命令：pacman -S mingw-w64-x86_64-gcc（安装 MinGW64 的 GCC）。

## (4) 独立编译器：MSVC

MSVC 是微软的编译器，与 GCC/LLVM 无直接关系，特点包括：

集成于 Visual Studio，直接调用 cl.exe 编译代码。

生成原生 Windows 程序（依赖 MSVCRT 运行时库）。

与 MinGW64 或 Clang 生成的二进制文件 ABI 不兼容。

## (5) 辅助工具：Clangd
Clangd 是 Language Server 工具，依赖 Clang 解析代码，提供 IDE 功能：

需配合编译命令数据库（compile_commands.json）。

可与任意编译器（如 GCC、MSVC）结合，但需确保 Clang 能解析目标代码。

# 3. 工具链的协作场景

# 场景 1：Windows 开发
使用 MSYS2 + MinGW64（GCC）

```
## 安装 MinGW64 的 GCC
pacman -S mingw-w64-x86_64-gcc
## 编译代码
g++ main.cpp -o main.exe
```
## 使用 MSVC
在 Visual Studio 中直接创建项目，MSVC 自动处理编译和链接。

# 场景 2：跨平台开发
使用 Clang/LLVM

```
## Linux/macOS
clang++ main.cpp -o main
## Windows（通过 MSYS2 安装 LLVM）
pacman -S mingw-w64-x86_64-clang
clang++ main.cpp -o main.exe
```

# 场景 3：代码分析与补全
使用 Clangd + 任意编译器

生成 compile_commands.json（如通过 CMake 或 bear 工具），Clangd 自动提供代码提示。

# 4. 总结对比
| 工具    | 依赖关系                 | 主要用途                           | 典型使用场景                     |
| ------- | ------------------------ | ---------------------------------- | -------------------------------- |
| LLVM    | 独立基础设施             | 提供模块化编译器架构               | 跨平台编译器开发、代码优化       |
| Clang   | LLVM的前端               | 解析 C/C++ 代码，生成 LLVM IR      | 与 LLVM 配合编译、静态分析       |
| Clangd  | 依赖 Clang               | 提供 IDE 代码提示和跳转            | 配合 VSCode/CLion 等编辑器       |
| GCC     | 独立编译器集合           | 编译 C/C++ 代码                    | Linux 开发、跨平台项目           |
| MinGW64 | 基于 GCC，移植到 Windows | 在 Windows 上使用 GCC 工具链       | 生成无依赖的 Windows 程序        |
| MSYS2   | 提供环境和包管理         | 安装和管理 MinGW64、Clang 等工具链 | Windows 上的类 Unix 开发环境     |
| MSVC    | 独立于 GCC/LLVM          | 编译原生 Windows 应用              | Visual Studio 项目、DirectX 开发 |

# 5. 关系图
```
+-----------------+
|    LLVM         |←-------+
+-----------------+        |
  |                        |
  v                        |
+-----------------+        |
|     Clang       |←---+   |
+-----------------+    |   |
  |                    |   |
  v                    |   |
+-----------------+    |   |
|    Clangd       |    |   |
+-----------------+    |   |
                       |   |
+-----------------+    |   |
|      GCC        |    |   |
+-----------------+    |   |
  |                    |   |
  v                    |   |
+-----------------+    |   |
|   MinGW64       |----+   |
+-----------------+        |
                           |
+-----------------+        |
|     MSYS2       |--------+
+-----------------+        |
  |                        |
  v                        |
+-----------------+        |
|     MSVC        |←-------+
+-----------------+
```
虚线箭头：MSYS2 可以安装和管理 MinGW64、Clang/LLVM 等工具链。

MSVC 独立于其他工具链，但可通过 CMake 等工具与 MSYS2 环境协作。


LLVM 是编译器“引擎”，Clang 是它的“方向盘”（前端），GCC 是另一套老牌“引擎”；MinGW 是让 GCC 在 Windows 上跑起来的“改装套件”；MSVC 是微软家的“专属引擎”；MSYS2 是 Windows 上的“工具箱”，能装 GCC、Clang 等工具；Clangd 是“智能导航”，帮你写代码时不迷路。

```
具体关系:

LLVM：编译器底层框架，提供优化和生成代码的能力。

Clang：LLVM 的“翻译官”，负责理解 C++ 代码，转交给 LLVM 处理。

Clangd：基于 Clang 的“代码小助手”，帮你补全代码、找错误。

GCC：另一套独立编译器（和 LLVM 是竞争对手）。

MinGW64：把 GCC 移植到 Windows，让 GCC 能编译 Windows 程序。

MSYS2：一个“魔法盒子”，里面可以安装 MinGW 的 GCC、Clang 等工具链。

MSVC：微软的亲儿子编译器，和上面那些都没血缘关系，只爱 Windows。
```