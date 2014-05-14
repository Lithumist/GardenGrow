// Part of GardenGrow.
#include "button.h"
#include <iostream>

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
    init( normal, over, t );
}

void ggButton::init(sf::IntRect normal , sf::IntRect over , sf::Texture* t) {
    mouseOver, doAction = false;
    rectNormal = normal;
    rectOver = over;
    width = rectNormal.width;
    height = rectNormal.height;
    texture = t;
    sprNormal.setTextureRect( normal );
    sprOver.setTextureRect( over );
    if ( t ) {
        sprNormal.setTexture( *texture );
        sprOver.setTexture( *texture );
    }
}

bool ggButton::pointInButton( int px, int py ) {
    int x, y;
    x = (int)getPosition().x;
    y = (int)getPosition().y;
    if ( px >= x && px <= x+width && py >= y && py <= y+height ) {
        return true;
    } else {
        return false;
    }
}

void ggButton::onEvent(sf::Window* window, sf::Event* e)
{
    if ( e->type == sf::Event::MouseButtonPressed ) {
        if ( e->mouseButton.button == sf::Mouse::Left ) {
            int mx, my;
            mx = sf::Mouse::getPosition(*window).x;
            my = sf::Mouse::getPosition(*window).y;
            if ( pointInButton( mx,my ) ) {
                doAction = true;
            }
        }
    }
}

void ggButton::tick(sf::Window* window)
{
    int mx, my;
    mx = sf::Mouse::getPosition(*window).x;
    my = sf::Mouse::getPosition(*window).y;

    int x, y;
    x = (int)getPosition().x;
    y = (int)getPosition().y;

    // test if mouse is over button
    if ( pointInButton(mx,my) ) {
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

    if ( mouseOver == false ) {
        target.draw(sprNormal,states);
    } else {
        target.draw(sprOver,states);
    }
}