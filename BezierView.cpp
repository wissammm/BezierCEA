#include "Bezier.h"
#include "Dump.h"
#include "View.h"
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <array>
#include <filesystem>

std::filesystem::path getResultPath() { return std::filesystem::u8path(RESULT_DIR); }

int main(int, char**) {
    std::cout << "Bienvenue dans la petite IHM\n";

    const auto points = randomPoint(6, 50, 50);

    Bezier curve_castel;
    int    nb_points_on_curve = 60;

    View  view;
    view.createWindow(400,600);

}