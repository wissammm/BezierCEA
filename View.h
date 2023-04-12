#pragma once
#include <SDL2/SDL.h>
#include "Coord.h"
#include "Bezier.h"
#include <vector>

struct Color
{
    int r, g, b;
};

struct View
{
  public:
    int           createWindow(int h, int w);
    Color         color = Color({0, 255, 255});
    SDL_Window*   window;
    SDL_Renderer* renderer;

    void drawLine(Segment segment);
    void drawLines(Segments lines);
    void changeColor(int r, int g, int b);
    void drawLines(std::vector<Coord> points);

  private:
};