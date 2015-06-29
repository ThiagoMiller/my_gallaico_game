#include "clock.h"

#include <stdio.h>
#include <unistd.h>



static clock_game time_of_match = { 0, 0, 0 };

void get_time_of_day( char *format )
{
    if ( time_of_match.hrs < 10 ) {
            sprintf( format, "0%d", time_of_match.hrs );
    } else {
            sprintf( format, ":%d", time_of_match.hrs );
    }

    if ( time_of_match.min < 10 ) {
        sprintf( format, "%s:0%d", format, time_of_match.min );
    } else {
        sprintf( format, "%s:%2d", format, time_of_match.min );
    }

    if( time_of_match.sec < 10 ) {
        sprintf( format, "%s:0%d", format, time_of_match.sec );
    } else {
        sprintf( format, "%s:%2d", format, time_of_match.sec );
    }
}

int get_sec( void )
{
    return time_of_match.sec;
}

void* handle_time( void *a )
{
    int elapsed = 0, sec = 0, min = 0, MIN = 0, hrs = 0, d = 0, f = 0;

    while ( !is_hero_dead() ) {

        usleep( 1000000 );
		elapsed++;

		if ( elapsed % 60 == 0 ) {
			min = elapsed / 60;
			d = min * 60;
			if ( min % 60 == 0 ) {
				hrs = min / 60;
				f = 60 * hrs;
			}
        }

		sec = elapsed - d;
		MIN = min - f;

        time_of_match.hrs = hrs;
        time_of_match.min = MIN;
        time_of_match.sec = sec;

    }

    return NULL;
}

