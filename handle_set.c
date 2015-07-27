#include "handle_set.h"
#include "thread.h"
#include "jogo2.h"
#include "handle_hero.h"
#include "clock.h"
#include "audio.h"
#include "stat.h"

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

	printf( CLEAN VERTICAL_BORDER );
    //printf( CLEAN BEGIN VERTICAL_BORDER );

    printf( LEFT_BORDER BLUE_B "TIME: %s\n\n" RESET ,format );

	printf( LEFT_BORDER  );

    for ( i = 0; i < WIDTH * 2 + 5 ; i++ )
		printf( WHITE_B " " RESET);

    printf( LEFT_BORDER );

    //for ( i = 0; i < WIDTH + 10; i++ )
     //   printf( BLUE_B " " RESET);
     //printf( RED_B "\t\t\t" RESET ); Report
     //printf( BLUE_B YELLOW "\t" "SCORE:" WHITE " %d" "\t" RESET, get_score() );

	puts("");
	for ( i = 0; i < HEIGHT; i++ ) {
        printf( LEFT_BORDER WHITE_B "  " RESET " " );
        for ( j = 0; j < WIDTH; j++ ) {
            celula = get_cell( create_pos( i, j ) );
            printable = celula->layer0 != NULL ? celula->layer0 : celula->layer1 != NULL ? celula->layer1 : default_status() ;
            printf( "%s" "%c" RESET " ", printable->color, printable->body );
		}
		printf(  WHITE_B "  " RESET );
		//printf( LEFT_BORDER  "\033[48;5;8m"  "\t\t\t" RESET  ); Report
		puts("");
	}
    printf(  LEFT_BORDER  );
	for ( i = 0; i < WIDTH * 2 + 5; i++ )
		printf( WHITE_B " " RESET);

    //printf( LEFT_BORDER RED_B "\t\t\t" RESET ); report

	printf( "\n\n" LEFT_BORDER YELLOW "SCORE:" RESET" %d", get_score() );
	printf( "\t\t  " "%s" RESET, get_bosta_format() );
	printf( VERTICAL_BORDER );

  //update_audio();
  //if ( is_dead ) game_over();
}

void game_over()
{
    print_set();

    set_trilha_pause();
    play_morte();

    usleep(2000000);

    print_stat_game();

    play_tonto();

    usleep(1500000);
}

void* handle_set( void *a )
{
    while ( !is_hero_dead() ) {
        print_set();
        update_audio();
        usleep( 1000000/24 );
    }

    game_over();

    return NULL;
}


void set_cell( obj *obj, TYPE_BODY body )
{
    if ( body == CHAR )
        for_this_match[obj->pos->row][obj->pos->col].layer0 = obj->printable;
    else
        for_this_match[obj->pos->row][obj->pos->col].layer1 = obj->printable;
}

void unset_cell( pos *actual_pos, TYPE_BODY body ) {
    if ( body == CHAR )
        for_this_match[actual_pos->row][actual_pos->col].layer0 = NULL;
    else
        for_this_match[actual_pos->row][actual_pos->col].layer1 = NULL;
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

void move_to( obj *obj, pos next_pos )
{
    lock();

    unset_cell( obj->pos, CHAR );
    *obj->pos = next_pos;
    set_cell( obj, CHAR );

    unlock();
}

