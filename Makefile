# The compiler flags used when compiling
CFLAGS= -std=c99 -Wall

allocate: allocate.o string.o scheduler.o pqueue.o process.o processor.o
	gcc $(CFLAGS) -o allocate allocate.o string.o scheduler.o pqueue.o process.o processor.o

allocate.o: allocate.c struct.h string.h pqueue.h process.h processor.h scheduler.h
	gcc $(CFLAGS) -c allocate.c

string.o: string.c string.h
	gcc $(CFLAGS) -c string.c

scheduler.o: scheduler.c scheduler.h struct.h
	gcc $(CFLAGS) -c scheduler.c

pqueue.o: pqueue.c pqueue.h struct.h
	gcc $(CFLAGS) -c pqueue.c 

process.o: process.c process.h struct.h
	gcc $(CFLAGS) -c process.c 

processor.o: processor.c processor.h struct.h
	gcc $(CFLAGS) -c processor.c 

.PHONY: clean

clean:
	rm -rf *.o allocate
