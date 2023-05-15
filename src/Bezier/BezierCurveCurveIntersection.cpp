#include "BezierCurveCurveIntersection.h"
#include <vector>
#include <stack>
#include "Bezier.h"
#include "BezierDecompose.h"
#include "BoundingBox.h"
#include "Geometry/Segment.h"
#define EPSILON_ANGLE 0.00000001

struct BezierWithInitialTime
{
    Bezier bez;
    double tBegin;
    double tEnd;
};

std::vector<double> curveCurveBoundingBoxMethod(Bezier bez1, Bezier bez2, size_t nb_max_iter) {

    size_t nb_iter = 0;

    std::stack<BezierWithInitialTime> callStackBez1;
    std::stack<BezierWithInitialTime> callStackBez2;

    std::vector<double> timesFoundInterpolate;
    while (nb_iter < nb_max_iter && callStackBez1.size() > 0) {
        BezierWithInitialTime actualBez1 = callStackBez1.top();
        auto                  aabbBez1   = convexBoundingBox(actualBez1.bez);
        callStackBez1.pop();

        while (nb_iter < nb_max_iter && callStackBez2.size() > 0) {

            BezierWithInitialTime actualBez2 = callStackBez2.top();
            auto                  aabbBez2   = convexBoundingBox(actualBez2.bez);
            callStackBez2.pop();

            if (isAABBintersectAABB(aabbBez1, aabbBez2)) {
                //TODO change condition 
                if (0 < EPSILON_ANGLE) {
                    timesFoundInterpolate.push_back(actualBez1.tBegin + (actualBez1.tEnd - actualBez1.tBegin) / 2.0);
                } else {
                    auto   decomposeBez = decompose(actualBez1.bez, 0.5);
                    double middle       = actualBez1.tBegin + (actualBez1.tEnd - actualBez1.tBegin) / 2.0;
                    callStackBez1.push(BezierWithInitialTime({decomposeBez[0], actualBez1.tBegin, middle}));
                    callStackBez1.push(BezierWithInitialTime({decomposeBez[1], middle, actualBez1.tEnd}));

                    decomposeBez = decompose(actualBez2.bez, 0.5);
                    middle       = actualBez2.tBegin + (actualBez2.tEnd - actualBez2.tBegin) / 2.0;
                    callStackBez2.push(BezierWithInitialTime({decomposeBez[0], actualBez2.tBegin, middle}));
                    callStackBez2.push(BezierWithInitialTime({decomposeBez[1], middle, actualBez2.tEnd}));
                }
            }
        }
    }

    return timesFoundInterpolate;
}
