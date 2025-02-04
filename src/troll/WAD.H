#ifndef WAD_H
#define WAD_H

#include <stdio.h>

typedef struct file_tag{
	char filename[14];
	int offset;    /* offset from beginwadptr */
	int size;
	int cur_index;
	char *buffer;
	struct file_tag *next;
} file_type;

int FileSize( FILE *fp );
int wad_fread( void *buffer, long size, long number, file_type *file);
int wad_fseek(file_type *fp, int offset, int position);
char wad_fgetc(file_type *fp);
int wad_feof(file_type *fp);

		char filename[14];
		int beginwadoffset;  /* beginning of files */
		FILE *wadptr;
		file_type *files;   /* list of files, their size and offset */
		int endoffset;
		int numfiles;

        WAD( char * );

        void Initialize( void );
        void Save(void);
        file_type *OpenFile( char * );
        void CloseFile( file_type * );
        void AddFile( char * );
        void RemoveFile( char * );

#endif
