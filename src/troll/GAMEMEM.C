#include "gamemem.h"
#include "error.h"

/* allocate memory for bitmaps */

long mem_index=0;  /* index in memory */
long mem_total=5000000;
char *motherload;

void InitializeMemory( void ){
	if( (motherload=(char *)malloc( mem_total )) == NULL )
		Error( "Couldn't allocate enough memory to run game.\n" );
}

char *GameMalloc( long size ){
	static char *temp_ptr;
	long temp_index=mem_index;

	mem_index += size;
	temp_ptr = &(motherload[temp_index]);

	return( temp_ptr );
}

void FreeMemory( void ){
	free( motherload );
}
