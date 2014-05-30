CXXFLAGS = -std=c++11 -O0 -g
CFLAGS   = -std=c99   -O0 -g

CXXFILES = main
CC   = clang
CXX  = clang++

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
