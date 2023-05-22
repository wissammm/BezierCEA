//testRayIntersect.cpp

#include <limits.h>
#include <iostream>
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include "Geometry/Segment.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BoundingBox.h"
#include "Bezier/BezierEvaluate.h"
#include "gtest/gtest.h"
#include <optional>
#include <cmath>
#include <random>

//TODO : Mettre a jour les appels de tests

TEST(Angle, flatAngle) {
    auto aabb1 = std::vector<Coord>{Coord({1, 0}), Coord({0, 0}), Coord({1, 1}), Coord({0, 1})};

    auto hull1 = minMaxFromPoints(aabb1);

    auto aabb2 = std::vector<Coord>{Coord({1.5, 0.5}), Coord({0.5, 0.5}), Coord({1.5, 1.5}), Coord({0.5, 1.5})};

    auto hull2 = minMaxFromPoints(aabb2);

    EXPECT_TRUE(isAABBintersectAABB(hull1, hull2));
}
