#include <iostream>
using namespace std;
#define HI_BOY "HiBoy"
#define COM(s) s
#define ADDWELL(s) #s

int main()
{
    cout<<HI_BOY<<endl;
    cout<<COM(HI_BOY)<<endl;
    cout<<ADDWELL(HI_BOY)<<endl;
    return 0;
}