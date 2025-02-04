#include "graphics.h"
#include <dos.h>
          
#define TEST_FILE "c:\\game\\intro.pcx"

image_type *test;
page_type page;

void Mosaic( image_type *image, int block_size, int ulx, int uly, page_type where );

void main(int argc, char *argv[]){
        int i, size=30;

        if( argc == 2 )
                size = atoi( argv[1] );

        MakePage( &page );
        open_image( TEST_FILE, &test );
        load_palette( TEST_FILE );
        init();
        setVGApalette( palette );

        clear_screen( page, 0 );
        Mosaic( test, 5, 0, 0, page );
        DrawScreen( page );
        getchar();
        clear_screen( page, 0 );
        for(i=size; i>1; i-=1 ){
                Mosaic( test, i, 0, 0, page );
                DrawScreen( page );
                clear_screen( page, 0 );
                //delay(30);
        }
        delay(100);
        for(i=1; i<size; i+=1 ){
                Mosaic( test, i, 0, 0, page );
                DrawScreen( page );
                clear_screen( page, 0 );
                //delay(30);
        }

        deinit();
        close_image( &test );
        DestroyPage( &page );
}

void Mosaic( image_type *image, int block_size, int ulx, int uly, page_type where ){
        int x, y, byte=0;
        int ystop=(uly+image->height),  /* actual x width and y height on screen */
            xstop=(ulx+image->width);

        for ( y = uly; y < ystop; y+=block_size){
                for ( x = ulx; x < xstop; x+=block_size){
                        DrawFilledRectangle( x, y, block_size, image->bitmap[byte], where );
                        byte+=block_size;
		}
                byte=y*xstop+(image->width)*(block_size-1);
       }
}

void DrawFilledRectangle( int ulx, int uly, int size, int color, page_type where ){
        int x, y, xstop=ulx+size, ystop=uly+size;

        for ( y = uly; y < ystop; ++y){
                for ( x = ulx; x < xstop; ++x){
                        if(x>-1 && y>-1 && x<320 && y<200)
                                where[( x + (y << 8) + (y << 6))] = color;
		}
       }
}
