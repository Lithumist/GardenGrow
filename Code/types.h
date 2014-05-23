// Part of GardenGrow.

#ifndef TYPES_H
#define TYPES_H

/*
    Declares basic enum types
*/

enum ggCellType             { CELL_ANY    = 0, 

                              CELL_STONE  = 1, 
                              CELL_WATER  = 2, 
                              CELL_SEED   = 3, 

                              CELL_SPROUT = 4, 
                              CELL_PLANT  = 5, 
                              CELL_FLOWER = 6, 
                              CELL_TREE   = 7, 
                            };

enum ggInterfaceController  { CTRL_EDITOR , CTRL_GAME };

#endif