#define upKEY     72
#define downKEY   80
#define leftKEY   75
#define rightKEY  77

#define BOAT          "boat.pcx"
#define TANK          "tank.pcx"
#define SIDESWIPER    "sideswip.pcx"
#define BOMBER        "bomber.pcx"
#define MINIPERRY     "minipery.pcx"
#define WTRBALLOON    "wbalon.pcx"
#define SEPLANE       "stkwshdw.pcx"
#define PERPLANE      "perryp.pcx"

#define SCENE         "r&stream.pcx"
#define SCENE2        "desert2.pcx"
#define SCENE3        "highway.pcx"
#define SCENE4        "nightsea.pcx"

#define REDBULLET     "rbullet.pcx"
#define BLUEBULLET    "bbullet.pcx"
#define YELLOWBULLET  "ybullet.pcx"

#define REDBULLET_PER     "rbullet2.pcx"
#define BLUEBULLET_PER    "bbullet2.pcx"
#define YELLOWBULLET_PER  "ybullet2.pcx"

#define SEPLANE_HIT1  "stkwshd2.pcx"
#define SEPLANE_HIT2  "stkwshd3.pcx"
#define PERPLANE_HIT1 "perryp2.pcx"
#define PERPLANE_HIT2 "perryp3.pcx"

#define SEPLANE_BUP1  "stkbup1.pcx"
#define SEPLANE_BUP2  "stkbup2.pcx"
#define SEPLANE_BUP3  "stkbup3.pcx"

#define BLOWUP_1      "blowup1.pcx"
#define BLOWUP_2      "blowup2.pcx"
#define BLOWUP_3      "blowup3.pcx"

#define GAMEOVER_PIC  "gameover.pcx"
#define YOUWIN_PIC    "youwin.pcx"
#define NEXTLEVEL_PIC "levelfin.pcx"

/* power ups */
#define ENERGY_PIC    "firstaid.pcx"
#define SPEED_PIC     "speed.pcx"
#define BLUEB_PIC     "bbulletp.pcx"
#define REDB_PIC      "rbulletp.pcx"
#define YELLOWB_PIC   "ybulletp.pcx"

#define MAINTITLE_TITLE    "title.pcx"
#define MAINTITLE_PICTURE  "desert.pcx"
#define MAINTITLE_SRTOPTNS "strtoptn.pcx"
#define MAINTITLE_CURSOR   "bbullet.pcx"
#define MAINTITLE_PLYRCHSE "perrystk.pcx"
#define MAINTITLE_OPTIONS  "dificult.pcx"

/* Stick E.'s bullets */
#define _redBULLET     1
#define _blueBULLET    2
#define _yellowBULLET  3

/* Perry's bullets */
#define _redBULLET_PER     4
#define _blueBULLET_PER    5
#define _yellowBULLET_PER  6

/* an underscore signifies an object */
#define _waterballoon  1
#define _miniperry     2
#define _bomber        3
#define _sideswipe     4
#define _tank          5
#define _boat          6
#define _enemybullet   7

#define _energy        1
#define _speed         2
#define _bb            3
#define _rb            4
#define _yb            5

#define MAXSPEED   25
#define MINSPEED    1

#define MAXPLANESPEED 15
#define MINPLANESPEED  3

#define MAXLEVEL       4

#define PAUSE            while ( !kbhit() )
#define DISCARDKEY       if ( kbhit() ) getch();
#define WAIT(x)   for(temparg=-120000L;temparg<=(10000*(x));++temparg);

#define OFF 0
#define ON  1

#define SCORES_FILE "hiscore.dat"

#include <stdlib.h>
#include <fcntl.h>
#include <conio.h>
#include <stdio.h>
#include <alloc.h>
#include <dos.h>
#include <joystick.h>
#include <music.h>

/***************************************************************************/
/*************************   Global varibles    ****************************/
/***************************************************************************/

typedef struct {
	char    manufacturer;
	char    version;
	char    encoding;
	char    bits_per_pixel;
	int     xmin,ymin;
	int     xmax,ymax;
	int     hres;
	int     vres;
	char    pallete[48];
	char    reserved;
	char    colour_planes;
	int     bytes_per_line;
	int     pallete_type;
	char    filler[58];
		} PCXHEAD;
PCXHEAD   header;

/* The variable header is a struct that will contain all the usefull picture
information shown in the above fields.  */

unsigned int width,depth;    /* will hold the header info for width and depth*/
unsigned int bytes;

typedef struct {
					long int score;
					char initials[3];
					} SCORE;

typedef struct {
					SCORE    num[5]; } HISCORES;

HISCORES scorelist;

typedef struct {
					int x, y, dx, dy, object, width, depth, status;
					} OBJECT;

OBJECT objectlist[ 20 ], poweruplist[ 10 ];

typedef struct {
					int x, y, dx, dy, type, homeon;
					} BULLET;

BULLET shots[ 10 ];          //max bullets on screen at one time

char palette[768];

typedef long int counter_type;


char UJ = 1;             /*<<********** U S E   J O Y S T I C K *********/


char *video, *videoscreen, *scrollingscreen; //virtual screens (execpt vidscr)
char *WTRBLN, *rbullet, *ybullet, *bbullet;
char *miniPERRY, *bomber, *tank;

char *SEPlane_HIT1, *SEPlane_HIT2,
	  *SEPlane_BUP1, *SEPlane_BUP2, *SEPlane_BUP3;

char  *buffer,
		*SEPlane;

char *blowup1, *blowup2, *blowup3;

char *gameover_title, *youwin_title;

char *energyPOWER, *speedPOWER, *bbPOWER, *rbPOWER, *ybPOWER;

char *LEVEL1;                          //will hold all information for level1
long int placeinLEVEL;                 //holds current place in level

char *LEVEL1_powerups;
long int placeinpowerups = 0;

int objectsinLEVEL, MAXOBJECTS;
int bulletsinLEVEL;
int powerupsinLEVEL;

int curLEVEL = 1;      /* <---------- C u r r e n t   l e v e l *************/
int startingover = 0;

int levellength = 12000;         //length of level 0 - 20000
int leveldifficulty = 3;         //diffuculty 1-5

long int index;       //place in buffer (for scrolling)

char Music = ON;      /************ T U R N   M U S I C   O N   O R   O F F */

int xloc     = 135,   //player locations
	 yloc     = 75 ;

long int score = 0;

long int noof_bbs = 20,
			noof_rbs = 10,
			noof_ybs = 30;

char scrollspeed        = 2,
	  planespeed         = 3,
	  energy             = 10,
	  hitplaneANIMATION  = 0,
	  killplaneANIMATION = 0;

FILE          *input;

/***************************************************************************/
/*****************************   S O N G S    ******************************/
/***************************************************************************/

/* I N T R O D U C T I O N   S O N G  */
unsigned char entertainer[] = {
	SO,1,   D,EI, Ds,EI, E,EI,
	SO,2,   C,EI, R ,EI,
	SO,1,   E,EI,
	SO,2,   C,EI, R,EI,
	SO,1,   E,EI,
	SO,2,   C,H, R,Q, D,EI, Ds,EI, E,EI, C,EI, D,EI, E,EI, R,EI,
	SO,1,   B,EI,
	SO,2,   D,Q, C,H+Q,

	SO,1,   D,EI, Ds,EI, E,EI,
	SO,2,   C,EI, R ,EI,
	SO,1,   E,EI,
	SO,2,   C,EI, R,EI,
	SO,1,   E,EI,
	SO,2,   C,H, R,Q,
	SO,1,   A,EI, G,EI, Fs,EI, A,EI,
	SO,2,   C,EI, E,EI, R,EI, D,EI, C,EI,
	SO,1,   A,EI,
	SO,2,   D,H, R,Q,
	/************************/
	SO,1,   D,EI, Ds,EI, E,EI,
	SO,2,   C,EI, R ,EI,
	SO,1,   E,EI,
	SO,2,   C,EI, R,EI,
	SO,1,   E,EI,
	SO,2,   C,H, R,Q, D,EI, Ds,EI, E,EI, C,EI, D,EI, E,EI, R,EI,
	SO,1,   B,EI,
	SO,2,   D,Q, C,H+Q,

			  C,EI, D,EI, E,EI, C,EI, D,EI, E,EI, R,Q, C,EI, D,EI, C,EI,
			  E,EI, C,EI, D,EI, E,EI, R,Q, C,EI, D,EI, C,EI, E,EI, C,EI,
			  D,EI, E,EI, R,EI,
	SO,1,   B,EI,
	SO,2,   D,Q, C,H+Q, R,W,R,W,R,W,R,W, REPEAT };


/* G A M E    O V E R   S O N G */
unsigned char taps[]={SO,1,G,W,R,EI,G,Q,R,EI,SO,2,C,DW,R,W,
	SO,1,G,W,R,EI,SO,2,C,Q,R,EI,E,DW,R,DW,
	SO,1,G,W,R,EI,SO,2,C,Q,R,EI,E,W,R,S,
	SO,1,G,W,R,EI,SO,2,C,Q,R,EI,E,W,R,S,
	SO,1,G,W,R,EI,SO,2,C,Q,R,EI,E,W,R,S,
	R,W,C,W,R,EI,E,Q,R,EI,G,W,
	R,W,E,W,R,EI,C,W,R,EI,SO,1,G,W,R,W,
	G,W,R,EI,G,Q,R,EI,SO,2,C,DW,R,DW,R,DW,
	END};

/* L E V E L   1   S O N G */
unsigned char Contra[] =
{
	 SO,1,    D,Q, D,Q, F,Q, D,Q, Gs,H-S, G,H-S, F,Q,
		  D,Q, D,Q, F,Q, D,Q, Gs,H-S, G,H-S, F,Q,
		  D,Q, D,Q, F,Q, D,Q, Gs,H-S, G,H-S, F,Q,
		  D,Q, D,Q, F,Q, D,Q, G,H-S, Gs,H-S, A,Q,

		  E,Q, E,Q, G,Q, E,Q, As,H-S, A,H-S, G,Q,
		  E,Q, E,Q, G,Q, E,Q, As,H-S, A,H-S, G,Q,
		  E,Q, E,Q, G,Q, E,Q, As,H-S, A,H-S, G,Q,
		  E,Q, E,Q, G,Q, E,Q, A,H-S, As,H-S, B,Q,

		  F,Q, R,Q, D,Q, R,Q, Fs,Q, R,Q, D,Q, R,Q,
		  F,Q, R,Q, D,Q, R,Q, Fs,Q, R,Q, D,Q, R,Q,
		  F,Q, F,Q, D,Q, D,Q, Fs,Q, Fs,Q, D,Q, D,Q,
		  F,Q, F,Q, D,Q, D,Q, Fs,Q, Fs,Q, D,Q, D,Q,
		  F,Q, F,Q, D,Q, D,Q, Fs,Q, Fs,Q, D,Q, D,Q,
		  F,Q, F,Q, D,Q, D,Q, G,H-S, Gs,H-S, A,EI,     REPEAT
};

