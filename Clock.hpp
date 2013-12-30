/**
 * Clock.hpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_  1

#include "ClockQueue.hpp"

class ClockBase{
public:
   /**
    * ClockBase - default constructor, initializes data 
    * structures and sets the default resolution to
    * 1000 nanoseconds.  The clock is incremented with
    * whatever method the sub-class so chooses
    */
   ClockBase();

   /**
    * ClockBase - fancier constructor.  Initializes data
    * structures and sets the resolution to that which
    * is supplied in the constructor.  Time is kept in
    * seconds and nanoseconds to avoid unfortunate loss
    * of time due to round off errors.
    * @param   seconds - time_t
    * @param   nanoseconds - long
    */
   ClockBase( time_t seconds,
              long   nanoseconds );
   
   /**
    * ClockBase - even fancier constructor.  Initializes data
    * structures and sets the resolution to that which
    * is supplied in the constructor.  Time is kept in
    * seconds and nanoseconds to avoid unfortunate loss
    * of time due to round off errors.  The last param
    * is used to specify the core on which all sub-threads
    * will run.  If the core is outside the number of cores
    * available on this platorm then an assertion should
    * fail and will stop execution.
    *
    * @param   seconds - time_t
    * @param   nanoseconds - long
    */
   ClockBase( time_t seconds,
              long   nanoseconds,
              int    core );

   /**
    * Destructor - cleans up after the base class
    */
   virtual ~ClockBase();
  
   /**
    * initialize - Should be called before anything else, 
    */
   virtual void initialize();
   
protected:
   /** FUNCTIONS **/
   
   /**
    * start - starts the timer thread and the update
    * thread.  One thread serves the requests and 
    * another keeps up with the time.  
    */
   void  start();
   
   virtual void checkRequests()     = 0;
   virtual void serviceRequests()   = 0;
   /**
    * updateTime - called to update the time based one 
    * whatever virtual function implements this.
    */
   virtual void updateTime()        = 0;

   /** VARIABLES **/
   /* clock counter - pretty sure we'll never need to wrap */
   volatile std::atomic<uint64_t>         clock;
   /* current resolution of counter, actual time is clock * resolution */
   const struct timespec                  res;
   /* all current queues, one queue for each requesting function */
   volatile     SystemClock::ClockQueue  *queues;

private:
   const int    core;
   std::thread *clock_updater;
   std::thread *servicer;
};

#endif /* END _CLOCK_HPP_ */
