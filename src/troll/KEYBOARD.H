/*
**      KEYBOARD.H
**
**      Defined constants and prototypes for KEYBOARD.C.  See KEYBOARD.C
**      for documentation of functions.
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <dos.h>
#include <conio.h>

/* defined constants for keyboard ports */

#define KEYBOARD_INT	0x09
#define KEY_BUFFER	0X60
#define KEY_CONTROL	0X61
#define INT_CONTROL	0X20

#define WaitForKeyPressed while(!keypressed) delay(1)
#define WaitForKeyRelease while(keypressed) delay(1)
#define WaitForKeyP(x) while( keyboard[ x ] == 0 ) delay(1)
#define WaitForKeyR(x) while( keyboard[ x ] == 1 ) delay(1)
#define WaitForKeyPR      //WaitForKeyPressed;WaitForKeyRelease

/* defined constants for indexes to the keyboard array.
** i.e. keyboard[INDEX_1]: if 1 then 1 is pressed, 0 if it is up
*/

#define INDEX_ESC	1
#define INDEX_1		2
#define INDEX_2		3
#define INDEX_3		4
#define INDEX_4		5
#define INDEX_5		6
#define INDEX_6		7
#define INDEX_7		8
#define INDEX_8		9
#define INDEX_9		10
#define INDEX_0		11
#define INDEX_MINUS	12
#define INDEX_EQUALS	13
#define INDEX_BACKSPACE	14
#define INDEX_TAB	15
#define INDEX_Q		16
#define INDEX_W		17
#define INDEX_E		18
#define INDEX_R		19
#define INDEX_T		20
#define INDEX_Y		21
#define INDEX_U		22
#define INDEX_I		23
#define INDEX_O		24
#define INDEX_P		25
#define INDEX_LEFT_BRACKET	26
#define INDEX_RIGHT_BRACKET	27
#define INDEX_ENTER	28
#define INDEX_CTRL	29
#define INDEX_A		30
#define INDEX_S		31
#define INDEX_D		32
#define INDEX_F		33
#define INDEX_G		34
#define INDEX_H		35
#define INDEX_J		36
#define INDEX_K		37
#define INDEX_L		38
#define INDEX_SEMICOLON	39
#define INDEX_APOSTROPHE	40
#define INDEX_LEFT_SHIFT	42
#define INDEX_BACK_SLASH	43
#define INDEX_Z		44
#define INDEX_X		45
#define INDEX_C		46
#define INDEX_V		47
#define INDEX_B		48
#define INDEX_N		49
#define INDEX_M		50
#define INDEX_COMMA	51
#define INDEX_PERIOD	52
#define INDEX_FORWARD_SLASH	53
#define INDEX_RIGHT_SHIFT	54
#define INDEX_PRINT_SCREEN		55
#define INDEX_ALT	56
#define INDEX_SPACE	57
#define INDEX_CAPS_LOCK	58
#define INDEX_F1		59
#define INDEX_F2		60
#define INDEX_F3		61
#define INDEX_F4		62
#define INDEX_F5		63
#define INDEX_F6		64
#define INDEX_F7		65
#define INDEX_F8		66
#define INDEX_F9		67
#define INDEX_F10	68
#define INDEX_NUM_LOCK	69
#define INDEX_SCROLL_LOCK	70
#define INDEX_HOME	71
#define INDEX_UP		72
#define INDEX_PGUP	73
#define INDEX_NUM_MINUS	74
#define INDEX_LEFT	75
#define INDEX_CENTER	76
#define INDEX_RIGHT	77
#define INDEX_NUM_PLUS	78
#define INDEX_END	79
#define INDEX_DOWN	80
#define INDEX_PGDOWN	81
#define INDEX_INS	82
#define INDEX_DEL	83

extern char keyboard[100];
extern int cur_key;
extern void (interrupt far *Old_Isr)(void);

void interrupt far New_Key_Int(void);
void InitKeyboard(void);
void StartKeyboardInterrupt(void);
void HaltKeyboardInterrupt(void);
                                
#endif
