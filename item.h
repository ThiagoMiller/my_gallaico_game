#ifndef ITEM_H
#define ITEM_H

#include "characters.h"
#include "set.h"

typedef enum { _COIN_, _BOSTA_, _TRAP_, _FRUIT_ } ITEM;

obj *create_item( ITEM );
void clean_item( cell* );
obj *find_available( obj*, int );


#endif // ITEM_H
