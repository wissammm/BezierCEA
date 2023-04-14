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

    View  view;
    view.createWindow();

}