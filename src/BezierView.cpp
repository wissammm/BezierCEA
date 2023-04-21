#include "Bezier/Bezier.h"
#include "IO/Dump.h"
#include "View/View.h"
#include <vector>
#include <string>
#include <ctime>



std::filesystem::path getResultPath() { return std::filesystem::u8path(RESULT_DIR); }

int main(int, char**) {
    std::cout << "Bienvenue dans la petite IHM\n";

    View  view;
    view.createWindow();

}