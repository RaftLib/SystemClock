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
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds ) : clock_updater( nullptr ),
                                             servicer( nullptr ),
                                             clock( 0 ),
                                             res( { seconds,
                                                    nanoseconds } )
{
}

ClockBase::ClockBase( time_t seconds,
                      long   nanoseconds,
                      int    core        ) : clock_updater( nullptr ),
                                             servicer( nullptr ),
                                             clock( 0 ),
                                             res( { seconds,
                                                    nanoseconds } )
{
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
   /** derived class must allocate the queues somewhere before here **/
   assert( queues != nullptr );
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
   
   while( true )
   {
      checkRequests();
      serviceRequests();
   }
}

void
ClockBase::initialize()
{
}
