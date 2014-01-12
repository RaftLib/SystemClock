/**
 * LinuxAffinity.hpp - 
 * @author: Jonathan Beard
 * @version: Fri Jan 10 14:08:38 2014
 */
#ifndef _LINUXAFFINITY_HPP_
#define _LINUXAFFINITY_HPP_  1
#include "ClockBase.hpp"
class LinuxAffinity : public Affinity {
public:
   virtual  bool  pinThreads( int core );
};
#endif /* END _LINUXAFFINITY_HPP_ */
