#ifndef MAIN2_H
#define MAIN2_H

#define INTRO_SCREEN "intro.pcx"

#include "graphics.h"
#include "objects.h"
#include "text.h"
#include "main.h"
#include "inventry.h"
#include "sound.h"

object_type *object_that_collided;  /* collision with player */

char fadepalettein=1;

object_type *objects;        /* object list */

page_type page;              /* page to draw on */

vbackground_type *intro_screen;

/*** talk screens ***/

image_type *sawman_talkscreen,
	*minerboss_talkscreen,
	*oldminer_talkscreen;


/*****/

image_type *whole_heart, *half_heart, *empty_heart;

image_type *whole_heart_cave,
	*half_heart_cave,
	*empty_heart_cave;

image_type *whole_heart_forest,
	*half_heart_forest,
	*empty_heart_forest;


double energy=60.0;       /* intialize energy */
int max_energy=60;

/*****/


/* when adding screen, update LoadScreen(), InitializeScreen(), LoadCurPalette() */

enum screens { cavern=1, forest, cavern2, cavern3, cavern4, cavern5, cavern6, cavebattle };

short cur_screen = cavern;

/*******/

char person_fighting_miner_boss=0;
char miner_boss_dead = 0;
char got_diamond=0;
char left_miner_boss=0;


/*******/

char person_talking = 0,
     person_giving = 0;;
char person_shooting = 0,
     person_throwing = 0;

/******/

sprite_type *bullet;
sprite_type *rock;

sprite_type *person;
sprite_type *person_hit;
sprite_type *person_throw;
sprite_type *person_shoot;

/******/
/******/
sprite_type *person_cave,
	*person_hit_cave,
	*person_shoot_cave,
	*bullet_cave,
	*person_throw_cave,
	*rock_cave;

sprite_type *person_forest,
	*person_hit_forest,
	*person_shoot_forest,
	*bullet_forest,
	*person_throw_forest,
	*rock_forest;

/******/

background_type *background;

background_type *background_cave,
	*background_cave2,
	*background_cave3,
 	*background_cave4,
	*background_cave5,
	*background_cave6,
	*background_cavebattle,
	*background_forest;

/**************************/

void movetoxy(int x, int y);

void OpenEnergyPics( short level );
void DrawEnergy( void );
void InitializeEnergy(void);
void SubtractEnergy( short enemy_id );
void CloseEnergyPics( void );


void LoadScreen( int value );
void InitializeScreen( short screen );
void CleanupScreen( void );

void LoadCurPalette( void );

void ShootBullet( void );
void ThrowRock( void );

void InitializeIntro(void);
void InitializeTalkScreens(void);
void InitializeSprites(void);
void InitializeBackgrounds(void);
void InitializeEnergyPics(void);

void ShowIntro(void);

void Talk( void );
void BossTalk( void );

void KillObject( object_type **list, object_type *object );

void Give( int inv );

void SetPersonX( short x );
void SetPersonY( short y );

/****************************/

void InitializeEnergy(void){
	energy=60.0;
	max_energy=60;
}

void KillObject( object_type **list, object_type *object ){
	if( cur_screen == cavebattle ){
		miner_boss_dead = 1;
	}
	RemoveObject( list, object->sprite );
}

void InitializeIntro(void){
	open_vbackground( INTRO_SCREEN, &intro_screen );
}

void ShowIntro(void){
        int i;
        image_type *intro;
        float ratio;
        int x, y;

        memset( palette, 0, 768 );
        setVGApalette( palette );

        intro = VBackgroundToImage( intro_screen );

        clear_screen( page, 0 );

        x = 160-(0.01*160.0);
        y = 100-(0.01*100.0);

        Zoom( intro, 0.01, x, y, page );
        DrawScreen( page );

        load_palette( INTRO_SCREEN );
        fade_to_palette( palette, 1 );
                 
        for(ratio=0.01; ratio<=1.0; ratio+=0.01){
                x = 160-(ratio*160.0);
                y = 100-(ratio*100.0);
                Zoom( intro, ratio, x, y, page );
                delay( (long)(200-(ratio*200.0)) );
                DrawScreen( page );
        }
//        put_vbackground( intro_screen, page );

        Zoom( intro, 1, 0, 0, page );
        DrawScreen( page );

	WaitForKeyPressed;

	fade_to_black( palette, 20 );
}

