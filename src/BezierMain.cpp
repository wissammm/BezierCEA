#include "Bezier/Bezier.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierEvaluate.h"
#include "Bezier/Hull.h"
#include "IO/Dump.h"
#include "Bezier/Hull.h"
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
    std::cout << "Hello, world!\n";

    //  const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;

    {
        auto timer = Timer{"test timer: "};
        // Bezier  bez     = Bezier(std::vector<Coord>({
        //     Coord({0.0, 1.0}),
        //     Coord({-1.0, -1.0}),
        //     Coord({-1.0, -2.0}),
        //     Coord({0.0, -3.0}),

        // }));
        Bezier bez = Bezier(std::vector<Coord>({
            Coord({197.0, 90.0}),
            Coord({52.0, 133.0}),
            Coord({50.0, 43.0}),
            Coord({213.0, 116.0}),

        }));

        Buffer  bezBuff = createBuffer(bez.degree);
        Segment X       = Segment({Coord({-1000.0, 0.0}), Coord({1000.0, 0.0})});
        Segment A       = Segment({Coord({0.0, 0.0}), Coord({1.0, 1.0})});
        Segment Aprim   = Segment({Coord({1.0, 1.0}), Coord({2.0, 2.0})});
        Segment B       = Segment({Coord({0.0, 1.0}), Coord({1.0, 0.0})});

        std::vector<Coord> tmp = convexHull(bez);

        auto hull = convexHull(bez);

        for (Root r : bez.roots) {
            if (r.isYaxis) {
                std::cout << "Root y axis : time t =" << r.time << " x= " << evalCasteljau(bez, r.time, bezBuff).x
                          << " y = " << evalCasteljau(bez, r.time, bezBuff).y << std::endl;
            } else {
                std::cout << "Root x axis : time t =" << r.time << " x= " << evalCasteljau(bez, r.time, bezBuff).x
                          << " y = " << evalCasteljau(bez, r.time, bezBuff).y << std::endl;
            }
        }
        // // if (doIntersect(A.a, A.b, Aprim.a, Aprim.b)) { //DOINTERSECT ne marche pas
        // //     std::cout << " A x B ; x= " << lineLineIntersection(Aprim, A).x
        // //               << " y : " << lineLineIntersection(Aprim, A).y << std::endl;
        // // }
        // // auto naive = intersectionNaive(bez, X, 6);
        // // std::cout << "Naiv ssize  = " << naive.size() << std::endl;
        // // std::cout << " Intesect naive \n x: " << naive[0].inter.x << " y :" << naive[0].inter.y << std::endl;

        // auto newton = intersectionNewtonMethod(bez,X,0.000001);

        // std::cout << " Intesect newton \n x: " << newton[0].inter.x << " y :" << newton[0].inter.y << std::endl;
    }
}
