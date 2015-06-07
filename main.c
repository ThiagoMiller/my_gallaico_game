#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <jogo.h>


int main()
{
    init_fmod();
    system( "clear" );

    printf( BECON "\n" LEFT_BORDER PINK " VAI COMEÇAR A BAIXARIA!\n" RESET );
    sleep(2);

    build_set();
    init_threads();
    play_trilha();

    join_threads();

    release_audio();
    release_threads();

    return 0;
}
