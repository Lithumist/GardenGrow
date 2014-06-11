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
    
    // spritesheet texture
    static sf::Texture txtCell;
    void drawTile( int index, sf::RenderWindow* window, ggInterface* i );

public:
    // load the texture
    static void loadTexture();

    // position (in grid coords)
    int x, y;

    // displacement
    int dx, dy;
    int gx(){ int t=dx; dx=0; return x+t; }
    int gy(){ int t=dy; dy=0; return y+t; }

    // type
    ggCellType type;

    // options
    bool disable;
    
    // constructors
    ggCell();
    ggCell(int xgrid, int ygrid, ggCellType typ);

    // functions
    void draw( ggInterface* i , sf::RenderWindow* window );

};

#endif