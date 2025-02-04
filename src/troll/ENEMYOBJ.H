#ifndef ENEMYOBJ_H
#define ENEMYOBJ_H

#define NUM_ENEMYS 3
#define ENEMY_INDEX 0  /* index in sprite table array (0 or 1) */

#define NUM_OBJECTS 4
#define OBJECT_INDEX 1

#define NUM_CHARACTERS 2
#define CHARACTER_INDEX 2
						  /* frames, num directions, directions, files in order of directions */
					/* num of fields */
char *enemy_filenames[ NUM_ENEMYS ][35]= { { "5", "1", "S", "blob.pcx", "blob2.pcx", "blob3.pcx", "blob2.pcx", "blob.pcx" },
                                           { "4", "1", "S", "fire.pcx", "fire2.pcx", "fire3.pcx", "fire4.pcx" },
                                           { "15", "2", "WEW", "miner1.pcx", "miner2.pcx", "miner3.pcx", "miner4.pcx", "miner5.pcx", "miner6.pcx", "miner7.pcx", "miner8.pcx", "miner9.pcx", "miner10.pcx", "miner5.pcx", "miner4.pcx", "miner3.pcx", "miner2.pcx", "miner1.pcx",
                                                              "miner1e.pcx", "miner2e.pcx", "miner3e.pcx", "miner4e.pcx", "miner5e.pcx", "miner6e.pcx", "miner7e.pcx", "miner8e.pcx", "miner9e.pcx", "miner10e.pcx", "miner5e.pcx", "miner4e.pcx", "miner3e.pcx", "miner2e.pcx", "miner1e.pcx"} };

char *object_filenames[ NUM_OBJECTS ][20]= { {"1", "1", "SS", "tree1.pcx"},
                                             {"1", "1", "SS", "trestump.pcx"},
					     {"9", "1", "SS", "diamon1s.pcx", "diamon2s.pcx", "diamon3s.pcx", "diamon4s.pcx", "diamon5s.pcx", "diamon2s.pcx", "diamon3s.pcx", "diamon4s.pcx", "diamon5s.pcx" },
                                             {"9", "1", "SS", "diamond1.pcx", "diamond2.pcx", "diamond3.pcx", "diamond4.pcx", "diamond5.pcx", "diamond2.pcx", "diamond3.pcx", "diamond4.pcx", "diamond5.pcx" } };

char *character_filenames[ NUM_CHARACTERS ][ 10 ]={ {"6", "1", "SS", "sawman1.pcx", "sawman1.pcx", "sawman2.pcx", "sawman3.pcx", "sawman4.pcx", "sawman4.pcx"},
             				            {"4", "1", "SS", "olminer1.pcx", "olminer1.pcx", "olminer2.pcx", "olminer1.pcx"} };

#endif
