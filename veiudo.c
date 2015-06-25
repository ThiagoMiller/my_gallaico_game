#include <veiudo.h>


monster *create_monster( pos *pos )
{
    monster *veiudo = ( monster* )malloc( sizeof( monster ) );
    veiudo->flag = ( flag* )malloc( sizeof( flag ) );
    veiudo->printable = ( status* )malloc( sizeof( status ) );

    veiudo->pos = pos;

    veiudo->flag->wet = 0, veiudo->flag->stopped = 0, veiudo->flag->shitted = 0;

    veiudo->printable->body = 'M';
    veiudo->printable->color = strdup( DEFAULT );
    veiudo->eated_fruts = 0;
    veiudo->score = 0;

    return veiudo;
}
