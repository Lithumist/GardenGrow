// Part of GardenGrow.
#include "editor.h"
#include <iostream>
#include "funcs.h"
#include "image_io.h"
#include "file_dialog.h"

ggEditor::ggEditor( ggInterface* in , ggInterfaceController* cur_ctrl )
{
    // NULL pointer check
    if (    !in         || 
            !cur_ctrl
    ) {
        // TODO -> Spit out an error here.
    }

    i = in;
    currentController = cur_ctrl;
    wspawn_count = 0;
    seed_count = 0;
}

void ggEditor::onControl()
{
    out("Editor in control now.\n");
    // Modify interface options
    i->btnResetEnabled = true;
    i->tileSelectorEnabled = true;
}

void ggEditor::onEvent( sf::Window* window , sf::Event* e )
{
    if ( *currentController != CTRL_EDITOR ) {
        return;
    }

    // create cells on left click
    if ( e->type == sf::Event::MouseButtonPressed && e->mouseButton.button == sf::Mouse::Left ) {
        if ( e->mouseButton.y > GG_CONTROL_BAR_HEIGHT ) {
            sf::Vector2i gridLocation = i->windowToGrid( e->mouseButton.x , e->mouseButton.y );
            // std::cout << "(" << gridLocation.x << ", " << gridLocation.y << ")\n";
            // delete cell under
            ggCell* under = i->cellAt(gridLocation.x, gridLocation.y, CELL_ANY, &i->cellsInitial);
            if ( under ) {
                ggCell cellDeleted = i->delCellInitial(gridLocation.x, gridLocation.y);
                updateCount();
            }
            if ( i->selectedType == CELL_WSPAWN && wspawn_count >= GG_WSPAWN_MAX ) {
                out("You can only place 1 water spawner!\n");
            } else if ( i->selectedType == CELL_SEED && seed_count >= 20 ) {
                out( "You can only place 20 seeds!\n");
            } else {
                i->addCellInitial( ggCell(gridLocation.x, gridLocation.y, i->selectedType) );
            }
            if ( i->selectedType == CELL_WSPAWN )   ++ wspawn_count;
            if ( i->selectedType == CELL_SEED )     ++ seed_count;
            
        }
    }

    // delete cells on right click
    if ( e->type == sf::Event::MouseButtonPressed && e->mouseButton.button == sf::Mouse::Right ) {
        if ( e->mouseButton.y > GG_CONTROL_BAR_HEIGHT ) {
            sf::Vector2i gridLocation = i->windowToGrid( e->mouseButton.x , e->mouseButton.y );
            // std::cout << "(" << gridLocation.x << ", " << gridLocation.y << ")\n";
            ggCell cellDeleted = i->delCellInitial(gridLocation.x, gridLocation.y); // doesn't matter if cell doesn't exist
            updateCount();
        }
    }
}

void ggEditor::tick( sf::Window* window )
{
    if ( *currentController != CTRL_EDITOR ) {
        return;
    }

    // If play pressed, hand control over to game.
    if ( i->btnPlay.doAction ) {
        i->btnPlay.doAction = false;
        i->loadInitialCellPattern();
        *currentController = CTRL_GAME;
    }
    if ( i->btnStop.doAction ) i->btnStop.doAction = false;
    if ( i->btnPause.doAction ) i->btnPause.doAction = false;
    if ( i->btnReset.doAction ) {
        wspawn_count = 0;
        seed_count = 0;
        i->btnReset.doAction = false;
    }
    if ( i->btnSave.doAction ) {
        i->btnSave.doAction = false;
        std::string pathFileName = pop_file_dialog( DIALOG_SAVE, "\\patterns\\", window->getSystemHandle() );
        if ( pathFileName != "" ) {
            save_as_image( pathFileName, i->cellsInitial );
        }
    }
    if ( i->btnLoad.doAction ) {
        i->btnLoad.doAction = false;
        // TODO -> Figure out how to update seed and fountain count after loading
        std::string pathFileName = pop_file_dialog( DIALOG_OPEN, "\\patterns\\", window->getSystemHandle() );
        if ( pathFileName != "" ) {
            load_from_image( pathFileName, i->cellsInitial );
            updateCount();
            i->panX = 0.0f;
            i->panY = 0.0f;
            i->zoomLevel = 1.0f;
        }
    }
}

void ggEditor::draw( sf::RenderWindow* window )
{
    if ( *currentController != CTRL_EDITOR ) {
        return;
    }

    // nothing atm.
}

void ggEditor::updateCount()
{
    wspawn_count = 0;
    seed_count = 0;
    for ( unsigned int index=0; index<i->cellsInitial.size(); ++index ) {
        if ( i->cellsInitial[ index ].type == CELL_WSPAWN ) {
            ++ wspawn_count;
        }
        if ( i->cellsInitial[ index ].type == CELL_SEED ) {
            ++ seed_count;
        }
    }
}