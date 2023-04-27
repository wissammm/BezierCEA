//testRayIntersect.cpp

#include <limits.h>
#include <iostream>
#include "../src/Bezier/Bezier.h"
#include "../src/Geometry/Coord.h"
#include "../src/Geometry/Segment.h"
#include "../src/Bezier/BezierRayIntersection.h"
#include "../src/Bezier/BezierEvaluate.h"
#include "gtest/gtest.h"
#include <cmath>
#include <random>

TEST(RayIntersectionNaiveNewton, NumberOfIntersections) {
    Curve bez                  = Curve(Bezier({
        Coord({0.0, 0.0}),
        Coord({0.3, 1.5}),
        Coord({0.8, 1}),
        Coord({1.0, 0.0}),
    }));
    Curve bezier4ControlPoints = Curve(bez);
    Coord minYx0_5             = Coord({0.5, -100});

    Coord   maxYx0_5 = Coord({0.5, 100});
    Segment Xaxis    = Segment({minYx0_5, maxYx0_5});

    auto inter = intersectionNaive(bezier4ControlPoints, Xaxis, 100000);
    EXPECT_EQ(inter.size(), 1) << "Doit passer par deux points de la courbe, nombre d'intersections " << inter.size();
}

TEST(RayIntersectionNaiveNewton, BoundsCurve) {
    Curve bez                  = Curve(Bezier({
        Coord({0.0, 0.0}),
        Coord({0.8, 1.5}),
        Coord({0.3, 1}),
        Coord({1.0, 0.0}),
    }));
    Curve bezier4ControlPoints = Curve(bez);
    Coord minX                 = Coord({-1000, 0.0});

    Coord   maxX  = Coord({10000, 0.0});
    Segment Xaxis = Segment({minX, maxX});

    auto inter = intersectionNaive(bezier4ControlPoints, Xaxis, 1000);
    EXPECT_EQ(inter.size(), 2) << "Intersection aux Bords pas trouvé, problème viens Surement de IsOnSegment";
    if (inter.size() != 0) {
        EXPECT_NEAR(inter[0].time, 0, 0.0001)
            << "Intersection aux Bords pas trouvé, problème viens Surement de IsOnSegment";

        inter = intersectionNewtonMethod(bezier4ControlPoints, Xaxis, 1e-5);

        EXPECT_NEAR(inter[0].time, 0, 0.0001);
    }
}

TEST(RayIntersectionNaiveNewton, NumberOfIntersections1) {
    Curve bez                  = Curve(Bezier({
        Coord({0.0, 0.0}),
        Coord({0.3, 1.5}),
        Coord({0.8, 1}),
        Coord({1.0, 0.0}),
    }));
    Curve bezier4ControlPoints = Curve(bez);
    Coord minYx0_5             = Coord({0.5, -100});

    Coord   maxYx0_5 = Coord({0.5, 100});
    Segment Xaxis    = Segment({minYx0_5, maxYx0_5});

    auto inter = intersectionNaive(bezier4ControlPoints, Xaxis, 100000);
    EXPECT_EQ(inter.size(), 1) << "Doit passer par deux points de la courbe, nombre d'intersections " << inter.size();
}

TEST(RayIntersectionNaiveNewton, BadFirstGuessNewton) {
    Curve bez                  = Curve(Bezier({
        Coord({0.0, 0.0}),
        Coord({0.0, 1.5}), //symétrique
        Coord({1.0, 1.5}),
        Coord({1.0, 0.0}),
    }));
    Curve bezier4ControlPoints = Curve(bez);
    Coord minYx0_5             = Coord({0.0, -100});

    Coord   maxYx0_5 = Coord({0.0, 100});
    Segment Yaxis    = Segment({minYx0_5, maxYx0_5});

    double u = newtonMethod(bez, 78945.264, Yaxis, 0.000001);

    EXPECT_NEAR(u, 0.0, 0.0001) << "First guess is important; u = " << u;
}

TEST(RayIntersectionNaiveNewton, LikeABully) {
    std::mt19937                     generator;
    std::uniform_real_distribution<> distribution(0, 1);

    for (uint_fast16_t i = 3; i < 5; i++) {
        auto curve = randomPoint(i, 256, 256);
        for (uint_fast16_t j = 0; j < 128; ++j) {
            auto    points             = randomPoint(1, 256, 256);
            auto point = points.controlPoint[0];
            double  t                  = distribution(generator);
            Buffer  buffer             = createBuffer(curve.nbControlPoint);
            Coord   on_curve           = evalCasteljau(curve, t, buffer);
            Segment seg                = Segment({on_curve, point});
            auto    intersections      = intersectionNewtonMethod(curve, seg, 0.00000001);
            bool    one_good_intersect = false;
            for (size_t k = 0; k < intersections.size(); ++k) {
                if (std::abs(intersections[i].time - t) < 0.1) {
                    one_good_intersect = true;
                } else {
                    std::cout << "not a intersect " << std::endl;
                }
            }
            if (!one_good_intersect) {
                std::cout << "no intersects, nb of intersection =  "<< intersections.size() << std::endl;
                std::cout << " Point \n x: " << point.x << " y :" << point.y << std::endl;
                std::cout << " Point On Curve  \n x: " << on_curve.x << " y :" << on_curve.y << std::endl;

                for (size_t k = 0; k < intersections.size(); ++k) {

                    std::cout << "t expected = "<< t<<" ,t we have"<<intersections[k].time << std::endl;
                }
            }
            ASSERT_TRUE(one_good_intersect);
        }
    }
}
