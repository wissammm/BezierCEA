#include "View/View.h"
#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Cli.h"
#include "View/CurveDraw.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <string>
#include <iostream>

#define WIDTH  900
#define HEIGHT 700

// Create custom split() function.
std::vector<std::string> customSplit(std::string str, char separator) {
    int                      startIndex = 0, endIndex = 0;
    std::vector<std::string> strings;
    for (int i = 0; i <= str.size(); i++) {

        // If we reached the end of the word or the end of the input.
        if (str[i] == separator || i == str.size()) {
            endIndex = i;
            std::string temp;
            temp.append(str, startIndex, endIndex - startIndex);
            strings.push_back(temp);
            startIndex = endIndex + 1;
        }
    }
    return strings;
}

void View::consoleCreator() {

    std::string choice;
    std::cin >> choice;
    auto strings = customSplit(choice, ' ');
    if (strings[0].compare("bezier") == 0) {
        CurveDraw curveDraw;

        if (strings[0].compare("-p") == 0) {
            if (strings.size() % 2 == 0) {
                Bezier bez = Bezier(strings.size() - 1);
                for (int i = 2; i < strings.size(); i += 2) {
                    bez.push_back(Coord({std::stod(strings[i]), std::stod(strings[i + 1])}));
                }
                curveDraw.bezier = Curve(bez);
                curveDraw.points = casteljau(bez, pointsOnCurves);
                curveDraw.name   = std::to_string(curves.size());
                curves.push_back(curveDraw);
            } else {
                std::cout << "Nombres de points impair" << std::endl;
            }

        } else {
            // std::string nb   = strings[0];
            Curve       bez  = randomPoint(8, HEIGHT, WIDTH);
            curveDraw.bezier = Curve(bez);
            curveDraw.points = casteljau(bez, pointsOnCurves);
            curveDraw.name   = std::to_string(curves.size());
            curves.push_back(curveDraw);
        }
    }
}

int View::createWindow() {
    //:SOURCE: https://stackoverflow.com/questions/14646208/adding-sdl-library-to-my-program

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow("Bezier",                            //    window title
                              SDL_WINDOWPOS_UNDEFINED,             //    initial x position
                              SDL_WINDOWPOS_UNDEFINED,             //    initial y position
                              WIDTH,                               //    width, in pixels
                              HEIGHT,                              //    height, in pixels
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL //    flags - see below
    );

    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        // std::cout << "Could not create window: " << SDL_GetError() << '\n';
        return 1;
    }

    // Declare rect of square
    SDL_Rect squareRect;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Event loop exit flag
    bool quit = false;
    while (!quit) {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        consoleCreator();
        // Initialize renderer color white for the background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        for (int i = 0; i < curves.size(); ++i) {
            drawLines(curves[i].points);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return 0;
}

void View::drawLine(Segment segment) {

    thickLineRGBA(renderer, segment.a.x, segment.a.y, segment.b.x, segment.b.y, 3, color.r, color.g, color.b, 1);

    // Update screen
    SDL_RenderPresent(renderer);
}

void View::drawLines(Segments lines) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    for (size_t i = 0; i < lines.size(); i++) {
        drawLine(lines[i]);
    }
    SDL_RenderPresent(renderer);
}

void View::drawLines(std::vector<Coord> points) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    for (size_t i = 0; i < points.size() - 1; i++) {
        drawLine(Segment({points[i], points[i + 1]}));
    }
    SDL_RenderPresent(renderer);
}
