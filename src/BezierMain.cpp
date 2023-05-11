#include "Bezier/Bezier.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/BoundingBox.h"
#include "IO/Dump.h"

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

int main(int, char**) {
    

    //  const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;

    {
        auto   timer = Timer{"test timer: "};
        Bezier bez   = Bezier(std::vector<Coord>({
            Coord({0.0, 1.0}),
            Coord({-1.0, -1.0}),
            Coord({-1.0, -2.0}),
            Coord({0.0, -3.0}),
        }));
        // Bezier bez = Bezier(std::vector<Coord>({
        //     Coord({197.0, 90.0}),
        //     Coord({52.0, 133.0}),
        //     Coord({50.0, 43.0}),
        //     Coord({213.0, 116.0}),

        // }));

        // Bezier bez = Bezier(randomPoints(10, 250, 250));
        Segment X       = Segment({Coord({-1000.0, 0.0}), Coord({1000.0, 0.0})});
        auto    vec     = rayBoundingBoxMethod(bez, X, 100);
        Buffer  bezBuff = createBuffer(bez.degree);
        for (int i = 0; i < vec.size() ; i++) {
            std::cout << i << " proposition, time = " << vec[i];
        }

        // Segment A       = Segment({Coord({0.0, 0.0}), Coord({1.0, 1.0})});
        // Segment Aprim   = Segment({Coord({1.0, 1.0}), Coord({2.0, 2.0})});
        // Segment B       = Segment({Coord({0.0, 1.0}), Coord({1.0, 0.0})});
        // auto curve = casteljau(bez,1000);
        // // std::vector<Coord> tmp = convexBoundingBox(bez);

        // auto                 hull = AABBtoQuad(convexBoundingBox(bez));
        // std::vector<Segment> segs;

        // segs.push_back(Segment({hull[0], hull[hull.size() - 1]}));

        // writeSegmentsVTK(segs,"BoundingbBox.vtk");
        // writeLinesVTK(curve,"curve.vtk");
        // writePointsVTK(bez.controlPoint,"control_points.vtk");
        // std::vector<Coord> roo;

        // for (int i = 0; i <bez.roots.size() ; i++) {
        //     roo.push_back(evalCasteljau(bez,bez.roots[i].time,bezBuff));
        // }
        // writePointsVTK(roo,"roots.vtk");
    }
}