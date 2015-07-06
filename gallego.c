#include "gallego.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *state_color[];

hero *create_hero( pos *pos )
{
    hero *gallego = ( hero* )malloc( sizeof( hero ) );
   // gallego->flag = ( flag* )malloc( sizeof( flag ) );
    gallego->obj = ( obj* )malloc( sizeof( obj ) );
    gallego->obj->printable = ( status* )malloc( sizeof( status ) );

    gallego->obj->pos = pos;

   // gallego->flag->cagating = 0, gallego->flag->dead = 0, gallego->flag->limpping = 0;
    //gallego->flag->trying_cagate = 0, gallego->flag->wet = 0;

    gallego->obj->printable->body = HERO;
    gallego->obj->printable->color = state_color[DEFAULT_HERO_COLOR];

    gallego->cagating = 0;
    gallego->cagated = 0;
    gallego->limpping = 0;
    gallego->trapped = 0;
    gallego->eated_fruts = 0;
    gallego->score = 0;
    gallego->dead = 0;

    return gallego;
}
