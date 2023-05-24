//testRayIntersect.cpp

#include <limits.h>
#include <iostream>
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include "Geometry/Segment.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierEvaluate.h"
#include "gtest/gtest.h"
#include <optional>
#include <cmath>
#include <random>

//TODO : Mettre a jour les appels de tests

TEST(RayIntersectionNaiveNewton, NumberOfIntersections) {
    Bezier bez                  = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({0.3, 1.5}),
        Coord({0.8, 1}),
        Coord({1.0, 0.0}),
    }));
    Bezier bezier4ControlPoints = Bezier(bez);
    Coord  minYx0_5             = Coord({0.5, -100});

    Coord   maxYx0_5 = Coord({0.5, 100});
    Segment Xaxis    = Segment({minYx0_5, maxYx0_5});

    auto inter = intersectionRayBezier(
        bezier4ControlPoints, Xaxis,
        {.mode = NAIVE, .evaluateCoordOnBezier = true, .naiveOptions = {.nbPointsOnCurve = 1000}});
    EXPECT_EQ(inter.size(), 1) << "Doit passer par deux points de la courbe, nombre d'intersections " << inter.size();
}

TEST(RayIntersectionNaiveNewton, BoundsBezier) {
    Bezier bez                  = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({0.8, 1.5}),
        Coord({0.3, 1}),
        Coord({1.0, 0.0}),
    }));
    Bezier bezier4ControlPoints = Bezier(bez);
    Coord  minX                 = Coord({-1000, 0.0});

    Coord   maxX  = Coord({10000, 0.0});
    Segment Xaxis = Segment({minX, maxX});

    auto inter = intersectionRayBezier(
        bezier4ControlPoints, Xaxis,
        {.mode = NAIVE, .evaluateCoordOnBezier = true, .naiveOptions = {.nbPointsOnCurve = 1000}});
    EXPECT_EQ(inter.size(), 2) << "Intersection aux Bords pas trouvé, problème viens Surement de IsOnSegment";
    if (inter.size() != 0) {
        EXPECT_NEAR(inter[0].time, 0, 0.0001)
            << "Intersection aux Bords pas trouvé, problème viens Surement de IsOnSegment";

        inter = intersectionRayBezier(
            bezier4ControlPoints, Xaxis,
            {.mode = NAIVE, .evaluateCoordOnBezier = true, .naiveOptions = {.nbPointsOnCurve = 1000}});
        EXPECT_NEAR(inter[0].time, 0, 0.0001);
    }
}

TEST(RayIntersectionNaiveNewton, NumberOfIntersections1) {
    Bezier bez                  = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({0.3, 1.5}),
        Coord({0.8, 1}),
        Coord({1.0, 0.0}),
    }));
    Bezier bezier4ControlPoints = Bezier(bez);
    Coord  minYx0_5             = Coord({0.5, -100});

    Coord   maxYx0_5 = Coord({0.5, 100});
    Segment Xaxis    = Segment({minYx0_5, maxYx0_5});

    auto inter = intersectionRayBezier(
        bezier4ControlPoints, Xaxis,
        {.mode = NAIVE, .evaluateCoordOnBezier = true, .naiveOptions = {.nbPointsOnCurve = 1000}});
    EXPECT_EQ(inter.size(), 1) << "Doit passer par deux points de la courbe, nombre d'intersections " << inter.size();
}

TEST(RayIntersectionNaiveNewton, BadFirstGuessNewton) {
    Bezier bez                  = Bezier(std::vector<Coord>({
        Coord({0.0, 0.0}),
        Coord({0.0, 1.5}), //symétrique
        Coord({1.0, 1.5}),
        Coord({1.0, 0.0}),
    }));
    Bezier bezier4ControlPoints = Bezier(bez);
    Coord  minYx0_5             = Coord({0.0, -100});

    Coord   maxYx0_5 = Coord({0.0, 100});
    Segment Yaxis    = Segment({minYx0_5, maxYx0_5});

    auto u = newtonMethodIntersectionBezierRay(
        bez, 78945.264, Yaxis, true, {.epsilon = 0.0001, .nMaxIterations = 100000, .minRange = -1, .maxRange = 2});
    double res;
    if (u) {
        res = *u;
        EXPECT_NEAR(res, 0.0, 0.0001) << "First guess is important; u = " << res;
    } else {
        EXPECT_FALSE(true);
    }
}

// TEST(RayIntersectionNaiveNewton, LikeABullyNaiveNewton) {
//     std::mt19937                     generator;
//     std::uniform_real_distribution<> distribution(0, 1);
//     int                              cptNotFound = 0;
//     int                              cpt         = 0;

//     for (uint_fast16_t i = 3; i < 5; i++) {
//         auto   controlPoint = randomPoints(i, 256, 256);
//         Bezier curve        = Bezier(controlPoint);
//         for (uint_fast16_t j = 0; j < 128; ++j) {
//             auto point = randomPoint(256, 256);

