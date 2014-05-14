// Part of GardenGrow

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

/*
    gui button class
*/

class ggButton : public sf::Drawable, public sf::Transformable
{
private:
    // draw function
    virtual void draw( sf::RenderTarget& target , sf::RenderStates states ) const;

    bool mouseOver;
    sf::IntRect rectNormal, rectOver;
    int width, height;
    sf::Texture* texture;
    sf::Sprite sprNormal, sprOver;
public:
    bool doAction; // If true then button has been pressed. Make sure to set back to false.
    ggButton();
    ggButton(sf::Texture* t);
    ggButton(sf::IntRect normal , sf::IntRect over);
    ggButton(sf::IntRect normal , sf::IntRect over , sf::Texture* t);
    void init(sf::IntRect normal , sf::IntRect over , sf::Texture* t);
    bool pointInButton( int px, int py );
    void tick(sf::Window* window);
    void onEvent(sf::Window* window, sf::Event* e);
};

#endif