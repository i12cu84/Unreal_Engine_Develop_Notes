#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <iostream>
#include <fstream>

class MyData {
public:
    int value;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & value;
    }
};

int main() {
    MyData data;
    data.value = 42;

    // Serialize to a binary file
    std::ofstream ofs("data.bin");
    boost::archive::binary_oarchive oa(ofs);
    oa << data;

    // Deserialize from the binary file
    MyData loadedData;
    std::ifstream ifs("data.bin");
    boost::archive::binary_iarchive ia(ifs);
    ia >> loadedData;

    std::cout << "Loaded data value: " << loadedData.value << std::endl;
}
