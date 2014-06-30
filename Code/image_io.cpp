// Part of GardenGrow.

/*
    Defines functions to save and load save states as images.
*/

#include "image_io.h"
#include "options.h"
#include "funcs.h"
#include "intrin.h" // vc++ specific

bool save_as_image( std::string argFilename, std::vector<ggCell>& argCells )
{
    // saves a vector of cells as an image.
    // could pack more into each pixel but it's not necessary

    // calculate the image size needed
    unsigned int dimWidth = 128;
    unsigned int hlpBytesNeeded = GG_BYTES_PER_CELL*argCells.size();
    unsigned int dimHeight = 18 + (hlpBytesNeeded/4)/128;
    out("height is " + std::to_string( dimHeight ));

    // load template header
    sf::Image imgHeader;
    if ( !imgHeader.loadFromFile("../data/pattern_header.png") ) {
        return false;
    }

    // create new image with header
    sf::Image imgPattern;
    imgPattern.create( dimWidth, dimHeight, sf::Color(0,0,0));
    imgPattern.copy( imgHeader, 0, 0 );

    // prepare for writing
    unsigned int posX = 0;
    unsigned int posY = 16;

    // write byte order marking
    imgPattern.setPixel( posX, posY, int_to_pixel( GG_BOM ) );
    increment( posX, posY );

    // write cell count
    imgPattern.setPixel( posX, posY, int_to_pixel( argCells.size() ) );
    increment( posX, posY );

    // write all pixels
    for ( unsigned int index=0; index<argCells.size(); ++index ) {
        // generate colours
        sf::Color colX, colY, colType;
        colX = int_to_pixel( argCells[index].get_cur_pos_x() );
        colY = int_to_pixel( argCells[index].get_cur_pos_y() );
        colType = int_to_pixel( argCells[index].type );
        // write to image
        imgPattern.setPixel( posX, posY, colX );
        increment( posX, posY );
        imgPattern.setPixel( posX, posY, colY );
        increment( posX, posY );
        imgPattern.setPixel( posX, posY, colType );
        increment( posX, posY );
        // output colours used
        out("[" + std::to_string(index) + "] ");
        out("X    : ( " + std::to_string(colX.r) + ", " + std::to_string(colX.g) + ", " + std::to_string(colX.b) + ", " + std::to_string(colX.a) + " )\n");
        out("[" + std::to_string(index) + "] ");
        out("Y    : ( " + std::to_string(colY.r) + ", " + std::to_string(colY.g) + ", " + std::to_string(colY.b) + ", " + std::to_string(colY.a) + " )\n");
        out("[" + std::to_string(index) + "] ");
        out("Type : ( " + std::to_string(colType.r) + ", " + std::to_string(colType.g) + ", " + std::to_string(colType.b) + ", " + std::to_string(colType.a) + " )\n");
    }

    // save image
    imgPattern.saveToFile( argFilename );
    return true;

}

bool load_from_image ( std::string argFilename, std::vector<ggCell>& argVector )
{
    // constructs a vector of ggCells from an image file

    // open image file
    sf::Image imgPattern;
    if ( !imgPattern.loadFromFile( argFilename ) ) {
        return false;
    }

    // prepare vector
    argVector.clear();

    // prepare for reading
    unsigned int posX = 0;
    unsigned int posY = 16;
    bool flagSwapOrder = false;

    // read byte order
    int inBom = pixel_to_int( imgPattern.getPixel( posX, posY ), false );
    increment( posX, posY );
    if ( inBom == GG_BOM_WRONG ) {
        flagSwapOrder = true;
    }

    // read cell count
    unsigned int numCells = pixel_to_int( imgPattern.getPixel( posX, posY ), false );
    increment( posX, posY );

    // read all cells into vector
    for ( unsigned int index = 0; index < numCells; ++index ) {
        // read in values
        int inX = 0;
        int inY = 0;
        int inType = 0;
        inX = pixel_to_int( imgPattern.getPixel( posX, posY ), flagSwapOrder );
        increment( posX, posY );
        inY = pixel_to_int( imgPattern.getPixel( posX, posY ), flagSwapOrder );
        increment( posX, posY );
        inType = pixel_to_int( imgPattern.getPixel( posX, posY ), flagSwapOrder );
        increment( posX, posY );
        // construct and add cell
        ggCell cellNew( inX, inY, (ggCellType)inType );
        argVector.push_back( cellNew );
    }
    return true;
}

sf::Color int_to_pixel( int number ) {
    // code number to look better as an image
    number += GG_INT_CODE;
    // convert to pixel
    int r_single = number & 0xff000000;
    int g_single = number & 0x00ff0000;
    int b_single = number & 0x0000ff00;
    int a_single = number & 0x000000ff;
    int r = r_single >> 24;
    int g = g_single >> 16;
    int b = b_single >> 8;
    int a = a_single;
    sf::Color colour((unsigned char)r,(unsigned char)g,(unsigned char)b,(unsigned char)a);
    return colour;
}

int pixel_to_int( sf::Color colour, bool swap ) {
    int r = (int) colour.r;
    int g = (int) colour.g;
    int b = (int) colour.b;
    int a = (int) colour.a;
    int number = r << 24;
    number = number | g << 16;
    number = number | b << 8;
    number = number | a;
    if ( swap ) {
        number = (int)_byteswap_ulong( number );
    }
    // decode
    number -= GG_INT_CODE;
    return number;
}

void increment( unsigned int& x, unsigned int& y ) {
    ++x;
    if ( x >= 128 ) {
        x = 0;
        ++y;
    }
}