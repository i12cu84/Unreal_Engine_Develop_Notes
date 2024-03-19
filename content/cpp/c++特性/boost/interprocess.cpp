#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>

int main() {
    using namespace boost::interprocess;

    managed_shared_memory segment(create_only, "MySharedMemory", 65536);

    int* shared_data = segment.construct<int>("SharedData")(42);

    // In another process, open the shared memory and access the data
    managed_shared_memory other_segment(open_only, "MySharedMemory");

    int* other_data = other_segment.find<int>("SharedData").first;
    if (other_data) {
        std::cout << "Value in other process: " << *other_data << std::endl;
    }
}