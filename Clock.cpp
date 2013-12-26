/**
 * Clock.cpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#include "Clock.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <features.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#include <sched.h>
#include <unistd.h>

ClockBase::ClockBase() : clock_updater( nullptr ),
                         servicer( nullptr ),
                         clock( 0 ),
                         res( {0    /* seconds */,
                               1000 /* nanoseconds */ } )
{
   try
   {
      clock_updater = new std::thread( updateTime );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate clock updater thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   try
   {
      servicer = new std::thread( start() );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate servicer thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   /** threads should now be rolling along until termination **/
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds ) : clock_updater( nullptr ),
                                             servicer( nullptr ),
                                             clock( 0 ),
                                             res( { seconds,
                                                    nanoseconds } )
{
   try
   {
      clock_updater = new std::thread( updateTime );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate clock updater thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   try
   {
      servicer = new std::thread( start() );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate servicer thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   /** threads should now be rolling along until termination **/
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds,
                      int    core        ) : clock_updater( nullptr ),
                                             servicer( nullptr ),
                                             clock( 0 ),
                                             res( { seconds,
                                                    nanoseconds } )
{
   try
   {
      clock_updater = new std::thread( updateTime );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate clock updater thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   try
   {
      servicer = new std::thread( start() );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate servicer thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   /** threads should now be rolling along until termination **/
}

ClockBase::~ClockBase()
{
   delete( clock_updater );
   delete( servicer      );
}
/**
 * start - starts the timer
 */
void
ClockBase::start()
{
   /** start clock thread **/
   assert( clock_updater != nullptr );
   clock_updater->start();
   while( true )
   {
      checkRequests();
      serviceRequests();
   }
}

void
ClockBase::initialize()
{
   /** do nothing **/
}

void
ClockBase::selfInitialize( int assigned_processor )
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
   CPU_SET( assigned_processor,
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
