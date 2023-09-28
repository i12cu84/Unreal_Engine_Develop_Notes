照例
```
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
```
在这个示例中，有一个包含一组数字的 std::vector，然后使用 std::async 在多个线程中并行计算每个数字的平方。每个计算任务都返回一个 std::future 对象，将这些对象存储在 futures 向量中。

然后，遍历 futures 向量，使用 future.get() 等待每个异步任务的完成，并获取其结果。最后，将所有平方值相加，得到这些数字的平方和，并将其打印到控制台上。

这个示例展示了如何使用 std::future 和 std::async 来执行多个并发任务，并在需要时获取它们的结果，以实现高效的并行计算。