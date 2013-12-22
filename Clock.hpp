/**
 * Clock.hpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_  1

typedef long double theclock_t;

class ClockBase{
public:
   ClockBase();
   virtual ~ClockBase();
  
   /**
    * start - starts the timer 
    */
   void  start();
   
protected:
   /** FUNCTIONS **/
   virtual void checkRequests()     = 0;
   virtual void serviceRequests()   = 0;
   
   /**
    * updateTime - called to update the time based one 
    * whatever virtual function implements this.
    */
   virtual void updateTime();

   /** VARIABLES **/
   volatile uint64_t timer;
   const theclock_t  res;
private:
   
   std::thread *clock_updater;
};

#endif /* END _CLOCK_HPP_ */
