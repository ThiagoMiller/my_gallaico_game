#include "stat.h"
#include "clock.h"

#include <stdio.h>
#include <stdlib.h>

//stat_game *stat;

void print_stat_game( void )
{
    get_time_of_day( stat->how_long );

    printf("\033c");

    puts("");

    printf( "\t\t" "\033[0;31m" "+----------------------------------------------+" "\033[0m" "\n" );
    printf( "\t\t" "\033[0;31m" "                    GAME OVER                   " "\033[0m" "\n" );
    printf( "\t\t" "\033[0;31m" "                    SEU TONTO                   " "\033[0m" "\n" );
    printf( "\t\t" "\033[0;31m" "+----------------------------------------------+" "\033[0m" "\n" );

    printf( "\t\t" "\033[0;33m" "\033[7m" "SCORE:" "\033[0m" "\t\t\t\t\t" "%8d" "\n\n", stat->score );

    printf( "\t\t" "\033[0;33m" "TIME:" "\033[0m" "\t\t\t\t\t" "%s" "\n", stat->how_long );
    printf( "\t\t" "\033[0;33m" "COIN:" "\033[0m" "\t\t\t\t\t" "%8d" "\n", stat->coin );
    printf( "\t\t" "\033[0;33m" "FRUITS:" "\033[0m" "\t\t\t\t\t" "%8d" "\n", stat->eat );
    printf( "\t\t" "\033[0;33m" "CAGATE:" "\033[0m" "\t\t\t\t\t" "%8d" "\n", stat->cagate );
    printf( "\t\t" "\033[0;33m" "LIMP:" "\033[0m" "\t\t\t\t\t" "%8d" "\n", stat->limp );
    printf( "\t\t" "\033[0;33m" "TRAP:" "\033[0m" "\t\t\t\t\t" "%8d" "\n", stat->trap );
    printf( "\t\t" "\033[0;33m" "HERO STEP IN BIG SHIT:" "\033[0m" "\t\t\t" "%8d" "\n", stat->hero_step_big_shit );
    printf( "\t\t" "\033[0;33m" "HERO STEP IN SMALL SHIT:" "\033[0m" "\t\t" "%8d" "\n", stat->hero_step_in_small_shit );

    printf( "\t\t" "\033[0;33m" "MONSTER STEP IN BIG SHIT:" "\033[0m" "\t\t" "%8d" "\n", stat->monster_step_in_big_shit );
    printf( "\t\t" "\033[0;33m" "MONSTER STEP IN SMALL SHIT:" "\033[0m" "\t\t" "%8d" "\n", stat->monster_step_in_small_shit );
    printf( "\t\t" "\033[0;33m" "PROVOCATE:" "\033[0m" "\t\t\t\t" "%8d" "\n", stat->provocate );

    printf( "\t\t" "\033[0;33m" "HERO WALKED:" "\033[0m" "\t\t\t\t" "%8d" "\n", stat->hero_walk );
    printf( "\t\t" "\033[0;33m" "MONSTER WALKED:" "\033[0m" "\t\t\t\t" "%8d" "\n", stat->monster_walk );

    printf( "\t\t" "\033[0;31m" "+-----------------------------------------------+" "\033[0m" "\n" );
}

stat_game *create_stat_game( void )
{
    stat_game *stat = ( stat_game* )malloc( sizeof( stat_game ) );

    stat->cagate = 0;
    stat->coin = 0;
    stat->eat = 0;
    stat->limp = 0;
    stat->hero_step_big_shit = 0;
    stat->hero_step_big_shit = 0;
    stat->monster_step_in_big_shit = 0;
    stat->monster_step_in_small_shit = 0;
    stat->trap = 0;
    stat->hero_walk = 0;
    stat->monster_walk = 0;
    stat->provocate = 0;
    stat->score = 0;

    return stat;
}

void init_stat_game( void )
{
    stat = create_stat_game();
}

void score_up( int score )
{
    stat->score = (int)( stat->score + score ) < 0 ? 0 : ( stat->score + score );
}

int get_score( void )
{
    return stat->score;
}

void destroy_stat_game( void )
{
    return;
}

