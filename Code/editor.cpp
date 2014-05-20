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
    // nothing atm.
}

void ggEditor::tick( sf::Window* window )
{
    // nothing atm.
}

void ggEditor::draw( sf::RenderWindow* window )
{
    // nothing atm.
}