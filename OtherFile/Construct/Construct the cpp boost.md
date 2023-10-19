download url -> https://www.boost.org/
download 1.83.0 fast -> https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.7z

启动 cmd 
-> cd C:\Program File\boost
-> bootstrap.bat
双击 -> b2.exe

.vscode -> 
c_cpp_properties.json
在其中加入:
"includePath": [
    "C:\\Program File\\boost",
]
tasks.json
在其中加入:
"args": [
    "-I",
    "C:/Program File/mingw/boost"
],

测试代码:
```
#include <iostream>
#include <boost/version.hpp>
#include <boost/config.hpp>
 
using namespace std;
int main()
{
	cout<<BOOST_VERSION<<endl;
	cout<<BOOST_LIB_VERSION<<endl;
	cout<<BOOST_PLATFORM<<endl;
	cout<<BOOST_COMPILER<<endl;
	cout<<BOOST_STDLIB<<endl;
	getchar();
	return 0;
}
```

```
#include <boost/any.hpp>
#include <string>
#include <vector>
#include <iostream>
 
using namespace std;
using namespace boost;
int main()
{
    typedef vector<boost::any> many;
    many a;
    a.push_back(2);
    a.push_back(string("test"));
    for (unsigned int i = 0; i < a.size(); ++i)
    {
        cout << a[i].type().name() << endl;
        try
        {
            int result = any_cast<int>(a[i]);
            cout << result << endl;
        }
        catch (boost::bad_any_cast& ex)
        {
            cout << "cast error:" << ex.what() << endl;
        }
    }
}
```

```
libboost_math_tr1l-mgw132-mt-d-x32-1_70 和 libboost_math_tr1l-mgw132-mt-x32-1_70 是Boost库的两个不同版本，区别在于它们是否启用了调试模式（-d标志）和是否包含了调试信息。

具体区别如下：

libboost_math_tr1l-mgw132-mt-d-x32-1_70 是包含了调试信息的库，通常用于开发和调试阶段。这个库允许你在调试器中跟踪和分析代码，以便更容易排查和解决问题。

libboost_math_tr1l-mgw132-mt-x32-1_70 是编译优化的库，通常用于发布和部署生产环境的应用程序。这个库没有包含调试信息，因此会减小应用程序的大小，提高执行速度。

选择使用哪个库取决于你的需求。在开发阶段，通常会使用带有调试信息的库以便于调试。在发布和部署应用程序时，通常会使用不带调试信息的库以获得更好的性能。

注意：在实际项目中，你可能需要配置你的构建系统，以根据需要选择使用哪个库版本。
```

另外方法2:
boost解压到mingw/include

启动 cmd 
-> cd C:\Program File\mingw\include\tools\build\src\engine
-> .\build.bat gcc

得到一个bin.ntx86_64
-> 内部b2.exe和bjam.exe文件迁移到C:\Program File\mingw\include
启动 cmd 
-> .\b2.exe toolset=gcc

随后在C:\Program File\mingw\include\stage\lib内部东西全部迁移到C:\Program File\mingw\lib
打开vs code的tasks.json,额外加入以下内容
```
{
    "tasks": [
        {
            "args": [
                "-I",//-I <dir>: 添加头文件搜索路径。
                "C:\\Program File\\mingw\\include",
                "-L",//-L <dir>: 添加库文件搜索路径。
                "C:\\Program File\\mingw\\lib",
                "-lbfd",//"C:\\Program File\\mingw\\lib中对应的名字是libfd.a
                "-lboost_atomic-mgw132-mt-d-x32-1_70",//"C:\\Program File\\mingw\\lib中对应的名字是libboost_atomic-mgw132-mt-d-x32-1_70.a
            ]
        }
    ]
}
```