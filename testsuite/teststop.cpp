#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <array>
#include <cassert>
#include "SystemClock.tcc"

int 
main( int argc, char **argv )
{
#if __linux
   SystemClock< Cycle  > clock( 0 /** core zero **/ );  
#else
   SystemClock< System > clock( 0 /** core zero **/ );   
#endif
   const auto resolution( clock.getResolution() );
   const auto microseconds( 1000 );
   const auto num_iterations( 1e3 );
   double diff_accum( 0.0 );
   for( auto iterations( 0 ); iterations < num_iterations; iterations++ )
   {
      auto start( clock.stop() );
      usleep( (useconds_t) microseconds );
      const auto diff( clock.start() - start );
      diff_accum += diff;
   }
   const double average( diff_accum / num_iterations );
   /** 
    * 10x is pretty much completely arbitrary and a bad swap
    * will result in this test failing
    */
   assert( average < 10 * resolution );
   return( EXIT_SUCCESS );
}
