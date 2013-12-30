/**
 * RealTimeClock.tcc - 
 * @author: Jonathan Beard
 * @version: Sat Dec 21 09:12:12 2013
 */
#ifndef _REALTIMECLOCK_TCC_
#define _REALTIMECLOCK_TCC_  1
#include "Clock.hpp"
#include <cstdlib>
#include <iostream>
#include <errno.h>
#include <time.h>
#include <cstring>

#include "shm.hpp"
template <int CLOCK> class RealTimeClock : public ClockBase
{
public:

   RealTimeClock( int num_requestors,
                  const char* key,
                  size_t key_length  ) : ClockBase(),
                                         requestors( num_requestors )
   {
      std::strncpy( reinterpret_cast<char*>(&key_buffer[0]), 
                    key,
                    key_length );
   }

   RealTimeClock( time_t seconds,
                  long nanoseconds,
                  int num_requestors,
                  const char *key,
                  size_t key_length  ) : ClockBase( seconds,
                                                    nanoseconds ),
                                         requestors( num_requestors )
   {
      std::strncpy( reinterpret_cast<char*>(&key_buffer[0]), 
                    key,
                    key_length );
   }

   RealTimeClock( time_t seconds,
                  long   nanoseconds,
                  int    core,
                  int    num_requestors,
                  const char *key,
                  size_t key_length     ) : ClockBase( seconds,
                                                       nanoseconds,
                                                       core ),
                                            requestors( num_requestors )
   {
      std::strncpy( reinterpret_cast<char*>(&key_buffer[0]), 
                    key,
                    key_length );
   }

   virtual ~RealTimeClock()
   {
      Close( reinterpret_cast< const char*>(&key_buffer[0]),
             (void*) queues,
             sizeof( ClockQueue ),
             requesters,
             true,
             true );
   }

#if(0)
#endif
protected:

   virtual void checkRequests()
   {

   }

   virtual void serviceRequests()
   {

   }

   /**
    * updateTime - updates time based on the linux nanosleep function.
    * This funciton is called by the base class.
    */
   virtual void updateTime()
   {
      for(;;)
      {
         const int ret_val( clock_nanosleep( CLOCK /* clock ID */ ,
                                             0              /* flags */    ,
                                             res   /* request */ ,
                                             /* remain struct timespec  */
                                           ) );
         std::lock( clock_lock );
         clock++;
         std::unlock( clock_lock );
      }
   }                

   virtual void initialize()
   {
      /* pin processor */
      /* the cpuset should be inherited by forked processes */
      cpu_set_t   *cpuset( nullptr );
      const int8_t processors_to_allocate( 1 );
      size_t cpu_allocate_size( -1 );
#if   (__GLIBC_MINOR__ > 9 ) && (__GLIBC__ == 2 )
      cpuset = CPU_ALLOC( processors_to_allocate );
      assert( cpuset != nullptr );
      cpu_allocate_size =  CPU_ALLOC_SIZE( processors_to_allocate );
      CPU_ZERO_S( cpu_allocate_size, cpuset );
#else
      cpu_allocate_size = sizeof( cpu_set_t );
      cpuset = (cpu_set_t*) malloc( cpu_allocate_size );
      assert( cpuset != nullptr );
      CPU_ZERO( cpuset );
#endif
      CPU_SET( core,
               cpuset );
      auto setaffinity_ret_val( success );
      errno = success;
      setaffinity_ret_val = sched_setaffinity( 0 /* self */,
                                               cpu_allocate_size,
                                               cpuset );
      if( setaffinity_ret_val != success )
      {
         perror( "Failed to set processor affinity" );
         exit( EXIT_FAILURE );
      }

      /** allocate shared memory **/
      assert( queues == nullptr );
      queues = (ClockQueue*) SHM::Init( 
            reinterpret_cast< const char*>(key[0]) /* key       */,
            sizeof( ClockQueue )                   /* item size */,
            requesters                             /* nitems    */,
            true                                   /* zero      */);
      assert( queues != nullptr );      
   }

private:
   const int requesters;
   char      key_buffer[32];
};
#endif /* END _REALTIMECLOCK_TCC_ */
