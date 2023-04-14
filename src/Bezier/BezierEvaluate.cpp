#include "BezierEvaluate.h"

Coord evalCasteljau(const Curve& curve, double t, Buffer& buffer) {
    //: SOURCE: https://fr.wikipedia.org/wiki/Algorithme_de_Casteljau
    const auto n = curve.degree;

    buffer[0] = curve.controlPoint;
    for (size_t j = 1; j <= n; ++j) {
        for (size_t i = 0; i <= n - j; ++i) {
            const auto& A = buffer[j - 1][i + 1];
            const auto& B = buffer[j - 1][i];
            auto&       C = buffer[j][i];

            C.x = t * (A.x - B.x) + B.x;
            C.y = t * (A.y - B.y) + B.y;
        }
    }

    return buffer[n][0];
}

std::vector<Coord> casteljau(const Curve& curve, size_t nb_points_on_curve) {
    Buffer bufferCurve = createBuffer(curve.degree);

    auto curvePoints = std::vector<Coord>();
    curvePoints.reserve(nb_points_on_curve);
    for (size_t i = 0; i <= nb_points_on_curve; i++) {
        curvePoints.push_back(
            evalCasteljau(curve, static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1., bufferCurve));
    }
    return curvePoints;
}
