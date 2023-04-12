#include "Bezier.h"
#include "Dump.h"
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <array>
#include <filesystem>

std::filesystem::path getResultPath() { return std::filesystem::u8path(RESULT_DIR); }

int main(int, char**) {
    std::cout << "Hello, world!\n";

    const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    Bezier curve_bez;
    int    nb_points_on_curve = 60;


    {
    
        Bezier curve_castel_normal;
        Bezier curve_castel_minus_1;
        Bezier curve_castel_plus_1;
        Bezier curve_castel_plus_minus_1;

        const auto pointsMinus1     = lower(points); 
        const auto pointsPlus1      = elevate(points);
        const auto pointsPlusMinus1 = lower(pointsPlus1);
        curve_castel_normal         = casteljau(points, nb_points_on_curve);
        curve_castel_minus_1        = casteljau(pointsMinus1, nb_points_on_curve);
        curve_castel_plus_1         = casteljau(pointsPlus1, nb_points_on_curve);
        curve_castel_plus_minus_1   = casteljau(pointsPlusMinus1, nb_points_on_curve);

        create_directories(getResultPath());
        writeLinesVTK(points, getResultPath() / "lines.vtk");
        writeLinesVTK(pointsMinus1, getResultPath() / "linesMinus1.vtk");
        writeLinesVTK(pointsPlus1, getResultPath() / "linesPlus1.vtk");
        writeLinesVTK(pointsPlusMinus1, getResultPath() / "linesPlusMinus1.vtk");
        writeLinesVTK(curve_castel_normal, getResultPath() / "curve.vtk");
        writeLinesVTK(curve_castel_minus_1, getResultPath() / "curve_minus_1.vtk");
        writeLinesVTK(curve_castel_plus_1, getResultPath() / "curve_plus_1.vtk");
        writeLinesVTK(curve_castel_plus_minus_1, getResultPath() / "curve_plus_minus_1.vtk");
    }
}