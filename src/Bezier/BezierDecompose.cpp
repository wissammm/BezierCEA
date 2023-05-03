#include "BezierDecompose.h"


std::array<Bezier, 2> decompose(const Bezier& curve, double t) {

    auto buffer = createBuffer(curve.degree);

    evalCasteljau(curve, t, buffer);

    //: SOURCE: https://www.youtube.com/watch?v=lPJo1jayLdc
    Bezier part1(curve.nbControlPoint);
    Bezier part2(curve.nbControlPoint);

    for (size_t i = 0; i < curve.nbControlPoint; ++i) {
        part1.controlPoint.push_back(buffer[i][0]);
        part2.controlPoint[curve.nbControlPoint - i - 1] = (buffer[i][curve.nbControlPoint - i - 1]);
    }
    std::array<Bezier, 2> ret = {part1, part2};
    return ret;
}