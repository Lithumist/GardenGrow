// Part of GardenGrow.

/*
    Implements the file dialog interface for windows
*/

#include "options.h"
#ifdef GG_WINDOWS

#include "file_dialog.h"
#include "funcs.h"
#include <Windows.h>
#include <SFML/Graphics.hpp>

std::string pop_file_dialog( ggDialogType argType, std::string argStartPath, sf::WindowHandle argHandle )
{
    // TODO -> Clean up with proper prefixes

    // initial bullshit
    char winFileName[ MAX_PATH ] = "";
    OPENFILENAME ofn;
    ZeroMemory( &ofn, sizeof(ofn) );

    // set file dialog options
    ofn.lStructSize = sizeof( ofn );
    ofn.hwndOwner = argHandle;
    ofn.lpstrFilter = "PNG Images (*.png)\0*.png\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = winFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrDefExt = "png";

    // set initial directory
    // this is actually quite unsafe. Not likely to be a problem though
    char pathWorkingDirectory [ MAX_PATH ] = "";
    char pathStartPath        [ MAX_PATH ] = "";
    strcpy( pathStartPath, argStartPath.c_str() );
    GetCurrentDirectory( MAX_PATH, pathWorkingDirectory );
    ofn.lpstrInitialDir = lstrcat( pathWorkingDirectory, pathStartPath );

    // deal with opening or saving a file
    if ( argType == DIALOG_OPEN ) {
        ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
        if ( !GetOpenFileName( &ofn ) ) {
            return "";
        }
    }
    if ( argType == DIALOG_SAVE ) {
        ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        if ( !GetSaveFileName( &ofn ) ) {
            return "";
        }
    }
    
    return (std::string)ofn.lpstrFile;
}

#endif