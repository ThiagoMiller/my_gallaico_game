#ifndef HANDLE_HERO_H
#define HANDLE_HERO_H

#include "gallego.h"
#include "set.h"

void* handle_hero( void* );
void init_hero( void );
pos get_hero_pos( void );
void hero_dead( void );
int is_hero_dead(void);
int get_score(void);
char *get_bosta_format( void );


void found_fruit( cell* );
void found_coin( cell* );
void found_big_bosta( cell* );
void found_little_bosta( cell* );
void found_trap( cell* );


#endif // HANDLE_HERO_H
