#include "BezierRayIntersection.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include "BezierDerivate.h"
#include "BezierDecompose.h"
#include <algorithm>
#include <math.h>

#define TOLERANCE 0.1
#include <iostream>
#include <cmath>
using namespace std;

bool touchHull(Curve bez, Segment seg) {
    if (doIntersect(bez.controlPoint[0], bez.controlPoint[bez.degree], seg.a, seg.b))
        return true;
    for (int i = 0; i < bez.degree; ++i) {
        if (doIntersect(bez.controlPoint[i], bez.controlPoint[i + 1], seg.a, seg.b))
            return true;
    }
    return false;
}

double newtonMethod(Curve bez, double guessT, Segment seg, double epsilon) {
    bez                 = changeOrigin(bez, seg.a);
    seg.b               = seg.b - seg.a;
    seg.a               = Coord({0.0, 0.0});
    Curve  deriv        = derivate(bez);
    Buffer bufferCurve  = createBuffer(bez.degree);
    Buffer bufferDerive = createBuffer(bez.degree - 1);

    double dy = seg.b.y / distance(seg);
    double dx = seg.b.x / distance(seg);
    double u;

    Coord  Cu, CuPrim;
    double Fu, FuPrim;
    int    cpt = 0;
    do {
        Cu     = evalCasteljau(bez, guessT, bufferCurve);
        CuPrim = evalCasteljau(deriv, guessT, bufferDerive);

        Fu     = dy * Cu.x - dx * Cu.y;
        FuPrim = dy * CuPrim.x - dx * CuPrim.y;
        guessT = u;
        u      = guessT - (Fu / FuPrim);
        cpt++;
    } while (std::abs(guessT - u) > epsilon);
    return u;
}

std::vector<Intersection> intersectionNewtonMethod(Curve bez, Segment seg, double epsilon) {

    Buffer                    bufferCurve  = createBuffer(bez.degree);
    auto                      guessesNaive = intersectionNaive(bez, seg, 1000);
    std::vector<Intersection> guessesNewton;
    for (const Intersection& inter : guessesNaive) {

        double newton = newtonMethod(bez, inter.time, seg, epsilon);
        guessesNewton.push_back({evalCasteljau(bez, newton, bufferCurve), newton});
    }
    return guessesNewton;
}

std::vector<Intersection> intersectionNaive(Curve bez, Segment seg, size_t nbPoints) {

    std::vector<Intersection> guesses;
    auto                      points = casteljau(bez, nbPoints);
    for (int i = 0; i < points.size() - 1; ++i) {

        if (doIntersect(seg.a, points[i], seg.b, points[i + 1])) {

            auto point = intersect(seg.a, points[i], seg.b, points[i + 1]);

            if (onSegment(point, points[i], points[i + 1])) {

                guesses.push_back(Intersection({point, static_cast<double>(i) / static_cast<double>(nbPoints)}));
            }
        }
    }
    return guesses;
}

std::vector<Intersection> getAllIntersections(Segments segments, Curves curves, double epsilone, OPTIONS options) {
    return std::vector<Intersection>();
}