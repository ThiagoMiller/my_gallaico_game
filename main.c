#include "jogo2.h"
#include "thread.h"
#include "getch.h"
#include "audio.h"
#include "characters.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int e;

void print_menu( void )
{
    printf( CLEAN "\n\n" );
/*
  system( "figlet '   as aventuras de'" );
  system( "figlet '         GALLEGUINHO'" );
*/

    system( "toilet --gay -f future '     as aventuras de'" );
    puts("");
    system( "toilet --gay -f pagga '          GALEGUINHO'" );

    printf( "\n\n" "\t\t\t" "      " "%s" "  " "INICIAR JOGO" "  " "\033[0m" "\n\n", e == 0 ? "\033[7m" : "\033[27m" );
    printf( "\t\t\t" "      " "%s" "  " "VER RECORDES" "  " "\033[0m" "\n\n", e == 1 ? "\033[7m" : "\033[27m" );
    printf( "\t\t\t" "      " "%s" "  " "    SAIR    " "  " "\033[0m" "\n\n\n\n\n\n", e == 2 ? "\033[7m" : "\033[27m" );
    printf( "\t\t" "bardos de biotec ilimitados(c) 2015\n\n" );
}

void call_game( void )
{
    init_main_fmod();

    printf( CLEAN  );
    puts("");
    //printf( "\n" LEFT_BORDER "    " PINK " VAI COMEÇAR A BAIXARIA!\n" RESET );
    system( "toilet --gay -f mini 'vai começar a baixaria...'" );
    sleep(2);

    build_set();
    init_threads();
    play_trilha();

    join_threads();

    clean_up_threads();

    release_main_audio();
}

int main()
{
    int c;
    e = 0;

    init_menu_fmod();

    while ( 1 ) {

        print_menu();

        play_alex_kid();

        while ( ( c = getch() ) != '\n' ) {

            switch ( c ) {
                case 'w' :
                    e = e == 0 ? 0 : e - 1;
                    play_menu_ch();
                    break;
                case 's' :
                    e = e == 2 ? 2 : e + 1;
                    play_menu_ch();
                    break;
                default :
                    continue;
            }

            print_menu();
            update_menu_audio();

        }

        stop_alex_kid();

        if ( e == 0 )
            call_game();
        else if ( e == 1 )
            ;
        else
            break;

    }

    printf( CLEAN );
    resetTermios();
    release_menu_audio();

    return 0;
}
