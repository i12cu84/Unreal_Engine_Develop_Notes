Boost.Log：用于日志记录的库。
示例：记录日志到文件。

```cpp
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

int main() {
    boost::log::add_file_log("sample.log");

    BOOST_LOG_TRIVIAL(info) << "This is an informational message.";
    BOOST_LOG_TRIVIAL(error) << "An error occurred.";

    return 0;
}
```