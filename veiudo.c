#include "veiudo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *state_color[];

monster *create_monster( pos *pos )
{
    monster *veiudo = ( monster* )malloc( sizeof( monster ) );
 //   veiudo->flag = ( flag* )malloc( sizeof( flag ) );
    veiudo->obj = ( obj* )malloc( sizeof( obj ) );
    veiudo->obj->printable = ( status* )malloc( sizeof( status ) );

    veiudo->obj->pos = pos;
    veiudo->stepped_in_shit = 0;

    //veiudo->flag->wet = 0, veiudo->flag->stopped = 0, veiudo->flag->shitted = 0;

    veiudo->obj->printable->body = MONSTER;
    veiudo->obj->printable->color = state_color[DEFAULT_MONSTER_COLOR];

    return veiudo;
}
