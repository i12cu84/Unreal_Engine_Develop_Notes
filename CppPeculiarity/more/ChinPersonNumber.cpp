// 暴力计算后四位身份证
#include <iostream>
#include <string>
#include <regex>
using namespace std;
string turn(int a)
{
    string temp;
    while (a != 0)
    {
        temp = (char)(a % 10 + '0') + temp;
        a /= 10;
    }
    int len = temp.length();
    for (int i = 0; i < 4 - len; i++)
        temp = '0' + temp;
    return temp;
}
bool validateIdCard(const std::string &idNumber)
{
    std::regex pattern("^[1-9]\\d{5}(19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[1-2]\\d|3[01])\\d{3}([0-9Xx])$");
    if (std::regex_match(idNumber, pattern))
    {
        int factors[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        int checkSum = 0;
        for (int i = 0; i < 17; ++i)
        {
            checkSum += (idNumber[i] - '0') * factors[i];
        }
        int modResult = checkSum % 11;
        char checkDigit = (modResult == 2) ? 'X' : ('0' + (12 - modResult) % 11);
        if (idNumber.back() == checkDigit)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main()
{
    std::string idNumber = "66666620231103"; // fron 14 num 666666-2023-11-03
    unsigned int n = 0;
    for (int i = 0; i < 10000; i++) // get last 4num ????
    {
        std::string num = idNumber + turn(i);
        if (validateIdCard(num))
        {
            std::cout << num << std::endl;
            n++;
        }
    }
    cout << n << endl;
    return 0;
}