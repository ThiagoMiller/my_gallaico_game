#define HEIGHT 10
#define WIDTH 10
#define QNT_COINS 10
#define QNT_TRAPS 10
#define QNT_FRUIT 3

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define PINK    "\033[38;5;161m"
#define SAGOL   "\033[38;5;93m"
#define BOLDWHITE   "\033[1m\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"

#define CLEAN "\033[2J"
#define BECON "\033[s"
#define RESPAWN "\033[u"
#define BEGIN "\033[0;0H"

#define LEFT_BORDER "\t\t\t"
#define VERTICAL_BORDER "\n\n"

enum { BLOCK = '.', COIN = '0', HERO = 'G', DEAD = 'X', TRAP = '~', MONSTER = 'M' };

typedef struct {
    char arena[ HEIGHT ][ WIDTH ];
    unsigned int score;
} game_data;

typedef struct {
    int row;
    int column;
    char on;
} pos;


typedef struct {
	pos pos;
	unsigned int is_dead:1;
} hero;

typedef struct {
    pos pos;
	unsigned int catched:1;
	unsigned int wet:1;
	int wet_sec;
} monster;

typedef struct {
    int hrs;
    int min;
    int sec;
} clock_game;

typedef struct {
    char data[ QNT_COINS + QNT_FRUIT + QNT_TRAPS + 2 ][2];
    int ptr;
} lista;


char getch( void );
void resetTermios( void );

char get_( int, int );
void set_( int, int, char );
int get_score( void );
void score_up( void );
void build_set( void );

void move_to( pos, pos, char );
void raffle( int * );
void print_set( void );

void *handle_hero( void * );
void *handle_monster( void * );
void* handle_set( void * );
void* handle_time( void * );
int game_over( void );

void init_threads();
void join_threads();
void lock();
void unlock();
void release_threads();

pos get_hero_pos( void );
void set_hero_pos( pos );
void hero_dead( void );
int is_hero_dead(void);

void set_monster_pos( pos  );
int is_monster_wet( void );

void init_fmod( void );
void play_trilha( void );
void play_tonto( void );
void play_action_moeda();
void play_action_walking();
void play_morte();
void play_monstro();
void set_walking_volume( float );
void play_limite();
void set_trilha_pause();
void play_wet1();
void play_wet2();
void play_mancando1();
void play_mancando2();
void update_audio();
/*void release_trilha( void );
void release_tonto( void );
void release_actions();
void release_system( void );*/
void release_audio( void );

void get_time_of_day( char *);
int get_sec( void );




