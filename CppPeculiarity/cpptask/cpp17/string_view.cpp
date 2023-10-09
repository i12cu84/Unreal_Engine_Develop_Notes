#include <iostream>
#include <string_view>
int main() {
    /*
    std::string myString = "Hello, World!";// 创建一个字符串
    std::string_view myStringView(myString);// 创建一个string_view，指向myString的数据
    std::cout << "String View: " << myStringView << std::endl;// 输出字符串视图的内容
    std::cout << "Length: " << myStringView.length() << std::endl;// 访问字符串视图的长度
    std::string_view subStringView = myStringView.substr(0, 5);// 使用字符串视图的substr方法创建一个子视图
    std::cout << "Sub String View: " << subStringView << std::endl;// 输出子视图的内容
    */
    std::string originalString = "Hello, World!";
    std::string_view stringView(originalString);
    std::cout << "Original View: " << originalString << std::endl;
    std::cout << "String View: " << stringView << std::endl;

    originalString += " This is a new part.";
    std::cout << "Original View: " << originalString << std::endl;
    std::cout << "String View: " << stringView << std::endl;

    return 0;
}
