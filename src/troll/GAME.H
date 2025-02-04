#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <mem.h>
#include <dos.h>
#include <fcntl.h>
#include <conio.h>
#include "error.h"

#define clear_screen(x,y)  memset( x, y, 64000 )
#define WaitForSync   while(inp(0X3DA) & 0x08);while(!(inp(0x3DA) & 0X08));


#define MAXINDEXES 65535 /* used by open_vbackground() and put_vbackground() */
#define MAXINDEXES_2 131070   /* MAXINDEXES * 2 */
#define MAXINDEXES_3 196605   /* MAXINDEXES * 3 */
#define MAXINDEXES_4 262140

long index=0;

typedef long int counter_type;

typedef unsigned char * page_type;

/* virtual background */
typedef struct vbackground_tag {
        char **bitmap;           /* 2d cause index !> 65535 for 1d */
        short ulx, uly;
        short width, height;
} vbackground_type;

typedef struct image_tag {
	unsigned char *bitmap;
        short width;
        short height;
} image_type;

typedef struct {
	char    manufacturer;
	char    version;
	char    encoding;
	char    bits_per_pixel;
        short   xmin,ymin;
        short   xmax,ymax;
        short   hres;
        short   vres;
	char    pallete[48];
	char    reserved;
	char    colour_planes;
        short   bytes_per_line;
        short   pallete_type;
	char    filler[58];
		} PCXHEAD;
PCXHEAD   header;

/* The variable header is a struct that will contain all the usefull picture
information shown in the above fields.  */

unsigned int width,depth;    /* will hold the header info for width and depth*/
unsigned int bytes;

typedef unsigned char palette_type;
palette_type palette[768];

unsigned char *videoscreen=(unsigned char *)0xA0000;

void cpalette(char color, char r, char g, char b );
void init(void);
void deinit(void);           /* return to normal     */
void setVGApalette(char *p); /* set the vga pallete  */
void open_image(char *filename, image_type **image);
void open_vbackground(char *filename, vbackground_type **vbackground);
void close_image(image_type **image);
void close_vbackground(vbackground_type **image);
void put_image (image_type *image, int ulx, int uly, char transparent, char *where );
void put_vbackground (vbackground_type *vbackground, char *where );
void fade_to_black( void );
void fade_to_palette( char *, int );
long sqrt_FAST(long v);
void load_palette(char *filename);
void scrollx_single( int , char *, int );
void DrawScreen( char *from );
void MakePage( unsigned char **page );
void DestroyPage( unsigned char **page );

/***************************************************************************/
/***********************      BEGIN FUNCTIONS     **************************/
/***************************************************************************/

void MakePage( unsigned char **page ) {
	if( ((*page)=(unsigned char *)malloc( sizeof(unsigned char)*64000 )) == NULL )
		Error( "Not enough memory.\n" );
}

void DestroyPage( unsigned char **page ) {
	free( (*page) );
}

void DrawScreen( char *from ) {
        WaitForSync;
	memcpy( videoscreen, from, 64000 );
}

void scrollx_single( int pixels, char *what, int size ) {
	int i;
	char *buffer;

	buffer = (char *)malloc( size );
	for(i=0;i<200;++i) {
		buffer[ (i<<8)+(i<<6) ] = what[ (i<<8)+(i<<6) ];
	  //	memcpy( &(buffer[(i<<8)+(i<<6) + 1]), &(what[ (i<<8)+(i<<6) + 1]), 319 );
	}
	memcpy( what, buffer, size );
}

void close_image(image_type **image) {
	free( (*image)->bitmap );
	free( (*image) );
}

void close_vbackground(vbackground_type **vbackground) {
        int i,
		 number_of_i=((*vbackground)->height*(*vbackground)->width)/MAXINDEXES;

	for(i=0; i<number_of_i; ++i )
		free( (*vbackground)->bitmap[i] );
	free( (*vbackground)->bitmap[number_of_i] );
	free( (*vbackground)->bitmap );
	free( (*vbackground) );
}

void init( void ) {
   union REGS r;
   r.x.eax = 0x13;
   int386( 0x10, &r, &r );
   /*
	asm {
		mov ax, 13h
		int 10h
	};
    */
}
void load_palette(char *filename)
{
	int i;
	FILE *fp;
	PCXHEAD dummy;

	if((fp=fopen(filename,"rb")) != NULL){
			/* read in the header */
		  if(fread((char *) &dummy,1,sizeof(PCXHEAD),fp) == sizeof(PCXHEAD)){
		  /*check to make sure it's a picture */
			 if(dummy.manufacturer==0x0a && dummy.version ==5){
				 if(!fseek(fp,-769L,SEEK_END)){
					 if(fgetc(fp) == 0x0c && fread(palette,1,768,fp) == 768) {
						 fseek(fp,128L,SEEK_SET);
					 }
					 else
						 Error("error reading pallete");
				 }
				 else
					 Error("error seeking to pallete");
			}
			else
				 Error("not a 256 color pcx file.\n");
		}
		else
			Error("error reading %s.\n",filename);
	}
	else
		Error("Error opening %s.\n",filename);

fclose(fp);

//convert eight bits to six bits
for (i=0;i<768;i++) palette[i]=palette[i] >> 2;
}

