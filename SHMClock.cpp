/**
 * SHMClock.cpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 14:15:58 2014
 */
#include <cassert>

#include "SHMClock.hpp"
#include "shm.hpp"
void
SHMClock::initialize()
{
   /** initialize shared memory **/
   assert( timer == nullptr );
   timer = (Timer*) SHM::Init( SHMKey.c_str() /* key */,
                               sizeof( Timer )/* size */,
                               1              /* n items */,
                               true           /* zero    */ );
   assert( timer != nullptr );                               
}
