Boost.Serialization：用于序列化数据的库，可以将对象转换为二进制或文本格式。
示例：将对象序列化为二进制文件和反序列化。

```cpp
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <iostream>
#include <fstream>

class MyData {
public:
    int value;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & value;
    }
};

int main() {
    MyData data;
    data.value = 42;

    // Serialize to a binary file
    std::ofstream ofs("data.bin");
    boost::archive::binary_oarchive oa(ofs);
    oa << data;

    // Deserialize from the binary file
    MyData loadedData;
    std::ifstream ifs("data.bin");
    boost::archive::binary_iarchive ia(ifs);
    ia >> loadedData;

    std::cout << "Loaded data value: " << loadedData.value << std::endl;
}
```