/***************************************************************************/
/***********************    Number pictures      **************************/
/***************************************************************************/

char one[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,0,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,0 };

char two[] = {   10,10,
		0,0,1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,
		0,0,1,1,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0 };

char three[] = {  10,10,
		0,0,1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,1,1,1,1,0,0,
		0,0,0,0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,0,0,0 };

char four[] = {   10,10,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,1,1,0,0,
		0,1,1,0,0,0,1,1,0,0,
		0,1,1,0,0,0,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,0,1,1,0,0 };

char five[] = { 10,10,
		0,0,1,1,1,1,1,1,1,0,
		0,0,1,1,1,1,1,1,1,0,
		0,0,1,1,0,0,0,0,0,0,
		0,0,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,1,1,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,1,0,0 };

char six[] = {  10,10,
		0,0,0,0,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,0,0,
		0,0,1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,1,1,1,1,0,0,
		0,1,1,1,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char seven[] = { 10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0 };

char eight[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,0,0,0 };

char nine[] = {   10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,0,0,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,1,1,0,0,
		0,0,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,0,0,0,0 };

char zero[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,1,0,1,1,0,
		0,1,1,0,0,1,0,1,1,0,
		0,1,1,0,1,0,0,1,1,0,
		0,1,1,0,1,0,0,1,1,0,
		0,1,1,1,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char a_A[] = {  10,10,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };

char b_B[] = {  10,10,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,0,0,0 };

char c_C[] = {  10,10,
		0,0,0,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,1,0,
		0,0,0,1,1,1,1,1,0,0 };

char d_D[] = {  10,10,
		0,1,1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,0,0,0 };

char e_E[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0 };

char f_F[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0 };

char g_G[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,1,1,1,1,1,0,
		0,1,1,0,1,1,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char h_H[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };

char i_I[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0 };

char j_J[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,0,0,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char k_K[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,1,1,0,0,
		0,1,1,0,0,1,1,0,0,0,
		0,1,1,0,1,1,0,0,0,0,
		0,1,1,1,1,0,0,0,0,0,
		0,1,1,1,1,1,0,0,0,0,
		0,1,1,0,0,1,1,0,0,0,
		0,1,1,0,0,0,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0 };

char l_L[] = {  10,10,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0 };

char m_M[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,0,0,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,0,1,1,0,1,1,0,
		0,1,1,0,1,1,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };

char n_N[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,1,0,0,0,1,1,0,
		0,1,1,1,0,0,0,1,1,0,
		0,1,1,0,1,0,0,1,1,0,
		0,1,1,0,1,0,0,1,1,0,
		0,1,1,0,0,1,0,1,1,0,
		0,1,1,0,0,1,0,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };

char o_O[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char p_P[] = {  10,10,
		0,1,1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0 };

char q_Q[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,1,0,1,1,0,
		0,1,1,0,0,1,1,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,0,1,1,1,1,1,1,1,0,
		0,0,0,1,1,1,1,0,1,1 };

char r_R[] = {  10,10,
		0,1,1,1,1,1,1,0,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,1,1,1,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };


char s_S[] = {  10,10,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,0,0,0,
		0,0,1,1,1,1,1,0,0,0,
		0,0,0,1,1,1,1,1,0,0,
		0,0,0,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char t_T[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0 };

char u_U[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0 };

char v_V[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0 };

char w_W[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,1,1,0,1,1,0,
		0,1,1,0,1,1,0,1,1,0,
		0,1,1,0,1,1,0,1,1,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,1,1,1,1,1,1,0,0,
		0,0,0,1,0,0,1,0,0,0 };

char x_X[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,1,1,0,0,1,1,0,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0 };

char y_Y[] = {  10,10,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,1,1,0,0,0,0,1,1,0,
		0,0,1,1,0,0,1,1,0,0,
		0,0,0,1,1,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,0,1,1,0,0,0,0 };

char z_Z[] = {  10,10,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,1,1,0,0,0,
		0,0,0,0,1,1,0,0,0,0,
		0,0,0,1,1,0,0,0,0,0,
		0,0,1,1,0,0,0,0,0,0,
		0,1,1,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0 };

char dash[] = {  10,10,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0 };

/***************************************************************************/

enemybullet[] = {  3,3,
				 10,10,10,
				 10,15,10,
				 10,10,10 };

/***************************************************************************/
/***********************   Function Prototypes    **************************/
/***************************************************************************/

void cpalette(unsigned char color, char r, char g, char b );
void scrolly (char speed, char direction, char *buffer, char *what );
void flip    (char *dest, char *source, char transparent, int bytes );
void deinit(void);           /* return to normal     */
void setVGApalette(char *p); /* set the vga pallete  */
void ReadBuffer_A(FILE *fp, char *buffer );
void ReadBGBuffer(FILE *fp, char *buffer );
FILE *open_pic (char *filename);
void open_image(char *filename, char *pic);
void put_image (char *pic, int ulx, int uly, char transparent );
void put_image_hflip (char *pic, int ulx, int uly, char transparent );
void put_image_vflip (char *pic, int ulx, int uly, char transparent );
void put_letter (char *pic, int ulx, int uly, char transparent, char color );
void makelevels(void);
void drawobjects(void);
void drawpowerups(void);
void drawbullets(void);
void shootbullet( char type );
void checkbullethit( void );
void checkplanehit( void );
void checkpoweruphit( void );
void hitplane( void );
void killplane(void);
void endgame( void );
void wingame( void );
void cleanup( void );
void drawenergy( void );
void drawbulletmeter( void );
void printNUM( int x, int y, long int num, char color);
void printSTR( int x, int y, char *str   , char color);
void gotonextLEVEL(void);
void initLEVEL(void);
int findclosestenemy( int bulletno );
long sqrt_FAST(long v);   //used for homing missile ( to find shortest distance )
void increasePOWERspeed(void);
void decreasePOWERspeed(void);
void openHISCORES( void );
void saveHISCORES( void );
void printHISCORES( void );
void checkHISCORES( void );
void shootenemybullet( void );
void fade_to_black( void );
void fade_to_palette( void );

/***************************************************************************/
/***********************      MAIN PROGRAM        **************************/
/***************************************************************************/

main(int argc, char *argv[])
{
/***************************************************************************/
/*******************  Begin declaration of variables   *********************/
/***************************************************************************/

	FILE *input_temp, *input_temp2;
	counter_type  temparg=0;

	char
			 key       = 't',
			 dir       = -1  ;

	int c,
		 JoyButton,
		 JoyPad  = 0,
		 Tred    = 0,
		 Tyellow = 0,
		 Tblue   = 0,
		 Tgreen  = 0,
		 T84     = 0;

	/****************************************************/
	/**** Intro, main title, and option screen(s) *******/
	/****************************************************/

	char *mt_title, *mt_picture, *mt_strtoptn, *mt_cursor, *temp;
	char start_options = 1, player_options = 1;

	if ( argc >= 1 ) if ( argv[1] == "-m" || argv[1] == "-M" ) Music == OFF;

	/*initialize vgamode 320x200 in 256 color mode*/
	asm {
		 mov  ax, 13h
		 int  10h
		 };

	if ( Music == ON ) install( entertainer );

	videoscreen = MK_FP( 0xa000, 0 );           //make pointer to video screen
	video           = (char *)malloc(64000);    //virtual screen

	mt_title    = (char *)malloc(64000);
	mt_picture  = (char *)malloc(64000);
	mt_strtoptn = (char *)malloc(20000);
	mt_cursor   = (char *)malloc(  102);
	temp        = (char *)malloc(64000);

	input_temp  = open_pic  ( MAINTITLE_PICTURE  );
	input_temp2 = open_pic  ( MAINTITLE_TITLE    );

	open_image( MAINTITLE_SRTOPTNS, mt_strtoptn);
	open_image( MAINTITLE_CURSOR  , mt_cursor  );

	setVGApalette( palette );
	cpalette( 0, 1, 1, 1);                      //make color #0 = black

	ReadBGBuffer(input_temp , mt_picture  );
	ReadBGBuffer(input_temp2, mt_title    );

	fclose( input_temp  );
	fclose( input_temp2 );

	memcpy( temp, mt_title, 64000 );

mainscreen:

	memcpy( video, mt_picture, 64000 );

	temparg = 0;
	for(JoyButton=0;JoyButton<=199;++JoyButton) //same thing as put_image
		for (c = 0; c<=319; ++c)                 //but put_image(...) wouldn't
		{                                        //work :( ??????????
			if ( mt_title[temparg] != 0 )
				video[ c+(JoyButton*320) ] = mt_title[temparg];
			++temparg;
		}

	memcpy( videoscreen, video, 64000);

	PAUSE;     /* Wait for key press or, if joystick enabled, button press */

	put_image( mt_strtoptn, 100, 90, 0);
	memcpy( mt_title, video, 64000);
	put_image( mt_cursor, 100, 80+(17*start_options), 0);
	memcpy( videoscreen, video, 64000);

	DISCARDKEY;
	key = 0; //initialize key
	while ( key != 13 )
	{
		key    = 0; //initialize pad & key

		while ( key != upKEY && key != downKEY &&  key != 13  )
		{
			if ( kbhit() ) key = getch();
		}
		if ( key != 13 )
			if ( start_options == 1 )
				start_options = 2;
			else
				start_options = 1;

		memcpy( video, mt_title, 64000);  //refresh screen
		put_image( mt_cursor, 100, 80+(17*start_options), 0); //put cursor
		memcpy( videoscreen, video, 64000);                   //show screen
	}

	if ( start_options == 2 )     /************ option screen  ***********/
	{
		memcpy( video, mt_picture, 64000);
		open_image( MAINTITLE_OPTIONS, mt_title );
		temparg == 2;
		for(JoyButton=0;JoyButton<=199;++JoyButton) //same thing as put_image
		for (c = 60; c<=379; ++c)                 //but put_image(...) wouldn't
		{                                        //work :( ??????????
			if ( mt_title[temparg] != 0 )
				video[ c+(JoyButton*320) ] = mt_title[temparg];
			++temparg;
		}
		memcpy( mt_title, video, 64000);    //copy whats on screen at this point
		put_image( mt_cursor, 15, 50+(20*leveldifficulty), 0);
		memcpy( videoscreen, video, 64000 );

		key = 0; //initialize key
		while ( key != 13 )
		{
			key    = 0; //initialize pad & key

			while ( key != upKEY && key != downKEY &&  key != 13  )
			{
				if ( kbhit() ) key = getch();
			}

			if ( key != 13 )
			{
				if ( key == upKEY   ) --leveldifficulty;
				if ( key == downKEY ) ++leveldifficulty;
				if ( leveldifficulty < 1 ) leveldifficulty = 1;
				if ( leveldifficulty > 5 ) leveldifficulty = 5;
			}

			memcpy( video, mt_title, 64000);
			put_image( mt_cursor, 15, (50+(20*leveldifficulty)), 0);  //put cursor
			memcpy( videoscreen, video, 64000);                     //show screen
		}
		memcpy( mt_title, temp, 64000 );
		goto mainscreen;
	}

	if ( start_options == 1 )        /********** choose player **********/
	{
		memcpy( video, mt_picture, 64000 );
		open_image( MAINTITLE_PLYRCHSE, mt_title );
		for(JoyButton=0;JoyButton<=199;++JoyButton) //same thing as put_image
		for (c = 60; c<=379; ++c)                 //but put_image(...) wouldn't
		{                                        //work :( ??????????
			if ( mt_title[temparg] != 0 )
				video[ c+(JoyButton*320) ] = mt_title[temparg];
			++temparg;
		}
		cpalette( 22, 45, 23, 4 );  //hide player description if not hilighted
		cpalette( 23, 45, 23, 4 );
		memcpy( videoscreen ,video, 64000 );

	/*********** Get player choice **************/

	if ( player_options == 1 )
		{
			cpalette( 22, 63, 0, 0 );
			cpalette( 23, 45, 22, 4 );
		}
		else
		{
			cpalette( 22, 45, 22, 4 );
			cpalette( 23, 63, 0, 0 );
		}

	DISCARDKEY;
	key = 0; //allow into the loop
	while ( key != 13 )
	{
		key    = 0; //initialize pad & key

		while ( key != upKEY && key != downKEY &&  key != 13  )
		{
			if ( kbhit() ) key = getch();
		}
		if ( key != 13 )
			if ( player_options == 1 )
				player_options = 2;
			else
				player_options = 1;

		if ( player_options == 1 )
		{
			cpalette( 22, 63, 0, 0 );
			cpalette( 23, 45, 23, 4 );
		}
		else
		{
			cpalette( 22, 45, 23, 4 );
			cpalette( 23, 63, 0, 0 );
		}
	}
	}

	if ( Music == ON ) restore();

	memset( videoscreen, 0, 64000 );

	cpalette( 22, 63, 63, 63 );   //undo palette changes
	cpalette( 23, 63, 63, 63 );

	free( mt_title    );    /* free up memory used by introduction */
	free( mt_picture  );
	free( mt_strtoptn );
	free( mt_cursor   );
	free( temp        );


/***************************************************************************/
/*********************  Allocate memory to variables   *********************/
/***************************************************************************/

	buffer  = (char *) malloc(64000);

	scrollingscreen = (char *)malloc(64000);    //background screen
	LEVEL1          = (char *)malloc(20000);    //info for level 1
	LEVEL1_powerups = (char *)malloc(20000);

	SEPlane   = (char *)malloc( 2502 ); //allocate memory for plane sprite
	WTRBLN    = (char *)malloc(  902 ); //allocate memory for balloon sprite
	miniPERRY = (char *)malloc(  902 ); //allocate memory for mini-Perry sprite
	bomber    = (char *)malloc(  902 ); //allocate memory for bomber sprite
	tank      = (char *)malloc(  902 );

	SEPlane_HIT1 = (char *)malloc( 2502 );
	SEPlane_HIT2 = (char *)malloc( 2502 );

	SEPlane_BUP1 = (char *)malloc( 2502 );
	SEPlane_BUP2 = (char *)malloc( 2502 );
	SEPlane_BUP3 = (char *)malloc( 2502 );

	gameover_title = (char *)malloc( 2502 );
	youwin_title   = (char *)malloc( 2502 );

	energyPOWER    = (char *)malloc( 102 );
	speedPOWER     = (char *)malloc( 102 );
	rbPOWER        = (char *)malloc( 102 );
	ybPOWER        = (char *)malloc( 102 );
	bbPOWER        = (char *)malloc( 102 );

	blowup1 = (char *)malloc( 902 );
	blowup2 = (char *)malloc( 902 );
	blowup3 = (char *)malloc( 902 );

/***************************************************************************/
/************************  INITIALIZE VARIABLES   **************************/
/***************************************************************************/

	if ( player_options == 1 )
		open_image(PERPLANE   , SEPlane  );  //Lt. Perry
	else
		open_image(SEPLANE   , SEPlane   );  //Stick E.

	if ( player_options == 1 )                       //Lt. Perry
	{
		open_image(PERPLANE_HIT1 , SEPlane_HIT1 );
		open_image(PERPLANE_HIT2 , SEPlane_HIT2 );
	}
	else                                             //Stick E.
	{
		open_image(SEPLANE_HIT1 , SEPlane_HIT1 );
		open_image(SEPLANE_HIT2 , SEPlane_HIT2 );
	}
	open_image(SEPLANE_BUP1 , SEPlane_BUP1 );
	open_image(SEPLANE_BUP2 , SEPlane_BUP2 );
	open_image(SEPLANE_BUP3 , SEPlane_BUP3 );

	open_image( GAMEOVER_PIC, gameover_title );
	open_image( YOUWIN_PIC, youwin_title );

	open_image( ENERGY_PIC , energyPOWER );
	open_image( SPEED_PIC  , speedPOWER  );
	open_image( BLUEB_PIC  , bbPOWER     );
	open_image( REDB_PIC   , rbPOWER     );
	open_image( YELLOWB_PIC, ybPOWER     );

	open_image( BLOWUP_1, blowup1 );
	open_image( BLOWUP_2, blowup2 );
	open_image( BLOWUP_3, blowup3 );

	bbullet         = (char *)malloc(102);      //blue bullet
	rbullet         = (char *)malloc(102);      //red bullet
	ybullet         = (char *)malloc(102);      //yellow bullet

	if ( player_options == 1 )    //Lt. Perry
	{
		open_image(REDBULLET_PER   , rbullet);
		open_image(YELLOWBULLET_PER, ybullet);
		open_image(BLUEBULLET_PER  , bbullet);
	}
	else
	{
		open_image(REDBULLET   , rbullet);
		open_image(YELLOWBULLET, ybullet);
		open_image(BLUEBULLET  , bbullet);
	}

	MAXOBJECTS = 10 + (2*leveldifficulty);

/***************************************************************************/
/************************  Begin game rountines   **************************/
/***************************************************************************/


/*
 The rest of the program is repeated throughout every level.  The
previous part of this program was to be repeated only once.
*/

beginlevel:

	memset( videoscreen, 0, 64000 );
	initLEVEL();

	makelevels();                      //create the levels

/***************************************************************************/
/********************   End variable initilzation   ************************/
/***************************************************************************/

/**************************************************************************/
/**********************  System initialized *******************************/
/**************************************************************************/

		ReadBGBuffer(input , buffer );              //get background picture
		fclose(input );

		memcpy ( scrollingscreen, buffer, 64000 );

		if ( Music == ON ) install( Contra );    //play song

		while ( key != 'q' )
		{
			while ( !kbhit() )
			{
				/**********************************/
				/******* Joystick readings ********/
				/**********************************/

				if ( xloc > 269 ) xloc = 269;
				if ( xloc < 0   ) xloc =   0;

				if ( yloc > 149 ) yloc = 149;
				if ( yloc < 0   ) yloc =   0;

				JoyButton = JoyButtonPressed();

				if ( JoyButton == 0 )
				{
					Tred    = 0;
					Tyellow = 0;
					Tgreen  = 0;
					Tblue   = 0;
					T84     = 0;
				}

				if ( JoyButton == redBUTTON  && Tred == 0 && noof_rbs > 0 )
				{
					--noof_rbs;
					if ( player_options == 1 )        //Perry
						shootbullet( _redBULLET_PER    );
					else
						shootbullet( _redBULLET    );
					Tred = 1;
				}

				if ( JoyButton == yellowBUTTON && Tyellow == 0 && noof_ybs > 0)
				{
					--noof_ybs;
					if ( player_options == 1 )        //Perry
						shootbullet( _yellowBULLET_PER    );
					else
						shootbullet( _yellowBULLET    );
					Tyellow = 1;
				}

				if ( JoyButton == -84 && T84 == 0 && noof_bbs > 0)   //both buttons
				{
					--noof_bbs;
					if ( player_options == 1 )        //Perry
						shootbullet( _blueBULLET_PER    );
					else
						shootbullet( _blueBULLET    );
					T84 = 1;
				}

				if ( JoyButton == blueBUTTON && Tblue == 0 )
				{
					++scrollspeed;
					if ( scrollspeed <= MAXSPEED ) increasePOWERspeed();
					if ( scrollspeed > MAXSPEED ) scrollspeed = MAXSPEED;
					Tblue = 1;
				}

				if ( JoyButton == greenBUTTON && Tgreen == 0 )
				{
					--scrollspeed;
					if ( scrollspeed >= MINSPEED ) decreasePOWERspeed();
					if ( scrollspeed < MINSPEED ) scrollspeed = MINSPEED;
					Tgreen = 1;
				}

				xloc += planespeed*JoyPadX();
				yloc += planespeed*JoyPadY();

				/**********************************/
				/******* Graphical drawing ********/
				/**********************************/

				checkbullethit ();
				checkplanehit  ();
				checkpoweruphit();

				scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
				memcpy   ( video, scrollingscreen, 64000);

				drawpowerups();
				drawobjects();
				if ( startingover == 1 ) break;
				drawbullets();

				/****************************************************/
				/**************** Plane animation *******************/
				/****************************************************/

				if ( killplaneANIMATION == 5 )
				{
					put_image(SEPlane_BUP1 , xloc  , yloc, 0);
					--killplaneANIMATION;
				}
				else if ( killplaneANIMATION == 4 )
				{
					put_image(SEPlane_BUP2 , xloc  , yloc, 0);
					--killplaneANIMATION;
				}
				else if ( killplaneANIMATION == 3 )
				{
					put_image(SEPlane_BUP3 , xloc  , yloc, 0);
					--killplaneANIMATION;
				}
				else if ( killplaneANIMATION == 2 )
				{
					--killplaneANIMATION;
				}
				else if ( killplaneANIMATION == 1 )
				{
					endgame();
				}
				else if ( hitplaneANIMATION == 3 )
				{
					put_image(SEPlane_HIT1 , xloc  , yloc, 0);
					--hitplaneANIMATION;
				}
				else if ( hitplaneANIMATION == 2 )
				{
					put_image(SEPlane_HIT2 , xloc  , yloc, 0);
					--hitplaneANIMATION;
				}
				else if ( hitplaneANIMATION == 1 )
				{
					put_image(SEPlane_HIT1 , xloc  , yloc, 0);
					--hitplaneANIMATION;
				}
				else put_image(SEPlane    , xloc  , yloc, 0);

				/******************************************************/

				//if ( random(leveldifficulty) != 0 ) shootenemybullet();

				drawenergy();

				printNUM ( 0, 185, score, 1 );

				drawbulletmeter();

				memcpy   (videoscreen, video , 64000  );

			} /* END WHILE( !KBHIT() ) */

			key = getch();

			if ( key == upKEY   ) yloc += -planespeed;
			if ( key == downKEY ) yloc +=  planespeed;
			if ( key == leftKEY ) xloc += -planespeed;
			if ( key == rightKEY) xloc +=  planespeed;
			if ( key == 'm'     )
			{
				if ( Music == ON )
				{
					Music = OFF;
					restore();
				}
				else
				{
					Music = ON;
					install( Contra );
				}
			}
			if ( startingover == 1 ) break;
		}
		if ( startingover == 1 ) goto beginlevel;
		if ( Music == ON ) restore();
deinit();
return 0;
}


/***************************************************************************/
/***********************      BEGIN FUNCTIONS     **************************/
/***************************************************************************/

void drawbulletmeter( void )
{
	put_image( bbullet, 150, 185, 0 );
	printNUM ( 150, 185, noof_bbs, 1 );

	put_image( rbullet, 200, 185, 0 );
	printNUM ( 200, 185, noof_rbs, 1 );

	put_image( ybullet, 250, 185, 0 );
	printNUM ( 250, 185, noof_ybs, 1 );
}

void drawenergy( void )
{
	int incr;

	for ( incr = 0; incr < energy; ++incr )
		put_image( energyPOWER, (15*incr), 0, 0 );

	put_image( speedPOWER, 0, 15, 0 );
	printNUM ( 0, 15, planespeed, 1 );
}

void checkpoweruphit( void )
{
	int objectno;

	for ( objectno = 1; objectno <= 10; ++objectno )
	{
		if ( poweruplist[ objectno ].x != -1 )
		{
			if ( (xloc+50) >= (poweruplist[ objectno ].x)                               &&
				  (xloc   ) <= (poweruplist[ objectno ].x+poweruplist[ objectno ].width) &&
				  (yloc+10) >= (poweruplist[ objectno ].y)                               &&
				  (yloc   ) <= (poweruplist[ objectno ].y+poweruplist[ objectno ].depth) )
			{
				poweruplist[ objectno ].x    = -1;
				poweruplist[ objectno ].y    = -1;
				if ( poweruplist[ objectno ].object == _energy ) ++energy;
				if ( poweruplist[ objectno ].object == _speed  ) if ( planespeed < MAXPLANESPEED ) ++planespeed;
				if ( poweruplist[ objectno ].object == _bb && noof_bbs < 999 ) noof_bbs += 2;
				if ( poweruplist[ objectno ].object == _rb && noof_rbs < 999 ) noof_rbs += 2;
				if ( poweruplist[ objectno ].object == _yb && noof_ybs < 999 ) noof_ybs += 2;
				--powerupsinLEVEL;
			}
		}
	}
}

void checkplanehit( void )
{
	int objectno;

	for ( objectno = 1; objectno <= MAXOBJECTS; ++objectno )
	{
		if ( objectlist[ objectno ].x != -1 )
		{
			if ( (xloc+50) >= (objectlist[ objectno ].x)                              &&
				  (xloc   ) <= (objectlist[ objectno ].x+objectlist[ objectno ].width) &&
				  (yloc+10) >= (objectlist[ objectno ].y)                              &&
				  (yloc   ) <= (objectlist[ objectno ].y+objectlist[ objectno ].depth) )
			{
				if ( objectlist[ objectno ].status == 0 )
				{
					objectlist[ objectno ].status = 4; //blow up plane (3 frames)
					--objectsinLEVEL;
					hitplane();
				}
			}
		}
	}
}

void hitplane( void )
{
	if ( energy < 5 && planespeed > MINPLANESPEED) --planespeed;
	--energy;
	if ( energy == 0 ) killplane();
	hitplaneANIMATION = 3;
}

void killplane( void )
{
	killplaneANIMATION = 5;
}

void gotonextLEVEL(void)
{
	if ( Music == ON ) restore();

	++curLEVEL;
	if ( curLEVEL > MAXLEVEL ) wingame();

	open_image( NEXTLEVEL_PIC, youwin_title );

	while ( !kbhit() )
	{
		scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
		memcpy   ( video, scrollingscreen, 64000);
		put_image(SEPlane  , xloc,  yloc, 0);

		if ( xloc < 135 ) ++xloc;        /* brings plane to the center */
		else if ( xloc > 135 ) --xloc;
		if ( yloc < 140 ) ++yloc;
		else if ( yloc > 140 ) --yloc;

		put_image( youwin_title, 130, 50, 0 );
		printNUM( 138, 90, curLEVEL, 237 );
		memcpy   (videoscreen, video , 64000  );
	}
	startingover = 1;
	open_image( YOUWIN_PIC, youwin_title );
}


void wingame ( void )
{
	char key = 12;

	while ( key != 13 )
	{
		if ( kbhit() ) key = getch();
		scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
		memcpy   ( video, scrollingscreen, 64000);
		put_image(SEPlane  , xloc,  yloc, 0);

		if ( xloc < 135 ) ++xloc;        /* brings plane to the center */
		else if ( xloc > 135 ) --xloc;
		if ( yloc < 140 ) ++yloc;
		else if ( yloc > 140 ) --yloc;

		put_image( youwin_title, 130, 50, 0 );
		memcpy   (videoscreen, video , 64000  );
	}

	openHISCORES();
	checkHISCORES();
	saveHISCORES();

	while ( key == 13 )
	{
		if ( kbhit() ) key = getch();
		scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
		memcpy   ( video, scrollingscreen, 64000);
		printHISCORES();
		memcpy   (videoscreen, video , 64000  );
	}

	cleanup();
	exit(1);
}

void endgame ( void )
{
	char key=13;
	if ( Music == ON ) { restore(); install( taps ); }

	openHISCORES();
	checkHISCORES();
	saveHISCORES();

	while ( key == 13 )
	{
		if ( kbhit() ) key = getch();
		scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
		memcpy   ( video, scrollingscreen, 64000);
		printHISCORES();
		memcpy   (videoscreen, video , 64000  );
	}

	while ( key != 13 )
	{
		if ( kbhit() ) key = getch();
		scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
		memcpy   ( video, scrollingscreen, 64000);
		put_image( gameover_title, 130, 50, 0 );
		memcpy   (videoscreen, video , 64000  );
	}
	cleanup();
	exit(1);
}

int findclosestenemy( int bulletno )
{
	int objectno, min = 2000, closest, x, y;

	if ( objectsinLEVEL > 0 )
	{
		for ( objectno = 1; objectno <= MAXOBJECTS; ++objectno )
		{
			if ( objectlist[ objectno ].x != -1 )
			{
				x = objectlist[ objectno ].x - shots[ bulletno ].x ;
				y = objectlist[ objectno ].y - shots[ bulletno ].y ;
				if (  sqrt_FAST(  (x*x)  +  (y*y)  ) < min  )
				{
					closest = objectno;
				}
			}
		}
		return( closest );
	}
	return( -1 );
}

void checkbullethit( void )
{
	int bulletno, objectno;

	for ( bulletno = 1; bulletno <= 10; ++bulletno )
	{
		if ( shots[ bulletno ].x != -1 )
		{
			for ( objectno = 1; objectno <= MAXOBJECTS; ++objectno )
			{
				if ( objectlist[ objectno ].x != -1 )
				{
					if ( (shots[ bulletno ].x+10) >= (objectlist[ objectno ].x)                              &&
						  (shots[ bulletno ].x   ) <= (objectlist[ objectno ].x+objectlist[ objectno ].width) &&
						  (shots[ bulletno ].y+10) >= (objectlist[ objectno ].y)                              &&
						  (shots[ bulletno ].y   ) <= (objectlist[ objectno ].y+objectlist[ objectno ].depth) )
					{
						if ( objectlist[ objectno ].status == 0 )
						{
							objectlist[ objectno ].status = 4;   //blow up (3 frames)
							if ( objectlist[ objectno ].object == _waterballoon )
								score += 100*leveldifficulty;
							if ( objectlist[ objectno ].object == _miniperry )
								score += 200*leveldifficulty;
							if ( objectlist[ objectno ].object == _bomber )
								score += 300*leveldifficulty;
							if ( objectlist[ objectno ].object == _tank )
								score += 400*leveldifficulty;
							if ( objectlist[ objectno ].object == _boat )
								score += 500*leveldifficulty;
							if ( objectlist[ objectno ].object == _sideswipe )
								score += 700*leveldifficulty;
							if ( objectlist[ objectno ].object == _enemybullet )
								score += 1000*leveldifficulty;
							--objectsinLEVEL;
							if ( shots[ bulletno ].type != _redBULLET )
							{
								shots     [ bulletno ].x = -1;
								shots     [ bulletno ].y = -1;
								--bulletsinLEVEL;
							}
						}
					}
				}
			}
		}
	}
}

void shootbullet( char type )
{
	int incr=1;

	if ( bulletsinLEVEL < 9 )
	{
		while ( shots[incr].x != -1 && incr <= 10) ++incr;//look for an empty slot for bullet
		if ( type == _redBULLET )
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   = 0;
			shots[ incr ].dy   = -5;
			shots[ incr ].type = _redBULLET;

		}
		if ( type == _blueBULLET )      //forked shot
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   = -4;
			shots[ incr ].dy   = -6;
			shots[ incr ].type = _blueBULLET;
			while ( shots[incr].x != -1 && incr <= 10) ++incr;  //find another place
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   =  4;
			shots[ incr ].dy   = -6;
			shots[ incr ].type = _blueBULLET;
			}
		if ( type == _yellowBULLET )
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   = 0;
			shots[ incr ].dy   = -7-planespeed;
			shots[ incr ].type = _yellowBULLET;
		}
		if ( type == _redBULLET_PER )  //homing bullet
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   =  15;
			shots[ incr ].dy   =  10;
			shots[ incr ].type = _redBULLET_PER;
			shots[ incr ].homeon = findclosestenemy( incr );
		}
		if ( type == _blueBULLET_PER )      //forked shot
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   = -4-planespeed;
			shots[ incr ].dy   = 0;
			shots[ incr ].type = _blueBULLET_PER;
			while ( shots[incr].x != -1 && incr <= 10) ++incr;  //find another place
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   =  4+planespeed;
			shots[ incr ].dy   = 0;
			shots[ incr ].type = _blueBULLET_PER;
			}
		if ( type == _yellowBULLET_PER )
		{
			shots[ incr ].x    = xloc+18;
			shots[ incr ].y    = yloc;
			shots[ incr ].dx   = 0;
			shots[ incr ].dy   = -13-planespeed;
			shots[ incr ].type = _yellowBULLET_PER;
		}
		++bulletsinLEVEL;
	}
}

void drawbullets(void)
{
	int incr;

	for ( incr = 1; incr <= 10; ++incr )
	{
		if ( shots[incr].y <= 0  || shots[incr].y >= 200 ||
			  shots[incr].x <= 0  || shots[incr].x >= 320  )    //bullets are 10x10
		{
			shots[incr].x = -1;
			shots[incr].y = -1;
			--bulletsinLEVEL;
		}
		if ( shots[incr].x != -1 )
		{
			if ( shots[incr].type == _redBULLET )
			{
				put_image( rbullet, shots[incr].x,
										  shots[incr].y, 0 );
				shots[incr].x += shots[incr].dx;
				shots[incr].y += shots[incr].dy;
			}

			if ( shots[incr].type == _yellowBULLET )
			{
				put_image( ybullet, shots[incr].x,
										  shots[incr].y, 0 );
				shots[incr].x += shots[incr].dx;
				shots[incr].y += shots[incr].dy;
			}

			if ( shots[incr].type == _blueBULLET )
			{
				put_image( bbullet, shots[incr].x,
										  shots[incr].y, 0 );
				shots[incr].x += shots[incr].dx;
				shots[incr].y += shots[incr].dy;
		  }
		  if ( shots[incr].type == _redBULLET_PER )
			{
				if ( shots[incr].homeon != -1 && objectlist[ shots[incr].homeon ].x != -1)
				{
					if ( objectlist[ shots[incr].homeon ].y < shots[incr].y )
					{
						put_image( rbullet, shots[incr].x,
												  shots[incr].y, 0 );
						shots[incr].y -= shots[incr].dy;
					}
					else if ( objectlist[ shots[incr].homeon ].y > shots[incr].y )
					{
						put_image_vflip( rbullet, shots[incr].x,
														  shots[incr].y, 0 );
						shots[incr].y += shots[incr].dy;
					}
					if ( objectlist[ shots[incr].homeon ].x < shots[incr].x )
					{
						shots[incr].x -= shots[incr].dx;
					}
					else if ( objectlist[ shots[incr].homeon ].x > shots[incr].x )
					{
						shots[incr].x += shots[incr].dx;
					}
				}
				else
				{
					put_image( rbullet, shots[incr].x,
											  shots[incr].y, 0 );
					shots[incr].x += 0;
					shots[incr].y -= shots[incr].dy;
				}
			}

			if ( shots[incr].type == _yellowBULLET_PER )
			{
				put_image( ybullet, shots[incr].x,
										  shots[incr].y, 0 );
				shots[incr].x += shots[incr].dx;
				shots[incr].y += shots[incr].dy;
			}

			if ( shots[incr].type == _blueBULLET_PER )
			{
				put_image( bbullet, shots[incr].x,
										  shots[incr].y, 0 );
				shots[incr].x += shots[incr].dx;
				shots[incr].y += shots[incr].dy;
		  }

		}
	}
}

void increasePOWERspeed(void)
{
	int incr;

	for ( incr = 1; incr <= 10; ++incr )
		if ( poweruplist[incr].x != -1 )
			++poweruplist[incr].dy;
}

void decreasePOWERspeed(void)
{
	int incr;

	for ( incr = 1; incr <= 10; ++incr )
		if ( poweruplist[incr].x != -1 )
			--poweruplist[incr].dy;
}

void drawpowerups(void)
{
	int incr;
	int x,y;
	long int byte=2;

	for ( incr = 1; incr <= 10; ++incr )
	{
		if ( poweruplist[incr].y >= 199 )
		{
			poweruplist[incr].x = -1;
			poweruplist[incr].y = -1;
			--powerupsinLEVEL;
		}
		if ( poweruplist[incr].x != -1 )
		{
			if ( poweruplist[incr].object == _energy )
			{
				put_image( energyPOWER, poweruplist[incr].x,
												poweruplist[incr].y, 0 );

				poweruplist[incr].x += poweruplist[incr].dx;
				poweruplist[incr].y += poweruplist[incr].dy;
			}
			if ( poweruplist[incr].object == _speed )
			{
				put_image(  speedPOWER, poweruplist[incr].x,
												poweruplist[incr].y, 0 );
				poweruplist[incr].x += poweruplist[incr].dx;
				poweruplist[incr].y += poweruplist[incr].dy;
			}
			if ( poweruplist[incr].object == _bb )
			{
				put_image(  bbPOWER, poweruplist[incr].x,
											poweruplist[incr].y, 0 );
				poweruplist[incr].x += poweruplist[incr].dx;
				poweruplist[incr].y += poweruplist[incr].dy;
			}
			if ( poweruplist[incr].object == _rb )
			{
				put_image(  rbPOWER, poweruplist[incr].x,
											poweruplist[incr].y, 0 );
				poweruplist[incr].x += poweruplist[incr].dx;
				poweruplist[incr].y += poweruplist[incr].dy;
			}
			if ( poweruplist[incr].object == _yb )
			{
				put_image(  ybPOWER, poweruplist[incr].x,
											poweruplist[incr].y, 0 );
				poweruplist[incr].x += poweruplist[incr].dx;
				poweruplist[incr].y += poweruplist[incr].dy;
			}
		}
	}

	if ( LEVEL1_powerups[ placeinpowerups ] != 0 && powerupsinLEVEL < 10 )
	{
		incr = 1;
		while (poweruplist[ incr ].x != -1 && incr <= 10) ++incr;
		if ( LEVEL1_powerups[ placeinpowerups ] == _energy )
		{
			poweruplist[ incr ].x      = random(320);
			poweruplist[ incr ].y      = -9;
			poweruplist[ incr ].dx     = 0;
			poweruplist[ incr ].dy     = scrollspeed;
			poweruplist[ incr ].width  = 10;
			poweruplist[ incr ].depth  = 10;
			poweruplist[ incr ].object = _energy;
		}
		if ( LEVEL1_powerups[ placeinpowerups ] == _speed )
		{
			poweruplist[ incr ].x      = random(320);
			poweruplist[ incr ].y      = -9;
			poweruplist[ incr ].dx     = 0;
			poweruplist[ incr ].dy     = scrollspeed;
			poweruplist[ incr ].width  = 10;
			poweruplist[ incr ].depth  = 10;
			poweruplist[ incr ].object = _speed;
		}
		if ( LEVEL1_powerups[ placeinpowerups ] == _bb )
		{
			poweruplist[ incr ].x      = random(320);
			poweruplist[ incr ].y      = -9;
			poweruplist[ incr ].dx     = 0;
			poweruplist[ incr ].dy     = scrollspeed;
			poweruplist[ incr ].width  = 10;
			poweruplist[ incr ].depth  = 10;
			poweruplist[ incr ].object = _bb;
		}
		if ( LEVEL1_powerups[ placeinpowerups ] == _rb )
		{
			poweruplist[ incr ].x      = random(320);
			poweruplist[ incr ].y      = -9;
			poweruplist[ incr ].dx     = 0;
			poweruplist[ incr ].dy     = scrollspeed;
			poweruplist[ incr ].width  = 10;
			poweruplist[ incr ].depth  = 10;
			poweruplist[ incr ].object = _rb;
		}
		if ( LEVEL1_powerups[ placeinpowerups ] == _yb )
		{
			poweruplist[ incr ].x      = random(320);
			poweruplist[ incr ].y      = -9;
			poweruplist[ incr ].dx     = 0;
			poweruplist[ incr ].dy     = scrollspeed;
			poweruplist[ incr ].width  = 10;
			poweruplist[ incr ].depth  = 10;
			poweruplist[ incr ].object = _yb;
		}
		++powerupsinLEVEL;
	}
	if ( powerupsinLEVEL < 10 ) ++placeinpowerups;
}


void drawobjects(void)
{
	int incr,scrap;

	for ( incr = 1; incr <= MAXOBJECTS; ++incr )
	{
		if ( objectlist[incr].y <= -50 || objectlist[incr].y >= 220 ||
			  objectlist[incr].x <= -50 || objectlist[incr].x >= 370  )
		{
			objectlist[incr].x = -1;
			objectlist[incr].y = -1;
			--objectsinLEVEL;
		}
		if ( objectlist[incr].x != -1 )
		{
			if ( objectlist[incr].object == _waterballoon )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
					if ( objectlist[incr].dx >= 0 )
						put_image( WTRBLN, objectlist[incr].x,
												 objectlist[incr].y, 0 );
					else
						put_image_hflip( WTRBLN, objectlist[incr].x,
														 objectlist[incr].y, 0 );
				}
				objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}

			if ( objectlist[incr].object == _miniperry )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
				put_image( miniPERRY, objectlist[incr].x,
											 objectlist[incr].y, 0 );
				}
				if ( objectlist[incr].x > xloc )
					objectlist[incr].x -= objectlist[incr].dx;
				else if ( objectlist[incr].x < xloc )
					objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}

			if ( objectlist[incr].object == _bomber )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
				put_image( bomber, objectlist[incr].x,
										 objectlist[incr].y, 0 );
				}
				if ( objectlist[incr].x > xloc )
					objectlist[incr].x -= objectlist[incr].dx;
				else if ( objectlist[incr].x < xloc )
					objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}
			if ( objectlist[incr].object == _tank )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
				put_image( tank,      objectlist[incr].x,
											 objectlist[incr].y, 0 );
				}
				objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}
			if ( objectlist[incr].object == _boat )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
				put_image( tank,      objectlist[incr].x,
											 objectlist[incr].y, 0 );
				}
				objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}

			if ( objectlist[incr].object == _enemybullet )
			{
				if ( objectlist[ incr ].status == 4 )
				{
					put_image( blowup1, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 3 )
				{
					put_image( blowup2, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 2 )
				{
					put_image( blowup3, objectlist[incr].x,
												objectlist[incr].y, 0 );
					--objectlist[ incr ].status;
				}
				else if ( objectlist[ incr ].status == 1 )
				{
					objectlist[ incr ].x = -1;
					objectlist[ incr ].y = -1;
					--objectlist[ incr ].status;
				}
				else
				{
				put_image( enemybullet, objectlist[incr].x,
												objectlist[incr].y, 0 );
				}
				objectlist[incr].x += objectlist[incr].dx;
				objectlist[incr].y += objectlist[incr].dy;
			}
		}
	}

	if ( LEVEL1[ placeinLEVEL ] != 0 && objectsinLEVEL < MAXOBJECTS )
	{
		incr = 1;
		while (objectlist[ incr ].x != -1 && incr <= MAXOBJECTS) ++incr;
		if ( LEVEL1[ placeinLEVEL ] == _sideswipe )
		{
			scrap = random(2);
			if ( scrap == 0 )
				objectlist[ incr ].x      = -30;
			if ( scrap == 1 )
				objectlist[ incr ].x      = 350;
			if ( scrap == 0 )
				objectlist[ incr ].dx     = 7+random(5);
			if ( scrap == 1 )
				objectlist[ incr ].dx     = -7-random(5);
			objectlist[ incr ].y      = random(170);
			objectlist[ incr ].dy     = scrollspeed;
			objectlist[ incr ].width  = 30;
			objectlist[ incr ].depth  = 30;
			objectlist[ incr ].object = _waterballoon; //tell is to use WTRBALON
			objectlist[ incr ].status = 0;
		}
		if ( LEVEL1[ placeinLEVEL ] == _waterballoon )
		{
			objectlist[ incr ].x      = random(320);
			objectlist[ incr ].y      = -49;
			objectlist[ incr ].dx     = 0;
			objectlist[ incr ].dy     = (random(2)+1) + scrollspeed;
			objectlist[ incr ].width  = 25;
			objectlist[ incr ].depth  = 25;
			objectlist[ incr ].object = _waterballoon;
			objectlist[ incr ].status = 0;
		}
		if ( LEVEL1[ placeinLEVEL ] == _miniperry )
		{
			objectlist[ incr ].x      = random(320);
			objectlist[ incr ].y      = -30;
			objectlist[ incr ].dx     = 1;
			objectlist[ incr ].dy     = (random(2)+3) + scrollspeed +curLEVEL;
			objectlist[ incr ].width  = 25;
			objectlist[ incr ].depth  = 25;
			objectlist[ incr ].object = _miniperry;
			objectlist[ incr ].status = 0;
		}
		if ( LEVEL1[ placeinLEVEL ] == _bomber )
		{
			objectlist[ incr ].x      = random(320);
			objectlist[ incr ].y      = -30;
			objectlist[ incr ].dx     = curLEVEL+2;
			objectlist[ incr ].dy     = (random(2)+4) + scrollspeed+curLEVEL;
			objectlist[ incr ].width  = 30;
			objectlist[ incr ].depth  = 30;
			objectlist[ incr ].object = _bomber;
			objectlist[ incr ].status = 0;      //not blowing up
		}
		if ( LEVEL1[ placeinLEVEL ] == _tank )
		{
			objectlist[ incr ].x      = 110 + random(90);
			objectlist[ incr ].y      = -30;
			objectlist[ incr ].dx     = 0;
			objectlist[ incr ].dy     = scrollspeed+random(3);
			objectlist[ incr ].width  = 30;
			objectlist[ incr ].depth  = 30;
			objectlist[ incr ].object = _tank;
			objectlist[ incr ].status = 0;      //not blowing up
		}
		if ( LEVEL1[ placeinLEVEL ] == _boat )
		{
			objectlist[ incr ].x      = random(320);
			objectlist[ incr ].y      = -30;
			objectlist[ incr ].dx     = 0;
			objectlist[ incr ].dy     = scrollspeed+random(3);
			objectlist[ incr ].width  = 30;
			objectlist[ incr ].depth  = 30;
			objectlist[ incr ].object = _boat;
			objectlist[ incr ].status = 0;      //not blowing up
		}
		++objectsinLEVEL;
	}
	if ( objectsinLEVEL < 10 || scrollspeed > 7) ++placeinLEVEL;
	if ( placeinLEVEL >= levellength ) gotonextLEVEL();
}

