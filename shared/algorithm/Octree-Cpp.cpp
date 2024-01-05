#include <iostream>
#include <vector>

// 定义八叉树节点
struct OctreeNode {
    double x, y, z; // 节点的坐标
    int data;      // 节点存储的数据，这里假设是整数

    OctreeNode* children[8]; // 8个子节点

    OctreeNode(double x, double y, double z, int data) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->data = data;
        for (int i = 0; i < 8; i++) {
            children[i] = nullptr;
        }
    }
};

// 定义八叉树类
class Octree {
public:
    Octree(double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        root = new OctreeNode((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2, -1);
        this->minX = minX;
        this->minY = minY;
        this->minZ = minZ;
        this->maxX = maxX;
        this->maxY = maxY;
        this->maxZ = maxZ;
    }

    // 插入数据
    void insert(double x, double y, double z, int data) {
        insertRecursive(root, x, y, z, data, minX, minY, minZ, maxX, maxY, maxZ);
    }

    // 查询数据
    int query(double x, double y, double z) {
        return queryRecursive(root, x, y, z, minX, minY, minZ, maxX, maxY, maxZ);
    }

private:
    OctreeNode* root;
    double minX, minY, minZ, maxX, maxY, maxZ;

    // 递归插入
    void insertRecursive(OctreeNode* node, double x, double y, double z, int data,
                         double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        // 如果节点没有子节点，创建子节点
        if (node->children[0] == nullptr) {
            splitNode(node, minX, minY, minZ, maxX, maxY, maxZ);
        }

        // 确定数据应该插入哪个子节点
        int index = calculateChildIndex(node, x, y, z);

        // 递归插入子节点
        insertRecursive(node->children[index], x, y, z, data,
                        minX, minY, minZ, maxX, maxY, maxZ);
    }

    // 递归查询
    int queryRecursive(OctreeNode* node, double x, double y, double z,
                       double minX, double minY, double minZ, double maxX, double maxY, double maxZ) {
        // 如果节点没有子节点，返回该节点的数据
        if (node->children[0] == nullptr) {
            return node->data;
        }

        // 确定查询应该在哪个子节点中进行
        int index = calculateChildIndex(node, x, y, z);

        // 递归查询子节点
        return queryRecursive(node->children[index], x, y, z,
                              minX, minY, minZ, maxX, maxY, maxZ);
    }

    // 分割节点成8个子节点
    void splitNode(OctreeNode* node, double minX, double minY, double minZ,
                   double maxX, double maxY, double maxZ) {
        double midX = (minX + maxX) / 2;
        double midY = (minY + maxY) / 2;
        double midZ = (minZ + maxZ) / 2;

        node->children[0] = new OctreeNode(midX, midY, midZ, -1);
        node->children[1] = new OctreeNode(midX, midY, maxZ, -1);
        node->children[2] = new OctreeNode(midX, minY, midZ, -1);
        node->children[3] = new OctreeNode(midX, minY, maxZ, -1);
        node->children[4] = new OctreeNode(minX, midY, midZ, -1);
        node->children[5] = new OctreeNode(minX, midY, maxZ, -1);
        node->children[6] = new OctreeNode(minX, minY, midZ, -1);
        node->children[7] = new OctreeNode(minX, minY, maxZ, -1);
    }

    // 计算数据应该插入哪个子节点
    int calculateChildIndex(OctreeNode* node, double x, double y, double z) {
        int index = 0;
        if (x > node->x) index += 1;
        if (y > node->y) index += 2;
        if (z > node->z) index += 4;
        return index;
    }
};

int main() {
    Octree octree(-10.0, -10.0, -10.0, 10.0, 10.0, 10.0);

    // 插入测试数据
    octree.insert(1.0, 2.0, 3.0, 42);
    octree.insert(-5.0, -6.0, 7.0, 99);

    // 查询测试数据
    int result1 = octree.query(1.0, 2.0, 3.0);
    int result2 = octree.query(-5.0, -6.0, 7.0);

    std::cout << "Query Result 1: " << result1 << std::endl; // 应该输出42
    std::cout << "Query Result 2: " << result2 << std::endl; // 应该输出99

    return 0;
}