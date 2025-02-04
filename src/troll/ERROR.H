/* error.h */
#ifndef ERROR_H

#define ERROR_H

#include <stdarg.h>

void Error(char *format, ...);


void Error(char *format, ...)
{
	va_list list;
	static char formatBuffer[256];
	va_start(list, format);
	vsprintf(formatBuffer, format, list);
	//deinit();
	printf("ERROR: %s\n",formatBuffer);
	exit(1);
}

#endif
