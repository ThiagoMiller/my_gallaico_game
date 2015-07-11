#include "audio.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fmod.h>
#include <fmod_errors.h>

static FMOD_SYSTEM *fmod_system, *fmod_system2;
static FMOD_SOUND *trilha, *tonto, *action_moeda, *action_walking, *morte, *limite, *monstro, *owyeh, *wet, *mancando1, *mancando2, *madrecita, *alex_kid, *menu_ch;
static FMOD_CHANNEL *trilha_channel, *alex_kid_channel;
static FMOD_RESULT result;

//FMOD_REVERB3D *shalosh;

static int on = 0;

void fmod_check_errors( FMOD_RESULT result )
{
    if ( result != FMOD_OK ) {
        fprintf( stderr, "FMOD error! (%d) %s", result, FMOD_ErrorString( result ) );
        exit( 1 );
    }
}

void init_main_fmod()
{

    result = FMOD_System_Create( &fmod_system );
    fmod_check_errors( result );

    result = FMOD_System_Init( fmod_system, 32, FMOD_INIT_NORMAL, NULL );
    fmod_check_errors( result );

    result = FMOD_System_CreateStream( fmod_system, "Audio/trilha.mp3", FMOD_LOOP_NORMAL, 0, &trilha  );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/tonto.wav", FMOD_DEFAULT, 0, &tonto );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/moeda.wav", FMOD_DEFAULT, 0, &action_moeda );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/walking.mp3", FMOD_DEFAULT, 0, &action_walking );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/morte.wav", FMOD_DEFAULT, 0, &morte );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/limite.wav", FMOD_DEFAULT, 0, &limite );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/monstro.mp3", FMOD_DEFAULT, 0, &monstro );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/owyeh.wav", FMOD_DEFAULT, 0, &owyeh );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/wet.wav", FMOD_DEFAULT, 0, &wet );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/mancando1.wav", FMOD_DEFAULT, 0, &mancando1 );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/mancando2.wav", FMOD_DEFAULT, 0, &mancando2 );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system, "Audio/madrecita.wav", FMOD_DEFAULT, 0, &madrecita );
    fmod_check_errors( result );

   // FMOD_System_CreateReverb3D( fmod_system, &shalosh );
}

void init_menu_fmod()
{
    result = FMOD_System_Create( &fmod_system2 );
    fmod_check_errors( result );

    result = FMOD_System_Init( fmod_system2, 32, FMOD_INIT_NORMAL, NULL );
    fmod_check_errors( result );

    result = FMOD_System_CreateStream( fmod_system2, "Audio/alex_kid.mp3", FMOD_LOOP_NORMAL, 0, &alex_kid  );
    fmod_check_errors( result );

    result = FMOD_System_CreateSound( fmod_system2, "Audio/menu_ch.mp3", FMOD_DEFAULT, 0, &menu_ch );
    fmod_check_errors( result );
}


void play_trilha()
{
    result = FMOD_System_PlaySound( fmod_system, trilha, 0,0, &trilha_channel );
    fmod_check_errors( result );
    on = 1;

    result = FMOD_Channel_SetVolume( trilha_channel, 0.4 );
    fmod_check_errors( result );
}

void play_alex_kid()
{
    result = FMOD_System_PlaySound( fmod_system2, alex_kid, 0,0, &alex_kid_channel );
    fmod_check_errors( result );

    result = FMOD_Channel_SetVolume( alex_kid_channel, 0.5 );
    fmod_check_errors( result );
}

void stop_alex_kid()
{
    result = FMOD_Channel_Stop( alex_kid_channel );
    fmod_check_errors( result );
}

void stop_trilha()
{
    result = FMOD_Channel_Stop( trilha_channel );
    fmod_check_errors( result );
}

void set_trilha_pause()
{
    if ( ! on )
        return;

    result = FMOD_Channel_SetPaused( trilha_channel, 1 );
    fmod_check_errors( result );
}

void play_monstro()
{
    result = FMOD_System_PlaySound( fmod_system, monstro, 0 ,0 ,NULL );
    fmod_check_errors( result );
}

void play_morte()
{
    result = FMOD_System_PlaySound( fmod_system, morte, 0 ,0 ,NULL );
    fmod_check_errors( result );
    //usleep(1300000);
}

void play_limite()
{
    result = FMOD_System_PlaySound( fmod_system, limite, 0 ,0 ,NULL );
    fmod_check_errors( result );
}

void play_action_moeda()
{
    result = FMOD_System_PlaySound( fmod_system, action_moeda, 0 ,0 ,NULL );
    fmod_check_errors( result );
}

void play_action_walking()
{
    result = FMOD_System_PlaySound( fmod_system, action_walking, 0 ,0 ,0 );
    fmod_check_errors( result );
}

/*void set_walking_volume( float v )
{
    result = FMOD_Channel_SetVolume( walking_channel ,v );
    fmod_check_errors( result );
}
*/

void play_tonto()
{
    result = FMOD_System_PlaySound( fmod_system, tonto, 0,0,0 );
    fmod_check_errors( result );
    sleep( 3 );
}

void play_owyeh()
{
    result = FMOD_System_PlaySound( fmod_system, owyeh, 0,0,0 );
    fmod_check_errors( result );
}

void play_wet()
{
    result = FMOD_System_PlaySound( fmod_system, wet, 0,0,0 );
    fmod_check_errors( result );
}

void play_mancando1()
{
    result = FMOD_System_PlaySound( fmod_system, mancando1, 0,0,0 );
    fmod_check_errors( result );
}

void play_mancando2()
{
    result = FMOD_System_PlaySound( fmod_system, mancando2, 0,0,0 );
    fmod_check_errors( result );
}

void play_madrecita()
{
    result = FMOD_System_PlaySound( fmod_system, madrecita, 0,0,0 );
    fmod_check_errors( result );
}

void play_menu_ch()
{
    result = FMOD_System_PlaySound( fmod_system2, menu_ch, 0,0,0 );
    fmod_check_errors( result );
}


void update_audio()
{
    result = FMOD_System_Update( fmod_system );
    fmod_check_errors( result );
}

void update_menu_audio()
{
    result = FMOD_System_Update( fmod_system2 );
    fmod_check_errors( result );
}

/*
void release_trilha()
{
     result = FMOD_Sound_Release( trilha );
     fmod_check_errors( result );
}

void release_tonto()
{
    result = FMOD_Sound_Release( tonto );
    fmod_check_errors( result );
}

void release_actions()
{
    result = FMOD_Sound_Release( action_moeda );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( action_walking );
    fmod_check_errors( result );
}



void release_system()
{
    result = FMOD_System_Close(fmod_system);
    fmod_check_errors( result );

    result = FMOD_System_Release(fmod_system);
    fmod_check_errors( result );
}

*/

void release_main_audio()
{
    result = FMOD_Sound_Release( trilha );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( madrecita );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( mancando1 );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( mancando2 );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( owyeh );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( wet );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( limite );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( monstro );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( morte );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( tonto );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( action_moeda );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( action_walking );
    fmod_check_errors( result );

    result = FMOD_System_Close(fmod_system);
    fmod_check_errors( result );

    result = FMOD_System_Release(fmod_system);
    fmod_check_errors( result );

}

void release_menu_audio()
{
    result = FMOD_Sound_Release( alex_kid );
    fmod_check_errors( result );

    result = FMOD_Sound_Release( menu_ch );
    fmod_check_errors( result );

    result = FMOD_System_Close(fmod_system2);
    fmod_check_errors( result );

    result = FMOD_System_Release(fmod_system2);
    fmod_check_errors( result );
}






