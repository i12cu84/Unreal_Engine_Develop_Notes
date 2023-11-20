#include <stdio.h>
#include <typeinfo>
#include <iostream>

#define MAX1(x, y) ({                \
    decltype(x) _max1 = (x);         \
    decltype(y) _max2 = (y);         \
    (void) (&_max1 == &_max2);       \
    _max1 > _max2 ? _max1 : _max2;})

#define MAX2(a,b) ((a>b)? a:b)

int main(int argc, char *argv[])
{
    int a = 1;
    float b = 1.1;
    int c = 0;
    
    c = MAX1(1,2);
    printf("max0:%d\n", c);
    
    c = MAX2(a,b);
    printf("max1:%d\n", c);

    return 0;
}
