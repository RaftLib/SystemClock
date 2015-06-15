AUTOMAKE_OPTIONS=foreign
AM_CXXFLAGS = -std=c++11  -O3 -DNOSERIAL=1 -DRDTSCP=1
AM_CFLAGS   = -std=c99    -O3
AM_CPPFLAGS =  -I. -I$(top_srcdir)/include 


if BUILD_OS_IS_DARWIN
LINUX_LDADD = 
else
LINUX_LDADD = -lpthread -lrt
testclock_LDFLAGS  = -static
endif

TESTS = testclock teststop

check_PROGRAMS = 
check_PROGRAMS += testclock
testclock_SOURCES = testclock.cpp
testclock_LDADD = -L./$(top_srcdir)/src -lsystemclock $(LINUX_LDADD)

check_PROGRAMS += teststop
teststop_SOURCES = teststop.cpp
teststop_LDADD = -L./$(top_srcdir)/src -lsystemclock $(LINUX_LDADD)

