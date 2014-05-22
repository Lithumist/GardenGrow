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

    // Modify interface options
    i->btnResetEnabled = false;
    i->tileSelectorEnabled = false;
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
        for ( unsigned int t=0; t<i->cellsScreen->size(); ++t )
        {
            /****************/
            /* <game logic> */
            /****************/

            // A few notes:
            /*
                I opted to not include a 'default' case and handle basic cell vector swapping once because, 
                I wanted cells that had not been implemented yet to just disappear. Prevents me from possible
                future headaches.
            */


            ggCell oldCell( i->cellsScreen->at(t) );

            // if there already is a cell here, then skip this
            // FIXME -> ugh...

            switch( oldCell.type )
            {
                case CELL_STONE:
                    // does nothing.
                    i->addCell( ggCell(oldCell.x, oldCell.y, oldCell.type) );
                break;

                case CELL_WATER:
                    // move right if space free.
                    if ( ! (i->cellAt(oldCell.x+1, oldCell.y, CELL_STONE)) ) {
                        i->addCell( ggCell(oldCell.x + 1, oldCell.y, oldCell.type) );
                    } else {
                        i->addCell( ggCell(oldCell.x, oldCell.y, oldCell.type) );
                    }
                break;
            }


            /*****************/
            /* </game logic> */
            /*****************/
        }
        i->flipCellBuffers();
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