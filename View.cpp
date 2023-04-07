#include "View.h"
#include <SDL2/SDL.h>
void View::changeColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
}

int View::createWindow(int h, int w) {
    //:SOURCE: https://stackoverflow.com/questions/14646208/adding-sdl-library-to-my-program

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow("An SDL2 window",                    //    window title
                              SDL_WINDOWPOS_UNDEFINED,             //    initial x position
                              SDL_WINDOWPOS_UNDEFINED,             //    initial y position
                              w,                                   //    width, in pixels
                              h,                                   //    height, in pixels
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

        // Clear screen
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
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
}

void View::drawLines(std::vector<Coord> points) {

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
    for (size_t i = 0; i < points.size() - 1; i++) {
        drawLine(Segment({points[i], points[i + 1]}));
    }
}
