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
#include <cassert>
#include "SystemClock.tcc"

template < class A, class B, class C > bool rangecheck( A &&val, B &&time, C &&resolution )
{
   const auto resolution_mult( time ); 
   const auto upper( time + resolution_mult );
   const auto lower( time - resolution_mult );
   if( val >= lower and val <= upper )
   {  
      return( true );
   }
   std::cout << "Range check failed with value (" << val << "), range is(" << 
      lower << ", " << upper << ").\n";
   return( false );
}

int 
main( int argc, char **argv )
{
   SystemClock< System > clock( 0 /** core zero **/ );   
   const auto resolution( clock.getResolution() );
   const auto microseconds( 1000 );
   for( auto iterations( 0 ); iterations < 10; iterations++ )
   {
      auto start = clock.getTime();
      usleep( (useconds_t) microseconds );
      const auto diff( clock.getTime() - start );
      assert( rangecheck( diff, microseconds * .000001, resolution ) == true );
   }
   return( EXIT_SUCCESS );
}
