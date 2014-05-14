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
    // set up buttons
    btnPlay.init( sf::IntRect(0,0,20,20) , sf::IntRect(0,20,20,20) , &txtBtnControl);
    btnPlay.setPosition( 20 , 20 );

    btnPause.init( sf::IntRect(20,0,20,20) , sf::IntRect(20,20,20,20) , &txtBtnControl);
    btnPause.setPosition( 42 , 20 );

    btnStop.init( sf::IntRect(40,0,20,20) , sf::IntRect(40,20,20,20) , &txtBtnControl);
    btnStop.setPosition( 64 , 20 );
}

void ggInterface::onEvent( sf::Window* window ,sf::Event* e )
{
    btnPlay.onEvent( window, e );
    btnPause.onEvent( window, e );
    btnStop.onEvent( window, e );
}

void ggInterface::tick(sf::Window* window)
{
    // tick buttons
    btnPlay.tick(window);
    btnPause.tick(window);
    btnStop.tick(window);
}

void ggInterface::draw( sf::RenderWindow* window )
{
    // draw buttons
    window->draw( btnPlay );
    window->draw( btnPause );
    window->draw( btnStop );
}