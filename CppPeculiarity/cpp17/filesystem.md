```
#include <iostream>
#include <filesystem>
int main()
{
    std::filesystem::path sourcePath = "./filesystem.cpp";
    std::filesystem::path destinationPath = "./filesystem_copy_file.cpp";
    try
    {
        std::filesystem::copy_file(sourcePath, destinationPath);
        std::cout << "File copied successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    /*
    try {
        std::filesystem::remove(destinationPath); // 删除文件
        //std::filesystem::remove_all(directoryPath); // 删除目录及其内容
        std::cout << "File(s) or directory removed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    */
    
    /*
    std::filesystem::path newName = "filesystem_copy_file_new_name.cpp";
    try {
        std::filesystem::rename(destinationPath, newName);//重命名
        std::cout << "File or directory renamed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    */
    return 0;
}
```
std::filesystem 是 C++17 中引入的标准库，用于操作文件系统路径和文件操作。
示例有复制、删除、重命名文件

```
#include <iostream>
#include <filesystem>
int main()
{
    std::filesystem::path dirPath = "new_directory";
    try
    {
        std::filesystem::create_directory(dirPath); // 创建文件夹
        std::cout << "Directory created successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::filesystem::path filePath = "filesystem.cpp";

    if (std::filesystem::exists(filePath))
        std::cout << "File exists." << std::endl; // 文件是否存在
    else
        std::cout << "File does not exist." << std::endl;

    try
    {
        std::uintmax_t fileSize = std::filesystem::file_size(filePath); // 获取文件的大小
        std::cout << "File size: " << fileSize << " bytes" << std::endl;
        std::filesystem::file_time_type lastWriteTime = std::filesystem::last_write_time(filePath); // 获取文件的最后修改时间
        std::cout << "Last write time: " << lastWriteTime.time_since_epoch().count() << " nanoseconds" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```
另外,有创建文件夹、判断文件是否存在以及获取文件大小和最后修改时间等方法