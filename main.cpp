#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Clock.hpp"
#include "ClockQueue.hpp"
#include "RealTimeClockSHM.hpp"

int
main( int argc, char **argv )
{
   RealTimeClockSHM clock( 0 /* seconds */,
                    1000 /* nanoseconds */,
                    1 /* num requesters */,
                    "theclockkey",
                    11 );
   clock.start();

   SystemClock::ClockQueue *instance( 
               RealTimeClockSHM::getClockQueueInstance("theclockkey") );
   assert( instance != nullptr );
   const double timeToStop( 1.123 + 
      SystemClock::ClockQueue::getTime( instance[0]  ) );
   std::cerr << "Time to stop: " << timeToStop << "\n";
   volatile double last( 0.0 );
   while( timeToStop >= 
         ( last = SystemClock::ClockQueue::getTime( instance[0]  ) ) )
   {
      /** do nothing **/
      std::cerr << "CTime: " << last << "\n";
   }
   std::cerr << "Timer Stopped at time: " << last << "\n";
   std::cerr << "Target Stop Time: " << timeToStop << "\n";
   return( EXIT_SUCCESS );
}
