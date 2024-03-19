当然，`typedef`是C++98中的一个关键字，它用于为现有的类型创建一个新的名称。以下是一个使用`typedef`的例子：

```cpp
#include <iostream>
#include <vector>

// 使用typedef为std::vector<int>创建一个新的名称IntVector
typedef std::vector<int> IntVector;

int main() {
    // 现在可以使用IntVector来代替std::vector<int>
    IntVector v = {1, 2, 3, 4, 5};

    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

在这个例子中，我们使用`typedef`关键字为`std::vector<int>`类型创建了一个新的名称`IntVector`。然后我们就可以使用`IntVector`来代替`std::vector<int>`，这使得代码更加简洁和易读。这是C++98中引入的一种非常有用的特性。