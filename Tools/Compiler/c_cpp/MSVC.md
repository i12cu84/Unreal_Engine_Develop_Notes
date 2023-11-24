MSVC（Microsoft Visual C/C）是一款由微软开发的编译器套件，主要用于编译和运行Windows平台上的C和C++程序。
与Linux系列操作系统不同，Windows原生环境不提供类似gcc、Clang等开源编译器，因此MSVC在Windows平台上扮演着重要的角色。
MSVC编译器工具链主要由两部分组成：cl.exe和link.exe。其中：
cl.exe：这是C/C编译器，用于将源代码编译为通用对象文件格式（COFF）的机器代码。此外，cl.exe还负责编译C/C代码中的静态库和动态库。
link.exe：这是链接器，负责将通用对象文件格式（COFF）机器代码和库文件链接在一起，以创建可执行文件（.exe）或动态链接库（DLL）。
为了使用MSVC，开发者需要下载并安装Microsoft Visual Studio，这是一个集成开发环境（IDE），包含了MSVC编译器、调试器、集成测试器等工具。
在安装过程中，会在PC上生成两个目录：Windows Kits目录（包含所有的Windows 10 SDK文件）和Microsoft Visual Studio目录（包含MSVC的全部编译链接工具链以及大部分函数库与头文件）。
MSVC的环境变量配置需要手动设置，主要包括以下几个方面：
编译器路径：需要将MSVC的编译器（cl.exe）和链接器（link.exe）添加到系统的PATH环境变量中。
编译选项：在编译C/C代码时，需要设置相应的编译选项，例如指定使用静态库还是动态库、是否开启优化等。
头文件路径：需要将MSVC包含的头文件路径添加到编译器的INCLUDE环境变量中。
库文件路径：需要将MSVC提供的库文件路径添加到系统的LIB环境变量中。