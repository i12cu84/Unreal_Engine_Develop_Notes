#include <boost/any.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace boost;
int main()
{
    typedef vector<boost::any> many;
    many a;
    a.push_back(2);
    a.push_back(string("test"));
    for (unsigned int i = 0; i < a.size(); ++i)
    {
        cout << a[i].type().name() << endl;
        try
        {
            int result = any_cast<int>(a[i]);
            cout << result << endl;
        }
        catch (boost::bad_any_cast& ex)
        {
            cout << "cast error:" << ex.what() << endl;
        }
    }
}