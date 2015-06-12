#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jogo.h>

#define WAIT  1700000 // 1,7 seg
#define DELAY 450000 // 0,45 segs

static monster veiudo = { .catched = 0, .wet = 0, .stopped = 0 };

pos get_monster_pos( void )
{
    return veiudo.pos;
}

void set_monster_pos( pos next_pos )
{
    veiudo.pos = next_pos;
}

int is_monster_catched( void )
{
    return veiudo.catched;
}

void monster_catched( void )
{
    veiudo.catched = 1;
}

int is_monster_wet( void )
{
    return veiudo.wet;
}

int is_monster_stopped( void )
{
    return veiudo.stopped;
}

static void move( pos next_pos )
{
    pos monster_pos = get_monster_pos();
    next_pos.on = get_( next_pos.row, next_pos.column );
    char body = MONSTER;
    if ( is_monster_catched() ) {
        body = DEAD;
        hero_dead();
    }

    play_monstro();
    move_to( monster_pos, next_pos, body );
    set_monster_pos( next_pos );
}


void _monster_moviment_default( pos *gallego_pos, pos *monster_pos, pos *next_pos )
{
    if ( gallego_pos->row > monster_pos->row ) {
        if ( gallego_pos->column > monster_pos->column ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row ++; break;
                case 2 : case 3 : next_pos->column ++; break;
                case 4 : next_pos->row ++, next_pos->column ++; break;
            }
        }
        else if ( gallego_pos->column < monster_pos->column ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row ++; break;
                case 2 : case 3 : next_pos->column --; break;
                case 4 : next_pos->row ++, next_pos->column --; break;
            }
        }
        else {
            next_pos->row ++;
        }
    }
    else if ( gallego_pos->row < monster_pos->row ) {
        if ( gallego_pos->column > monster_pos->column ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row --; break;
                case 2 : case 3 : next_pos->column ++; break;
                case 4 : next_pos->row --, next_pos->column ++; break;
            }
        }
        else if ( gallego_pos->column < monster_pos->column ) {
            switch ( get_rand( 5 ) ) {
                case 0 : case 1 : next_pos->row --; break;
                case 2 : case 3 : next_pos->column --; break;
                case 4 : next_pos->row --, next_pos->column --; break;
            }
        }
        else {
            next_pos->row --;
        }
    }
    else {
        if ( gallego_pos->column > monster_pos->column )
            next_pos->column ++;
        else if ( gallego_pos->column < monster_pos->column )
            next_pos->column --;
        else
            ;
    }
}

void search_hero( void(*how_to_search)(pos*,pos*,pos*), pos *gallego_pos, pos *monster_pos, pos *next_pos )
{
    how_to_search( gallego_pos, monster_pos, next_pos );
}

void maybe_monster_wants_stop( void )
{
    int rand_sound = get_rand( 20 );
    if (  rand_sound > 17 && !is_monster_wet() ) {
        veiudo.stopped = 1;
        if ( rand_sound == 18 ) play_owyeh();
        else play_madrecita();
        usleep(1000000);
        veiudo.stopped = 0;
    }
}


void* handle_monster( void *a )
 {
    usleep( WAIT );

	while ( !is_hero_dead() ) {

        pos gallego_pos = get_hero_pos(), monster_pos = get_monster_pos(), next_pos = get_monster_pos();

        maybe_monster_wants_stop();

        search_hero( _monster_moviment_default, &gallego_pos, &monster_pos, &next_pos );

        if ( gallego_pos.row == next_pos.row && gallego_pos.column == next_pos.column )
            monster_catched();

        if ( get_( next_pos.row, next_pos.column ) == TRAP ) {
            veiudo.wet_sec = get_sec();
            veiudo.wet = 1;
            // vou por som de pisar no molhado que ficará na função move...junto com o monster.wav
            if ( !get_rand( 15 ) )
                play_wet();
        }


        // a ser colocado no set.c!
        if ( get_sec() - veiudo.wet_sec == 2 || get_sec() - veiudo.wet_sec == -58 )
            veiudo.wet = 0;

        move( next_pos );
        usleep( DELAY );

	}

     return NULL;
 }
