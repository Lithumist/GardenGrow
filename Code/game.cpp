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
            ggCell oldCell( i->cellsScreen->at(t) );

            // if there already is a cell here, then skip this
            int co = 0;
            i->cellAt(oldCell.x , oldCell.y, false, &co);
            if ( co > 1 ) {
                i->cellsScreen->at(t).disable = true;
                continue;
            }

            switch( oldCell.type )
            {
                case CELL_STONE:
                    // does nothing.
                break;

                case CELL_WATER:
                    // spawns 4 new water tiles if there are at least 2 water tiles adjacent
                    int c = 0;
                    i->cellAt(oldCell.x, oldCell.y, true, &c);
                    if( c >= 2 ) {
                        i->addCell(ggCell( oldCell.x+1 , oldCell.y , CELL_WATER));
                        i->addCell(ggCell( oldCell.x-1 , oldCell.y , CELL_WATER));
                        i->addCell(ggCell( oldCell.x , oldCell.y+1 , CELL_WATER));
                        i->addCell(ggCell( oldCell.x , oldCell.y-1 , CELL_WATER));
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