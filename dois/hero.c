#include <stdio.h>
#include <jogo.h>

extern char set[ WIDTH ][ HEIGHT ];
extern int score;
extern int is_game_over;

hero gallego;

void move( int *actual_row, int *actual_column  )
{
	if ( *actual_column >= 0 && *actual_column < WIDTH && *actual_row >= 0 && *actual_row < HEIGHT ) {

		if ( set[*actual_row][*actual_column] == TRAP  ) {
			set[ gallego.row ][ gallego.column ] = BLOCK;
			set[ *actual_row ][ *actual_column ] = DEAD;
			gallego.is_dead = 1;
			return;
			//print_set();
		}

		if ( set[*actual_row][*actual_column] == COIN )
			score++;

		set[ gallego.row ][ gallego.column ] = BLOCK;
		set[ *actual_row ][ *actual_column ] = HERO;
		gallego.column = *actual_column, gallego.row = *actual_row;

	} else {
		*actual_column = gallego.column, *actual_row = gallego.row;
	}
}

static void _inicialize( void )
{
    int coord[2];
	raffle( coord );

	gallego.row = coord[0], gallego.column = coord[1];
	gallego.is_dead = 0;
	set[ gallego.row ][ gallego.column ] = HERO;
	//print_set();
}

void* handle_hero( void *a )
{
    _inicialize();
    int direction, actual_column = gallego.column, actual_row = gallego.row;
    while ( ( direction = getch() ) != 'q' ) {

        switch( direction ) {
            case 'w' :
                actual_row --;
                break;
            case 's' :
                actual_row ++;
                break;
            case 'a' :
                actual_column --;
                break;
            case 'd' :
                actual_column ++;
                break;
            default :
                continue;
        }

        if ( gallego.is_dead ) break;
        move( &actual_row, &actual_column );
        //print_set();
        if ( gallego.is_dead ) break;
    }
    is_game_over = 1;
    return NULL;
}






