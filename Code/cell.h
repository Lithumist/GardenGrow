// Part of GardenGrow.

#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include "types.h"
#include <vector>

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
    void drawTile( int index, sf::RenderWindow* window, ggInterface* i, bool nopan = false );
    void drawTile( int index, sf::RenderWindow* window, ggInterface* i, int gridXpos, int gridYpos, bool nopan = false );

    // positions
    int curX, curY, newX, newY;

public:
    // load the texture
    static void loadTexture();

    // fuck
    static std::vector<ggCell*> treeDrawList;
    // drawing things on top bullshit
    static void draw_top_things( sf::RenderWindow* window, ggInterface* i, bool nopan = false );

    // position (in grid coords)
    int x, y;

    // full flag
    bool full;

    // is watered flag
    bool watered;
    bool watered2;

    // flower sprite index
    int indexFlower;

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

    // movable type function
    bool is_movable();

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