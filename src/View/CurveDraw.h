#pragma once
#include "View/Color.h"
#include "Bezier/Bezier.h"
#include <string>

struct CurveDraw{
    uint id;
    Curve bezier;
    std::vector<Coord> points;
    std::string name;
    Color c = Color(20,20,20);
};