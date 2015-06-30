#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *limpping_color = BOLDGREEN RED_B;
static char *cagating_color = BOLDGREEN BROWN_B;
static char *default_color = BOLDGREEN;


hero *create_hero( pos *pos )
{
    hero *gallego = ( hero* )malloc( sizeof( hero ) );
   // gallego->flag = ( flag* )malloc( sizeof( flag ) );
    gallego->printable = ( status* )malloc( sizeof( status ) );

    gallego->pos = pos;

   // gallego->flag->cagating = 0, gallego->flag->dead = 0, gallego->flag->limpping = 0;
    //gallego->flag->trying_cagate = 0, gallego->flag->wet = 0;

    gallego->printable->body = HERO;
    gallego->printable->color = strdup( default_color );
    gallego->eated_fruts = 0;
    gallego->score = 0;
    gallego->dead = 0;

    return gallego;
}
