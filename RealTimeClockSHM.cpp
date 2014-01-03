/**
 * RealTimeClockSHM.cpp - 
 * @author: Jonathan Beard
 * @version: Tue Dec 31 10:23:23 2013
 */
#include <iostream>
#include <errno.h>
#include <time.h>
#include <cstring>
#include <cassert>
#include "RealTimeClockSHM.hpp"
#include "shm.hpp"

RealTimeClockSHM::RealTimeClockSHM( int num_requestors,
                                 const char* key,
                                 size_t key_length  ) : ClockBase(),
                                                        requestors( num_requestors )
{
   std::strncpy( reinterpret_cast<char*>(&key_buffer[0]), 
                 key,
                 key_length );
	updateTime = updateTimeFunction;
   checkRequestsFunction = theCheckRequestsFunction; 
}

RealTimeClockSHM::RealTimeClockSHM( time_t seconds,
                                 long nanoseconds,
                                 int num_requestors,
                                 const char *key,
                                 size_t key_length  ) : ClockBase( seconds,
                                                                   nanoseconds ),
                                                                   requestors( 
                                                                     num_requestors )
{
   std::strncpy( reinterpret_cast<char*>(&key_buffer[0]), 
                 key,
                 key_length );
	updateTime = updateTimeFunction;
   checkRequestsFunction = theCheckRequestsFunction; 
}

RealTimeClockSHM::RealTimeClockSHM( time_t seconds,
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
	updateTime = updateTimeFunction;
   checkRequestsFunction = theCheckRequestsFunction; 
}

RealTimeClockSHM::~RealTimeClockSHM()
{  
   callSelfDestruct();
   SHM::Close( reinterpret_cast< const char*>(&key_buffer[0]),
          (void*) queues,
          sizeof( SystemClock::ClockQueue ),
          requestors,
          true,
          true );
}


void 
RealTimeClockSHM::updateTimeFunction( ClockBase &base )
{
   const int success( 0 );
   while( ! base.selfdestruct )
   {
      errno = success;
      struct timespec remainder( {0,0} );
      const int ret_val( clock_nanosleep( CLOCK_REALTIME      /* clock ID */ ,
                                          0          /* flags */    ,
                                          &base.res       /* request */ ,
                                          &remainder /* remain struct timespec  */
                                        ) );
      if( ret_val == EINTR && remainder.tv_sec != 0 && remainder.tv_nsec != 0 )
      {
         /** try sleep again with remainder, ignore ramainder on sec. attempt **/
         struct timespec remainder_two( {0,0} );
         errno = success;
         const int ret_val_two( clock_nanosleep( CLOCK_REALTIME,
                          0,
                          &remainder,
                          &remainder_two ) );
         if( ret_val_two != success && ret_val_two != EINTR )
         {
            perror( "Failed to sleep for the designated amount of time!!" );
         }
      }
      /** increment clock atomically **/
   	base.incrementClock();
	}
}                

void 
RealTimeClockSHM::theCheckRequestsFunction( ClockBase &base )
{
   RealTimeClockSHM &base_rtc_shm( reinterpret_cast<
                                    RealTimeClockSHM&>( base ) );
   while( ! base.selfdestruct ){                                    
      for( int i( 0 ); i < base_rtc_shm.getRequestors() ; i++ )
      {
         if( SystemClock::ClockQueue::isRequestWaiting( base_rtc_shm.queues[i] ) )
         {
            const auto clock_val( base_rtc_shm.getClock() );
            SystemClock::ClockQueue::acknowledgeRequest( base_rtc_shm.queues[i] );
            const double   nanoseconds( base_rtc_shm.res.tv_nsec * clock_val );
            const time_t   seconds(     base_rtc_shm.res.tv_sec  * clock_val );
            const double   nano_convert( nanoseconds * 1.0e-9 );
            const double   curr_time( nano_convert + seconds );
            SystemClock::ClockQueue::sendTime( base_rtc_shm.queues[i], curr_time );
         }
      }
   }
}

void 
RealTimeClockSHM::initialize()
{
	const int success( 0 );
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
   queues = (SystemClock::ClockQueue*) SHM::Init( 
         &key_buffer[0],
         sizeof( SystemClock::ClockQueue )                   /* item size */,
         requestors                             /* nitems    */,
         true                                   /* zero      */);
   assert( queues != nullptr );      
}

SystemClock::ClockQueue*
RealTimeClockSHM::getClockQueueInstance( const char *shm_key )
{
   SystemClock::ClockQueue *output( nullptr );
   output = (SystemClock::ClockQueue*) SHM::Open( shm_key );
   return( output );
}

void
RealTimeClockSHM::closeClockQueueInstance( const char *shm_key,
                                           SystemClock::ClockQueue *ptr,
                                           size_t      num_timers )
{
   SHM::Close( shm_key,
               ptr,
               sizeof( SystemClock::ClockQueue ),
               num_timers,
               false,
               true );
               
}

const int
RealTimeClockSHM::getRequestors()
{
   return( requestors ); 
}