SOURCES = ballQuery.c gen_points.c
SOURCES+=
OBJS = $(SOURCES:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -g -w -std=gnu99 -fopenmp -O3 #-I../
LDFLAGS=-lm
TARGET = ballQuery

all: $(OBJS)
	#$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

ballQuery.o: ballQuery.c

gen_points.o: gen_points.c

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)