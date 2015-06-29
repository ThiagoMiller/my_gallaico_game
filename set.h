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
void move_to( pos, pos, status* );
void init_arena( void );
cell *get_cell( pos );
void set_cell( pos, status*, TYPE_BODY );
void print_set( void );
void* handle_set( void* );
void unset_cell( pos, TYPE_BODY );



#endif // SET_H
