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

                              CELL_POWER   = 5, 
                              CELL_PUSH    = 6, 
                              CELL_SPIN    = 7, 
                              CELL_WSPAWN  = 8,
                              CELL_DEAD    = 9,

                              CELL_T_LEFT  = 10,
                              CELL_T_MID   = 11,
                              CELL_T_RIGHT = 12,
                              CELL_T_STUMP = 20,
                              CELL_T_BASE  = 21,
                              CELL_T_SAP   = 22,

                              CELL_LIGHT_0 = 23,
                              CELL_LIGHT_1 = 24
                            };

enum ggInterfaceController  { CTRL_EDITOR , CTRL_GAME };

enum _ggDirection { DIRECTION_RIGHT = 1,
                    DIRECTION_LEFT  = 2,
                    DIRECTION_DOWN  = 3,
                    DIRECTION_UP    = 4
                  };
inline int direction_to_x( _ggDirection argDir ) {
    if ( argDir == DIRECTION_RIGHT ) {
        return 1;
    } else if ( argDir == DIRECTION_LEFT ) {
        return -1;
    } else {
        return 0;
    }
}
inline int direction_to_y( _ggDirection argDir ) {
    if ( argDir == DIRECTION_DOWN ) {
        return 1;
    } else if ( argDir == DIRECTION_UP ) {
        return -1;
    } else {
        return 0;
    }
}

/*
struct _ggMoveInfo {
    
};
*/

#endif