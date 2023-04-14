#include "BezierDecompose.h"


std::array<Curve, 2> decompose(const Curve& curve, double t) {

    auto buffer = createBuffer(curve.degree);

    evalCasteljau(curve, t, buffer);

    //: SOURCE: https://www.youtube.com/watch?v=lPJo1jayLdc
    Curve part1, part2(curve.nbControlPoint);

    for (size_t i = 0; i < curve.nbControlPoint; ++i) {
        part1.controlPoint.push_back(buffer[i][0]);
        part2.controlPoint[curve.nbControlPoint - i - 1] = (buffer[i][curve.nbControlPoint - i - 1]);
    }
    std::array<Curve, 2> ret = {part1, part2};
    return ret;
}