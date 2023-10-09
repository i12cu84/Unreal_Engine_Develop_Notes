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
