#include "BoundingBox.h"

#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDerivate.h"
#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Geometry/Newton.h"
#include <vector>
#include <optional>
#include <cmath>

bool isIntersectSegmentBoundingBox(AABB aabb, Segment seg) {
    if (isPointInAABB(aabb, seg.a) && !isPointInAABB(aabb, seg.b) ||
        isPointInAABB(aabb, seg.b) && !isPointInAABB(aabb, seg.a))
        return true;
    return false;
}

// bool isPointInPolygon(std::vector<Coord> hull, Coord point) {
//     constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();
//     Segment        seg        = Segment({point, Coord({MAX_DOUBLE - 1, MAX_DOUBLE - 1})}); //RAYON INFINI

//     size_t cpt       = 0;
//     auto   intersect = lineLineIntersection(seg, Segment({hull[0], hull[hull.size() - 1]}));
//     if (intersect)
//         cpt++;
//     for (size_t i = 0; i < hull.size() - 1; ++i) {
//         intersect = lineLineIntersection(seg, Segment({hull[i], hull[i + 1]}));
//         if (intersect) {
//             cpt++;
//         }
//     }
//     return !(cpt % 2);
// }

std::vector<Coord> AABBtoQuad(AABB aabb) {
    std::vector<Coord> hull = std::vector<Coord>(4);
    hull[0]                 = Coord({aabb.base.x, aabb.base.y + aabb.h});
    hull[1]                 = Coord({aabb.base.x + aabb.w, aabb.base.y + aabb.h});
    hull[2]                 = Coord({aabb.base.x + aabb.w, aabb.base.y});
    hull[3]                 = aabb.base;
    return hull;
}

bool isPointInAABB(AABB aabb, Coord point) {
    if (point.x > aabb.base.x && point.x < aabb.base.x + aabb.w && point.y > aabb.base.y &&
        point.y < aabb.base.y + aabb.h) {
        return true;
    }
    return false;
}

bool isAABBintersectAABB(AABB aabb1, AABB aabb2) {
    if ((aabb2.base.x >= aabb1.base.x + aabb1.w)     // trop à droite
        || (aabb2.base.x + aabb2.w <= aabb1.base.x)  // trop à gauche
        || (aabb2.base.y >= aabb1.base.y + aabb1.h)  // trop en bas
        || (aabb2.base.y + aabb2.h <= aabb1.base.y)) // trop en haut
        return false;
    else
        return true;
}

AABB minMaxFromPoints(std::vector<Coord> points) {
    AABB aabb;
    aabb.w      = -std::numeric_limits<double>::infinity();
    aabb.base.x = std::numeric_limits<double>::infinity();
    aabb.h      = -std::numeric_limits<double>::infinity();
    aabb.base.y = std::numeric_limits<double>::infinity();
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].x < aabb.base.x) {
            aabb.base.x = points[i].x;
        } else if (points[i].x > aabb.base.x + aabb.w) {
            aabb.w = aabb.w - aabb.base.x;
        }
        if (points[i].y < aabb.base.y) {
            aabb.base.y = points[i].y;
        } else if (points[i].y > aabb.base.y + aabb.h) {
            aabb.h = aabb.h - aabb.base.y;
        }
    }
    return aabb;
}

std::vector<AABB> decomposeAABBinTwo(AABB aabb) {
    std::vector<AABB> doubleAABB = std::vector<AABB>(2);
    if (aabb.h <= aabb.w) {
        doubleAABB[0] = AABB(aabb.base, aabb.w / 2.0, aabb.h);
        doubleAABB[1] = AABB(Coord({aabb.w / 2.0, aabb.h}), aabb.w, aabb.h);
        return doubleAABB;
    }
    doubleAABB[0] = AABB(aabb.base, aabb.w, aabb.h / 2.0);
    doubleAABB[1] = AABB(Coord({aabb.w, aabb.h / 2.0}), aabb.w, aabb.h);
    return doubleAABB;
}

std::optional<double> findExtremum(Bezier               derivateFirst,
                                   Bezier               derivateSecond,
                                   double               firstGuess,
                                   char                 axis,
                                   Buffer               first,
                                   Buffer               second,
                                   const NewtonOptions& options) {
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
        result = newton(f, df, firstGuess, {.epsilon = 0.0001, .nMaxIterations = 100});
    } else if (axis == 'y') {
        const auto f = [&](double u) {
            Coord Cu = evalCasteljau(derivateFirst, u, first);
            return Cu.y;
        };
        const auto df = [&](double u) {
            Coord CuPrim = evalCasteljau(derivateSecond, u, second);
            return CuPrim.y;
        };
        result = newton(f, df, firstGuess, {.epsilon = 0.0001, .nMaxIterations = 100});
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
AABB convexBoundingBox(Bezier& curve) {

    double nbPointsLUT = 2 * curve.degree; // comme la fréquence d'echantillonage
    curve.lut          = computeLUT(curve, nbPointsLUT);
    curve.roots        = rootsFromLUT(curve, curve.lut);
    std::vector<Coord> points;
    Buffer             buffer = createBuffer(curve.degree);
    for (Root r : curve.roots) {
        points.push_back(evalCasteljau(curve, r.time, buffer));
    }
    points.push_back(curve.controlPoint[0]);
    points.push_back(curve.controlPoint[curve.controlPoint.size() - 1]);

    return minMaxFromPoints(points);
}

AABB minimumBoundingBox() { return AABB(); }