#include "Bezier/Bezier.h"
#include "Geometry/Coord.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

int id = 0;

using Selection = std::vector<std::string>;

void printSelection(std::vector<std::string>& selection) {
    for (int i = 0; i < selection.size(); ++i) {
        std::cout << i + 1 << " : " << selection[i] << std::endl;
    }
}
