#include <stdio.h>
#include <jogo.h>

static hero gallego = { .is_dead = 0 };

pos get_hero_pos( void )
{
    return gallego.pos;
}

void set_hero_pos( pos actual_pos )
{
    gallego.pos = actual_pos;
}

static void move( pos *actual_pos )
{
    pos gallego_pos = get_hero_pos();

	if ( actual_pos->column >= 0 && actual_pos->column < WIDTH && actual_pos->row >= 0 && actual_pos->row < HEIGHT ) {

        char destiny = get_( actual_pos->row, actual_pos->column );
        char body = ( destiny == TRAP || destiny == MONSTER ) ? DEAD : HERO;

		/*if ( on == TRAP || on == MONSTER ) {
            gallego.is_dead = 1;
            move_to( &gallego.pos, actual_row, actual_column, DEAD );

			return;
			//print_set();
		}
            */

        ////////////////////////////////////
        ///////////////////////////qqq
        play_action_walking();
        move_to( gallego_pos, *actual_pos, body );
        if ( destiny == COIN ) {
            score_up(); // colocar globsl...
            play_action_moeda();
        }

        set_hero_pos( *actual_pos );

	} else {
        play_limite();
		*actual_pos = gallego_pos;
	}
}
/*
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
*/
void* handle_hero( void *a )
{
    //_inicialize();

    pos actual_pos = get_hero_pos();
    int direction;
    while ( ( direction = getch() ) != 'q' ) {

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
            default :
                continue;
        }

        move( &actual_pos );

    }

    return NULL;
}