void shootenemybullet( void )
{
	int incr = 1, enemywhoshot=1;

	/* find empty spot */
	while ( incr <= MAXOBJECTS && objectlist[ incr ].x != -1 ) ++incr;

	if ( incr = 1 )
	{
		++enemywhoshot;
		while ( enemywhoshot <= MAXOBJECTS && objectlist[ enemywhoshot ].x == -1 ) ++enemywhoshot;
	}

	if ( incr < MAXOBJECTS && enemywhoshot < MAXOBJECTS )
	{
		objectlist[ incr ].x      = objectlist[ enemywhoshot ].x+1;
		objectlist[ incr ].y      = objectlist[ enemywhoshot ].y+1;

		if ( xloc > objectlist[ incr ].x )
			objectlist[ incr ].dx     = (leveldifficulty*2);
		else if ( xloc < objectlist[ incr ].x )
			objectlist[ incr ].dx     = (-leveldifficulty*2);
		else
			objectlist[ incr ].dx     = 1;

		if ( yloc > objectlist[ incr ].y )
			objectlist[ incr ].dy     = (leveldifficulty*2);
		else if ( yloc < objectlist[ incr ].y )
			objectlist[ incr ].dy     = (-leveldifficulty*2);
		else
			objectlist[ incr ].dy     = 1;

		objectlist[ incr ].width  = 5;
		objectlist[ incr ].depth  = 5;
		objectlist[ incr ].object = _enemybullet;
		objectlist[ incr ].status = 0;      //not blowing up
		++objectsinLEVEL;
	}
}

