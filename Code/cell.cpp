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
    switch ( type )
    {
        case CELL_STONE:
            i->drawCell( window, x, y, sf::Color( 96,96,96 ) );
        break;

        case CELL_WATER:
            i->drawCell( window, x, y, sf::Color( 32,128,128 ) );
        break;

        case CELL_SEED:
            i->drawCell( window, x, y, sf::Color( 230,128,128 ) );
        break;

        case CELL_SPROUT:
            i->drawCell( window, x, y, sf::Color( 96,255,96 ) );
        break;

        case CELL_PLANT:
            i->drawCell( window, x, y, sf::Color( 64,200,64 ) );
        break;

        case CELL_FLOWER:
            i->drawCell( window, x, y, sf::Color( 255,64,64 ) );
        break;

        case CELL_BABY:
            i->drawCell( window, x, y, sf::Color( 255,255,64 ) );
        break;

        case CELL_TREE:
            i->drawCell( window, x, y, sf::Color( 160,130,64 ) );
        break;

        case CELL_OAK:
            i->drawCell( window, x, y, sf::Color( 32,32,255 ) );
        break;
    }
}