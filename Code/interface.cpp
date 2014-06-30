// Part of GardenGrow.
#include "interface.h"
#include <iostream>
#include "options.h"

ggInterface::ggInterface()
{
    ctrlHeldDown, midHeldDownPrev = false;
    mouseXPrev, mouseYPrev = 0;
    gridVisible = true;
    zoomLevel = 1.0f;
    panX = 0.0f;
    panY = 0.0f;
    colGrid.a=              128; colGrid.r=              255; colGrid.g=              255; colGrid.b=             255;
    colControlBackground.a= 255; colControlBackground.r= 128; colControlBackground.g= 64; colControlBackground.b= 255;
    wheelSensitivity = GG_MOUSEWHEEL_ZOOM_SENSITIVITY;
    btnResetEnabled = false;
    tileSelectorEnabled = false;
    selectedType = CELL_SEED;
    flagHelp = false;
    helpPosX = 200;
    helpPosY = 200;
    helpScrollX = 1;
    helpScrollY = 1;
    selectorIndex = 0;
}

bool ggInterface::loadAssets()
{
    bool success = true;
    if ( !txtBtnControl.loadFromFile("data/btn_control.png") ) {
        success = false;
    }
    if ( !fontCaption.loadFromFile( "data/Minecrafter_3.ttf" ) ) {
        success = false;
    }
    if ( !txtHelp.loadFromFile( "patterns/meta.gg" ) ) {
        success = false;
    }
    return success;
}

void ggInterface::init()
{
    // set up buttons
    btnPlay.init( sf::IntRect(0,0,20,20) , sf::IntRect(0,20,20,20) , &txtBtnControl);
    btnPlay.setPosition( 20 , 5 );

    btnPause.init( sf::IntRect(20,0,20,20) , sf::IntRect(20,20,20,20) , &txtBtnControl);
    btnPause.setPosition( 44 , 5 );

    btnStop.init( sf::IntRect(40,0,20,20) , sf::IntRect(40,20,20,20) , &txtBtnControl);
    btnStop.setPosition( 68 , 5 );

    btnSave.init( sf::IntRect(60,0,60,20) , sf::IntRect(60,20,60,20) , &txtBtnControl );
    btnSave.setPosition( 100 , 5 );

    btnLoad.init( sf::IntRect(120,0,60,20) , sf::IntRect(120,20,60,20) , &txtBtnControl );
    btnLoad.setPosition( 164 , 5 );

    btnReset.init( sf::IntRect(180,0,60,20) , sf::IntRect(180,20,60,20) , &txtBtnControl );
    btnReset.setPosition( 228 , 5 );

    btnGrid.init( sf::IntRect(0,40,20,20) , sf::IntRect(0,60,20,20) , &txtBtnControl );
    btnGrid.setPosition( 298 , 5 );

    btnCentre.init( sf::IntRect(20,40,20,20) , sf::IntRect(20,60,20,20) , &txtBtnControl );
    btnCentre.setPosition( 322 , 5 );


    // set up texts
    textTest.setFont( fontCaption );
    textTest.setString( "Hello World!" );
    textTest.setCharacterSize( 32 );
    textTest.setColor( sf::Color::Magenta );

    textLimit.setFont( fontCaption );
    textLimit.setString( "no limit" );
    textLimit.setCharacterSize( 10 );
    textLimit.setColor( sf::Color::Green );
    textLimit.setPosition( 4, 585 );


    // Set up help
    sprHelp.setTexture( txtHelp );
}

