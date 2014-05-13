// Part of GardenGrow.
#include "button.h"

ggButton::ggButton()
{
    sf::IntRect n(0,0,0,0);
    sf::IntRect o(0,0,0,0);
    ggButton( n, o, NULL );
}

ggButton::ggButton(sf::Texture* t)
{
    sf::IntRect n(0,0,0,0);
    sf::IntRect o(0,0,0,0);
    ggButton( n, o, t );
}

ggButton::ggButton(sf::IntRect normal , sf::IntRect over)
{
    ggButton( normal, over, NULL );
}

ggButton::ggButton(sf::IntRect normal , sf::IntRect over , sf::Texture* t)
{
    mouseOver, doAction = false;
    rectNormal = normal;
    rectOver = over;
    width = rectNormal.width;
    height = rectNormal.height;
}

void ggButton::tick()
{
    int mx, my;
    mx = sf::Mouse::getPosition().x;
    my = sf::Mouse::getPosition().y;

    float x, y;
    x = getPosition().x;
    y = getPosition().y;

    // test if mouse is over button
    if ( mx >= x && mx <= x+width && my >= y && my <= y+height ) {
        mouseOver = true;
    } else {
        mouseOver = false;
    }
}

void ggButton::draw( sf::RenderTarget& target , sf::RenderStates states ) const
{
    if ( texture == NULL ) {
        // FIXME -> Add some error output here.
        return;
    }

    states.transform *= getTransform();
    states.texture = texture;
    target.draw(
}