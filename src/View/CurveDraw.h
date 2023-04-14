#pragma once
#include "View/Color.h"
#include <string>

struct Curve{
    uint id;
    Bezier bezier;
    std::vector<Coord> points;
    std::string name;
    Color c = Color(20,20,20);
};