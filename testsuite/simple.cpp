#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <array>
#include <cassert>
#include "SystemClock.tcc"
#include <thread>

int 
main( int argc, char **argv )
{

   SystemClock< System > clock( 0 /** core zero **/ );   

   std::cerr << clock.getTime() << "\n";
   std::this_thread::sleep_for( std::chrono::seconds(2) );
   std::cerr << clock.getTime() << "\n";
   std::this_thread::sleep_for( std::chrono::seconds(2) );
   std::cerr << clock.getTime() << "\n";
   std::this_thread::sleep_for( std::chrono::seconds(2) );
   clock.stop();
   std::cerr << clock.getTime() << "\n";
   std::this_thread::sleep_for( std::chrono::seconds(2) );
   std::cerr << "should be same as prior: " << clock.getTime() << "\n";
   clock.start();
   std::this_thread::sleep_for( std::chrono::seconds(2) );
   std::cerr << "should be +2 seconds: " << clock.getTime() << "\n";

   return( EXIT_SUCCESS );
}
