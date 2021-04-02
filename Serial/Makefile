SOURCES = data.c tcpServer.c udpServer.c server.c
SOURCES+= ../Common/ballQuery.c ../Common/gen_points.c
OBJS = $(SOURCES:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -g -w -std=gnu99 -fopenmp -03 #-I../
LDFLAGS=-lm
TARGET = BallAlg-Serial

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS)

main.o: main.c

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)