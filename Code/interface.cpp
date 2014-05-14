// Part of GardenGrow.
#include "interface.h"
#include <iostream>

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


    // set up buttons
    btnPlay.init( sf::IntRect(0,0,20,20) , sf::IntRect(0,20,20,20) , &txtBtnControl);
    btnPlay.setPosition( 20 , 20 );
}

void ggInterface::onEvent( sf::Window* window ,sf::Event* e )
{
    btnPlay.onEvent( window, e );
}

void ggInterface::tick(sf::Window* window)
{
    // tick buttons
    btnPlay.tick(window);
    if ( btnPlay.doAction ) {
        btnPlay.doAction = false;
        std::cout << "Pressed.\n";
    }
}

void ggInterface::draw( sf::RenderWindow* window )
{
    // temp code
    sprBtnPlay.setPosition(10,10);
    sprBtnPause.setPosition(35,10);
    sprBtnStop.setPosition(60,10);
    
    //window->draw(sprBtnPlay);
    //window->draw(sprBtnPause);
    //window->draw(sprBtnStop);

    // draw buttons
    window->draw( btnPlay );
}