#include <characters.h>

#define  WET "\033[1m\033[32m\033[44m"
#define  LIMPPING "\033[1m\033[32m\033[41m"
#define  CAGATING "\033[1m\033[32m\033[48;5;58m"
#define  DEFAULT "\033[1m\033[32m"


typedef struct {
    unsigned int wet:1;
    unsigned int limpping:1;
    unsigned int trying_cagate:1;
    unsigned int cagating:1;
    unsigned int dead:1;
} flag;


typedef struct {
    pos *pos;
    flag *flag;
    status *printable;
    unsigned int eated_fruts:2;
    unsigned int score;
} hero;

hero *create_hero( pos* );

