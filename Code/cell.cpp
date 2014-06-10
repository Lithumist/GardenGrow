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

ggCell::ggCell(int xgrid, int ygrid, ggCellType typ) :
 x      (xgrid),
 y      (ygrid),
 type   (typ),
 disable(false)
{}

void ggCell::loadTexture() {
    txtCell.loadFromFile( "data/cell.png" );
}

void ggCell::drawTile( int index, sf::RenderWindow* window, ggInterface* i )
{
    sf::IntRect bounds;
    bounds.left = (index % 10) * 20;
    bounds.top = (index / 10) * 20;
    bounds.width = 20;
    bounds.height = 20;
    sf::Sprite sprTile( txtCell, bounds );
    sf::Vector2f pos = i->gridToWindow( (float)x , (float)y );
    sprTile.setPosition( pos );
    
    window->draw( sprTile );

}


// Draw function
void ggCell::draw( ggInterface* i , sf::RenderWindow* window  )
{
    if       ( type >= 0 && type <= 3) // first few types
    {
        drawTile( type, window, i );
    }
    else if  ( type == 4 ) // flowers
    {
        drawTile( 4 + (rand()%5), window, i );
    }
    else if  ( type >= 5 ) // last few types
    {
        drawTile( 5 + type, window, i );
    }
}