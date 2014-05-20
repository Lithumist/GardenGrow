// Part of GardenGrow.

#ifndef TYPES_H
#define TYPES_H

/*
    Declares basic enum types
*/

enum ggCellType             { CELL_STONE , 
                              CELL_WATER , 
                              CELL_SEED ,
                              CELL_SPROUT , 
                              CELL_PLANT , 
                              CELL_FLOWER , 
                              CELL_BABY , 
                              CELL_TREE , 
                              CELL_OAK
                            };

enum ggInterfaceController  { CTRL_EDITOR , CTRL_GAME };

#endif