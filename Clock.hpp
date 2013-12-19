/**
 * Clock.hpp - 
 * @author: Jonathan Beard
 * @version: Wed Dec 18 14:07:59 2013
 */
#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_  1

class ClockBase{
public:
   ClockBase() = default;
   virtual ~ClockBase() = default;
   
   virtual  void    init()  = 0;
   virtual  void    reset() = 0;

   virtual  clock_t getTime();
   virtual  clock_t getResolution();
protected:
   volatile clock_t *clock;
};

#endif /* END _CLOCK_HPP_ */
