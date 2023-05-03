#include "Hull.h"

#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDerivate.h"
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include <vector>
#include <optional>
#include <cmath>

std::vector<Coord> simpleHull(Bezier curve) {
    std::vector<Coord> hull = std::vector<Coord>(4);
    double             xmax = -std::numeric_limits<double>::infinity();
    double             xmin = std::numeric_limits<double>::infinity();
    double             ymax = -std::numeric_limits<double>::infinity();
    double             ymin = std::numeric_limits<double>::infinity();
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

double findExtremum(Bezier  derivateFirst,
                    Bezier  derivateSecond,
                    double firstGuess,
                    char   axis,
                    Buffer first,
                    Buffer second,
                    double epsilon,
                    double minRange,
                    double maxRange) {
    std::optional<double>  result;

    if (axis == 'x') {
        const auto f = [&](double u) {
            Coord Cu = evalCasteljau(derivateFirst, u, first);
            return Cu.x;
        };
        const auto df = [&](double u) {
            Coord CuPrim = evalCasteljau(derivateSecond, u, second);
            return CuPrim.x;
        };
        result = newton(f, df, firstGuess, epsilon, 100);
    } else if (axis == 'y') {
        const auto f = [&](double u) {
            Coord Cu = evalCasteljau(derivateFirst, u, first);
            return Cu.y;
        };
        const auto df = [&](double u) {
            Coord CuPrim = evalCasteljau(derivateSecond, u, second);
            return CuPrim.y;
        };
        result = newton(f, df, firstGuess, epsilon, 100);
    }

    if (result)
        return *result;
    else
        return firstGuess;
}

std::vector<Coord> convexHull(Bezier curve) {
    double epsilon     = 0.005;
    Bezier  derivFirst  = derivate(curve);
    auto   derivSecond = derivate(derivFirst);

    Buffer buffer            = createBuffer(curve.degree);
    Buffer bufferDerivFirst  = createBuffer(derivFirst.degree);
    Buffer bufferDerivSecond = createBuffer(derivSecond.degree);

    //Newton
    double guessT = 0.5;
    Coord  C, Cu, CuPrim;
    double Fu, FuPrim;
    int    cpt = 0;

    double u = guessT;
    //xmax
    auto xminFirst  = std::numeric_limits<double>::max();
    auto xminSecond = std::numeric_limits<double>::max();

    do {
        C      = evalCasteljau(curve, guessT, buffer);
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