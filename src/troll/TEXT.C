/*
**      TEXT.C
**
**      All routines for using BIOS fonts are provided in this file.
*/


#include "graphics.h"
#include "error.h"

char char_set[255][64];

/* stores the BIOS characters as sprites for compatibility with current
** display routines.
*/

image_type bios_char[255];

/*      LoadFont()
**      PRECONDITION : none
**      POSTCONDITION: the BIOS fonts are loaded as sprites into the
**                     bios_char array.
*/

void LoadFont(void)
{
	unsigned char *bios = (unsigned char *)0xFFA6E;
	long offset = 0, cv, i;
	char temp;

	for(cv = 0; cv < 256; cv++)
	{
		bios_char[cv].width = 8;
		bios_char[cv].height = 8;
                if((bios_char[cv].bitmap = (char *)malloc(sizeof(char) * 64)) == NULL)
                        Error("Out of memory for the bios font\n");
	}

	for(cv = 0; cv < 256; cv++)
	{
		for(i = 0; i < 8; i++)
		{
			temp = bios[offset + i];
			bios_char[cv].bitmap[i * 8 + 7] = temp & 0x01;
			bios_char[cv].bitmap[i * 8 + 6] = temp & 0x02;
			bios_char[cv].bitmap[i * 8 + 5] = temp & 0x04;
			bios_char[cv].bitmap[i * 8 + 4] = temp & 0x08;
			bios_char[cv].bitmap[i * 8 + 3] = temp & 0x10;
			bios_char[cv].bitmap[i * 8 + 2] = temp & 0x20;
			bios_char[cv].bitmap[i * 8 + 1] = temp & 0x40;
			bios_char[cv].bitmap[i * 8 + 0] = temp & 0x80;
		}
		offset += 8;
	}
}

/*      DispChar()
**      PRECONDITION : c is the character to display, x and y are the screen
**                     coordinates, color is the text color, and buffer is
**                     where the character will be displayed.
**      POSTCONDITION: The BIOS font for c is placed in buffer.
*/

void DispChar(char c, short x, short y, unsigned char color, page_type page)
{
	short cv;
        image_type temp;

	if( (temp.bitmap = (char *)malloc(sizeof(char) * 64)) == NULL)
		Error( "Not enough memory.\n" );
	temp.height = bios_char[c].height;
	temp.width = bios_char[c].width;
	memcpy(temp.bitmap, bios_char[c].bitmap, 64);
	
	for(cv = 0; cv < 64; cv++)
		if(temp.bitmap[cv])
			temp.bitmap[cv] = color;

        put_image(&temp, x, y, 0, page);

	free(temp.bitmap);
}

/*      Print()
**      PRECONDITION : buffer is where to display the string, color is
**                     the color to use, and format is the string to
**                     display (accepts format specifiers)
**      POSTCONDITION: by displaying each character one by one using
**                     DispChar(), the string is placed on the screen.
*/

void Print(page_type page, short x, short y, char color, char *format, ...)
{
        short temp_x =x, temp_y =y+50;
	short xclip = 180;
	va_list list;
        long cv = 0;

	static char formatBuffer[256];
	va_start(list, format);
	vsprintf(formatBuffer, format, list);
	while(formatBuffer[cv] != '\0')
	{		
                DispChar(formatBuffer[cv], x, y, color, page);
                if( y > temp_y ){
			xclip = 234;
		}
		if(x > xclip)
		{
                        x = temp_x;
			y += 10;
			if( formatBuffer[cv+1] == ' ' )
				++cv;
		}
		else
			x += 8;
		cv++;
	}
	
}
