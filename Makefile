#check wheter to build on linux or on windows
ifeq "$(OS)" "Windows_NT"
	CC=gcc
	LD=g++
	CFLAGS=-I"C:\MinGW\freeglut\include" -c 
	LDFLAGS=-L"C:\MinGW\freeglut\lib" -L"lib\windows" -lglew32 -lfreeglut -lglu32 -lopengl32 -static-libgcc -static-libstdc++
#add this when removing console
#-Wl,--subsystem,windows
	BINDIR=bin/windows
	FINALFILE=cubiverse.exe
else
	CC=g++
	LD=g++
	CFLAGS=-g -lboost_system -lboost_thread
	LDFLAGS=-g -L"lib/linux" -lm -lboost_system -lboost_signals -lboost_thread -lGL -lGLU -lglut -lGLEW
	BINDIR=bin/linux
	FINALFILE=cubiverse
endif

#BINDIR=bin
SRCS = $(wildcard src/*.cpp src/voxelart_engine/*.cpp)
OBJS = $(patsubst src/%.cpp,$(BINDIR)/%.o,$(SRCS))

game: $(OBJS)
	@echo $(SRCS)" | "$(OBJS)
	@echo "Testing out whats going on"
	$(LD)  $(OBJS) -o $(FINALFILE) $(LDFLAGS)

$(BINDIR)/%.o : src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR):
	mkdir $(BINDIR)
