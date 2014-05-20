// Part of GardenGrow.

/*
    Creates window and starts game.
*/

#include <SFML/Graphics.hpp>

#include "options.h"
#include "types.h"
#include "interface.h"
#include "editor.h"
#include "game.h"

int main()
{
    sf::RenderWindow gameWindow( sf::VideoMode (GG_WINDOW_WIDTH,GG_WINDOW_HEIGHT) , GG_WINDOW_CAPTION , sf::Style::Titlebar | sf::Style::Close );

    // Pointer to whcih cell vector to render
    std::vector<ggCell>* cr;

    // Set up background to render
    sf::RectangleShape background(sf::Vector2f( GG_WINDOW_WIDTH , GG_WINDOW_HEIGHT ));
    background.setFillColor( GG_BACKGROUND_COLOUR );

    // Create interface
    ggInterface Interface;
    Interface.loadAssets();
    Interface.init();

    // Create controller variable
    ggInterfaceController Control = CTRL_EDITOR;
    ggInterfaceController ControlPrev = CTRL_EDITOR;

    // Create editor
    ggEditor Editor( &Interface , &Control );
    Editor.onControl();

    // Create game
    ggGame Game( &Interface , &Control );




    // Game loop
    while (gameWindow.isOpen())
    {
        // events
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            
            Interface.onEvent( &gameWindow, &event );
            Editor.onEvent( &gameWindow, &event );
            Game.onEvent( &gameWindow, &event );
        }

        // tick
        Interface.tick( &gameWindow );
        // editor
        ControlPrev = Control;
        Editor.tick( &gameWindow );
        if (ControlPrev != Control) {
            Game.onControl();
        }
        // game
        ControlPrev = Control;
        Game.tick( &gameWindow );
        if (ControlPrev != Control) {
            Editor.onControl();
        }

        // decide whcih cell vector to draw
        if ( Control == CTRL_EDITOR ) {
            cr = Interface.cellsPattern;
        } else if ( Control == CTRL_GAME ) {
            cr = Interface.cellsScreen;
        }

        // draw
        gameWindow.clear();
        gameWindow.draw( background );
        Interface.draw( &gameWindow , cr );
        Editor.draw( &gameWindow );
        Game.draw( &gameWindow );
        gameWindow.display();
    }

    return 0;
}