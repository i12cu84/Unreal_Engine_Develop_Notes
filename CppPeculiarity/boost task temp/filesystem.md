Boost.Filesystem：用于文件系统操作的库。
示例：列出指定目录中的所有文件。

```cpp
#include <boost/filesystem.hpp>
#include <iostream>

int main() {
    boost::filesystem::path directory_path("/path/to/directory");

    if (boost::filesystem::is_directory(directory_path)) {
        for (auto& entry : boost::filesystem::directory_iterator(directory_path)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
}
```