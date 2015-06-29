typedef struct {
    int hrs;
    int min;
    int sec;
} clock_game;

void get_time_of_day( char *format );
int get_sec( void );
void* handle_time( void* );
