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

template <int N> class RealTimeClock : public ClockBase
{
public:
   RealTimeClock( time_t seconds,
                  long   nanoseconds,
                  int    core         ) : ClockBase( resolution ),
                                          local_resolution( { seconds,
                                                              nanoseconds } ),
                                          core( core )
   {
      /* nothing to be done here */
   }

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
       
   }                

   virtual void initialize()
   {
      const int ret_val( clock_nanosleep( CLOCK_REALTIME /* clock ID */ ,
                                          0              /* flags */    ,
                                          /* request */ ,
                                          /* remain struct timespec  */
                                        ) );
   }

private:
   const struct timespec local_resolution;
};
#endif /* END _REALTIMECLOCK_TCC_ */
