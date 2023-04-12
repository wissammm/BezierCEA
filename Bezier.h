#pragma once

#include "Coord.h"
#include <vector>

using Bezier   = std::vector<Coord>;


Bezier elevate(const Bezier& curve);