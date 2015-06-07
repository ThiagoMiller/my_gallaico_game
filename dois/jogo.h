#define HEIGHT 10
#define WIDTH 10
#define QNT_COINS 5
#define QNT_TRAPS 5

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"

#define CLEAN "\033[J"
#define BECON "\033[s"
#define RESPAWN "\033[u"
#define BEGIN "\033[0;0H"

#define LEFT_BORDER "\t\t\t"
#define VERTICAL_BORDER "\n\n"

enum { BLOCK = '.', COIN = '0', HERO = 'P', DEAD = 'X', TRAP = '~', MONSTER = 'M' };

typedef struct {
	int row;
	int column;
	int is_dead;
} hero;

typedef struct {
    int row;
	int column;
	char on;
	int catched;
} monster;


char getch( void );
void build_set( void );
void raffle( int * );
void* print_set( void * );
void *handle_hero( void * );
void *handle_monster( void * );
int game_over( void );





