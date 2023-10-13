#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> topK(vector<int> &nums, int k)
{
    priority_queue<pair<int, int>> pq;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++)
    {
        if (pq.size() < k)
        {
            pq.push({nums[i], i});
        }
        else if (nums[i] < pq.top().first)
        {
            pq.pop();
            pq.push({nums[i], i});
        }
    }
    while (!pq.empty())
    {
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}
int main()
{
    vector<int> nums;
    for (int i = 6; i > 0; --i)
    {
        nums.push_back(i);
    }
    int k = 6;
    vector<int> res = topK(nums, k);
    for (int i : res)
    {
        cout << "Index: " << i << ", Value: " << nums[i] << endl;
    }

    return 0;
}
