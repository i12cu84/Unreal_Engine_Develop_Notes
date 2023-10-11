//gcc版本检查
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%ld\n",__cplusplus);
    return 0;
}

/*
名字(Name)	宏(Macro)	标准(Standard)
C++98	__cplusplus = 199711L	ISO/IEC 14882:1998
C++11	__cplusplus = 201103L	ISO/IEC 14882:2011
C++14	__cplusplus = 201402L	ISO/IEC 14882:2014
C++17	__cplusplus = 201703L	ISO/IEC 14882:2017
*/