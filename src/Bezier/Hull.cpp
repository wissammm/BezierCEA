#include "Hull.h"

#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDerivate.h"
#include "Geometry/Coord.h"
#include <vector>
#include <cmath>

std::vector<Coord> simpleHull(Curve curve) {
    std::vector<Coord> hull = std::vector<Coord>(4);
    double             xmax = __DBL_MIN__;
    double             xmin = __DBL_MAX__;
    double             ymax = __DBL_MIN__;
    double             ymin = __DBL_MAX__;
    for (size_t i = 0; i < curve.nbControlPoint; ++i) {
        if (curve.controlPoint[i].x < xmin) {
            xmin = curve.controlPoint[i].x;
        } else if (curve.controlPoint[i].x > xmax) {
            xmax = curve.controlPoint[i].x;
        }
        if (curve.controlPoint[i].y < ymin) {
            ymin = curve.controlPoint[i].y;
        } else if (curve.controlPoint[i].y > ymax) {
            ymax = curve.controlPoint[i].y;
        }
    }
    hull[0] = Coord({xmin, ymax});
    hull[1] = Coord({xmax, ymax});
    hull[2] = Coord({xmax, ymin});
    hull[3] = Coord({xmin, ymin});
    return hull;
}

std::vector<Coord> convexHull(Curve curve) {
    double epsilon     = 0.005;
    Curve  derivFirst  = derivate(curve);
    auto   derivSecond = derivate(derivFirst);

    Buffer buffer = createBuffer(curve.degree);
    Buffer bufferDerivFirst  = createBuffer(derivFirst.degree);
    Buffer bufferDerivSecond = createBuffer(derivSecond.degree);

    //Newton
    double guessT = 0.5;
    Coord  C , Cu, CuPrim;
    double Fu, FuPrim;
    int    cpt = 0;

    double u = guessT;
    //xmax
    auto xminFirst  = __DBL_MAX__;
    auto xminSecond = __DBL_MAX__;

    do {
        C =  evalCasteljau(curve, guessT, buffer);
        Cu     = evalCasteljau(derivFirst, guessT, bufferDerivFirst);
        CuPrim = evalCasteljau(derivSecond, guessT, bufferDerivSecond);

        xminFirst  = std::min(xminFirst, Cu.x);
        xminSecond = std::min(xminSecond, CuPrim.x);

        // FuPrim = dy * CuPrim.x - dx * CuPrim.y;
        guessT = u;
        u      = (guessT - (xminFirst / xminSecond));

        cpt++;
    } while (std::abs(guessT - u) > epsilon);

    return std::vector<Coord>();
}

std::vector<Coord> minimumHull() { return std::vector<Coord>(); }