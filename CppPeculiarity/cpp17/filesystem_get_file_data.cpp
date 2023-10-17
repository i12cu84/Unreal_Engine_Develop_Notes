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
