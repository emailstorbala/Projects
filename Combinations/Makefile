CC = g++
OBJS = getcombinations.o
EXECUTABLE = getcombinations 
CFLAGS = -Wall -s -O3 -std=c++20
LFLAGS = -s
LIBS=-lboost_program_options -lfmt

all:    $(EXECUTABLE)

$(EXECUTABLE):  $(OBJS)
	$(CC) $(LFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)

%.o:    %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f $(OBJS) $(EXECUTABLE)