void ggInterface::onEvent( sf::Window* window ,sf::Event* e )
{
    // update ctrl trigger
    ctrlHeldDown = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);

    // adjust zoom based on mouse wheel
    if ( ctrlHeldDown ) {
        if ( e->type == sf::Event::MouseWheelMoved ) {
            //std::cout << "mouse wheel delta: " << e->mouseWheel.delta << std::endl;
            float zoomDelta = (float)(e->mouseWheel.delta) * wheelSensitivity;
            zoomLevel += zoomDelta;
            if ( zoomLevel < 0.1f ) zoomLevel = 0.1f;
        }
    }
    else if (tileSelectorEnabled)
    {
        // adjust tile selection based on mouse wheel
        if ( e->type == sf::Event::MouseWheelMoved ) {
            selectedType = (ggCellType)(selectedType + e->mouseWheel.delta);
            #ifdef GG_RESTRICT_CELL_SELECT
            // Code to restrict cell choice.
            ggCellType allowedTypes [6] = { CELL_SEED, CELL_T_SAP, CELL_WSPAWN, CELL_PUSH, CELL_SPIN, CELL_LIGHT_0 };
            selectorIndex += e->mouseWheel.delta;
            if ( selectorIndex < 0 ) selectorIndex = 5;
            if ( selectorIndex > 5 ) selectorIndex = 0;
            selectedType = allowedTypes[ selectorIndex ];
            #endif

            // update cell limit caption
            if ( selectedType == CELL_WSPAWN ) {
                textLimit.setString( std::to_string(wspawn_count) + " / 1" );
                if ( wspawn_count >= 1 ) {
                    textLimit.setColor( sf::Color::Red );
                } else {
                    textLimit.setColor( sf::Color::Green );
                }
            } else {
                textLimit.setString( "no limit" );
                textLimit.setColor( sf::Color::Green );
            }
        }
    }

    if ( ctrlHeldDown && sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !midHeldDownPrev )
    {
        mouseXPrev = sf::Mouse::getPosition(*window).x;
        mouseYPrev = sf::Mouse::getPosition(*window).y;
    }

    // adjust pan based on mouse wheel
    if ( ctrlHeldDown ) {
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Middle) ) {
            int deltaX, deltaY;
            deltaX = mouseXPrev - sf::Mouse::getPosition(*window).x;
            deltaY = mouseYPrev - sf::Mouse::getPosition(*window).y;

            pan( (float)deltaX, (float)deltaY );

            mouseXPrev = sf::Mouse::getPosition(*window).x;
            mouseYPrev = sf::Mouse::getPosition(*window).y;
        }
    }

    // handle mouse click on grid
    if ( e->type == sf::Event::MouseButtonPressed && e->mouseButton.button == sf::Mouse::Left ) {
        //sf::Vector2i gridLocation = windowToGrid( e->mouseButton.x , e->mouseButton.y );
        //std::cout << "(" << gridLocation.x << ", " << gridLocation.y << ")\n";
        // add a cell
        //cells.push_back( ggCell(gridLocation.x, gridLocation.y) );
    }

    // update mid-previous trigger
    midHeldDownPrev = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

    // do buton events
    btnPlay.onEvent( window, e );
    btnPause.onEvent( window, e );
    btnStop.onEvent( window, e );
    btnSave.onEvent( window, e );
    btnLoad.onEvent( window, e );
    btnReset.onEvent( window, e );
    btnGrid.onEvent( window, e );
    btnCentre.onEvent( window, e );
}

void ggInterface::tick(sf::Window* window)
{
    ggCell::treeDrawList.clear();

    if ( selectedType == CELL_WSPAWN ) {
        if ( wspawn_count >= 1 ) {
            textLimit.setColor( sf::Color::Red );
        } else {
            textLimit.setColor( sf::Color::Green );
        }
    }

    // scroll help screen..
    if ( flagHelp ) {
        if ( helpPosX >= 700 )
            helpScrollX = -1;
        if ( helpPosX <= 0 )
            helpScrollX = 1;
        if ( helpPosY >= 525 )
            helpScrollY = -1;
        if ( helpPosY <= 0 )
            helpScrollY = 1;
        helpPosX += helpScrollX;
        helpPosY += helpScrollY;
        sprHelp.setPosition( (float)helpPosX, (float)helpPosY );
    }

    // tick buttons
    btnPlay.tick(window);
    btnPause.tick(window);
    btnStop.tick(window);
    btnSave.tick(window);
    btnLoad.tick(window);
    btnReset.tick(window);
    btnGrid.tick(window);
    btnCentre.tick(window);

    // handle interface only buttons
    if ( btnGrid.doAction ) {
        btnGrid.doAction = false;
        gridVisible = !gridVisible;
    }
    if ( btnReset.doAction ) {
        // bad hack, ggEditor does some other logic and sets the doAction flag false again.
        //btnReset.doAction = false;
        if ( btnResetEnabled ) {
            cellsInitial.clear();
        } else {
            btnReset.doAction = false;
        }
    }
    if ( btnCentre.doAction ) {
        btnCentre.doAction = false;
        zoomLevel = 1.0f;
        panX = 0.0f;
        panY = 0.0f;
    }
}


