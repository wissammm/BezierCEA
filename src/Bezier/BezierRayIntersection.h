#pragma once

#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include <optional>

enum OPTIONS{
    NAIVE,
    NEWTON,
};


struct NewtonForBezier
{
  public:
    double  u;
    Curve   curve;
    Segment axe;
    double  dx, dy;
    Curve   deriv;
    Coord   Cu, CuPrim;
    Buffer  bufferCurve;
    Buffer  bufferDerive;

    NewtonForBezier(double guess, Curve bez, Segment seg);

    // std::optional<double> computeNewton();

    double d(double prevU);
    double df(double prevU);

  private:
    void computeVariables();
};

struct Intersection{
    Coord inter;
    double time;
};

bool touchHull(Curve bez, Segment seg);
double newtonMethod(Curve bez, double guessT, Segment seg, double epsilon);
std::vector<Intersection> intersectionNewtonMethod(Curve bez, Segment seg, double epsilon);
std::vector<Intersection> intersectionNaive(Curve bez, Segment seg, size_t nbPoints);
std::vector<Intersection> getAllIntersections(Segments segments, Curves curves, double epsilone, OPTIONS options);