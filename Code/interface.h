// Part of GardenGrow.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "options.h"
#include "button.h"
#include "cell.h"
#include <vector>

/*
    Enums
*/

enum ggCellType             { CELL_SEED                 };
enum ggInterfaceController  { CTRL_EDITOR , CTRL_GAME   };

/*
    Declares a class for manipulating the 'editor-like' interface.
*/

class ggCell;

class ggInterface
{
    friend class ggCell;
private:
    // assets
    sf::Texture txtBtnControl;

    // buttons
    ggButton btnPlay, btnPause, btnStop;
    ggButton btnSave, btnLoad, btnReset;
    ggButton btnGrid;

    // cell list
    std::vector<ggCell> cells;

    // triggers and event variables
    bool ctrlHeldDown, midHeldDownPrev;
    int mouseXPrev, mouseYPrev;

    // zoom and pan variables
    float zoomLevel;
    float panX, panY;
    float wheelSensitivity;

    // colours
    sf::Color colGrid;
    sf::Color colControlBackground;

    // control flags
    bool gridVisible;

    // helper functions
    void drawGrid( sf::RenderWindow* window );
    void drawInterfaceBackground( sf::RenderWindow* window );
    void drawCell( sf::RenderWindow* window, int xpos, int ypos, sf::Color col );

public:
    ggInterface();

    bool loadAssets(); // first call this
    void init(); // then this

    void tick( sf::Window* window );
    void onEvent( sf::Window* window , sf::Event* e );
    void draw( sf::RenderWindow* window );

    void pan( float dx , float dy );

    sf::Vector2i windowToGrid( int mouse_x , int mouse_y );
    sf::Vector2f gridToWindow( float grid_x , float grid_y );

};

#endif