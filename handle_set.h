#ifndef HANDLE_SET_H
#define HANDLE_SET_H

#include "set.h"

void move_to( obj*, pos );
void init_arena( void );
cell *get_cell( pos );
void set_cell( obj*, TYPE_BODY );
void print_set( void );
void* handle_set( void* );
void unset_cell( pos*, TYPE_BODY );


#endif // HANDLE_SET_H
