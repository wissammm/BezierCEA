#pragma once
#include "Geometry/Coord.h"
#include <vector>
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"

double             findExtremum(Bezier  derivateFirst,
                                Bezier  derivateSecond,
                                double firstGuess,
                                char   axis,
                                Buffer first,
                                Buffer second,
                                double epsilon,
                                double learningRate,
                                double minRange,
                                double maxRange);
std::vector<Coord> simpleHull(Bezier curve);
std::vector<Coord> convexHull(Bezier curve);
