#include <characters.h>

#define WET "\033[1m\033[32m\033[44m"
#define SHITTED "\033[38;5;93m\033[48;5;58m"
#define STOPPED "\033[38;5;93m\033[43m"
#define DEFAULT "\033[38;5;93m"

typedef struct {
    unsigned int wet:1;
    unsigned int stopped:1;
    unsigned int shitted:1;
} flag;

typedef struct {
    pos *pos;
    flag *flag;
    status *printable;
} monster;
