SystemClock
===========

###Description:
A simple front end for multiple clock back ends so that 
multiple threads may read the same clock value.  The 
minimum resolution (in this case latency) of multiple
back to back calls of the system clock is returned
through the latency function.  There are multiple x86
time-stamp counters in place, as well as linux and OSX 
system counters.  Time stamp counters aren't available
on OSX despite there being x86 processors in place since
there is no corresponding processor pinning which makes
it highly likely that the thread reading the time stamp
counter will migrate and make any subsequent TSC readings
invalid.

###TODO:
Future releases will add ARM support (soon).  There 
is a shared memory version floating around that I'll 
upload as well which is useful for multi-process timing.
If anybody wants to code up a TCP sync between multiple
systems that'd be cool too, although if you do, please
add the verification data to the verification data 
compressed folder so that folks who want to use it know
that it has in fact been tested.

###Building:
```bash
aclocal
autoconf
automake --add-missing
make check
```

###Other Notes:
Make check might fail, I need to re-work the way I test
some things since context swaps can heavily influence
short execution back-to-back timings when observing time
from a thread that is not synchronous with the timing 
thread.

Compiles with Linux (gcc, icc, clang) and on OS X (10.7 - 10.10)
with gcc,icc, and clang.  
