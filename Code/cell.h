// Part of GardenGrow.

#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "types.h"

class ggInterface;

/*
    Declares a cell class. Stores all info about a specific cell in an ggInterface.
    Handles it's own drawing.
*/

class ggCell
{
private:
    // position (in grid coords)
    int x, y;
    // type
    ggCellType type;

public:
    
    ggCell();
    ggCell(int xgrid, int ygrid, ggCellType typ);

    void draw( ggInterface* i , sf::RenderWindow* window );

};

#endif