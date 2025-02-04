/*
**      TEXT.H
**
**      Prototypes for Text functions, see TEXT.C for documentation.
*/

#ifndef TEXT_H
#define TEXT_H

extern image_type bios_char[255];

void LoadFont(void);
void DispChar(char c, short x, short y, unsigned char color, page_type page);
void Print(page_type page, short x, short y, char color, char *format, ...);

#endif
