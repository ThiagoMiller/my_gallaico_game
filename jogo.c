#include "jogo2.h"
#include "handle_set.h"
#include "handle_hero.h"
#include "handle_monster.h"
#include "handle_coin.h"
#include "handle_fruits.h"
#include "bosta.h"
#include "trap.h"
#include "stat.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

void build_set( void )
{
    init_arena();

    init_hero();
    init_monster();
    init_fruits();
    init_coins();
    init_bosta();
    init_trap();
    init_stat_game();

    print_set();
}

pos create_pos( int row, int col )
{
    pos new_pos = { row, col };
    return new_pos;
}

pos *raffle( void )
{
    pos *position = ( pos* )malloc( sizeof( pos ) );
    pos pos_rand;

    cell *printable;
    status *body0, *body1;

    while ( 1 ) {
        pos_rand.col = get_rand( WIDTH ), pos_rand.row = get_rand( HEIGHT );
        printable = get_cell( pos_rand );

        body0 = printable->layer0;
        body1 = printable->layer1;

        if (  body0 != NULL || body1 != NULL )
            continue;

        *position = pos_rand; //
		break;
    }

    return position;
}

int get_rand( int untill )
{
    static int inicialized = 0;
    if ( !inicialized ) {
        srand(time(NULL));
        inicialized = 1;
    }

    return rand() % untill;
}
