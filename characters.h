#ifndef CHARACTERS_H
#define CHARACTERS_H

#define HEIGHT 14
#define WIDTH 16
#define QNT_COINS 3
#define QNT_TRAPS 10
#define QNT_FRUIT 3

// reset color
#define RESET   "\033[0m"

// foreground color
#define WHITE   "\033[37m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define PINK    "\033[38;5;161m"
#define SAGOL   "\033[38;5;93m"
#define BROWN   "\033[38;5;58m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"

// background color
#define BLUE_B "\033[44m"
#define RED_B "\033[41m"
#define BROWN_B "\033[48;5;58m"
#define WHITE_B "\033[0;47m"
#define YELLOW_B "\033[43m"
#define GREEN_B "\033[48;5;40m"

// control console position
//#define CLEAN "\033[2J"
#define CLEAN "\033c"
#define BECON "\033[s"
#define RESPAWN "\033[u"
#define BEGIN "\033[0;0H"

// borders
#define LEFT_BORDER "\t\t\t"
#define VERTICAL_BORDER "\n\n"

typedef struct {
    int row;
    int col;
} pos;

typedef struct {
    char *color;
    char body;
    unsigned int available:1;
} status;

typedef struct {
    pos *pos;
    status *printable;
 } obj;

typedef enum {
  OBJ, CHAR
} TYPE_BODY;

enum { BLOCK = '.', COIN = '0', HERO = 'G', DEAD = 'X', TRAP = '~', MONSTER = 'M', FRUIT = 'f', BOSTA = 's', L_BOSTA = ';' };

enum state {
    DEFAULT_HERO_COLOR,
    DEFAULT_MONSTER_COLOR,
    LIMP_COLOR,
    CAGATE_COLOR,
    CAGATED_COLOR,
    DEAD_COLOR,
    STEP_IN_SHIT_COLOR,
    STOPPED_UP_COLOR,
    WET_COLOR
};


#endif // CHARACTERS_H
