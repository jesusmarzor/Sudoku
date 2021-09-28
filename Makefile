CC= g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -Wall -g -std=c++11
EXEC = Sudoku
DEPS = Sudoku.h
OBJS = Sudoku.o main.o
SRCS =  $(OBJS:.o=.cpp)

.PHONY: all clean doc

all: $(EXEC) #doc

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(EXEC):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

clean:
	$(RM) $(EXEC) $(EXEC).o $(OBJS)

doc: $(SRCS)
	doxygen
