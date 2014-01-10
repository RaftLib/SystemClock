/**
 * ClockBase.hpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 13:48:57 2014
 */
#ifndef _CLOCKBASE_HPP_
#define _CLOCKBASE_HPP_  1
#include "Timer.hpp"

class ClockBase { 
public:
   void  initialize()= 0;
   void  start()     = 0;
   void  shutdown()  = 0;

   static   double   getTime( volatile Timer *timer );
protected:
   volatile Timer *timer;
};
#endif /* END _CLOCKBASE_HPP_ */
