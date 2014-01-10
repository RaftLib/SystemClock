/**
 * LinuxClock.hpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 14:08:38 2014
 */
#ifndef _LINUXCLOCK_HPP_
#define _LINUXCLOCK_HPP_  1
#include "ClockBase.hpp"
class LinuxClock : public ClockBase {
public:
   bool  pinThreads( int core );
};
#endif /* END _LINUXCLOCK_HPP_ */
