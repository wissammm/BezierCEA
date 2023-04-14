#pragma once
#include <SDL2/SDL.h>

#include "Geometry/Coord.h"
#include "Bezier/Bezier.h"
#include "Cli.h"
#include "Color.h"
#include <vector>
#include <random>


using Curves= std::vector<Curve>;

struct View
{
  public:
    int           createWindow();
    Color         color = Color(0, 255, 255);
    SDL_Window*   window;
    SDL_Renderer* renderer;
    Curves curves;



    void drawLine(Segment segment);
    void drawLines(Segments lines);
    void changeColor(int r, int g, int b);
    void drawLines(std::vector<Coord> points);
    

  private:
    int menuCLI();

    
};