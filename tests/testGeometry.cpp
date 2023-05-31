//testRayIntersect.cpp

#include <limits.h>
#include <iostream>
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include "Geometry/Doublons.h"
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
    auto points = std::vector<Coord>{Coord({0, 0}), Coord({1, 0}), Coord({2, 15})};

    auto flat = isControlPointsFlat(points, 0.0001);
    EXPECT_FALSE(flat);

    points = std::vector<Coord>{Coord({0, 0}), Coord({1, 0}), Coord({2, 0.000000000001})};

    flat = isControlPointsFlat(points, 0.0001);
    EXPECT_TRUE(flat);
}

TEST(Angle, flatAngleSpecialCase1) {
    auto points = std::vector<Coord>{Coord({103, 198}), Coord({105, 115}), Coord({81, 255})};

    auto flat = isControlPointsFlat(points, 0.00000000000000001);
    EXPECT_FALSE(flat);
}

TEST(Doublons, doublonsSimple) {
    const auto          f = [&](double a, double b) { return std::abs(a - b) < 1; };
    std::vector<double> d{50, 50, 65, 48, 56, 78, 15, 50, 48};
    auto                sansDoublons = doublons(d, f);
    ASSERT_EQ(sansDoublons.size(),d.size()-3);
}
