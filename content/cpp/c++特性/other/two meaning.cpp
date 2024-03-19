#include <iostream>
using namespace std;
void print_null(int * p_null)
{
    if (p_null)
    {
        cout << "p_null is not null" << endl;
    }
    else
    {
        cout << "p_null is null" << endl;
    }
}

int main ()
{
    int n;//=NULL;
    int* p_null=&n;
    int* p_nullptr=nullptr;

    print_null(p_null);
    print_null(p_nullptr);
}