CXXFLAGS = -std=c++11 -O3
CFLAGS   = -std=c99 -O3

CXXFILES = main
CC = clang
CXX = clang++

LIBS =-lpthread -lrt

OBJS  = $(addsuffix .o, $(CXXFILES)) $(addsuffix .o, $(CFILES))
FILES = $(addsuffix .cpp, $(CXXFILES)) $(addsuffix .c, $(CFILES))

clock: $(FILES)
	$(MAKE) $(OBJS)
	clang++ $(CXXFLAGS) -o clock $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) clock
