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

enum SystemType { Linux_x86, Linux_ARM, Darwin };
typedef long double sclock_t;

template < SystemType type > class SystemClock {
public:
   SystemClock() : updater( updateClock, std::ref( clock ) )
   {
   }

   virtual ~SystemClock()
   {
      updater.join();
   }

   
   sclock_t getTime()
   {
      return( clock.read() );
   }


protected:
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
   } clock;


   static void updateClock( Clock &clock_v )
   {
      while( true )
      {
         clock_v.clock.increment();
      }
   }

private:

   std::thread updater;
};
#endif /* END _SYSTEMCLOCK_HPP_ */
