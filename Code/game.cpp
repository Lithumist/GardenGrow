// Part of GardenGrow.
#include "game.h"
#include <iostream>

ggGame::ggGame( ggInterface* in , ggInterfaceController* cur_ctrl )
{
    // NULL pointer check
    if (    !in         || 
            !cur_ctrl
    ) {
        // TODO -> Spit out an error here.
    }

    i = in;
    currentController = cur_ctrl;

    timeForOneTick = sf::seconds( GG_DEFAULT_TICK_TIME );
}

void ggGame::onControl()
{
    std::cout << "Game in control now.\n";

    // Set appropriate buttons active and inactive
    i->btnResetEnabled = false;
}

void ggGame::onEvent( sf::Window* window , sf::Event* e )
{
    if ( *currentController != CTRL_GAME ) {
        return;
    }

    // reset the tick timer
    tickTimer.restart();
}

void ggGame::tick( sf::Window* window )
{
    if ( *currentController != CTRL_GAME ) {
        return;
    }

    // Hand control to editor if stop button pressed
    if ( i->btnStop.doAction ) {
        i->btnStop.doAction = false;
        *currentController = CTRL_EDITOR;
    }

    if ( tickTimer.getElapsedTime() >= timeForOneTick )
    {
        std::cout << "Tick.\n";
        /* <game logic> */

        // move all cells to the right
        for ( unsigned int t=0; t<i->cellsScreen->size(); ++t ) {
            ggCell cell( i->cellsScreen->at(t) );
            cell.x += 1;
            i->addCell( cell );
        }

        // swap buffers
        i->flipCellBuffers();

        /* </game logic> */
        tickTimer.restart();
    }
}

void ggGame::draw( sf::RenderWindow* window )
{
    if ( *currentController != CTRL_GAME ) {
        return;
    }

    // nothing atm.
}