void InitializeTalkScreens(void){
	open_image( "sawmantk.pcx", &sawman_talkscreen );
	open_image( "olminetk.pcx", &oldminer_talkscreen );
	open_image( "minertk.pcx",  &minerboss_talkscreen );
}

void BossTalk( void ){	
	if( fadepalettein == 0 ){
	if( cur_screen == cavebattle ){ /* miner */
		static char miner_talked=0;
		static char show_diamond=0;

		if( object_that_collided != NULL && object_that_collided->info->status == object_obj && object_that_collided->info->index == 3){ /* get diamond */
			got_diamond = 1;        	
			SetInventory( diamond_inv, 1); 
			RemoveObject( &objects, object_that_collided->sprite );
                }
			
		if( miner_boss_dead && !show_diamond ){
			object_info_type info;
			show_diamond = 1;

			info.status     = object_obj;
			info.index      = 3;  /* big diamond */
		
			info.ulx_vb = 190;
			info.uly_vb = 170;
		
		        info.frames_check = 0;   /* off */

			info.hold_frame = 1;
			info.how_long = 200;
			info.hold_frame_counter = 190;
	
			InsertObjectYSort( &objects, &info, sprite_table[ OBJECT_INDEX ][ 3 ] );
		}
		if( !miner_talked ){
			put_image( minerboss_talkscreen, 60, 27, 0, page );
			Print( page, 70, 37, 1, "You cannot have my beautiful, precious diamonds... you will never leave here alive!" );
			DrawScreen( page );
			miner_talked = 1;
 			WaitForKeyPressed;
		}
		
	}
	}
}

void Give( int inv ){
	object_type *character;  /* collision with player */

	if( inv == diamond_inv ){
		WaitForKeyRelease;

		if( (character = CheckCharacterCollision( person, objects )) != NULL ){
			if( character->info->index == 0 ){ /* woodsman */
				got_diamond = 0;
				SetInventory( diamond_inv, 0);
				SetInventory( gun_inv, 1);
				put_image( sawman_talkscreen, 60, 27, 0, page );
				Print( page, 70, 37, 1, "Wow... a diamond. Now I can make a diamond saw and get my work done a lot quicker. To show my gratitute to you take this gun. It isn't much but it's all I got. I won't be needing it anymore. Thanks again." );				
				DrawScreen( page );
				WaitForKeyPressed;			
			}
			if( character->info->index == 1 ){ /* old miner */
				put_image( oldminer_talkscreen, 60, 27, 0, page );
				Print( page, 70, 37, 1, "I have no use for a diamond. I mine them all day. I'll be mining them for the rest of my life... believe me. I've seen enough diamonds." );
				DrawScreen( page );
				WaitForKeyPressed;			
			}
		}
	}
}

void Talk( void ){
	object_type *character;  /* collision with player */

	WaitForKeyRelease;

	if( (character = CheckCharacterCollision( person, objects )) != NULL ){
		if( character->info->index == 0 ){ /* woodsman */
			put_image( sawman_talkscreen, 60, 27, 0, page );
			if( GetInventory( gun_inv ) ){
				Print( page, 70, 37, 255, "I can't thank you enough. I'll be forever in your debt. If I can do anything for you just tell me.  If you come back later I'll have the trees blocking the entrance to the village cut down." );
			}
			else{
				Print( page, 70, 37, 255, "These woods can get dangerous when the sun goes down. I make sure to carry a gun with me if I'm working late.  If I could get a diamond saw then I'd finish in no time. The problem is that they're just so scarce..." );
			}
			DrawScreen( page );
			WaitForKeyPressed;			
		}
		if( character->info->index == 1 ){ /* old miner */
			put_image( oldminer_talkscreen, 60, 27, 0, page );
			Print( page, 70, 37, 1, "Diamonds are a useful resource, they can be used to make sharp cutting tools.  But you won't find many diamonds around here.  When the mine's owner went mad, he locked himself in these caves to guard his diamonds." );
			DrawScreen( page );
			WaitForKeyPressed;					
		}
	}
}

