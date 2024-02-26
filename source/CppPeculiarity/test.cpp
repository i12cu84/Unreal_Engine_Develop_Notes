#include <iostream>
#include <functional>
using namespace std;
#if 0

#elif 1

#define UFUNCTION(...)

class test{
public:
    UFUNCTION()
    void testprint()
    {
        cout<<"testprint"<<endl;
    }
};

int main()
{
    test t;
    t.testprint();
    cout<<1<<endl;
    return 0;
}

#endif
