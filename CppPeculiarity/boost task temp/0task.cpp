#if 1
// lexcast18_11.cpp -- simple cast from float to string
#include <iostream>
#include <string>
#include "boost/lexical_cast.hpp"
 
int main()
{
    using namespace std;
    cout << "Enter your weight: ";
    float weight;
    cin >> weight;
    string gain = "A 10% increase raises ";
    string wt = boost::lexical_cast<string> (weight);
    gain = gain + wt + " to ";      // string operator()
    weight = 1.1 * weight;
    gain = gain + boost::lexical_cast<string>(weight) + ".";
    cout << gain << endl;
    return 0;
}

#elif 1
#include <boost/random.hpp>
#include <iostream>

int main() {
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 5; ++i) {
        int random_number = dist(gen);
        std::cout << "Random number: " << random_number << std::endl;
    }
}
#elif 1

#include <iostream>
#include <memory>
int main()
{
    int arr[4] = {1, 2, 3, 4};
    int *p1 = std::assume_aligned<16>(arr);
    // 使用p1，而不是arr，以确保从对齐假设中受益。
    // 但是，如果arr没有对齐，无论是否使用p1，程序都具有未定义行为。
    std::cout << *p1 << '\n';
    return 0;
}
#endif