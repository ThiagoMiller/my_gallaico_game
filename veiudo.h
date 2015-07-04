#ifndef MONSTER_H
#define MONSTER_H

#include <characters.h>

/*
typedef struct {
    unsigned int wet:1;
    unsigned int stopped:1;
    unsigned int shitted:1;
} flag;*/

typedef struct {
    obj *obj;
    unsigned int stepped_in_shit:1;
} monster;


monster *create_monster( pos* );

void init_monster( void );
void* handle_monster( void* );
pos get_monster_pos( void );


#endif // MONSTER_H
