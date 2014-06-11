// Part of GardenGrow.

#ifndef TYPES_H
#define TYPES_H

/*
    Declares basic enum types
*/

enum ggCellType             { CELL_ANY     = 0, 

                              CELL_STONE   = 1, 
                              CELL_WATER   = 2, 
                              CELL_SEED    = 3, 
                              CELL_FLOWER  = 4, 

                              CELL_POWER_1 = 5, 
                              CELL_POWER_0 = 6,
                              CELL_PUSH    = 7, 
                              CELL_SPIN    = 8, 
                              CELL_WSPAWN  = 9
                            };

enum ggInterfaceController  { CTRL_EDITOR , CTRL_GAME };

#endif