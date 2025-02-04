#include "inventry.h"

#include "graphics.h"
#include "keyboard.h"
#include "main2.h"   /* LoadCurPalette() */

typedef struct inv_tag{
   image_type *image;
   image_type *image_highlight;
   char present;
} inv_type;

extern page_type page;

inv_type inventory[ MAX_INV ];

short cur_inv=0;  /* current inventory choice is rock */

char *inv_files[ MAX_INV ][2] = { {"rockinv.pcx", "rockinh.pcx"},
                                  {"guninv.pcx" , "guninvh.pcx"},
				  {"diaminv.pcx", "diaminvh.pcx"} };

vbackground_type *inventory_screen;

int  GetInventory( int inv ){
	return( inventory[inv].present );
}

void SetInventory( int inv, int value ){
	if( value == 0 && cur_inv == inv )
		cur_inv = 0;
	inventory[inv].present = value;
}

void ShowInventory( void ){
   short i, j, count, move;   

   WaitForKeyRelease;

   clear_screen( page, 0 );
   DrawScreen( page );

   load_palette( INVENTORY_FILE );
   setVGApalette( palette );              /* change palettes */

   while( keyboard[ INDEX_I ] == 0 && keyboard[ INDEX_ENTER ] == 0 ){
      
	   put_vbackground( inventory_screen, page );
	   
           count = 0;
	   for(j=10; j<180; j += 60 )   /* 3 by 4 */
	      for(i=10; i<210; i += 50 ){   
	         if( count < MAX_INV )
	            if( inventory[count].present ){
	               if( cur_inv == count )
	                  put_image( inventory[count].image_highlight, i, j, 0, page );
	               else
	                  put_image( inventory[count].image, i, j, 0, page );
	            }
	         ++count;
	      }
	   DrawScreen( page );
           
	   if( move != 0 ) WaitForKeyRelease;
	     
           move = (keyboard[ INDEX_DOWN ] - keyboard[ INDEX_UP ])*4;
	   move += (keyboard[ INDEX_RIGHT ] - keyboard[ INDEX_LEFT ]);

           if( (cur_inv+move) >= 0 && (cur_inv+move) < MAX_INV ){
	   	if( move > 0 ){
	        	for(i=cur_inv+move; i<MAX_INV; ++i ){
	              	   if( inventory[i].present ){
        	        	 cur_inv = i; 
                		 break;
             	  	   }
            		}
	    	}
	  	else if( move < 0 ){
	        	for(i=cur_inv+move; i>=0; --i ){
	              	   if( inventory[i].present ){
        	        	 cur_inv = i; 
                		 break;
             	  	   }
            		}
	    	}	
	   }
   }
   WaitForKeyRelease;

   clear_screen( page, 0 );
   DrawScreen( page );

   LoadCurPalette();
   setVGApalette( palette );
}

void InitializeInventoryScreen( void ){
   short count;

   open_vbackground( INVENTORY_FILE, &inventory_screen );

   for(count=0; count<MAX_INV; ++count ){
         open_image( inv_files[count][0], &(inventory[count].image) );
         open_image( inv_files[count][1], &(inventory[count].image_highlight) );
         inventory[count].present = 0;
   }
   
   inventory[rock_inv].present = 1;  /* start with rock */
}
   

void CloseInventoryScreen( void ){
   short count;

   close_vbackground( &inventory_screen );

   for(count=0; count<MAX_INV; ++count ){
      close_image( &(inventory[count].image) );
   }
}
