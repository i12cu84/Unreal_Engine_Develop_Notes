#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> v{1, 2, 3};
    for (auto [i, j] = pair{v.begin(), v.end()}; i != j; ++i)
        cout << *i << " ";
    cout << endl;
}