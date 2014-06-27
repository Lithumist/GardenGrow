// Part of GardenGrow.
#include "game.h"
#include "funcs.h"
#include <iostream>
#include <algorithm>

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
        // TODO -> handle water cells somehow

        // first pass though old cells
        // reset AffectCount
        for ( unsigned int t=0; t<i->cellsCurrent.size(); ++t ) {
            i->cellsCurrent[ t ].AffectCount = 0;
        }

        // second pass through the old cells
        // determine how many cells will affect each cell
        // also calculates the new positions (applied in second pass if AffectCount <= 1)
        for ( unsigned int t=0; t<i->cellsCurrent.size(); ++t )
        {
            ggCell oldCell( i->cellsCurrent[t] );

            // update the watered flag for the cell
            if ( oldCell.type == CELL_WATER ) {
                oldCell.watered = true;
            } else {
                int count = 0;
                ggCell* rCell = i->cellAt( oldCell.get_cur_pos_x() + 1, oldCell.get_cur_pos_y()     );
                ggCell* lCell = i->cellAt( oldCell.get_cur_pos_x() - 1, oldCell.get_cur_pos_y()     );
                ggCell* dCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() + 1 );
                ggCell* uCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() - 1 );
                if ( rCell && rCell->type == CELL_WATER ) ++ count;
                if ( lCell && lCell->type == CELL_WATER ) ++ count;
                if ( dCell && dCell->type == CELL_WATER ) ++ count;
                if ( uCell && uCell->type == CELL_WATER ) ++ count;
                if ( count >= 1 ) {
                    oldCell.watered = true;
                } else {
                    oldCell.watered = false;
                }
            }

            if ( oldCell.type == CELL_SEED && oldCell.watered ) {
                i->cellsCurrent[t].type = CELL_FLOWER;
            }

            if ( oldCell.type == CELL_FLOWER && !oldCell.watered ) {
                i->cellsCurrent[t].type = CELL_DEAD;
            }

            if ( oldCell.type == CELL_PUSH || oldCell.type == CELL_SPIN )
            {
                ggCell* rCell = i->cellAt( oldCell.get_cur_pos_x() + 1, oldCell.get_cur_pos_y()     );
                ggCell* lCell = i->cellAt( oldCell.get_cur_pos_x() - 1, oldCell.get_cur_pos_y()     );
                ggCell* dCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() + 1 );
                ggCell* uCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() - 1 );

                // check if can spin
                bool flagCanSpin = true;
                if ( oldCell.type == CELL_SPIN ) {
                    if ( rCell && !rCell->is_movable() ) flagCanSpin = false;
                    if ( lCell && !lCell->is_movable() ) flagCanSpin = false;
                    if ( dCell && !dCell->is_movable() ) flagCanSpin = false;
                    if ( uCell && !uCell->is_movable() ) flagCanSpin = false;
                }

                if ( rCell && rCell->is_movable() && i->can_push( rCell, DIRECTION_RIGHT ) ) {
                    ++ rCell->AffectCount;
                    if ( oldCell.type == CELL_PUSH ) {
                        move_chain( rCell, DIRECTION_RIGHT );
                    }
                    if ( oldCell.type == CELL_SPIN && flagCanSpin ) {
                        rCell->set_new_pos_x( rCell->get_cur_pos_x() - 1 );
                        rCell->set_new_pos_y( rCell->get_cur_pos_y() + 1 );
                    }
                }

                if ( lCell && lCell->is_movable() && i->can_push( lCell, DIRECTION_LEFT ) ) {
                    ++ lCell->AffectCount;
                    if ( oldCell.type == CELL_PUSH ) {
                        move_chain( lCell, DIRECTION_LEFT );
                    }
                    if ( oldCell.type == CELL_SPIN && flagCanSpin ) {
                        lCell->set_new_pos_x( lCell->get_cur_pos_x() + 1 );
                        lCell->set_new_pos_y( lCell->get_cur_pos_y() - 1 );
                    }
                }

                if ( dCell && dCell->is_movable() && i->can_push( dCell, DIRECTION_DOWN ) ) {
                    ++ dCell->AffectCount;
                    if ( oldCell.type == CELL_PUSH ) {
                        move_chain( dCell, DIRECTION_DOWN );
                    }
                    if ( oldCell.type == CELL_SPIN && flagCanSpin ) {
                        dCell->set_new_pos_x( dCell->get_cur_pos_x() - 1 );
                        dCell->set_new_pos_y( dCell->get_cur_pos_y() - 1 );
                    }
                }

                if ( uCell && uCell->is_movable() && i->can_push( uCell, DIRECTION_UP ) ) {
                    ++ uCell->AffectCount;
                    if ( oldCell.type == CELL_PUSH ) {
                        move_chain( uCell, DIRECTION_UP );
                    }
                    if ( oldCell.type == CELL_SPIN && flagCanSpin ) {
                        uCell->set_new_pos_x( uCell->get_cur_pos_x() + 1 );
                        uCell->set_new_pos_y( uCell->get_cur_pos_y() + 1 );
                    }
                }
            }
        }

        // reverse the order of the old cells
        // to make the order in which you place pusher cells more intuitive 
        // TODO -> sort list so that the cells that are furthest north west are first.
        std::reverse( i->cellsCurrent.begin(), i->cellsCurrent.end() );

        // third pass through the old cells
        // add cells with new positions to updated vector
        // only if AffectCount <= 1
        // also handle fountain cells
        for ( unsigned int t=0; t<i->cellsCurrent.size(); ++t )
        {
            ggCell oldCell( i->cellsCurrent[t] );

            if ( oldCell.type == CELL_WSPAWN )
            {
                ggCell* rCell = i->cellAt( oldCell.get_cur_pos_x() + 1, oldCell.get_cur_pos_y()     );
                ggCell* lCell = i->cellAt( oldCell.get_cur_pos_x() - 1, oldCell.get_cur_pos_y()     );
                ggCell* dCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() + 1 );
                ggCell* uCell = i->cellAt( oldCell.get_cur_pos_x()    , oldCell.get_cur_pos_y() - 1 );

                if ( !rCell ) {
                    i->cellsUpdated.push_back( ggCell( oldCell.get_cur_pos_x() + 1, oldCell.get_new_pos_y(), CELL_WATER ) );
                }
                if ( !lCell ) {
                    i->cellsUpdated.push_back( ggCell( oldCell.get_cur_pos_x() - 1, oldCell.get_new_pos_y(), CELL_WATER ) );
                }
                if ( !dCell ) {
                    i->cellsUpdated.push_back( ggCell( oldCell.get_cur_pos_x(), oldCell.get_new_pos_y() + 1, CELL_WATER ) );
                }
                if ( !uCell ) {
                    i->cellsUpdated.push_back( ggCell( oldCell.get_cur_pos_x(), oldCell.get_new_pos_y() - 1, CELL_WATER ) );
                }
            }

            if ( oldCell.AffectCount <= 1 ) {
                i->cellsUpdated.push_back( ggCell( oldCell.get_new_pos_x(), oldCell.get_new_pos_y(), oldCell.type ) );
            } else 
            {
                //out( "jam " + std::to_string( oldCell.AffectCount ) + "\n" );
                i->cellsUpdated.push_back( ggCell( oldCell.get_cur_pos_x(), oldCell.get_cur_pos_y(), oldCell.type ) );
            }
        }
        

        out("Tick ");
        out(uint_to_string( (unsigned int)i->cellsCurrent.size() ));
        out(".\n");
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

void ggGame::move_chain( ggCell* argStart, _ggDirection argDir )
{
    // get new position
    int nextX = argStart->get_cur_pos_x() + direction_to_x( argDir );
    int nextY = argStart->get_cur_pos_y() + direction_to_y( argDir );

    // get next cell in the chain
    ggCell* cellNext = i->cellAt( nextX, nextY );

    // move current cell
    argStart->set_new_pos_x( nextX );
    argStart->set_new_pos_y( nextY );

    // if there is another cell in the chain
    // move it too
    if ( cellNext ) {
        return move_chain( cellNext, argDir );
    }
}