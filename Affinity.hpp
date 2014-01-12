/**
 * Affinity.hpp - 
 * @author: Jonathan Beard
 * @version: Sun Jan 12 13:41:31 2014
 */
#ifndef _AFFINITY_HPP_
#define _AFFINITY_HPP_  1
class Affinity {
public:
   virtual  bool  pinThreads( int core ) = 0;
};
#endif /* END _AFFINITY_HPP_ */
