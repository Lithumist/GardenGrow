// Part of GardenGrow.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "options.h"
#include "button.h"
#include "cell.h"
#include <vector>

/*
    Declares a class for manipulating the 'editor-like' interface.
*/

class ggInterface
{
private:
    // assets
    sf::Texture txtBtnControl;
    // buttons
    ggButton btnPlay, btnPause, btnStop;
    ggButton btnSave, btnLoad, btnReset;
    // cell list
    std::vector<ggCell> cells;
    // triggers
    bool ctrlHeldDown, midHeldDownPrev;
    int mouseXPrev, mouseYPrev;
    // zoom
    float zoomLevel;
    float panX, panY;
    float wheelSensitivity;
    // colours
    sf::Color colGrid;
    sf::Color colControlBackground;
    // helper functions
    void drawGrid( sf::RenderWindow* window );
    void drawInterfaceBackground( sf::RenderWindow* window );

    sf::Vector2i windowToGrid( int mouse_x , int mouse_y );
    sf::Vector2f gridToWindow( float grid_x , float grid_y );

public:
    ggInterface();

    bool loadAssets(); // first call this
    void init(); // then this
    void tick( sf::Window* window );
    void onEvent( sf::Window* window , sf::Event* e );
    void draw( sf::RenderWindow* window );
    void drawCell( sf::RenderWindow* window, int xpos, int ypos, sf::Color col );

    void pan( float dx , float dy );

};

#endif