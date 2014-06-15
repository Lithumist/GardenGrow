// Part of GardenGrow.

/*
    Creates window and starts game.
*/

#include <SFML/Graphics.hpp>

#include "options.h"
#include "types.h"
#include "interface.h"
#include "editor.h"
#include "game.h"
#include "funcs.h"
#include "image_io.h"
#include "file_dialog.h"
#include <string>
#include <iostream>
#include <ctime>
#include <sstream>

int main()
{
    srand( time(0) );
    sf::RenderWindow gameWindow( sf::VideoMode (GG_WINDOW_WIDTH,GG_WINDOW_HEIGHT) , GG_WINDOW_CAPTION , sf::Style::Titlebar | sf::Style::Close );

    // Pointer to whcih cell vector to render
    std::vector<ggCell>* cr;

    // Set up background to render
    sf::RectangleShape background(sf::Vector2f( GG_WINDOW_WIDTH , GG_WINDOW_HEIGHT ));
    background.setFillColor( GG_BACKGROUND_COLOUR );

    // Create interface
    ggInterface Interface;
    Interface.loadAssets();
    ggCell::loadTexture();
    Interface.init();

    // Create controller variable
    ggInterfaceController Control = CTRL_EDITOR;
    ggInterfaceController ControlPrev = CTRL_EDITOR;

    // Create editor
    ggEditor Editor( &Interface , &Control );
    Editor.onControl();

    // Create game
    ggGame Game( &Interface , &Control );
    
    // test int-pixel conversion functions
    while ( 0 ) {
    out("\nInput Num: 1996\n");
    sf::Color col;
    int inNum = 1996;
    col = int_to_pixel( inNum );
    out("r: " + std::to_string(col.r) + "\n");
    out("g: " + std::to_string(col.g) + "\n");
    out("b: " + std::to_string(col.b) + "\n");
    out("a: " + std::to_string(col.a) + "\n");
    int outNum = pixel_to_int( col, false );
    out("Output Num: " + std::to_string(outNum) + "\n");
    }

    // test file dialog function
    while( 0 ) {
    std::string path = pop_file_dialog( DIALOG_SAVE, "\\patterns\\", gameWindow.getSystemHandle() );
    out("path=" + path + "\n");
    }

    // Game loop
    while (gameWindow.isOpen())
    {
        // events
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
            
            // take screenshots.
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    sf::Image screen = gameWindow.capture();
                    std::string fname = "screenshots/";
                    time_t now = time(0);
                    tm* ltm = localtime(&now);
                    std::stringstream ss;
                    ss << ltm->tm_year << ltm->tm_mon+1 << ltm->tm_mday << " " << ltm->tm_hour << ltm->tm_min << ltm->tm_sec;
                    fname += ss.str() + ".png";
                    if ( screen.saveToFile( fname ) ) {
                        out("Saved \"" + fname + "\"\n");
                    }
                }
            }
            
            Interface.onEvent( &gameWindow, &event );
            Editor.onEvent( &gameWindow, &event );
            Game.onEvent( &gameWindow, &event );
        }

        // tick
        Interface.tick( &gameWindow );
        // editor
        ControlPrev = Control;
        Editor.tick( &gameWindow );
        if (ControlPrev != Control) {
            Game.onControl();
        }
        // game
        ControlPrev = Control;
        Game.tick( &gameWindow );
        if (ControlPrev != Control) {
            Editor.onControl();
        }

        // decide whcih cell vector to draw
        if ( Control == CTRL_EDITOR ) {
            cr = Interface.cellsPattern;
        } else if ( Control == CTRL_GAME ) {
            cr = Interface.cellsScreen;
        }

        // draw
        gameWindow.clear();
        gameWindow.draw( background );
        Interface.draw( &gameWindow , cr );
        Editor.draw( &gameWindow );
        Game.draw( &gameWindow );
        gameWindow.display();
    }

    return 0;
}