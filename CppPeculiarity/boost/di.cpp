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