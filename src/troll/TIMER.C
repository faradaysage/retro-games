#include "timer.h"
#include <sys\timeb.h>

char first_timing=1;
struct timeb start_time;
struct timeb end_time;

void Synchronize( long milliseconds ){
        if( first_timing ){
                ftime( &start_time );
                first_timing=0;
        }
        else{
                ftime( &end_time );
                if( end_time.time == start_time.time ){
                        int loop_time;
                        loop_time=end_time.millitm-start_time.millitm;
                        if( loop_time < milliseconds ){
                                delay( milliseconds-loop_time );
                        }
                }
                ftime( &start_time );
        }
}
