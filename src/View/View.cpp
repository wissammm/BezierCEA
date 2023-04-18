#include "View/View.h"
#include "Bezier/Bezier.h"
#include "Cli.h"
#include "View/CurveDraw.h"

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#define WIDTH  900
#define HEIGHT 700
using Selection = std::vector<std::string>;

Selection menu_principal = Selection({
    "0 : Quitter",
    "1 : Créer courbe",
});

int View::menuCLI() {

    std::cout << "Menu" << std::endl;

    printSelection(menu_principal);

    size_t    choosen = inInt(static_cast<size_t>(menu_principal.size() + 1));
   

    if (choosen == 1) {
        curves.push_back(createCurve());
    }

    return EXIT_SUCCESS;
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

        // Initialize renderer color white for the background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

        // Clear screen
        SDL_RenderClear(renderer);

        color.changeColor(1, 1, 1);

        // Update screen
        SDL_RenderPresent(renderer);

        int signal = menuCLI();

        for (size_t i = 0; i < curves.size(); ++i) {
            color = curves[i].c;
            drawLines(curves[i].points);
        }
    }
    return 0;
}

void View::drawLine(Segment segment) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    SDL_RenderDrawLine(renderer, segment.a.x, segment.a.y, segment.b.x, segment.b.y);

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
