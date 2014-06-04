/**
 * main.cpp - 
 * @author: Jonathan Beard
 * @version: Sun Apr 20 15:37:04 2014
 * 
 * Copyright 2014 Jonathan Beard
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <fstream>
#include <array>
#include "SystemClock.tcc"

#define RESOLUTION 1
int 
main( int argc, char **argv )
{
   SystemClock< System > clock;   
#ifdef TESTCLOCK   
   const int microseconds( atoi( argv[ 1 ] ) );
   auto start = clock.getTime();
   usleep( (useconds_t) microseconds );
   std::cerr << (clock.getTime() - start) << "\n";
   start = clock.getTime();
   usleep( (useconds_t) microseconds );
   std::cerr << (clock.getTime() - start) << "\n";
   start = clock.getTime();
   usleep( (useconds_t) microseconds );
   std::cerr << (clock.getTime() - start) << "\n";
   start = clock.getTime();
   usleep( (useconds_t) microseconds );
   std::cerr << (clock.getTime() - start) << "\n";
   start = clock.getTime();
#elif defined TESTPERIOD
   const size_t count( 1e6 );
   std::ofstream ofs( argv[ 1 ] );
   if( ! ofs.is_open() )
   {
      std::cerr << "Failed to open output file!!\n";
      exit( EXIT_FAILURE );
   }
   std::array< sclock_t , count > update_array; 
   for( size_t index( 0 ); index < count; index++ )
   {
      update_array[ index ] = clock.getTime();
   }
   struct Mean{
      Mean() : total( 0.0 ),
               n( 0 )
      {}

      double   total;
      uint64_t n;

      void operator += (const float val )
      {
         total += val;
         n++;
      }

      std::ostream& print( std::ostream &stream )
      {
         stream << (total / n );
         return( stream );
      }
   } mean;

   for( size_t index( 1 ); index < count; index++ )
   {
      const float val( update_array[ index ] - update_array[ index - 1 ] );
      if( val > 1e-12 ) /** something lower than we'd expect resolution to be **/
      {
         mean += val; 
      }
      ofs << ( val ) << "\n";  
   }
   std::cout << "Mean resolution: ";
   mean.print( std::cout ) << "\n";
   ofs.close();
#elif defined RESOLUTION
   std::cout << "Resolution: " << clock.getResolution() << "\n";
#endif
   return( EXIT_SUCCESS );
}
