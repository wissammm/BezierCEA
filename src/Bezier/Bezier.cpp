#include "Bezier.h"
#include "Geometry/Segment.h"
#include <iostream>
#include <cmath>

int binomial(int n, int k) {
    if (k == 0 || k == n)
        return 1;
    return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

double bernstein(int m, int i, double u) { return binomial(m, i) * pow(u, i) * pow((1 - u), m - i); }

Bezier changeOrigin(Bezier curve, Coord p) {

    for (Coord& point : curve.controlPoint) {
        point = point - p;
    }
    return curve;
}

Bezier changeOriginTo0(Bezier curve) {

    for (Coord& point : curve.controlPoint) {
        point = point - curve.controlPoint[0];
    }
    return curve;
}

Bezier rotatePoints(Bezier curve) {

    double             dx           = curve.controlPoint[curve.degree].x;
    double             dy           = curve.controlPoint[curve.degree].x;
    double             a            = atan2(dy, dx);
    std::vector<Coord> controlPoint = std::vector<Coord>(curve.controlPoint.size());
    for (int i = 0; i < curve.controlPoint.size(); ++i){
        controlPoint[i]= Coord({
             curve.controlPoint[i].x * cos(-a) - curve.controlPoint[i].y * sin(-a), //
             curve.controlPoint[i].x * sin(-a) + curve.controlPoint[i].y * cos(-a)
        });
    }
    return Bezier (controlPoint);

}

Buffer createBuffer(size_t degree) {
    Buffer buffer(degree + 1);
    for (size_t i = 0; i <= degree; i++) {
        buffer[i].resize(degree + 1 - i);
    }
    return buffer;
}

Coord randomPoint(int x, int y) { return Coord({static_cast<double>(rand() % x), static_cast<double>(rand() % y)}); }

std::vector<Coord> randomPoints(int n, int x, int y) {
    std::vector<Coord> random_points;

    for (int i = 0; i < n; i++) {

        random_points.push_back(randomPoint(x, y));
    }
    return random_points;
}
