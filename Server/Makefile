CFLAGS := -Wall -g -pthread
TARGETS := serverMonitor
CC := gcc $(CFLAGS)

all: $(TARGETS)

serverMonitor: server.c webServer/config.c webServer/request.c webServer/response_header.c webServer/webServer.c utils/parse.c utils/Mmap.c utils/Malloc.c socket/ipv4.c socket/ipv6.c socket/unspec.c socket/protocol_handler.c monitor/statsController.c monitor/getSize.c monitor/getStats.c
	$(CC) -o $@ $^

clean:  
	rm -fv *.o *~ $(TARGETS)

test: all
	./serverMonitor

strace: all
	strace -f ./serverMonitor
