#include "mySocket.h"

#include <unistd.h>
#include <stdio.h>

int protocol_handler(int protoId,int *sd,char *port){
	
	switch(protoId){
		 	case 0:  //IPV4 or IPV6
				if(unspec(sd,port) < 0) return -1;
				break;
			case 4:  //IPV4
				if(ipv4(sd,port) < 0) return -1;
				break;
			case 6:  //IPV6
				if (ipv6(sd,port) < 0) return -1;
				break;
			default:
				puts("Bad ProtocolId");
				return -1;
		}
	return 0;
}
