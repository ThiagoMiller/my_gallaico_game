#include <stdio.h>
#include <stdlib.h>
#include <jogo.h>

#define DELAY 1

extern hero gallego;
extern char set[ WIDTH ][ HEIGHT ];
extern int is_game_over;


static void move( monster *monster, int *actual_row, int *actual_column )
{
    if ( !monster->catched ) {
		set[ monster->row ][ monster->column ] = monster->on;
		monster->on = set[ *actual_row ][ *actual_column ];
		set[ *actual_row ][ *actual_column ] = MONSTER;
		monster->column = *actual_column, monster->row = *actual_row;
    }
    else {
        is_game_over = 1;
        set[ monster->row ][ monster->column ] = monster->on;
        set[ *actual_row ][ *actual_column ] = DEAD;

       // print_set();
    }
}


static void _inicialize( monster *monster )
{
    int coord[2];
	raffle( coord );
	monster->row = coord[0], monster->column = coord[1];
	monster->catched = 0;
	monster->on = BLOCK;
	set[ monster->row ][ monster->column ] = MONSTER;
	//print_set();
}

void* handle_monster( void *a )
 {
    monster monster;
    _inicialize( &monster );

	srand(time(NULL));
	int actual_column = monster.column, actual_row = monster.row;
    // enquanto o thread do herói não retornar...
	while ( 1 ) {
       // int rand_;
        //int hero_row = hero.row, hero_column = hero.column;
        //int monster_row =
        if ( is_game_over )
            break;

        if ( gallego.row > monster.row ) {
            if ( gallego.column > monster.column ) {
                switch ( rand() % 4 ) {
                    case 0 : case 1 : actual_row ++;
                    case 2 : case 3 : actual_column ++;
                    case 4 : actual_row ++, actual_column ++;
                }
            }
            else if ( gallego.column < monster.column ) {
                switch ( rand() % 4 ) {
                    case 0 : case 1 : actual_row ++;
                    case 2 : case 3 : actual_column --;
                    case 4 : actual_row ++, actual_column --;
                }
            }
            else {
                actual_row ++;
            }
        }
        else if ( gallego.row < monster.row ) {
            if ( gallego.column > monster.column ) {
                switch ( rand() % 4 ) {
                    case 0 : case 1 : actual_row --;
                    case 2 : case 3 : actual_column ++;
                    case 4 : actual_row --, actual_column ++;
                }
            }
            else if ( gallego.column < monster.column ) {
                switch ( rand() % 4 ) {
                    case 0 : case 1 : actual_row --;
                    case 2 : case 3 : actual_column --;
                    default : actual_row --, actual_column --;
                }
            }
            else {
                actual_row --;
            }
        }
        else {
            if ( gallego.column > monster.column )
                actual_column ++;
            else if ( gallego.column < monster.column )
                actual_column --;
            else
                gallego.is_dead = 1, monster.catched = 1;
        }
        move( &monster, &actual_row, &actual_column );
         if ( is_game_over )
            break;
        sleep( DELAY );
        //print_set();
	}

    /*while( 1 ) {
        set[1][0] = BLOCK;
        set[0][0] = MONSTER;
        sleep(1);
        print_set();
        set[1][0] = MONSTER;
        set[0][0] = BLOCK;
        sleep(1);
        print_set();
    }*/
     return NULL;
 }
