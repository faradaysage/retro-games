#ifndef OBJECTS_H
#define OBJECTS_H

#include "sprite.h"
#include "map.h"
#include "sound.h"

/* how big around is each object */
#define OBJECT_RADIUS 11

/* when you add an intelligence be sure to update DrawObjects()
	where the AI is called */

extern char keypressed;
extern sprite_type *person;  /* Enemy2AI() uses it */

typedef struct object_info_tag {
	char status, index;             /* object/enemy, which one */
	int ulx_vb, uly_vb;
	int ulx_vb_origin, uly_vb_origin;
        signed char dir_mov_x;           /* current x direction the object is moving */
        signed char dir_mov_y;           /* current y direction the object is moving */
	char range_x;
	char range_y;
        char frames_check;  /* frames_*, useful for objects */
        char frames_last;   /* that disappear after time */
        char frames_on;
	char use_energy;   /* object uses energy?  ex: fire doesn't */
        short energy;       /* only used if object is enemy */
	char hold_frame;
	char how_long;
	char hold_frame_counter;
} object_info_type;

typedef struct object_tag {
	sprite_type *sprite;
	object_info_type *info;
	struct object_tag *next;
} object_type;

enum object_enum { enemy_obj, object_obj, bullet_obj, character_obj };

object_type *HeadOfList( object_type *object );
void MakeObjectList( object_type **object, object_info_type *info, sprite_type *sprite );
void DestroyObjectList( object_type **object );
void AddObject( object_type *list, object_info_type *info, sprite_type *sprite );
void RemoveObject( object_type **list, sprite_type *sprite );
int  NumObjectsInList( object_type *list );
void CreateObjectListWithBackground( object_type **list, background_type *background );
void DrawObjects( sprite_type *player, object_type *list, background_type *background, page_type page );
void DrawObjectsHit( sprite_type *player, object_type *list, background_type *background, page_type page );
void UpdateObjects( object_type **head, background_type *background );

void ReInsertObjectYSort( object_type **list, object_type *object );
void InsertObjectYSort( object_type **list, object_info_type *info, sprite_type *sprite );


/*********** begin ai functions ***********/
/* All AI functions must return a value: 1 if the function changed the
	object's y position, 0 otherwise */

char Bullet0AI(object_type *object );
char Bullet1AI(object_type *object );
char Enemy0AI(object_type *object);
char Enemy2AI(object_type *object); /* miner boss */

char Bullet0AI(object_type *object ){  //bullet
	object->info->ulx_vb += object->info->dir_mov_x;
	object->info->uly_vb += object->info->dir_mov_y;

	if( object->info->dir_mov_y != 0 )
		return( 1 );  /* y was tampered with */
	else
		return( 0 );
}

char Bullet1AI( object_type *object ){   //rock
           object->info->ulx_vb += object->info->dir_mov_x;
           object->info->uly_vb += object->info->dir_mov_y;

           if( object->info->dir_mov_y != 0 )
                   return( 1 );  /* y was tampered with */
           else
                   return( 0 );
}


