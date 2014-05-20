// Part of GardenGrow.
#include "cell.h"
#include "interface.h"

// Constructors
ggCell::ggCell() {
    ggCell( 0,0 );
}

ggCell::ggCell(int xgrid, int ygrid) :
 x (xgrid),
 y (ygrid)
{}


// Draw function
void ggCell::draw( ggInterface* i , sf::RenderWindow* window  )
{
    i->drawCell( window, x, y, sf::Color::Red );
}