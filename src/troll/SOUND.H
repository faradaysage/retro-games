/*
**      SOUND.H
**
**      Prototypes for SOUND.C, see SOUND.C for documentation.
*/


#ifndef SOUND_H
#define SOUND_H

#define MAX_SOUNDS_PLAYING 4
#define NUM_SOUNDS 8

#define throw_sound 0
#define hit_sound   1
#define miss_sound  2
#define shoot_sound 3
#define saw_sound   4
#define littlepickaxe_sound 5
#define bigpickaxe_sound 6
#define fire_sound 7
#define personhit_sound 8

#define SOUND_CHANNEL 10

#include <AUDIO.H>
#include <IMPORT.H>
#include <TIMER.H>

extern DSM *CurMusic;
extern Sample *sounds[NUM_SOUNDS];


void InitSoundCard(void);
void LoadMusic(char *filename, int Form);
void PlayMusic(void);
void StopMusic(void);
void dPollTimer(void);
void InitSounds(void);
void PlaySound(char);
void UpdateSounds(void);

#endif