char Enemy0AI(object_type *object){
	
	if( (
	    (
	    ((MidBottomX(object->sprite)+object->info->range_x) >= MidBottomX(person)) &&
	    (MidBottomX(person) >= MidBottomX(object->sprite))
	    ) ||
	    
	    (
	    ((MidBottomX(object->sprite)-object->info->range_x) <= MidBottomX(person)) &&
	    (MidBottomX(person) <= MidBottomX(object->sprite))
	    )
	    ) &&
	    
	    (
	    (
	    ((MidBottomY(object->sprite)+object->info->range_y) >= MidBottomY(person)) &&
	    (MidBottomY(person) >= MidBottomY(object->sprite))
	    ) ||
	    
	    (
	    ((MidBottomY(object->sprite)-object->info->range_y) <= (MidBottomY(person)) &&
	    (MidBottomY(person) <= MidBottomY(object->sprite))
	    )
	    ) )){
	if( MidBottomX(person) > MidBottomX(object->sprite) && object->info->dir_mov_x < 0 )
		object->info->dir_mov_x *= -1;
	if( MidBottomX(person) < MidBottomX(object->sprite) && object->info->dir_mov_x > 0 )
		object->info->dir_mov_x *= -1;
	if( MidBottomY(person) > MidBottomY(object->sprite) && object->info->dir_mov_y < 0 )
		object->info->dir_mov_y *= -1;
	if( MidBottomY(person) < MidBottomY(object->sprite) && object->info->dir_mov_y > 0 )
		object->info->dir_mov_y *= -1;	
	object->info->ulx_vb += object->info->dir_mov_x;
	object->info->uly_vb += object->info->dir_mov_y;
	}

/*	if( ((object->info->ulx_vb_origin+object->info->range_x) < object->info->ulx_vb) ||
		 ((object->info->ulx_vb_origin-object->info->range_x) > object->info->ulx_vb) ){
		object->info->dir_mov_x *= -1;
		if( object->sprite->facing == east ){
			if( object->sprite->dir_struct.west != -1 )
				ChangeFace( object->sprite, west );
		}
		else{
			if( object->sprite->dir_struct.east != -1 )
				ChangeFace( object->sprite, east );
		}
	}
	if( ((object->info->uly_vb_origin+object->info->range_y) < object->info->uly_vb) ||
		 ((object->info->uly_vb_origin-object->info->range_y) > object->info->uly_vb) ){
		object->info->dir_mov_y *= -1;
		if( object->sprite->facing == east ){
			if( object->sprite->dir_struct.west != -1 )
				ChangeFace( object->sprite, west );
		}
		else{
			if( object->sprite->dir_struct.east != -1 )
				ChangeFace( object->sprite, east );
		}
	}
*/
        if( object->info->dir_mov_y != 0 )
                return( 1 );  /* y was tampered with */
        else
                return( 0 );
}

char Enemy2AI(object_type *object){
	object->info->ulx_vb += object->info->dir_mov_x;
	object->info->uly_vb += object->info->dir_mov_y;
	
	if( object->info->dir_mov_x < 0 ){
		ChangeFace( object->sprite, west );
	}
	else{
		ChangeFace( object->sprite, east );
	}

	if( MidBottomX(person) > MidBottomX(object->sprite) && object->info->dir_mov_x < 0 )
		object->info->dir_mov_x *= -1;
	if( MidBottomX(person) < MidBottomX(object->sprite) && object->info->dir_mov_x > 0 )
		object->info->dir_mov_x *= -1;
	if( MidBottomY(person) > MidBottomY(object->sprite) && object->info->dir_mov_y < 0 )
		object->info->dir_mov_y *= -1;
	if( MidBottomY(person) < MidBottomY(object->sprite) && object->info->dir_mov_y > 0 )
		object->info->dir_mov_y *= -1;	

        if( object->info->dir_mov_y != 0 )
                return( 1 );  /* y was tampered with */
        else
                return( 0 );
}

/********* end ai functions ***********/


/* precondition: list is not NULL
	assuming list is already sorted with exception to object,
	sorts the list by moving object to it's place with respect
	to y-axis (object->info->uly_vb) */
void ReInsertObjectYSort( object_type **list, object_type *object ){
	object_type *previous=NULL;
	object_type *begin=(*list);
	char object_found = 0, object_replaced = 0;

        /* remove the object element from the list */
	while( (object_found == 0) && ((*list) != NULL) ){
		if( (*list) == object ){
			if( previous == NULL ){ /* first element in list */
				(*list)=(*list)->next;
				begin = *list;       /* new head */
				object->next = NULL;
				object_found = 1;
			}
			else{
				previous->next = (*list)->next;
				object->next = NULL;
				object_found = 1;
			}
		}
		previous = (*list);
		(*list) = (*list)->next;
	}
	previous = NULL;
	(*list) = begin;  /* move head to beginning */
	/* object is now free, replace it in the list */

        if( (*list) == NULL ){   /* if an empty list, then make it first */
                (*list) = object;
                begin = object;
        }
        else{
                while( (object_replaced == 0) && ((*list) != NULL) ){
                        if( (*list)->info->uly_vb > object->info->uly_vb ){  /* object belong in front of (*list) */
                                if( previous == NULL ){
                                        object->next = (*list);
                                        begin = object;
                                        object_replaced = 1;
                                }
                                else {
                                        previous->next = object;
                                        object->next = (*list);
                                        object_replaced = 1;
                                }
                        }
                        previous = (*list);
                        (*list) = (*list)->next;
                }
                if( ((*list) == NULL) && (object_replaced == 0) ){ /* insert at end */
                        previous->next = object;
                        object->next = NULL;
                        object_replaced = 1;
                }
        }

	(*list) = begin;  /* make *list point to first node */

        /* could return success... successful only
		if (object_found == object_replaced == 1) */
}

