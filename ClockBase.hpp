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
   virtual  void  initialize()= 0;
   virtual  void  start()     = 0;
   virtual  void  shutdown()  = 0;

protected:
   volatile Timer *timer;
};
#endif /* END _CLOCKBASE_HPP_ */
