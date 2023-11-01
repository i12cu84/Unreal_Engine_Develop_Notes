#include <iostream>  
#include <boost/compute.hpp>

using boost::compute::buffer;  
using boost::compute::context;  
using boost::compute::device;  
using boost::compute::program;  
using boost::compute::kernel;

int main() {  
    // 创建一个设备对象  
    device dev = device::find_first();  
      
    // 创建一个上下文对象  
    context ctx(dev);

    // 编写一个计算斐波那契数列的 GPU 内核  
    std::string source =  
        "__global__ void fibonacci(int* a, int n) {  "  
        "    if (n == 1 || n == 2) {  "  
        "        a[n] = 1;  "  
        "    } else {  "  
        "        a[n] = a[n - 1] + a[n - 2];  "  
        "    }  "  
        "}"  
        "void fibonacci_host(int* a, int n) {  "  
        "    for (int i = 2; i < n; ++i) {  "  
        "        a[i] = a[i - 1] + a[i - 2];  "  
        "    }  "  
        "}";

    // 将源代码编译为 GPU 程序  
    program::buffer binary(ctx, source.c_str(), source.length());  
    program prog(ctx, binary);

    // 分配 GPU 内存  
    buffer<int> a(ctx, 10);

    // 初始化输入数据  
    for (int i = 0; i < 10; ++i) {  
        a[i] = i;  
    }

    // 在 GPU 上运行内核  
    prog.run_gpu(kernel::name_of("fibonacci"), a.get_handle(), 10);

    // 将 GPU 结果复制回主机内存  
    std::vector<int> h_a(10);  
    a.read(h_a.data(), 10);

    // 输出结果  
    for (int i = 0; i < 10; ++i) {  
        std::cout << "Fibonacci(" << i << ") = " << h_a[i] << std::endl;  
    }

    return 0;  
}
