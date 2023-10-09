#include <iostream>
#include <vector>
#include <future>
int calculateSquare(int x)
{
    return x * x;
}
int main()
{
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<std::future<int>> futures;
    // 启动多个异步任务来计算每个数字的平方
    for (int num : numbers)
    {
        futures.push_back(std::async(std::launch::async, calculateSquare, num));
    }
    // 等待每个异步任务完成并获取结果
    int sumOfSquares = 0;
    for (std::future<int> &future : futures)
    {
        sumOfSquares += future.get();
    }
    std::cout << "Sum of squares: " << sumOfSquares << std::endl;
    return 0;
}
