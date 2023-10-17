Boost.Random：用于生成伪随机数的库。
示例：生成一些随机整数。

```cpp
#include <boost/random.hpp>
#include <iostream>

int main() {
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 5; ++i) {
        int random_number = dist(gen);
        std::cout << "Random number: " << random_number << std::endl;
    }
}
```