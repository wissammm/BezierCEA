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

bool touchHull(Curve bez, Segment seg) {
    if (doIntersect(bez.controlPoint[0], bez.controlPoint[bez.degree], seg.a, seg.b))
        return true;
    for (int i = 0; i < bez.degree; ++i) {
        if (doIntersect(bez.controlPoint[i], bez.controlPoint[i + 1], seg.a, seg.b))
            return true;
    }
    return false;
}

NewtonForBezier::NewtonForBezier(double guess, Curve bez, Segment seg) {
    u     = guess;
    curve = bez;
    axe   = seg;

    curve = changeOrigin(bez, seg.a);

    axe.b        = axe.b - axe.a;
    axe.a        = Coord({0.0, 0.0});
    deriv        = derivate(curve);
    bufferCurve  = createBuffer(curve.degree);
    bufferDerive = createBuffer(curve.degree - 1);

    //veceur directeur
    dy = axe.b.y / distance(axe);
    dx = axe.b.x / distance(axe);
};

std::optional<double> NewtonForBezier::computeNewton() {
    const auto f = [&]() { return this->d(); };
    std::optional<double> newtonResult = newton(this->d, this->df, u);
    return newtonResult;
}

double NewtonForBezier::d(double prevU) {
    u = prevU;
    computeVariables();
    double Fu;
    Fu = dy * Cu.x - dx * Cu.y;
    return Fu;
};

double NewtonForBezier::df(double prevU) {
    double FuPrim;
    FuPrim = dy * CuPrim.x - dx * CuPrim.y;
    return FuPrim;
};

void NewtonForBezier::computeVariables() {
    Cu     = evalCasteljau(curve, u, bufferCurve);
    CuPrim = evalCasteljau(deriv, u, bufferDerive);
};

double newtonMethod(Curve bez, double guessT, Segment seg, double epsilon) {
    bez                 = changeOrigin(bez, seg.a);
    seg.b               = seg.b - seg.a;
    seg.a               = Coord({0.0, 0.0});
    Curve  deriv        = derivate(bez);
    Buffer bufferCurve  = createBuffer(bez.degree);
    Buffer bufferDerive = createBuffer(bez.degree - 1);

    //veceur directeur
    double dy = seg.b.y / distance(seg);
    double dx = seg.b.x / distance(seg);
    double u  = guessT;

    Coord  Cu, CuPrim;
    double Fu, FuPrim;
    int    cpt = 0;
    do {
        Cu     = evalCasteljau(bez, guessT, bufferCurve);
        CuPrim = evalCasteljau(deriv, guessT, bufferDerive);

        Fu     = dy * Cu.x - dx * Cu.y;
        FuPrim = dy * CuPrim.x - dx * CuPrim.y;
        guessT = u;
        u      = (guessT - (Fu / FuPrim));

        cpt++;
    } while (std::abs(guessT - u) > epsilon);
    return u;
}

std::vector<Intersection> intersectionNewtonMethod(Curve bez, Segment seg, double epsilon) {

    Buffer                    bufferCurve  = createBuffer(bez.degree);
    auto                      guessesNaive = intersectionNaive(bez, seg, 10);
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
        // Vraiment CRACRA TODO, changer ça

        auto point = lineLineIntersection(seg.a, seg.b, points[i], points[i + 1]);

        if (isOnBothSegments(point, seg.a, seg.b, points[i], points[i + 1]) && points[i].x != __DBL_MAX__ &&
            points[i].y != __DBL_MAX__) {

            guesses.push_back(Intersection({point, static_cast<double>(i) / static_cast<double>(nbPoints)}));
        }
    }

    return guesses;
}

std::vector<Intersection> getAllIntersections(Segments segments, Curves curves, double epsilone, OPTIONS options) {
    return std::vector<Intersection>();
}