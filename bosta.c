#include "bosta.h"
#include "item.h"
#include "handle_set.h"
#include "jogo2.h"
#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>

static obj *bosta;

void init_bosta( void )
{
    bosta = create_item( _BOSTA_ );
}

void rebosteio( pos bosta_pos )
{
    obj *bosta_available = find_available( bosta, WIDTH * HEIGHT );

    if ( bosta_available->pos != NULL )
        free( bosta_available->pos );

    bosta_available->pos = ( pos* )malloc( sizeof( pos ) );
    *bosta_available->pos = bosta_pos;

    bosta_available->printable->body = BOSTA;

    set_cell( bosta_available, OBJ );
}

void down_bosta( status *b )
{
    b->body = L_BOSTA;
}
