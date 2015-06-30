#include "veiudo.h"
#include "gallego.h"
#include "set.h"
#include "jogo2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WAIT  1700000 // 1,7 seg
#define DELAY 450000 // 0,45 segs

monster *veiudo;

pos get_monster_pos( void )
{
    return *veiudo->pos;
}

void set_monster_pos( pos pos)
{
  veiudo->pos->col = pos.col, veiudo->pos->row = pos.row;
}

void init_monster( void )
{
    veiudo = create_monster( raffle() );
    set_cell( *veiudo->pos, veiudo->printable, CHAR );
}

void _monster_moviment_default( pos *gallego_pos, pos *monster_pos, pos *next_pos )
{
    if ( gallego_pos->row > monster_pos->row ) {
        if ( gallego_pos->col > monster_pos->col ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row ++; break;
                case 2 : case 3 : next_pos->col ++; break;
                case 4 : next_pos->row ++, next_pos->col ++; break;
            }
        }
        else if ( gallego_pos->col < monster_pos->col ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row ++; break;
                case 2 : case 3 : next_pos->col --; break;
                case 4 : next_pos->row ++, next_pos->col --; break;
            }
        }
        else {
            next_pos->row ++;
        }
    }
    else if ( gallego_pos->row < monster_pos->row ) {
        if ( gallego_pos->col > monster_pos->col ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row --; break;
                case 2 : case 3 : next_pos->col ++; break;
                case 4 : next_pos->row --, next_pos->col ++; break;
            }
        }
        else if ( gallego_pos->col < monster_pos->col ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row --; break;
                case 2 : case 3 : next_pos->col --; break;
                case 4 : next_pos->row --, next_pos->col --; break;
            }
        }
        else {
            next_pos->row --;
        }
    }
    else {
        if ( gallego_pos->col > monster_pos->col )
            next_pos->col ++;
        else if ( gallego_pos->col < monster_pos->col )
            next_pos->col --;
        else
            ;
    }
}


void search_hero( void(*how_to_search)(pos*,pos*,pos*), pos *gallego_pos, pos *monster_pos, pos *next_pos )
{
    how_to_search( gallego_pos, monster_pos, next_pos );
}

/*
static void move( pos next_pos )
{
    pos monster_pos = get_monster_pos();
   // next_pos.on = is_monster_shited() ? BLOCK : get_( next_pos.row, next_pos.col );
    char body = MONSTER;
    if ( is_monster_catched() ) {
        body = DEAD;
        hero_dead();
    }

    //play_monstro();
    move_to( monster_pos, next_pos, body );
    if ( is_monster_shited() ) {
        play_wet();
        usleep( 1000000 );
        veiudo.shited = 0;

    set_monster_pos( next_pos );
}

*/

void* handle_monster( void *a )
 {
    //status printable;

    usleep( WAIT );

	while ( !is_hero_dead() ) {

        pos gallego_pos = get_hero_pos(), monster_pos = get_monster_pos(), next_pos = get_monster_pos();

       // maybe_monster_wants_stop();

        search_hero( _monster_moviment_default, &gallego_pos, &monster_pos, &next_pos );

        if ( gallego_pos.row == next_pos.row && gallego_pos.col == next_pos.col ) {
            free( veiudo->printable->color );
            veiudo->printable->color = strdup( RED );
            veiudo->printable->body = DEAD;
            hero_dead();
        }

        move_to( monster_pos, next_pos, veiudo->printable );

        set_monster_pos( next_pos );
      /*  if ( get_( next_pos.row, next_pos.col ) == BOSTA ) {
            score_up();
            pisou_na_bosta();
            veiudo.shited_sec = get_sec();
        }

        if ( get_( next_pos.row, next_pos.col ) == TRAP ) {
            veiudo.wet_sec = get_sec();
            veiudo.wet = 1;
            // vou por som de pisar no molhado que ficará na função move...junto com o monster.wav
            //if ( !get_rand( 15 ) )
             //   play_wet();
        }

       // if ( get_sec() - veiudo.shited_sec == 2 || get_sec() - veiudo.shited_sec == -58 )
        //    veiudo.shited = 0;
        // a ser colocado no set.c!
        if ( get_sec() - veiudo.wet_sec == 2 || get_sec() - veiudo.wet_sec == -58 )
            veiudo.wet = 0;
*/
      //  move( next_pos );
        usleep( DELAY );

	}

     return NULL;
 }

