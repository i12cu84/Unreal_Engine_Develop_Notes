#if 1
//filesystem_copy_file
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

#elif 1
//filesystem_copy
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

#elif 1
//filesystem_get_file_data
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

#endif