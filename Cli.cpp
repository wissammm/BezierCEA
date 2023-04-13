#include "Bezier.h"
#include "Coord.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

int id = 0;

using Selection = std::vector<std::string>;

Selection random = Selection({
    "Aléatoire",
    "Pas Aléatoire",
});

void printSelection(std::vector<std::string>& selection) {
    for (int i = 0; i < selection.size(); ++i) {
        std::cout << i + 1 << " : " << selection[i] << std::endl;
    }
}
