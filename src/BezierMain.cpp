#include "Bezier/Bezier.h"
#include "Bezier/BezierRayIntersection.h"
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

    const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;

    {
        auto    timer = Timer{"test timer: "};
        Bezier  bez   = Bezier({
            Coord({1.0, 7.0}),
            Coord({8.0, -12.0}),
            Coord({11.0, -23.0}),
        });
        Segment A     = Segment({Coord({0.0, 0.0}), Coord({100.0, 0.0})});
        auto    naive = intersectionNaive(bez, A);

        std::cout << "Intesect naive \n x: " << naive[0].x << " y :" << naive[0].y << std::endl;

        auto newton = intersectionNewtonMethod(bez,A,0.1);

        // std::cout << "Intesect newton \n x: " << newton[0].x << " y :"<<newton[0].y <<std::endl;
    }
}
