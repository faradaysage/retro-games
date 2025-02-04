#include "wad.h"
#include "error.h"
#include <stdio.h>
//#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int i;

WAD( char *wadname ){
        strcpy( filename, wadname );
        files = NULL;
        numfiles = 0;
        endoffset = 0;
}

void Initialize( void ){
	file_type *temp;
	file_type *begin;
	
	if( (wadptr = fopen( filename, "rb" ))  == NULL )
                Error( "Could not open %s", filename );
	
	if( fread( &numfiles, sizeof(int), 1, wadptr ) != 1 )
                Error("Not a valid WAD.");
	
	
	if( numfiles != 0 ){
                files = (file_type *)malloc( sizeof(file_type) );
		if( (fread( files->filename, 1, 14, wadptr )) == 14 )
			if( (fread( &(files->offset), sizeof(int), 1, wadptr )) == 1 )
				if( (fread( &(files->size), sizeof(int), 1, wadptr )) == 1 )
                                        ;//Error( "Bad WAD file." );
		files->next = NULL;
		}

	begin = files;

        for( i=1; i<numfiles; ++i){
                temp = (file_type *)malloc( sizeof(file_type) );;
		if( (fread( temp->filename, 1, 14, wadptr )) == 14 )
			if( (fread( &(temp->offset), sizeof(int), 1, wadptr )) == 1 )
				if( (fread( &(temp->size), sizeof(int), 1, wadptr )) == 1 )
                                        ;//Error( "Bad WAD file." );
		temp->next = NULL;
		files->next = temp;
		files = files->next;
	}
	beginwadoffset = ftell(wadptr);  /* save beginning of WAD (after numfiles) */
	
	fseek( wadptr, 0, SEEK_END );
        
	endoffset = ftell( wadptr ) - beginwadoffset;

	fseek(wadptr, beginwadoffset, SEEK_SET);

	files = begin;  /* move the pointer back to the beginning */
}

void CloseFile( file_type *fp ){
        free( fp->buffer);
        free( fp );
}

file_type *OpenFile( char *filename_look ){
        file_type *begin=files;   /* save beginning */
        char found_it=0;
        static file_type *temp;

                for(i = 0; filename_look[i] != '\0'; i++)
			filename_look[i] = toupper(filename_look[i]);

        temp = (file_type *)malloc( sizeof(file_type) );;
        fseek(wadptr, beginwadoffset, SEEK_SET);
        while( (files != NULL) && (found_it == 0) ){
                if( strcmp( files->filename, filename_look ) == 0 ){  /* found it */
                        fseek( wadptr, files->offset, SEEK_CUR );
						strcpy(temp->filename,files->filename);
                        temp->size = files->size;
                        temp->cur_index=0;
                        temp->buffer = (char *)malloc( files->size );
                        fread(temp->buffer, 1, files->size, wadptr);
                        found_it = 1;
                }
                files = files->next;
        }
        files = begin;       /* move back to beginning */

		if(!found_it)
			temp = NULL;
		
        return( temp );
}

int FileSize( FILE *fp ){
        int start, end;

        start=ftell(fp);
        fseek( fp, 0, SEEK_END );
        end=ftell(fp);
        fseek( fp, 0, SEEK_SET );

        return( end-start );
}

void RemoveFile( char *removename ){
        file_type *begin=files;
        file_type *previous=NULL;
        int size;
        char found_it=0;

                for(i = 0; removename[i] != '\0'; i++)
			removename[i] = toupper(removename[i]);

        if( files != NULL ){
                while( files != NULL && !found_it){                        
                        if( strcmp( files->filename, removename ) == 0 ){  /* found it */
                                found_it = 1;
                                if( previous != NULL ){
                                        previous->next = files->next;
                                        size = files->size;
                                        free( files->buffer);
                                        free( files );
                                }
                                else{
                                        previous=files;
                                        size = files->size;
                                        files = files->next;
                                        begin = files;
                                        free( previous->buffer);
                                        free( previous );
                                }{
                                file_type *temp=files;
                                while( files != NULL ){
                                        files->offset -= size;
                                        files = files->next;
                                }
                                endoffset -= size;
                                files=temp;}
                                --numfiles;

                        }
                        previous = files;
                        if( files != NULL )
                                files = files->next; /* find last file */
                }
        }
        files = begin;
}

