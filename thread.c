#include "thread.h"
#include "gallego.h"
#include "veiudo.h"
#include "set.h"
#include "clock.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

static pthread_t t_monster, t_hero, t_set, t_clock, t_fruit, t_coin;
static pthread_mutex_t move_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_attr_t attr;

int s;

void error( char *msg )
{
	fprintf( stderr, "%s: %s\n", msg, strerror( errno ) );
	exit( 1 );
}


void init_threads()
{
    if ( pthread_mutex_init( &move_lock, NULL ) == -1 )
        error( "Can't create mutex 'move_lock'" );

    if ( pthread_attr_init( &attr ) == -1 )
        error( "Can't create attr for the threads" );

    if ( pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE ) == -1 )
        error( "Can't set 'joinable' to thread's attr" );

    if ( pthread_create( &t_monster, &attr, handle_monster, NULL ) == -1 )
        error( "Can't create thread for Monster" );

    if ( pthread_create( &t_hero, &attr, handle_hero, NULL ) == -1 )
        error( "Can't create thread for Hero" );

     if ( pthread_create( &t_set, &attr, handle_set, NULL ) == -1 )
        error( "Can't create thread for set" );

    if ( pthread_create( &t_clock, &attr, handle_time, NULL ) == -1 )
        error( "Can't create thread for clock" );

    if ( pthread_create( &t_fruit, &attr, handle_fruits, NULL ) == -1 )
        error( "Can't create thread for fruit" );

    if ( pthread_create( &t_coin, &attr, handle_coins, NULL ) == -1 )
        error( "Can't create thread for coins" );
}

void join_threads()
{
    void *result;

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

        s = pthread_cancel( t_coin );
        if ( s ) error( "Can't stop the t_coin thread..." );

    } else {

        s = pthread_join( t_monster, &result );
        if ( s ) error( "Can't join thread for monster" );

        s = pthread_join( t_set, &result );
        if ( s ) error( "Can't join thread for t_set" );

        s = pthread_join( t_clock, &result );
        if ( s ) error( "Can't join thread for t_clock" );

        s = pthread_join( t_fruit, &result );
        if ( s ) error( "Can't join thread for t_fruit" );

        s = pthread_join( t_coin, &result );
        if ( s ) error( "Can't join thread for t_coin" );
    }
}
/*
void cancel_threads( char c )
{
    if ( c == HERO ) {
        s = pthread_cancel( t_monster );
        if ( s ) error( "Can't stop the t_moster thread..." );
    }
    else {
        s = pthread_cancel( t_hero );
        if ( s ) error( "Can't stop the t_hero thread..." );
    }

    s = pthread_cancel( t_set );
    if ( s ) error( "Can't stop the t_set thread..." );

    s = pthread_cancel( t_clock );
    if ( s ) error( "Can't stop the t_clock thread..." );

    s = pthread_cancel( t_fruit );
    if ( s ) error( "Can't stop the t_fruit thread..." );

    s = pthread_cancel( t_coin );
    if ( s ) error( "Can't stop the t_coin thread..." );
}

*/
void lock()
{
    s = pthread_mutex_lock( &move_lock );
    if ( s ) error( "Can't lock thread flow" );
}

void unlock()
{
    s = pthread_mutex_unlock( &move_lock );
    if ( s ) error( "Can't unlock thread flow" );
}

void clean_up_threads()
{
    s = pthread_mutex_destroy( &move_lock );
    if ( s ) error( "Can't destroy mutex" );

    s = pthread_attr_destroy( &attr );
    if ( s ) error( "Can't destroy attr" );
}

void release_threads()
{
    pthread_exit( NULL );
}
