#include <iostream>
using namespace std;

int main()
{
    int array[] = { 1,2,3,4 };
    int *p = array;
    printf("*p++ = %d \n", *p++);//先取值，后指针++，A = *p；
    printf("*++p = %d \n", *++p);//先指针++，后取值， A = *(++p)；
    printf("++*p = %d \n", ++*p);//先取值，后值++ ，A = (*p)+1；
    printf("(*p)++ = %d \n", (*p)++);//先取值，后值++ ，A = (*p)+1；
    return 0;
}