#include <boost/simd/pack.hpp>
#include <iostream>

int main() {
    boost::simd::pack<float, 4> a{1.0f, 2.0f, 3.0f, 4.0f};
    boost::simd::pack<float, 4> b{2.0f, 2.0f, 2.0f, 2.0f};
    boost::simd::pack<float, 4> result = a + b;

    for (int i = 0; i < 4; ++i) {
        std::cout << "Result[" << i << "] = " << result[i] << std::endl;
    }
}
