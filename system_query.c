#include <stdio.h>
#include <stdlib.h>
/* should include this for std=c99 */
#include <alloca.h>
#include <stdint.h>
#include <errno.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

#if (__APPLE__ == 1)
#include <sys/sysctl.h>
#endif

#if (__ARMEL__ == 1)
#include <time.h>
#endif

#if (__linux__ == 1)
#include <sys/sysinfo.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#endif


#if ARM
#include <linux/module.h>
#include <linux/kernel.h>
#endif

#include "system_query.h"

#ifndef USEPROCCPUINFO
#define USEPROCCPUINFO 1
#endif

/* forward declarations */
#if defined __linux__ && (USEPROCCPUINFO == 0)
extern unsigned long long int __get_clockfreq();
#endif
/* end forward declarations */

inline uint32_t n_processors(){
#ifdef __linux__
   const uint32_t n_procs = get_nprocs();
   return (n_procs);
#elif defined __APPLE__ || __BSD__
   uint32_t mib[4];
   uint32_t n_procs;
   size_t len = sizeof(n_procs);
   /* set the mib for hw.ncpu */
   mib[0] = CTL_HW;
   mib[1] = HW_AVAILCPU;
   /* get the number of CPUs from the system */
   sysctl(mib, 2, &n_procs, &len, NULL, 0);

   if( n_procs < 1 ) 
   {
        mib[1] = HW_NCPU;
        sysctl( mib, 2, &n_procs, &len, NULL, 0 );

        if( n_procs < 1 )
        {
            n_procs = 1;
        }
   }
   return (n_procs);
#else
#warning n_processors undefined for this platform!!
   return (-1);
#endif
}

inline clock_t getStatedCPUFrequency(){
#ifdef __linux__
#if __ARMEL__
   /* get info from /sys/devices
    * NOTE: must be running as root to do this!!
    */

#elif (USEPROCCPUINFO == 1)
   FILE  *fp = NULL;
   errno = 0;
   fp = fopen("/proc/cpuinfo", "r");
   if(fp == NULL)
   {
      perror( "Failed to read proc/cpuinfo!!\n" );
      return( EXIT_FAILURE );
   }
   const size_t buff_size = 20;
   char *key = (char*) alloca(sizeof(char) * buff_size);
   char *value = (char*) alloca(sizeof(char) * buff_size);
   assert( key != NULL );
   assert( value != NULL );
   memset( key, '\0', buff_size );
   memset( value, '\0', buff_size );
   clock_t clock = 0;
   int count = EOF;
   while( ( count = fscanf(fp,"%[^:]:%[^\n]\n", key, value) ) != EOF )
   {
      if( count == 2 ){
         /* TODO, not the best way to get CPU Frequency */
         if( strncmp( key, "cpu MHz", 7 ) == 0 )
         {
            clock = (clock_t) (atof( value ) * 1e6f );
            goto END;
         }
      }
   }
END:   
   fclose( fp );
   return( clock );
#else
   return ((clock_t)__get_clockfreq());
#endif
#elif defined __APPLE__ || __BSD__
   uint32_t mib[4];
   clock_t freq;
   size_t len = sizeof(freq);
   mib[0] = CTL_HW;
   mib[1] = HW_CPU_FREQ;
   sysctl(mib,2,&freq,&len,NULL,0);
   return (freq);
#else
#warning getStatedCPUFrequency undefined for this platform!!
   assert( false );
   return ( EXIT_FAILURE );
#endif
   /* keep the compiler happy */
   return( EXIT_SUCCESS );
}

inline clock_t getStatedBusFrequency(){
#ifdef __linux__
   return (0);
#elif defined __APPLE__ || __BSD__
   uint32_t mib[4];
   clock_t freq;
   size_t len = sizeof(freq);
   mib[0] = CTL_HW;
   mib[1] = HW_BUS_FREQ;
   sysctl(mib,2,&freq,&len,NULL,0);
   return (freq);
#else
#warning getStatedBusFrequency unsupported for this platform!!
   return (-1);
#endif
}

inline size_t getCacheLineSize(){
#ifdef __linux__
   return (0);
#elif defined __APPLE__ || __BSD__
   uint32_t mib[4];
   clock_t size;
   size_t len = sizeof(size);
   mib[0] = CTL_HW;
   mib[1] = HW_CACHELINE;
   sysctl(mib,2,&size,&len,NULL,0);
   return (size);
#else
#warning getCacheLineSize unsupported for this platform!!
   return (-1);
#endif
}

inline size_t getCacheSize(const uint8_t level){
#ifdef __linux__
   return (0);
#elif defined __APPLE__ || __BSD__
   uint32_t mib[4];
   clock_t size;
   size_t len = sizeof(size);
   mib[0] = CTL_HW;
   switch (level){
      case 1:
         mib[1] = HW_L1ICACHESIZE;
         break;
      case 2:
         mib[1] = HW_L1DCACHESIZE;
         break;
      case 3:
         mib[1] = HW_L2CACHESIZE;
         break;
      case 4:
         mib[1] = HW_L3CACHESIZE;
         break;
      default:
         fprintf(stderr,"Error, invalid level %d!!\n",level);
         exit(-1);
         break;
   }
   sysctl(mib,2,&size,&len,NULL,0);
   return (size);
#else
#warning getCacheSize unsupported for this platform!!
   return (-1);
#endif
}

inline uint64_t readTimeStampCounter()
{
   uint64_t cycles = 0;

#if __ARMEL__
   struct timespec ts;
   errno = 0;
   if( clock_gettime( CLOCK_REALTIME, &ts ) != 0 )
   {
      perror( "Failed to read real time clock, exiting!!\n");
      exit( EXIT_FAILURE );
   }
   /**
    * Note: we've got seconds and microseconds from the struct,
    * timespec:
    * struct timespec {
    *    time_t tv_sec;  //seconds
    *    long   tv_nsec; //nanoseconds
    * };
    * so we'll convert to microseconds since that's about the
    * best resolution we can hope for given that we're making
    * a function call to do this.
    */
    uint64_t micros( ts.tv_sec * 1e6 );
    micros += (ts.tv_nsec * 1e-3 );
    cycles = micros;
#else
/* x86 of some type */
#if __x86_64
   uint64_t highBits = 0x0, lowBits = 0x0;
   __asm__ volatile("\
      lfence                           \n\
      rdtsc                            \n\
      movq     %%rax, %[low]           \n\
      movq     %%rdx, %[high]"          
      :
      /*outputs here*/
      [low]    "=r" (lowBits),
      [high]   "=r" (highBits)
      :
      /*inputs here*/
      :
      /*clobbered registers*/
      "rax","rdx"
   );
   cycles = (lowBits & 0xffffffff) | (highBits << 32); 
#else
   uint32_t highBits = 0x0, lowBits = 0x0;
   __asm__ volatile("\
      lfence                           \n\
      rdtsc                            \n\
      movl     %%eax, %[low]           \n\
      movl     %%edx, %[high]"          
      :
      /*outputs here*/
      [low]    "=r" (lowBits),
      [high]   "=r" (highBits)
      :
      /*inputs here*/
      :
      /*clobbered registers*/
      "eax","edx"
   );
   cycles = highBits;
   cycles = (lowBits) | (cycles << 32); 
#endif /* tsc 32/64-bit x86 */

#endif /* end arm vs. x86 */
   return (cycles);
}

inline void forcePreviousInstructionsToComplete()
{
   __asm__ volatile("lfence "::);
}

