#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <jogo.h>


static game_data _for_this_match = { .score = 0 };


void set_( int row, int column, char body  )
{
    _for_this_match.arena[ row ][ column ] = body;
}

char get_( int row, int column )
{
    return _for_this_match.arena[ row ][ column ];
}

void score_up( void )
{
    _for_this_match.score ++;
}

int get_score( void )
{
    return _for_this_match.score;
}

int game_over( void )
{
    set_trilha_pause();
    play_morte();

	printf( LEFT_BORDER "\033[6C" RED "  GAME OVER" RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "+----------------+" RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "     SEU TONTO   " RESET "\n" );
	printf( LEFT_BORDER "\033[3C" RED "    PONTUAÇÃO %d " RESET "\n", get_score() );
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
	int i, j;
	char color_fruit[20];
	char format[9];
	get_time_of_day( format );
/*
	if ( !inicialized ) {
		printf( BECON CLEAN );
		inicialized++;
	}
*/
	printf( CLEAN RESPAWN  VERTICAL_BORDER );
    //printf( CLEAN BEGIN VERTICAL_BORDER );

    printf( LEFT_BORDER "\033[0;44m" "TIME: %s\n\n" RESET ,format );

	printf( LEFT_BORDER  );
	/*for ( i = 0; i < WIDTH; i++ )
		printf( "%d ", i );
    */
    for ( i = 0; i < WIDTH * 2 + 5 ; i++ )
		printf( "\033[0;47m" " " RESET);

	puts("");
	for ( i = 0; i < HEIGHT; i++ ) {
		printf( LEFT_BORDER "\033[0;47m" "  " RESET " " );
		for ( j = 0; j < WIDTH; j++ ) {
            char obj = get_( i, j );
			switch ( obj ) {
				case HERO      :
                    if ( is_gallego_cagating() )
                         printf( BOLDGREEN "\033[48;5;58m"  "%c" RESET " ", obj );
                    else if ( is_hero_mancado() )
                        printf( BOLDGREEN "\033[41m"  "%c"   RESET " ", obj );
                    else
                        printf( BOLDGREEN   "%c "   RESET, obj );
                    break;
                case BOSTA:
                    printf( "\033[38;5;58m"  "%c " RESET, obj ); break;
				case COIN      :   printf( BOLDYELLOW  "%c "   RESET, obj ); break;
				case TRAP      :   printf( BOLDBLUE    "%c "   RESET, obj ); break;
				case FRUIT     :
                    get_color_fruit( color_fruit, i, j );
                    printf(  "%s%c "   RESET, color_fruit, obj ); break;
				case MONSTER   :
                    if ( is_monster_shited() )
                         printf( SAGOL "\033[48;5;58m" "%c" RESET " ", obj );
                    else if (  is_monster_stopped() )
                        printf( SAGOL "\033[43m" "%c" RESET " ", obj );
                    else if ( is_monster_wet()  )
                        printf( RED "\033[44m"    "%c"   RESET " ", obj );
                    else
                        printf( SAGOL       "%c "   RESET, obj );
                    break;
				case DEAD :
					printf(  BOLDRED "\033[43m" "%c" RESET " ", obj );
					is_dead = 1;
					break;
				default : printf( WHITE "%c " RESET, obj );
			}
		}
		printf(  "\033[0;47m" "  " RESET );
		puts("");
	}
    printf(  LEFT_BORDER  );
	for ( i = 0; i < WIDTH * 2 + 5; i++ )
		printf( "\033[0;47m" " " RESET);

	printf( "\n" LEFT_BORDER YELLOW "MOEDAS:" RESET" %d", get_score() );
	printf( VERTICAL_BORDER );

	/*if ( gallego.is_dead || is_game_over ) {
        break;
    }
    */
    update_audio();
    if ( is_dead ) game_over();
}

void* handle_set( void *a )
{
    while ( 1 ) {
        print_set();
        usleep( 1000000/24 );
    }

    return NULL;
}





// Unificar os moves??? E os _inicialize???
void move_to( pos old_pos, pos new_pos, char body )
{
    lock();//

    set_( old_pos.row, old_pos.column, old_pos.on );//

  //  if ( body == MONSTER )
   //     pos->on = get_( actual_row, actual_column );
   // else
     //   if ( get_( actual_row, actual_column ) == COIN ) {
       //     _for_this_match.score++;
        //    play_action_moeda();
        //}
    set_( new_pos.row, new_pos.column, body );//

    //print_set();//
    //update_audio();//

    unlock();//
}


void raffle( int *coord )
{
    int column_rand, row_rand;

    while ( 1 ) {
        column_rand = get_rand( WIDTH ), row_rand = get_rand( HEIGHT );
        if ( get_( row_rand, column_rand ) != BLOCK )
            continue;

		coord[0] = row_rand, coord[1] = column_rand;
		break;
	}
}

int get_rand( int untill )
{
    static int inicialized = 0;
    if ( !inicialized ) {
        srand(time(NULL));
        inicialized = 1;
    }

    return rand() % untill;
}

void build_set( void )
{
    int coord[2];
	int i, j;
	pos actual_pos = { .on = BLOCK };

	// set arena
	for (i=0; i < HEIGHT; i++)
		for (j=0; j < WIDTH; j++)
			set_( i, j, BLOCK );

    // set coins pos
	for ( i = 0; i < QNT_COINS; i++ ) {
		raffle( coord );
		set_( coord[0], coord[1], COIN );
	}


    // set traps pos
	for ( i = 0; i < QNT_TRAPS; i++ ) {
		raffle( coord );
		set_( coord[0], coord[1], TRAP );
	}

	// set hero pos
	raffle( coord );
	set_( coord[0], coord[1], HERO );
	actual_pos.row = coord[0], actual_pos.column = coord[1];
  set_hero_pos( actual_pos );

	// set monster pos
	raffle( coord );
	set_( coord[0], coord[1], MONSTER );
	actual_pos.row = coord[0], actual_pos.column = coord[1];
	set_monster_pos( actual_pos );

    // first print
    print_set();

}
