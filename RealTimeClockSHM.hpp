/**
 * RealTimeClockSHM.hpp - 
 * @author: Jonathan Beard
 * @version: Tue Dec 31 10:23:23 2013
 */
#ifndef _REALTIMECLOCKSHM_HPP_
#define _REALTIMECLOCKSHM_HPP_  1

#include "Clock.hpp"
#include "ClockQueue.hpp"
#include <cstdlib>


class RealTimeClockSHM : public ClockBase
{
public:

   RealTimeClockSHM( int num_requestors,
                  const char* key,
                  size_t key_length  ); 
                                         

   RealTimeClockSHM( time_t seconds,
                  long nanoseconds,
                  int num_requestors,
                  const char *key,
                  size_t key_length  ); 

   RealTimeClockSHM( time_t seconds,
                  long   nanoseconds,
                  int    core,
                  int    num_requestors,
                  const char *key,
                  size_t key_length     ); 

   virtual ~RealTimeClockSHM();

   static SystemClock::ClockQueue* getClockQueueInstance( const char *shm_key );
   static void closeClockQueueInstance( const char              *shm_key,
                                        SystemClock::ClockQueue *ptr,
                                        size_t                   num_timers );

   const int   getRequestors();

   /** function gets passed to base class **/                                
   static void updateTimeFunction( ClockBase &base );
   static void theCheckRequestsFunction( ClockBase &base );
protected:
   virtual void initialize();

private:
   const int requestors;
   char      key_buffer[32];
};
#endif /* END _REALTIMECLOCKSHM_HPP_ */