void ThrowRock( void ){
	object_info_type info;

	info.status     = bullet_obj;
	info.index      = 1;

	info.ulx_vb = background->actual->ulx+(bullet->cel[0]->width>>1)+person->ulx;
	info.uly_vb = background->actual->uly+bullet->cel[0]->height+person->uly;

        info.frames_check = 1;   /* on */
        info.frames_last = rock->frames-1;    /* only show 11 frames (0..10), then get rid of it */
        info.frames_on = 0;      /* initialize counter */

	info.hold_frame = 0;     /* off */

        if( person->facing == north ){
                rock->facing = north;
		info.dir_mov_x = 0;
		info.dir_mov_y = -4;
	}
	if( person->facing == south ){
                rock->facing = south;
		info.dir_mov_x = 0;
                info.dir_mov_y = 4;
	}
	if( person->facing == east ){

		rock->facing = east;
                info.dir_mov_x = 4;
		info.dir_mov_y = 0;
        }
	if( person->facing == west ){
		rock->facing = west;
		info.dir_mov_x = -4;
		info.dir_mov_y = 0;
	}

	InsertObjectYSort( &objects, &info, rock );
}

void ShootBullet( void ){
	object_info_type info;

	info.status     = bullet_obj;
	info.index      = 0;

	info.ulx_vb = background->actual->ulx+(bullet->cel[0]->width>>1)+person->ulx;
	info.uly_vb = background->actual->uly+bullet->cel[0]->height+person->uly;

        info.frames_check = 0;   /* off */
	info.hold_frame = 0;     /* off */ 

	if( person->facing == north ){
		bullet->facing = north;
		info.dir_mov_x = 0;
                info.dir_mov_y = -5;
	}
	if( person->facing == south ){
		bullet->facing = south;
		info.dir_mov_x = 0;
		info.dir_mov_y = 5;
	}
	if( person->facing == east ){
		bullet->facing = east;
		info.dir_mov_x = 5;
		info.dir_mov_y = 0;
	}
	if( person->facing == west ){
		bullet->facing = west;
		info.dir_mov_x = -5;
		info.dir_mov_y = 0;
	}
	InsertObjectYSort( &objects, &info, bullet );
}