void AddFile( char *filename ){
        char *buffer;
        FILE *fp;
        file_type *newfile;
        file_type *begin;
        int filesize;
        char duplicate = 0;

                for(i = 0; filename[i] != '\0'; i++)
			filename[i] = toupper(filename[i]);
        begin = files;
        while( files != NULL ){
                if( strcmp( files->filename, filename ) == 0 )
                        duplicate = 1;
                files = files->next;
        }
        files = begin;

        if( !duplicate ){  /* if files already isn't in there */
                if( (fp = fopen( filename, "rb" )) == NULL )
                        Error( "Couldn't open %s", filename );
        
                filesize = FileSize( fp );
                buffer = (char *)malloc( filesize );
                fread( buffer, 1, filesize, fp);
                fclose(fp);
        
                newfile = (file_type *)malloc( sizeof(file_type) );
        
                strcpy( newfile->filename, filename );
                newfile->offset = endoffset;
                newfile->size = filesize;
                newfile->next = NULL;
                newfile->buffer = buffer;
                endoffset += filesize;
                numfiles += 1;
        
                if( files == NULL ){       /* if inserting into the first position */
                        files = newfile;
                }
                else{
                        begin = files;
                        {file_type *tmp_ptr;
        
                        while( files != NULL ){                        
                                tmp_ptr = files;
                                files = files->next; /* find last file */
                        }
                        files = tmp_ptr;}
                        files->next = newfile;
                        files = begin;                
                }
        }
}

void Save(void){
        file_type *begin;
        FILE *startWAD;
        int checkfiles=numfiles;

        if( (startWAD = fopen( filename, "wb" ))  == NULL )
                Error( "Could not open %s", filename );
        
        begin = files;
        if( (fwrite( &numfiles, sizeof(int), 1, startWAD )) != 1 )
                Error( "Error writing to %s", filename );

        while( files != NULL ){
                --checkfiles;
                if( (fwrite( files->filename, 1, 14, startWAD )) != 14 )
                        Error( "Error writing to %s", filename );
                if( (fwrite( &(files->offset), sizeof(int), 1, startWAD )) != 1 )
                        Error( "Error writing to %s", filename );
                if( (fwrite( &(files->size)  , sizeof(int), 1, startWAD )) != 1 )
                        Error( "Error writing to %s", filename );
                files = files->next;
        }

        if( checkfiles != 0 ){
                printf( "Check: files = %d\n", checkfiles );
        }
        files = begin;
        while( files != NULL ){
                fwrite( files->buffer, 1, files->size, startWAD );
                files = files->next;
        }
        files = begin;
        fclose( startWAD );
}
        
int wad_fread( void *buffer, long size, long number, file_type *file){
        int i;

        for( i=0; i < (size*number); ++i ){
                if( file->cur_index >= file->size )
                        break;
                ((char *)buffer)[i]=file->buffer[file->cur_index++];
        }

        return( i/size );
}


int wad_fseek(file_type *fp, int offset, int position)
{
	if(position == SEEK_SET)
		fp->cur_index = offset;
	else if(position == SEEK_CUR)
		fp->cur_index += offset;
	else if(position == SEEK_END)
		fp->cur_index = fp->size + offset;

	if( fp->cur_index > fp->size )
		fp->cur_index = fp->size;

	return 0;
}

char wad_fgetc(file_type *fp)
{
	char ch;

	if(wad_fread(&ch,1,sizeof(char),fp) == 0)
		return NULL;

	return ch;
}

int wad_feof(file_type *fp)
{
	return(fp->cur_index >= fp->size);
}
			
