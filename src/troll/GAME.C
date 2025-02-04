#include "wad.h"
#include "gamemem.h"
#include <stdio.h>
#include <conio.h>
#include "graphics.h"
#include "keyboard.h"
#include "sprite.h"
#include "main.h"    /* contains some macros and the pic files used */ 
#include "map.h"
#include "colision.h"
#include "main2.h"   /* contains most functions used in here */
#include "inventry.h"
#include "text.h"
#include "sound.h"
#include "timer.h"

#define SYNCH 10

/* collision variables */
collision_type        *collision;             /* collision in map */
bullet_collision_type *bullet_collision;      /* collisions with bullet */

extern short cur_inv;
extern char keyboard[100];
extern char keypressed;

void HandleKeyboardInput( void );
void AdjustAllCharactersFace( void );
void DrawPersonAndObjects( void );
char *c;

void main() {
	int x, y;
        counter_type i;

        printf("Initializing WAD file...\n");
        WAD( "game.wad" );
        Initialize();
        printf("done...\n");
	printf("Initializing soundcard...");
        InitSoundCard();
	printf("done...\n");
	printf("Loading sounds...");
        InitSounds();
	printf("done...\n");
        printf( "Allocating memory..." );
	InitializeMemory();
	printf( "done.\n" );
	printf( "Loading sprites..." );
	InitializeIntro();
	InitializeTalkScreens();
	InitializeSprites();
	InitializeEnergyPics();
	printf( "done.\n" );
	printf( "Loading backgrounds..." );
	InitializeBackgrounds();
	printf( "done.\n" );

	printf( "Loading fonts..." );
        LoadFont();
	printf( "done.\n" );
	printf( "Opening energy pics..." );
	OpenEnergyPics( cur_screen );
	printf( "done\n" );
	printf( "Making page..." );
        MakePage( &page );
	printf( "done.\n" );
        printf( "Creating sprite table..." );fflush(stdout);
        CreateSpriteTable();
        printf( "done.\n" );fflush(stdout);
	init();
	
	StartKeyboardInterrupt();

	LoadMusic( "armani.s3m", FORM_S3M );
	PlayMusic();
	ShowIntro();
        InitializeScreen( cur_screen );
        InitializeInventoryScreen();

startover:

        person->speed = 2;
	while( keyboard[ INDEX_Q ] != 1 ) {
                Synchronize( SYNCH );
		HandleKeyboardInput();

		if( got_diamond && !left_miner_boss ){
			left_miner_boss = 1;
			LoadScreen( cavern );
		}

		collision = CheckCollision( background, person );
		HandleCollision( collision, background, person );
                
                ScrollBackgroundWithSprite( background, person, 2, 2, 90, 60, 180, 80 );
		KeepBackgroundInBounds( background );

		PutBackground( background, page );

		AdjustAllCharactersFace();

                object_that_collided = CheckSpriteCollision( person, objects );

		DrawPersonAndObjects();

		UpdateObjects( &objects, background );

                DrawEnergy();

                if( fadepalettein == 1 ){
                        memset( palette, 0, 768 );
                        setVGApalette( palette );
                }
                DrawScreen( page );

                if( fadepalettein == 1 ){
                        fadepalettein = 0;
                        LoadCurPalette();
                        fade_to_palette( palette, 20 );
                }


                bullet_collision = CheckBulletCollision( objects );
		HandleBulletCollision( bullet_collision, &objects );
		if( energy < 0 ){
			cur_screen = cavern;
			LoadScreen( cavern );
			InitializeEnergy();
			goto startover;
		} 
	}
	HaltKeyboardInterrupt();
	StopMusic();
        deinit();
        DestroySpriteTable();
        CleanupScreen();
        CloseEnergyPics();
        CloseInventoryScreen();
	FreeMemory();
}

void DrawPersonAndObjects( void ){
	static char hit_count=0;

	if( !(object_that_collided != NULL && object_that_collided->info->status == enemy_obj) ){
		hit_count = 0;
	}
        /* in order of precedence */
	if( object_that_collided != NULL && object_that_collided->info->status == enemy_obj){ /* collsion occured */
                DrawObjectsHit( person_hit, objects, background, page );
        	SubtractEnergy( object_that_collided->info->index );
		if( hit_count%10 == 0 ){
			if( object_that_collided->info->index == 1 ){
				if( hit_count%30 == 0 )
					PlaySound( fire_sound );
			}
			PlaySound( personhit_sound );
		}
		++hit_count;
        }
	else if( person_shooting == 1 ){
                if( person_shoot->curframe == 1 )
                   ShootBullet();  /* for timing with frames */

		/* draw person_shoot */
		DrawObjects( person_shoot, objects, background, page );
		IncrCurFrame( person_shoot );
		if( person_shoot->curframe == 0 )
			person_shooting = 0;
	}
	else if( person_throwing == 1 ){
                if( person_throw->curframe == 3 )
                   ThrowRock();  /* for timing with frames */

		DrawObjects( person_throw, objects, background, page );
		IncrCurFrame( person_throw );
		if( person_throw->curframe == 0 )
			person_throwing = 0;
	}
	else{
		DrawObjects( person, objects, background, page );
		BossTalk();  /* if at the boss screen then ... */
		if( person_talking == 1 ){
			Talk();
			person_talking = 0;
		}		
		else if( person_giving == 1 ){
			Give(diamond_inv);
			person_giving = 0;
		}
        }
	
}

void AdjustAllCharactersFace( void ){
	AdjustCharacterFace( person );  /* adjust the direction facing */
	AdjustCharacterFace( person_hit );
	AdjustCharacterFace( person_shoot );
	AdjustCharacterFace( person_throw );
	AdjustCharacterFace( bullet );
}

void HandleKeyboardInput( void ){
   person_throw->ulx = person_shoot->ulx = person_hit->ulx = person->ulx += (keyboard[ INDEX_RIGHT ] - keyboard[ INDEX_LEFT ])*person->speed;
   person_throw->uly = person_shoot->uly = person_hit->uly = person->uly += (keyboard[ INDEX_DOWN ] - keyboard[ INDEX_UP ])*person->speed;

   if( keyboard[INDEX_UP] || keyboard[INDEX_DOWN] || keyboard[INDEX_LEFT] || keyboard[INDEX_RIGHT] ) {
	IncrCurFrame( person );
   }
   else {
	if(person->curframe != 0) {
	   IncrCurFrame( person );
	}
   }
   if( keyboard[ INDEX_ALT ] == 1 ){  /* attack button */
	if( cur_inv == gun_inv && person_shooting == 0 && num_bullets < MAXBULLETS ){
		person_shooting = 1;
		++num_bullets;
		PlaySound( shoot_sound );
	}
        else if( cur_inv == rock_inv && person_throwing == 0 ){
		person_throwing = 1;
		PlaySound( throw_sound );
	}
        else if( cur_inv == diamond_inv ){
		person_giving = 1;
	} 

   }
   if( keyboard[ INDEX_I ] ){
      ShowInventory();
   }
   if( keyboard[ INDEX_T ] ){
      person_talking = 1; 
   }	
}
