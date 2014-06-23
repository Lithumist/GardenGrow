// Part of GardenGrow.
#include "game.h"
#include "funcs.h"
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
    flagPaused = false;
}

void ggGame::onControl()
{
    out("Game in control now.\n");

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
        flagPaused = false;
        *currentController = CTRL_EDITOR;
    }
    if ( i->btnPlay.doAction ) {
        i->btnPlay.doAction = false;
        if ( flagPaused ) {
            flagPaused = false;
            out("Game unpaused.");
        }
    }
    if ( i->btnSave.doAction ) i->btnSave.doAction = false;
    if ( i->btnLoad.doAction ) i->btnLoad.doAction = false;

    if ( i->btnPause.doAction ) {
        i->btnPause.doAction = false;
        flagPaused = !flagPaused;
        // output
        flagPaused ? out("Game paused.") : out("Game unpaused.");
    }

    if ( tickTimer.getElapsedTime() >= timeForOneTick && !flagPaused )
    {
        for ( unsigned int t=0; t<i->cellsCurrent.size(); ++t )
        {
            // get old position
            ggCell oldCell( i->cellsCurrent[t] );

            // spinner
            if ( oldCell.type == CELL_SPIN && !oldCell.del ) {
                // add the spinner
                i->addCell( ggCell(oldCell.x, oldCell.y, CELL_SPIN) );
                {
                    // find cells adjacent
                    ggCell* cellRight = i->cellAt( oldCell.x + 1, oldCell.y     );
                    ggCell* cellLeft  = i->cellAt( oldCell.x - 1, oldCell.y     );
                    ggCell* cellDown  = i->cellAt( oldCell.x    , oldCell.y + 1 );
                    ggCell* cellUp    = i->cellAt( oldCell.x    , oldCell.y - 1 );
                    // rotate them
                    if ( cellRight && i->isMovable(*cellRight) ) {
                        cellRight->dx = -1;
                        cellRight->dy = 1;
                    }
                    if ( cellLeft && i->isMovable(*cellLeft) ) {
                        cellLeft->dx = 1;
                        cellLeft->dy = -1;
                    }
                    if ( cellDown && i->isMovable(*cellDown) ) {
                        cellDown->dx = -1;
                        cellDown->dy = -1;
                    }
                    if ( cellUp && i->isMovable(*cellUp) ) {
                        cellUp->dx = 1;
                        cellUp->dy = 1;
                    }
                }
            }

            // pusher
            if ( oldCell.type == CELL_PUSH && !oldCell.del ) {
                // add the pusher
                i->addCell( ggCell(oldCell.x, oldCell.y, CELL_PUSH) );
                {
                    // find cells adjacent
                    ggCell* cellRight = i->cellAt( oldCell.x + 1, oldCell.y     );
                    ggCell* cellLeft  = i->cellAt( oldCell.x - 1, oldCell.y     );
                    ggCell* cellDown  = i->cellAt( oldCell.x    , oldCell.y + 1 );
                    ggCell* cellUp    = i->cellAt( oldCell.x    , oldCell.y - 1 );
                    // move them
                    if ( cellRight && i->isMovable(*cellRight) ) {
                        cellRight->dx = 1;
                        if ( !i->handleOverlap( cellRight, 1, 0 ) ) {
                            cellRight->full = true;
                        }
                    }
                    if ( cellLeft && i->isMovable(*cellLeft) ) {
                        cellLeft->dx = -1;
                        if ( !i->handleOverlap( cellLeft, -1, 0 ) ) {
                            cellLeft->full = true;
                        }
                    }
                    if ( cellDown && i->isMovable(*cellDown) ) {
                        cellDown->dy = 1;
                        if ( !i->handleOverlap( cellDown, 0, 1 ) ) {
                            cellDown->full = true;
                        }
                    }
                    if ( cellUp && i->isMovable(*cellUp) ) {
                        cellUp->dy = -1;
                        if ( !i->handleOverlap( cellUp, 0, -1 ) ) {
                            cellUp->full = true;
                        }
                    }
                }
            }

            
        }

        for ( unsigned int t=0; t<i->cellsCurrent.size(); ++t )
        {
            // get old position
            ggCell oldCell( i->cellsCurrent[t] );

            // keep stationary cells where they are
            if ( 
                    oldCell.type == CELL_STONE   ||
                    oldCell.type == CELL_WATER   ||
                    oldCell.type == CELL_POWER   ||
                    oldCell.type == CELL_DEAD
                    && !oldCell.del 
               )
            {
                i->addCell( ggCell(oldCell.gx(), oldCell.gy(), oldCell.type) );
            }

            // water fountain
            if ( oldCell.type == CELL_WSPAWN && !oldCell.del ) {
                // add the fountain
                i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_WSPAWN) );
                {
                    // find cells adjacent
                    ggCell* cellRight = i->cellAt( oldCell.x + 1, oldCell.y     );
                    ggCell* cellLeft  = i->cellAt( oldCell.x - 1, oldCell.y     );
                    ggCell* cellDown  = i->cellAt( oldCell.x    , oldCell.y + 1 );
                    ggCell* cellUp    = i->cellAt( oldCell.x    , oldCell.y - 1 );
                    // rotate them
                    if ( !cellRight ) {
                        i->addCell( ggCell(oldCell.x + 1, oldCell.y, CELL_WATER) );
                    }
                    if ( !cellLeft ) {
                        i->addCell( ggCell(oldCell.x - 1, oldCell.y, CELL_WATER) );
                    }
                    if ( !cellDown ) {
                        i->addCell( ggCell(oldCell.x, oldCell.y + 1, CELL_WATER) );
                    }
                    if ( !cellUp ) {
                        i->addCell( ggCell(oldCell.x, oldCell.y - 1, CELL_WATER) );
                    }
                }
            }

            // seeds
            if ( oldCell.type == CELL_SEED && !oldCell.del ) {
                int adj_cells = i->countCellsAdjacent( oldCell.gx(), oldCell.gy(), CELL_WATER );
                if ( adj_cells >= 1 ) {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_FLOWER) );
                } else {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_SEED) );
                }
            }

            // flowers
            if ( oldCell.type == CELL_FLOWER && !oldCell.del ) {
                int adj_cells = i->countCellsAdjacent( oldCell.gx(), oldCell.gy(), CELL_WATER );
                if ( adj_cells >= 1 ) {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_FLOWER) );
                } else {
                    i->addCell( ggCell(oldCell.gx(), oldCell.gy(), CELL_DEAD) );
                }
            }

            

            


            /*****************/
            /* </game logic> */
            /*****************/
        }
        out("Tick ");
        out(uint_to_string( (unsigned int)i->cellsCurrent.size() ));
        out(".\n");
        i->resetCellDelta();
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