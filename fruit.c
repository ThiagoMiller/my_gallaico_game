#include "fruit.h"
#include "jogo2.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    int num_fruit;
    char color_fruit[HEIGHT][WIDTH][30];
} fruit;

static fruit salada_mista = { 0 };


int get_num_fruit( void )
{
    return salada_mista.num_fruit;
}

void get_color_fruit( char *color_fruit, int row, int column )
{
     strcpy( color_fruit, salada_mista.color_fruit[row][column] );
}

void more_num_fruit( void )
{
    salada_mista.num_fruit ++;
}

void menos_fruit( void )
{
    salada_mista.num_fruit --;
}


void _set_fruit( void )
{
    int coord[2];
    char *color;

    raffle( coord );
    set_( coord[0], coord[1], FRUIT );
    more_num_fruit();
    switch( get_rand(4) ) {
        case 0: color = RED; break;
        case 1: color = YELLOW; break;
        case 2: color = MAGENTA; break;
        default: color = GREEN;
    }
    strcpy( salada_mista.color_fruit[coord[0]][coord[1]], color );

}

void set_fruit( int num ) {
    int i;
    for ( i = 0; i < num; i++ ) {
        _set_fruit();
        usleep( 500000 );
    }
}

void *handle_fruit( void *a )
{
   // int elapsed, start, coord[2];
    //start = get_sec();
    while ( !is_hero_dead() ) {
        usleep( 8000000 );
        if ( get_num_fruit() == MAX_FRUIT )
            continue;

        switch ( get_rand(10) ) {
            case 7:
            case 8: set_fruit(2); break;
            case 9: set_fruit(3); break;
            default: set_fruit(1);
        }

    }

    return NULL;
}
