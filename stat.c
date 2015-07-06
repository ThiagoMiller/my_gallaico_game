#include "stat.h"

#include <stdio.h>
#include <stdlib.h>

stat_game *stat;

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

    return stat;
}

void init_stat_game( void )
{
    stat = create_stat_game();
}

void destroy_stat_game( void )
{
    return;
}

