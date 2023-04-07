#pragma once
#include <SDL2/SDL.h>
#include "Coord.h"

struct Color{
    int r,g,b;
};

struct View{
    public :
        Color color = Color({0,255,255});
        SDL_Window *window;


        int createWindow(int h, int w);
        void drawLine(Segment segment);
        void drawLines()
        void changeColor(int r, int g, int b);

    private:


};