#ifndef ITEM_H
#define ITEM_H

#include "characters.h"

#define MAX_COINS 10
#define MAX_FRUITS 5

typedef struct {
    pos *pos;
    status *printable;
    unsigned int available:1;
 } item;


item *create_coin( void );
item *create_fruits( void );

void init_fruits( void );
item *find_available( void );
void *handle_fruits( void *a );

#endif // ITEM_H
