// Part of GardenGrow.

#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "options.h"
#include "button.h"
#include "cell.h"
#include <vector>
#include <array>

/*
    Declares a class for manipulating the 'editor-like' interface.
*/

class ggCell;

class ggInterface
{
    friend class ggCell;
private:
    // assets
    sf::Texture txtBtnControl;

    // triggers and event variables
    bool ctrlHeldDown, midHeldDownPrev;
    int mouseXPrev, mouseYPrev;

    // colours
    sf::Color colGrid;
    sf::Color colControlBackground;

    // control flags
    bool gridVisible;

    // helper functions
    void drawGrid( sf::RenderWindow* window );
    void drawInterfaceBackground( sf::RenderWindow* window );
    void drawCell( sf::RenderWindow* window, int xpos, int ypos, sf::Color col );
    void drawSelectedTile( sf::RenderWindow* window, int mx, int my );

public:
    // cell list
    std::vector<ggCell> cellsCurrent;
    std::vector<ggCell> cellsUpdated;
    std::vector<ggCell> cellsInitial;

    // zoom and pan variables
    float zoomLevel;
    float panX, panY;
    float wheelSensitivity;

    // tile placing variables and flags
    bool tileSelectorEnabled;
    ggCellType selectedType;

    // buttons
    ggButton btnPlay, btnPause, btnStop;
    ggButton btnSave, btnLoad, btnReset;
    ggButton btnGrid, btnCentre;
    bool btnResetEnabled;

    // functions
    ggInterface();

    bool loadAssets(); // first call this
    void init(); // then this

    void tick( sf::Window* window );
    void onEvent( sf::Window* window , sf::Event* e );
    void draw( sf::RenderWindow* window , std::vector<ggCell>* cellVectorToDraw );

    void pan( float dx , float dy );

    sf::Vector2i windowToGrid( int mouse_x , int mouse_y );
    sf::Vector2f gridToWindow( float grid_x , float grid_y );

    void addCell( ggCell cell );
    void addCellInitial( ggCell cell );
    ggCell delCellInitial( int x, int y );
    void loadInitialCellPattern();
    void flipCellBuffers();

    int countCellsAt(int x, int y);
    void deleteCellsAt(int x, int y);
    ggCell* cellAt(int x, int y, ggCellType ty=CELL_ANY, std::vector<ggCell>* vec=NULL);
    int countCellsAdjacent(int x, int y, ggCellType ty=CELL_ANY);
    int countCellsAdjacent(int x, int y, std::array<ggCell*, 8>& ptrList, ggCellType ty=CELL_ANY);

    bool handleOverlap( ggCell* argTop, int argDx, int argDy, unsigned int argCount=0 ); // depreciated
    bool can_push( ggCell* argCell, _ggDirection argDir, unsigned int argCount=0 );

};

#endif