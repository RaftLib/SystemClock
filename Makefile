CXXFLAGS = -std=c++11 -O0 -g -Wall
CFLAGS   = -std=c99 -O0 -g -Wall

CXXFILES = Clock RealTimeClockSHM shm main
CFILES   = getrandom

CC = clang
CXX = clang++

LIBS = -lrt

OBJS  = $(addsuffix .o, $(CXXFILES)) $(addsuffix .o, $(CFILES))
FILES = $(addsuffix .cpp, $(CXXFILES)) $(addsuffix .c, $(CFILES))

clock: $(FILES)
	$(MAKE) $(OBJS)
	clang++ $(CXXFLAGS) -o clock $(OBJS) $(LIBS)

clean:
	rm -rf $(OBJS) clock
