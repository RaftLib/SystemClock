AUTOMAKE_OPTIONS=foreign
AM_CXXFLAGS = -std=c++11  -O3 -DNOSERIAL=1
AM_CFLAGS   = -std=c99    -O3
AM_CPPFLAGS =  -I./$(top_srcdir)/include

noinst_LIBRARIES = libsystemclock.a
libsystemclock_a_SOURCES = Clock.cpp
