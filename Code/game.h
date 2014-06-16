// Part of Garden Grow.

#ifndef GAME_H
#define GAME_H

#include "interface.h"
#include <SFML/Graphics.hpp>
#include "types.h"

/*
    The game class. One of the classes that can take control of the interface.
*/

class ggGame
{
private:
    // interface pointer
    ggInterface* i;
    ggInterfaceController* currentController;

    // timing
    sf::Clock tickTimer;
    bool flagPaused;
public:
    // timing
    sf::Time timeForOneTick;

    // constructor
    ggGame( ggInterface* in , ggInterfaceController* cur_ctrl );

    // heatbeat functions
    void onControl(); // called when this class takes control of the interface
    void onEvent( sf::Window* window , sf::Event* e );
    void tick( sf::Window* window );
    void draw( sf::RenderWindow* window ); // draw any overlay
};

#endif