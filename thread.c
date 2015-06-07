#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <jogo.h>

static pthread_t t_monster, t_hero;
static pthread_mutex_t move_lock = PTHREAD_MUTEX_INITIALIZER;


void error( char *msg )
{
	fprintf( stderr, "%s: %s\n", msg, strerror( errno ) );
	exit( 1 );
}


void init_threads()
{
    if ( pthread_create( &t_monster, NULL, handle_monster, NULL ) == -1 )
        error( "Can't create thread for Monster" );

    if ( pthread_create( &t_hero, NULL, handle_hero, NULL ) == -1 )
        error( "Can't create thread for Hero" );
}

void join_threads()
{
    void *result;
    int s;

    s = pthread_join( t_hero, &result );
    if ( s ) error( "Can't join thread for hero" );

    s = pthread_cancel( t_monster );
    if ( s ) error( "Can't stop the t_moster thread..." );

    s = pthread_join( t_monster, &result );
    if ( s ) error( "Can't join thread for monster" );
}

void lock()
{
    int s;
    s = pthread_mutex_lock( &move_lock );
    if ( s ) error( "Can't lock thread flow" );
}

void unlock()
{
    int s;
    s = pthread_mutex_unlock( &move_lock );
    if ( s ) error( "Can't unlock thread flow" );
}

void release_threads()
{
    pthread_exit( NULL );
}




