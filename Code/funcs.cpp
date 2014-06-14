// Part of GardenGrow.

/*
    Defines all the functions in funcs.h
*/

#include "funcs.h"
#include <sstream>

void out ( std::string msg ) {
    // wrap to standard output stream
    std::cout << msg;
}

std::string uint_to_string( unsigned int a ) {
    std::stringstream ss;
    ss << a;
    return ss.str();
}