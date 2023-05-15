#include "BezierRayIntersection.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include "BezierDerivate.h"
#include "BezierDecompose.h"
#include "BoundingBox.h"
#include "Geometry/Newton.h"
#include "Geometry/Segment.h"
#include <optional>
#include <algorithm>
#include <math.h>
#include <stack>
#define EPSILON_ANGLE 0.000001

#define TOLERANCE 0.1
#include <iostream>
#include <cmath>

bool isControlPointsFlat(std::vector<Coord> controlPoints, double epsilon) {
    if(controlPoints.size() <= 2) std::cerr << "WARNING : Invalid control point size, may be size 3 or more " << std::endl;
    for (size_t i = 1; i < controlPoints.size() - 1; i++) {
        auto A = controlPoints[i - 1];
        auto B = controlPoints[i];
        auto C = controlPoints[i + 1];

        auto u = B - A;
        auto v = C - B;

        if (!(determinant(u.x, u.y, v.x, v.y) <= epsilon * epsilon * dot(u, u) * dot(v, v))) {
            return false;
        }
    }
    
    return true;
}

double newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, NewtonOptions newtonOption) {
    bez                 = changeOrigin(bez, seg.a);
    seg.b               = seg.b - seg.a;
    seg.a               = Coord({0.0, 0.0});
    Bezier deriv        = derivate(bez);
    Buffer bufferBezier = createBuffer(bez.degree());
    Buffer bufferDerive = createBuffer(bez.degree() - 1);

    //veceur directeur
    double dy = seg.b.y / distance(seg);
    double dx = seg.b.x / distance(seg);

    const auto f = [&](double u) {
        Coord Cu = evalCasteljau(bez, u, bufferBezier);
        return dy * Cu.x - dx * Cu.y;
    };
    const auto df = [&](double u) {
        Coord CuPrim = evalCasteljau(deriv, u, bufferDerive);
        return dy * CuPrim.x - dx * CuPrim.y;
    };

    const auto result = newton(f, df, guessT, newtonOption);

    if (result)
        return *result;
    else
        return guessT;
}
//{.epsilon = epsilon, .nMaxIterations = 1000000}

std::vector<double> rayBoundingBoxMethod(Bezier bez, Segment ray, BoundingBoxOptions aabbOptions) {

    size_t nb_iter = 0;

    std::stack<BezierWithInitialTime> bezierStack;
    double                            dy = (ray.b.y - ray.a.y) / distance(ray);
    double                            dx = (ray.b.x - ray.a.x) / distance(ray);
    bezierStack.push(BezierWithInitialTime({bez, 0.0, 1.0, 0}));
    std::vector<double> timesFoundInterpolate;
    while (bezierStack.size() > 0) {
        BezierWithInitialTime actualBez = bezierStack.top();
        bezierStack.pop();

        auto aabb  = convexBoundingBox(actualBez.bez);
        auto inter = isIntersectRayAABB(ray.a, Coord({dx, dy}), aabb);

        if (inter) {
            if (isControlPointsFlat(actualBez.bez.controlPoint, aabbOptions.flatAngle) ||
                actualBez.depth == aabbOptions.maxDepth) {
                timesFoundInterpolate.push_back(actualBez.tBegin + ((actualBez.tEnd - actualBez.tBegin) / 2.0));
            } else {
                actualBez.depth++;
                auto   decomposeBez = decompose(actualBez.bez, 0.5);
                double middle       = actualBez.tBegin + (actualBez.tEnd - actualBez.tBegin) / 2.0;
                bezierStack.push(BezierWithInitialTime({decomposeBez[0], actualBez.tBegin, middle, actualBez.depth++}));
                bezierStack.push(BezierWithInitialTime({decomposeBez[1], middle, actualBez.tEnd, actualBez.depth++}));
            }
        }

        nb_iter++;
    }

    return timesFoundInterpolate;
}

std::vector<CoordTime> intersectionNewtonMethod(Bezier                      bez,
                                                Segment                     seg,
                                                double                      epsilon,
                                                BezierRayIntersectionOption options) {

    Buffer                 bufferBezier = createBuffer(bez.degree());
    auto                   guessesNaive = intersectionNaive(bez, seg, options.naiveOptions);
    std::vector<CoordTime> guessesNewton;

    for (const CoordTime& inter : guessesNaive) {
        double newton = newtonMethodIntersectionBezierRay(bez, inter.time, seg, options.newtonOptions);
        guessesNewton.push_back({evalCasteljau(bez, newton, bufferBezier), newton});
    }
    return guessesNewton;
}

std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, NaiveOptions naiveOptions) {
    constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();

    std::cerr << "WARNING :  intersectionNaive don't work correctly in certains cases \nWatch Tests" << std::endl;
    AABB aabb;
    if (!(naiveOptions.useSimpleBoundingBox)) {
        std::cerr << "WARNING : rootsBoundingBox can forget some roots in high degree curves" << std::endl;
        aabb = convexBoundingBox(bez);
    } else {
        aabb = simpleBoundingBox(bez);
    }
    std::vector<CoordTime> guesses;
    auto                   points = casteljau(bez, naiveOptions.nbPointsOnCurve);
    for (int i = 0; i < points.size() - 1; ++i) {

        if (isIntersectSegmentBoundingBox(aabb, seg)) {
            auto point = lineLineIntersection(seg.a, seg.b, points[i], points[i + 1]);

            if (point) {
                if (isOnBothSegments(*point, seg.a, seg.b, points[i], points[i + 1])) {

                    guesses.push_back(CoordTime(
                        {*point, static_cast<double>(i) / static_cast<double>(naiveOptions.nbPointsOnCurve)}));
                }
            }
        }
    }
    return guesses;
}
