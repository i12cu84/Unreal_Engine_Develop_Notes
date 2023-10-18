Boost.MPL：用于元编程的库，支持在编译时操作类型和数据结构。
示例：使用boost::mpl编写元编程代码。

```cpp
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <iostream>

namespace mpl = boost::mpl;

int main() {
    typedef mpl::vector<int, double, float> types;

    typedef mpl::transform<types, mpl::_1 const&>::type const_types;

    std::cout << "Original Types: ";
    mpl::for_each<types>(std::cout << mpl::_1() << " ");
    std::cout << std::endl;

    std::cout << "Constant Types: ";
    mpl::for_each<const_types>(std::cout << mpl::_1() << " ");
    std::cout << std::endl;
}
```