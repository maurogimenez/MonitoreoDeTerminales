#include "myWebServer.h"
#include "../utils/myUtils.h"

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

int request (char *buffer, char *droot, int csd){

	int fd=0;
	char *file;     //ruta+nombredearchivo
	char *ext;      //extension
	char *fileaux;  //nombretemporal
	char *filename; //nombre final del archivo (sin la ruta)
	
    if ( Malloc(&file,256) )    { return -1; }
    if ( Malloc(&ext,6) )       { return -1; }
    if ( Malloc(&fileaux,249) ) { return -1; }
    if ( Malloc(&filename,249) ){ return -1; }

	//Parseo la peticion
	if ( parse("GET /.*([\r\n])",buffer,5,fileaux) < 0 ){
		//	 free(file);
		//	 free(ext);
		//	 free(fileaux);
		//	 free(filename);
		puts("error parse_name");
		return -1;
	}

	filename=strtok(fileaux," ");
	//free(fileaux);

	if ( strstr(filename,"HTTP/1.") != NULL )  {puts("No args"); filename="index.html";}
	
	snprintf(file,strlen(filename)+strlen(droot)+1,"%s%s",droot,filename);  //Path al archivo
	//	free(filename);

	if ( (fd=open (file,O_RDONLY)) < 0 ){
		//	 free(file);
		//	 free(ext);
		puts("error open");
		return -10;
	}else{ 
		strtok(file,".");
		ext=strtok(NULL,".");

		printf("Extension: %s",ext);

		if (response_header(fd,ext,csd) < 0){  //HTTPResponse en base a la extension
			//	 free(file);
			//	 free(ext);
			close(fd);
			puts("error en response_header");
			return -1;
		}else{
			//	 free(ext);
			//	 free(file);
			close(fd);
			return 0;
		}
	}
}
