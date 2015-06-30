#ifndef HERO_H
#define HERO_H

#include "characters.h"

/*
typedef struct {
    unsigned int wet:1;
    unsigned int limpping:1;
    unsigned int trying_cagate:1;
    unsigned int cagating:1;
    unsigned int dead:1;
} flag;
*/

typedef struct {
    pos *pos;
   // flag *flag;
    unsigned int dead:1;
    status *printable;
    unsigned int eated_fruts:2;
    unsigned int score;
} hero;


hero *create_hero( pos* );
void* handle_hero( void* );
void init_hero( void );
pos get_hero_pos( void );
void set_hero_pos( pos );
void hero_dead( void );
int is_hero_dead(void);

#endif // HERO_H
