#include <iostream>
#include <filesystem>
int main()
{
    // 指定要列出文件的目录路径
    std::filesystem::path directoryPath = "./";
    try
    {
        // 使用 std::filesystem::directory_iterator 遍历目录
        for (const auto &entry : std::filesystem::directory_iterator(directoryPath)) // 检查 entry 是否为文件
            if (entry.is_regular_file())
                std::cout << "File: " << entry.path() << std::endl;
            else if (entry.is_directory())
                std::cout << "Directory: " << entry.path() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
