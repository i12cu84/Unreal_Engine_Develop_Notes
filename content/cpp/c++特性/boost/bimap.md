Boost.Bimap是一个双向映射的容器，它可以通过键或值进行查找。它支持多种数据类型，包括自定义类型。以下是一个简单的Boost.Bimap程序示例，它创建了一个字符串到整数的映射：

```
#include <iostream>
#include <boost/bimap.hpp>

int main()
{
    boost::bimap<std::string, int> bm;

    bm.insert({"one", 1});
    bm.insert({"two", 2});
    bm.insert({"three", 3});

    std::cout << "bm[\"one\"] = " << bm.left.at("one") << "\n";
    std::cout << "bm.right[2] = " << bm.right.at(2) << "\n";

    return 0;
}
```