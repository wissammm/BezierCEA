#include "BezierRayIntersection.h"
#include "Bezier.h"
#include "BezierEvaluate.h"
#include "BezierDerivate.h"
#include "BezierDecompose.h"
#include <algorithm>
#include <math.h>
#include <iostream>
#include <cmath>
using namespace std;

// Define a structure to represent a point

// Compute the intersection point of two line segments
Coord getIntersectionPoint(Coord a1, Coord a2, Coord b1, Coord b2) {
    double ua = ((b2.x - b1.x) * (a1.y - b1.y) - (b2.y - b1.y) * (a1.x - b1.x)) /
                ((b2.y - b1.y) * (a2.x - a1.x) - (b2.x - b1.x) * (a2.y - a1.y));
    Coord intersection;
    intersection.x = a1.x + ua * (a2.x - a1.x);
    intersection.y = a1.y + ua * (a2.y - a1.y);
    return intersection;
}

// Check if a point is on a line segment
bool isOnSegment(Coord p, Coord a, Coord b) {
    if (p.x <= fmax(a.x, b.x) && p.x >= fmin(a.x, b.x) && p.y <= fmax(a.y, b.y) && p.y >= fmin(a.y, b.y)) {
        return true;
    }
    return false;
}

// Check if a point is on both line segments
bool isOnBothSegments(Coord p, Coord a1, Coord a2, Coord b1, Coord b2) {
    if (isOnSegment(p, a1, a2) && isOnSegment(p, b1, b2)) {
        return true;
    }
    return false;
}

// Define the points for two line segments

int orientation(Coord p, Coord q, Coord r) {
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0; // collinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Coord p1, Coord q1, Coord p2, Coord q2) {
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && isOnSegment(p1, p2, q1))
        return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && isOnSegment(p1, q2, q1))
        return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && isOnSegment(p2, p1, q2))
        return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && isOnSegment(p2, q1, q2))
        return true;

    return false; // Doesn't fall in any of the above cases
}

bool touchHull(Curve bez, Segment seg) {
    if (doIntersect(bez.controlPoint[0], bez.controlPoint[bez.degree], seg.a, seg.b))
        return true;
    for (int i = 0; i < bez.degree; ++i) {
        if (doIntersect(bez.controlPoint[i], bez.controlPoint[i + 1], seg.a, seg.b))
            return true;
    }
    return false;
}

std::vector<Coord> translatePointsTo0(std::vector<Coord> bez) {
    // translate so that the curve starts at (0,0)
    std::vector<Coord> translate(bez.size());

    for (int i = 0; i < translate.size(); ++i) {
        translate[0] = translate[i] - translate[0];
    }
    return translate;
}

std::vector<Coord> rotateToX(std::vector<Coord> bez) {
    // translate so that the curve starts at (0,0)
    std::vector<Coord> rotate(bez.size());
    double             a = std::atan2(bez[bez.size() - 1].y, bez[bez.size() - 1].x);
    Coord              p;
    for (int i = 0; i < rotate.size(); ++i) {
        p.x    = bez[i].x * std::cos(-a) - bez[i].y * std::sin(-a);
        p.y    = bez[i].x * std::sin(-a) + bez[i].y * std::sin(-a);
        bez[i] = p;
    }
    return rotate;
}

std::vector<double> firstGuesses(Curve bez, Segment seg) { return std::vector<double>(); }

double getTimeByResult(Coord A, Coord B, Coord C) { return (C.x - B.x) / (A.x - B.x); }

double newtonMethod(Curve bez, double guessT, Segment seg, double epsilone) {
    Curve deriv = derivate(bez);

    double temps = guessT + 10;
    //search x
    Buffer bufferCurve  = createBuffer(bez.degree);
    Buffer bufferDerive = createBuffer(bez.degree-1);
    double a            = (seg.a.y - seg.b.y / seg.a.x - seg.b.x);
    double b            = -a * seg.b.x + seg.b.y;
    do {
        guessT = temps;
        temps  = guessT - (evalCasteljau(bez, guessT, bufferCurve).x / evalCasteljau(deriv, guessT, bufferDerive).x) -
                (a * temps + b);
    }while (std::abs(guessT - temps) > epsilone);
    
    return temps;
}

std::vector<Coord> intersectionNewtonMethod(Curve bez, Segment seg, double epsilone) {
    // Etape 0 : vérifiation boite englobante
    // if (!touchHull(bez, seg)) {
    //     return std::vector<Coord>();
    // }
    Buffer bufferCurve = createBuffer(bez.degree);
    double guessT      = newtonMethod(bez, 0.5, seg, 0.1);
    printf("guess t = %f", guessT);
    // Etape 1 : translate et rotate Seg sur l'axe 0, appliquer la meme transformation à bez et à ses first guests
    // seg sur l'axe 0 : fait;
    // à faire

    // Etape 1 : trouver les first guests, avec la méthode de Thibaud
    // A faire : firstGuesses()

    // Etape 3 : résoudre f(x) = 0, avec la méthode de newton pour chaque guess
    // Fait
    return std::vector<Coord>({evalCasteljau(bez, guessT, bufferCurve)});
}

std::vector<Coord> intersectionNaive(Curve bez, Segment seg) {

    std::vector<Coord> guesses;
    auto               points = casteljau(bez, 20);
    for (int i = 0; i < points.size() - 1; ++i) {

        if (doIntersect(seg.a, seg.b, points[i], points[i + 1])) {
            auto point = getIntersectionPoint(seg.a, seg.b, points[i], points[i + 1]);
            if (isOnBothSegments(point, seg.a, seg.b, points[i], points[i + 1])) {
                guesses.push_back(point);
            }
        }
    }
    return guesses;
}
