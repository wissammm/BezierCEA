#pragma once
#include "Bezier.h"

std::vector<double> curveCurveBoundingBoxMethod(Bezier bez1, Bezier bez2, size_t nb_max_iter);
