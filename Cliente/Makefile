CFLAGS := -Wall -g
TARGETS := clientMon
CC := gcc $(CFLAGS)

all: $(TARGETS)

clientMon: monitorClient.c getStats.c getStatsController.c Malloc.c format2protocol.c send2server.c Write.c refreshWait.c
	$(CC) -o $@ $^

clean:  
	rm -fv *.o *~ $(TARGETS)

test: all
	./clientMon

strace: all
	strace -f ./clientMon
