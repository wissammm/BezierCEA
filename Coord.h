#pragma once

#include <vector>

struct Coord : Drawable
{
    double x;
    double y;
};

struct Segment : Drawable
{
    Coord a;
    Coord b;
};

struct Bezier : Drawable
{
    std::vector<Coord> bezier;
    size_t             size() { return bezier.size(); };    
};

struct Segments : Drawable
{
    std::vector<Segment> segments;

    size_t size() { return segments.size(); };

};

struct Drawable
{
};

Coord operator-(const Coord& coord);
Coord operator+(const Coord& coord1, const Coord& coord2);
Coord operator-(const Coord& coord1, const Coord& coord2);
Coord operator*(const Coord& coord, double factor);
Coord operator*(double factor, const Coord& coord);
