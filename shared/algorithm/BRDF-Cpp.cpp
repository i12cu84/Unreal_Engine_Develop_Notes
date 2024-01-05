#include <iostream>
#include <random>
#include <cmath>

// 定义一个3D向量类
struct Vec3 {
    double x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
};

// 计算两个向量的点积
double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 归一化一个向量
Vec3 normalize(const Vec3& v) {
    double length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vec3(v.x / length, v.y / length, v.z / length);
}

// Lambertian BRDF函数
double lambertianBRDF(const Vec3& normal, const Vec3& lightDir) {
    double cosTheta = dot(normal, lightDir);
    if (cosTheta < 0) {
        return 0.0;  // 光线与法线方向背离，返回0
    }
    return cosTheta / M_PI;  // Lambertian BRDF公式
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // 定义表面法线和入射光线方向
    Vec3 normal(0, 0, 1);  // 表面法线，通常是归一化的
    Vec3 lightDir(dis(gen), dis(gen), dis(gen));  // 入射光线方向，随机生成

    // 归一化光线方向
    lightDir = normalize(lightDir);

    // 计算Lambertian BRDF
    double brdf = lambertianBRDF(normal, lightDir);

    std::cout << "Lambertian BRDF: " << brdf << std::endl;

    return 0;
}
