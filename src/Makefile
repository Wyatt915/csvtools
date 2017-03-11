CC = g++
CFLAGS = -c -g -std=c++14

SRCS = dataset.cpp fileops.cpp histogram.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = csvtools

all: $(MAIN)
	@echo  Compiling finished.

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	rm *.o
