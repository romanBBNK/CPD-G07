SOURCES = main.c tree.c
SOURCES+=
OBJS = $(SOURCES:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -g -w -std=gnu99 -fopenmp -O3 #-I../
LDFLAGS=-lm
TARGET = ballAlg-omp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

main.o: main.c

tree.o: tree.c tree.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)