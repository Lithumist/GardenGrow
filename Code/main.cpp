// Part of GardenGrow.

/*
    Creates window and starts game.
*/

#include <SFML/Graphics.hpp>

#include "options.h"

int main()
{
    sf::RenderWindow gameWindow( sf::VideoMode (GG_WINDOW_WIDTH,GG_WINDOW_HEIGHT) , GG_WINDOW_CAPTION , sf::Style::Titlebar | sf::Style::Close );
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (gameWindow.isOpen())
    {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }

        gameWindow.clear();
        gameWindow.draw(shape);
        gameWindow.display();
    }

    return 0;
}