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
    obj *obj;
    unsigned int cagating:1;
    unsigned int cagated:1;
    unsigned int limpping:1;
    unsigned int trapped:1;
    unsigned int dead:1;
    unsigned int eated_fruts:2;
    unsigned int score;
} hero;


hero *create_hero( pos* );



#endif // HERO_H
