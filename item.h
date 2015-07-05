#ifndef ITEM_H
#define ITEM_H

#include "characters.h"
#include "set.h"

#define MAX_COINS 10
#define MAX_FRUITS 5

typedef enum { _COIN_, _BOSTA_, _TRAP_, _FRUIT_ } ITEM;

obj *create_item( ITEM );
void clean_item( cell* );

void init_fruits( void );
void init_coins( void );

obj *find_available( obj*, int );
void *handle_fruits( void* );
void *handle_coins( void* );


#endif // ITEM_H
