CFLAGS := -Wall -g
TARGETS := serverMonitor
CC := gcc $(CFLAGS)

all: $(TARGETS)

serverMonitor: monitorServer.c webServer/config.c parse.c socket/ipv4.c socket/ipv6.c socket/unspec.c
	$(CC) -o $@ $^

clean:  
	rm -fv *.o *~ $(TARGETS)

test: all
	./serverMonitor
