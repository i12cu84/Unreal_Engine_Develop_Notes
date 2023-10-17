#include <boost/multi_array.hpp>
#include <iostream>

int main() {
    using array_type = boost::multi_array<int, 3>;
    array_type array(boost::extents[2][3][4]);

    int value = 1;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                array[i][j][k] = value++;
            }
        }
    }

    std::cout << "Element at (1, 2, 3): " << array[1][2][3] << std::endl;
}
