/**
 * SystemClock.hpp - 
 * @author: Jonathan Beard
 * @version: Sun Apr 20 15:41:37 2014
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
#ifndef _SYSTEMCLOCK_HPP_
#define _SYSTEMCLOCK_HPP_  1
#include <thread>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <time.h>

enum SystemType { Linux_x86, Linux_ARM, Darwin };
enum ClockType  { Dummy, Cycle, System };

typedef long double sclock_t;

template < SystemType type, ClockType T > class SystemClock {
public:
   SystemClock() : clock(   nullptr ),
                   updater( nullptr ),
                   stop(    false )
   {
      clock    = new Clock();
      updater  = new std::thread( updateClock, clock , std::ref( stop ) );
   }

   virtual ~SystemClock()
   {
      updater->join();
      delete( updater );
      updater = nullptr;
      delete( clock );
      clock = nullptr;
   }

   
   sclock_t getTime()
   {
      return( clock->read() );
   }

   void     done()
   {
      stop = true;
   }


private:
   class Clock {
   public:
      Clock() : a( 0.0 ),
                b( 0.0 )
      {}
      
      void increment()
      {
         a++;
         b++;
      }

      void increment( sclock_t inc )
      {
         a += inc;
         b += inc;
      }

      sclock_t read()
      {
         struct{
            sclock_t a;
            sclock_t b;
         } copy;
         do{
            copy.a = a;
            copy.b = b;
         }while( copy.a != copy.b );
         return( copy.b );
      }

   private:
      volatile sclock_t a;
      volatile sclock_t b;
   };



   static void updateClock( Clock *clock , volatile bool &done )
   {
      std::function< void ( Clock* ) > function;
      switch( T )
      {
         case( Dummy ):
         {
            function = []( Clock *clock ){ clock->increment(); };
         }
         break;
         case( Cycle ):
         {
            assert( false );
         }
         break;
         case( System ):
         {
#ifdef   __linux
            struct timespec curr_time;
            struct timespec prev_time;
            std::memset( &curr_time, 0, sizeof( struct timespec ) ); 
            std::memset( &prev_time, 0, sizeof( struct timespec ) ); 
            if( clock_gettime( CLOCK_REALTIME, &prev_time ) != 0 )
            {
               perror( "Failed to get initial time." );
            }
            function = [&]( Clock *clock )
            {
               errno = 0;
               if( clock_gettime( CLOCK_REALTIME, &curr_time ) != 0 )
               {
                  perror( "Failed to get current time!" );
               }
               const struct timespec diff( 
                  { .tv_sec  = curr_time.tv_sec  - prev_time.tv_sec,
                    .tv_nsec = curr_time.tv_nsec - prev_time.tv_nsec } );
               prev_time = curr_time;
               /* update global time */
               const sclock_t seconds( 
                     (sclock_t ) diff.tv_sec + ( ( sclock_t ) diff.tv_nsec * 1.0e-9 ) );
               clock->increment( seconds );
            };
#elif defined __APPLE__

#else

#endif
         }
         break;
         default:
            break;
      }
      while( ! done )
      {
         function( clock );
      }
   }
   
   Clock             *clock;
   std::thread       *updater;
   volatile bool     stop;

};
#endif /* END _SYSTEMCLOCK_HPP_ */
