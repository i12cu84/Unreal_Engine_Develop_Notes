#include <iostream>
#include <forward_list>
using namespace std;
int main()
{
    forward_list<int> myForwardList = {1, 2, 3, 4, 5}; // 创建一个 forward_list
    myForwardList.push_front(0);                       // 在前面插入元素
    cout << "Forward List: ";                          // 遍历并打印 forward_list 中的元素
    for (const int &num : myForwardList)
        cout << num << " ";
    cout << endl;
    myForwardList.pop_front(); // 删除第一个元素
    cout << "Modified List: "; // 遍历并打印修改后的 forward_list
    for (const int &num : myForwardList)
        cout << num << " ";
    cout << endl;
    return 0;
}
