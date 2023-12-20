//gcc版本检查
#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("%ld\n",__STDC_VERSION__);
    return 0;
}

/*
名字(Name)	宏(Macro)	标准(Standard)
C99	__STDC_VERSION__ = 199901L	ISO/IEC 14882:1999
C11	__STDC_VERSION__ = 201112L	ISO/IEC 14882:2011
C17	__STDC_VERSION__ = 201710L	ISO/IEC 14882:2017
*/