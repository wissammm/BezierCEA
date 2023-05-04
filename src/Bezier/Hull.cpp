#include "Hull.h"

#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDerivate.h"
#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Geometry/Newton.h"
#include <vector>
#include <optional>
#include <cmath>

bool isIntersectSegmentHull(std::vector<Coord> hull, Segment seg) {
    auto intersect = lineLineIntersection(seg, Segment({hull[0], hull[hull.size() - 1]}));
    if (intersect)
        return true;
    for (size_t i = 0; i < hull.size() - 1; ++i) {
        intersect = lineLineIntersection(seg, Segment({hull[i], hull[i + 1]}));
        if (intersect) {
            return true;
        }
    }
    return false;
}

bool isPointInHull(std::vector<Coord> hull, Coord point) {
    constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();
    Segment        seg        = Segment({point, Coord({MAX_DOUBLE - 1, MAX_DOUBLE - 1})}); //RAYON INFINI

    size_t cpt       = 0;
    auto   intersect = lineLineIntersection(seg, Segment({hull[0], hull[hull.size() - 1]}));
    if (intersect)
        cpt++;
    for (size_t i = 0; i < hull.size() - 1; ++i) {
        intersect = lineLineIntersection(seg, Segment({hull[i], hull[i + 1]}));
        if (intersect) {
            cpt++;
        }
    }
    return !(cpt % 2);
}

std::vector<Coord> minMaxFromPoints(std::vector<Coord> points) {
    std::vector<Coord> hull = std::vector<Coord>(4);
    double             xmax = -std::numeric_limits<double>::infinity();
    double             xmin = std::numeric_limits<double>::infinity();
    double             ymax = -std::numeric_limits<double>::infinity();
    double             ymin = std::numeric_limits<double>::infinity();
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].x < xmin) {
            xmin = points[i].x;
        } else if (points[i].x > xmax) {
            xmax = points[i].x;
        }
        if (points[i].y < ymin) {
            ymin = points[i].y;
        } else if (points[i].y > ymax) {
            ymax = points[i].y;
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
    std::vector<Coord> points;
    Buffer             buffer = createBuffer(curve.degree);
    for (Root r : curve.roots) {
        points.push_back(evalCasteljau(curve, r.time, buffer));
    }
    points.push_back(curve.lut[0].coord);
    points.push_back(curve.lut[curve.lut.size() - 1].coord);

    return minMaxFromPoints(points);
}

std::vector<Coord> minimumHull() { return std::vector<Coord>(); }