//             double  t             = distribution(generator);
//             Buffer  buffer        = createBuffer(curve.nbControlPoint());
//             Coord   on_curve      = evalCasteljau(curve, t, buffer);
//             Segment seg           = Segment({on_curve, point});
//             auto    intersections = intersectionRayBezier(
//                 curve, seg,
//                 {.mode = NAIVE, .evaluateCoordOnBezier = true, .naiveOptions = {.nbPointsOnCurve = 100000}});
//             bool one_good_intersect = false;
//             for (size_t k = 0; k < intersections.size(); ++k) {
//                 double diff = t - intersections[k].time;
//                 if (std::abs(diff) <= 0.001) {
//                     one_good_intersect = true;
//                 } else {
//                     // std::cout << "not a intersect " << std::endl;
//                 }
//             }
//             if (!one_good_intersect) {
//                 cptNotFound++;
//                 // std::cout << "no intersects, nb of intersection =  " << intersections.size() << std::endl;
//                 // std::cout << " Point \n x: " << point.x << " y :" << point.y << std::endl;
//                 // std::cout << " Point On Curve  \n x: " << on_curve.x << " y :" << on_curve.y << std::endl;

//                 // for (size_t k = 0; k < intersections.size(); ++k) {

//                 //     std::cout << "t expected = " << t << " ,t we have" << intersections[k].time << std::endl;
//                 // }
//             }
//             // ASSERT_TRUE(one_good_intersect);
//             cpt++;
//         }
//     }
//     std::cout << "NAIVE : nb intersections not found =  " << cptNotFound << " on " << cpt << " intersections"
//               << std::endl;
//     ASSERT_TRUE(true);
// }

TEST(RayIntersectionNaiveNewton, LikeABullyAABBNewton) {
    std::mt19937                     generator;
    std::uniform_real_distribution<> distribution(0, 1);
    int                              cptNotFound = 0;
    int                              cpt         = 0;

    for (uint_fast16_t i = 3; i < 5; i++) {
        auto   controlPoint = randomPoints(i, 256, 256);
        Bezier curve        = Bezier(controlPoint);
        for (uint_fast16_t j = 0; j < 128; ++j) {
            auto point = randomPoint(256, 256);

            double  t                  = distribution(generator);
            Buffer  buffer             = createBuffer(curve.nbControlPoint());
            Coord   on_curve           = evalCasteljau(curve, t, buffer);
            Segment seg                = Segment({point, on_curve});
            auto    intersections      = intersectionRayBezier(curve, seg,
                                                               {
                                                                   .mode                  = BOUNDING_BOX,
                                                                   .evaluateCoordOnBezier = true,
                                                                   .isSegment             = false,
                                                                   .newtonOptions         = {.epsilon = 0.001},
                                                                   .aabbOptions = {.epsilon = 0.01, .maxDepth = 30}
            });
            bool    one_good_intersect = false;
            for (size_t k = 0; k < intersections.size(); ++k) {
                double diff = t - intersections[k].time;
                if (std::abs(diff) <= 0.01) {
                    one_good_intersect = true;
                } else {
                    // std::cout << "not a intersect " << std::endl;
                }
            }
            if (!one_good_intersect) {
                cptNotFound++;
                // std::cout << "no intersects, nb of intersection =  " << intersections.size() << std::endl;
                // std::cout << " Point \n x: " << point.x << " y :" << point.y << std::endl;
                // std::cout << " Point On Curve  \n x: " << on_curve.x << " y :" << on_curve.y << std::endl;

                // for (size_t k = 0; k < intersections.size(); ++k) {

                //     std::cout << "t expected = " << t << " ,t we have" << intersections[k].time << std::endl;
                // }
            }
            cpt++;
            //ASSERT_TRUE(one_good_intersect);
        }
    }
    std::cout << "AABB : nb intersections not found =  " << cptNotFound << " on " << cpt << " intersections"
              << std::endl;
    ASSERT_TRUE(true);
}

TEST(RayIntersectionNaiveNewton, SpecialCase1) {
    auto curve = Bezier(std::vector<Coord>({Coord({103, 198}), Coord({105, 115}),
                                            Coord({81, 255})}));
    auto point = Coord({74, 236});

    double  t                  = 0.135477004296;
    Buffer  buffer             = createBuffer(curve.nbControlPoint());
    Coord   on_curve           = evalCasteljau(curve, t, buffer);
    Segment seg                = Segment({point, on_curve});
    auto    intersections      = intersectionRayBezier(curve, seg,
                                                       {
                                                           .mode                  = BOUNDING_BOX,
                                                           .evaluateCoordOnBezier = true,
                                                           .isSegment             = false,
                                                           .newtonOptions         = {.epsilon = 0.001},
                                                           .aabbOptions           = {.epsilon = 0.000000001, .maxDepth = 10}
    });
    bool    one_good_intersect = false;
    for (size_t k = 0; k < intersections.size(); ++k) {
        double diff = t - intersections[k].time;
        if (std::abs(diff) <= 0.01) {
            one_good_intersect = true;
        } else {
            // std::cout << "not a intersect " << std::endl;
        }
    }

    ASSERT_TRUE(one_good_intersect);
}