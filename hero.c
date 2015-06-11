#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <jogo.h>

static hero gallego = { .is_dead = 0 };

pos get_hero_pos( void )
{
    return gallego.pos;
}

void set_hero_pos( pos actual_pos )
{
    gallego.pos = actual_pos;
}

void hero_dead( void )
{
    gallego.is_dead = 1;
}

int is_hero_dead(void)
{
    return gallego.is_dead;
}

static void move( pos *actual_pos )
{
    pos gallego_pos = get_hero_pos();

    int rand_sound = rand() % 40;
    if ( rand_sound > 37 ) {
        *actual_pos = gallego_pos;
        switch ( rand_sound ) {
            case 38 :  play_mancando1(); return;
            case 39 :  play_mancando2(); return;
        }
    }
  /*  if ( rand_sound == 11 ) {
        *actual_pos = gallego_pos;
        play_mancando1();
        return;
    }
    else if ( rand_sound == 10 ) {
        *actual_pos = gallego_pos;
        play_mancando2();
        return;
    } */

	if ( actual_pos->column >= 0 && actual_pos->column < WIDTH && actual_pos->row >= 0 && actual_pos->row < HEIGHT ) {
        char body = HERO;
        char destiny = get_( actual_pos->row, actual_pos->column );
        if ( destiny == TRAP || destiny == MONSTER ) {
            body = DEAD;
            hero_dead();
        }
        //char body = ( destiny == TRAP || destiny == MONSTER ) ? DEAD : HERO;

		/*if ( on == TRAP || on == MONSTER ) {
            gallego.is_dead = 1;
            move_to( &gallego.pos, actual_row, actual_column, DEAD );

			return;
			//print_set();
		}
            */

        ////////////////////////////////////
        ///////////////////////////qqq

        play_action_walking();
        move_to( gallego_pos, *actual_pos, body );
        if ( destiny == COIN ) {
            score_up(); // colocar globsl...
            play_action_moeda();
        }

        set_hero_pos( *actual_pos );

	} else {
        play_limite();
		*actual_pos = gallego_pos;
	}
}
/*
static void _inicialize( void )
{
    int coord[2];
	raffle( coord );

	gallego.pos.row = coord[0], gallego.pos.column = coord[1];
	gallego.pos.on = BLOCK;
	gallego.is_dead = 0;

	set_( gallego.pos.row, gallego.pos.column, HERO );

	print_set();
}
*/
void* handle_hero( void *a )
{
    //_inicialize();
    srand( time(NULL) );
    pos actual_pos = get_hero_pos();
    int direction;
    while ( ( direction = getch() ) != 'q' && !is_hero_dead() ) {
        switch( direction ) {
            case 'w' :
                actual_pos.row --;
                break;
            case 's' :
                actual_pos.row ++;
                break;
            case 'a' :
                actual_pos.column --;
                break;
            case 'd' :
                actual_pos.column ++;
                break;
            default :
                continue;
        }

        move( &actual_pos );

    }

    return NULL;
}






