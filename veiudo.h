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
    pos *pos;
 //   flag *flag;
    status *printable;
} monster;

monster *create_monster( pos* );

void init_monster( void );
void* handle_monster( void* );
pos get_monster_pos( void );
void set_monster_pos( pos );


#endif // MONSTER_H
