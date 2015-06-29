#include "gallego.h"
#include "veiudo.h"
#include "jogo2.h"
#include "set.h"
#include "getch.h"
#include <stdio.h>


hero *gallego;



pos get_hero_pos( void )
{
  return *gallego->pos;
}

void set_hero_pos( pos pos)
{
   gallego->pos->col = pos.col, gallego->pos->row = pos.row;
}

void hero_dead( void )
{
    gallego->dead = 1;
    gallego->printable->body = DEAD;
}

int is_hero_dead(void)
{
    return gallego->dead;
}
/*
void trying_cagate(void)
{
    gallego->flag->trying_cagate = 1;
    if ( gallego->eated_fruts == 3 )
      cagate();
    else
      it_was_just_a_little_fart();
}

void it_was_just_a_little_fart()
{
    gallego->flag->trying_cagate = 0;
}

int is_gallego_trying_cagate(void)
{
    return gallego->flag->trying_cagate;
}

void eat_frut()
{
    //menos_fruit();
    if ( gallego->eated_fruts == 3 )
        return;
    gallego->eated_fruts++;
}

int is_ready_bosta(void)
{
    return gallego->eated_fruts == 3 ? 1 : 0;
}

int is_gallego_cagating(void)
{
    return gallego->flag->cagating;
}

void cagate(void)
{
    gallego->flag->cagating = 1;
    gallego->flag->trying_cagate = 0;
    gallego->eated_fruts = 0;
   // gallego.pos.on = BOSTA;
}

void cagated( void )
{
    gallego->flag->cagating = 0;
}

int is_cagated(void)
{
    return is_gallego_cagating() ? 1 : 0;
}

int is_hero_limpping(void)
{
    return gallego->flag->limpping;
}


void maybe_gallego_is_limpping( void )
{
    int rand_sound = get_rand( 40 );
    if ( rand_sound > 37 ) {
        gallego->flag->limpping = 1;

        if ( rand_sound == 38 ) play_mancando1();
        else play_mancando2();
    }
}
*/
static void move( pos *actual_pos )
{
    pos gallego_pos = get_hero_pos();

  //  maybe_gallego_is_limpping(); // botar um if para não colidir cagate com mancate!

	if (    actual_pos->col >= 0         &&
          actual_pos->col < WIDTH      &&
          actual_pos->row >= 0            &&
          actual_pos->row < HEIGHT
        //  !is_hero_limpping()             )
      )
    {
        cell *destiny = get_cell( *actual_pos );
        if ( destiny->layer0 != NULL && destiny->layer0->body == MONSTER) {
            gallego->printable->body = DEAD;
            hero_dead();
        }
      /*  if ( destiny->layer1->body == TRAP || destiny->layer0->body == MONSTER ) {
            gallego->printable->body = DEAD;
            hero_dead();
        }*/

       /* if (  is_cagated() ) {
            gallego_pos.on = BOSTA;
            cagated();
        }

*/
        //play_action_walking();
        move_to( gallego_pos, *actual_pos, gallego->printable );

      /*  if ( destiny == COIN ) {
            score_up();
            play_action_moeda();
        }
        else if ( destiny == FRUIT ) {
            score_up();
            eat_frut();
        }
*/

        set_hero_pos( *actual_pos );

	} else {
        *actual_pos = gallego_pos;
    /*    if ( is_gallego_trying_cagate() ) {
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
        }*/
	}
}


void init_hero()
{
  gallego = create_hero( raffle() );
  set_cell( *gallego->pos, gallego->printable, CHAR );
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
                actual_pos.col --;
                break;
            case 'd' :
                actual_pos.col ++;
                break;
            case ' ' :
               // trying_cagate();
                continue;
            default :
                continue;
        }

        move( &actual_pos );

    }

    return NULL;
}
