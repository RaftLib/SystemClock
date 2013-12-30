#ifndef _CLOCKQUEUE_HPP_
#define _CLOCKQUEUE_HPP_  1


namespace SystemClock{

struct ClockQueue
{
   ClockQueue() : request( 0 ),
                  send( 0 ),
                  time( 0.0 )
   {
      /** nothing to do here **/
   }

   static void requestTime( ClockQueue &queue )
   {
     queue.request = UINT32_MAX;
   }

   static void acknowledgeRequest( ClockQueue &queue )
   {
      queue.request = 0;
   }

   static void sendTime( ClockQueue &queue, const long double curr_time )
   {
      queue.time = curr_time;
      queue.send = UINT32_MAX;
   }

   static void acknowledgeSend( ClockQueue &queue )
   {
      queue.send = 0;
   }

   uint32_t       request;
   uint32_t       send;
   long double    time;
};

} /** end namespace SystemClock **/
#endif /* END _CLOCKQUEUE_HPP_ */
