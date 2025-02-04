/*
**      SOUND.C
**
**      Sound and music routines that use the Digital Sound Interface Kit
**      v2.0.
*/

/* DSIK 2.0 include files */
#include "sound.h"

/* The current music module */

DSM *CurMusic;

/* Sound samples */
Sample *sounds[NUM_SOUNDS];
char voice_num=0;

/*      InitSoundCard()
**      PRECONDITION : none
**      POSTCONDITION: reads soundcard info from SETUP.CFG and initializes
**                     the card
*/

void InitSoundCard(void)
{
        SoundCard SC;

        dRegisterDrivers();
        if (dLoadSetup(&SC,"SETUP.CFG") || dInit(&SC))
                Error("Error intializing Soundcard.  Please run SETUP.EXE.");
        atexit(dDone);
}

/*
**      LoadMusic()
**      PRECONDITION : filename is the DSM file to open
**      POSTCONDITION: The song specified by filename is loaded into
**                     memory.
*/

void LoadMusic(char *filename, int Form)
{
        if(!(CurMusic = dImportModule(filename, Form)))
                Error("Error loading Music %s.",filename);
        dSetupVoices(CurMusic->Header.NumTracks+MAX_SOUNDS_PLAYING, 255);
	voice_num=CurMusic->Header.NumTracks;
}

/*
**      PlayMusic()
**      PRECONDITION : LoadMusic() has been called
**      POSTCONDITION: Starts song playing and installs an interrupt to
**                     Poll the soundcard 50 times per second.
*/

void PlayMusic(void)
{
        dPlayMusic(CurMusic);

        dInitTimer();

        /* Setup interrupt to poll soundcard 50 times per second */
        dStartTimer((void(*)(void)) dPoll,TICKS(50));        
}

/*
**      StopMusic()
**      PRECONDITION : PlayMusic() has been called
**      POSTCONDITION: stops Soundcard polling and stops playing the song.
*/

void StopMusic(void)
{
        dStopTimer();
        dStopMusic();
}
        
/*
**      InitSounds()
**      PRECONDITION : none
**      POSTCONDITION: Loads sound samples into memory
*/

void InitSounds(void)
{
        if((sounds[throw_sound] = dLoadSample("throw.wav")) == 0)
                Error("Loading THROW.WAV");
        if((sounds[hit_sound] = dLoadSample("hit.wav")) == 0)
                Error("Loading CANHIT.WAV");
	if((sounds[miss_sound] = dLoadSample("miss.wav")) == 0)
                Error("Loading THROW.WAV");
        if((sounds[shoot_sound] = dLoadSample("shoot.wav")) == 0)
                Error("Loading CANHIT.WAV");
	if((sounds[saw_sound] = dLoadSample("saw.wav")) == 0)
                Error("Loading THROW.WAV");
        if((sounds[littlepickaxe_sound] = dLoadSample("lilpicht.wav")) == 0)
                Error("Loading CANHIT.WAV");
	if((sounds[bigpickaxe_sound] = dLoadSample("pickhit.wav")) == 0)
                Error("Loading THROW.WAV");
        if((sounds[fire_sound] = dLoadSample("fire.wav")) == 0)
                Error("Loading CANHIT.WAV");
        if((sounds[personhit_sound] = dLoadSample("perhit.wav")) == 0)
                Error("Loading CANHIT.WAV");
	
	dSetupVoices(MAX_SOUNDS_PLAYING, 255 );
}

void PlaySound(char soundnum){
	dPlayVoice( voice_num, sounds[ soundnum ] );
	++voice_num;
	voice_num = (CurMusic->Header.NumTracks-1)+((voice_num-(CurMusic->Header.NumTracks-1)) % MAX_SOUNDS_PLAYING);

        dInitTimer();

        /* Setup interrupt to poll soundcard 50 times per second */
        dStartTimer((void(*)(void)) dPoll,TICKS(50));        

}

void UpdateSounds(void){
	char index=0;
	char dPolled = 0;

	while( !dPolled && index<NUM_SOUNDS){
		if( dGetVoiceStatus(index) == PS_PLAYING ){
			dPoll();
			dPolled = 1;
		}
		++index;
	}
}