void makelevels(void)
{
	long int incr;

	memset( LEVEL1, 0, 20000 );
	memset( objectlist, -1, (sizeof(OBJECT)*11) );

	memset( LEVEL1_powerups, 0, 20000 );
	memset( poweruplist, -1, (sizeof(OBJECT)*11) );

	if ( curLEVEL == 1 )
	{
		for( incr = 0; incr <= 20000; incr += (6-leveldifficulty)*20 )
		{
			LEVEL1[ incr+5 ]  = _miniperry;
			LEVEL1[ incr+4 ]  = _miniperry;
			LEVEL1[ incr+3 ]  = _miniperry;
			LEVEL1[ incr+2 ]  = _miniperry;
			LEVEL1[ incr+1 ]  = _miniperry;
			LEVEL1[ incr+20 ] = _miniperry;
			LEVEL1[ incr+19 ] = _bomber;
			LEVEL1[ incr+18 ] = _bomber;
			LEVEL1[ incr+17 ] = _bomber;
			LEVEL1[ incr+16 ] = _bomber;
			LEVEL1[ incr+6 ]  = _waterballoon;
			LEVEL1[ incr+7 ]  = _waterballoon;
			LEVEL1[ incr+8 ]  = _waterballoon;
			LEVEL1[ incr+9 ]  = _waterballoon;
			LEVEL1[ incr+10]  = _waterballoon;
		}
	}
	if ( curLEVEL == 2 )
	{
		for( incr = 0; incr <= 20000; incr += (6-leveldifficulty)*20 )
		{
			LEVEL1[ incr+5 ]  = _miniperry;
			LEVEL1[ incr+4 ]  = _miniperry;
			LEVEL1[ incr+3 ]  = _miniperry;
			LEVEL1[ incr+2 ]  = _miniperry;
			LEVEL1[ incr+1 ]  = _miniperry;
			LEVEL1[ incr+20 ] = _bomber;
			LEVEL1[ incr+19 ] = _bomber;
			LEVEL1[ incr+18 ] = _bomber;
			LEVEL1[ incr+17 ] = _bomber;
			LEVEL1[ incr+16 ] = _bomber;
			LEVEL1[ incr+6 ]  = _sideswipe;
			LEVEL1[ incr+7 ]  = _sideswipe;
			LEVEL1[ incr+8 ]  = _sideswipe;
			LEVEL1[ incr+9 ]  = _sideswipe;
			LEVEL1[ incr+10]  = _sideswipe;
		}
	}
	if ( curLEVEL == 3 )
	{
		for( incr = 0; incr <= 20000; incr += (6-leveldifficulty)*20 )
		{
			LEVEL1[ incr+5 ]  = _miniperry;
			LEVEL1[ incr+4 ]  = _miniperry;
			LEVEL1[ incr+3 ]  = _miniperry;
			LEVEL1[ incr+2 ]  = _miniperry;
			LEVEL1[ incr+1 ]  = _miniperry;
			LEVEL1[ incr+20 ] = _bomber;
			LEVEL1[ incr+19 ] = _bomber;
			LEVEL1[ incr+18 ] = _bomber;
			LEVEL1[ incr+17 ] = _bomber;
			LEVEL1[ incr+16 ] = _bomber;
			LEVEL1[ incr+11 ] = _tank;
			LEVEL1[ incr+12 ] = _tank;
			LEVEL1[ incr+13 ] = _tank;
			LEVEL1[ incr+14 ] = _tank;
			LEVEL1[ incr+15 ] = _tank;
			LEVEL1[ incr+6 ]  = _sideswipe;
			LEVEL1[ incr+7 ]  = _sideswipe;
			LEVEL1[ incr+8 ]  = _sideswipe;
			LEVEL1[ incr+9 ]  = _sideswipe;
			LEVEL1[ incr+10]  = _sideswipe;
		}
	}
	if ( curLEVEL == 4 )
	{
		for( incr = 0; incr <= 20000; incr += (6-leveldifficulty)*20 )
		{
			LEVEL1[ incr+5 ]  = _miniperry;
			LEVEL1[ incr+4 ]  = _miniperry;
			LEVEL1[ incr+3 ]  = _miniperry;
			LEVEL1[ incr+2 ]  = _miniperry;
			LEVEL1[ incr+1 ]  = _miniperry;
			LEVEL1[ incr+20 ] = _bomber;
			LEVEL1[ incr+19 ] = _bomber;
			LEVEL1[ incr+18 ] = _bomber;
			LEVEL1[ incr+17 ] = _bomber;
			LEVEL1[ incr+16 ] = _bomber;
			LEVEL1[ incr+11 ] = _boat;
			LEVEL1[ incr+12 ] = _boat;
			LEVEL1[ incr+13 ] = _boat;
			LEVEL1[ incr+14 ] = _boat;
			LEVEL1[ incr+15 ] = _boat;
			LEVEL1[ incr+6 ]  = _sideswipe;
			LEVEL1[ incr+7 ]  = _sideswipe;
			LEVEL1[ incr+8 ]  = _sideswipe;
			LEVEL1[ incr+9 ]  = _sideswipe;
			LEVEL1[ incr+10]  = _sideswipe;
		}
	}
	for( incr= 0; incr <= 20000; incr += (leveldifficulty*30) )
	{
		LEVEL1_powerups[ incr ]        = _energy;
		LEVEL1_powerups[ incr+1 ]      = _bb;
		LEVEL1_powerups[ incr+20 ]      = _rb;
		LEVEL1_powerups[ incr+3 ]      = _yb;
		LEVEL1_powerups[ incr +10]     = _energy;
		LEVEL1_powerups[ incr +2]      = _energy;
		LEVEL1_powerups[ incr +30]     = _speed;
	}
}

