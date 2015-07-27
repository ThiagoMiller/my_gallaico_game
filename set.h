#ifndef SET_H
#define SET_H

#include "characters.h"


typedef struct {
    status *layer0;
    status *layer1;
} cell;

typedef cell cells[HEIGHT][WIDTH];
typedef cell (*arena)[ WIDTH ];

arena create_arena( void );



#endif // SET_H
