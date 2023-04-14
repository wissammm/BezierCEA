#include "View/View.h"
#include "Bezier/Bezier.h"
#include "Cli.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#define NB_POINTS_ON_CURVE 150
#define WIDTH 900
#define HEIGHT 700
using Selection = std::vector<std::string>;
int id = 0;


size_t inInt(size_t const& max) {
    size_t choice;
    std::cin >> choice;
    if (choice > max) {
        return -1;
    }
    return choice;
}

std::vector<Coord> getPositions(size_t& nbPoints) {
    double             x, y;
    std::vector<Coord> positions;
    for (size_t i = 0; i < nbPoints; ++i) {
        std::cout << "x" << i + 1 <<" ";
        std::cin >> x;
        std::cout << "y" << i + 1 <<" ";
        std::cin >> y;
        positions.push_back(Coord({x, y}));
    }

    return positions;
}

std::string chooseName() {
    std::string choice;
    std::cin >> choice;
    return choice;
}

std::vector<std::string> menu_principal ={
    std::string("Créer courbe de bézier"),
    std::string("Supprimer courbe de bézier"),
    std::string("Ajouter un point"),
    std::string("Supprimer un point"),
};

Curve createCurve() {
    Curve curveReturn;
    std::cout << "Nom : ";
    curveReturn.name = chooseName();
    std::cout << "Nombre de points : ";
    size_t nbPoint = inInt(100);
    // if (nbPoint == -1)
    //     SDL_Error;

    std::cout << "aléatoire 0, sinon 1" << std::endl;
    int selec = inInt(100000000000);

    //TODO:Wissam: Choisir la taille de fenetre de view
    if (selec + 1 == 2)
        curveReturn.bezier = getPositions(nbPoint);
    else
        curveReturn.bezier = randomPoint(nbPoint, 600, 400);
    curveReturn.id = ++id;
    curveReturn.c.randomColor();
    curveReturn.points = casteljau(curveReturn.bezier,NB_POINTS_ON_CURVE);
    return curveReturn;
}

int View::menuCLI() {

    std::cout << "Menu" << std::endl;
    std::cout << "0 : Quitter" <<  std::endl;
    // printSelection(menu_principal);
    for (int i = 0; i < menu_principal.size(); ++i) {
        std::cout << i + 1 << " : " << menu_principal[i] << std::endl;
    }
    size_t choosen = inInt(static_cast<size_t>(menu_principal.size() + 1));
    Curve curve;

    if(choosen == 1){
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
                              WIDTH,                                   //    width, in pixels
                              HEIGHT,                                   //    height, in pixels
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

        for (size_t i = 0; i<curves.size() ;++i){
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
