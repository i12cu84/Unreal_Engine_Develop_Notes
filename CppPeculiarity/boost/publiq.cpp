#include <boost/publiq.hpp>
#include <iostream>

void worker_function() {
    // Worker logic
    std::cout << "Worker function called" << std::endl;
}

int main() {
    boost::publiq::distributed_executor executor;
    executor.execute(worker_function);

    // Wait for completion
    executor.wait();

    std::cout << "Execution completed" << std::endl;
}
