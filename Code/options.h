// Part of GardenGrow.

#ifndef OPTIONS_H
#define OPTIONS_H

/*
    Declares program option macros.
*/

#define GG_WINDOW_WIDTH 800
#define GG_WINDOW_HEIGHT 600
#define GG_WINDOW_CAPTION "Garden Grow"

#define GG_CONTROL_BAR_HEIGHT 30

#define GG_MOUSEWHEEL_ZOOM_SENSITIVITY 0.02f
#define GG_GRID_DRAW_THRESHOLD 500
// GG_GRID_DRAW_THRESHOLD the higher the value, the quicker the grid WONT be drawn on zoom out

#define GG_BACKGROUND_COLOUR sf::Color(112,64,24)

#define GG_DEFAULT_TICK_TIME 1.0f 
// GG_DEFAULT_TICK_TIME is in seconds.

#endif