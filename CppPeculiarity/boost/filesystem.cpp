#include <iostream>
#include <boost/filesystem.hpp>

int main() {
    boost::filesystem::path directory_path("/path/to/directory");

    if (boost::filesystem::is_directory(directory_path)) {
        for (auto& entry : boost::filesystem::directory_iterator(directory_path)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
}
