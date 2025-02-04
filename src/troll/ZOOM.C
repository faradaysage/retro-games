#include "graphics.h"
#include <dos.h>

image_type *test;
page_type page;

void Zoom( image_type *image, double ratio, int ulx, int uly, page_type where );

void main(int argc, char *argv[]){
        double i;
        int max_ratio=1.0;

        MakePage( &page );
        if( argc < 2 )
                fprintf( stderr, "Need to specify a filename.\n\n" );
        if( argc > 2 )
                max_ratio = (double)atoi(argv[2]);                

        open_image( argv[1], &test );
                        
        load_palette( argv[1] );
        init();
        setVGApalette( palette );

        clear_screen( page, 0 );
        for(i=0.1; i<max_ratio; i+=0.1 ){
                Zoom( test, i, 0, 0, page );
                DrawScreen( page );
                clear_screen( page, 0 );
        }

        deinit();
        close_image( &test );
        DestroyPage( &page );
}

void Zoom( image_type *image, double ratio, int ulx, int uly, page_type where ){
        int x, y, byte=0;
        int ystop=(uly+image->height),  /* actual x width and y height on screen */
            xstop=(ulx+image->width);

        double real_byte=0.0;   /* use double to keep track when add is decimal */
        double add;             /* number to increment bytes each iteration */
                                /* keeps the perspective realistic */
        double incr_y;          /* keep perspective in y plane */
        int cur_y=uly;          /* counter for current y pos */
        double real_cur_y=uly;  /* use double because incr_y may be decimal */

        add=(1.0/ratio);    /* adjust values to work with ratio */
        ystop*=ratio;
        xstop*=ratio;
        incr_y=(image->height)/((double)ystop);  

        for ( y = uly; y < ystop; ++y){
                for ( x = ulx; x < xstop; ++x){
                        if(x>-1 && y>-1 && x<320 && y<200)
                                where[( x + (y << 8) + (y << 6))] = image->bitmap[byte];
                        byte=real_byte+=add;
		}
                /* new y may not already have byte at next y position, */
                byte=real_byte=cur_y*image->width;  /* this fixes it */
                cur_y=real_cur_y+=incr_y;
       }
}

