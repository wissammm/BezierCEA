#pragma once
#include <random>

struct Color
{
    int  r, g, b;
    Color(int rnew, int gnew, int bnew){
        r = rnew;
        g = gnew;
        b = bnew;
    };
    void changeColor(int rnew, int gnew, int bnew) {
        r = rnew;
        g = gnew;
        b = bnew;
    };
    void randomColor() {
        r = rand() %255;
        g = rand() %255;
        b = rand() %255;
    };

};
