#include "item.h"
#include "set.h"
#include "jogo2.h"

#include <stdio.h>
#include <stdlib.h>

#define TRAP_THRESHOLD 18

static obj *traps;
static int traps_remain;

void init_trap( void )
{
    int i;

    traps = create_item( _TRAP_ );
    traps_remain = QNT_TRAPS;

    for ( i = 0; i < QNT_TRAPS; i++ ) {
        ( traps + i )->pos = raffle();
        ( traps + i )->printable->available = 0;
        set_cell( traps + i, OBJ );
    }
}

void minus_trap( void )
{
    if ( --traps_remain < TRAP_THRESHOLD ) {
        obj *trap_available;
        while ( ( trap_available = find_available( traps, QNT_TRAPS ) ) != NULL ) {
            free( trap_available->pos );
            trap_available->pos = raffle();
            set_cell( trap_available, OBJ );
            traps_remain++;
        }
    }
}





