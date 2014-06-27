// Part of GardenGrow.
#include "cell.h"
#include "interface.h"
#include "types.h"
#include <SFML/System.hpp>

sf::Texture ggCell::txtCell;

// Constructors
ggCell::ggCell() {
    ggCell( 0,0,CELL_SEED );
}

ggCell::ggCell(int argXGrid, int argYGrid, ggCellType argType) :
 curX   (argXGrid),
 curY   (argYGrid),
 newX   (argXGrid),
 newY   (argYGrid),
 type   (argType),
 disable(false),
 full   (false),
 watered(false),
 AffectCount(0)
{}

void ggCell::loadTexture() {
    txtCell.loadFromFile( "data/cell.png" );
}

void ggCell::drawTile( int index, sf::RenderWindow* window, ggInterface* i, bool nopan )
{
    sf::IntRect bounds;
    bounds.left = (index % 10) * 20;
    bounds.top = (index / 10) * 20;
    bounds.width = 20;
    bounds.height = 20;
    sf::Sprite sprTile( txtCell, bounds );
    sprTile.setScale( i->zoomLevel, i->zoomLevel );
    float px, py;
    if ( nopan == true ) {
        px = 0.0f;
        py = 0.0f;
    } else {
        px = i->panX;
        py = i->panY;
    }
    sf::Vector2f pos = i->gridToWindow( (float)get_cur_pos_x() , (float)get_cur_pos_y() );
    pos.x -= px;
    pos.y -= py;
    sprTile.setPosition( pos );
    
    window->draw( sprTile );

}


// Draw function
void ggCell::draw( ggInterface* i , sf::RenderWindow* window , bool nopan )
{
    if       ( type >= 0 && type <= 3) // first few types
    {
        drawTile( type, window, i, nopan );
    }
    else if  ( type == 4 ) // flowers
    {
        drawTile( 4 + (rand()%5), window, i, nopan );
    }
    else if  ( type >= 5 ) // other types
    {
        drawTile( 5+type, window, i, nopan );
    }
}

bool ggCell::is_movable()
{
    if ( type == CELL_PUSH ) return false;
    if ( type == CELL_SPIN ) return false;
    if ( type == CELL_WSPAWN  ) return false;
    if ( full ) return false;
    return true;
}