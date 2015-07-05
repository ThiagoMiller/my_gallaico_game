#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *item_colors[] = {
    YELLOW,
    BROWN,
    BLUE
};

obj *create_item( ITEM item )
{
    int max_item;
    char body, *color;

    if ( item == _COIN_ ) {
        max_item = MAX_COINS;
        body = COIN;
        color = item_colors[_COIN_];
    }
    else if ( item == _FRUIT_ ) {
        max_item = MAX_FRUITS;
        body = FRUIT;
        color = NULL;
    }
    else if ( item == _TRAP_ ) {
        max_item = QNT_TRAPS;
        body = TRAP;
        color = item_colors[_TRAP_];
    }
    else {
        max_item = WIDTH * HEIGHT;
        body = BOSTA;
        color = item_colors[_BOSTA_];
    }

    obj *item_obj = ( obj* )calloc( max_item, sizeof( obj ) );

    int i;
    for ( i = 0; i < max_item; i++ ) {
        ( item_obj + i )->pos = NULL;
        ( item_obj + i )->printable = (status*)malloc( sizeof( status ) );
        ( item_obj + i )->printable->body = body;
        ( item_obj + i )->printable->color = color;
        ( item_obj + i )->printable->available = 1;
    }

    return item_obj;
}

obj *find_available( obj *item, int max_item )
{
    obj *available = NULL;

    int i;
    for ( i = 0; i < max_item; i++, item++ ) {
        if ( item->printable->available ) {
            available = item;
            available->printable->available = 0;
            break;
        }
    }

    return available;
}


void clean_item( cell *item )
{
    item->layer1->available = 1;
    item->layer1 = NULL;
}


