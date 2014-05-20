// Part of GardenGrow.
#include "editor.h"

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
    // nothing atm.
}

void ggEditor::onEvent( sf::Window* window , sf::Event* e )
{
    // create cells on mouse click.
    if ( e->type == sf::Event::MouseButtonPressed && e->mouseButton.button == sf::Mouse::Left ) {
        if ( e->mouseButton.y > GG_CONTROL_BAR_HEIGHT ) {
            sf::Vector2i gridLocation = i->windowToGrid( e->mouseButton.x , e->mouseButton.y );
            // std::cout << "(" << gridLocation.x << ", " << gridLocation.y << ")\n";
            i->addCell( ggCell(gridLocation.x, gridLocation.y, CELL_SEED) );
        }
    }
}

void ggEditor::tick( sf::Window* window )
{
    // nothing atm.
}

void ggEditor::draw( sf::RenderWindow* window )
{
    // nothing atm.
}