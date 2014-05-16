// Part of GardenGrow.

#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

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

public:
    
    ggCell();
    ggCell(int xgrid, int ygrid);

    void draw( ggInterface* i , sf::RenderWindow* window );

};

#endif