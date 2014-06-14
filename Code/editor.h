// Part of Garden Grow.

#ifndef EDITOR_H
#define EDITOR_H

#include "interface.h"
#include <SFML/Graphics.hpp>
#include "types.h"

/*
    The editor class. One of the classes that can take control of the interface.
*/

class ggEditor
{
private:
    // interface pointer
    ggInterface* i;
    ggInterfaceController* currentController;

    int wspawn_count;
    int seed_count;
public:
    // constructor
    ggEditor( ggInterface* in , ggInterfaceController* cur_ctrl );

    // heatbeat functions
    void onControl(); // called when this class takes control of the interface
    void onEvent( sf::Window* window , sf::Event* e );
    void tick( sf::Window* window );
    void draw( sf::RenderWindow* window ); // draw any overlay
};

#endif