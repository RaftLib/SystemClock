/**
 * Clock.cpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#include "Clock.hpp"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <features.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include <sched.h>
#include <unistd.h>

ClockBase::ClockBase() : 
                         res( {0    /* seconds */,
                               1000 /* nanoseconds */ } ),
                         clock( 0 ),
                         queues( nullptr ),
								 core( 0 ),
								 updateTime( nullptr ),
								 clock_updater( nullptr )
{
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds ) : 
                                             res( { seconds,
                                                    nanoseconds } ),
                                             clock( 0 ),
                                             queues( nullptr ),
															core( 0 ),
								 							updateTime( nullptr ),
							 								clock_updater( nullptr )
{
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds,
                      int    core        ) : 
                                             res( { seconds,
                                                    nanoseconds } ),
                                             clock( 0 ),
                                             queues( nullptr ),
															core( core ),
								 							updateTime( nullptr ),
							 								clock_updater( nullptr )
{
}

ClockBase::~ClockBase()
{
   delete( clock_updater );
}
/**
 * start - starts the timer
 */
void
ClockBase::start()
{
   initialize();
   /** derived class must allocate the queues somewhere before here **/
   assert( queues != nullptr );
   try
   {
      clock_updater = new std::thread( updateTime, std::ref( *this ) );
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate clock updater thread, exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
	while( true )
   {
      checkRequests();
   }
}

void
ClockBase::initialize()
{
}

void
ClockBase::incrementClock()
{
	this->clock++;
}
