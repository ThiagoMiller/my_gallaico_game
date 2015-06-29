#include "set.h"
#include "thread.h"
#include "jogo2.h"
#include "clock.h"
#include "gallego.h"

#include <stdio.h>
#include <unistd.h>


static arena for_this_match;


status *default_status( void )
{
    static status _default_status = { .color = WHITE, .body = BLOCK };
    return &_default_status;
}

void print_set( void )
{
	char format[9];
	get_time_of_day( format );

    int i, j;
    cell *celula;
    status *printable; // *_default_status = &default_status;

	printf( CLEAN RESPAWN  VERTICAL_BORDER );
    //printf( CLEAN BEGIN VERTICAL_BORDER );

    printf( LEFT_BORDER BLUE_B "TIME: %s\n\n" RESET ,format );

	printf( LEFT_BORDER  );

    for ( i = 0; i < WIDTH * 2 + 5 ; i++ )
		printf( WHITE_B " " RESET);

	puts("");
	for ( i = 0; i < HEIGHT; i++ ) {
        printf( LEFT_BORDER WHITE_B "  " RESET " " );
        for ( j = 0; j < WIDTH; j++ ) {
            celula = get_cell( create_pos( i, j ) );
            printable = celula->layer0 != NULL ? celula->layer0 : celula->layer1 != NULL ? celula->layer1 : default_status() ;
            printf( "%s" "%c" RESET " ", printable->color, printable->body );
		}
		printf(  WHITE_B "  " RESET );
		puts("");
	}
    printf(  LEFT_BORDER  );
	for ( i = 0; i < WIDTH * 2 + 5; i++ )
		printf( WHITE_B " " RESET);

	//printf( "\n" LEFT_BORDER YELLOW "MOEDAS:" RESET" %d", get_score() );
	printf( VERTICAL_BORDER );

  //update_audio();
  //if ( is_dead ) game_over();
}

void* handle_set( void *a )
{
    while ( !is_hero_dead() ) {
        print_set();
        usleep( 1000000/24 );
    }
    print_set();

    return NULL;
}


void set_cell( pos next_pos, status *printable, TYPE_BODY body )
{
    if ( body == CHAR )
        for_this_match[next_pos.row][next_pos.col].layer0 = printable;
    else
        for_this_match[next_pos.row][next_pos.col].layer1 = printable;
}

void unset_cell( pos actual_pos, TYPE_BODY body ) {
    if ( body == CHAR )
        for_this_match[actual_pos.row][actual_pos.col].layer0 = NULL;
    else
        for_this_match[actual_pos.row][actual_pos.col].layer1 = NULL;
}

cell *get_cell( pos pos )
{
  return &for_this_match[pos.row][pos.col];
}
// as camadas funcionarão de maneira que a 0 receba sempre uma personagem, a 1 um objeto e a 3 sempre será o piso
// o herós quando for a uma posição com um objeto, ele recebe o bônus e destrói esse objeto.
void init_arena( void )
{
  for_this_match = create_arena();
}

void move_to( pos actual_pos, pos next_pos, status *printable )
{
    lock();

    unset_cell( actual_pos, CHAR );
    set_cell( next_pos, printable, CHAR );

    unlock();
}

