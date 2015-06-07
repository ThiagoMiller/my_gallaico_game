#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <jogo.h>

//static char set[ WIDTH ][ HEIGHT ];
//int score = 0;

static game_data _for_this_match = { .score = 0 };


int game_over( void )
{
    set_trilha_pause();
    play_morte();

	printf( LEFT_BORDER "\033[6C" RED "  GAME OVER" RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "+----------------+" RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "     SEU TONTO   " RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "    PONTUAÇÃO %d " RESET "\n", _for_this_match.score );
	printf( LEFT_BORDER "\033[3C" RED "+----------------+" RESET "\n\n" );

    play_tonto();
    release_audio();

    resetTermios();

	exit( 666 );
}

void print_set( void )
{
//	static int inicialized = 0;
	int is_dead = 0;
/*
	if ( !inicialized ) {
		printf( BECON CLEAN );
		inicialized++;
	}
*/
	printf( RESPAWN CLEAN VERTICAL_BORDER );
    //printf( CLEAN BEGIN VERTICAL_BORDER );
	int i, j;

	printf( LEFT_BORDER "   " );
	for ( i = 0; i < WIDTH; i++ )
		printf( "%d ", i );

	puts("");
	for ( i = 0; i < HEIGHT; i++ ) {
		printf( LEFT_BORDER "%d  ", i );
		for ( j = 0; j < WIDTH; j++ ) {
            char obj = get_( i, j );
			switch ( obj ) {
				case HERO      :   printf( BOLDGREEN   "%c "   RESET, obj ); break;
				case COIN      :   printf( BOLDYELLOW  "%c "   RESET, obj ); break;
				case TRAP      :   printf( BOLDBLUE    "%c "   RESET, obj ); break;
				case MONSTER   :   printf( SAGOL       "%c "   RESET, obj ); break;
				case DEAD :
					printf( BOLDRED "%c " RESET, obj );
					is_dead = 1;
					break;
				default : printf( WHITE "%c " RESET, obj );
			}
		}
		puts("");
	}
	printf( "\n" LEFT_BORDER YELLOW "MOEDAS:" RESET" %d", _for_this_match.score );
	printf( VERTICAL_BORDER );

	/*if ( gallego.is_dead || is_game_over ) {
        break;
    }
    */
    if ( is_dead ) game_over();
}

void set_( int row, int column, char body  )
{
    _for_this_match.arena[ row ][ column ] = body;
}

char get_( int row, int column )
{
    return _for_this_match.arena[ row ][ column ];
}

// Unificar os moves??? E os _inicialize???
void move_to( pos *pos, int actual_row, int actual_column, char body )
{
    lock();

    set_( pos->row, pos->column, pos->on );

    if ( body == MONSTER )
        pos->on = get_( actual_row, actual_column );
    else
        if ( get_( actual_row, actual_column ) == COIN ) {
            _for_this_match.score++;
            play_action_moeda();
        }
    set_( actual_row, actual_column, body );
    pos->row = actual_row, pos->column = actual_column;

    print_set();
    update_audio();

    unlock();
}


void raffle( int *coord )
{
	static int tabu[ 2 + QNT_COINS + QNT_TRAPS ][ 2 ], acm = 0;

	srand(time(NULL));

	NEXT_TRY: while ( 1 ) {
		int xrand = rand() % WIDTH, yrand = rand() % HEIGHT, i;

		for ( i = 0; i < acm; i++ ) {
			if ( tabu[i][0] == xrand && tabu[i][1] == yrand )
				goto NEXT_TRY;
		}

		tabu[ acm ][ 0 ] = xrand, tabu[ acm ][ 1 ] = yrand;
		coord[0] = xrand, coord[1] = yrand;
		break;
	}
	acm++;
}

void build_set( void )
{
    int coord[2];

	int i, j;
	for (i=0; i < HEIGHT; i++)
		for (j=0; j < WIDTH; j++)
			set_( i, j, BLOCK );


	for ( i = 0; i < QNT_COINS; i++ ) {
		raffle( coord );
		set_( coord[0], coord[1], COIN );
	}

	for ( i = 0; i < QNT_TRAPS; i++ ) {
		raffle( coord );
		set_( coord[0], coord[1], TRAP );
	}
}

