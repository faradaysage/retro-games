#ifndef MAIN_H

#include "graphics.h"
#include "sprite.h"
#define MAIN_H

#define KeepBackgroundInBounds( b )        \
		if ((b)->actual->ulx < 0)                    \
			(b)->actual->ulx = 0;                     \
		if ((b)->actual->uly < 0)                    \
			(b)->actual->uly = 0;                     \
		if ((b)->actual->ulx+320 > (b)->actual->width)       \
			(b)->actual->ulx = (b)->actual->width-320;        \
		if ((b)->actual->uly+200 > (b)->actual->height)      \
			(b)->actual->uly = (b)->actual->height-200


#define AdjustCharacterFace(x)            \
	if( keyboard[INDEX_UP]==1 ){           \
		if( (x)->dir_struct.north != -1)    \
			(x)->facing=north;               \
	}                                      \
	else if( keyboard[INDEX_DOWN]==1 ){    \
		if( (x)->dir_struct.south != -1)    \
			(x)->facing=south;               \
	}                                      \
	else if( keyboard[INDEX_RIGHT]==1 ){   \
		if( (x)->dir_struct.east != -1)     \
			(x)->facing=east;                \
	}                                      \
	else if( keyboard[INDEX_LEFT]==1 )     \
		if( (x)->dir_struct.west != -1)     \
			(x)->facing=west

		/* picture files for sprites */
                char *person_files_cave[]={ "4", "4", "SEWNE", "person1s.pcx",
					        	 "person2s.pcx",
							 "person3s.pcx",
							 "person4s.pcx",
							 "person1e.pcx",
							 "person2e.pcx",
							 "person3e.pcx",
							 "person4e.pcx",
							 "person1w.pcx",
							 "person2w.pcx",
							 "person3w.pcx",
							 "person4w.pcx",
							 "person1n.pcx",
							 "person2n.pcx",
							 "person3n.pcx",
							 "person4n.pcx" };

         char *person_files_forest[]={ "4", "4", "SEWNE", "prson1sf.pcx",
                                                         "prson2sf.pcx",
                                                         "prson3sf.pcx",
                                                         "prson4sf.pcx",
                                                         "prson1ef.pcx",
                                                         "prson2ef.pcx",
                                                         "prson3ef.pcx",
                                                         "prson4ef.pcx",
                                                         "prson1wf.pcx",
                                                         "prson2wf.pcx",
                                                         "prson3wf.pcx",
                                                         "prson4wf.pcx",
                                                         "prson1nf.pcx",
                                                         "prson2nf.pcx",
                                                         "prson3nf.pcx",
                                                         "prson4nf.pcx" };

	char *person_hit_files_cave[]={ "1", "4", "NEWSE", "perhit1n.pcx",
						"perhit1e.pcx",
						"perhit1w.pcx",
						"perhit1s.pcx" };
        char *person_hit_files_forest[]={ "1", "4", "NEWSE", "prhit1nf.pcx",
						"prhit1ef.pcx",
						"prhit1wf.pcx",
						"prhit1sf.pcx" }; 
	char *person_shoot_files_cave[]={ "6", "4", "NEWSE", "persht1n.pcx",
							"persht2n.pcx",
							"persht3n.pcx",
							"persht4n.pcx",
							"persht5n.pcx",
							"persht6n.pcx",
							"persht1e.pcx",
							"persht2e.pcx",
							"persht3e.pcx",
							"persht4e.pcx",
							"persht5e.pcx",
							"persht6e.pcx",
							"persht1w.pcx",
							"persht2w.pcx",
							"persht3w.pcx",
							"persht4w.pcx",
							"persht5w.pcx",
							"persht6w.pcx",
							"persht1s.pcx",
							"persht2s.pcx",
							"persht3s.pcx",
							"persht4s.pcx",
							"persht5s.pcx",
							"persht6s.pcx" };
        char *person_shoot_files_forest[]={ "6", "4", "NEWSE", "prsht1nf.pcx",
							"prsht2nf.pcx",
							"prsht3nf.pcx",
							"prsht4nf.pcx",
							"prsht5nf.pcx",
							"prsht6nf.pcx",
							"prsht1ef.pcx",
							"prsht2ef.pcx",
							"prsht3ef.pcx",
							"prsht4ef.pcx",
							"prsht5ef.pcx",
							"prsht6ef.pcx",
							"prsht1wf.pcx",
							"prsht2wf.pcx",
							"prsht3wf.pcx",
							"prsht4wf.pcx",
							"prsht5wf.pcx",
							"prsht6wf.pcx",
							"prsht1sf.pcx",
							"prsht2sf.pcx",
							"prsht3sf.pcx",
							"prsht4sf.pcx",
							"prsht5sf.pcx",
							"prsht6sf.pcx" }; 
	char *bullet_files_cave[]={ "1", "4", "NEWSS", "bulletn.pcx",
						"bullete.pcx",
						"bulletw.pcx",
						"bullets.pcx" };
        char *bullet_files_forest[]={ "1", "4", "NEWSS", "bulletnf.pcx",
						"bulletef.pcx",
						"bulletwf.pcx",
						"bulletsf.pcx" };
	char *person_throw_files_cave[]={ "6", "4", "EWSNE", "perthw1e.pcx",
						"perthw2e.pcx",
						"perthw3e.pcx",
						"perthw4e.pcx",
						"perthw5e.pcx",
						"perthw6e.pcx",
						"perthw1w.pcx",
						"perthw2w.pcx",
						"perthw3w.pcx",
						"perthw4w.pcx",
						"perthw5w.pcx",
						"perthw6w.pcx",
						"perthw1s.pcx",
						"perthw2s.pcx",
						"perthw3s.pcx",
						"perthw4s.pcx",
						"perthw5s.pcx",
						"perthw6s.pcx",
						"perthw1n.pcx",
						"perthw2n.pcx",
						"perthw3n.pcx",
						"perthw4n.pcx",
						"perthw5n.pcx",
						"perthw6n.pcx" };
        char *person_throw_files_forest[]={ "6", "4", "EWSNE", "prthw1ef.pcx",
						"prthw2ef.pcx",
						"prthw3ef.pcx",
						"prthw4ef.pcx",
						"prthw5ef.pcx",
						"prthw6ef.pcx",
						"prthw1wf.pcx",
						"prthw2wf.pcx",
						"prthw3wf.pcx",
						"prthw4wf.pcx",
						"prthw5wf.pcx",
						"prthw6wf.pcx",
						"prthw1sf.pcx",
						"prthw2sf.pcx",
						"prthw3sf.pcx",
						"prthw4sf.pcx",
						"prthw5sf.pcx",
						"prthw6sf.pcx",
						"prthw1nf.pcx",
						"prthw2nf.pcx",
						"prthw3nf.pcx",
						"prthw4nf.pcx",
						"prthw5nf.pcx",
						"prthw6nf.pcx"  };
        char *rock_files[]={ "8", "4", "EWNSE", "rock1e.pcx",
					 "rock2e.pcx",
					 "rock3e.pcx",
                                         "rock4e.pcx",
                                         "rock5e.pcx",
                                         "rock6e.pcx",
                                         "rock7e.pcx",
                                         "rock8e.pcx",
                                         "rock1w.pcx",
					 "rock2w.pcx",
					 "rock3w.pcx",
                                         "rock4w.pcx",
                                         "rock5w.pcx",
                                         "rock6w.pcx",
                                         "rock7w.pcx",
                                         "rock8w.pcx",
                                         "rock1n.pcx",
                                         "rock2n.pcx",
                                         "rock3n.pcx",
                                         "rock4n.pcx",
                                         "rock5n.pcx",
                                         "rock6n.pcx",
                                         "rock7n.pcx",
                                         "rock8n.pcx",
                                         "rock1s.pcx",
                                         "rock2s.pcx",
                                         "rock3s.pcx",
                                         "rock4s.pcx",
                                         "rock5s.pcx",
                                         "rock6s.pcx",
                                         "rock7s.pcx",
                                         "rock8s.pcx" };
	char *cave_background_files[]={ "cliffs2.pcx", "cliffs2.map" };
        char *cave2_background_files[]={ "cliffs3.pcx", "cliffs3.map" };
	char *cave3_background_files[]={ "cliffs1.pcx", "cliffs1.map" };
	char *cave4_background_files[]={ "cliffs4.pcx", "cliffs4.map" };
	char *cave5_background_files[]={ "cliffs5.pcx", "cliffs5.map" };    
	char *cave6_background_files[]={ "cliffs6.pcx", "cliffs6.map" };
	char *cavebattle_background_files[]={ "cliffbat.pcx", "cliffbat.map" };        
        char *forest_background_files[]={ "forest.pcx", "forest.map" };

void ScrollBackgroundWithSprite(background_type *b, sprite_type *s,int rb, int rs,int ulx, int uly,int lrx,int lry);

void ScrollBackgroundWithSprite(background_type *b, sprite_type *s,int rb, int rs,int ulx, int uly,int lrx,int lry) {
		if( (s)->ulx < (ulx) ){
			(b)->actual->ulx -=rb;
			if( (b)->actual->ulx > 0 )
				(s)->ulx += rs;
		}
		if( (s)->uly < (uly) ){
			(b)->actual->uly -=rb;
			if( (b)->actual->uly > 0 )
				(s)->uly+= rs;
		}
		if( (s)->ulx > (lrx) ){
			(b)->actual->ulx += rb;
			if( (b)->actual->ulx < ((b)->actual->width-320) )
				(s)->ulx -= rs;
		}
		if( (s)->uly > (lry) ){
			(b)->actual->uly += rb;
			if( (b)->actual->uly < ((b)->actual->height-200) )
			  (s)->uly -= rs;
		}

}
#endif
