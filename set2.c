#include "set.h"
#include <stdio.h>
#include <stdlib.h>

arena create_arena( void )
{
    int i, j;
    arena for_this_match = ( arena )malloc( sizeof( cells ) );

    for ( i = 0; i < HEIGHT; i++ )
      for ( j = 0; j < WIDTH; j++ )
        for_this_match[i][j].layer0 = NULL, for_this_match[i][j].layer1 = NULL;

    return for_this_match;
}
