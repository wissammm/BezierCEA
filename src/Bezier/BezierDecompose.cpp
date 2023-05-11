#include "BezierDecompose.h"

std::array<Bezier, 2> decompose(const Bezier& curve, double t) {

    auto buffer = createBuffer(curve.degree);

    evalCasteljau(curve, t, buffer);

    //: SOURCE: https://www.youtube.com/watch?v=lPJo1jayLdc
    Bezier part1(curve.nbControlPoint);
    Bezier part2(curve.nbControlPoint);

    for (size_t i = 0; i < curve.nbControlPoint; ++i) {
        part1.controlPoint[i] = buffer[i][0];
        part2.controlPoint[curve.nbControlPoint - i - 1] = buffer[i][curve.nbControlPoint - i - 1];
    }
    // if (curve.roots.size() > 0) {
    //     for (size_t i = 0; i < curve.roots.size(); ++i) {
    //         if (curve.roots[i].time > t) {
    //             part2.roots.push_back(curve.roots[i]);
    //         } else {
    //             part1.roots.push_back(curve.roots[i]);
    //         }
    //     }
    // }

    // if (curve.lut.size() > 0) {
    //     auto n    = curve.lut.size() * t;
    //     part1.lut = std::vector(curve.lut.begin(), curve.lut.begin() + n);
    //     part1.lut = std::vector(curve.lut.begin() + n, curve.lut.end());
    // }
    std::array<Bezier, 2> ret = {part1, part2};
    return ret;
}