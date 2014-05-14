// Part of GardenGrow.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "options.h"
#include "button.h"

/*
    Declares a class for manipulating the 'editor-like' interface.
*/

class ggInterface
{
private:
    // assets
    sf::Texture txtBtnControl;
    // buttons
    ggButton btnPlay;
    ggButton btnPause;
    ggButton btnStop;

public:
    bool loadAssets(); // first call this
    void init(); // then this
    void tick( sf::Window* window );
    void onEvent( sf::Window* window , sf::Event* e );
    void draw( sf::RenderWindow* window );

};

#endif