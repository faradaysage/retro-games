#ifndef COLISION_H
#define COLISION_H

#define MAXBULLETS 50

#include "sprite.h"
#include "map.h"
#include "objects.h"
#include "sound.h"

#define GetIPos(sprite, background) ((((sprite)->ulx+((sprite)->cel[(sprite->frames*sprite->facing)+sprite->curframe]->height/2))+(background)->actual->ulx)/ENTRY_SIZE)
#define GetJPos(sprite, background) (((sprite)->uly+(sprite)->cel[(sprite->frames*sprite->facing)+sprite->curframe]->width)+(background)->actual->uly)/ENTRY_SIZE;

extern char miner_boss_dead;

char num_bullets=0;

/* changed in CheckCollision(), used in HandleCollision() */
short last_x, last_y;  /* if sprite runs into unpassable position restore to last position */

typedef struct collision_tag {   /* for collisions in map */
	 char value;
	 char passable;
	 char enemy;
	 char object;
	 char attainable;
} collision_type;

typedef struct bullet_collision_tag{
	object_type *object[MAXBULLETS];
	object_type *bullet[MAXBULLETS];
	char num_collisions;
} bullet_collision_type;


void LoadScreen( int value );

/* CheckCollision() and HandleCollision() deal with collisions in map,
	not with sprites */
collision_type *CheckCollision( background_type *background, sprite_type *sprite );
void HandleCollision( collision_type *collision, background_type *background, sprite_type *sprite );

/* CheckSpriteCollision() checks for a collision between a sprite (passed)
	and an object list (passed) */
object_type *CheckSpriteCollision( sprite_type *sprite, object_type *object_list );
int SpritesTouching( sprite_type *sprite1, sprite_type *sprite2 );


bullet_collision_type *CheckBulletCollision( object_type *list );
void HandleBulletCollision( bullet_collision_type *bullet_collision, object_type **list );

object_type *CheckCharacterCollision( sprite_type *sprite, object_type *object_list );

object_type *CheckCharacterCollision( sprite_type *sprite, object_type *object_list ){
        short mb_sprite = MidBottomY(sprite);
        short mb_object;
        short place_in_sprite_x, place_in_sprite_y;
        short sprite_max_x = sprite->ulx+sprite->cel[0]->width,
		 object_max_x;

	while( object_list != NULL ){
		mb_object = MidBottomY(object_list->sprite);
		/* if sprite in y range of object */
		if( ((mb_sprite <  (mb_object+OBJECT_RADIUS)) && (mb_sprite > (mb_object-OBJECT_RADIUS))) && (object_list->sprite != sprite) ){
			/* if sprite in x range (bitmaps overlapping) of object */
			object_max_x = object_list->sprite->ulx+object_list->sprite->cel[0]->width;
			if( ((sprite_max_x >= object_list->sprite->ulx) && (sprite_max_x <= object_max_x)) ||
				 ((object_max_x >= sprite->ulx) && (object_max_x <= sprite_max_x)) ){
				if( object_list->info->status == character_obj )
                                        return( object_list );
			}
		}
		object_list = object_list->next;
	}
	return( NULL );  /* couldn't find a character collision */
}


void HandleBulletCollision( bullet_collision_type *bullet_collision, object_type **list ){
	int i;
 
	for(i=0; i<bullet_collision->num_collisions; ++i ){
		if( bullet_collision->object[i]->info->use_energy == 1 ){
			if( bullet_collision->bullet[i]->info->index == 1 ) /* rock */
				bullet_collision->object[i]->info->energy -= 1;
			else if( bullet_collision->bullet[i]->info->index == 0 ) /* bullet */ 
				bullet_collision->object[i]->info->energy -= 2;
			if( bullet_collision->object[i]->info->energy <= 0 )
				KillObject( list, bullet_collision->object[i] );
			PlaySound( hit_sound );
		}
		else
			PlaySound( miss_sound );
		RemoveObject( list, bullet_collision->bullet[i]->sprite );
	}
}

bullet_collision_type *CheckBulletCollision( object_type *list ){
	object_type *head=list;
        object_type *object_collided;
	static bullet_collision_type bullet_collision;

	bullet_collision.num_collisions = 0;
	while( list != NULL ){
		if( list->info->status == bullet_obj ){
                        object_collided = CheckSpriteCollision( list->sprite, head );
                        if( object_collided != NULL ){
                                bullet_collision.object[bullet_collision.num_collisions] = object_collided;
				bullet_collision.bullet[bullet_collision.num_collisions] = list;
				++bullet_collision.num_collisions;
			}
		}
		list = list->next;
	}
	return( &bullet_collision );
}

