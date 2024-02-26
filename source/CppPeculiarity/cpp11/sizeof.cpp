#include <iostream>
using namespace std;
struct A 
{
    int data[10];
    int a;
};
int main() 
{
    cout << "size " << sizeof(A::data) << endl;
    return 0;
}