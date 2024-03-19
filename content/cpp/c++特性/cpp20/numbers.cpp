#include <iostream>
#include <numbers>

int main() {
    std::cout << "e ≈ " << std::numbers::e_v<double> << std::endl;
    std::cout << "log2e ≈ " << std::numbers::log2e_v<double> << std::endl;
    std::cout << "log10e ≈ " << std::numbers::log10e_v<double> << std::endl;
    std::cout << "π ≈ " << std::numbers::pi_v<double> << std::endl;
    std::cout << "inv_pi π ≈ " << std::numbers::inv_pi_v<double> << std::endl;
    std::cout << "inv_sqrtpi π ≈ " << std::numbers::inv_sqrtpi_v<double> << std::endl;
    std::cout << "ln2 ≈ " << std::numbers::ln2_v<double> << std::endl;
    std::cout << "ln10 ≈ " << std::numbers::ln10_v<double> << std::endl;
    std::cout << "sqrt2 ≈ " << std::numbers::sqrt2_v<double> << std::endl;
    std::cout << "sqrt3 ≈ " << std::numbers::sqrt3_v<double> << std::endl;
    std::cout << "inv_sqrt3 ≈ " << std::numbers::inv_sqrt3_v<double> << std::endl;
    return 0;
}