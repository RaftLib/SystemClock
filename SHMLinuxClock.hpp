/**
 * SHMLinuxClock.hpp - 
 * @author: Jonathan Beard
 * @version: Sun Jan 12 13:59:43 2014
 */
#ifndef _SHMLINUXCLOCK_HPP_
#define _SHMLINUXCLOCK_HPP_  1
#include "ClockBase.hpp"
#include "LinuxAffinity.hpp"
#include "Affinity.hpp"
#include "SHMClock.hpp"
#include "ClockTypes.hpp"


template < ClockType T > class SHMLinuxClock : public SHMClock, public LinuxAffinity {
public:
   SHMLinuxClock( const std::string shm_key ) : SHMClock( shm_key )
   {

   }
   
   virtual ~SHMLinuxClock()
   {

   }

   virtual void initialize()
   {
      ::initialize();
      bool pin_success( pinThreads( 0 ) );
      if( ! pin_success )
      {
         std::cerr << 
            "Warning: failed to pin processor, times returned may not be correct!!\n";
      }
   }

   virtual void start()
   {

   }

   virtual void shutdown()
   {

   }
};
#endif /* END _SHMLINUXCLOCK_HPP_ */
