//操作文件 同名不同类型文件 克隆指定位置
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

// 检查文件是否存在
bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath.c_str());
    return file.good();
}

int main() {
    // 设置源文件夹路径和目标文件夹路径
    std::string sourceFolderPath = "E:\\music"; // 替换为源文件夹的实际路径
    std::string targetFolderPath = "E:\\mp3"; // 替换为目标文件夹的实际路径

    // 遍历源文件夹
    for (const auto& entry : fs::directory_iterator(sourceFolderPath)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string fileName = entry.path().filename().string();

            // 检查文件是否以".flac"结尾
            if (fs::path(fileName).extension() == ".flac") {
                // 构建相应的mp3文件名
                std::string mp3FileName = fs::path(fileName).stem().string() + ".mp3";
                std::string mp3FilePath = (fs::path(sourceFolderPath) / mp3FileName).string();

                // 如果mp3文件存在，将其移动到目标文件夹
                if (fileExists(mp3FilePath)) {
                    fs::copy_file(mp3FilePath, fs::path(targetFolderPath) / mp3FileName, fs::copy_options::overwrite_existing);
                    std::cout << "Moved: " << mp3FileName << " to " << targetFolderPath << std::endl;
                }
            }
        }
    }

    return 0;
}
