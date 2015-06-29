#include "veiudo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *wet_color = SAGOL BLUE_B;
static char *shitted_color = SAGOL BROWN_B;
static char *stopped_color = SAGOL YELLOW_B;
static char *default_color = SAGOL;

monster *create_monster( pos *pos )
{
    monster *veiudo = ( monster* )malloc( sizeof( monster ) );
 //   veiudo->flag = ( flag* )malloc( sizeof( flag ) );
    veiudo->printable = ( status* )malloc( sizeof( status ) );

    veiudo->pos = pos;

    //veiudo->flag->wet = 0, veiudo->flag->stopped = 0, veiudo->flag->shitted = 0;

    veiudo->printable->body = MONSTER;
    veiudo->printable->color = strdup( default_color );

    return veiudo;
}
