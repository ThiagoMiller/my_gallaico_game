#include "item.h"
#include "set.h"
#include "jogo2.h"
#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_FRUIT_COLOR 6

static item *fruits;

static char *fruit_colors[] = {
    RED,
    GREEN,
    YELLOW,
    WHITE,
    BLUE,
    MAGENTA,
};

void init_fruits( void )
{
    fruits = create_fruits();
}

item *find_available( void )
{
    item *available = NULL;

    int i;
    for ( i = 0; i < MAX_FRUITS; i++ ) {
        if ( ( fruits + i )->available ) {
            available = ( fruits + i );
            available->available = 0;
            break;
        }
    }

    return available;
}

void *handle_fruits( void *a )
{
    item *fruit_available;
    while ( !is_hero_dead() ) {

        usleep( 5000000 );

        if ( ( fruit_available = find_available() ) != NULL ) {
            if ( fruit_available->pos != NULL )
                free( fruit_available->pos );

            fruit_available->pos = raffle();

            if ( fruit_available->printable->color != NULL )
                free( fruit_available->printable->color );

            fruit_available->printable->color = strdup( fruit_colors[ get_rand( NUM_FRUIT_COLOR ) ] );

            set_cell( *fruit_available->pos, fruit_available->printable, OBJ );
        }

    }
    printf( "fruit\n" );

    return NULL;
}
