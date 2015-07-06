#ifndef STAT_H
#define STAT_H

typedef struct {
    char how_long[9];
    unsigned int eat;
    unsigned int coin;
    unsigned int cagate;
    unsigned int trap;
    unsigned int limp;
    unsigned int hero_step_big_shit;
    unsigned int hero_step_in_small_shit;
    unsigned int monster_step_in_big_shit;
    unsigned int monster_step_in_small_shit;
    unsigned int hero_walk;      /* será que é grande o suficiente? */
    unsigned int monster_walk;
    unsigned int provocate;
} stat_game;

stat_game *create_stat_game( void );
void init_stat_game( void );



#endif // STAT_H
