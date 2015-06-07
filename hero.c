#include <stdio.h>
#include <jogo.h>

hero gallego;

static void move( int *actual_row, int *actual_column  )
{
	if ( *actual_column >= 0 && *actual_column < WIDTH && *actual_row >= 0 && *actual_row < HEIGHT ) {
        char on = get_( *actual_row, *actual_column );

       // if ( on == COIN ) score++;

        char body = ( on == TRAP || on == MONSTER ) ? DEAD : HERO;
		/*if ( on == TRAP || on == MONSTER ) {
            gallego.is_dead = 1;
            move_to( &gallego.pos, actual_row, actual_column, DEAD );

			return;
			//print_set();
		}
            */
        play_action_walking();
        move_to( &gallego.pos, *actual_row, *actual_column, body );


	} else {
        play_limite();
		*actual_column = gallego.pos.column, *actual_row = gallego.pos.row;
	}
}

static void _inicialize( void )
{
    int coord[2];
	raffle( coord );

	gallego.pos.row = coord[0], gallego.pos.column = coord[1];
	gallego.pos.on = BLOCK;
	gallego.is_dead = 0;

	set_( gallego.pos.row, gallego.pos.column, HERO );

	print_set();
}

void* handle_hero( void *a )
{
    _inicialize();
    int direction, actual_column = gallego.pos.column, actual_row = gallego.pos.row;
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

        move( &actual_row, &actual_column );

    }

    return NULL;
}






