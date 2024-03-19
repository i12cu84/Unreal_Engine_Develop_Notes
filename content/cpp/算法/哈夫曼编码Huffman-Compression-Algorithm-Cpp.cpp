#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

// 赫夫曼树节点
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char d, int freq) : data(d), frequency(freq), left(nullptr), right(nullptr) {}
};

// 用于优先队列的比较器，频率低的节点排在前面
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// 创建赫夫曼树
HuffmanNode* buildHuffmanTree(map<char, int>& frequencyMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    // 创建叶子节点，并将它们加入优先队列
    for (auto& entry : frequencyMap) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    // 构建赫夫曼树
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

// 生成赫夫曼编码表
void generateHuffmanCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (!root)
        return;

    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// 压缩文件
void compressFile(const string& inputFile, const string& outputFile, map<char, string>& huffmanCodes) {
    ifstream inFile(inputFile, ios::in | ios::binary);
    ofstream outFile(outputFile, ios::out | ios::binary);

    string buffer = "";
    char ch;

    // 读取输入文件并将字符替换为赫夫曼编码
    while (inFile.get(ch)) {
        buffer += huffmanCodes[ch];
    }

    // 将二进制字符串写入输出文件
    while (buffer.length() % 8 != 0) {
        buffer += '0'; // 填充到8的倍数
    }

    for (size_t i = 0; i < buffer.length(); i += 8) {
        string byte = buffer.substr(i, 8);
        char byteChar = static_cast<char>(stoi(byte, nullptr, 2));
        outFile.put(byteChar);
    }

    inFile.close();
    outFile.close();
}

int main() {
    // 读取输入文件并统计字符频率
    string inputFile = "input.txt";
    map<char, int> frequencyMap;
    ifstream inFile(inputFile);
    char ch;

    while (inFile.get(ch)) {
        frequencyMap[ch]++;
    }

    inFile.close();

    // 构建赫夫曼树
    HuffmanNode* root = buildHuffmanTree(frequencyMap);

    // 生成赫夫曼编码表
    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 压缩文件
    string outputFile = "compressed.bin";
    compressFile(inputFile, outputFile, huffmanCodes);

    cout << "File compressed successfully!" << endl;

    return 0;
}
