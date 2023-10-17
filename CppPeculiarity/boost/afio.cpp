#include <boost/afio.hpp>
#include <iostream>

int main() {
    boost::afio::async_file file("example.txt", boost::afio::file_flags::read);
    boost::afio::file_handle::const_buffer_type buffer(1024);

    file.read(buffer).get();
    std::cout << "Read: " << buffer.data() << std::endl;
}