void cpalette( unsigned char color, char r, char g, char b )
{
	outp( 0x3c8, color );
	outp( 0x3c9, r     );
	outp( 0x3c9, g     );
	outp( 0x3c9, b     );
}

void put_image_vflip (char *pic, int ulx, int uly, char transparent )
{
	char width = pic[0];
	char depth = pic[1];

	int x, y, byte=2;

	for ( y = (uly+depth)-1; y >= uly; --y)
		for ( x = ulx; x < (ulx+width); ++x)
		{
			if ( x >= 0 && x <= 319 && y >= 0 && y <= 199 )
				if ( pic[byte] != transparent )
					video[ (x+(320*y)) ] = pic[byte];
			++byte;
		}
}

void put_image_hflip (char *pic, int ulx, int uly, char transparent )
{
	char width = pic[0];
	char depth = pic[1];

	int x, y, byte=2;

	for ( y = uly; y < (uly+depth); ++y)
		for ( x = (ulx+width)-1; x >= ulx; --x)
		{
			if ( x >= 0 && x <= 319 && y >= 0 && y <= 199 )
				if ( pic[byte] != transparent )
					video[ (x+(320*y)) ] = pic[byte];
			++byte;
		}
}


void put_image( char *pic, int ulx, int uly, char transparent )
{
	char width = pic[0];
	char depth = pic[1];

	int x, y, byte=2;

	for ( y = uly; y < (uly+depth); ++y)
		for ( x = ulx; x < (ulx+width); ++x)
		{
			if ( x >= 0 && x <= 319 && y >= 0 && y <= 199 )
				if ( pic[byte] != transparent )
					video[ (x+(320*y)) ] = pic[byte];
			++byte;
		}
}

