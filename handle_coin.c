#include "item.h"
#include "set.h"
#include "jogo2.h"
#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static obj *coins;

void init_coins( void )
{
    coins = create_item( _COIN_ );
}

void *handle_coins( void *a )
{
    obj *coin_available;
    while ( !is_hero_dead() ) {
        usleep( 9000000 );
        if ( ( coin_available = find_available( coins, MAX_COINS ) ) != NULL ) {
            if ( coin_available->pos != NULL )
                free( coin_available->pos );

            coin_available->pos = raffle();

            set_cell( coin_available, OBJ );
        }

    }

    return NULL;
}
