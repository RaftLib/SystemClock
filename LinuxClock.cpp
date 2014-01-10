/**
 * LinuxClock.cpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 14:08:38 2014
 */
#include "LinuxClock.hpp"

#define __GNU_SOURCE
#include <sched.h>
#include <cstdlib>
#include <cstdint>

void
LinuxClock::pinThreads( int core )
{
   const int success( 0 );
   cpu_set_t *cpuset( nullptr );
   const int8_t processors_to_allocate( 1 );
   size_t       cpu_allocate_size( -1 );
  
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
}   
