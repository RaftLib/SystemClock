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
                         res( {0,1000} ),
                         selfdestruct( false ),
                         clock( 0 ),
                         queues( nullptr ),
								 core( 0 ),
								 updateTime( nullptr ),
                         checkRequestsFunction( nullptr ),
								 clock_updater( nullptr ),
                         requestor_thread( nullptr )
{
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds ) : 
                                             res( {seconds , nanoseconds } ),
                                             selfdestruct( false ),
                                             clock( 0 ),
                                             queues( nullptr ),
															core( 0 ),
								 							updateTime( nullptr ),
                                             checkRequestsFunction( nullptr ),
							 								clock_updater( nullptr ),
                                             requestor_thread( nullptr )
{
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds,
                      int    core        ) : 
                                             res({ seconds, nanoseconds } ),
                                             selfdestruct( false ),
                                             clock( 0 ),
                                             queues( nullptr ),
															core( core ),
								 							updateTime( nullptr ),
                                             checkRequestsFunction( nullptr ),
							 								clock_updater( nullptr ),
                                             requestor_thread( nullptr )
{
}

ClockBase::~ClockBase()
{
   /** threads cleaned up by calling callSelfDestruct() in derived class **/
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
   
   try
   {
      requestor_thread = new std::thread( checkRequestsFunction,
                                                   std::ref( (*this) ) ); 
   }
   catch( std::bad_alloc )
   {
      std::cerr << "Failed to allocate requestor thread, exiting!!\n";
      exit( EXIT_FAILURE );
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

void
ClockBase::callSelfDestruct()
{
   selfdestruct = true;
   clock_updater->join();
   delete( clock_updater );
   clock_updater = nullptr;
   requestor_thread->join();
   delete( requestor_thread );
   requestor_thread = nullptr;
}

const double
ClockBase::getRealTime()
{
   const auto val( clock.load( std::memory_order_relaxed ) );
   const double nanoseconds( (double)val * (double)res.tv_nsec * 1.0e-9 );
   const double output( nanoseconds + ( res.tv_sec * val ) );
   return( val * 4 );
}
