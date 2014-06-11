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
    if ( i->btnPlay.doAction ) i->btnPlay.doAction = false;

    if ( tickTimer.getElapsedTime() >= timeForOneTick )
    {
        std::cout << "Tick.\n";
        for ( unsigned int t=0; t<i->cellsScreen->size(); ++t )
        {
            /****************/
            /* <game logic> */
            /****************/

            ggCell oldCell( i->cellsScreen->at(t) );

            // ##################### CHANGE ALL SHIT TO USE gx AND gy

            // keep stationary cells where they are
            if ( 
                    oldCell.type == CELL_STONE ||
                    oldCell.type == CELL_WATER
               )
            {
                i->addCell( ggCell(oldCell.gx(), oldCell.gy(), oldCell.type) );
            }

            if ( oldCell.type == CELL_SEED ) {
                int adj_cells = i->countCellsAdjacent( oldCell.gx(), oldCell.gy(), CELL_WATER );
                if ( adj_cells >= 1 ) {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_FLOWER) );
                } else {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_SEED) );
                }
            }

            if ( oldCell.type == CELL_PUSH ) {
                // add the pusher
                i->addCell( ggCell(oldCell.x, oldCell.y, CELL_PUSH) );
                // find cells adjacent
                ggCell* cellRight = i->cellAt( oldCell.x + 1, oldCell.y     );
                ggCell* cellLeft  = i->cellAt( oldCell.x - 1, oldCell.y     );
                ggCell* cellDown  = i->cellAt( oldCell.x    , oldCell.y + 1 );
                ggCell* cellUp    = i->cellAt( oldCell.x    , oldCell.y - 1 );
                // move them
                if ( cellRight ) {
                    cellRight->dx = 1;
                    std::cout << "r\n";
                }
                if ( cellLeft ) {
                    cellLeft->dx = -1;
                    std::cout << "l\n";
                }
                if ( cellDown ) {
                    cellDown->dy = 1;
                    std::cout << "d\n";
                }
                if ( cellUp ) {
                    cellUp->dy = -1;
                    std::cout << "u\n";
                }
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