void LoadScreen( int value ){
   short prev_screen;

   prev_screen = cur_screen;

   CleanupScreen();
   fade_to_black( palette, 20 );
   InitializeScreen( value );

   CloseEnergyPics();
   OpenEnergyPics( value );

   if( prev_screen == cavebattle ){
	SetPersonX(0);
	SetPersonY(0);
	background->actual->uly = background->actual->ulx = 0;
   }
   if( prev_screen == cavern ){
      if( cur_screen == cavern ){
         SetPersonX(0);
         SetPersonY(0);
     	 background->actual->uly = background->actual->ulx = 0;
      }
      else if( cur_screen == forest ){
         SetPersonX(53);
         SetPersonY(133);
     	 background->actual->uly = background->actual->ulx = 0;
      }
      else if( cur_screen == cavern2 ){
         SetPersonX(0);
	 SetPersonY(0);
	 background->actual->uly = background->actual->ulx = 0;
      }
      else if( cur_screen == cavern3 ){
         SetPersonX(270);
         SetPersonY(80);			
         background->actual->ulx = background->actual->width;
	 background->actual->uly = 0;
      }
   }
   else if( prev_screen == forest ){
      if( cur_screen == cavern ){
         background->actual->ulx = 279;
	 background->actual->uly = 0;
         SetPersonX(190);
         SetPersonY(0);
      }
   }
   else if( prev_screen == cavern2 ){
      if( cur_screen == cavern ){
         background->actual->ulx = 279;
	 background->actual->uly = 0;
         SetPersonX(270);
         SetPersonY(0);
      }
      else if( cur_screen == cavern4 ){
         SetPersonX(0);
         SetPersonY(30);
	 background->actual->uly = background->actual->ulx = 0;
      }	
      else if( cur_screen == cavern5 ){
         SetPersonX(25);
         SetPersonY(-30);
	 background->actual->uly = background->actual->ulx = 0;
      }		
   }
   else if( prev_screen == cavern3 ){
      if( cur_screen == cavern ){
         SetPersonX(0);
         SetPersonY(120);
	 background->actual->uly = background->actual->ulx = 0;
      }
   }
   else if( prev_screen == cavern4 ){
      if( cur_screen == cavern2 ){
         SetPersonX(270);
         SetPersonY(50);
         background->actual->ulx = background->actual->width;
	 background->actual->uly = 0;
      }
      else if( cur_screen == cavern5 ){
         SetPersonX(230);
         SetPersonY(-10);
         background->actual->ulx = background->actual->width;
	 background->actual->uly = 0;
      }
      else if( cur_screen == cavern6 ){
         SetPersonX(0);
         SetPersonY(40);
	 background->actual->uly = background->actual->ulx = 0;
      }	
   }
   else if( prev_screen == cavern5 ){
      if( cur_screen == cavern2 ){
         SetPersonX(148);
         SetPersonY(125);
         background->actual->ulx = background->actual->width;
         background->actual->uly = background->actual->height;	
      }
      else if( cur_screen == cavern4 ){
         SetPersonX(180);
         SetPersonY(125);
         background->actual->ulx = background->actual->width;
	 background->actual->uly = background->actual->height;
      }
   }
   else if( prev_screen == cavern6 ){
      if( cur_screen == cavern4 ){
         SetPersonX(270);
         SetPersonY(50);
         background->actual->ulx = background->actual->width;
	 background->actual->uly = 0;
      }
      else if( cur_screen == cavebattle ){
         SetPersonX(0);
         SetPersonY(0);
	 background->actual->uly = background->actual->ulx = 0;
      }
   }
   person->speed = 2;
}

void LoadCurPalette( void ){
   if( cur_screen == cavern || cur_screen == cavern2 || cur_screen == cavern3 || cur_screen == cavern4 || cur_screen == cavern5 || cur_screen == cavern6 || cur_screen == cavebattle )
      load_palette( cave_background_files[0] );
   else if( cur_screen == forest )
      load_palette( forest_background_files[0] );
}

void InitializeSprites(void){
	OpenSprite( &person_cave, person_files_cave );
        OpenSprite( &person_hit_cave, person_hit_files_cave );
        OpenSprite( &person_shoot_cave, person_shoot_files_cave );
        OpenSprite( &bullet_cave, bullet_files_cave );
        OpenSprite( &person_throw_cave, person_throw_files_cave );
        OpenSprite( &rock_cave, rock_files );

        OpenSprite( &person_forest, person_files_forest );
	OpenSprite( &person_hit_forest, person_hit_files_forest );
	OpenSprite( &person_shoot_forest, person_shoot_files_forest );
	OpenSprite( &bullet_forest, bullet_files_forest );
	OpenSprite( &person_throw_forest, person_throw_files_forest );
        OpenSprite( &rock_forest, rock_files );
}	

void InitializeBackgrounds(void){
	OpenBackground( &background_cave, cave_background_files );
	OpenBackground( &background_cave2, cave2_background_files );
	OpenBackground( &background_cave3, cave3_background_files );
	OpenBackground( &background_forest, forest_background_files );
	OpenBackground( &background_cave4, cave4_background_files );
	OpenBackground( &background_cave5, cave5_background_files );
	OpenBackground( &background_cave6, cave6_background_files );
	OpenBackground( &background_cavebattle, cavebattle_background_files );
}