void InsertObjectYSort( object_type **list, object_info_type *info, sprite_type *sprite ){
     object_type *object;
     object_type *previous=NULL;
     object_type *begin=(*list);
     char object_inserted = 0;

     if( (*list) == NULL ){   /* if an empty list, then make it first */
        MakeObjectList( list, info, sprite );
     }
     else{
	MakeObjectList( &object, info, sprite );
           
	while( (object_inserted == 0) && ((*list) != NULL) ){
		if( (*list)->info->uly_vb > object->info->uly_vb ){  /* object belong in front of (*list) */
			if( previous == NULL ){
				object->next = (*list);
				begin = object;
				object_inserted = 1;
			}
			else {
				previous->next = object;
				object->next = (*list);
				object_inserted = 1;
			}
		}
		previous = (*list);
		(*list) = (*list)->next;
	}
	if( ((*list) == NULL) && (object_inserted == 0) ){ /* insert at end */
		previous->next = object;
		object->next = NULL;
		object_inserted = 1;
	}

	(*list) = begin;  /* make *list point to first node */
	/* could return success... successful only
		if (object_found == object_replaced == 1) */
   }
}

/* UpdateObjects()
	changes their position accordingly, removes them from the list if
	they are off the background, calls their AI routines */
void UpdateObjects( object_type **head, background_type *background ){
	object_type *list=(*head);
	object_type *update[100];  /* list of objects that need to be updated */
	object_type *temp;
	char i, num_to_update = 0; /* assuming that no more than 100 object will change there y pos in one iteration */

	while( list != NULL ){
		if( (list->info->ulx_vb > background->actual->width)  ||
			 (list->info->uly_vb > background->actual->height) ||
			 ((list->info->ulx_vb+list->sprite->cel[0]->width) < 0) ||
                         ((list->info->uly_vb+list->sprite->cel[0]->height) < 0) ||
                         ((list->info->frames_check == 1) && (list->info->frames_on == list->info->frames_last)) ){

			if( (list->info->frames_check == 1) && (list->info->frames_on == list->info->frames_last) )
				if( list->info->status == bullet_obj && list->info->index == 1 )
					PlaySound( miss_sound );  /* rock misses */

			temp = list;
			list = list->next;                    /* get rid of object if it */
			RemoveObject( head, temp->sprite );   /* is out of bounds */
		}
		else{
                        if( list->sprite->auto_incr ){
				if( list->info->hold_frame ){  /* used to delay the first frame (diamond uses this) */ 
					if( list->info->hold_frame_counter == list->info->how_long ){
						list->info->hold_frame_counter = 0;
						IncrCurFrame( list->sprite );
		                                if( list->info->frames_check )
                		                   ++list->info->frames_on;
					}
					else{
						if( list->sprite->curframe == 0 ){
							++list->info->hold_frame_counter;
						}
						else{
							IncrCurFrame( list->sprite );
		                                	if( list->info->frames_check )
                		                   		++list->info->frames_on;
						}
					}
				}
				else{
					IncrCurFrame( list->sprite );
                                	if( list->info->frames_check )
                                   		++list->info->frames_on;
				}
                        }
			if( list->info->status == enemy_obj ){
				if( list->info->index == 0 ){ /* blob */
					if( Enemy0AI( list ) ){  /* if function tampered with y pos */
						update[num_to_update] = list;
						++num_to_update;
					}
				}
				else if( list->info->index == 2 ){ /* miner boss */
					if( Enemy2AI( list ) ){  
						update[num_to_update] = list;
						++num_to_update;
					}
				}
			}
			else if( list->info->status == bullet_obj ){
				if( list->info->index == 0 ){   /* players bullet */
					if( Bullet0AI( list ) ){
							update[num_to_update] = list;
						++num_to_update;
					}
				}
				else if( list->info->index == 1 ){   /* players bullet */
                                        if( Bullet1AI( list ) ){
							update[num_to_update] = list;
						++num_to_update;
					}
				}
			}
			list = list->next;
		}
	}

	for(i=0; i<num_to_update; ++i){  /* update list */
		ReInsertObjectYSort( head, update[i] );
	}
}


