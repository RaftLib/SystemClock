/**
 * Timer.hpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 13:41:34 2014
 */
#ifndef _TIMER_HPP_
#define _TIMER_HPP_  1

typedef uint64_t timer_t;

class Timer{
   Timer() : timerA( 0 ),
             timerB( 0 )
   {};

   timer_t  timerA;
   timer_t  timerB;
};

#endif /* END _TIMER_HPP_ */
