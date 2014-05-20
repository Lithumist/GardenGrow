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

public:
    // position (in grid coords)
    int x, y;

    // type
    ggCellType type;
    
    // constructors
    ggCell();
    ggCell(int xgrid, int ygrid, ggCellType typ);

    // functions
    void draw( ggInterface* i , sf::RenderWindow* window );

};

#endif