sf::Vector2i ggInterface::windowToGrid( int mouse_x , int mouse_y )
{
    sf::Vector2i result;
    sf::Vector2f working;

    working.x = (float)mouse_x;
    working.y = (float)mouse_y;

    // convert mouse coords to grid coords
    working.x = (float)(mouse_x) / (zoomLevel * 20.0f);
    working.y = (float)(mouse_y) / (zoomLevel * 20.0f);

    // apply pan
    working.x += panX / (zoomLevel * 20.0f);
    working.y += panY / (zoomLevel * 20.0f);

    // handle negative integer division effects
    if ( working.x < 0 ) working.x -= 1;
    if ( working.y < 0 ) working.y -= 1;

    // convert to int
    result.x = (int)working.x;
    result.y = (int)working.y;

    return result;
}

sf::Vector2f ggInterface::gridToWindow( float grid_x , float grid_y )
{
    sf::Vector2f result;
    sf::Vector2f working;

    working.x = (float)grid_x;
    working.y = (float)grid_y;

    // convert grid coords to mouse coords.
    // (top left)
    working.x = grid_x * (zoomLevel * 20.0f);
    working.y = grid_y * (zoomLevel * 20.0f);

    // convert to int
    result.x = working.x;
    result.y = working.y;

    return result;
}

void ggInterface::pan(float dx , float dy)
{
    panX += dx;
    panY += dy;
}

void ggInterface::draw( sf::RenderWindow* window , std::vector<ggCell>* cellVectorToDraw )
{
    // draw cells
    for ( unsigned int c=0; c<cellVectorToDraw->size(); ++c ) {
        cellVectorToDraw->at(c).draw( this, window );
    }

    // draw top cells
    ggCell::draw_top_things( window, this);

    // draw help
    if ( flagHelp ) {
        window->draw( sprHelp );
    }

    // draw grid
    if ( gridVisible ) {
        drawGrid( window );
    }

    // draw selected tile
    if (tileSelectorEnabled) {
        drawSelectedTile( window , sf::Mouse::getPosition(*window).x , sf::Mouse::getPosition(*window).y );
    }

    // draw interface background
    drawInterfaceBackground( window );

    // draw buttons
    window->draw( btnPlay );
    window->draw( btnPause );
    window->draw( btnStop );
    window->draw( btnSave );
    window->draw( btnLoad );
    window->draw( btnReset );
    window->draw( btnGrid );
    window->draw( btnCentre );

    // draw test text
    //window->draw( textTest );
    window->draw( textLimit );
}


void ggInterface::drawGrid( sf::RenderWindow* window )
{
    // calculate 
    // calculate line spacing according to zoom level
    float spacing = 20.0f * zoomLevel;
    if ( (int)spacing == 0 ) {
        // don't draw lines if we have to divide by 0
        return;
    }
    int lineCountHor = GG_WINDOW_WIDTH / (int)spacing + 1;
    int lineCountVer = GG_WINDOW_HEIGHT / (int)spacing + 1;

    // don't draw lines if there will be too many
    if ( lineCountHor == GG_WINDOW_WIDTH - GG_GRID_DRAW_THRESHOLD || lineCountVer == GG_WINDOW_HEIGHT - GG_GRID_DRAW_THRESHOLD ) {
        return;
    }

    // FUCKING GENIUS
    // Constants to translate the grid by the smallest
    // ... ammount possible to look like it's scrolling.
    // At least 1 hour was spent thinking this up.
    float panXConstant, panYConstant;
    panXConstant = fmod( (float)panX , spacing );
    panYConstant = fmod( (float)panY , spacing );
    // </god>

    // draw horisontal lines
    for ( float y=0; y<lineCountHor; ++y ) {
        // create line
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f( 0.0f , y*spacing-panYConstant ) , colGrid ) ,
            sf::Vertex(sf::Vector2f( GG_WINDOW_WIDTH , y*spacing-panYConstant ) , colGrid )
        };
        // draw it
        window->draw( line , 2 , sf::Lines );
    }

    // draw vertical lines
    for ( float x=0; x<lineCountHor; ++x ) {
        // create line
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f( x*spacing-panXConstant , 0.0f ) , colGrid ) ,
            sf::Vertex(sf::Vector2f( x*spacing-panXConstant , GG_WINDOW_HEIGHT ) , colGrid )
        };
        // draw it
        window->draw( line , 2 , sf::Lines );
    }
}

