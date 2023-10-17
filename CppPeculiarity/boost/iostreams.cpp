#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>

int main() {
    boost::iostreams::mapped_file_source file("example.txt");

    if (file.is_open()) {
        std::cout << "File size: " << file.size() << " bytes" << std::endl;
        std::cout.write(file.data(), file.size());
    }
}
