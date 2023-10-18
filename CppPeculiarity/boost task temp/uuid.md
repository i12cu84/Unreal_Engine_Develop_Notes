Boost.Uuid：用于生成和操作通用唯一标识符（UUID）的库。
示例：生成一个随机的UUID。

```cpp
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

int main() {
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();

    std::cout << "Generated UUID: " << uuid << std::endl;
}
```