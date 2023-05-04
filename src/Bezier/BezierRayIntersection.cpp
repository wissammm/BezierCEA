#include "BezierRayIntersection.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include "BezierDerivate.h"
#include "BezierDecompose.h"
#include "Geometry/Newton.h"
#include <optional>
#include <algorithm>
#include <math.h>

#define TOLERANCE 0.1
#include <iostream>
#include <cmath>
using namespace std;

double newtonMethodIntersectionBezierRay(Bezier bez, double guessT, Segment seg, double epsilon) {
    bez                 = changeOrigin(bez, seg.a);
    seg.b               = seg.b - seg.a;
    seg.a               = Coord({0.0, 0.0});
    Bezier deriv        = derivate(bez);
    Buffer bufferBezier = createBuffer(bez.degree);
    Buffer bufferDerive = createBuffer(bez.degree - 1);

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
    const auto result = newton(f, df, guessT, { .epsilon = epsilon, .nMaxIterations = 1000000});

    if (result)
        return *result;
    else
        return guessT;
}

std::vector<CoordTime> intersectionNewtonMethod(Bezier bez, Segment seg, double epsilon, size_t nbPointOnBezier) {

    Buffer                 bufferBezier = createBuffer(bez.degree);
    auto                   guessesNaive = intersectionNaive(bez, seg, nbPointOnBezier);
    std::vector<CoordTime> guessesNewton;
    for (const CoordTime& inter : guessesNaive) {
        double newton = newtonMethodIntersectionBezierRay(bez, inter.time, seg, epsilon);
        guessesNewton.push_back({evalCasteljau(bez, newton, bufferBezier), newton});
    }
    return guessesNewton;
}

std::vector<CoordTime> intersectionNaive(Bezier bez, Segment seg, size_t nbPoints) {
    constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();

    std::vector<CoordTime> guesses;
    auto                   points = casteljau(bez, nbPoints);
    for (int i = 0; i < points.size() - 1; ++i) {
        // Vraiment CRACRA TODO, changer ça
        // TODO rajouter la hull 
        auto point = lineLineIntersection(seg.a, seg.b, points[i], points[i + 1]);

        if (point) {
            if (isOnBothSegments(*point, seg.a, seg.b, points[i], points[i + 1]) && points[i].x != MAX_DOUBLE &&
                points[i].y != MAX_DOUBLE) {

                guesses.push_back(CoordTime({*point, static_cast<double>(i) / static_cast<double>(nbPoints)}));
            }
        }
    }

    return guesses;
}

// std::vector<CoordTime> getAllIntersections(Segments segments, Beziers curves, double epsilone, OPTIONS options) {
//     return std::vector<CoordTime>();
// }