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
#include "SystemClock.tcc"

int 
main( int argc, char **argv )
{
   const int microseconds( atoi( argv[ 1 ] ) );
   SystemClock< System > clock;
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
   return( EXIT_SUCCESS );
}
