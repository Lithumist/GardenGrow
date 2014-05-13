// Part of GardenGrow.
#include "interface.h"

bool ggInterface::loadAssets()
{
    bool success = true;
    
    if ( !txtBtnControl.loadFromFile("data/btn_control.png") ) {
        success = false;
    }

    return success;
}

void ggInterface::init()
{
    // bind all textures to sprites

    // play button
    sprBtnPlay.setTexture       ( txtBtnControl );
    sprBtnPlay.setTextureRect   ( sf::IntRect(0,0,20,20) );

    // pause button
    sprBtnPause.setTexture       ( txtBtnControl );
    sprBtnPause.setTextureRect   ( sf::IntRect(20,0,20,20) );

    // stop button
    sprBtnStop.setTexture       ( txtBtnControl );
    sprBtnStop.setTextureRect   ( sf::IntRect(40,0,20,20) );
}

void ggInterface::draw( sf::RenderWindow* window )
{
    // temp code
    sprBtnPlay.setPosition(10,10);
    sprBtnPause.setPosition(35,10);
    sprBtnStop.setPosition(60,10);
    
    window->draw(sprBtnPlay);
    window->draw(sprBtnPause);
    window->draw(sprBtnStop);
}