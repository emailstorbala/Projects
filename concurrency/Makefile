OBJS = FileDetails.o Concurrent.o main.o
EXECUTABLE = FileDetails
CFLAGS = -Wall -s -O3 -std=c++17
LFLAGS = -s
CC = g++
LIBS=-lboost_program_options -lpthread

all:    $(EXECUTABLE)

$(EXECUTABLE):  $(OBJS)
	$(CC) $(LFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)

%.o:    %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f $(OBJS) $(EXECUTABLE)
