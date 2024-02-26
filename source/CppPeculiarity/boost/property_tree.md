Boost.PropertyTree：用于操作XML、INI、JSON等配置文件格式的库。
示例：解析JSON配置文件并读取其中的值。

```cpp
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

int main() {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json("config.json", pt);

    std::string username = pt.get<std::string>("user.username");
    int port = pt.get<int>("network.port");

    std::cout << "Username: " << username << std::endl;
    std::cout << "Port: " << port << std::endl;
}
```