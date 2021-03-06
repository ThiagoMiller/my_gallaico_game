#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <jogo.h>

static pthread_t t_monster, t_hero, t_set, t_clock, t_fruit;
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

     if ( pthread_create( &t_set, NULL, handle_set, NULL ) == -1 )
        error( "Can't create thread for set" );

    if ( pthread_create( &t_clock, NULL, handle_time, NULL ) == -1 )
        error( "Can't create thread for clock" );

    if ( pthread_create( &t_fruit, NULL, handle_fruit, NULL ) == -1 )
        error( "Can't create thread for fruit" );
}

void join_threads()
{
    void *result;
    int s;

    s = pthread_join( t_hero, &result );
    if ( s ) error( "Can't join thread for hero" );

    if ( !is_hero_dead() ) {

        s = pthread_cancel( t_monster );
        if ( s ) error( "Can't stop the t_moster thread..." );

        s = pthread_cancel( t_set );
        if ( s ) error( "Can't stop the t_set thread..." );

        s = pthread_cancel( t_clock );
        if ( s ) error( "Can't stop the t_clock thread..." );

        s = pthread_cancel( t_fruit );
        if ( s ) error( "Can't stop the t_fruit thread..." );

    } else {

        s = pthread_join( t_monster, &result );
        if ( s ) error( "Can't join thread for monster" );

        s = pthread_join( t_set, &result );
        if ( s ) error( "Can't join thread for t_set" );

        s = pthread_join( t_clock, &result );
        if ( s ) error( "Can't join thread for t_clock" );

        s = pthread_join( t_fruit, &result );
        if ( s ) error( "Can't join thread for t_fruit" );
    }
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




