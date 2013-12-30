/**
 * shm.hpp - 
 * @author: Jonathan Beard
 * @version: Thu Aug  1 14:26:34 2013
 */
#ifndef _SHM_HPP_
#define _SHM_HPP_  1

#include <stdlib.h>

class SHM{
public:
   SHM()          = delete;
   virtual ~SHM() = delete;
   /**
    * GenKey - generate a shared key at the memory 
    * address pointed to by ptr *key with length 
    * length.
    * @param   buffer - char *
    * @param   length - size_t
    */
   static void GenKey(char *buffer, size_t length);

   /**
    * Init - initialize SHM segment with file descriptor
    * key, with the number of items (nitems) and number
    * of bytes each (nbytes).  Returns NULL if error, and
    * prints the error code to std::cerr 
    * @param   key - const char *
    * @param   nbytes - size_t
    * @param   items - size_t
    * @param   zero  - zero before returning memory, default: true
    * @return  void* - ptr to beginning of memory allocated
    */
   static void*   Init( const char *key, 
                        size_t nbytes,
                        size_t nitems,
                        bool   zero = true );

   /** 
    * Open - opens the shared memory segment with the file
    * descriptor stored at key.
    * @param   key - const char *
    * @return  void* - start of allocated memory, or NULL if
    *                  error
    */
   static void*   Open( const char *key );

   /**
    * Close - returns true if successful, false otherwise.
    * @param   key - const char*
    * @param   ptr - start ptr to mapped region
    * @param   nbytes - number of bytes for each element in mapped region
    * @param   nitems - total number of items with size nbytes
    * @param   zero  - zero mapped region before closing, default: false
    * @return  bool - true if successful.
    */
   static bool    Close( const char *key, 
                         void *ptr,
                         size_t nbytes,
                         size_t nitems,
                         bool   zero = false ,
                         bool   unlink = false );
};

#endif /* END _SHM_HPP_ */
