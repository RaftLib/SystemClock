#ifndef _CLOCKQUEUE_HPP_
#define _CLOCKQUEUE_HPP_  1

#include <cstdint>
#include <iostream>

namespace SystemClock{

struct ClockQueue
{
   ClockQueue() : request( 0 ),
                  send( 0 ),
                  time( 0.0 ),
                  signal_high( UINT32_MAX ),
                  signal_low( 0 )
   {
      /** nothing to do here **/
   }

   static void requestTime(  volatile ClockQueue &queue )
   {
     queue.request = queue.signal_high;
   }

   static void acknowledgeRequest(  volatile ClockQueue &queue )
   {
      queue.request = queue.signal_low;
   }

   static void sendTime(  volatile ClockQueue &queue, const double curr_time )
   {
      queue.time = curr_time;
      queue.send = queue.signal_high;
   }

   static void acknowledgeSend(  volatile ClockQueue &queue )
   {
      queue.send = queue.signal_low;
   }

   static bool isRequestWaiting(  volatile ClockQueue &queue )
   {
      return( queue.request == queue.signal_high );
   }

   static double getTime(  volatile ClockQueue &queue )
   {
      requestTime( queue );
      volatile double output( 0.0 );
      while( queue.send ^ queue.signal_high /* spin till data avail */ )
      {
         output = queue.time;
      }
      acknowledgeSend( queue );
      return( output );
   }

   uint32_t       request;
   uint32_t       send;
   double         time;
   const uint32_t signal_high;
   const uint32_t signal_low;
};

} /** end namespace SystemClock **/
#endif /* END _CLOCKQUEUE_HPP_ */
