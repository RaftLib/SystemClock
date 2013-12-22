/**
 * Clock.cpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#include "Clock.hpp"
#include <time.h>
#include <features.h>

ClockBase::ClockBase() : clock_updater( nullptr ),
                         clock( 0 ),
                         res( 100.00e-9 )
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
}

ClockBase::ClockBase( theclock_t resolution) : clock_updater( nullptr ),
                                               clock( 0 ),
                                               res( resolution )
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
   /** start clock thread **/
   while( true )
   {
      checkRequests();
      serviceRequests();
   }
}


void
ClockBase::updateTime()
{
   
}
