#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Clock.hpp"
#include "ClockQueue.hpp"
#include "RealTimeClockSHM.hpp"
#include <unistd.h>

int
main( int argc, char **argv )
{
   RealTimeClockSHM clock( 0 /* seconds */,
                    1000 /* nanoseconds */,
                    1 /* num requesters */,
                    "theclockkey",
                    11 );
   std::cerr << "Attempting to start\n";
   clock.start();
   std::cerr << "Attempting to initialize instance!!\n";
   SystemClock::ClockQueue *instance( 
               RealTimeClockSHM::getClockQueueInstance("theclockkey") );
   std::cerr << "Instance Initialized\n";
   assert( instance != nullptr );
   std::cerr << "Time before sleep: " << 
      SystemClock::ClockQueue::getTime( *instance ) << "\n";
   errno = 0;
   if( sleep( 2 ) != 0 )
   {
      perror( "Failed to sleep for 2 seconds!!\n" );
   }
   assert( errno == 0 );
   std::cerr << "Time after sleep: " << 
      SystemClock::ClockQueue::getTime( *instance ) << "\n"; 
   return( EXIT_SUCCESS );
}
