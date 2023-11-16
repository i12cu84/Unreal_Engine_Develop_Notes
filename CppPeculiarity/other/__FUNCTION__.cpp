#include <iostream>
using namespace std; 
void print(void)
{
    printf("%s line: %d, function: %s \n", __FILE__,__LINE__, __FUNCTION__);
}
 
int main()
{
    print();
    return 0;
}