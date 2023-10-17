vs code to cpp20

cmd -> gcc -v => gcc version 13.2.0 (x86_64-win32-seh-rev0, Built by MinGW-Builds project)

vs code -> plugins setting (Competitive Programming Helper (cph))
-> Cph > Language > Cpp:Args -> -std=c++20
-> Cph > Language > Cpp:Submission Compiler -> GNU G++20 11.2.0

.vscode -> 
c_cpp_properties.json
在其中加入:
"configurations": [
    {
        "cppStandard": "c++20"
    }
]
tasks.json
在其中加入:
"args": [
    //"-fdiagnostics-color=always",
    //"-g",
    "-std=c++20",
    "${file}",
    "-o",
    "${fileDirname}\\${fileBasenameNoExtension}.exe"
],

测试代码:
```
#include <iostream>
#include <span>
void print_elements(std::span<int> arr)
{
    for (const auto &elem : arr)
        std::cout << elem << ' ';
    std::cout << '\n';
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    print_elements(arr);
    return 0;
}
```