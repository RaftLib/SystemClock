AUTOMAKE_OPTIONS=foreign
AM_CXXFLAGS = -std=c++11  -O3 -DNOSERIAL=1 -DRDTSCP=1
AM_CFLAGS   = -std=c99    -O3
AM_CPPFLAGS =  -I. -I$(top_srcdir)/include 

LINUXADD =
AM_LDFLAGS = 

if LINUX
LINUXADD    += -lrt -lpthread
AM_LDFLAGS  += -static -Wl,--no-whole-archive
endif

LDADD = -L./$(top_srcdir)/src -lsystemclock $(LINUXADD)

TESTS = testclock teststop

check_PROGRAMS = 
check_PROGRAMS += testclock
testclock_SOURCES = testclock.cpp

check_PROGRAMS += teststop
teststop_SOURCES = teststop.cpp