void DrawObjects( sprite_type *player, object_type *list, background_type *background, page_type page ){
	int x, y, width, height;
	char player_was_drawn = 0;

	while( list != NULL ){
		width  = list->sprite->cel[0]->width;
		height = list->sprite->cel[0]->height;
		x = list->info->ulx_vb - background->actual->ulx-(width>>1);
		y = list->info->uly_vb - background->actual->uly-height;
		list->sprite->ulx = x;
		list->sprite->uly = y;
		if( ((x+width) > 0) && (x < 320) && ((y+height) > 0 ) && (y < 200) ){
			if( player_was_drawn == 0 )
				if( MidBottomY(list->sprite) > MidBottomY(player) ){
					PutSprite( player, page );  /* put player in front/back of */
					player_was_drawn = 1;       /* object to give 3d illusion */
				}
			PutSprite( list->sprite, page );
		}
		list = list->next;
	}
	if( player_was_drawn == 0 )
		PutSprite( player, page );
}

/* draws person mosaic */

void DrawObjectsHit( sprite_type *player, object_type *list, background_type *background, page_type page ){
	int x, y, width, height;
	char player_was_drawn = 0;

	while( list != NULL ){
		width  = list->sprite->cel[0]->width;
		height = list->sprite->cel[0]->height;
		x = list->info->ulx_vb - background->actual->ulx-(width>>1);
		y = list->info->uly_vb - background->actual->uly-height;
		list->sprite->ulx = x;
		list->sprite->uly = y;
		if( ((x+width) > 0) && (x < 320) && ((y+height) > 0 ) && (y < 200) ){
			if( player_was_drawn == 0 )
				if( MidBottomY(list->sprite) > MidBottomY(player) ){
                                        PutSpriteMosaic( player, page );  /* put player in front/back of */
					player_was_drawn = 1;       /* object to give 3d illusion */
				}
                        PutSprite( list->sprite, page );
		}
		list = list->next;
	}
	if( player_was_drawn == 0 )
                PutSpriteMosaic( player, page );
}


/* Precondition:  Sprite table was created */
void CreateObjectListWithBackground( object_type **list, background_type *background ){
	int i, j;
	unsigned char index_j;
	char first_one_done = 0;
	object_info_type info;

	for(j=0; j<background->map->num_j; ++j )
		for(i=0; i<background->map->num_i; ++i ){
			/* enemy and object means character */
			if( GetBit( enemy, background->map->table[i][j] ) && GetBit( object, background->map->table[i][j] ) ){
				index_j = GetValue(background->map->table[i][j]);
				info.ulx_vb_origin = info.ulx_vb = (i+1)*ENTRY_SIZE;
				info.uly_vb_origin = info.uly_vb = (j+1)*ENTRY_SIZE;
                                info.status = character_obj;
				info.index = index_j;
                                info.frames_check=0;
				info.hold_frame = 0;
				if( first_one_done ){
                                        AddObject( *list, &info, sprite_table[ CHARACTER_INDEX ][ index_j ] );
				}
				else{
					first_one_done = 1;
                                        MakeObjectList( list, &info, sprite_table[ CHARACTER_INDEX ][ index_j ] );
				}
			}
			else if( GetBit( enemy, background->map->table[i][j] ) ){
				index_j = GetValue(background->map->table[i][j]);
				info.ulx_vb_origin = info.ulx_vb = (i+1)*ENTRY_SIZE;
				info.uly_vb_origin = info.uly_vb = (j+1)*ENTRY_SIZE;
				info.status = enemy_obj;
				info.index = index_j;
                                info.frames_check=0;
				info.use_energy=0;
				info.hold_frame=0;
				if( index_j == 0 ){   /* enemy 0 (blob)*/
					info.dir_mov_x = 1;
					info.dir_mov_y = 1;
					info.range_x = 35;
					info.range_y = 20;
					info.use_energy=1;
					info.energy=4;
				}
				else if( index_j == 2 ){   /* enemy 2 (miner boss)*/
					info.dir_mov_x = 1;
					info.dir_mov_y = 1;
					info.use_energy=1;
					info.energy=20;
				}
				if( first_one_done ){
					AddObject( *list, &info, sprite_table[ ENEMY_INDEX ][ index_j ] );
				}
				else{
					first_one_done = 1;
					MakeObjectList( list, &info, sprite_table[ ENEMY_INDEX ][ index_j ] );
				}
			}
                        else if( GetBit( object, background->map->table[i][j] ) ){
				index_j = GetValue(background->map->table[i][j]);
				info.ulx_vb_origin = info.ulx_vb = (i+1)*ENTRY_SIZE;
				info.uly_vb_origin = info.uly_vb = (j+1)*ENTRY_SIZE;
                                info.status = object_obj;
				info.index = index_j;
                                info.frames_check=0;
				info.hold_frame=0;
				if( index_j == 2 ){   /* object 2 (diamond)*/
					info.hold_frame=1;
					info.how_long=200;
					info.hold_frame_counter=190;
				}
				if( index_j == 3 ){   /* object 3 (big diamond)*/
					info.hold_frame=1;
					info.how_long=200;
					info.hold_frame_counter=190;
				}
				if( first_one_done ){
                                        AddObject( *list, &info, sprite_table[ OBJECT_INDEX ][ index_j ] );
				}
				else{
					first_one_done = 1;
                                        MakeObjectList( list, &info, sprite_table[ OBJECT_INDEX ][ index_j ] );
				}
			}
		}
}


