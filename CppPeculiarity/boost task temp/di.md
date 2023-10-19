Boost.DI：用于依赖注入的库，可用于解耦和测试组件。
download：https://github.com/boost-ext/di
示例：使用Boost.DI进行依赖注入。

```cpp
#include <boost/di.hpp>
#include <iostream>

class ILogger {
public:
    virtual void log(const std::string& message) = 0;
};

class ConsoleLogger : public ILogger {
public:
    void log(const std::string& message) override {
        std::cout << "Log: " << message << std::endl;
    }
};

int main() {
    using namespace boost::di;

    auto injector = make_injector(
        bind<ILogger>().to<ConsoleLogger>()
    );

    auto logger = injector.create<ILogger>();
    logger->log("Hello, Boost.DI!");
}
```