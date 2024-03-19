#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// 定义一个3D向量类
struct Vec3 {
    double x, y, z;
    Vec3() : x(0), y(0), z(0) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }
    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }
    Vec3 operator*(double scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }
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

// 定义一个射线类
struct Ray {
    Vec3 origin;
    Vec3 direction;
    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
    Vec3 pointAt(double t) const {
        return origin + direction * t;
    }
};

// 定义一个球体类
struct Sphere {
    Vec3 center;
    double radius;
    Sphere(const Vec3& center, double radius) : center(center), radius(radius) {}

    // 判断光线是否与球体相交
    bool intersect(const Ray& ray, double& t) const {
        Vec3 oc = ray.origin - center;
        double a = dot(ray.direction, ray.direction);
        double b = 2.0 * dot(oc, ray.direction);
        double c = dot(oc, oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
            double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
            if (t1 > 0.001) {
                t = t1;
                return true;
            } else if (t2 > 0.001) {
                t = t2;
                return true;
            }
        }
        return false;
    }
};

// 随机数生成器
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);

// 蒙特卡洛路径追踪
Vec3 trace(const Ray& ray, const std::vector<Sphere>& spheres, int depth) {
    if (depth == 0) {
        return Vec3(0, 0, 0);  // 递归深度达到限制时返回黑色
    }

    double t;
    int hitSphere = -1;
    for (int i = 0; i < spheres.size(); ++i) {
        if (spheres[i].intersect(ray, t) && (hitSphere == -1 || t < t)) {
            hitSphere = i;
        }
    }

    if (hitSphere == -1) {
        // 如果没有相交的球体，返回背景颜色
        return Vec3(0.2, 0.7, 0.8);
    }

    Vec3 hitPoint = ray.pointAt(t);
    Vec3 normal = normalize(hitPoint - spheres[hitSphere].center);
    Vec3 target = hitPoint + normal + randomInUnitSphere();

    // 递归追踪反射光线
    return 0.5 * trace(Ray(hitPoint, target - hitPoint), spheres, depth - 1);
}

// 在单位球体内生成随机点
Vec3 randomInUnitSphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(distribution(generator), distribution(generator), distribution(generator)) - Vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return p;
}

int main() {
    const int width = 800;
    const int height = 400;
    const int numSamples = 100;
    const int maxDepth = 50;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    Vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    Vec3 horizontal(4.0, 0.0, 0.0);
    Vec3 vertical(0.0, 2.0, 0.0);
    Vec3 origin(0.0, 0.0, 0.0);

    std::vector<Sphere> spheres = {Sphere(Vec3(0, 0, -1), 0.5), Sphere(Vec3(0, -100.5, -1), 100)};

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            Vec3 color(0, 0, 0);
            for (int s = 0; s < numSamples; ++s) {
                double u = double(i + distribution(generator)) / double(width);
                double v = double(j + distribution(generator)) / double(height);
                Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
                color = color + trace(ray, spheres, maxDepth);
            }
            color = color / double(numSamples);
            color = Vec3(sqrt(color.x), sqrt(color.y), sqrt(color.z)); // Gamma校正
            int ir = int(255.99 * color.x);
            int ig = int(255.99 * color.y);
            int ib = int(255.99 * color.z);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
