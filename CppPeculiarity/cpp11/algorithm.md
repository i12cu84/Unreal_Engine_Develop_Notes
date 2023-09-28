C++11 引入了许多新的标准库算法函数，以扩展 STL（标准模板库）的功能。以下是 C++11 中新增的一些重要算法函数：
std::for_each：对容器中的元素执行指定的操作。
std::copy_if：从一个容器复制满足特定条件的元素到另一个容器。
std::move：将指定范围的元素从一个容器移动到另一个容器。
std::all_of：检查容器中的所有元素是否都满足特定条件。
std::any_of：检查容器中是否有任何一个元素满足特定条件。
std::none_of：检查容器中是否没有任何一个元素满足特定条件。
std::count_if：计算容器中满足特定条件的元素的数量。
std::remove_if：从容器中删除满足特定条件的元素。
std::remove_copy_if：从一个容器复制不满足特定条件的元素到另一个容器，并从原容器中删除它们。
std::transform：对容器中的元素应用指定的操作，并将结果存储在另一个容器中。
std::generate：使用生成器函数填充容器的元素。
std::generate_n：使用生成器函数填充指定数量的容器元素。
std::iota：将一系列连续的值填充到容器中。
std::minmax_element：查找容器中的最小和最大元素。
std::is_sorted：检查容器是否已按升序排序。
std::is_sorted_until：查找容器中排序的截止位置。
std::next_permutation 和 std::prev_permutation：生成容器中元素的下一个或前一个排列。
这些新的算法函数增加了 C++ 标准库的功能，使其更加强大和灵活。它们可以用于各种情况，从元素的搜索和排序到元素的转换和操作。这些函数的引入使得在编写 C++ 代码时更容易表达各种算法操作。

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
int main()
{
    std::vector<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    // 1. 使用 std::for_each 对容器中的元素执行操作
    std::cout << "Squared values: ";
    std::for_each(numbers.begin(), numbers.end(), [](int x)
                  { std::cout << x * x << " "; });
    std::cout << std::endl;
    // 2. 使用 std::copy_if 复制满足条件的元素到另一个容器
    std::vector<int> evenNumbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evenNumbers), [](int x)
                 { return x % 2 == 0; });
    std::cout << "Even numbers: ";
    for (int num : evenNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 3. 使用 std::move 将元素从一个容器移动到另一个容器
    std::vector<int> source = {10, 20, 30};
    std::vector<int> destination;
    std::move(source.begin(), source.end(), std::back_inserter(destination));
    std::cout << "Moved elements: ";
    for (int num : destination)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 4. 使用 std::all_of 检查容器中的所有元素是否都满足特定条件
    bool allEven = std::all_of(numbers.begin(), numbers.end(), [](int x)
                               { return x % 2 == 0; });

    std::cout << "All even? " << (allEven ? "Yes" : "No") << std::endl;
    // 5. 使用 std::any_of 检查容器中是否有任何一个元素满足特定条件
    bool anyGreaterThan5 = std::any_of(numbers.begin(), numbers.end(), [](int x)
                                       { return x > 5; });
    std::cout << "Any greater than 5? " << (anyGreaterThan5 ? "Yes" : "No") << std::endl;
    // 6. 使用 std::none_of 检查容器中是否没有任何一个元素满足特定条件
    bool noneLessThan0 = std::none_of(numbers.begin(), numbers.end(), [](int x)
                                      { return x < 0; });

    std::cout << "None less than 0? " << (noneLessThan0 ? "Yes" : "No") << std::endl;
    // 7. 使用 std::count_if 计算容器中满足特定条件的元素的数量
    int countGreaterThan3 = std::count_if(numbers.begin(), numbers.end(), [](int x)
                                          { return x > 3; });
    std::cout << "Count greater than 3: " << countGreaterThan3 << std::endl;
    // 8. 使用 std::remove_if 从容器中删除满足特定条件的元素
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [](int x)
                                 { return x == 5; }),
                  numbers.end());
    std::cout << "After removing 5s: ";
    for (int num : numbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 9. 使用 std::remove_copy_if 从一个容器复制不满足特定条件的元素到另一个容器
    std::vector<int> notEqual5;
    std::remove_copy_if(numbers.begin(), numbers.end(), std::back_inserter(notEqual5), [](int x)
                        { return x == 5; });
    std::cout << "Not equal to 5: ";
    for (int num : notEqual5)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 10. 使用 std::transform 对容器中的元素应用指定的操作
    std::vector<int> squaredNumbers;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(squaredNumbers), [](int x)
                   { return x * x; });
    std::cout << "Squared numbers: ";
    for (int num : squaredNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 11. 使用 std::generate 使用生成器函数填充容器的元素
    std::vector<int> generatedNumbers(5);
    int counter = 1;
    std::generate(generatedNumbers.begin(), generatedNumbers.end(), [&counter]()
                  { return counter++; });
    std::cout << "Generated numbers: ";
    for (int num : generatedNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 12. 使用 std::generate_n 使用生成器函数填充指定数量的容器元素
    std::vector<int> generatedNNumbers;
    std::generate_n(std::back_inserter(generatedNNumbers), 5, [&counter]()
                    { return counter++; });
    std::cout << "Generated N numbers: ";
    for (int num : generatedNNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 13. 使用 std::iota 将一系列连续的值填充到容器中
    std::vector<int> iotaNumbers(5);
    std::iota(iotaNumbers.begin(), iotaNumbers.end(), 10);
    std::cout << "Iota numbers: ";
    for (int num : iotaNumbers)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 14. 使用 std::minmax_element 查找容器中的最小和最大元素
    auto minMax = std::minmax_element(numbers.begin(), numbers.end());
    std::cout << "Min element: " << *minMax.first << std::endl;
    std::cout << "Max element: " << *minMax.second << std::endl;
    // 15. 使用 std::is_sorted 检查容器是否已按升序排序
    bool sorted = std::is_sorted(numbers.begin(), numbers.end());
    std::cout << "Is sorted? " << (sorted ? "Yes" : "No") << std::endl;
    // 16. 使用 std::is_sorted_until 查找容器中排序的截止位置
    auto sortedUntil = std::is_sorted_until(numbers.begin(), numbers.end());
    std::cout << "Sorted until element: " << *sortedUntil << std::endl;
    // 17. 使用 std::next_permutation 生成容器中元素的下一个排列
    std::vector<int> permutationNumbers = {1, 2, 3};
    do
    {
        for (int num : permutationNumbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(permutationNumbers.begin(), permutationNumbers.end()));
    return 0;
}
```

这个示例程序演示了如何使用 C++11 新增的 17 个算法函数来执行各种不同的操作，包括遍历、复制、移动、检查条件、删除、变换、生成、排序和排列等。这些函数大大提高了代码的灵活性和可读性。