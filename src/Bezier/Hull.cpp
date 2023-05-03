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

std::optional<double> findExtremum(Bezier derivateFirst,
                                   Bezier derivateSecond,
                                   double firstGuess,
                                   char   axis,
                                   Buffer first,
                                   Buffer second,
                                   double epsilon,
                                   double minRange,
                                   double maxRange,
                                   double learningRate) {
    std::optional<double> result;

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

    return result;
}

std::vector<Root> rootsFromLUT(Bezier curve, std::vector<CoordTime> lut) {
    std::vector<Root> roots;

    double epsilon     = 0.005;
    Bezier derivFirst  = derivate(curve);
    auto   derivSecond = derivate(derivFirst);

    Buffer bufferDerivFirst  = createBuffer(derivFirst.degree);
    Buffer bufferDerivSecond = createBuffer(derivSecond.degree);
    double tmp               = -1;
    size_t cpt               = 0;
    double rootY             = -1;
    double rootX             = -1;
    for (CoordTime l : lut) {
        auto result = findExtremum(derivFirst, derivSecond, l.time, 'y', bufferDerivFirst, bufferDerivSecond);
        if (result)
            rootY = *result;

        if ((std::abs(rootY - tmp) > 0.00001) && (rootY >= 0 && rootY <= 1)) {
            roots.push_back(Root({rootY, true}));
            tmp = rootY;
            cpt++;
        }
        // if (cpt >= curve.degree - 1)
        //     break;
    }

    cpt = 0;
    tmp = -1;
    for (CoordTime l : lut) {
        auto result = findExtremum(derivFirst, derivSecond, l.time, 'x', bufferDerivFirst, bufferDerivSecond);
        if (result)
            rootX = *result;

        if ((std::abs(rootX - tmp) > 0.00001) && (rootX >= 0 && rootX <= 1)) {
            roots.push_back(Root({rootX, false}));
            tmp = rootX;
        }
        // if (cpt >= curve.degree - 1)
        //     break;
    }

    return roots;
}

std::vector<Coord> convexHull(Bezier& curve) {

    double nbPointsLUT = 2 * curve.degree; // comme la fréquence d'echantillonage
    curve.lut          = computeLUT(curve, nbPointsLUT);
    curve.roots        = rootsFromLUT(curve, curve.lut);

    return std::vector<Coord>(1);
}

std::vector<Coord> minimumHull() { return std::vector<Coord>(); }