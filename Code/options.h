// Part of GardenGrow.

#ifndef OPTIONS_H
#define OPTIONS_H

/*
    Declares program option macros.
*/

// PLATFORM
#define GG_WINDOWS
// I'll add more if/when I support them

#define GG_WINDOW_WIDTH 800
#define GG_WINDOW_HEIGHT 600
#define GG_WINDOW_CAPTION "Garden Grow"

#define GG_CONTROL_BAR_HEIGHT 30

#define GG_MOUSEWHEEL_ZOOM_SENSITIVITY 0.02f
#define GG_GRID_DRAW_THRESHOLD 500
// GG_GRID_DRAW_THRESHOLD the higher the value, the quicker the grid WONT be drawn on zoom out

#define GG_BACKGROUND_COLOUR sf::Color(52,123,4)

#define GG_DEFAULT_TICK_TIME 0.3f 
// GG_DEFAULT_TICK_TIME is in seconds.

#define GG_WSPAWN_MAX 1
#define GG_SEED_MAX 20000000

#define GG_RESTRICT_CELL_SELECT
// comment out for debug mode where you can palce all cell types

#define GG_BYTES_PER_CELL 12
// number of bytes needed per

#define GG_INT_CODE 5000
// ammount to add onto numbers before they're serialised to look better as an image 

#define GG_BOM 0xff000000
#define GG_BOM_WRONG 0x000000ff
// byte order marking

#define GG_MAX_CELL_DISPLACEMENT_CHAIN 10

#endif