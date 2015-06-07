#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <jogo.h>

#define WAIT  1700000 // 3,00 seg
#define DELAY 450000 // 0,45 segs

extern hero gallego;


static void move( monster *monster, int actual_row, int actual_column )
{
    char body = monster->catched ? DEAD : MONSTER;
  /*  if ( !monster->catched ) {
        move_to( &monster->pos, actual_row, actual_column );
    }
    else {
        is_game_over = 1;
        set[ monster->row ][ monster->column ] = monster->on;
        set[ *actual_row ][ *actual_column ] = DEAD;
    }
    */
    play_monstro();
    move_to( &monster->pos, actual_row, actual_column, body );

}


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

void* handle_monster( void *a )
 {
    monster monster;
    _inicialize( &monster );

	srand(time(NULL));
	int actual_column = monster.pos.column, actual_row = monster.pos.row;

    usleep( WAIT );

	while ( 1 ) {

        if ( gallego.pos.row > monster.pos.row ) {
            if ( gallego.pos.column > monster.pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_row ++; break;
                    case 2 : case 3 : actual_column ++; break;
                    case 4 : actual_row ++, actual_column ++; break;
                }
            }
            else if ( gallego.pos.column < monster.pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_row ++; break;
                    case 2 : case 3 : actual_column --; break;
                    case 4 : actual_row ++, actual_column --; break;
                }
            }
            else {
                actual_row ++;
            }
        }
        else if ( gallego.pos.row < monster.pos.row ) {
            if ( gallego.pos.column > monster.pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_row --; break;
                    case 2 : case 3 : actual_column ++; break;
                    case 4 : actual_row --, actual_column ++; break;
                }
            }
            else if ( gallego.pos.column < monster.pos.column ) {
                switch ( rand() % 5 ) {
                    case 0 : case 1 : actual_row --; break;
                    case 2 : case 3 : actual_column --; break;
                    case 4 : actual_row --, actual_column --; break;
                }
            }
            else {
                actual_row --;
            }
        }
        else {
            if ( gallego.pos.column > monster.pos.column )
                actual_column ++;
            else if ( gallego.pos.column < monster.pos.column )
                actual_column --;
            else
                ;
        }

        if ( gallego.pos.row == actual_row && gallego.pos.column == actual_column )
            monster.catched = 1;

        move( &monster, actual_row, actual_column );
        usleep( DELAY );

	}

     return NULL;
 }