void ggInterface::drawInterfaceBackground( sf::RenderWindow* window )
{
    // draw control bar background
    sf::RectangleShape rectControlBar( sf::Vector2f(GG_WINDOW_WIDTH,GG_CONTROL_BAR_HEIGHT) );
    rectControlBar.setFillColor( colControlBackground );

    // draw all
    window->draw( rectControlBar );
}

void ggInterface::drawCell( sf::RenderWindow* window, int xpos, int ypos, sf::Color col )
{
    // get grid pos
    sf::Vector2f gridPos = gridToWindow( (float)xpos , (float)ypos );

    // draw rectangle
    sf::RectangleShape cell(sf::Vector2f( zoomLevel*20.0f , zoomLevel*20.0f));
    cell.setPosition( gridPos.x-panX, gridPos.y-panY );
    cell.setFillColor( col );
    window->draw( cell );
}

void ggInterface::drawSelectedTile( sf::RenderWindow* window, int mx, int my )
{
    // create and draw cell
    sf::Vector2i g = windowToGrid( mx , my );
    ggCell cell(g.x,g.y,selectedType);
    cell.draw( this , window, false );
}

void ggInterface::addCell( ggCell cell ) {
    cellsUpdated.push_back( cell );
}

void ggInterface::flipCellBuffers()
{
    cellsCurrent.clear();
    cellsCurrent = cellsUpdated;
    cellsUpdated.clear();
}

void ggInterface::addCellInitial( ggCell cell ) {
    cellsInitial.push_back( cell );
}

ggCell ggInterface::delCellInitial( int x, int y )
{
    for ( unsigned int c=0; c<cellsInitial.size(); ++c ) {
        if ( cellsInitial[c].get_cur_pos_x() == x && cellsInitial[c].get_cur_pos_y() == y )
        {
            // get a copy before deleting
            ggCell cellCopy = cellsInitial[c];
            cellsInitial.erase( cellsInitial.begin() + c );
            return cellCopy;
        }
    }
    return ggCell( 0, 0, CELL_ANY );
}

void ggInterface::loadInitialCellPattern() {
    // copy ready to start game
    cellsCurrent = cellsInitial;
}


// ---
// search functions
// ---

int ggInterface::countCellsAt(int x, int y)
{
    int count = 0;
    for ( unsigned int c=0; c<cellsCurrent.size(); ++c ) {
        if ( cellsCurrent[c].get_cur_pos_x() == x && cellsCurrent[c].get_cur_pos_y() == y )
        {
            ++ count;
        }
    }
    return count;
}

void ggInterface::deleteCellsAt(int x, int y)
{
    std::cout <<  "DEPRECIATED FUNCTION ggInterface::deleteCellsAt()" ;
    /*
    for ( unsigned int c=0; c<cellsCurrent.size(); ++c ) {
        if ( cellsCurrent[c].get_cur_pos_x() == x && cellsCurrent[c].get_cur_pos_y() == y )
        {
            cellsCurrent[c].del = true;
        }
    }
    */

}

// Might want to rewrite this to make less wtf..
// TODO -> Test when ty is default.
ggCell* ggInterface::cellAt(int x, int y, ggCellType ty, std::vector<ggCell>* vec)
{
    if ( vec == NULL ) {
        vec = &cellsCurrent;
    }

    for ( unsigned int c=0; c<vec->size(); ++c ) {
        if ( (*vec)[c].get_cur_pos_x() == x && (*vec)[c].get_cur_pos_y() == y )
        {
            if ( ty == CELL_ANY ) {
                return &(*vec)[c];
            } else {
                if ( (*vec)[c].type == ty ) {
                    return &(*vec)[c];
                }
            }
        }
    }
    // couldn't find any cell
    return NULL;
}

