
#include <iostream>
#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include "Geometry/Newton.h"
#include "Geometry/Segment.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/PointOnCurve.h"
#include "gtest/gtest.h"
#include <optional>
#include <cmath>
#include <random>

//TODO : Mettre a jour les appels de tests

TEST(PointOnCurve, simplePointOnCurve) {
           Bezier bez1  = Bezier(std::vector<Coord>({
            Coord({0.0, 1.0}),
            Coord({-1.0, 0.0}),
            Coord({-1.0, -1.0}),
            Coord({0.0, -2.0}),
        }));
        

        auto    buf      = createBuffer(bez1.degree());
        auto    pOnCurve = Coord({-1.0, -1.0});
        auto    p        = getNearestPointOnCurve(bez1, pOnCurve, 8);
        
        EXPECT_NEAR(distance(p.coord,pOnCurve), 0, 0.1);

}
