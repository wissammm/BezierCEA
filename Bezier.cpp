#include "Bezier.h"

Bezier elevate(const Bezier& curve) {
    Bezier retElevate(curve.size() + 1);
    retElevate[0] = curve[0];

    Coord tmpPoint;
    for (size_t i = 1; i < (curve.size() + 1); i++) {
        tmpPoint      = (((curve.size() - i) * curve[i]) + (curve[i - 1] * i)) / (curve.size());
        retElevate[i] = tmpPoint;
    }
    retElevate[curve.size()] = curve[curve.size() - 1];
    return retElevate;
}