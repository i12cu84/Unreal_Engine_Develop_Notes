#include <string>
#include <iostream>
struct Person {
    std::string name;
    int age;
    std::string address;
    void print()
    {
        std::cout << "Name: " << name << "\n";
        std::cout << "Age: " << age << "\n";
        std::cout << "Address: " << address << "\n";
    }
};
Person p1{"John", 25, "123 Main St."};
int main()
{
    p1.print();
    return 0;
}
