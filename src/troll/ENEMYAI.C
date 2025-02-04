#include "enemyai.h"

extern sprite_type *person;

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
	object->info->ulx_vb += object->info->dir_mov_x;
	object->info->uly_vb += object->info->dir_mov_y;

	if( ((object->info->ulx_vb_origin+object->info->range_x) < object->info->ulx_vb) ||
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

	if( person->ulx > object->sprite->ulx && object->info->dir_mov_x < 0 )
		object->info->dir_mov_x *= -1;
	if( person->ulx < object->sprite->ulx && object->info->dir_mov_x > 0 )
		object->info->dir_mov_x *= -1;
	if( person->uly > object->sprite->uly && object->info->dir_mov_y < 0 )
		object->info->dir_mov_y *= -1;
	if( person->uly < object->sprite->uly && object->info->dir_mov_y > 0 )
		object->info->dir_mov_y *= -1;	

        if( object->info->dir_mov_y != 0 )
                return( 1 );  /* y was tampered with */
        else
                return( 0 );
}
