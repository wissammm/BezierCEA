#include "BezierDerivate.h"

Curve derivate(const Curve& curve) {

    //: SOURCE: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
    //: COMMENT: pas sur que ca marche ...
    Curve retDeriv(curve.degree);

    for (size_t i = 1; i < retDeriv.nbControlPoint; i++) {
        retDeriv.controlPoint[i - 1] =  static_cast<double>(curve.nbControlPoint) * (curve.controlPoint[i - 1] - curve.controlPoint[i]) ;
    }
    return retDeriv;
}

