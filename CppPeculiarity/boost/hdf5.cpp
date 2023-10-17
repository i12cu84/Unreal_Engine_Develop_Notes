#include <boost/hdf5.hpp>
#include <iostream>

int main() {
    boost::hdf5::file file("data.h5", boost::hdf5::file_flags::read_write);

    if (!file.exists("dataset")) {
        boost::hdf5::dataset dataset = file.create_dataset<int>("dataset", 100);
        std::cout << "Created dataset with 100 elements" << std::endl;
    } else {
        boost::hdf5::dataset dataset = file.open_dataset<int>("dataset");
        std::cout << "Dataset size: " << dataset.size() << " elements" << std::endl;
    }
}
