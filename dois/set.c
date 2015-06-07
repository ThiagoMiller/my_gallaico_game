#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <jogo.h>

char set[ WIDTH ][ HEIGHT ];
int score = 0;

extern int is_game_over;
extern hero gallego;


int game_over( void )
{
	fprintf( stderr, LEFT_BORDER "\033[6C" RED "GAME OVER" RESET "\n" );
	fprintf( stderr, LEFT_BORDER "\033[3C" RED "+-------------+" RESET "\n" );
	fprintf( stderr, LEFT_BORDER "\033[3C" RED "|  SEU TONTO  |" RESET "\n" );
	fprintf( stderr, LEFT_BORDER "\033[3C" RED "| PONTUAÇÃO %d |" RESET "\n", score );
	fprintf( stderr, LEFT_BORDER "\033[3C" RED "+-------------+" RESET "\n\n" );
	exit( 2 );
}

void* print_set( void* a )
{
	while ( 1 ) {

	static int inicialized = 0;
	//int is_dead = 0;

	if ( !inicialized ) {
		printf( BECON CLEAN );
		inicialized++;
	}

	printf( RESPAWN VERTICAL_BORDER );

	int i, j;

	printf( LEFT_BORDER "   " );
	for ( i = 0; i < WIDTH; i++ )
		printf( "%d ", i );

	puts("");
	for ( i = 0; i < HEIGHT; i++ ) {
		printf( LEFT_BORDER "%d  ", i );
		for ( j = 0; j < WIDTH; j++ ) {
			switch ( set[i][j] ) {
				case HERO : printf( BOLDGREEN "%c " RESET, set[i][j] ); break;
				case COIN : printf( BOLDYELLOW "%c " RESET, set[i][j] ); break;
				case TRAP : printf( BOLDBLUE "%c " RESET, set[i][j] ); break;
				case DEAD :
					printf( BOLDRED "%c " RESET, set[i][j] );
					//is_dead = 1;
					break;
				default : printf( WHITE "%c " RESET, set[i][j] );
			}
		}
		puts("");
	}
	printf( "\n" LEFT_BORDER YELLOW "MOEDAS:" RESET" %d", score );
	printf( VERTICAL_BORDER );

	if ( gallego.is_dead || is_game_over ) {
        break;
    }
  //  sleep(2);
    }
    return NULL;
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
			set[i][j] = BLOCK;


	for ( i = 0; i < QNT_COINS; i++ ) {
		raffle( coord );
		set[ coord[0] ][ coord[1] ] = COIN;
	}

	for ( i = 0; i < QNT_TRAPS; i++ ) {
		raffle( coord );
		set[ coord[0] ][ coord[1] ] = TRAP;
	}
}