/* precondition: sprites bitmaps are overlapping */
/* returns 1 if both sprites current bitmaps overlap a non-zero color */
int SpritesTouching( sprite_type *sprite1, sprite_type *sprite2 ){
        short x_s1, x_s2;
        short int start_x_s1, start_x_s2;

        short y_s1, y_s2;
        short start_y_s1, start_y_s2;

        short max_x_s1 = sprite1->cel[0]->width,
		 max_x_s2 = sprite2->cel[0]->width,
		 max_y_s1 = sprite1->cel[0]->height,
		 max_y_s2 = sprite2->cel[0]->height;

	if( sprite1->ulx < sprite2->ulx ){
		x_s1 = start_x_s1 = (sprite2->ulx - sprite1->ulx);
		x_s2 = start_x_s2 = 0;
	}
	else{
		x_s1 = start_x_s1 = 0;
		x_s2 = start_x_s2 = (sprite1->ulx - sprite2->ulx);
	}
	if( sprite1->uly < sprite2->uly ){
		y_s1 = start_y_s1 = (sprite2->uly - sprite1->uly);
		y_s2 = start_y_s2 = 0;
	}
	else{
		y_s1 = start_y_s1 = 0;
		y_s2 = start_y_s2 = (sprite1->uly - sprite2->uly);
	}
	/* while not at end of one bitmap */
	while( (y_s1 < max_y_s1) && (y_s2 < max_y_s2) ) {
		if( (sprite1->cel[ CelIndexNum(sprite1) ]->bitmap[ x_s1+(y_s1*max_x_s1) ] != 0 ) &&
			 (sprite2->cel[ CelIndexNum(sprite2) ]->bitmap[ x_s2+(y_s2*max_x_s2) ] != 0 ) )
			return( 1 );   /* found collision */
		++x_s1;
		++x_s2;
		if( x_s1 >= max_x_s1 || x_s2 >= max_x_s2 ){ /* move to next (x,y) */
			++y_s1;
			++y_s2;
			x_s1 = start_x_s1;
			x_s2 = start_x_s2;
		}
	}
	return( 0 ); /* didn't find a collsion */
}

object_type *CheckSpriteCollision( sprite_type *sprite, object_type *object_list ){
        short mb_sprite = MidBottomY(sprite);
        short mb_object;
        short place_in_sprite_x, place_in_sprite_y;
        short sprite_max_x = sprite->ulx+sprite->cel[0]->width,
		 object_max_x;

	while( object_list != NULL ){
		mb_object = MidBottomY(object_list->sprite);
		/* if sprite in y range of object */
		if( ((mb_sprite <  (mb_object+OBJECT_RADIUS)) && (mb_sprite > (mb_object-OBJECT_RADIUS))) && (object_list->sprite != sprite) ){
			/* if sprite in x range (bitmaps overlapping) of object */
			object_max_x = object_list->sprite->ulx+object_list->sprite->cel[0]->width;
			if( ((sprite_max_x >= object_list->sprite->ulx) && (sprite_max_x <= object_max_x)) ||
				 ((object_max_x >= sprite->ulx) && (object_max_x <= sprite_max_x)) ){
				if( SpritesTouching(sprite, object_list->sprite) )
                                        return( object_list );
			}
		}
		object_list = object_list->next;
	}
	return( NULL );  /* couldn't find a collision */
}


void HandleCollision( collision_type *collision, background_type *background, sprite_type *sprite ) {
	if( collision->passable == 0 ) {
				/* move to last passable place */
		sprite->ulx = last_x - background->actual->ulx;
		sprite->uly = last_y - background->actual->uly;
	}
	if( collision->attainable == 1 ){
		if( collision->value == 8 && miner_boss_dead ){ /* 8=cavebattle*/
			sprite->ulx = last_x - background->actual->ulx;
			sprite->uly = last_y - background->actual->uly;
		}
                LoadScreen( collision->value );
	}
}


/* CheckCollision()
	check for collision between sprite & background
	return statistics of the collision */

collision_type *CheckCollision( background_type *background, sprite_type *sprite ) {
	static collision_type collision;
        short i, j;  /* place in background->map that sprite is in */

	i = GetIPos( sprite, background );
	j = GetJPos( sprite, background );

	collision.value = GetValue( background->map->table[i][j] );
	collision.passable = GetBit( passable, background->map->table[i][j] );
	collision.enemy = GetBit( enemy, background->map->table[i][j] );
	collision.object = GetBit( object, background->map->table[i][j] );
	collision.attainable = GetBit( attainable, background->map->table[i][j] );

	if( collision.passable ) {  /* remember last passable place */
		last_x = background->actual->ulx + sprite->ulx;
		last_y = background->actual->uly + sprite->uly;
	}

	return( &collision );
}


#endif
