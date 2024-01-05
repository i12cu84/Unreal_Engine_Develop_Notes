#include <iostream>
#include <vector>
#include <cmath>

// NURBS曲线的控制点结构体
struct ControlPoint {
    double x, y, weight;
};

// NURBS曲线类
class NurbsCurve {
public:
    NurbsCurve(const std::vector<ControlPoint>& controlPoints, const std::vector<double>& knots)
        : controlPoints_(controlPoints), knots_(knots) {}

    // 计算NURBS曲线上某个参数值t处的点
    ControlPoint Evaluate(double t) const {
        ControlPoint result = {0.0, 0.0, 0.0};
        int n = controlPoints_.size() - 1;
        int p = knots_.size() - n - 2;

        for (int i = 0; i <= n; ++i) {
            double basis = BasisFunction(i, p, t);
            result.x += controlPoints_[i].x * controlPoints_[i].weight * basis;
            result.y += controlPoints_[i].y * controlPoints_[i].weight * basis;
            result.weight += controlPoints_[i].weight * basis;
        }

        result.x /= result.weight;
        result.y /= result.weight;
        result.weight = 1.0;

        return result;
    }

private:
    // 计算基函数
    double BasisFunction(int i, int p, double t) const {
        // 此处省略了基函数的具体计算，通常使用递归的方式实现
        // 可以使用Cox-de Boor递推公式来计算基函数
        // 实际应用中，通常会使用高效的方式预计算和存储基函数
        // 这里只做示例用途
        // 基函数的计算可以参考相关文档和教材
        // 这里简化为线性基函数
        if (knots_[i] <= t && t < knots_[i + 1]) {
            return 1.0;
        } else {
            return 0.0;
        }
    }

private:
    std::vector<ControlPoint> controlPoints_;
    std::vector<double> knots_;
};

int main() {
    // 控制点
    std::vector<ControlPoint> controlPoints = {
        {0.0, 0.0, 1.0},
        {1.0, 2.0, 1.0},
        {2.0, 3.0, 1.0},
        {3.0, 1.0, 1.0}
    };

    // 节点矢量
    std::vector<double> knots = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0};

    // 创建NURBS曲线对象
    NurbsCurve nurbsCurve(controlPoints, knots);

    // 在参数t处求点
    double t = 0.5;
    ControlPoint result = nurbsCurve.Evaluate(t);

    std::cout << "NURBS Curve at t=" << t << ": (" << result.x << ", " << result.y << ")" << std::endl;

    return 0;
}
