//合并文件
#include <iostream>
#include <fstream>
#include <vector>
int main() {
    // 定义要合并的文件名列表
    std::vector<std::string> inputFiles = {"E:\\file1.bin", "E:\\file2.bin"};
    std::string outputFile = "E:\\merged_file.bin"; // 合并后的文件名
    // 打开输出文件流
    std::ofstream outFile(outputFile, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "无法打开输出文件" << std::endl;
        return 1;
    }
    for (const std::string& inputFileName : inputFiles) {
        // 打开输入文件流
        std::ifstream inFile(inputFileName, std::ios::binary);
        if (!inFile.is_open()) {
            std::cerr << "无法打开输入文件" << inputFileName << std::endl;
            return 1;
        }
        // 从输入文件复制数据到输出文件
        outFile << inFile.rdbuf();
        // 关闭当前输入文件
        inFile.close();
    }
    // 关闭输出文件
    outFile.close();
    std::cout << "文件合并完成，已保存为 " << outputFile << std::endl;
    return 0;
}