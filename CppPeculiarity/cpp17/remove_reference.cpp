#include <iostream>  
using namespace std;

int main()
{
    int a=1;
    int&b =a;
    remove_reference<decltype(b)>::type c = a;
    printf("a%d b%d c%d \n",a,b,c);

    a=2;
    printf("a%d b%d c%d \n",a,b,c);

    b=3;
    printf("a%d b%d c%d \n",a,b,c);

    c=4;
    printf("a%d b%d c%d \n",a,b,c);
    return 0;
}