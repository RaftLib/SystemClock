/**
 * Clock.hpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_  1

class ClockBase{
public:
   ClockBase()          = default;
   virtual ~ClockBase() = default;
   
   
protected:
   volatile clock_t *clock;
};

#endif /* END _CLOCK_HPP_ */
