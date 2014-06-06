CXXFLAGS = -std=c++11 -O3
CFLAGS   = -std=c99   -O3 

CXXFILES = main Clock
CC   = gcc
CXX  = g++

ifneq ($(shell uname -s), Darwin)
RT = -lrt
STATIC = -static -static-libstdc++
endif

LIBS =-lpthread $(RT)


OBJS  = $(addsuffix .o, $(CXXFILES)) $(addsuffix .o, $(CFILES))
FILES = $(addsuffix .cpp, $(CXXFILES)) $(addsuffix .c, $(CFILES))

clock: $(FILES)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) $(STATIC) -o clock $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) clock
