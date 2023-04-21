#include "Bezier.h"


int binomial(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

double bernstein(int m, int i, double u) { return binomial(m, i) * pow(u, i) * pow((1 - u), m - i); }

Curve changeOrigin(Curve curve , Coord p){
    
    for(Coord & point : curve.controlPoint ){
        point = point - p;
    }
    return curve;

}

Buffer createBuffer(size_t degree) {
    Buffer buffer(degree + 1);
    for (size_t i = 0; i <= degree; i++) {
        buffer[i].resize(degree + 1 - i);
    }
    return buffer;
}

Curve randomPoint(int n, int y, int x) {
    Curve random_points = Curve(n);
    for (int i = 0; i < n; i++) {

        random_points.controlPoint.push_back(Coord({static_cast<double>(rand() % x), static_cast<double>(rand() % y)}));
    }
    return random_points;
}
