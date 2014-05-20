// Part of GardenGrow.
#include "editor.h"
#include <iostream>

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
}

void ggEditor::onControl()
{
    std::cout << "Editor in control now.\n";
    // Modify interface options
    i->btnResetEnabled = true;
    i->tileSelectorEnabled = true;
}

void ggEditor::onEvent( sf::Window* window , sf::Event* e )
{
    if ( *currentController != CTRL_EDITOR ) {
        return;
    }

    // create cells on mouse click.
    if ( e->type == sf::Event::MouseButtonPressed && e->mouseButton.button == sf::Mouse::Left ) {
        if ( e->mouseButton.y > GG_CONTROL_BAR_HEIGHT ) {
            sf::Vector2i gridLocation = i->windowToGrid( e->mouseButton.x , e->mouseButton.y );
            // std::cout << "(" << gridLocation.x << ", " << gridLocation.y << ")\n";
            i->addCellInitial( ggCell(gridLocation.x, gridLocation.y, i->selectedType) );
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
}

void ggEditor::draw( sf::RenderWindow* window )
{
    if ( *currentController != CTRL_EDITOR ) {
        return;
    }

    // nothing atm.
}