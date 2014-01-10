/**
 * SHMClock.hpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 14:15:58 2014
 */
#ifndef _SHMCLOCK_HPP_
#define _SHMCLOCK_HPP_  1
#include <string>
#include "ClockBase.hpp"
class SHMClock : public ClockBase {
public:
   void  intialize();
protected:
   const std::string SHMKey;
};
#endif /* END _SHMCLOCK_HPP_ */
