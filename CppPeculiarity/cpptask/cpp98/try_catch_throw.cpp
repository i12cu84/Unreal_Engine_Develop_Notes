#include <iostream>
void mightGoWrong() {
    bool error = true;
    if (error) {
        throw "Something went wrong!";
    }
}
int main() {
    try {
        mightGoWrong();
    }
    catch (const char* e) {
        std::cout << "Caught an exception: " << e << std::endl;
    }
    return 0;
}