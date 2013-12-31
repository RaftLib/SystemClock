CXXFLAGS = -std=c++11 -O3 -Wall
CFLAGS   = -std=c99 -O3 -Wall

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