void cpalette( char color, char r, char g, char b )
{
     outp( 0x3c8, color );
     outp( 0x3c9, r     );
     outp( 0x3c9, g     );
     outp( 0x3c9, b     );
}

void put_vbackground (vbackground_type *vbackground, char *where )
{
        int x, y;
	counter_type byte=((vbackground->width*vbackground->uly)+vbackground->ulx);
        int add=(vbackground->width-320);

	for ( y = 0; y < 200; ++y) {
		for ( x = 0; x < 320; ++x) {
			/* determine which array has the byte */
			if( byte < MAXINDEXES )
			  where[( (x) + (((y) << 8) + ((y) << 6)))] = vbackground->bitmap[0][byte];
			else if( byte < MAXINDEXES_2 )
			  where[( (x) + (((y) << 8) + ((y) << 6)))] = vbackground->bitmap[1][byte-MAXINDEXES];
			else if( byte < MAXINDEXES_3 )
			  where[( (x) + (((y) << 8) + ((y) << 6)))] = vbackground->bitmap[2][byte-MAXINDEXES_2];
			else if( byte < MAXINDEXES_4 )
			  where[( (x) + (((y) << 8) + ((y) << 6)))] = vbackground->bitmap[3][byte-MAXINDEXES_3];
			++byte;
		}
		byte += add;
	}
}

void put_image( image_type *image, int ulx, int uly, char transparent, char *where )
{
	counter_type x, y, byte=0;
        int ystop=uly+image->height,
		 xstop=ulx+image->width;

	for ( y = uly; y < ystop; ++y)
		for ( x = ulx; x < xstop; ++x)
		{
		  if(x>-1 && y>-1 && x<320 && y<200)
			if ( image->bitmap[byte] != transparent )
				where[( x + (y << 8) + (y << 6))] = image->bitmap[byte];
			++byte;
		}
}


void open_vbackground(char *filename, vbackground_type **vbackground )
{
        int x,c;
	counter_type i=0;
	long int   inc;
	FILE *fp;
	c=0;


	if ( ((*vbackground) = (vbackground_type *)malloc( sizeof(vbackground_type) )) ==NULL )
		Error( "Not enough memory.\n" );

	if((fp=fopen(filename,"rb")) != NULL){
			/* read in the header */
		  if(fread((char *) &header,1,sizeof(PCXHEAD),fp) == sizeof(PCXHEAD)){
		  /*check to make sure it's a picture */
			 if(header.manufacturer==0x0a && header.version ==5){
				 if(!fseek(fp,-769L,SEEK_END)){
					 if(fgetc(fp) == 0x0c && fread(palette,1,768,fp) == 768) {
						 int number_of_i, leftover_j; /* for allocated bitmap */

						 fseek(fp,128L,SEEK_SET);
						 /*allocate a big buffer */
						 (*vbackground)->width  = ((header.xmax - header.xmin)+1);
						 (*vbackground)->height = ((header.ymax - header.ymin)+1);

						 number_of_i = (((*vbackground)->width)*((*vbackground)->height)) / MAXINDEXES;
						 leftover_j  = (((*vbackground)->width)*((*vbackground)->height)) % MAXINDEXES;

						 /***** allocate memory for bitmap *****/
						 if( (((*vbackground)->bitmap) = (char **)malloc( sizeof(char *)*(number_of_i+1) )) == NULL )
							 Error( "Ran out of memory.\n");
						 for(i=0; i<number_of_i; ++i ) {
							 if( ((*vbackground)->bitmap[i] = (char *)malloc( sizeof(char)*MAXINDEXES )) == NULL )
								 Error( "Ran out of memory.\n");
						 }
						 if( ((*vbackground)->bitmap[number_of_i] =  (char *)malloc( sizeof(char)*leftover_j )) == NULL )
							 Error( "Ran out of memory.\n");

						 bytes=header.bytes_per_line;
					} else
						 Error("error reading pallete");
				}else
					Error("error seeking to pallete");
			}else
				Error("not a 256 color pcx file.\n");
	  }else
		  Error("error reading %s.\n",filename);
 } else
	 Error ("Error opening %s.\n",filename);

/***********************************************************************/
	for (i = 0; i < (((*vbackground)->height)*((*vbackground)->width)); ++i){
		c=fgetc(fp) & 0xff;  /* if it's a run of bytes field */

		if((c & 0xc0) == 0xc0) { /* and off the high bits */
			x=c & 0x3f;
			/* run the byte */
			c=fgetc(fp);
			while(x--) {
				if( i < MAXINDEXES )
					(*vbackground)->bitmap[0][i] = c;
				else if( i < MAXINDEXES_2 )
					(*vbackground)->bitmap[1][i-MAXINDEXES] = c;
				else if( i < MAXINDEXES_3 )
					(*vbackground)->bitmap[2][i-MAXINDEXES_2] = c;
				else if( i < MAXINDEXES_4 )
					(*vbackground)->bitmap[3][i-MAXINDEXES_3] = c;
				++i;
			}
			i--;
		}
		/*else just store it */
		else {
			if( i < MAXINDEXES )
				(*vbackground)->bitmap[0][i] = c;
			else if( i < MAXINDEXES_2 )
				(*vbackground)->bitmap[1][i-MAXINDEXES] = c;
			else if( i < MAXINDEXES_3 )
				(*vbackground)->bitmap[2][i-MAXINDEXES_2] = c;
			else if( i < MAXINDEXES_4 )
				(*vbackground)->bitmap[3][i-MAXINDEXES_3] = c;
		}
	}
	(*vbackground)->ulx = (*vbackground)->uly = 0;
	fclose(fp);
}