void scrolly( char speed, char direction, char *buffer, char *what )
{
	char *temp;
	temp = (char *)malloc(64000);

	if ( direction == -1 ) //up
	{
		memcpy( what, &what[ (speed*320) ], (64000-(speed*320)) );
		memcpy( &what[ (64000-(speed*320)) ], &buffer[index], (speed*320) );
		index += (speed*320);
		if ( index >= 64000 ) index = 0;
	}
	if ( direction == 1 ) //down
	{
		if ( (index+(speed*320)) > 64000 ) index = (64000-(speed*320));
		memcpy( temp , what      , (64000-(speed*320)) );
		memcpy( &what[ (speed*320) ], temp , (64000-(speed*320)) );
		memcpy(  what, &buffer[index], (speed*320) );
		index -= (speed*320);
		if ( index < 0 ) index = (64000-(speed*320));
	}
	free(temp);
}

void flip(char *dest, char *source, char transparent, int bytes )
{

	int index;

	for ( index = 0; index <= bytes; ++index)
	{
		if ( source[index] != transparent ) dest[index] = source[index];
	}

}

void open_image(char *filename, char *pic )
{
	int size,x,c,count;
	long int n;
	long int i=0;
	long int   inc;
	FILE *fp;
	c=0;

	if((fp=fopen(filename,"rb")) != NULL){
			/* read in the header */
		  if(fread((char *) &header,1,sizeof(PCXHEAD),fp)
		 == sizeof(PCXHEAD)){
		  /*check to make sure it's a picture */
			if(header.manufacturer==0x0a &&
				header.version ==5){

			if(!fseek(fp,-769L,SEEK_END)){
				if(fgetc(fp) == 0x0c &&
				 fread(palette,1,768,fp) == 768) {
					fseek(fp,128L,SEEK_SET);
					/*allocate a big buffer */
				width = (header.xmax -
				header.xmin) +1;
				depth = (header.ymax-
				header.ymin)+1;
				bytes=header.bytes_per_line;
					} else
			puts("error reading pallete");
		}else puts ("error seeking to pallete");
	}else printf("not a 256 color pcx file.\n");
	  }else printf("error reading %s.\n",filename);
/*  fclose(fp); */
 } else printf ("Error opening %s.\n",filename);

/***********************************************************************/
	pic[0] = width;  //store info of image
	pic[1] = depth;

	for (i = 2; i < ((depth*width)+2); ++i){
		c=fgetc(fp) & 0xff;  /* if it's a run of bytes field */

		if((c & 0xc0) == 0xc0) { /* and off the high bits */
			x=c & 0x3f;
			/* run the byte */
			c=fgetc(fp);
			while(x--)
			{
				pic[i++] = c;
			}
			i--;
			}
			/*else just store it */
			else
			{
				pic[i] = c;
			}
		}
	 fclose(fp);
}

