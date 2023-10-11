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
