#include <stdint.h>
#include <sys/types.h>

#define L1I 1
#define L1D 2
#define L2 3
#define L3 4

#ifdef __cplusplus
extern "C"{
#endif


uint32_t n_processors();

clock_t getStatedCPUFrequency();

clock_t getStatedBusFrequency();

size_t getCacheLineSize();

size_t getCacheSize(const uint8_t level);

uint64_t readTimeStampCounter();

void forcePreviousInstructionsToComplete();

#ifdef __cplusplus
}
#endif