FILE  *open_pic(char *filename)
{

	FILE *fp;

	if((fp=fopen(filename,"rb")) != NULL){
			/* read in the header */
		  if(fread((char *) &header,1,sizeof(PCXHEAD),fp)
		 == sizeof(PCXHEAD)){
		  /*check to make sure it's a picture */
			if(header.manufacturer==0x0a &&
				header.version ==5){

			if(!fseek(fp,-769L,SEEK_END)){
				if(fgetc(fp) == 0x0c &&
				 fread(palette,1,768,fp) == 768) {
					fseek(fp,128L,SEEK_SET);
					/*allocate a big buffer */
				width = (header.xmax -
				header.xmin) +1;
				depth = (header.ymax-
				header.ymin)+1;
				bytes=header.bytes_per_line;
					} else
			puts("error reading pallete");
		}else puts ("error seeking to pallete");
	}else printf("not a 256 color pcx file.\n");
	  }else printf("error reading %s.\n",filename);
/*  fclose(fp); */
 } else printf ("Error opening %s.\n",filename);

return fp;
}


void  ReadBuffer_A(FILE *fp, char *buffer)
{
	int size,x,c,count;
	long int n;
	long int i=0;
	long int   inc;
	c=0;

	for (i=0;i<64000;++i){
		c=fgetc(fp) & 0xff;  /* if it's a run of bytes field */

		if((c & 0xc0) == 0xc0) { /* and off the high bits */
			x=c & 0x3f;
			/* run the byte */
			c=fgetc(fp);
			while(x--)
			{
				if (c == 0 )
					c = video[i];
				buffer[i++]=c;
			}
			i--;
			}
			/*else just store it */
			else
			{
				if (c == 0 )
					c = video[i];
				buffer[i]=c;
			}
		}

}

void  ReadBGBuffer(FILE *fp, char *buffer)
{
	int size,x,c,count;
	long int n;
	long int i=0;
	long int   inc;
	c=0;

	for (i=0;i<64000;++i){
		c=fgetc(fp) & 0xff;  /* if it's a run of bytes field */

		if((c & 0xc0) == 0xc0) { /* and off the high bits */
			x=c & 0x3f;
			/* run the byte */
			c=fgetc(fp);
			while(x--) buffer[i++]=c;
			i--;
			}
			/*else just store it */
			else buffer[i]=c;
		}

}

void  deinit(void)   /*turn off graphics card */
{
	  asm{
	mov ax,3h
	int 10h
	};
}

void setVGApalette(char *p)   /*set the VGA palette to RGB buffer p */
{
	union REGS r;
	struct SREGS sr;
	int i;

	/* convert eight bits to six bits */
	for (i=0;i<768;i++) p[i]=p[i] >> 2;

	r.x.ax=0x1012;
	r.x.bx=0;
	r.x.cx=256;
	r.x.dx=FP_OFF(p);
	sr.es=FP_SEG(p);
	int86x(0x10,&r,&r,&sr);
}

void cleanup ( void )
{

		free(buffer );
		free(SEPlane);

		free(SEPlane_HIT1);
		free(SEPlane_HIT2);

		free(SEPlane_BUP1);
		free(SEPlane_BUP2);
		free(SEPlane_BUP3);

		free(WTRBLN );
		free(miniPERRY);
		free(bomber);
		free(scrollingscreen);
		free(videoscreen);

		free(rbullet);
		free(ybullet);
		free(bbullet);

		free(energyPOWER);
		free(speedPOWER);
		free(rbPOWER);
		free(ybPOWER);
		free(bbPOWER);

		free(blowup1);
		free(blowup2);
		free(blowup3);

		free(youwin_title);
		free(gameover_title);

		free(LEVEL1_powerups);
		free(LEVEL1);

		deinit();

		restore();
}

void printSTR( int x, int y, char *str   , char color)
{
	int numofLets, px;

	for ( numofLets = 0; str[numofLets] != '\0'; ++numofLets );

	for ( px=(12*numofLets)+x; numofLets >= 0; --numofLets, px -= 12 )
	{
		if ( str[ numofLets] == 'a' || str[ numofLets] == 'A' )
			put_letter( a_A, px, y, 0, color );

		if ( str[ numofLets] == 'b' || str[ numofLets] == 'B' )
			put_letter( b_B, px, y, 0, color );

		if ( str[ numofLets] == 'c' || str[ numofLets] == 'C' )
			put_letter( c_C, px, y, 0, color );

		if ( str[ numofLets] == 'd' || str[ numofLets] == 'D' )
			put_letter( d_D, px, y, 0, color );

		if ( str[ numofLets] == 'e' || str[ numofLets] == 'E' )
			put_letter( e_E, px, y, 0, color );

		if ( str[ numofLets] == 'f' || str[ numofLets] == 'F' )
			put_letter( f_F, px, y, 0, color );

		if ( str[ numofLets] == 'g' || str[ numofLets] == 'G' )
			put_letter( g_G, px, y, 0, color );

		if ( str[ numofLets] == 'h' || str[ numofLets] == 'H' )
			put_letter( h_H, px, y, 0, color );

		if ( str[ numofLets] == 'i' || str[ numofLets] == 'I' )
			put_letter( i_I, px, y, 0, color );

		if ( str[ numofLets] == 'j' || str[ numofLets] == 'J' )
			put_letter( j_J, px, y, 0, color );

		if ( str[ numofLets] == 'k' || str[ numofLets] == 'K' )
			put_letter( k_K, px, y, 0, color );

		if ( str[ numofLets] == 'l' || str[ numofLets] == 'L' )
			put_letter( l_L, px, y, 0, color );

		if ( str[ numofLets] == 'm' || str[ numofLets] == 'M' )
			put_letter( m_M, px, y, 0, color );

		if ( str[ numofLets] == 'n' || str[ numofLets] == 'N' )
			put_letter( n_N, px, y, 0, color );

		if ( str[ numofLets] == 'o' || str[ numofLets] == 'O' )
			put_letter( o_O, px, y, 0, color );

		if ( str[ numofLets] == 'p' || str[ numofLets] == 'P' )
			put_letter( p_P, px, y, 0, color );

		if ( str[ numofLets] == 'q' || str[ numofLets] == 'Q' )
			put_letter( q_Q, px, y, 0, color );

		if ( str[ numofLets] == 'r' || str[ numofLets] == 'R' )
			put_letter( r_R, px, y, 0, color );

		if ( str[ numofLets] == 's' || str[ numofLets] == 'S' )
			put_letter( s_S, px, y, 0, color );

		if ( str[ numofLets] == 't' || str[ numofLets] == 'T' )
			put_letter( t_T, px, y, 0, color );

		if ( str[ numofLets] == 'u' || str[ numofLets] == 'U' )
			put_letter( u_U, px, y, 0, color );

		if ( str[ numofLets] == 'v' || str[ numofLets] == 'V' )
			put_letter( v_V, px, y, 0, color );

		if ( str[ numofLets] == 'w' || str[ numofLets] == 'W' )
			put_letter( w_W, px, y, 0, color );

		if ( str[ numofLets] == 'x' || str[ numofLets] == 'X' )
			put_letter( x_X, px, y, 0, color );

		if ( str[ numofLets] == 'y' || str[ numofLets] == 'Y' )
			put_letter( y_Y, px, y, 0, color );

		if ( str[ numofLets] == 'z' || str[ numofLets] == 'Z' )
			put_letter( z_Z, px, y, 0, color );

		if ( str[ numofLets] == '-' )
			put_letter( dash, px, y, 0, color );
	}
}


