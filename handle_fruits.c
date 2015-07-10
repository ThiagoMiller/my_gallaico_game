#include "item.h"
#include "set.h"
#include "jogo2.h"
#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_FRUIT_COLOR 5

static obj *fruits;

static char *fruit_colors[] = {
    RED,
    GREEN,
    YELLOW,
    WHITE,
    MAGENTA,
};

void init_fruits( void )
{
    fruits = create_item( _FRUIT_ );
}

void *handle_fruits( void *a )
{
    obj *fruit_available;
    while ( /*!is_hero_dead()*/1 ) {

        usleep( 5000000 );

        if ( ( fruit_available = find_available( fruits, MAX_FRUITS ) ) != NULL ) {
            if ( fruit_available->pos != NULL )
                free( fruit_available->pos );

            fruit_available->pos = raffle();

            //if ( fruit_available->printable->color != NULL )
             //   free( fruit_available->printable->color );

            fruit_available->printable->color = fruit_colors[ get_rand( NUM_FRUIT_COLOR ) ];

            set_cell( fruit_available, OBJ );
        }

    }

    return NULL;
}
