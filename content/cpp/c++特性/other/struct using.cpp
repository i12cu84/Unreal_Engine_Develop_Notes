#include <iostream>
using namespace std;

struct {
    using Age=int;
    Age age;
}person{20};

int main()
{
    cout<<person.age<<endl;    
}