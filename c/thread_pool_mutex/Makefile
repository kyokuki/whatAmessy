
CC=gcc
CFLAGS=-Wall -g
TARGET=TEST
LIBS=-lpthread

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

default:$(TARGET) 
all:default


$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS) $(LIBS)
	

.PHONY:clean
clean:
	-rm *.o
	-rm TEST
