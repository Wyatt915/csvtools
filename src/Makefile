CC = g++
CFLAGS = -c -std=c++14

SRCS = dataset.cpp histogram.cpp main.cpp

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
