/*
**      KEYBOARD.C
**
**      All keyboard input handling routines are provided in this file.
**      In order to use the Keyboard handler, call StartKeyboardInterrupt().
**      Any time a key x is pressed, keyboard[INDEX_x] will be changed to
**      1.  The handler runs transparently in the background as an interrupt.
**      When finished, call HaltKeyboardInterrupt() to restore the old ISR.
*/

#include "keyboard.h"

/* array keeps track of keys pressed */

char keyboard[100];
char keypressed; //1 if key is pressed, 0 otherwise

/* current key pressed */

int cur_key;

/* original keyboard handler */

void (interrupt far *Old_Isr)(void);

/*      InitKeyboard()
**      PRECONDITION : none
**      POSTCONDITION: the keyboard array is initialized to all zero's.
*/

void InitKeyboard(void)
{
	int cv;

	for(cv = 0; cv < 100; cv++)
		keyboard[cv] = 0;

	keypressed = 0;
}

/*
**      New_Key_Int()
**      PRECONDITION : The old keyboard interrupt should be saved before
**                     installing a new one.
**      POSTCONDITION: This ISR should  be installed using the _dos_setvect()
**                     function.  Anytime a key is pressed or released, this
**                     ISR gets called.  It reads the key from the keyboard
**                     port and interprets which key was pressed/released.
**                     keyboard[INDEX_key] is set to 1 or zero depending on
**                     the event.
*/

void interrupt far New_Key_Int(void)
{
	union REGS regs;
	regs.h.al = inp(KEY_BUFFER);
	regs.h.ah = 0;
	cur_key = regs.h.al;
	regs.h.al = inp(KEY_CONTROL);
	regs.h.al = regs.h.al | 0x82;
	regs.h.al = outp(KEY_CONTROL,regs.h.al);
	regs.h.al = regs.h.al & 0x7F;
	regs.h.al = outp(KEY_CONTROL,regs.h.al);
	regs.h.al =  0X20;
	regs.h.al = outp(INT_CONTROL,regs.h.al);

	if(cur_key > 128) {
		keyboard[cur_key-128] = 0;
		keypressed = 0;
	}
	else if (cur_key <= 128) {
		keyboard[cur_key] = 1;
		keypressed = 1;
	}
}

/*      StartKeyboardInterrupt()
**      PRECONDITION : none
**      POSTCONDITION: the New_Key_Int ISR replaces the current keyboard
**                     handler.  The old handler is saved to Old_Isr.
*/

void StartKeyboardInterrupt(void)
{
	InitKeyboard();
	Old_Isr = _dos_getvect(KEYBOARD_INT);
	_dos_setvect(KEYBOARD_INT,New_Key_Int);
}

/*      HaltKeyboardInterrupt()
**      PRECONDITION : StartKeyboardInterrupt() has already been called
**      POSTCONDITION: Restores original keyboard handler
*/

void HaltKeyboardInterrupt(void)
{
	_dos_setvect(KEYBOARD_INT,Old_Isr);
}

