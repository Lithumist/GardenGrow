// Part of GardenGrow.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "options.h"

/*
    Declares a class for manipulating the 'editor-like' interface.
*/

class ggInterface
{
private:
    // assets
    sf::Texture txtBtnControl;
    // sprites
    sf::Sprite sprBtnPlay;
    sf::Sprite sprBtnPause;
    sf::Sprite sprBtnStop;

public:
    bool loadAssets(); // first call this
    void init(); // then this
    void draw( sf::RenderWindow* window );

};

#endif