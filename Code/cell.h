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
    void drawTile( int index, sf::RenderWindow* window, ggInterface* i, bool nopan = false);

    // positions
    int curX, curY, newX, newY;

public:
    // load the texture
    static void loadTexture();

    // position (in grid coords)
    int x, y;

    // full flag
    bool full;

    // delete flag
    bool del;

    // affect count
    int AffectCount;
    
    // positions get/set
    int  get_cur_pos_x()            { return curX; }
    int  get_cur_pos_y()            { return curY; }
    int  get_new_pos_x()            { return newX; }
    int  get_new_pos_y()            { return newY; }
    void set_cur_pos_x( int argX )  { curX = argX; newX = argX; }
    void set_cur_pos_y( int argY )  { curY = argY; newY = argY; }
    void set_new_pos_x( int argX )  { newX = argX; }
    void set_new_pos_y( int argY )  { newY = argY; }

    // displacement
    int dx, dy;
    int gx(){ return x+dx; }
    int gy(){ return y+dy; }

    // type
    ggCellType type;

    // options
    bool disable;
    
    // constructors
    ggCell();
    ggCell(int argXGrid, int argYGrid, ggCellType argType);

    // functions
    void draw( ggInterface* i , sf::RenderWindow* window , bool nopan = false );

};

#endif