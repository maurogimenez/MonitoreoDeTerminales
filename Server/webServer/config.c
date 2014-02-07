#include "myWebServer.h"
#include "../server.h"

#include <regex.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_SIZE 1024  //El tamanio debe ir acorde al tamanio del archivo que va a leer
#define debug 0

int config (char *cfgfile, char *puerto, char *droot){

    if (1 == debug) puts("config.c");

	char buff[BUFF_SIZE];
	int fd;
	
	memset (buff,'\0',sizeof buff);
	
	if ((fd = open(cfgfile, O_RDONLY)) < 0){
		perror ("open");
		return -1;
	}
	
	if (read(fd,buff,sizeof buff) < 0){
		perror ("read");
		return -1;
	}

	if (parse("droot=/.*(\\r|\\t|\\n|\\s)",buff,6,droot) < 0){
		perror("parse");
		return -1;
	}

//^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$

	if (parse("port=[0-9]?[0-9]?[0-9]?[0-9]?[0-9](\\r|\\t|\\n|\\s)",buff,5,puerto) < 0){
		perror("parse");
		return -1;
	}


    if (1 == debug) printf("fd:%d\nbuff:%s\ndroot:%s\nport:%s\n",fd,buff,droot,puerto);

	close(fd);
	
	return 0;
}
