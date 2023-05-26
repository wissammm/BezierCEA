#include "PointOnCurve.h"
#include "Geometry/Coord.h"
#include "Geometry/Segment.h"
#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDecompose.h"
#include <limits>

CoordTime getNearestPointOnCurve(Bezier bez, Coord p, size_t nbIter) {
    auto                  lut     = computeLUT(bez, bez.nbControlPoint());
    auto                  minDist = std::numeric_limits<double>::max();
    BezierWithInitialTime part    = BezierWithInitialTime({bez, 0, 1});
    size_t                lutMinDist;
    std::vector<double>   tmpDist(lut.size());
    for (size_t n = 0; n < nbIter; ++n) {

        for (size_t i = 0; i < lut.size(); ++i) {
            tmpDist[i] = distance(lut[i].coord, p);
            if (tmpDist[i] < minDist) {
                lutMinDist = i;
                minDist    = tmpDist[i];
            }
        }
        if (lutMinDist == 0) {
            part = BezierWithInitialTime(        //
                {decompose(bez, lut[1].time)[0], //
                 part.tBegin,                    //
                 part.tBegin + lut[1].time * (part.tEnd - part.tBegin)});
        } else if (lutMinDist == bez.nbControlPoint() - 1) {
            part = BezierWithInitialTime(                                                      //
                {decompose(bez, lut[bez.nbControlPoint() - 2].time)[1],                        //
                 part.tBegin + lut[bez.nbControlPoint() - 2].time * (part.tEnd - part.tBegin), //
                 part.tEnd});
        } else {
            if (tmpDist[lutMinDist-1]<tmpDist[lutMinDist+1]) {
                auto tmpEnd = part.tBegin + lut[1].time * (part.tEnd - part.tBegin);
                part = BezierWithInitialTime(                                                      //
                {decompose(bez, lut[lutMinDist-1].time)[0],                        //
                 part.tBegin + lut[lutMinDist-1].time * (part.tEnd - part.tBegin), //
                 part.tEnd});
            } else {
            }
        }
    }
}