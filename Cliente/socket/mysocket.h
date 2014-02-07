#ifndef MYSOCKET_H_
    #define MYSOCKET_H_
        
	int unspec(int* sd, char *port);
	int ipv4(int * sd, char *port);
	int ipv6(int * sd, char *port);

#endif
