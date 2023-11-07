#include <iostream>
#include <string>
#include <regex>
using namespace std;
#if 1
struct Test{
    int n;
    Test()
    {
        this->n=1;
    }
    
    void print()
    {
        cout<<n<<endl;
    }
}test;
int main()
{
    test.print();
}

#elif 1
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
    int n=NULL;
    int* p_null=&n;
    int* p_nullptr=nullptr;

    print_null(p_null);
    print_null(p_nullptr);
}
#elif 1
bool validateIdCard(const std::string &idNumber)
{
    std::regex pattern("^[1-9]\\d{5}(19|20)\\d{2}(0[1-9]|1[0-2])(0[1-9]|[1-2]\\d|3[01])\\d{3}([0-9Xx])$");
    if (std::regex_match(idNumber, pattern))
    {
        int factors[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        int checkSum = 0;
        for (int i = 0; i < 17; ++i)
        {
            checkSum += (idNumber[i] - '0') * factors[i];
        }
        int modResult = checkSum % 11;
        char checkDigit = (modResult == 2) ? 'X' : ('0' + (12 - modResult) % 11);
        if (idNumber.back() == checkDigit)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main()
{
}
#elif 1

#include <iostream>
#include <functional>

template<typename T>
T subtracts(T a)
{
    return a;
}

template<typename T,typename ... arg>
T subtracts(T a, arg ... args)
{
    return a-subtracts(args ...);
}

int main()
{
    
}

#elif 0

#include <boost/fiber/all.hpp>
#include <iostream>

int main() {
    boost::fibers::fiber fib([]() {
        std::cout << "Fiber started." << std::endl;
    });

    fib.join();
    std::cout << "Fiber finished." << std::endl;
}
#elif 1
#include <iostream>
#include <functional>

template<typename T>
T adds(T a)
{
    return a;
}

template<typename T,typename ... arg>
T adds(T a,arg... args)
{
    return a+adds(args...);
}

int main()
{
    std::cout << "num: " << adds(3) << std::endl;
    std::cout << "num: " << adds(3, 4) << std::endl;
    std::cout << "num: " << adds(3, 4,8) << std::endl;
    return 0;
}


#endif