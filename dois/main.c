#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <jogo.h>

int is_game_over = 0;

extern hero gallego;

void error( char *msg )
{
	fprintf( stderr, "%s: %s\n", msg, strerror( errno ) );
	exit( 1 );
}


int main()
{
    system( "clear" );
    build_set();
    //print_set();

    pthread_t t_monster, t_hero, t_set;

	if ( pthread_create( &t_monster, NULL, handle_monster, NULL ) == -1 )
        error( "Can't create thread for Monster" );

    if ( pthread_create( &t_hero, NULL, handle_hero, NULL ) == -1 )
        error( "Can't create thread for hero" );

    if ( pthread_create( &t_set, NULL, print_set, NULL ) == -1 )
        error( "Can't create thread for set" );

    void *result;
    pthread_join( t_monster, &result );
    pthread_join( t_hero, &result );
    pthread_join( t_set, &result );

    if ( gallego.is_dead )
        game_over();

    return 0;
}
