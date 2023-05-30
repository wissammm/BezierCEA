#include "Bezier/Bezier.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierCurveCurveIntersection.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BezierDerivate.h"
#include "Bezier/BoundingBox.h"
#include "Bezier/PointOnCurve.h"
#include "IO/Dump.h"
#include <optional>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <array>
#include <filesystem>

std::filesystem::path getResultPath() { return std::filesystem::u8path(RESULT_DIR); }

class Timer
{
  public:
    Timer(std::string message) : message(std::move(message)), tStart(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        const auto tEnd     = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration<double, std::milli>(tEnd - tStart).count();
        std::cout << message << duration << std::endl;
    }

  private:
    std::string                                    message;
    std::chrono::high_resolution_clock::time_point tStart;
};

struct BezierPerf
{
    std::vector<Bezier>  beziers;
    std::vector<Segment> ray;
};

BezierPerf createPerfModel() {
    BezierPerf perf;
    for (size_t i = 0; i < 500; ++i) {
        auto   controlPoint = randomPoints(5, 256, 256);
        Bezier curve        = Bezier(controlPoint);
        perf.beziers.push_back(curve);
    }
    for (size_t i = 0; i < 100; ++i) {
        auto point1 = randomPoint(256, 256);
        auto point2 = randomPoint(256, 256);
        perf.ray.push_back(Segment({point1, point2}));
    }
    return perf;
}

void evaluatePerf() {
    auto perf = createPerfModel();
    {
        auto timer = Timer{"AABB without avoid doublons: "};
        for (int i = 0; i < perf.beziers.size(); ++i) {

            for (int j = 0; j < perf.ray.size(); ++j) {

                intersectionRayBezier(perf.beziers[i], perf.ray[j],
                                      {
                                          .mode                  = BOUNDING_BOX,
                                          .evaluateCoordOnBezier = true,
                                          .isSegment             = false,
                                          .avoidDoublons         = false,
                                          .newtonOptions         = {.epsilon = 0.001},
                                          .aabbOptions           = {.epsilon = 0.001, .maxDepth = 10}
                });
            }
        }
    }
    {
        auto timer = Timer{"AABB with simple BoundingBox: "};
        for (int i = 0; i < perf.beziers.size(); ++i) {
            for (int j = 0; j < perf.ray.size(); ++j) {
                intersectionRayBezier(
                    perf.beziers[i], perf.ray[j],
                    {
                        .mode                  = BOUNDING_BOX,
                        .evaluateCoordOnBezier = true,
                        .isSegment             = false,
                        .avoidDoublons         = false,
                        .newtonOptions         = {.epsilon = 0.001},
                        .aabbOptions           = {.useSimpleBoundingBox = false, .epsilon = 0.001, .maxDepth = 10}
                });
            }
        }
    }
    {
        auto timer = Timer{"AABB with avoid doublons: "};
        for (int i = 0; i < perf.beziers.size(); ++i) {
            for (int j = 0; j < perf.ray.size(); ++j) {
                intersectionRayBezier(
                    perf.beziers[i], perf.ray[j],
                    {
                        .mode                  = BOUNDING_BOX,
                        .evaluateCoordOnBezier = true,
                        .isSegment             = false,
                        .avoidDoublons         = true,
                        .epsilonDoublons       = 0.001,
                        .newtonOptions         = {.epsilon = 0.001},
                        .aabbOptions           = {.useSimpleBoundingBox = false, .epsilon = 0.001, .maxDepth = 10}
                });
            }
        }
    }

    {
        auto timer = Timer{"NAIVE with avoid doublons: "};
        for (int i = 0; i < perf.beziers.size(); ++i) {
            for (int j = 0; j < perf.ray.size(); ++j) {
                intersectionRayBezier(perf.beziers[i], perf.ray[j],
                                      {
                                          .mode                  = NAIVE,
                                          .evaluateCoordOnBezier = true,
                                          .isSegment             = false,
                                          .avoidDoublons         = true,
                                          .epsilonDoublons       = 0.001,
                                          .newtonOptions         = {.epsilon = 0.001},
                                          .naiveOptions = {.useSimpleBoundingBox = false, .nbPointsOnCurve = 1000}
                });
            }
        }
    }
    {
        auto timer = Timer{"NAIVE without avoid doublons: "};
        for (int i = 0; i < perf.beziers.size(); ++i) {
            for (int j = 0; j < perf.ray.size(); ++j) {
                intersectionRayBezier(perf.beziers[i], perf.ray[j],
                                      {
                                          .mode                  = NAIVE,
                                          .evaluateCoordOnBezier = true,
                                          .isSegment             = false,
                                          .avoidDoublons         = false,
                                          .newtonOptions         = {.epsilon = 0.001},
                                          .naiveOptions = {.useSimpleBoundingBox = false, .nbPointsOnCurve = 1000}
                });
            }
        }
    }
}

int main(int, char**) {

    //  const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;

    {
        auto   timer = Timer{"test timer: "};
        Bezier bez1  = Bezier(std::vector<Coord>({
            Coord({0.0, 1.0}),
            Coord({-1.0, 0.0}),
            Coord({-1.0, -1.0}),
            Coord({0.0, -2.0}),
        }));
        Bezier bez2  = Bezier(std::vector<Coord>({
            Coord({-1.0, 0.0}),
            Coord({0.0, 0.70}),
            Coord({1.0, -1.0}),
            Coord({2.0, 0.0}),
        }));

        Segment X    = Segment({Coord({-10.0, 0.0000000001}), Coord({5.0, 0.00000000001})});
        Segment Xinv = Segment({Coord({5.0, -0.523001}), Coord({-10.0, -0.500789000001})});
        auto    buf  = createBuffer(bez1.degree());
        auto    p    = getNearestPointOnCurve(bez1, Coord({0, -2.0}), 5);

        std::cout << " point x:" << p.coord.x << " y : " << p.coord.y << " at time : " << p.time << std::endl
                  << "eval castel at time : "
                  << " point x:" << evalCasteljau(bez1, p.time, buf).x << " y : " << evalCasteljau(bez1, p.time, buf).y
                  << std::endl;
    }
    // LikeABullyAABBNewton();
    // evaluatePerf();
}
