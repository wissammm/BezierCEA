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
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = std::min(w, h) / 2;
    squareRect.h = std::min(w, h) / 2;

    // Square position: In the middle of the screen
    squareRect.x = w / 2 - squareRect.w / 2;
    squareRect.y = h / 2 - squareRect.h / 2;

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
        SDL_SetRenderDrawColor(renderer,0, 0, 0, 0);

        // Clear screen
        SDL_RenderClear(renderer);

        // Set renderer color red to draw the square
       SDL_SetRenderDrawColor(renderer,255, 0, 255, 0);

        // Draw filled square
        SDL_RenderFillRect(renderer, &squareRect);

        // Update screen
        SDL_RenderPresent(renderer);
    }
    return 0;
}

void View::drawLine(Segment segment) { int a; }
