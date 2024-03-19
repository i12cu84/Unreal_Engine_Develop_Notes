#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

// 定义一个2D点的数据结构
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 定义KD-Tree节点
struct KDNode {
    Point point;
    KDNode* left;
    KDNode* right;

    KDNode(const Point& p) : point(p), left(nullptr), right(nullptr) {}
};

// 用于比较两个点的函数，根据维度进行比较
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

// 构建KD-Tree
KDNode* buildKdTree(std::vector<Point>& points, int depth) {
    if (points.empty()) {
        return nullptr;
    }

    int k = points.size();
    int axis = depth % 2; // 交替选择x和y维度

    if (axis == 0) {
        std::sort(points.begin(), points.end(), compareX);
    } else {
        std::sort(points.begin(), points.end(), compareY);
    }

    int medianIndex = k / 2;
    KDNode* node = new KDNode(points[medianIndex]);
    
    std::vector<Point> leftPoints(points.begin(), points.begin() + medianIndex);
    std::vector<Point> rightPoints(points.begin() + medianIndex + 1, points.end());

    node->left = buildKdTree(leftPoints, depth + 1);
    node->right = buildKdTree(rightPoints, depth + 1);

    return node;
}

// KD-Tree中搜索最近邻点
KDNode* searchNearestNeighbor(KDNode* root, const Point& target, int depth, KDNode* best, double& bestDist) {
    if (root == nullptr) {
        return best;
    }

    int axis = depth % 2;
    KDNode* nextBranch = nullptr;
    KDNode* otherBranch = nullptr;

    if ((axis == 0 && target.x < root->point.x) || (axis == 1 && target.y < root->point.y)) {
        nextBranch = root->left;
        otherBranch = root->right;
    } else {
        nextBranch = root->right;
        otherBranch = root->left;
    }

    best = (searchNearestNeighbor(nextBranch, target, depth + 1, best, bestDist));

    double dist = std::sqrt((root->point.x - target.x) * (root->point.x - target.x) +
                            (root->point.y - target.y) * (root->point.y - target.y));

    if (dist < bestDist) {
        bestDist = dist;
        best = root;
    }

    if ((axis == 0 && target.x - bestDist <= root->point.x) ||
        (axis == 1 && target.y - bestDist <= root->point.y)) {
        best = searchNearestNeighbor(otherBranch, target, depth + 1, best, bestDist);
    }

    return best;
}

int main() {
    std::vector<Point> points = {{2, 3}, {5, 4}, {9, 6}, {4, 7}, {8, 1}, {7, 2}};
    KDNode* root = buildKdTree(points, 0);

    Point target(9, 2);
    double bestDist = std::numeric_limits<double>::max();
    KDNode* nearest = searchNearestNeighbor(root, target, 0, nullptr, bestDist);

    std::cout << "Nearest neighbor: (" << nearest->point.x << ", " << nearest->point.y << ")" << std::endl;

    return 0;
}
