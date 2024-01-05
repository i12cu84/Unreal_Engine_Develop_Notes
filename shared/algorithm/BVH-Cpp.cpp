#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <random>

// 定义一个3D向量类
struct Vec3 {
    double x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
};

// 定义一个包围盒（Bounding Box）数据结构
struct BoundingBox {
    Vec3 min;
    Vec3 max;

    BoundingBox() : min(Vec3(std::numeric_limits<double>::max(), std::numeric_limits<double>::max(), std::numeric_limits<double>::max())),
                    max(Vec3(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest())) {}

    // 更新包围盒以包含另一个盒子
    void expand(const BoundingBox& box) {
        min.x = std::min(min.x, box.min.x);
        min.y = std::min(min.y, box.min.y);
        min.z = std::min(min.z, box.min.z);
        max.x = std::max(max.x, box.max.x);
        max.y = std::max(max.y, box.max.y);
        max.z = std::max(max.z, box.max.z);
    }

    // 更新包围盒以包含一个点
    void expand(const Vec3& point) {
        min.x = std::min(min.x, point.x);
        min.y = std::min(min.y, point.y);
        min.z = std::min(min.z, point.z);
        max.x = std::max(max.x, point.x);
        max.y = std::max(max.y, point.y);
        max.z = std::max(max.z, point.z);
    }

    // 计算包围盒的表面积
    double surfaceArea() const {
        Vec3 extent = max - min;
        return 2.0 * (extent.x * extent.y + extent.x * extent.z + extent.y * extent.z);
    }
};

// 定义一个三角形类
struct Triangle {
    Vec3 vertices[3];
    BoundingBox bbox;

    Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2) {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
        bbox.expand(v0);
        bbox.expand(v1);
        bbox.expand(v2);
    }
};

// BVH节点数据结构
struct BVHNode {
    BoundingBox bbox;
    BVHNode* left;
    BVHNode* right;
    int start;
    int end;

    BVHNode(const std::vector<Triangle>& triangles, int start, int end) : start(start), end(end), left(nullptr), right(nullptr) {
        // 计算该节点包围盒
        bbox = BoundingBox();
        for (int i = start; i < end; ++i) {
            bbox.expand(triangles[i].bbox);
        }
    }
};

// 用于比较三角形在某一维度上的坐标
bool compareTriangles(const Triangle& a, const Triangle& b, int axis) {
    return a.vertices[0].x < b.vertices[0].x;
}

// 构建BVH树
BVHNode* buildBVHTree(std::vector<Triangle>& triangles, int start, int end, int axis) {
    if (start == end) {
        return nullptr;
    }

    if (end - start == 1) {
        return new BVHNode(triangles, start, end);
    }

    // 按照中间点将三角形划分成两组
    std::sort(triangles.begin() + start, triangles.begin() + end, [&axis](const Triangle& a, const Triangle& b) {
        return a.vertices[0].x < b.vertices[0].x;
    });

    int mid = start + (end - start) / 2;
    BVHNode* node = new BVHNode(triangles, start, end);

    // 递归构建左子树和右子树
    node->left = buildBVHTree(triangles, start, mid, (axis + 1) % 3);
    node->right = buildBVHTree(triangles, mid, end, (axis + 1) % 3);

    return node;
}

int main() {
    // 随机生成一些三角形
    std::vector<Triangle> triangles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.0, 10.0);

    for (int i = 0; i < 10; ++i) {
        Vec3 v0(dis(gen), dis(gen), dis(gen));
        Vec3 v1(dis(gen), dis(gen), dis(gen));
        Vec3 v2(dis(gen), dis(gen), dis(gen));
        triangles.emplace_back(v0, v1, v2);
    }

    // 构建BVH树
    BVHNode* root = buildBVHTree(triangles, 0, triangles.size(), 0);

    // 打印BVH树节点信息
    std::cout << "BVH Tree Nodes:" << std::endl;
    // 打印函数需要根据实际情况自行实现

    return 0;
}
