#include <iostream>
using namespace std;
int main()
{
     int num = 0x00636261; // 用16进制表示32位int，0x61是字符'a'的ASCII码
     int *pnum = &num;
     char *pstr = reinterpret_cast<char *>(pnum);
     cout << pnum << " " << *pnum << endl
          << static_cast<void *>(pstr) << " " << pstr << endl;
     // 0x45639ffd24 6513249
     // 0x45639ffd24 abc
     bool b1 = 1;
     int a = 196;
     bool b2 = *reinterpret_cast<bool *>(&a);
     cout << (b1 == b2) << endl
          << int(b1) << " " << b1 << endl
          << int(b2) << " " << b2 << endl;
     // 0
     // 1 1
     // 196 196
     unsigned int b = reinterpret_cast<unsigned int &>(a);
     cout << a << " " << b << endl;
     // 196 196
     return 0;
}