int ggInterface::countCellsAdjacent(int x, int y, ggCellType ty)
{
    // call the overload
    std::array<ggCell*, 8> ptrListDefault;
    return countCellsAdjacent( x , y , ptrListDefault , ty );
}

int ggInterface::countCellsAdjacent(int x, int y, std::array<ggCell*, 8>& ptrList, ggCellType ty)
{
    int count = 0;
    if ( ptrList[0] = cellAt(x-1,y,ty) ) { if ( !ptrList[0]->disable ) ++ count; }
    if ( ptrList[1] = cellAt(x+1,y,ty) ) { if ( !ptrList[1]->disable ) ++ count; }
    if ( ptrList[2] = cellAt(x,y-1,ty) ) { if ( !ptrList[2]->disable ) ++ count; }
    if ( ptrList[3] = cellAt(x,y+1,ty) ) { if ( !ptrList[3]->disable ) ++ count; }
    if ( ptrList[4] = cellAt(x-1,y-1,ty) ) { if ( !ptrList[4]->disable ) ++ count; }
    if ( ptrList[5] = cellAt(x-1,y+1,ty) ) { if ( !ptrList[5]->disable ) ++ count; }
    if ( ptrList[6] = cellAt(x+1,y-1,ty) ) { if ( !ptrList[6]->disable ) ++ count; }
    if ( ptrList[7] = cellAt(x+1,y+1,ty) ) { if ( !ptrList[7]->disable ) ++ count; }
    return count;
}

bool ggInterface::handleOverlap( ggCell* argTop, int argDx, int argDy, unsigned int argCount )
{
    /*
    ggCell* cellUnder = cellAt( argTop->gx(), argTop->gy() );
    if ( cellUnder && !isMovable( *cellUnder ) ) {
        argTop->dx = 0;
        argTop->dy = 0;
        return false;
    }
    if ( cellUnder ) {
        if ( argCount <= GG_MAX_CELL_DISPLACEMENT_CHAIN /* && !cellUnder->full  ) {
            cellUnder->dx = argDx;
            cellUnder->dy = argDy;
            ++ argCount;
            if ( !handleOverlap( cellUnder, argDx, argDy, argCount ) ) {
                argTop->dx = 0;
                argTop->dy = 0;
                return false;
            }
            return true;
        }
        argTop->dx = 0;
        argTop->dy = 0;
        return false;
    }
    */
    return true;
}

bool ggInterface::can_push( ggCell* argCell, _ggDirection argDir, unsigned int argCount )
{
    // check we haven't gone too far into the chain
    if ( argCount + 1 > GG_MAX_CELL_DISPLACEMENT_CHAIN ) {
        return false;
    }

    // calculate position of next cell in the chain
    int nextX, nextY;
    if ( argDir == DIRECTION_RIGHT ) {
        nextX = argCell->get_cur_pos_x() + 1;
        nextY = argCell->get_cur_pos_y();
    }
    if ( argDir == DIRECTION_LEFT ) {
        nextX = argCell->get_cur_pos_x() - 1;
        nextY = argCell->get_cur_pos_y();
    }
    if ( argDir == DIRECTION_DOWN ) {
        nextX = argCell->get_cur_pos_x();
        nextY = argCell->get_cur_pos_y() + 1;
    }
    if ( argDir == DIRECTION_UP ) {
        nextX = argCell->get_cur_pos_x();
        nextY = argCell->get_cur_pos_y() - 1;
    }
    
    // find the cell in that position
    ggCell* nextCell = cellAt( nextX, nextY );

    // if it doesn't exist then we can move
    if ( !nextCell ) {
        return true;
    } else {
        // if it exists
        // check if it's a movable type
        if ( nextCell->is_movable() ) {
            // check that we can move beyond that cell
            return can_push( nextCell, argDir, argCount + 1 );
        } else {
            return false;
        }
    }
}