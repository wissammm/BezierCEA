#pragma once
#include "Bezier.h"
#include "Coord.h"


using Selection = std::vector<std::string>;

Curve              createCurve();
void               printSelection(std::vector<std::string>& selection);
size_t             inInt(size_t const& max);
std::vector<Coord> getPositions(size_t& nbPoints);
std::string        chooseName();