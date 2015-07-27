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



#endif // MONSTER_H
