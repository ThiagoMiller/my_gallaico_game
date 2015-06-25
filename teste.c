#include <gallego.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pos *posi = (pos*)malloc( sizeof( pos ) );
    posi->col = 9;
    posi->row = 8;

    hero *gallaico = create_hero( posi );

    printf( "my body = %c\n", gallaico->printable->body );
    printf( "my color = %s\n", gallaico->printable->color );
    printf( "my pos - row = %d\n", gallaico->pos->row );
    printf( "my pos - column = %d\n", gallaico->pos->col );
    printf( "my flags:\n\t*cagating\t%d\n", gallaico->flag->cagating );
    printf( "\t*dead\t\t%d\n", gallaico->flag->dead );
    printf( "\t*limpping\t%d\n", gallaico->flag->limpping );
    printf( "\t*trying_cagate\t%d\n", gallaico->flag->trying_cagate );
    printf( "\t*wet\t\t%d\n", gallaico->flag->wet );
    printf( "Frutas comidas = %d\n\n", gallaico->eated_fruts );

    return 0;
}
