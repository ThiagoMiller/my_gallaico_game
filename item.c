#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


item *create_coin( void )
{
    item *coins = ( item* )calloc( MAX_COINS, sizeof( item ) );

    status *printable = (status*)malloc( sizeof( status ) ); //colocar no characters.c
    printable->body = COIN;
    printable->color = strdup( YELLOW );

    int i;
    for ( i = 0; i < MAX_COINS; i++ ) {
        ( coins + i )->pos = NULL;
        ( coins + i )->printable = printable;
        ( coins + i )->available = 1;
    }

    return coins;
}

item *create_fruits( void )
{
    item *fruits = ( item* )calloc( MAX_FRUITS, sizeof( item ) );
    status *printable;

    int i;
    for ( i = 0; i < MAX_FRUITS; i++ ) {
        ( fruits + i )->pos = NULL;
        ( fruits + i )->printable = (status*)malloc( sizeof( status ) );
        ( fruits + i )->printable->body = FRUIT;
        ( fruits + i )->printable->color = NULL;
        ( fruits + i )->available = 1;
    }

    return fruits;
}


