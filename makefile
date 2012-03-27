CC = g++  -g
LD = g++ 
TARGET = maze
SOURCES = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

maze:$(OBJS)
	$(CC) $(OBJS) libglui.a -lglut -lglui  -o maze

clean: 
	@/bin/rm *.o
