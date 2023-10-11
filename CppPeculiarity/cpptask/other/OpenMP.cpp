//OpenMP 测试
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <omp.h>
struct P {
    double x;
    double y;
    double z;
};
int main() {
    int N = 10000;
    std::vector<P> points(N);
    std::map<std::pair<P*, P*>, double> distanceMap;
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            double dx = points[i].x - points[j].x;
            double dy = points[i].y - points[j].y;
            double dz = points[i].z - points[j].z;
            double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            #pragma omp critical
            distanceMap[{&points[i], &points[j]}] = distance;
        }
    }
    return 0;
}
