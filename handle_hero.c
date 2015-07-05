#include "gallego.h"
#include "veiudo.h"
#include "jogo2.h"
#include "set.h"
#include "getch.h"
#include "bosta.h"
#include "item.h"
#include "trap.h"
#include "audio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char *state_color[];

static hero *gallego;


char *bosta_power[] = {
    "\033[48;5;8m" " B O S T A ",
    BROWN_B " B O" "\033[48;5;8m" " S T A ",
    BROWN_B " B O S " "\033[48;5;8m" "T A ",
    BROWN_B " B O S T A "
};

pos get_hero_pos( void )
{
  return *gallego->obj->pos;
}


void hero_dead( void )
{
    gallego->dead = 1;
}

int is_hero_dead(void)
{
    return gallego->dead;
}

int get_score(void)
{
    return gallego->score;
}

void trying_cagate(void)
{
   //gallego->flag->trying_cagate = 1;
    if ( gallego->eated_fruts == 3 ) {
        gallego->eated_fruts = 0;
        rebosteio( *gallego->obj->pos );
        gallego->obj->printable->color = state_color[ CAGATE_COLOR ];
        gallego->cagating = 1;
    //  cagate();
    }
 //   else
  //    it_was_just_a_little_fart();
}

void score_up( int score )
{
    gallego->score = (int)( gallego->score + score ) < 0 ? 0 : ( gallego->score + score );
}

char *get_bosta_format( void )
{
    return bosta_power[ gallego->eated_fruts ];
}

/*
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

*/
void maybe_gallego_is_limpping( void )
{
    if ( gallego->trapped ) return;

    int rand_sound = get_rand( 40 );
    if ( rand_sound > 37 ) {
        gallego->obj->printable->color = state_color[LIMP_COLOR];
        gallego->limpping = 1;
        if ( rand_sound == 38 ) play_mancando1();
        else play_mancando2();
    }
}

static void move( pos *next_pos )
{

    maybe_gallego_is_limpping(); // botar um if para não colidir cagate com mancate!

	if (    next_pos->col >= 0          &&
            next_pos->col < WIDTH       &&
            next_pos->row >= 0          &&
            next_pos->row < HEIGHT      &&
            !gallego->limpping          &&
            !gallego->trapped               )
    {
        if ( gallego->cagating ) {
            gallego->cagating = 0;
            gallego->obj->printable->color = state_color[DEFAULT_HERO_COLOR];
        }

        cell *destiny = get_cell( *next_pos );

        if ( destiny->layer0 != NULL && destiny->layer0->body == MONSTER) {
           // free( gallego->obj->printable->color );
            gallego->obj->printable->color = state_color[ DEAD_COLOR ];
            gallego->obj->printable->body = DEAD;
            hero_dead();
        }
        else if ( destiny->layer1 != NULL ) {
            switch ( destiny->layer1->body ) {
            case FRUIT :
                if ( gallego->eated_fruts < 3 )
                    gallego->eated_fruts++;
                score_up( 1 );
                clean_item( destiny );
                break;
            case COIN :
                score_up( 3 );
                clean_item( destiny );
                play_action_moeda();
                break;
            case BOSTA :
                down_bosta( destiny->layer1 );
                score_up( -2 );
                gallego->obj->printable->color = state_color[CAGATED_COLOR];
                gallego->cagated = 1;
                break;
            case L_BOSTA :
                score_up( -1 );
                gallego->obj->printable->color = state_color[CAGATED_COLOR];
                gallego->cagated = 1;
                clean_item( destiny );
                break;
            case TRAP :
                score_up( -10 );
                gallego->trapped = 1;
                gallego->obj->printable->color = state_color[TRAPPED_COLOR];
            }
        }
           /* if ( destiny->layer1->body == FRUIT ) {
                if ( gallego->eated_fruts < 3 )
                    gallego->eated_fruts++;

                score_up( 1 );
                clean_item( destiny );
            }
            else if ( destiny->layer1->body == COIN ) {
                score_up( 3 );
                clean_item( destiny );
            }
            else if ( destiny->layer1->body == BOSTA ) {
                down_bosta( destiny->layer1 );
                score_up( -2 );
            }
            else if ( destiny->layer1->body == L_BOSTA ) {
                clean_item( destiny );
                score_up( -1 );
            }


        }*/

      /*  if ( destiny->layer1->body == TRAP || destiny->layer0->body == MONSTER ) {
            gallego->printable->body = DEAD;
            hero_dead();
        }*/

       /* if (  is_cagated() ) {
            gallego_pos.on = BOSTA;
            cagated();
        }

*/
        play_action_walking();
        move_to( gallego->obj, *next_pos );

        if ( gallego->cagated ) {
            usleep(300000);
            gallego->obj->printable->color = state_color[DEFAULT_HERO_COLOR];
            gallego->cagated = 0;
        }


      /*  if ( destiny == COIN ) {
            score_up();
            play_action_moeda();
        }
        else if ( destiny == FRUIT ) {
            score_up();
            eat_frut();
        }
*/

	} else {
        *next_pos = get_hero_pos();
        if ( gallego->limpping ) {
            usleep(100000);
            gallego->obj->printable->color = state_color[DEFAULT_HERO_COLOR];
            gallego->limpping = 0;
        }
        else if ( gallego->trapped ) {
            static int acm = 0;

            gallego->obj->printable->color = state_color[TRY_GO_OUT_TRAP];
            usleep(100000);
            gallego->obj->printable->color = state_color[TRAPPED_COLOR];

            if ( ++acm == 8 ) {
                acm = 0;
                gallego->trapped = 0;
                gallego->obj->printable->color = state_color[DEFAULT_HERO_COLOR];
                clean_item( get_cell( *next_pos ) );
                minus_trap();
            }
            play_limite();
        }
        else {
            play_limite();
        }
    /*    if ( is_gallego_trying_cagate() ) {
        // programação de alto nível! a gente vê por aqui!
            if ( is_ready_bosta() ) {
                cagate();
               // next_pos->on = BOSTA;
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
    set_cell( gallego->obj, CHAR );
}


void* handle_hero( void *a )
{
    pos next_pos = get_hero_pos();
    int direction;
    while ( ( direction = getch() ) != 'q' && !is_hero_dead() ) {
        switch( direction ) {
            case 'w' :
                next_pos.row --;
                break;
            case 's' :
                next_pos.row ++;
                break;
            case 'a' :
                next_pos.col --;
                break;
            case 'd' :
                next_pos.col ++;
                break;
            case ' ' :
                trying_cagate();
                continue;
            default :
                continue;
        }

        move( &next_pos );

    }

    return NULL;
}
