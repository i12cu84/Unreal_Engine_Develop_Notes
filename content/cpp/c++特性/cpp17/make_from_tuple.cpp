#include <iostream>
#include <tuple>
struct Person
{
    std::string name;
    int age;
    Person(const std::string &n, int a) : name(n), age(a) {}
};
int main()
{
    std::tuple<std::string, int> personData("Alice", 30);
    // 使用 std::make_from_tuple 创建 Person 对象
    Person alice = std::make_from_tuple<Person>(personData);
    std::cout << "Name: " << alice.name << ", Age: " << alice.age << std::endl;
    return 0;
}
