#include "Bezier/Bezier.h"
#include "Bezier/BezierEvaluate.h"
#include "Geometry/Coord.h"
#include "CurveDraw.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#define NB_POINTS_ON_CURVE 150

int id = 0;

using Selection = std::vector<std::string>;

void printSelection(std::vector<std::string>& selection) {
    for (int i = 0; i < selection.size(); ++i) {
        std::cout << i + 1 << " : " << selection[i] << std::endl;
    }
}

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
        std::cout << "x" << i + 1 << " ";
        std::cin >> x;
        std::cout << "y" << i + 1 << " ";
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

// std::vector<std::string> menu_principal ={
//     std::string("Créer courbe de bézier"),
//     std::string("Supprimer courbe de bézier"),
//     std::string("Ajouter un point"),
//     std::string("Supprimer un point"),
// };

CurveDraw createCurve() {
    CurveDraw curveReturn = CurveDraw();
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
    
    curveReturn.c.randomColor();
    curveReturn.points = casteljau(curveReturn.bezier,NB_POINTS_ON_CURVE);
    return curveReturn;
}
