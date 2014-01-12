/**
 * OSXAffinity.hpp - 
 * @author: Jonathan Beard
 * @version: Sun Jan 12 13:41:31 2014
 */
#ifndef _OSXAFFINITY_HPP_
#define _OSXAFFINITY_HPP_  1
#include "Affinity.hpp"
class OSXAffinity : public Affinity {
public:
   virtual bool pinThreads( int core );
};
#endif /* END _OSXAFFINITY_HPP_ */
