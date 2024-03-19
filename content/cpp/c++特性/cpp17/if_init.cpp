#include <iostream>
#include <string>
using namespace std;
int main()
{
    // if (init; condition)
    string str = "Hi World";
    if (auto [pos, size] = pair(str.find("Hi"), str.size()); pos != string::npos) {
        std::cout << pos << " Hello, size is " << size;
    }
}