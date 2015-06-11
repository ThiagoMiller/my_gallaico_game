#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <jogo.h>

#define WAIT  1700000 // 1,7 seg
#define DELAY 450000 // 0,45 segs

static monster veiudo = { .catched = 0, .wet = 0 };

pos get_monster_pos( void )
{
    return veiudo.pos;
}

void set_monster_pos( pos actual_pos )
{
    veiudo.pos = actual_pos;
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


static void move( pos actual_pos )
{
    pos monster_pos = get_monster_pos();
    actual_pos.on = get_( actual_pos.row, actual_pos.column );
    char body = MONSTER;
    if ( is_monster_catched() ) {
        body = DEAD;
        hero_dead();
    }
   // char body = is_monster_catched() ? DEAD : MONSTER;

  /*  if ( !monster->catched ) {
        move_to( &monster->pos, actual_row, actual_column );
    }
    else {
        is_game_over = 1;
        set[ monster->row ][ monster->column ] = monster->on;
        set[ *actual_row ][ *actual_column ] = DEAD;
    }
    f ( body == MONSTER )
   //     pos->on = get_( actual_row, actual_column );
    */
    play_monstro();
    move_to( monster_pos, actual_pos, body );
    set_monster_pos( actual_pos );
}

/*
static void _inicialize( monster *monster )
{
    int coord[2];
	raffle( coord );

	monster->pos.row = coord[0], monster->pos.column = coord[1];
	monster->pos.on = BLOCK;
	monster->catched = 0;

	set_( monster->pos.row, monster->pos.column, MONSTER );
	print_set();
}
*/
void* handle_monster( void *a )
 {
   // monster monster;
    //_inicialize( &monster );

	srand(time(NULL));

	pos actual_pos = get_monster_pos();
	//int actual_column = monster.pos.column, actual_row = monster.pos.row;

    usleep( WAIT );

	while ( !is_hero_dead() ) {

        pos gallego_pos = get_hero_pos(), monster_pos = get_monster_pos();

        if ( gallego_pos.row > monster_pos.row ) {
            if ( gallego_pos.column > monster_pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_pos.row ++; break;
                    case 2 : case 3 : actual_pos.column ++; break;
                    case 4 : actual_pos.row ++, actual_pos.column ++; break;
                }
            }
            else if ( gallego_pos.column < monster_pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_pos.row ++; break;
                    case 2 : case 3 : actual_pos.column --; break;
                    case 4 : actual_pos.row ++, actual_pos.column --; break;
                }
            }
            else {
                actual_pos.row ++;
            }
        }
        else if ( gallego_pos.row < monster_pos.row ) {
            if ( gallego_pos.column > monster_pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_pos.row --; break;
                    case 2 : case 3 : actual_pos.column ++; break;
                    case 4 : actual_pos.row --, actual_pos.column ++; break;
                }
            }
            else if ( gallego_pos.column < monster_pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_pos.row --; break;
                    case 2 : case 3 : actual_pos.column --; break;
                    case 4 : actual_pos.row --, actual_pos.column --; break;
                }
            }
            else {
                actual_pos.row --;
            }
        }
        else {
            if ( gallego_pos.column > monster_pos.column )
                actual_pos.column ++;
            else if ( gallego_pos.column < monster_pos.column )
                actual_pos.column --;
            else
                ;
        }

        if ( gallego_pos.row == actual_pos.row && gallego_pos.column == actual_pos.column )
            monster_catched();

        if ( get_( actual_pos.row, actual_pos.column ) == TRAP ) {
            veiudo.wet_sec = get_sec();
            veiudo.wet = 1;
            int rand_sound =  rand() % 10;
            if ( rand_sound == 9 )
                play_wet1();
            else if ( rand_sound == 8 )
                play_wet2();
        }

        if ( get_sec() - veiudo.wet_sec == 2 || get_sec() - veiudo.wet_sec == -58 )
            veiudo.wet = 0;

        move( actual_pos );
        usleep( DELAY );

	}

     return NULL;
 }
