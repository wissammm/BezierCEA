#include "Bezier/Bezier.h"
#include "Bezier/BezierRayIntersection.h"
#include "Bezier/BezierEvaluate.h"
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
    std::cout << "Hello, world!\n";

    //  const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;

    {
        auto    timer = Timer{"test timer: "};
        Curve   bez   = Curve(Bezier({
            Coord({1.0, 7.0}),
            Coord({8.0, -12.0}),
            Coord({11.0, -23.0}),
            Coord({11.0, -24.0}),
        }));
        Segment X     = Segment({Coord({-1000.0, 0.0}), Coord({1000.0, 0.0})});
        Segment A     = Segment({Coord({0.0, 0.0}), Coord({1.0, 1.0})});
        Segment Aprim = Segment({Coord({1.0, 1.0}), Coord({2.0, 2.0})});
        Segment B     = Segment({Coord({0.0, 1.0}), Coord({1.0, 0.0})});

        if (doIntersect(A.a, A.b, Aprim.a, Aprim.b)) {
            std::cout << " A x B ; x= " << lineLineIntersection(Aprim, A).x
                      << " y : " << lineLineIntersection(Aprim, A).y << std::endl;
        }
        auto naive = intersectionNaive(bez, X, 6);
        std::cout << "Naiv ssize  = " << naive.size() << std::endl;
        std::cout << " Intesect naive \n x: " << naive[0].inter.x << " y :" << naive[0].inter.y << std::endl;
        // Buffer bufferCurve = createBuffer(bez.degree);
        // auto   newton      = evalCasteljau( bez, newtonMethod(bez, 0.5, X, 0.01), bufferCurve);

        // std::cout << " Intesect newton \n x: " << newton.x << " y :" << newton.y << std::endl;
    }
}
