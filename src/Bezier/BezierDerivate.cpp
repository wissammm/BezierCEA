#include "BezierDerivate.h"
#include "Geometry/Coord.h"

Bezier derivate(const Bezier& curve) {

    //: SOURCE: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
    //: COMMENT: pas sur que ca marche ...
    Bezier retDeriv(curve.degree);

    for (size_t i = 1; i < curve.nbControlPoint; i++) {
        retDeriv.controlPoint[i - 1] =  static_cast<double>(curve.degree) *
         (curve.controlPoint[i] - curve.controlPoint[i - 1] ) ;
    }
    return retDeriv;
}