void open_image(char *filename, image_type **image )
{
	int size,x,c,count;
	long int n;
	counter_type i=0;
	long int   inc;
	FILE *fp;
	c=0;

        if( ((*image) = (image_type *)malloc( sizeof(image_type) )) == NULL )
           Error( "Not enough memory for this.\n");

	if((fp=fopen(filename,"rb")) != NULL){
			/* read in the header */
		  if(fread((char *) &header,1,sizeof(PCXHEAD),fp) == sizeof(PCXHEAD)){
		  /*check to make sure it's a picture */
			 if(header.manufacturer==0x0a && header.version ==5){
				 if(!fseek(fp,-769L,SEEK_END)){
					 if(fgetc(fp) == 0x0c && fread(palette,1,768,fp) == 768) {
						 fseek(fp,128L,SEEK_SET);
						 /*allocate a big buffer */
						 (*image)->width  = (header.xmax - header.xmin) +1;
						 (*image)->height = (header.ymax - header.ymin)+1;
                                                 if ( ((*image)->bitmap = (char *)malloc( sizeof(char)*(((*image)->width)*((*image)->height)) )) == NULL )
							 Error( "Ran out of memory.\n" );
						 bytes=header.bytes_per_line;
					} else
						 Error("error reading pallete");
				}else
					Error("error seeking to pallete");
			}else
				Error("not a 256 color pcx file.\n");
	  }else
		  Error("error reading %s.\n",filename);
 } else
	 Error ("Error opening %s.\n",filename);

/***********************************************************************/

	for (i = 0; i < (((*image)->height)*((*image)->width)); ++i){
		c=fgetc(fp) & 0xff;  /* if it's a run of bytes field */

		if((c & 0xc0) == 0xc0) { /* and off the high bits */
			x=c & 0x3f;
			/* run the byte */
			c=fgetc(fp);
			while(x--)
			{
				(*image)->bitmap[i++] = c;
			}
			i--;
			}
			/*else just store it */
			else
			{
				(*image)->bitmap[i] = c;
			}
		}
	 fclose(fp);
}

void  deinit(void)   /*turn off graphics card */
{
   union REGS r;
   r.x.eax = 0x03;
   int386( 0x10, &r, &r );
   /*
	asm{
		mov ax,03h
		int 10h
	};
   */
}

void setVGApalette(char *p)   /*set the VGA palette to RGB buffer p */
{

	int cv;
	for(cv = 0; cv <= 255; cv++)
			cpalette(cv,p[cv*3],p[cv*3+1],p[cv*3+2]);
/*
	union REGS r;
	struct SREGS sr;
	int i;
      
	r.x.eax=0x1012;
	r.x.ebx=0;
	r.x.ecx=256;
	r.x.edx=FP_OFF(p);
	sr.es=FP_SEG(p);
        int386x(0x10,&r,&r,&sr);  
*/         
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

void fade_to_black( void )
{
	int index, notfinished = 1;

	char temp_pal[ 768 ];

	memcpy( temp_pal, palette, sizeof( char )*768 );

	while ( notfinished )
	{
		notfinished = 0;
		for ( index = 0; index < 768; ++index )
		{
			if ( temp_pal[ index ] > 0 )
				--temp_pal[ index ];
                        else if ( temp_pal[ index ] < 0 ){
                              ++temp_pal[ index ];
                        }
			else
				notfinished = 1;
		}
		if ( notfinished ) setVGApalette( temp_pal );
	}
}

void fade_to_palette(char *temp_pal, int time )
{
	int index, notfinished = 1;

	while ( notfinished )
	{
		notfinished = 0;
		for ( index = 0; index < 768; ++index )
		{
			if ( temp_pal[ index ] != palette[ index ] ) {
				notfinished = 1;
				++temp_pal[ index ];
			}
			/*else if ( temp_pal[ index ] < palette[ index ] ) {
				notfinished = 1;
				++temp_pal[ index ];
			} */
		}
		setVGApalette( temp_pal );
		delay(time);
	}
}
#endif
