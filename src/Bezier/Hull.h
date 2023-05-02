#pragma once 
#include "Geometry/Coord.h"
#include <vector>
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"



std::vector<Coord> simpleHull(Curve curve);
std::vector<Coord> convexHull(Curve curve);
