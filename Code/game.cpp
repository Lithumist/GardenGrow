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


            if ( oldCell.type == CELL_STONE ) {
                // does nothing at the moment.
                i->addCell( ggCell(oldCell.x, oldCell.y, oldCell.type) );
            }

            if ( oldCell.type == CELL_WATER ) {
                // water survives if it's adjacent to at least 1 other water cell.
                if ( i->countCellsAdjacent( oldCell.x, oldCell.y, CELL_WATER ) >= 1 ) {
                    i->addCell( ggCell(oldCell.x, oldCell.y, CELL_WATER) );
                }
            }

            if (oldCell.type >= 3 && oldCell.type <= 7 ) {
                // tier type cells spawn the next tier if
                // it has exactly 2 water tiles as its neighbour
                // (other types don't matter)
                int adjWaterCells = i->countCellsAdjacent( oldCell.x, oldCell.y, CELL_WATER );
                if ( adjWaterCells == 2 ) {
                    // try to determine the next tier cell type
                    int newType = oldCell.type;
                    ++ newType;
                    if ( newType <= 7 )
                    {
                        // handle normal tier upgrade
                        i->addCell(ggCell( oldCell.x, oldCell.y, (ggCellType)newType ));
                    }
                    else
                    {
                        // handle tree upgrade
                        
                    }
                }
                else if ( adjWaterCells >= 3 && adjWaterCells <= 7 ) {
                    // cell dies if there's 3-7 water tiles as it's neighbour
                }
                else if ( adjWaterCells >= 8 ) {
                    // cell turns into water if there's too much water around it.
                    i->addCell(ggCell( oldCell.x, oldCell.y, CELL_WATER ));
                }
                else {
                    // continue this tier cell to the next generation
                    i->addCell(ggCell( oldCell.x, oldCell.y, oldCell.type ));
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