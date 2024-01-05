#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// 定义一个3D向量类
class Vec3 {
public:
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

    Vec3 operator/(double scalar) const {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    double dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 cross(const Vec3& other) const {
        return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        double len = length();
        return Vec3(x / len, y / len, z / len);
    }
};

// 定义一个光线类
class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
};

// 定义一个球体类
class Sphere {
public:
    Vec3 center;
    double radius;

    Sphere(const Vec3& center, double radius) : center(center), radius(radius) {}

    // 判断光线和球体是否相交
    bool intersect(const Ray& ray, double& t) const {
        Vec3 oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            double sqrt_discriminant = std::sqrt(discriminant);
            double t1 = (-b - sqrt_discriminant) / (2.0 * a);
            double t2 = (-b + sqrt_discriminant) / (2.0 * a);
            t = (t1 < t2) ? t1 : t2;
            return true;
        }
    }
};

// 定义一个颜色类
class Color {
public:
    double r, g, b;

    Color() : r(0), g(0), b(0) {}
    Color(double r, double g, double b) : r(r), g(g), b(b) {}

    Color operator*(double scalar) const {
        return Color(r * scalar, g * scalar, b * scalar);
    }

    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b);
    }
};

// 定义场景
std::vector<Sphere> scene;

// 光线追踪函数
Color ray_trace(const Ray& ray, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0); // 递归深度达到上限时返回黑色
    }

    double closest_t = std::numeric_limits<double>::max();
    int closest_sphere = -1;

    // 寻找最近的交点
    for (int i = 0; i < scene.size(); i++) {
        double t;
        if (scene[i].intersect(ray, t) && t < closest_t) {
            closest_t = t;
            closest_sphere = i;
        }
    }

    if (closest_sphere != -1) {
        // 有交点，计算交点处的颜色
        Vec3 intersection_point = ray.origin + ray.direction * closest_t;
        Vec3 normal = (intersection_point - scene[closest_sphere].center).normalize();
        Vec3 light_direction = (Vec3(1, 2, 3)).normalize(); // 光源方向
        double diffuse_intensity = normal.dot(light_direction);

        if (diffuse_intensity < 0) {
            diffuse_intensity = 0;
        }

        Color sphere_color(1, 0, 0); // 球体颜色为红色
        Color light_color(1, 1, 1); // 光源颜色为白色
        Color diffuse_color = sphere_color * light_color * diffuse_intensity;

        // 计算反射光线
        Vec3 reflection_direction = ray.direction - normal * (2 * ray.direction.dot(normal));
        Ray reflection_ray(intersection_point, reflection_direction);

        // 递归追踪反射光线
        Color reflection_color = ray_trace(reflection_ray, depth - 1);

        // 最终颜色为漫反射颜色加上反射颜色
        Color final_color = diffuse_color + reflection_color;

        return final_color;
    } else {
        return Color(0, 0, 0); // 如果没有交点，返回黑色
    }
}

int main() {
    // 设置场景
    scene.push_back(Sphere(Vec3(0, 0, -5), 1.0));

    // 图像尺寸
    int image_width = 800;
    int image_height = 600;

    // 相机参数
    Vec3 camera_position(0, 0, 0);
    Vec3 camera_direction(0, 0, -1);
    double focal_length = 1.0;

    // 渲染图像
    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            double u = double(x) / double(image_width);
            double v = double(y) / double(image_height);
            Vec3 ray_direction = camera_direction + Vec3(u - 0.5, v - 0.5, 0) * focal_length;
            Ray ray(camera_position, ray_direction.normalize());
            Color pixel_color = ray_trace(ray, 5); // 递归深度为5
            std::cout << int(pixel_color.r * 255) << " " << int(pixel_color.g * 255) << " " << int(pixel_color.b * 255) << std::endl;
        }
    }

    return 0;
}