void printNUM( int x, int y, long int num, char color)
{
	long int scrap = num;
	int index, numofNums=0, holder_i = 2, px;
	double holder_d = 4.0;

	while ( holder_d >= 1.0 )
	{
		holder_d = scrap / 10.0;
		scrap = holder_d;
		++numofNums;
	}

	scrap = num;

	for ( px=(12*numofNums)+x; numofNums > 0; --numofNums, px -= 12 )
	{
		holder_i = scrap % 10;
		scrap = scrap / 10;

		if ( holder_i == 1 )
			put_letter( one, px, y, 0, color );
		if ( holder_i == 2 )
			put_letter( two, px, y, 0, color );
		if ( holder_i == 3 )
			put_letter( three, px, y, 0, color );
		if ( holder_i == 4 )
			put_letter( four, px, y, 0, color );
		if ( holder_i == 5 )
			put_letter( five, px, y, 0, color );
		if ( holder_i == 6 )
			put_letter( six, px, y, 0, color );
		if ( holder_i == 7 )
			put_letter( seven, px, y, 0, color );
		if ( holder_i == 8 )
			put_letter( eight, px, y, 0, color );
		if ( holder_i == 9 )
			put_letter( nine, px, y, 0, color );
		if ( holder_i == 0 )
			put_letter( zero, px, y, 0, color );
	}
}

void initLEVEL ( void )
{
	levellength = ( (leveldifficulty) * 400 );

	noof_bbs = (6-leveldifficulty)*20*(6-leveldifficulty);
	noof_rbs = (6-leveldifficulty)*10*(6-leveldifficulty);
	noof_ybs = (6-leveldifficulty)*30*(6-leveldifficulty);

	memset (shots, -1, (sizeof(BULLET)*10) );

	index           = (64000-(scrollspeed*320));  //place in buffer (for scrolling)
	placeinLEVEL    = 0;                 //place in level
	objectsinLEVEL  = 0;                 //# of objects already in level
	bulletsinLEVEL  = 0;                 //# of bullets in level at start
	placeinpowerups = 0;
	powerupsinLEVEL = 0;

	/* open sprites */

	if ( curLEVEL == 1 )
	{
		input    = open_pic  ( SCENE );   //open pictures
		open_image(WTRBALLOON, WTRBLN    );
		open_image(MINIPERRY , miniPERRY );
		open_image(BOMBER    , bomber    );
	}

	if ( curLEVEL == 2 )
	{
		input    = open_pic  ( SCENE2 );   //open pictures
		open_image(SIDESWIPER, WTRBLN    );
		open_image(MINIPERRY , miniPERRY );
		open_image(BOMBER    , bomber    );
	}
	if ( curLEVEL == 3 )
	{
		input    = open_pic  ( SCENE3 );   //open pictures
		open_image(TANK      , tank      );
		open_image(SIDESWIPER, WTRBLN    );
		open_image(MINIPERRY , miniPERRY );
		open_image(BOMBER    , bomber    );
	}
	if ( curLEVEL == 4 )
	{
		input    = open_pic  ( SCENE4 );   //open pictures
		open_image(BOAT      , tank      );
		open_image(SIDESWIPER, WTRBLN    );
		open_image(MINIPERRY , miniPERRY );
		open_image(BOMBER    , bomber    );
	}
	startingover = 0;
}

void put_letter (char *pic, int ulx, int uly, char transparent, char color )
{
	char width = pic[0];
	char depth = pic[1];

	int x, y, byte=2;

	for ( y = uly; y < (uly+depth); ++y)
		for ( x = ulx; x < (ulx+width); ++x)
		{
			if ( x >= 0 && x <= 319 && y >= 0 && y <= 199 )
				if ( pic[byte] != transparent )
					video[ (x+(320*y)) ] = color;
			++byte;
		}
}
long sqrt_FAST(long v)
{
	 int		i;
	 unsigned	long result,tmp;
    unsigned	long low,high;

if (v <= 1L) return((unsigned)v);

low = v;
high = 0L;
result = 0;

for (i = 0; i < 16; i++)
	 {
	 result += result;
	 high = (high << 2) | ((low >>30) & 0x3);
	 low <<= 2;

	 tmp = result + result + 1;
    if (high >= tmp)
	{
	result++;
	high -= tmp;
	}
	 }

if (v - (result * result) >= (result - 1))
	 result++;

return(result);
}

void printHISCORES( void )
{
	printSTR( 40, 35, " T O P    F I V E  ", 51 );
	printSTR( 30, 50, "ANTI-KEISH FIGHTERS", 50 );

	printSTR( 70 , 70, scorelist.num[1].initials, 166 );
	printNUM( 150, 70, scorelist.num[1].score   , 1 );

	printSTR( 70 , 85, scorelist.num[2].initials, 167 );
	printNUM( 150, 85, scorelist.num[2].score   , 3 );

	printSTR( 70 , 100, scorelist.num[3].initials, 168 );
	printNUM( 150, 100, scorelist.num[3].score   , 5 );

	printSTR( 70 , 115, scorelist.num[4].initials, 169 );
	printNUM( 150, 115, scorelist.num[4].score   , 7 );

	printSTR( 70 , 130, scorelist.num[5].initials, 170 );
	printNUM( 150, 130, scorelist.num[5].score   , 9 );
}

void openHISCORES( void )
{
	int handle;

	handle = open ( SCORES_FILE, O_RDONLY );
	/*
	FILE *fp;

	if((fp=fopen(filename,"rb")) != NULL){
		  if(fread((char *) &header,1,sizeof(PCXHEAD),fp)
		 == sizeof(PCXHEAD)){
	*/
	if ( handle == -1 )
	{
		/* create default hiscores */
		scorelist.num[1].score = 5000;
		scorelist.num[1].initials[0] = 'J';
		scorelist.num[1].initials[1] = 'P';
		scorelist.num[1].initials[2] = '\0';

		scorelist.num[2].score = 4000;
		scorelist.num[2].initials[0] = 'S';
		scorelist.num[2].initials[1] = 'e';
		scorelist.num[2].initials[2] = '\0';


		scorelist.num[3].score = 3000;
		scorelist.num[3].initials[0] = 'B';
		scorelist.num[3].initials[1] = 'd';
		scorelist.num[3].initials[2] = 'k';
		scorelist.num[3].initials[3] = '\0';


		scorelist.num[4].score = 2000;
		scorelist.num[4].initials[0] = 'M';
		scorelist.num[4].initials[1] = 'd';
		scorelist.num[4].initials[2] = 's';
		scorelist.num[4].initials[3] = '\0';

		scorelist.num[5].score = 1000;
		scorelist.num[5].initials[0] = 'G';
		scorelist.num[5].initials[1] = 's';
		scorelist.num[5].initials[2] = 's';
		scorelist.num[5].initials[3] = '\0';
	}
	else
	{
		read( handle, &scorelist, sizeof( scorelist ) +50);
		//close( handle );
	}
}
void saveHISCORES( void )
{
	int handle;

	remove ( SCORES_FILE );

	handle = creatnew ( SCORES_FILE, 0 );
	if ( handle == -1 )
	{
		remove ( SCORES_FILE );
		/* don't save it */
	}
	else
	{
		write( handle, &scorelist, sizeof( scorelist )+50 );
		_close( handle );
	}
}

void checkHISCORES( void )
{
	int beatscoreNUM, index;
	char key, timesthrough =0;
	char send[1], init[3];

	init[0] = '-';
	init[1] = '-';
	init[2] = '-';
	init[3] = '\0';

	for ( beatscoreNUM = 1; beatscoreNUM <= 6; ++beatscoreNUM )
	{
		if ( beatscoreNUM < 6 ) if ( score > scorelist.num[beatscoreNUM].score ) break;
	}

	if ( beatscoreNUM < 6 ) //beat one of the scores
	{
		while ( timesthrough < 3 )
		{
			while ( !kbhit() )
			{
				scrolly  ( scrollspeed, 1 , buffer, scrollingscreen );
				memcpy   ( video, scrollingscreen, 64000);
				printSTR( 40, 35, "ENTER YOUR INITIALS", 51 );
				printSTR( 125, 70, init, 167 );
				memcpy   (videoscreen, video , 64000  );
			}

			key = getch();
			if (  ( key <= 'z' && key >= 'a') || ( key <= 'Z' && key >= 'A') || key == ' ')
			{
				send[0] = key;
				send[1] = '\0';
				init[ timesthrough ] = key;
				++timesthrough;
			}
		}

		for ( index = 4; index >= beatscoreNUM; --index)
		{
			scorelist.num[index+1] = scorelist.num[index];
		}
		scorelist.num[ beatscoreNUM ].score = score;
		scorelist.num[ beatscoreNUM ].initials[0] = init[0];
		scorelist.num[ beatscoreNUM ].initials[1] = init[1];
		scorelist.num[ beatscoreNUM ].initials[2] = init[2];
		scorelist.num[ beatscoreNUM ].initials[3] = init[3];
	}
}

void fade_to_black( void )
{
	int index, notfinished = 1;

	char temp_pal[ 768 ];

	memcpy( temp_pal, palette, sizeof( char )*769 );

	while ( notfinished )
	{
		notfinished = 0;
		for ( index = 1; index <= 768; ++index )
		{
			if ( temp_pal[ index ] > 0 )
				--temp_pal[ index ];
			else if ( temp_pal[ index ] < 0 )
				++temp_pal[ index ];
			else
				notfinished = 1;
		}
		if ( notfinished ) setVGApalette( temp_pal );
	}
}

void fade_to_palette( void )
{
	int index, notfinished = 1;

	char temp_pal[ 768 ];

	memset( temp_pal, 0, sizeof( char )*769 );

	while ( notfinished )
	{
		notfinished = 0;
		for ( index = 1; index <= 768; ++index )
		{
			if ( temp_pal[ index ] > palette[ index ] )
				--temp_pal[ index ];
			else if ( temp_pal[ index ] < palette[ index ] )
				++temp_pal[ index ];
			else
				notfinished = 1;
		}
		if ( notfinished ) setVGApalette( temp_pal );
	}
}