#include <iostream>
#include <thread>
using namespace std;
int main()
{
	auto func = []()
	{
		for (int i = 0; i < 10; ++i)
		{
			cout << i << " ";
		}
		cout << endl;
	};
	std::thread t(func);
	if (t.joinable())
	{
		t.detach();
	}
	auto func1 = [](int k)
	{
		for (int i = 0; i < k; ++i)
		{
			cout << i << " ";
		}
		cout << endl;
	};
	std::thread tt(func1, 20);
	if (tt.joinable())
	{
		tt.join();
	}
	return 0;
}