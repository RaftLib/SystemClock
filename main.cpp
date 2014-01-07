#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <cassert>
#include "Clock.hpp"
#include "ClockQueue.hpp"
#include "RealTimeClockSHM.hpp"
#include "system_query.h"

void
run( /*std::chrono::microseconds us*/ )
{
   const std::chrono::seconds us( 2 );
   const auto start = std::chrono::high_resolution_clock::now();
   const auto end = start + us;
   do {
      std::this_thread::yield();
   } while (std::chrono::high_resolution_clock::now() < end);
   const std::chrono::microseconds us2 = std::chrono::high_resolution_clock::now();
   
}


int
main( int argc, char **argv )
{
   RealTimeClockSHM clock( 0 /* seconds */,
                    100 /* nanoseconds */,
                    -1 /* core */,
                    1 /* num requestors */,
                    "theclockkey",
                    11 );
   std::cerr << "Attempting to start\n";
   clock.start();
   std::cerr << "Attempting to initialize instance!!\n";
   volatile SystemClock::ClockQueue *instance( 
               RealTimeClockSHM::getClockQueueInstance("theclockkey") );
   std::cerr << "Instance Initialized\n";
   assert( instance != nullptr );
   std::cerr << "Time before sleep: " << 
      SystemClock::ClockQueue::getTime( *instance ) << "\n";
   std::thread t1( run );
   t1.join();
   std::cerr << "Time after sleep: " << 
      SystemClock::ClockQueue::getTime( *instance ) << "\n"; 

   return( EXIT_SUCCESS );
}
