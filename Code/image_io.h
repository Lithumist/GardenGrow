// Part of GardenGrow.

#ifndef IMAGE_IO_H
#define IMAGE_IO_H

#include "cell.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

bool save_as_image( std::string argFilename, std::vector<ggCell>& argCells );
bool load_from_image ( std::string argFilename, std::vector<ggCell>& argVector );
sf::Color int_to_pixel( int number );
int pixel_to_int( sf::Color colour, bool swap );
void increment( unsigned int& x, unsigned int& y );

#endif