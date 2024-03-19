#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// 定义一个矩形数据结构
struct Rectangle {
    int x, y, width, height;

    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
};

// 定义一个节点数据结构，包括矩形和子节点
struct BSPTreeNode {
    Rectangle rect;
    BSPTreeNode* left;
    BSPTreeNode* right;

    BSPTreeNode(const Rectangle& rect) : rect(rect), left(nullptr), right(nullptr) {}
};

// 生成随机矩形
Rectangle generateRandomRectangle(int maxWidth, int maxHeight) {
    int width = rand() % (maxWidth / 2) + 10;  // 随机宽度，最小宽度为10
    int height = rand() % (maxHeight / 2) + 10;  // 随机高度，最小高度为10
    int x = rand() % (maxWidth - width);  // 随机x坐标
    int y = rand() % (maxHeight - height);  // 随机y坐标
    return Rectangle(x, y, width, height);
}

// 递归构建BSP树
BSPTreeNode* buildBSPTree(std::vector<Rectangle>& rectangles) {
    if (rectangles.empty()) {
        return nullptr;
    }

    // 随机选择一个矩形作为分割平面
    int pivotIndex = rand() % rectangles.size();
    Rectangle pivotRect = rectangles[pivotIndex];

    // 分割矩形列表
    std::vector<Rectangle> leftRectangles;
    std::vector<Rectangle> rightRectangles;

    for (const auto& rect : rectangles) {
        if (rect.x + rect.width <= pivotRect.x || rect.x >= pivotRect.x + pivotRect.width) {
            // 矩形在分割平面左边或右边
            if (rect.x + rect.width <= pivotRect.x) {
                leftRectangles.push_back(rect);
            } else {
                rightRectangles.push_back(rect);
            }
        } else {
            // 矩形与分割平面有交叠部分
            int leftWidth = pivotRect.x - rect.x;
            int rightWidth = rect.x + rect.width - (pivotRect.x + pivotRect.width);

            if (leftWidth <= rightWidth) {
                leftRectangles.push_back(Rectangle(rect.x, rect.y, leftWidth, rect.height));
                rightRectangles.push_back(Rectangle(pivotRect.x + pivotRect.width, rect.y, rightWidth, rect.height));
            } else {
                rightRectangles.push_back(Rectangle(rect.x, rect.y, leftWidth, rect.height));
                leftRectangles.push_back(Rectangle(pivotRect.x + pivotRect.width, rect.y, rightWidth, rect.height));
            }
        }
    }

    // 递归构建左子树和右子树
    BSPTreeNode* leftNode = buildBSPTree(leftRectangles);
    BSPTreeNode* rightNode = buildBSPTree(rightRectangles);

    // 创建当前节点
    BSPTreeNode* currentNode = new BSPTreeNode(pivotRect);
    currentNode->left = leftNode;
    currentNode->right = rightNode;

    return currentNode;
}

// 递归打印BSP树
void printBSPTree(BSPTreeNode* root, int level) {
    if (root == nullptr) {
        return;
    }

    printBSPTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "   ";
    }
    std::cout << "[" << root->rect.x << "," << root->rect.y << "]-[" << root->rect.x + root->rect.width << ","
              << root->rect.y + root->rect.height << "]" << std::endl;

    printBSPTree(root->left, level + 1);
}

int main() {
    srand(time(nullptr));

    int maxWidth = 100;
    int maxHeight = 100;
    int numRectangles = 5;

    std::vector<Rectangle> rectangles;
    for (int i = 0; i < numRectangles; i++) {
        rectangles.push_back(generateRandomRectangle(maxWidth, maxHeight));
    }

    BSPTreeNode* root = buildBSPTree(rectangles);

    std::cout << "BSP Tree:" << std::endl;
    printBSPTree(root, 0);

    return 0;
}
