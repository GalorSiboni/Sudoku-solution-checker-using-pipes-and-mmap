CC=gcc
OBJS=v1.o v2.o check.o general.o
EXEC=v1 v2 check
CFLAGS = -std=gnu11

all: $(EXEC)

v1: v1.o general.o
	$(CC) -o $@ $^

v2: v2.o general.o
	$(CC) -o $@ $^

check: check.o general.o
	$(CC) -o $@ $^

v1.c: v1.h
v2.c: v2.h
check.c: check.h
general.c: general.h

clean: 
	rm -f $(EXEC) $(OBJS)
