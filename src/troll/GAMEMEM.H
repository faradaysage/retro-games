#ifndef GAMEMEM_H
#define GAMEMEM_H

#include <malloc.h>

void InitializeMemory( void );
char *GameMalloc( long size );
void FreeMemory( void );

#endif