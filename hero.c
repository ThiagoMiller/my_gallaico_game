#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jogo.h>

static hero gallego = { .is_dead = 0, .is_mancando = 0, .is_trying_cagate = 0, .is_cagating = 0, .eated_fruts = 0 };

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

void trying_cagate(void)
{
    gallego.is_trying_cagate = 1;
}

void it_was_just_a_little_fart()
{
    gallego.is_trying_cagate = 0;
}

int is_gallego_trying_cagate(void)
{
    return gallego.is_trying_cagate;
}

void eat_frut()
{
    menos_fruit();
    if ( gallego.eated_fruts == 3 )
        return;
    gallego.eated_fruts++;
}

int is_ready_bosta(void)
{
    return gallego.eated_fruts == 3 ? 1 : 0;
}

int is_gallego_cagating(void)
{
    return gallego.is_cagating;
}

void cagate(void)
{
    gallego.is_cagating = 1;
    gallego.is_trying_cagate = 0;
    gallego.eated_fruts = 0;
   // gallego.pos.on = BOSTA;
}

void cagated( void )
{
    gallego.is_cagating = 0;
}

int is_cagated(void)
{
    return is_gallego_cagating() ? 1 : 0;
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

    maybe_gallego_is_mancando(); // botar um if para não colidir cagate com mancate!

	if (    actual_pos->column >= 0     &&
            actual_pos->column < WIDTH  &&
            actual_pos->row >= 0        &&
            actual_pos->row < HEIGHT    &&
            !is_hero_mancado()          &&
            !is_gallego_trying_cagate()     )
    {
        char body = HERO;
        char destiny = get_( actual_pos->row, actual_pos->column );
        if ( destiny == TRAP || destiny == MONSTER ) {
            body = DEAD;
            hero_dead();
        }

        if (  is_cagated() ) {
            gallego_pos.on = BOSTA;
            cagated();
        }


        play_action_walking();
        move_to( gallego_pos, *actual_pos, body );

        if ( destiny == COIN ) {
            score_up();
            play_action_moeda();
        }
        else if ( destiny == FRUIT ) {
            score_up();
            eat_frut();
        }


        set_hero_pos( *actual_pos );

	} else {
        *actual_pos = gallego_pos;
        if ( is_gallego_trying_cagate() ) {
        // programação de alto nível! a gente vê por aqui!
            if ( is_ready_bosta() ) {
                cagate();
               // actual_pos->on = BOSTA;
            }
            else
                it_was_just_a_little_fart();
        }
        else if ( is_hero_mancado() ) {
            usleep( 100000 );
            gallego.is_mancando = 0;
        }
        else {
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
            case ' ' :
                trying_cagate();
                break;
            default :
                continue;
        }

        move( &actual_pos );

    }

    return NULL;
}






