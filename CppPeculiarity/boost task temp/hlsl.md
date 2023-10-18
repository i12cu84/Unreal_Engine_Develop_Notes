Boost.HLSL：用于编写高级着色器语言（HLSL）的库，支持GPU编程。
示例：使用boost::hls编写简单的HLSL着色器。

```cpp
#include <boost/hlsl.hpp>

// HLSL shader code
boost::hlsl::float4 main(boost::hlsl::float4 color) {
    return color;
}
```