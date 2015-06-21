#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jogo.h>

static hero gallego = { .is_dead = 0, .is_mancando = 0 };

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

int is_hero_mancado(void)
{
    return gallego.is_mancando;
}


void maybe_gallego_is_mancando( void )
{
    int rand_sound = get_rand( 40 );
    if ( rand_sound > 37 ) {
        gallego.is_mancando = 1;

        if ( rand_sound == 38 ) play_mancando1();
        else play_mancando2();
    }
}

static void move( pos *actual_pos )
{
    pos gallego_pos = get_hero_pos();

    maybe_gallego_is_mancando();

	if (    actual_pos->column >= 0     &&
            actual_pos->column < WIDTH  &&
            actual_pos->row >= 0        &&
            actual_pos->row < HEIGHT    &&
            !is_hero_mancado()    )
    {
        char body = HERO;
        char destiny = get_( actual_pos->row, actual_pos->column );
        if ( destiny == TRAP || destiny == MONSTER ) {
            body = DEAD;
            hero_dead();
        }

        play_action_walking();
        move_to( gallego_pos, *actual_pos, body );
        if ( destiny == COIN ) {
            score_up();
            play_action_moeda();
        }
        else if ( destiny == FRUIT ) {
            score_up();
            menos_fruit();
        }


        set_hero_pos( *actual_pos );

	} else {
        *actual_pos = gallego_pos;
        if ( is_hero_mancado() ) {
            usleep( 100000 );
            gallego.is_mancando = 0;
        } else {
            play_limite();
        }
	}
}

void* handle_hero( void *a )
{
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






