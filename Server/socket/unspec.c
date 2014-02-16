#include "mysocket.h"
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <string.h>


int unspec(int *sd, char *puerto){
	
//	struct addrinfo hints, *res, *ptr;
//	int opc = 1;
//
//	puerto[strlen(puerto)-1]='\0'; //Reemplazo el ultimo caracter de puerto(\n) por \0
//	
//	memset(&hints,0,sizeof hints);
//	
//	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
 //  	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
//
//	int errcode;
//
//	if ( (errcode = getaddrinfo("localhost",puerto,&hints,&res)) != 0 ){
//		printf("Error unspec: %s\n", gai_strerror(errcode));
//		return -1;
//	}
//
//
//	for ( ptr = res; ptr != NULL; ptr = ptr->ai_next ){
//		*sd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//		if (*sd < 0){
//			perror("socket unspec");
//			continue;
//		}
//		if (setsockopt(*sd,SOL_SOCKET,SO_REUSEADDR,&opc,sizeof opc) < 0){
//			perror("setsockopt");
//		}
//		if (bind(*sd, ptr->ai_addr, ptr->ai_addrlen) == 0)
			return 0; //Exitoso!
//	}
//	close(*sd);
//	return -1;
}
