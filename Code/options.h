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

#define GG_BACKGROUND_COLOUR sf::Color(52,123,4)

#define GG_DEFAULT_TICK_TIME 0.2f 
// GG_DEFAULT_TICK_TIME is in seconds.

#define GG_WSPAWN_MAX 1
#define GG_SEED_MAX 20

#define GG_RESTRICT_CELL_SELECT
// comment out for debug mode where you can palce all cell types

#endif