int NumObjectsInList( object_type *list ){
	int counter=0;

	while( list != NULL ){
		++counter;
		list = list->next;
	}

	return( counter );
}


void DestroyObjectList( object_type **object ) {
	object_type **temp=object;

	while( (*object) != NULL ){
		temp = object;
		(*object) = (*object)->next;
		free(*temp);
	}
}

void MakeObjectList( object_type **object, object_info_type *info, sprite_type *sprite ){
	if( ((*object)=(object_type *)malloc( sizeof(object_type) )) == NULL)
		Error( "Not enough memory.\n" );
	if( ((*object)->info=(object_info_type *)malloc( sizeof(object_info_type) )) == NULL)
		Error( "Not enough memory.\n" );
	if( ((*object)->sprite=(sprite_type *)malloc(sizeof(sprite_type))) == NULL )
		Error( "Not enough memory.\n" );

	memcpy( (*object)->sprite, sprite, sizeof(sprite_type) );
	(*object)->sprite->cel = sprite->cel;
	memcpy( (*object)->info, info, sizeof(object_info_type) );
	(*object)->next = NULL;
}


object_type *HeadOfList( object_type *object ){
	static object_type *head;

	head = object;

	while( head->next != NULL )
		head = head->next;       /* move to head node */

	return( head );
}

/* precondition: sprite was already created */
void AddObject( object_type *list, object_info_type *info, sprite_type *sprite ){
	object_type *temp, *head;

	if( (temp=(object_type *)malloc( sizeof(object_type) )) == NULL )
		Error( "Not enough memory.\n" );
	if( (temp->sprite=(sprite_type *)malloc( sizeof(sprite_type) )) == NULL )
		Error( "Not enough memory.\n" );

	memcpy( temp->sprite, sprite, sizeof(sprite_type) );
	temp->sprite->cel = sprite->cel;

	if( (temp->info=(object_info_type *)malloc( sizeof(object_info_type) )) == NULL)
		Error( "Not enough memory.\n" );
	memcpy( temp->info, info, sizeof(object_info_type) );

	temp->next = NULL;

	head = HeadOfList( list );
	head->next = temp;
}

/* postcondition: object that held sprite is removed */
void RemoveObject( object_type **list, sprite_type *sprite ){
	object_type *temp=(*list);
	object_type *begin=(*list);
	object_type *previous=NULL;

	while( temp != NULL ) {
		if( temp->sprite == sprite ){ /* if we found it */
			if( previous != NULL )
				previous->next = temp->next;  /* fix link */
			else
				begin = temp->next;
			free( temp->sprite );
			free( temp->info );
			free( temp );
		}
		previous = temp;
		temp = temp->next;
	}
	(*list) = begin;
}

#endif
