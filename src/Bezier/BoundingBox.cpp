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

#define EPSILON_RAY_INTERSECT 1e-20

bool isIntersectRayAABB(Coord rayOrigin, Coord rayDir, AABB aabb) {
    double epsilon = 0;
    if (rayDir.x == 0)
        epsilon = EPSILON_RAY_INTERSECT;
    auto tmin = (aabb.base.x - rayOrigin.x) / (rayDir.x + epsilon);
    auto tmax = (aabb.base.x + aabb.w - rayOrigin.x) / (rayDir.x + epsilon);

    if (tmin > tmax)
        std::swap(tmin, tmax);

    if (rayDir.y != 0)
        epsilon = 0;
    else
        epsilon = EPSILON_RAY_INTERSECT;

    auto tymin = (aabb.base.y - rayOrigin.y) / (rayDir.y + epsilon);
    auto tymax = (aabb.base.y + aabb.h - rayOrigin.y) / (rayDir.y + epsilon);

    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    return true;
};

std::vector<Coord> AABBtoQuad(AABB aabb) {
    std::vector<Coord> hull = std::vector<Coord>(4);
    hull[0]                 = Coord({aabb.base.x, aabb.base.y + aabb.h});
    hull[1]                 = Coord({aabb.base.x + aabb.w, aabb.base.y + aabb.h});
    hull[2]                 = Coord({aabb.base.x + aabb.w, aabb.base.y});
    hull[3]                 = aabb.base;
    return hull;
}

bool isPointInAABB(AABB aabb, Coord point) {
    if (point.x >= aabb.base.x && point.x <= aabb.base.x + aabb.w && point.y >= aabb.base.y &&
        point.y <= aabb.base.y + aabb.h) {
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
    AABB   aabb;
    double xmax = -std::numeric_limits<double>::infinity() + 1;
    double xmin = std::numeric_limits<double>::infinity();
    double ymax = -std::numeric_limits<double>::infinity() + 1;
    double ymin = std::numeric_limits<double>::infinity();
    for (size_t i = 0; i < points.size(); ++i) {
        if (points[i].x < xmin) {
            xmin = points[i].x;
        }
        if (points[i].x > xmax) {
            xmax = points[i].x;
        }
        if (points[i].y < ymin) {
            ymin = points[i].y;
        }
        if (points[i].y > ymax) {
            ymax = points[i].y;
        }
    }
    aabb.base = Coord({xmin, ymin});
    aabb.h    = ymax - ymin;
    aabb.w    = xmax - xmin;
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

    Buffer bufferDerivFirst  = createBuffer(derivFirst.degree());
    Buffer bufferDerivSecond = createBuffer(derivSecond.degree());
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
AABB convexBoundingBox(Bezier curve) {

    double nbPointsLUT = 2 * curve.degree(); // comme la fréquence d'echantillonage

    auto lut   = computeLUT(curve, nbPointsLUT);
    auto roots = rootsFromLUT(curve, lut);

    std::vector<Coord> points;
    Buffer             buffer = createBuffer(curve.degree());
    for (Root r : roots) {
        points.push_back(evalCasteljau(curve, r.time, buffer));
    }
    points.push_back(curve.controlPoint[0]);
    points.push_back(curve.controlPoint[curve.controlPoint.size() - 1]);

    return minMaxFromPoints(points);
}

AABB simpleBoundingBox(Bezier curve) { return minMaxFromPoints(curve.controlPoint); }