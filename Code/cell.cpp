// Part of GardenGrow.
#include "cell.h"
#include "interface.h"
#include "types.h"

// Constructors
ggCell::ggCell() {
    ggCell( 0,0,CELL_SEED );
}

ggCell::ggCell(int xgrid, int ygrid, ggCellType typ) :
 x      (xgrid),
 y      (ygrid),
 type   (typ)
{}


// Draw function
void ggCell::draw( ggInterface* i , sf::RenderWindow* window  )
{
    i->drawCell( window, x, y, sf::Color::Red );
}