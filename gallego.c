#include <gallego.h>


hero *create_hero( pos *pos )
{
    hero *gallego = ( hero* )malloc( sizeof( hero ) );
    gallego->flag = ( flag* )malloc( sizeof( flag ) );
    gallego->printable = ( status* )malloc( sizeof( status ) );

    gallego->pos = pos;

    gallego->flag->cagating = 0, gallego->flag->dead = 0, gallego->flag->limpping = 0;
    gallego->flag->trying_cagate = 0, gallego->flag->wet = 0;

    gallego->printable->body = 'P';
    gallego->printable->color = strdup( DEFAULT );
    gallego->eated_fruts = 0;
    gallego->score = 0;

    return gallego;
}