void InitializeScreen( short screen ){
    if( screen == cavebattle ){
	person_fighting_miner_boss = 1;

	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cavebattle;

	CreateObjectListWithBackground( &objects, background );
	StopMusic();
	LoadMusic( "song.dsm", FORM_DSM );
	PlayMusic();
     }
     if( screen == cavern6 ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave6;

	CreateObjectListWithBackground( &objects, background );
     }
     if( screen == cavern5 ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave5;

	CreateObjectListWithBackground( &objects, background );
     }
     if( screen == cavern4 ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave4;

	CreateObjectListWithBackground( &objects, background );
     }
     if( screen == cavern3 ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave3;

	CreateObjectListWithBackground( &objects, background );
     }
     if( screen == cavern2 ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave2;

	CreateObjectListWithBackground( &objects, background );
     }
     if( screen == cavern ){
	person = person_cave;
        person_hit = person_hit_cave;
        person_shoot = person_shoot_cave;
        bullet = bullet_cave;
        person_throw = person_throw_cave;
        rock = rock_cave;
        
        background = background_cave;

	CreateObjectListWithBackground( &objects, background );
	if( cur_screen == forest || cur_screen == cavern || cur_screen == cavebattle){
		StopMusic();
		LoadMusic( "return.mod", FORM_MOD );
		PlayMusic();
	}
    }
    if( screen == forest ){
	person = person_forest;
        person_hit = person_hit_forest;
        person_shoot = person_shoot_forest;
        bullet = bullet_forest;
        person_throw = person_throw_forest;
        rock = rock_forest;
        
        background = background_forest;

	CreateObjectListWithBackground( &objects, background );
	if( cur_screen == cavern ){
		StopMusic();
		LoadMusic( "heart.mod", FORM_MOD );
		PlayMusic();	
	}
    }
    fadepalettein=1;
    cur_screen = screen;
}   

void CleanupScreen( void ){

	DestroyObjectList( &objects );
}


void SubtractEnergy( short enemy_id ){
   energy -= 0.1;  /* for now */
}

void InitializeEnergyPics(void){
      open_image( "whc.pcx", &whole_heart_cave );
      open_image( "hhc.pcx", &half_heart_cave );
      open_image( "ehc.pcx", &empty_heart_cave );

      open_image( "whf.pcx", &whole_heart_forest );
      open_image( "hhf.pcx", &half_heart_forest );
      open_image( "ehf.pcx", &empty_heart_forest );

}

void OpenEnergyPics( short level ){
   if( level == cavern || level == cavern2 ){
      whole_heart = whole_heart_cave;
      half_heart = half_heart_cave;
      empty_heart = empty_heart_cave;
   }
   if( level == forest ){
      whole_heart = whole_heart_forest;
      half_heart = half_heart_forest;
      empty_heart = empty_heart_forest;
   }
}

void CloseEnergyPics( void ){
   close_image( &whole_heart );
   close_image( &half_heart );
   close_image( &empty_heart );
}

void DrawEnergy( void ){
   /* each heart is worth 10 points, half = 5 */
   short temp_energy=energy;
   short x, y=3;

   for(x=4; x<max_energy+4; x += 10, temp_energy -= 10 ){
      if( temp_energy < 0 )
         put_image( empty_heart, x, y, 0, page );
      else if( temp_energy <= 5 )
         put_image( half_heart, x, y, 0, page );
      else
         put_image( whole_heart, x, y, 0, page );
   }
}

void SetPersonX( short x ){
   person_throw->ulx = person_shoot->ulx = person_hit->ulx = person->ulx = x;
}

void SetPersonY( short y ){
   person_throw->uly = person_shoot->uly = person_hit->uly = person->uly = y;
}

void movetoxy(int x, int y)
{
	union REGS regs;

	regs.h.ah = 2;  /* set cursor position */
	regs.h.dh = y;
	regs.h.dl = x;
	regs.h.bh = 0;  /* video page 0 */
        int386(0x10, &regs, &regs);
}


#endif
