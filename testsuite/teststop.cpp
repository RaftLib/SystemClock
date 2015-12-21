#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <array>
#include <cassert>
#include <cmath>

#include "SystemClock.tcc"

int 
main( int argc, char **argv )
{
   SystemClock< System > clock( 0 /** core zero **/ );   
   const auto resolution( clock.getResolution() );
   const auto microseconds( 1000 );
   const auto num_iterations( 1e5 );
   double diff_accum( 0.0 );
   for( auto iterations( 0 ); iterations < num_iterations; iterations++ )
   {
      volatile auto start( clock.stop() );
      usleep( (useconds_t) microseconds );
      volatile const auto diff( clock.start() - start );
      diff_accum += diff;
   }
   const double average( diff_accum / num_iterations );
   const double tenperc( .001 /** microseconds **/ * .10 );
   if( std::isgreater( average, tenperc ) )
   {
      std::fprintf( stderr, 
                    "%.20f is greater than 10 percent (100 microseconds) of measured time.", 
                    average );
      std::exit( EXIT_FAILURE );
   }
   const double actual_fraction( ( average / .001 ) * 100 );
   //print out the actual fraction of time we're off
   std::fprintf( stderr, "%.20f\n", actual_fraction );
   /** else return success **/
   return( EXIT_SUCCESS );
}
