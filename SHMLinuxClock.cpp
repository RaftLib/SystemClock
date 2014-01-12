/**
 * SHMLinuxClock.cpp - 
 * @author: Jonathan Beard
 * @version: Sun Jan 12 13:59:43 2014
 */
#include "SHMLinuxClock.hpp"

SHMLinuxClock::SHMLinuxClock( const std::string shm_key ) : SHMClock( shm_key )
{

}

SHMLinuxClock::~SHMLinuxClock()
{

}

void
SHMLinuxClock::initialize()
{
   ::initialize();
   bool pin_success( pinThreads( 0 ) );
   if( ! pin_success )
   {
      std::cerr << 
         "Warning: failed to pin processor, times returned may not be correct!!\n";
   }
}

void
SHMLinuxClock::start()
{
   
}

void
SHMLinuxClock::shutdown()
{

}
