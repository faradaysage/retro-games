#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <dos.h>
#include <fcntl.h>
#include "wad.h"
#include "error.h"

#define ENTRY_SIZE 10

/* SetValue doesn't work for some reason, so when setting I used SetBit  */
/* 5 = 1, 6 = 2, ... (for editing map) */
#define SetValue(x,y)    y=(((~(1<<4))&(y))|((x)<<4))
#define GetValue(y)      ((y)>>4)
#define SetBit(x,y,z)    if((z)==0) y=((~(1<<(x)))&(y)); else y=((1<<(x))|(y))
#define GetBit(x,y)      (((1<<(x))&(y))>>(x))

enum bit_tag { passable=0, enemy, object, attainable };

/* each entry contains 4 bits with a value of TRUE or FALSE
	least significant:  passable
	.                   enemy
	.                   object
	.                   attainable
	the last 4-bits are the id;
*/
typedef struct map_tag {
        unsigned char **table;
        short num_i,num_j;   /* number i and j */
} map_type;

void MakeMap(map_type **map, vbackground_type *background);
void DestroyMap(map_type **map );
void SaveMap( char *filename, map_type *map );
void OpenMap( char *filename, map_type **map );

void OpenMap( char *filename, map_type **map ) {
        short i, j;
        short num_i, num_j;
        file_type *fp;

        if( (fp = OpenFile( filename )) == NULL )
		Error( "Couldn't open file.\n" );
        wad_fread( &num_i, 1, sizeof(short), fp );
        wad_fread( &num_j, 1, sizeof(short), fp );
	if( ((*map)=(map_type *)malloc( sizeof( map_type ) )) == NULL )
		Error( "Not enough memory.\n" );
        if( ((*map)->table=(unsigned char **)malloc( sizeof(char *)*num_i )) == NULL )
		Error( "Not enough memory.\n" );
	for(i=0; i<num_i; ++i )
                if( ((*map)->table[i]=(unsigned char *)malloc( sizeof(char)*num_j )) == NULL )
			Error( "Not enough memory.\n" );
        for(i=0; i<num_i; ++i )
           for(j=0; j<num_j; ++j )
              wad_fread( &((*map)->table[i][j]), 1, sizeof(char), fp );
        (*map)->num_i = num_i;
        (*map)->num_j = num_j;
        CloseFile( fp );
}

void SaveMap( char *filename, map_type *map ) {
        short i, j;
        FILE *fp;

        if( (fp = fopen( filename, "wb" )) == NULL )
		Error( "could not create file.\n" );
        fwrite( &(map->num_i), 1, sizeof(short), fp );
        fwrite( &(map->num_j), 1, sizeof(short), fp );
	for(i=0; i<map->num_i; ++i )
           for(j=0; j<map->num_j; ++j)
              fwrite( &(map->table[i][j]), 1, sizeof(char), fp );
        fclose( fp );
}

void MakeMap(map_type **map, vbackground_type *background) {
        short i;
        short num_i, num_j;

        num_i = (background->width-ENTRY_SIZE)/ENTRY_SIZE;
        num_j = (background->height-ENTRY_SIZE)/ENTRY_SIZE;

	if( ((*map) = (map_type *)malloc( sizeof( map_type ) )) == NULL )
		Error( "Not enough memory.\n" );
        if( ((*map)->table = (unsigned char **)malloc( sizeof(char *)*num_i )) == NULL )
		Error( "Not enough memory.\n" );
	for(i=0; i<num_i; ++i )
                if( ((*map)->table[i] = (unsigned char *)malloc( sizeof(char )*num_j )) == NULL )
			Error( "Not enough memory.\n" );

	(*map)->num_i = num_i;
	(*map)->num_j = num_j;
}

void DestroyMap(map_type **map ) {
        short i;

	for(i=0; i<((*map)->num_i); ++i )
		free( (*map)->table[i] );
	free( (*map)->table );
	free( (*map) );
}

#endif
