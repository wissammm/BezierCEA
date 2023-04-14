#pragma once
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include "View/View.h"
#include "View/CurveDraw.h"


using Selection = std::vector<std::string>;

Curve              createCurve();
void               printSelection(std::vector<std::string>& selection);
size_t             inInt(size_t const& max);
std::vector<Coord> getPositions(size_t& nbPoints);
std::string        chooseName();