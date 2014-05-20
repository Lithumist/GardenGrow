// Part of GardenGrow.

/*
    Creates window and starts game.
*/

#include <SFML/Graphics.hpp>

#include "options.h"
#include "interface.h"
#include "editor.h"

int main()
{
    sf::RenderWindow gameWindow( sf::VideoMode (GG_WINDOW_WIDTH,GG_WINDOW_HEIGHT) , GG_WINDOW_CAPTION , sf::Style::Titlebar | sf::Style::Close );

    // Create interface
    ggInterface Interface;
    Interface.loadAssets();
    Interface.init();

    // Create controller variable
    ggInterfaceController Control = CTRL_EDITOR;

    // Create editor
    ggEditor Editor( &Interface , &Control );



    // Game loop
    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            
            Interface.onEvent( &gameWindow, &event );
        }

        Interface.tick( &gameWindow );

        gameWindow.clear();
        //gameWindow.draw(shape);
        Interface.draw( &gameWindow );
        gameWindow.display();
    }

    return 0;
}