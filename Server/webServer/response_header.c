#include "myWebServer.h"

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


int response_header (int fd, char *ext, int csd){

	char buff[100];
	memset(buff,'\0',sizeof buff);
	
	int leido=0;
	
	char *ok="HTTP/1.0 200 OK\r\n";
	char *jpg="Content-Type: image/jpeg\n\n";
	char *pdf="Content-Type: application/pdf\n\n";
	char *html="Content-Type: text/html\n\n";
	char *txt="Content-Type: text/plain\n\n";

	if ( write (csd,ok,strlen(ok)) < 0){
		perror("write");
		return -1;
	}

	if ( (strcmp(ext,"jpg") == 0) || (strcmp(ext,"jpeg") == 0) || (strcmp(ext,"JPG") == 0) || (strcmp(ext,"JPEG") == 0) ){
		if ( write(csd,jpg,strlen(jpg)) < 0 ){
			perror("writejpg");
			return -1;
		}
	}else{
		if ( (strcmp(ext,"txt") == 0) || (strcmp(ext,"TXT") == 0 ) ){
			if ( write(csd,txt,strlen(txt)) < 0 ){
				perror("writetxt");
				return -1;
			}
		}else{
			if ( (strcmp(ext,"html") == 0) || (strcmp(ext,"HTML") == 0) ){
				if ( write(csd,html,strlen(html)) < 0 ){
					perror("writehtml");
					return -1;
				}
			}else{
				if ( (strcmp(ext,"pdf") == 0) || (strcmp(ext,"PDF") == 0) ){
					if ( write(csd,pdf,strlen(pdf)) < 0 ){
						perror("writepdf");
						return -1;
					}else{ //Extension no soportada
						puts("Extension invalida");
						return -1;
					}
				}
			}
		}
	}

	while ( (leido=read(fd,buff,100)) > 0 )
		if(write (csd,buff,leido) < 0){
			perror("write");
			return -1;
		}

	memset(buff,'\0',sizeof buff);
	return 0;
}
