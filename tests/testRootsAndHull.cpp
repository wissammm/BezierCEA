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

TEST(AABB, intersectionsAABB_AABBsimple) {
    auto aabb1 = std::vector<Coord>{Coord({1, 0}), Coord({0, 0}), Coord({1, 1}), Coord({0, 1})};

    auto hull1 = minMaxFromPoints(aabb1);

    auto aabb2 = std::vector<Coord>{Coord({1.5, 0.5}), Coord({0.5, 0.5}), Coord({1.5, 1.5}), Coord({0.5, 1.5})};

    auto hull2 = minMaxFromPoints(aabb2);

    EXPECT_TRUE(isAABBintersectAABB(hull1, hull2));
}

TEST(AABB, intersectionsAABB_AABB_hullInHull) {
    auto aabb1 = std::vector<Coord>{Coord({1, 0}), Coord({0, 0}), Coord({1, 1}), Coord({0, 1})};

    auto hull1 = minMaxFromPoints(aabb1);

    auto aabb2 = std::vector<Coord>{Coord({0.7, 0.3}), Coord({0.3, 0.3}), Coord({0.7, 0.7}), Coord({0.3, 0.7})};

    auto hull2 = minMaxFromPoints(aabb2);

    EXPECT_TRUE(isAABBintersectAABB(hull1, hull2));
}

TEST(AABB, intersectionsAABB_AABB_vertice) {
    auto aabb1 = std::vector<Coord>{Coord({1, 0}), Coord({0, 0}), Coord({1, 1}), Coord({0, 1})};

    auto hull1 = minMaxFromPoints(aabb1);

    auto aabb2 = std::vector<Coord>{Coord({2, 1}), Coord({1, 1}), Coord({2, 2}), Coord({1, 2})};

    auto hull2 = minMaxFromPoints(aabb2);

    EXPECT_TRUE(isAABBintersectAABB(hull1, hull2));
}

TEST(AABB, intersectionsAABB_AABB_edge) {
    auto aabb1 = std::vector<Coord>{Coord({1, 0}), Coord({0, 0}), Coord({1, 1}), Coord({0, 1})};

    auto hull1 = minMaxFromPoints(aabb1);

    auto aabb2 = std::vector<Coord>{Coord({2, 0}), Coord({1, 0}), Coord({2, 1}), Coord({1, 1})};

    auto hull2 = minMaxFromPoints(aabb2);

    EXPECT_TRUE(isAABBintersectAABB(hull1, hull2));
}

TEST(AABB, simpleRoot) {
    Bezier curve = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({0.0, 1.5}), //symétrique
        Coord({1.0, 1.5}),
        Coord({1.0, 0.0}),
    }));

    double nbPointsLUT = 2 * curve.degree(); // comme la fréquence d'echantillonage

    auto lut   = computeLUT(curve, nbPointsLUT);
    auto roots = rootsFromLUT(curve, lut, 0.000001);

    EXPECT_TRUE(roots[0].isYaxis);
    EXPECT_NEAR(roots[0].time, 0.5, 0.0001);
}

TEST(AABB, rootExtremeCase1) {
    Bezier curve = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({-0.5, -0.5}),
        Coord({0.0, -0.5}),
        Coord({11651561651565156156165156.0, 187841648154516587161.0}),
    }));

    double nbPointsLUT = 2 * curve.degree(); // comme la fréquence d'echantillonage

    auto lut    = computeLUT(curve, nbPointsLUT);
    auto roots  = rootsFromLUT(curve, lut, 0.00000001);
    auto convex = convexBoundingBox(curve);
    EXPECT_GE(roots.size(), 1);

    auto inAABB = casteljau(curve, 1000000);

    for (int i = 0; i < inAABB.size(); i++) {

        EXPECT_TRUE(isPointInAABB(convex, inAABB[i]));
    }
}

TEST(AABB, rootExtremeCaseLikeABully) {
    std::mt19937                     generator;
    std::uniform_real_distribution<> distribution(0, 1);
    int                              cptNotFound = 0;
    int                              cpt         = 0;

    for (uint_fast16_t i = 3; i < 5; i++) {
        printf(" a \n");
        for (uint_fast16_t j = 0; j < 50; ++j) {
            auto   controlPoint = randomPoints(i, 256, 256);
            Bezier curve        = Bezier(controlPoint);
            double nbPointsLUT  = 2 * curve.degree(); // comme la fréquence d'echantillonage

            auto lut    = computeLUT(curve, nbPointsLUT);
            auto roots  = rootsFromLUT(curve, lut, 0.00000001);
            auto convex = convexBoundingBox(curve);
            auto inAABB = casteljau(curve, 1000000);

            for (int i = 0; i < inAABB.size(); i++) {
                ASSERT_TRUE(isPointInAABB(convex, inAABB[i]));
            }
        }
    }
}
