AUTOMAKE_OPTIONS=foreign
AM_CXXFLAGS = -std=c++11  -O3 -DNOSERIAL=1 -DRDTSCP=1
AM_CFLAGS   = -std=c99    -O3
AM_CPPFLAGS =  -I. -I$(top_srcdir)/include 

TESTS = testclock
check_PROGRAMS = 
check_PROGRAMS += testclock
testclock_SOURCES = testclock.cpp
testclock_LDADD = -L./$(top_srcdir)/src -lsystemclock -lpthread -lrt
testclock_LDFLAGS  = -static
