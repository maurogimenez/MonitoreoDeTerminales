CFLAGS := -Wall -g
TARGETS := clientMon
CC := gcc $(CFLAGS)

all: $(TARGETS)

clientMon: monitorClient.c socket/ipv4.c socket/ipv6.c socket/unspec.c getStats.c getStatsController.c
	$(CC) -o $@ $^

clean:  
	rm -fv *.o *~ $(TARGETS)

test: all
	./clientMon
