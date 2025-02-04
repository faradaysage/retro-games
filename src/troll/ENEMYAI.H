#ifndef ENEMYAI_H
#define ENEMYAI_H

/* All AI functions must return a value: 1 if the function changed the
	object's y position, 0 otherwise */

char Bullet0AI(object_type *object );
char Bullet1AI(object_type *object );
char Enemy0AI(object_type *object);
char Enemy2AI(object_type *object); /* miner boss */

#endif