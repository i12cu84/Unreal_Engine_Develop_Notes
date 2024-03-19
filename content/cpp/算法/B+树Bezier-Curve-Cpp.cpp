#include <iostream>
#include <vector>

// 定义一个2D点的数据结构
struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

// 计算n次贝塞尔曲线上的点
Point bezier_curve(const std::vector<Point>& control_points, double t) {
    int n = control_points.size() - 1;
    std::vector<Point> temp_points = control_points;

    while (n > 0) {
        for (int i = 0; i < n; i++) {
            temp_points[i].x = (1 - t) * temp_points[i].x + t * temp_points[i + 1].x;
            temp_points[i].y = (1 - t) * temp_points[i].y + t * temp_points[i + 1].y;
        }
        n--;
    }

    return temp_points[0];
}

int main() {
    // 控制点定义
    std::vector<Point> control_points;
    control_points.push_back(Point(0, 0));
    control_points.push_back(Point(1, 2));
    control_points.push_back(Point(2, -1));
    control_points.push_back(Point(3, 1));
    control_points.push_back(Point(4, 0));

    // 计算并输出贝塞尔曲线上的点
    for (double t = 0; t <= 1.0; t += 0.1) {
        Point curve_point = bezier_curve(control_points, t);
        std::cout << "t=" << t << ": (" << curve_point.x << ", " << curve_point.y << ")" << std::endl;
    }

    return 0;
}
