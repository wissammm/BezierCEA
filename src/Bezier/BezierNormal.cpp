#include "BezierNormal.h"
#include "BezierEvaluate.h"
#include "Geometry/Coord.h"
#include "Geometry/Segment.h"

Coord computeTangent(Coord deriv_time_t) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(deriv_time_t.x * deriv_time_t.x + deriv_time_t.y * deriv_time_t.y);
    return Coord({deriv_time_t.x / m, deriv_time_t.y / m});
}

Coord computeNormal(Coord tengent) {
    //: SOURCE: https://pomax.github.io/bezierinfo/#derivatives
    double m = sqrt(tengent.x * tengent.x + tengent.y * tengent.y);

    return Coord({-tengent.y / m, tengent.x / m});
}



Coord tangente(Curve curve, size_t time) {
    Buffer      buffer      = createBuffer(curve.degree);
    Curve       deriv       = derivate(curve);
    const Coord deriv_point = evalCasteljau(deriv, time, buffer);
    return computeTangent(deriv_point);
}

Coord normal(Curve curve, size_t time) {
    Buffer      buffer      = createBuffer(curve.degree);
    Curve       deriv       = derivate(curve);
    const Coord deriv_point = evalCasteljau(deriv, time, buffer);
    auto        t           = computeTangent(deriv_point);
    return computeNormal(t);
}

CurveNormalsAndTangents normalsAndTangents(const Curve& bezier, size_t nb_points_on_curve, double factor) {

    Buffer buffer = createBuffer(bezier.degree);
    Curve  deriv  = derivate(bezier);

    auto result = CurveNormalsAndTangents{};
    for (int i = 0; i <= nb_points_on_curve; i++) {
        const double time = static_cast<double>(i) / static_cast<double>(nb_points_on_curve) * 1.;

        const Coord curvePoint = evalCasteljau(bezier, time, buffer);
        result.curve.push_back(curvePoint);

        const Coord deriv_point = evalCasteljau(deriv, time, buffer);
        const Coord tangent     = computeTangent(deriv_point);
        const Coord normal      = computeNormal(tangent);

        result.tangents.push_back(Segment({curvePoint, curvePoint + tangent * factor}));
        result.normals.push_back(Segment({curvePoint, curvePoint + normal * factor}));
    }
    return result;
}
